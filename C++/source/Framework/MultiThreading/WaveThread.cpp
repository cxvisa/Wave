/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/MultiThreading/WaveThread.h"
#include "Framework/Messaging/Local/WaveMessage.h"
#include "Framework/Messaging/Local/WaveEvent.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Messaging/Remote/InterLocationMessageTransportObjectManager.h"
#include "Framework/Messaging/Remote/InterLocationMessageReceiverObjectManager.h"
#include "Framework/Messaging/HaPeer/HaPeerMessageTransportObjectManager.h"
#include "WaveResourceIdEnums.h"
#include "Framework/ObjectModel/ReservedWaveLocalObjectManager.h"

#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sched.h>

using namespace std;

namespace WaveNs
{

static WaveServiceMap                         *s_pWaveServiceMap                                       = NULL;

       map<WaveThreadId, WaveObjectManager *>  WaveThread::m_prismThreadIdToWaveObjectManagerMap;
       WaveMutex                               WaveThread::m_prismThreadIdToWaveObjectManagerMapMutex;

WaveThread::WaveThread (WaveServiceId id, const string &serviceName, const UI32 &stackSize, const vector<UI32> *pCpuAffinityVector)
    : PrismPosixThread    (stackSize),
      m_waveServiceId    (id),
      m_wakeupCaller      (),
      m_wakeupCondition   (&m_wakeupCaller),
      m_cpuAffinityVector (*pCpuAffinityVector),
      m_terminateThread   (false)
{
    if (NULL == s_pWaveServiceMap)
    {
        s_pWaveServiceMap = new WaveServiceMap ();
    }

    s_pWaveServiceMap->addServiceMap (m_waveServiceId, this, serviceName);
    initializeHoldCounts ();
}

WaveThread::WaveThread (WaveServiceId id, WaveObjectManager *pWaveObjectManager, const string &serviceName, const UI32 &stackSize, const vector<UI32> *pCpuAffinityVector)
    : PrismPosixThread    (stackSize),
      m_waveServiceId    (id),
      m_wakeupCaller      (),
      m_wakeupCondition   (&m_wakeupCaller),
      m_cpuAffinityVector (*pCpuAffinityVector),
      m_terminateThread   (false)
{
    if (NULL == s_pWaveServiceMap)
    {
        s_pWaveServiceMap = new WaveServiceMap ();
    }

    s_pWaveServiceMap->addServiceMap (m_waveServiceId, this, serviceName);
    addWaveObjectManager (pWaveObjectManager);
    initializeHoldCounts ();
}

WaveThread::~WaveThread ()
{
    s_pWaveServiceMap->removeServiceMap (m_waveServiceId);

    UI32 numberOfWaveObjectManagers = m_pWaveObjectManagers.size ();
    UI32 i                          = 0;

    for (i = 0 ;i < numberOfWaveObjectManagers; i++)
    {
        delete m_pWaveObjectManagers[i];
    }

    WaveThreadId thisThreadId = pthread_self ();

    prismAssert (1 == numberOfWaveObjectManagers, __FILE__, __LINE__); // For now, enforce that there is exactly on Wave OM per thread.

    m_prismThreadIdToWaveObjectManagerMapMutex.lock ();

    m_prismThreadIdToWaveObjectManagerMap.erase (m_prismThreadIdToWaveObjectManagerMap.find (thisThreadId));

    m_prismThreadIdToWaveObjectManagerMapMutex.unlock ();
}

WaveThreadStatus WaveThread::start ()
{
    UI32          numberOfWaveObjectManagers = m_pWaveObjectManagers.size ();
    WaveThreadId thisThreadId               = pthread_self ();

    prismAssert (1 == numberOfWaveObjectManagers, __FILE__, __LINE__); // For now, enfore that there is exactly on Wave OM per thread.

    while (true)
    {
        if (true == (FrameworkToolKit::isFrameworkReadyToBoot ()))
        {
            break;
        }

        prismUSleep (10000);
    }

    m_prismThreadIdToWaveObjectManagerMapMutex.lock ();
    m_prismThreadIdToWaveObjectManagerMap[thisThreadId] = m_pWaveObjectManagers[0];
    //trace (TRACE_LEVEL_INFO, string ("WaveThread::start : Prism Thread ID ") + thisThreadId + string (" corresponds to Wave OM : ") + (m_pWaveObjectManagers[0])->getName ());
    m_prismThreadIdToWaveObjectManagerMapMutex.unlock ();

    setCpuAffinity (m_cpuAffinityVector);

    WaveMessage *pWaveMessage = NULL;
    WaveEvent   *pWaveEvent   = NULL;

    while (true)
    {
        if (true == m_terminateThread)
        {
            break;
        }

        m_gateKeeper.lock ();

        pWaveMessage = getNextMessageToProcess ();

        if (NULL == pWaveMessage)
        {
            m_wakeupCaller.lock ();
            m_gateKeeper.unlock ();
            m_wakeupCondition.wait ();
            m_wakeupCaller.unlock ();
        }
        else
        {
            m_gateKeeper.unlock ();

            WaveObjectManager *pWaveObjectManager = NULL;

            switch (pWaveMessage->getType ())
            {
                case WAVE_MESSAGE_TYPE_REQUEST :
                    pWaveObjectManager = getWaveObjectManagerForOperationCode (pWaveMessage->getOperationCode ());

                    if (NULL != pWaveObjectManager)
                    {
                        pWaveObjectManager->handleWaveMessage (pWaveMessage);
                    }
                    else
                    {
                        pWaveMessage->setCompletionStatus (WAVE_THREAD_ERROR_COULD_NOT_FIND_OM);

                        if (0 < m_pWaveObjectManagers.size ())
                        {
                            m_pWaveObjectManagers[0]->reply (pWaveMessage);
                        }
                        else
                        {
                            cerr << "This Service does not have any object managers to handle any requests.";
                            prismAssert (false, __FILE__, __LINE__);
                        }
                    }

                    break;

                case WAVE_MESSAGE_TYPE_RESPONSE :
                    pWaveObjectManager = getWaveObjectManagerForWaveMessageId (pWaveMessage->getMessageId ());

                    if (NULL != pWaveObjectManager)
                    {
                        pWaveObjectManager->handleWaveMessageResponse (FRAMEWORK_SUCCESS, pWaveMessage);
                    }
                    else
                    {
                        trace (TRACE_LEVEL_FATAL, "Failed to deliver response : Could not find corresponding Prism Object Manager.");
                        trace (TRACE_LEVEL_FATAL, string ("ServiceCode = ") + pWaveMessage->getServiceCode () + string (", OperationCode = ") + pWaveMessage->getOperationCode () +  string(", MessageId = ") + pWaveMessage->getMessageId ());
                        prismAssert (false, __FILE__, __LINE__);
                    }

                    break;

                case WAVE_MESSAGE_TYPE_EVENT :
                    pWaveEvent = dynamic_cast<WaveEvent *> (pWaveMessage);
                    prismAssert( NULL != pWaveEvent , __FILE__ , __LINE__);

                    pWaveObjectManager = getWaveObjectManagerForEventOperationCodeForListening (pWaveEvent->getSenderLocationId (), pWaveEvent->getServiceCode (), pWaveEvent->getOperationCode ());

                    if (NULL != pWaveObjectManager)
                    {
                        const WaveEvent *pTempEvent = reinterpret_cast <const WaveEvent *> (pWaveEvent);

                        pWaveObjectManager->handleWaveEvent (pTempEvent);
                    }
                    else
                    {
                        cerr << "This Service does not have any object managers to handle any events.";
                        prismAssert (false, __FILE__, __LINE__);

                        delete pWaveEvent;
                    }

                    break;

                default :
                    cerr << "WaveThread::start : Unknown message type : " << pWaveMessage->getType () << ", Service : " << s_pWaveServiceMap->getPrismServiceNameForServiceId (m_waveServiceId) << endl;
                    prismAssert (false, __FILE__, __LINE__);

                    break;
            }
        }
    }

    delete this;

    stopCallingThread ();

    // We should never reach here.  The above statement ends the execution of the thread.

    return (WAVE_THREAD_SUCCESS);
}

WaveThreadStatus WaveThread::consumePendingMessages ()
{
    while (true)
    {
        if (true == (FrameworkToolKit::isFrameworkReadyToBoot ()))
        {
            break;
        }

        prismSleep (1);
    }

    WaveMessage *pWaveMessage = NULL;
    WaveEvent   *pWaveEvent   = NULL;

    while (true)
    {
        if (true == m_terminateThread)
        {
            break;
        }

        m_gateKeeper.lock ();

        pWaveMessage = getNextMessageToProcess ();

        if (NULL == pWaveMessage)
        {
            m_gateKeeper.unlock ();

            return (WAVE_THREAD_SUCCESS);
        }
        else
        {
            m_gateKeeper.unlock ();

            WaveObjectManager *pWaveObjectManager = NULL;

            switch (pWaveMessage->getType ())
            {
                case WAVE_MESSAGE_TYPE_REQUEST :
                    pWaveObjectManager = getWaveObjectManagerForOperationCode (pWaveMessage->getOperationCode ());

                    if (NULL != pWaveObjectManager)
                    {
                        pWaveObjectManager->handleWaveMessage (pWaveMessage);
                    }
                    else
                    {
                        pWaveMessage->setCompletionStatus (WAVE_THREAD_ERROR_COULD_NOT_FIND_OM);

                        if (0 < m_pWaveObjectManagers.size ())
                        {
                            m_pWaveObjectManagers[0]->reply (pWaveMessage);
                        }
                        else
                        {
                            cerr << "This Service does not have any object managers to handle any requests.";
                            prismAssert (false, __FILE__, __LINE__);
                        }
                    }

                    break;

                case WAVE_MESSAGE_TYPE_RESPONSE :
                    pWaveObjectManager = getWaveObjectManagerForWaveMessageId (pWaveMessage->getMessageId ());

                    if (NULL != pWaveObjectManager)
                    {
                        pWaveObjectManager->handleWaveMessageResponse (FRAMEWORK_SUCCESS, pWaveMessage);
                    }
                    else
                    {
                        cout << ": Failed to deliver response : Could not find corresponding Prism Object Manager." << endl;
                        cout << "ServiceCode = " << pWaveMessage->getServiceCode () << ", OperationCode = " << pWaveMessage->getOperationCode () << ", MessageId = " << pWaveMessage->getMessageId () << endl;
                        prismAssert (false, __FILE__, __LINE__);
                    }

                    break;

                case WAVE_MESSAGE_TYPE_EVENT :

                    pWaveEvent = dynamic_cast<WaveEvent *> (pWaveMessage);
                    prismAssert( NULL != pWaveEvent , __FILE__ , __LINE__);

                    pWaveObjectManager = getWaveObjectManagerForEventOperationCodeForListening (pWaveEvent->getSenderLocationId (), pWaveEvent->getServiceCode (), pWaveEvent->getOperationCode ());

                    if (NULL != pWaveObjectManager)
                    {
                        const WaveEvent *pTempEvent = reinterpret_cast <const WaveEvent *> (pWaveEvent);

                        pWaveObjectManager->handleWaveEvent (pTempEvent);
                    }
                    else
                    {
                        cerr << "This Service does not have any object managers to handle any events.";
                        prismAssert (false, __FILE__, __LINE__);

                        delete pWaveEvent;
                    }

                    break;

                default :
                    cerr << "WaveThread::consumePendingMessages : Unknown message type : " << pWaveMessage->getType () << ", Service : " << s_pWaveServiceMap->getPrismServiceNameForServiceId (m_waveServiceId) << endl;
                    prismAssert (false, __FILE__, __LINE__);

                    break;
            }
        }
    }

    stopCallingThread ();

    // We should never reach here.  The above statement ends the execution of the thread.

    return (WAVE_THREAD_SUCCESS);
}

WaveMessageStatus WaveThread::submitMessage (WaveMessage *pWaveMessage)
{
    prismAssert (NULL != pWaveMessage, __FILE__, __LINE__);

    WaveMessagePriority messagePriority = pWaveMessage->getPriority ();

    // Check if the message has been submitted to a wrong thread.  This done by comparing this thread serviceid
    // to the message serviceid.
    // there is a n exception to this.  If the this thread serviceid is WAVE_SERVICE_INTER_LOCATION_MESSAGE_TRANSPORT, then
    // the thread will receive messages destined for other services since the thread has to transport to remote locations.

    if (((InterLocationMessageTransportObjectManager::getWaveServiceId ()) != m_waveServiceId) &&
         ((HaPeerMessageTransportObjectManager::getWaveServiceId ()) != m_waveServiceId) &&
         (m_waveServiceId != (pWaveMessage->getServiceCode ())))
    {
        cerr << "WaveThread::submitMessage : Internal Error : Submitted message to a wrong Prism Thread." << endl;
        prismAssert (false, __FILE__, __LINE__);
        return (WAVE_MESSAGE_ERROR_SUBMIT_TO_INVALID_THREAD);
    }

    // Before proceeding check if the Service has been enabled to accept messages other services.
    // We accept a few messages even before the service is enabled.  We accept messages like initialize
    // and enable messages.

    UI32                operationCode       = pWaveMessage->getOperationCode ();
    WaveObjectManager *pWaveObjectManager = getWaveObjectManagerForOperationCode (operationCode);

    // by the time we reach here we must not encounter a NULL WaveObjectManager.

    if (NULL == pWaveObjectManager)
    {
        trace (TRACE_LEVEL_FATAL, string ("WaveThread::submitMessage : There is no ObjectManager registered to rceive this operation code (") + operationCode + ").");
        prismAssert (false, __FILE__, __LINE__);
        return (WAVE_MESSAGE_ERROR_NO_OM_TO_ACCEPT_MESSAGE);
    }
    else
    {
        if (false == (pWaveObjectManager->getIsEnabled ()))
        {
            if (true == (pWaveObjectManager->isOperationAllowedBeforeEnabling (operationCode)))
            {
                // We cannot use trace method here.  It will lead to an infinite recursion because the trace service
                // might not have been enabled.  Also the trace statement causes invoking subMitMessage.

                // trace (TRACE_LEVEL_DEBUG, string ("WaveThread::submitMessage : Allowing the operation (") + operationCode + ") before enabling the service.");
            }
            else
            {
                trace (TRACE_LEVEL_DEBUG, "WaveThread::submitMessage : The Service (" + FrameworkToolKit::getServiceNameById (pWaveObjectManager->getServiceId ()) + ") is not enabled yet.  Try later.");
                return (WAVE_MESSAGE_ERROR_SERVICE_NOT_ENABLED);
            }
        }
    }

    WaveMessageStatus status = WAVE_MESSAGE_SUCCESS;

    m_gateKeeper.lock ();

    m_wakeupCaller.lock ();

    // We treat timer expirations differently.  Timer expirations will be handled when they expire.
    // Even if the messages, high priority messages and events are held for the service, still we deliver the
    // timer expiration notifications.  To achieve this we have a separate queue dedicated for for Timer Expiration notifications
    // messages.  Whenever the Timer service sends such a notification message that messages goes into a separate queue.  Otherwise
    // all the messages go into repective queues according to their priority and type.

    UI32 opertionCode = pWaveMessage->getOperationCode ();

    if ((WAVE_OBJECT_MANAGER_RESUME == operationCode) || (true == pWaveMessage->getIsMessageSupportedWhenServiceIsPaused ()))
    {
        m_frameworkResumeMessages.insertAtTheBack (pWaveMessage);
    }
    else if (WAVE_OBJECT_MANAGER_PAUSE == operationCode)
    {
        m_frameworkMessages.insertAtTheFront (pWaveMessage);
    }
    else if (WAVE_OBJECT_MANAGER_TIMER_EXPIRED == opertionCode) // For Timer Expiration Messages
    {
        m_timerExpirations.insertAtTheBack (pWaveMessage); // for all the other Framework messages like initialize, enable etc.,
    }
    else if (opertionCode >= (UINT_MAX - 1001))
    {
        m_frameworkMessages.insertAtTheBack (pWaveMessage);
    }
    else
    {
        if (WAVE_MESSAGE_PRIORITY_HIGH == messagePriority)
        {
            m_highPriorityMessages.insertAtTheBack (pWaveMessage);
        }
        else if (WAVE_MESSAGE_PRIORITY_NORMAL == messagePriority)
        {
            m_messages.insertAtTheBack (pWaveMessage);
        }
        else
        {
            cout << "WaveThread::submitMessage : Submitting message with unknown priority (" << messagePriority << ")." << endl;
            prismAssert (false, __FILE__, __LINE__);
            status = WAVE_MESSAGE_ERROR_UNKNOWN_PRIORITY;
        }
    }

    m_wakeupCondition.resume ();

    m_wakeupCaller.unlock ();

    m_gateKeeper.unlock ();

    return (status);
}

WaveMessageStatus WaveThread::submitMessageAtFront (WaveMessage *pWaveMessage)
{
    prismAssert (NULL != pWaveMessage, __FILE__, __LINE__);

    WaveMessagePriority messagePriority = pWaveMessage->getPriority ();

    // Check if the message has been submitted to a wrong thread.  This done by comparing this thread serviceid
    // to the message serviceid.
    // there is a n exception to this.  If the this thread serviceid is WAVE_SERVICE_INTER_LOCATION_MESSAGE_TRANSPORT, then
    // the thread will receive messages destined for other services since the thread has to transport to remote locations.

    if (((InterLocationMessageTransportObjectManager::getWaveServiceId ()) != m_waveServiceId) &&
         ((HaPeerMessageTransportObjectManager::getWaveServiceId ()) != m_waveServiceId) &&
         (m_waveServiceId != (pWaveMessage->getServiceCode ())))
    {
        cerr << "WaveThread::submitMessageAtFront : Internal Error : Submitted message to a wrong Prism Thread." << endl;
        prismAssert (false, __FILE__, __LINE__);
        return (WAVE_MESSAGE_ERROR_SUBMIT_TO_INVALID_THREAD);
    }

    // Before proceeding check if the Service has been enabled to accept messages other services.
    // We accept a few messages even before the service is enabled.  We accept messages like initialize
    // and enable messages.

    UI32                operationCode       = pWaveMessage->getOperationCode ();
    WaveObjectManager *pWaveObjectManager = getWaveObjectManagerForOperationCode (operationCode);

    // by the time we reach here we must not encounter a NULL WaveObjectManager.

    if (NULL == pWaveObjectManager)
    {
        trace (TRACE_LEVEL_FATAL, string ("WaveThread::submitMessageAtFront : There is no ObjectManager registered to rceive this operation code (") + operationCode + ").");
        prismAssert (false, __FILE__, __LINE__);
        return (WAVE_MESSAGE_ERROR_NO_OM_TO_ACCEPT_MESSAGE);
    }
    else
    {
        if (false == (pWaveObjectManager->getIsEnabled ()))
        {
            if (true == (pWaveObjectManager->isOperationAllowedBeforeEnabling (operationCode)))
            {
                // We cannot use trace method here.  It will lead to an infinite recursion because the trace service
                // might not have been enabled.  Also the trace statement causes invoking subMitMessage.

                // trace (TRACE_LEVEL_DEBUG, string ("WaveThread::submitMessage : Allowing the operation (") + operationCode + ") before enabling the service.");
            }
            else
            {
                trace (TRACE_LEVEL_DEBUG, "WaveThread::submitMessageAtFront : The Service (" + FrameworkToolKit::getServiceNameById (pWaveObjectManager->getServiceId ()) + ") is not enabled yet.  Try later.");
                return (WAVE_MESSAGE_ERROR_SERVICE_NOT_ENABLED);
            }
        }
    }

    WaveMessageStatus status = WAVE_MESSAGE_SUCCESS;

    m_gateKeeper.lock ();

    m_wakeupCaller.lock ();

    // We treat timer expirations differently.  Timer expirations will be handled when they expire.
    // Even if the messages, high priority messages and events are held for the service, still we deliver the
    // timer expiration notifications.  To achieve this we have a separate queue dedicated for for Timer Expiration notifications
    // messages.  Whenever the Timer service sends such a notification message that messages goes into a separate queue.  Otherwise
    // all the messages go into repective queues according to their priority and type.

    UI32 opertionCode = pWaveMessage->getOperationCode ();

    if (WAVE_OBJECT_MANAGER_RESUME == operationCode)
    {
        m_frameworkResumeMessages.insertAtTheFront (pWaveMessage);
    }
    else if (WAVE_OBJECT_MANAGER_PAUSE == operationCode)
    {
        m_frameworkMessages.insertAtTheFront (pWaveMessage);
    }
    else if (WAVE_OBJECT_MANAGER_TIMER_EXPIRED == opertionCode) // For Timer Expiration Messages
    {
        m_timerExpirations.insertAtTheFront (pWaveMessage); // for all the other Framework messages like initialize, enable etc.,
    }
    else if (opertionCode >= (UINT_MAX - 1001))
    {
        m_frameworkMessages.insertAtTheFront (pWaveMessage);
    }
    else
    {
        if (WAVE_MESSAGE_PRIORITY_HIGH == messagePriority)
        {
            m_highPriorityMessages.insertAtTheFront (pWaveMessage);
        }
        else if (WAVE_MESSAGE_PRIORITY_NORMAL == messagePriority)
        {
            m_messages.insertAtTheFront (pWaveMessage);
        }
        else
        {
            cout << "WaveThread::submitMessageAtFront : Submitting message with unknown priority (" << messagePriority << ")." << endl;
            prismAssert (false, __FILE__, __LINE__);
            status = WAVE_MESSAGE_ERROR_UNKNOWN_PRIORITY;
        }
    }

    m_wakeupCondition.resume ();

    m_wakeupCaller.unlock ();

    m_gateKeeper.unlock ();

    return (status);
}

WaveMessageStatus WaveThread::submitMessageAtBack (WaveMessage *pWaveMessage)
{
    prismAssert (NULL != pWaveMessage, __FILE__, __LINE__);

    WaveMessagePriority messagePriority = pWaveMessage->getPriority ();

    // Check if the message has been submitted to a wrong thread.  This done by comparing this thread serviceid
    // to the message serviceid.
    // there is a n exception to this.  If the this thread serviceid is WAVE_SERVICE_INTER_LOCATION_MESSAGE_TRANSPORT, then
    // the thread will receive messages destined for other services since the thread has to transport to remote locations.

    if (((InterLocationMessageTransportObjectManager::getWaveServiceId ()) != m_waveServiceId) &&
         ((HaPeerMessageTransportObjectManager::getWaveServiceId ()) != m_waveServiceId) &&
         (m_waveServiceId != (pWaveMessage->getServiceCode ())))
    {
        cerr << "WaveThread::submitMessageAtBack : Internal Error : Submitted message to a wrong Prism Thread." << endl;
        prismAssert (false, __FILE__, __LINE__);
        return (WAVE_MESSAGE_ERROR_SUBMIT_TO_INVALID_THREAD);
    }

    // Before proceeding check if the Service has been enabled to accept messages other services.
    // We accept a few messages even before the service is enabled.  We accept messages like initialize
    // and enable messages.

    UI32                operationCode       = pWaveMessage->getOperationCode ();
    WaveObjectManager *pWaveObjectManager = getWaveObjectManagerForOperationCode (operationCode);

    // by the time we reach here we must not encounter a NULL WaveObjectManager.

    if (NULL == pWaveObjectManager)
    {
        trace (TRACE_LEVEL_FATAL, string ("WaveThread::submitMessageAtBack : There is no ObjectManager registered to rceive this operation code (") + operationCode + ").");
        prismAssert (false, __FILE__, __LINE__);
        return (WAVE_MESSAGE_ERROR_NO_OM_TO_ACCEPT_MESSAGE);
    }
    else
    {
        if (false == (pWaveObjectManager->getIsEnabled ()))
        {
            if (true == (pWaveObjectManager->isOperationAllowedBeforeEnabling (operationCode)))
            {
                // We cannot use trace method here.  It will lead to an infinite recursion because the trace service
                // might not have been enabled.  Also the trace statement causes invoking subMitMessage.

                // trace (TRACE_LEVEL_DEBUG, string ("WaveThread::submitMessage : Allowing the operation (") + operationCode + ") before enabling the service.");
            }
            else
            {
                trace (TRACE_LEVEL_DEBUG, "WaveThread::submitMessageAtBack : The Service (" + FrameworkToolKit::getServiceNameById (pWaveObjectManager->getServiceId ()) + ") is not enabled yet.  Try later.");
                return (WAVE_MESSAGE_ERROR_SERVICE_NOT_ENABLED);
            }
        }
    }

    WaveMessageStatus status = WAVE_MESSAGE_SUCCESS;

    m_gateKeeper.lock ();

    m_wakeupCaller.lock ();

    // We treat timer expirations differently.  Timer expirations will be handled when they expire.
    // Even if the messages, high priority messages and events are held for the service, still we deliver the
    // timer expiration notifications.  To achieve this we have a separate queue dedicated for for Timer Expiration notifications
    // messages.  Whenever the Timer service sends such a notification message that messages goes into a separate queue.  Otherwise
    // all the messages go into repective queues according to their priority and type.

    UI32 opertionCode = pWaveMessage->getOperationCode ();

    if (WAVE_OBJECT_MANAGER_RESUME == operationCode)
    {
        m_frameworkResumeMessages.insertAtTheBack (pWaveMessage);
    }
    else if (WAVE_OBJECT_MANAGER_PAUSE == operationCode)
    {
        m_frameworkMessages.insertAtTheBack (pWaveMessage);
    }
    else if (WAVE_OBJECT_MANAGER_TIMER_EXPIRED == opertionCode) // For Timer Expiration Messages
    {
        m_timerExpirations.insertAtTheBack (pWaveMessage); // for all the other Framework messages like initialize, enable etc.,
    }
    else if (opertionCode >= (UINT_MAX - 1001))
    {
        m_frameworkMessages.insertAtTheBack (pWaveMessage);
    }
    else
    {
        if (WAVE_MESSAGE_PRIORITY_HIGH == messagePriority)
        {
            m_highPriorityMessages.insertAtTheBack (pWaveMessage);
        }
        else if (WAVE_MESSAGE_PRIORITY_NORMAL == messagePriority)
        {
            m_messages.insertAtTheBack (pWaveMessage);
        }
        else
        {
            cout << "WaveThread::submitMessageAtBack : Submitting message with unknown priority (" << messagePriority << ")." << endl;
            prismAssert (false, __FILE__, __LINE__);
            status = WAVE_MESSAGE_ERROR_UNKNOWN_PRIORITY;
        }
    }

    m_wakeupCondition.resume ();

    m_wakeupCaller.unlock ();

    m_gateKeeper.unlock ();

    return (status);
}

WaveMessageStatus WaveThread::recallMessage (WaveMessage *pWaveMessage)
{
    // We need not lock in this method since the message queues have built in locking mechanism.

    WaveMessageStatus   status          = WAVE_MESSAGE_SUCCESS;
    WaveMessagePriority messagePriority = pWaveMessage->getPriority ();

    if (WAVE_MESSAGE_PRIORITY_HIGH == messagePriority)
    {
        status = m_highPriorityMessageResponses.remove (pWaveMessage);
    }
    else if (WAVE_MESSAGE_PRIORITY_NORMAL == messagePriority)
    {
        status = m_messages.remove (pWaveMessage);
    }
    else
    {
        cout << "WaveThread::recallMessage : Submitting a reply message with unknown priority (" << messagePriority << ")." << endl;
        prismAssert (false, __FILE__, __LINE__);
        status = WAVE_MESSAGE_ERROR_RESPONSE_UNKNOWN_PRIORITY;
    }

    return (status);
}

UI32 WaveThread::recallTimerExpirationMessagesForTimer (const TimerHandle &timerHandle)
{
    // We need not lock in this method since the message queues have built in locking mechanism.

    return (m_timerExpirations.removeTimerExpirationsForTimer (timerHandle));
}

WaveMessageStatus WaveThread::submitReplyMessage (WaveMessage *pWaveMessage)
{
    prismAssert (NULL != pWaveMessage, __FILE__, __LINE__);

    WaveMessagePriority messagePriority = pWaveMessage->getPriority ();

    // FIXME : Sagar make sure that the thread is up and ready for receiving messages

    WaveServiceId senderServiceId = pWaveMessage->getSenderServiceCode ();

    // In general a thread accepts responses only for the messages that it sent out.

    if (m_waveServiceId != senderServiceId)
    {
        cerr << "WaveThread::submitReplyMessage : Submitting reply message to a wrong Prism Thread." << endl;
        prismAssert (false, __FILE__, __LINE__);
        return (WAVE_MESSAGE_ERROR_SUBMIT_RESPONSE_TO_INVALID_THREAD);
    }

    WaveMessageStatus status = WAVE_MESSAGE_SUCCESS;

    m_gateKeeper.lock ();

    m_wakeupCaller.lock ();

    UI32 opertionCode = pWaveMessage->getOperationCode ();

    if (WAVE_OBJECT_MANAGER_TIMER_EXPIRED == opertionCode) // For Timer Expiration Message Responses
    {
        m_timerExpirationResponses.insertAtTheBack (pWaveMessage); // for Responses to all the other Framework messages like initialize, enable etc.,
    }
    else if (opertionCode >= (UINT_MAX - 1001))
    {
        m_frameworkMessageResponses.insertAtTheBack (pWaveMessage);
    }
    else
    {
        if (WAVE_MESSAGE_PRIORITY_HIGH == messagePriority)
        {
            m_highPriorityMessageResponses.insertAtTheBack (pWaveMessage);
        }
        else if (WAVE_MESSAGE_PRIORITY_NORMAL == messagePriority)
        {
            m_messageResponses.insertAtTheBack (pWaveMessage);
        }
        else
        {
            cout << "WaveThread::submitReplyMessage : Submitting a reply message with unknown priority (" << messagePriority << ")." << endl;
            prismAssert (false, __FILE__, __LINE__);
            status = WAVE_MESSAGE_ERROR_RESPONSE_UNKNOWN_PRIORITY;
        }
    }

    m_wakeupCondition.resume ();

    m_wakeupCaller.unlock ();

    m_gateKeeper.unlock ();

    return (status);
}

WaveMessageStatus WaveThread::submitEvent (WaveEvent *pWaveEvent)
{
    prismAssert (NULL != pWaveEvent, __FILE__, __LINE__);

#if 0
    // Check if the message has been submitted to a wrong thread.  This done by comparing this thread serviceid
    // to the message serviceid.
    // there is a n exception to this.  If the this thread serviceid is WAVE_SERVICE_INTER_LOCATION_MESSAGE_TRANSPORT, then
    // the thread will receive messages destined for other services since the thread has to transport to remote locations.

    // Events are defined by the Sender (broadcasting) Service where as messages are defined by the recipient service.  So, we need to
    // compare the event receiver service id to the current thread service id.

    if (((InterLocationMessageTransportObjectManager::getWaveServiceId ()) != m_waveServiceId) && (m_waveServiceId != (pWaveEvent->getReceiverServiceId ())))
    {
        cerr << "WaveThread::submitEvent : Internal Error : Submitted message to a wrong Prism Thread." << endl;
        prismAssert (false, __FILE__, __LINE__);
        return (WAVE_EVENT_ERROR_SUBMIT_TO_INVALID_THREAD);
    }
#endif

    // Before proceeding check if the Service has been enabled to accept messages other services.
    // We accept a few messages even before the service is enabled.  We accept messages like initialize
    // and enable messages.

    WaveServiceId      eventSourceServiceId  = pWaveEvent->getServiceCode ();
    UI32                eventOperationCode    = pWaveEvent->getOperationCode ();
    LocationId          eventSourceLocationId = pWaveEvent->getSenderLocationId ();
    WaveObjectManager *pWaveObjectManager   = getWaveObjectManagerForEventOperationCodeForListening (eventSourceLocationId, eventSourceServiceId, eventOperationCode);

    // by the time we reach here we must not encounter a NULL WaveObjectManager.

    if (NULL == pWaveObjectManager)
    {
        trace (TRACE_LEVEL_FATAL, string ("WaveThread::submitEvent : There is no ObjectManager registered to rceive this event operation code (") + eventOperationCode + ").");
        prismAssert (false, __FILE__, __LINE__);
        return (WAVE_EVENT_ERROR_NO_OM_TO_ACCEPT_MESSAGE);
    }
    else
    {
        if (false == (pWaveObjectManager->getIsEnabled ()))
        {
            if (true == (WaveObjectManager::isEventAllowedBeforeEnabling (eventOperationCode)))
            {
                // We cannot use trace method here.  It will lead to an infinite recursion because the trace service
                // might not have been enabled.  Also the trace statement causes invoking subMitMessage.

                // trace (TRACE_LEVEL_DEBUG, string ("WaveThread::submitMessage : Allowing the operation (") + eventOperationCode + ") before enabling the service.");
            }
            else
            {
                trace (TRACE_LEVEL_DEBUG, "WaveThread::submitEvent : The Service (" + FrameworkToolKit::getServiceNameById (pWaveObjectManager->getServiceId ()) + ") is not enabled yet.  Try later.");
                return (WAVE_MESSAGE_ERROR_SERVICE_NOT_ENABLED);
            }
        }
    }

    WaveMessageStatus status = WAVE_MESSAGE_SUCCESS;

    m_gateKeeper.lock ();

    m_wakeupCaller.lock ();

    WaveMessage *pWaveMessage = dynamic_cast<WaveMessage *> (pWaveEvent);

    m_events.insertAtTheBack (pWaveMessage);

    m_wakeupCondition.resume ();

    m_wakeupCaller.unlock ();

    m_gateKeeper.unlock ();

    return (status);
}

WaveMessage *WaveThread::getNextMessageToProcess ()
{
    if (false == (m_frameworkResumeMessages.isEmpty ()))
    {
        // This queue shall not be affected by the holdall call and hence we do not need to empty any mutex locking though these are messages (not responses).
        // Replies for these messages will be submitted as normal framework messages and hence there is no corresponding reponses queue.

        return (m_frameworkResumeMessages.removeAndGetFromFront ());
    }

    if (false == (m_frameworkMessageResponses.isEmpty ()))
    {
        return (m_frameworkMessageResponses.removeAndGetFromFront ());
    }

    if (false == (m_frameworkMessages.isEmpty ()))
    {
        if (WAVE_MUTEX_SUCCESS == (m_frameworkMessagesMutex.tryLock ()))
        {
            WaveMessage *pWaveMessage = m_frameworkMessages.removeAndGetFromFront ();

            m_frameworkMessagesMutex.unlock ();

            return (pWaveMessage);
        }
    }

    if (false == (m_timerExpirationResponses.isEmpty ()))
    {
        return (m_timerExpirationResponses.removeAndGetFromFront ());
    }

    if (false == (m_timerExpirations.isEmpty ()))
    {
        return (m_timerExpirations.removeAndGetFromFront ());
    }

    if (false == (m_highPriorityMessageResponses.isEmpty ()))
    {
        return (m_highPriorityMessageResponses.removeAndGetFromFront ());
    }

    if (false == (m_highPriorityMessages.isEmpty ()))
    {
        if (WAVE_MUTEX_SUCCESS == (m_highPriorityMessagesMutex.tryLock ()))
        {
            WaveMessage *pWaveMessage = m_highPriorityMessages.removeAndGetFromFront ();

            m_highPriorityMessagesMutex.unlock ();

            return (pWaveMessage);
        }
    }

    if (false == (m_messageResponses.isEmpty ()))
    {
        return (m_messageResponses.removeAndGetFromFront ());
    }

    if (false == (m_events.isEmpty ()))
    {
        if (WAVE_MUTEX_SUCCESS == (m_eventsMutex.tryLock ()))
        {
            WaveMessage *pWaveMessage = m_events.removeAndGetFromFront ();

            m_eventsMutex.unlock ();

            return (pWaveMessage);
        }
    }

    if (false == (m_messages.isEmpty ()))
    {
        if (WAVE_MUTEX_SUCCESS == (m_messagesMutex.tryLock ()))
        {
            WaveMessage *pWaveMessage = m_messages.removeAndGetFromFront ();

            m_messagesMutex.unlock ();

            return (pWaveMessage);
        }
    }

    return (NULL);
}

WaveThread *WaveThread::getWaveThreadForServiceId (WaveServiceId id)
{
    return (s_pWaveServiceMap->getWaveThreadForServiceId (id));
}

vector<UI32> WaveThread::getCpuAffinityVectorForServiceId (WaveServiceId id)
{
    WaveThread  *pWaveThread       = getWaveThreadForServiceId (id);
    vector<UI32>  cpuAffinityVector;

    if (NULL != pWaveThread)
    {
        cpuAffinityVector = pWaveThread->getCpuAffinityVector ();
    }

    return (cpuAffinityVector);
}

string WaveThread::getPrismServiceNameForServiceId (const WaveServiceId &id)
{
    return (s_pWaveServiceMap->getPrismServiceNameForServiceId (id));
}

WaveServiceId WaveThread::getWaveServiceIdForServiceName (const string &serviceName)
{
    return (s_pWaveServiceMap->getWaveServiceIdForServiceName (serviceName));
}

void WaveThread::addWaveObjectManager (WaveObjectManager *pWaveObjectManager)
{
    m_pWaveObjectManagers.push_back (pWaveObjectManager);
}

WaveObjectManager *WaveThread::getWaveObjectManagerForOperationCode (UI32 operationCode)
{
    vector<WaveObjectManager *>::iterator  element             = m_pWaveObjectManagers.begin ();
    vector<WaveObjectManager *>::iterator  limitingElement     = m_pWaveObjectManagers.end (); // last element + 1
    WaveObjectManager                     *pWaveObjectManager = NULL;

    while (element < limitingElement)
    {
        pWaveObjectManager = *element;

        if (pWaveObjectManager->isOperationCodeSupported (operationCode))
        {
            return (pWaveObjectManager);
        }

        element++;
    }

    return (NULL);
}

WaveObjectManager *WaveThread::getWaveObjectManagerForEventOperationCode (UI32 eventOperationCode)
{
    vector<WaveObjectManager *>::iterator  element             = m_pWaveObjectManagers.begin ();
    vector<WaveObjectManager *>::iterator  limitingElement     = m_pWaveObjectManagers.end (); // last element + 1
    WaveObjectManager                     *pWaveObjectManager = NULL;

    while (element < limitingElement)
    {
        pWaveObjectManager = *element;

        if (pWaveObjectManager->isEventOperationCodeSupported (eventOperationCode))
        {
            return (pWaveObjectManager);
        }

        element++;
    }

    return (NULL);
}

WaveObjectManager *WaveThread::getWaveObjectManagerForEventOperationCodeForListening (const LocationId &eventSourceLocationId, const WaveServiceId &eventSourceServiceId, const UI32 &eventOperationCode)
{
    vector<WaveObjectManager *>::iterator  element             = m_pWaveObjectManagers.begin ();
    vector<WaveObjectManager *>::iterator  limitingElement     = m_pWaveObjectManagers.end (); // last element + 1
    WaveObjectManager                     *pWaveObjectManager = NULL;

    while (element < limitingElement)
    {
        pWaveObjectManager = *element;

        if (pWaveObjectManager->isEventOperationCodeSupportedForListening (eventSourceLocationId, eventSourceServiceId, eventOperationCode))
        {
            return (pWaveObjectManager);
        }

        element++;
    }

    return (NULL);
}

WaveObjectManager *WaveThread::getWaveObjectManagerForWaveMessageId  (UI32 prismMessageId)
{
    vector<WaveObjectManager *>::iterator  element            = m_pWaveObjectManagers.begin ();
    vector<WaveObjectManager *>::iterator  limitingElement    = m_pWaveObjectManagers.end (); // last element + 1
    WaveObjectManager                     *pWaveObjectManager  = NULL;

    while (element < limitingElement)
    {
        pWaveObjectManager = *element;

        if (pWaveObjectManager->isAKnownMessage (prismMessageId))
        {
            return (pWaveObjectManager);
        }

        element++;
    }

    return (NULL);
}

WaveObjectManager *WaveThread::getWaveObjectManagerForManagedClass (const string &managedClass)
{
    vector<WaveObjectManager *>::iterator  element             = m_pWaveObjectManagers.begin ();
    vector<WaveObjectManager *>::iterator  limitingElement     = m_pWaveObjectManagers.end (); // last element + 1
    WaveObjectManager                     *pWaveObjectManager = NULL;

    while (element < limitingElement)
    {
        pWaveObjectManager = *element;

        if (pWaveObjectManager->isManagedClassSupported (managedClass))
        {
            return (pWaveObjectManager);
        }

        element++;
    }

    return (NULL);
}

WaveServiceId WaveThread::getWaveServiceId () const
{
    return (m_waveServiceId);
}

bool WaveThread::hasWaveObjectManagers ()
{
    if (0 < m_pWaveObjectManagers.size ())
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

WaveThreadStatus WaveThread::joinAllThreads ()
{
    return (s_pWaveServiceMap->joinAllThreads ());
}

void WaveThread::initializeHoldCounts ()
{
    m_messagesHoldCount             = 0;
    m_highPriorityMessagesHoldCount = 0;
    m_eventsHoldCount               = 0;
    m_frameworkMessagesHoldCount    = 0;
}

void WaveThread::holdMessages ()
{
    if (0 == m_messagesHoldCount)
    {
        m_messagesMutex.lock ();
    }

    m_messagesHoldCount++;
}

void WaveThread::holdHighPriorityMessages ()
{
    if (0 == m_highPriorityMessagesHoldCount)
    {
        m_highPriorityMessagesMutex.lock ();
    }

    m_highPriorityMessagesHoldCount++;
}

void WaveThread::holdEvents ()
{
    if (0 == m_eventsHoldCount)
    {
        m_eventsMutex.lock ();
    }

    m_eventsHoldCount++;
}

void WaveThread::holdFrameworkMessages ()
{
    if (0 == m_frameworkMessagesHoldCount)
    {
        m_frameworkMessagesMutex.lock ();
    }

    m_frameworkMessagesHoldCount++;
}

void WaveThread::holdAll ()
{
    holdMessages ();
    holdHighPriorityMessages ();
    holdEvents ();
    holdFrameworkMessages ();
}

void WaveThread::unholdMessages ()
{
    if (0 == m_messagesHoldCount)
    {
        trace (TRACE_LEVEL_FATAL, "WaveThread::unholdMessages: trying to unhold without hold.");
        prismAssert (false, __FILE__, __LINE__);
    }

    m_messagesHoldCount--;

    if (0 == m_messagesHoldCount)
    {
        m_messagesMutex.unlock ();
    }
}

void WaveThread::unholdHighPriorityMessages ()
{
    if (0 == m_highPriorityMessagesHoldCount)
    {
        trace (TRACE_LEVEL_FATAL, "WaveThread::unholdHighPriorityMessages: trying to unhold without hold.");
        prismAssert (false, __FILE__, __LINE__);
    }
    m_highPriorityMessagesHoldCount--;

    if (0 == m_highPriorityMessagesHoldCount)
    {
        m_highPriorityMessagesMutex.unlock ();
    }
}

void WaveThread::unholdEvents ()
{
    if (0 == m_eventsHoldCount)
    {
        trace (TRACE_LEVEL_FATAL, "WaveThread::unholdEvents: trying to unhold without hold.");
        prismAssert (false, __FILE__, __LINE__);
    }
    m_eventsHoldCount--;

    if (0 == m_eventsHoldCount)
    {
        m_eventsMutex.unlock ();
    }
}

void WaveThread::unholdFrameworkMessages ()
{
    if (0 == m_frameworkMessagesHoldCount)
    {
        trace (TRACE_LEVEL_FATAL, "WaveThread::unholdFrameworkMessages: trying to unhold without hold.");
        prismAssert (false, __FILE__, __LINE__);
    }
    m_frameworkMessagesHoldCount--;

    if (0 == m_frameworkMessagesHoldCount)
    {
        m_frameworkMessagesMutex.unlock ();
    }
}

void WaveThread::unholdAll ()
{
    unholdMessages ();
    unholdHighPriorityMessages ();
    unholdEvents ();
    unholdFrameworkMessages ();
}

WaveThread *WaveThread::getWaveThreadForMessageRemoteTransport ()
{
    //return (getWaveThreadForServiceId (InterLocationMessageTransportObjectManager::getWaveServiceId ()));
    return (InterLocationMessageTransportObjectManager::getWaveThread ());
}

WaveThread *WaveThread::getWaveThreadForMessageHaPeerTransport ()
{
    return (HaPeerMessageTransportObjectManager::getWaveThread ());
}

UI32 WaveThread::getNumberOfPendingTimerExpirationMessages ()
{
    // The message queues are internally protected by locks.  We need not lock them explicitly here.

    return (m_timerExpirations.getSize ());
}

UI32 WaveThread::getNumberOfPendingNormalMessages ()
{
    // The message queues are internally protected by locks.  We need not lock them explicitly here.

    return (m_messages.getSize ());
}

UI32 WaveThread::getNumberOfPendingHighPriorityMessages ()
{
    // The message queues are internally protected by locks.  We need not lock them explicitly here.

    return (m_highPriorityMessages.getSize ());
}

void WaveThread::getListOfServiceIds (vector<WaveServiceId> &serviceIds)
{
    if (NULL != s_pWaveServiceMap)
    {
        s_pWaveServiceMap->getListOfServiceIds (serviceIds);
    }
}

void WaveThread::emptyIncomingMessageQueuesForDisable (vector<WaveMessage *> &incomingMessages)
{
    WaveMessage *pWaveMessage = NULL;

    m_gateKeeper.lock ();

    while (NULL != (pWaveMessage = m_timerExpirations.removeAndGetFromFront ()))
    {
        incomingMessages.push_back (pWaveMessage);
    }

    while (NULL != (pWaveMessage = m_highPriorityMessages.removeAndGetFromFront ()))
    {
        incomingMessages.push_back (pWaveMessage);
    }

    while (NULL != (pWaveMessage = m_messages.removeAndGetFromFront ()))
    {
        incomingMessages.push_back (pWaveMessage);
    }

    while (NULL != (pWaveMessage = m_events.removeAndGetFromFront ()))
    {
        incomingMessages.push_back (pWaveMessage);
    }

    m_gateKeeper.unlock ();
}

WaveThreadId WaveThread::getSelf ()
{
    return (pthread_self ());
}

vector<UI32> WaveThread::getCpuAffinityVector () const
{
    return (m_cpuAffinityVector);
}

void WaveThread::setCpuAffinity (const vector<UI32> &cpuAffinityVector)
{
    m_cpuAffinityVector = cpuAffinityVector;

    UI32         numberOfCpusInCpuAffinityVector = m_cpuAffinityVector.size ();
    UI32         i                               = 0;
    UI32         numberOfCpus                    = FrameworkToolKit::getNumberOfCpus ();
    string       cpuAffinityString;
    vector<UI32> effectiveCpuAffinityVector;
    cpu_set_t    cpuSet;
    UI32         numberOfCpusInSet               = sizeof (cpuSet);

    if (0 != numberOfCpusInCpuAffinityVector)
    {
        CPU_ZERO (&cpuSet);

        for (i = 0; i < numberOfCpusInCpuAffinityVector; i++)
        {
            prismAssert (m_cpuAffinityVector[i] < numberOfCpus, __FILE__, __LINE__);

            CPU_SET (m_cpuAffinityVector[i], &cpuSet);

            cpuAffinityString = cpuAffinityString + m_cpuAffinityVector[i] + string (":");
        }

        if (0 < (m_pWaveObjectManagers.size ()))
        {
            trace (TRACE_LEVEL_DEBUG, "WaveThread::setCpuAffinity : Enabling CPU Affinity for Service : " + m_pWaveObjectManagers[0]->getName () + ", Affinity : " + cpuAffinityString);
        }
        else
        {
            trace (TRACE_LEVEL_DEBUG, "WaveThread::setCpuAffinity : Enabling CPU Affinity for this thread.");
        }

        int setAffinityStatus = sched_setaffinity (syscall (SYS_gettid), sizeof (cpuSet), &cpuSet);

        if (0 < (m_pWaveObjectManagers.size ()))
        {
            if (0 == setAffinityStatus)
            {
                trace (TRACE_LEVEL_DEBUG, "SUCCESSFULLY set CPU Affinity for Service : " + m_pWaveObjectManagers[0]->getName ());
            }
            else
            {
                trace (TRACE_LEVEL_ERROR, "Failed to set CPU Affinity for Service : " + m_pWaveObjectManagers[0]->getName ());
            }
        }
        else
        {
            if (0 == setAffinityStatus)
            {
                trace (TRACE_LEVEL_DEBUG, "SUCCESSFULLY set CPU Affinity for this thread.");
            }
            else
            {
                trace (TRACE_LEVEL_ERROR, "Failed to set CPU Affinity for this thread.");
            }
        }
    }

    int getAffinityStatus = sched_getaffinity (syscall (SYS_gettid), sizeof (cpuSet), &cpuSet);

    if (0 < (m_pWaveObjectManagers.size ()))
    {
        if (0 == getAffinityStatus)
        {
            trace (TRACE_LEVEL_DEBUG, "SUCCESSFULLY get CPU Affinity for Service : " + m_pWaveObjectManagers[0]->getName ());

            for (i = 0; i < numberOfCpusInSet; i++)
            {
                if (CPU_ISSET (i, &cpuSet))
                {
                    effectiveCpuAffinityVector.push_back (i);
                }
            }
        }
        else
        {
            trace (TRACE_LEVEL_ERROR, "Failed to get CPU Affinity for Service : " + m_pWaveObjectManagers[0]->getName ());
        }
    }
    else
    {
        if (0 == getAffinityStatus)
        {
            trace (TRACE_LEVEL_DEBUG, "SUCCESSFULLY get CPU Affinity for this thread.");

            for (i = 0; i < numberOfCpusInSet; i++)
            {
                if (CPU_ISSET (i, &cpuSet))
                {
                    effectiveCpuAffinityVector.push_back (i);
                }
            }
        }
        else
        {
            trace (TRACE_LEVEL_ERROR, "Failed to get CPU Affinity for this thread.");
        }
    }

    m_cpuAffinityVector = effectiveCpuAffinityVector;
}

WaveObjectManager *WaveThread::getWaveObjectManagerForCurrentThread ()
{
    WaveObjectManager *pWaveObjectManager = NULL;

    m_prismThreadIdToWaveObjectManagerMapMutex.lock ();

    map<WaveThreadId, WaveObjectManager *>::iterator element    = m_prismThreadIdToWaveObjectManagerMap.find (pthread_self ());
    map<WaveThreadId, WaveObjectManager *>::iterator endElement = m_prismThreadIdToWaveObjectManagerMap.end ();

    if (endElement != element)
    {
        pWaveObjectManager = element->second;
    }
    else
    {
        pWaveObjectManager = ReservedWaveLocalObjectManager::getInstance ();
    }

    m_prismThreadIdToWaveObjectManagerMapMutex.unlock ();

    return (pWaveObjectManager);
}

WaveServiceId WaveThread::getWaveServiceIdForCurrentThread ()
{
    WaveObjectManager *pWaveObjectManager = NULL;
    WaveServiceId     prismServiceId;

    m_prismThreadIdToWaveObjectManagerMapMutex.lock ();

    map<WaveThreadId, WaveObjectManager *>::iterator element    = m_prismThreadIdToWaveObjectManagerMap.find (pthread_self ());
    map<WaveThreadId, WaveObjectManager *>::iterator endElement = m_prismThreadIdToWaveObjectManagerMap.end ();

    if (endElement != element)
    {
        pWaveObjectManager = element->second;
    }
    else
    {
        pWaveObjectManager = ReservedWaveLocalObjectManager::getInstance ();
    }

    prismAssert (NULL != pWaveObjectManager, __FILE__, __LINE__);

    prismServiceId = pWaveObjectManager->getServiceId ();

    m_prismThreadIdToWaveObjectManagerMapMutex.unlock ();

    return (prismServiceId);
}

void WaveThread::requestForThreadTermination ()
{
    m_terminateThread = true;
}

}
