/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.MultiThreading;

import static com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutexStatus.WAVE_MUTEX_SUCCESS;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.CxWave.Wave.Framework.Core.WaveServiceMap;
import com.CxWave.Wave.Framework.Messaging.HaPeer.HaPeerMessageTransportObjectManager;
import com.CxWave.Wave.Framework.Messaging.Local.WaveEvent;
import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.Messaging.Remote.InterLocationMessageTransportObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.FrameworkOpCodes;
import com.CxWave.Wave.Framework.ObjectModel.ReservedWaveLocalObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonMessageHandler;
import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
import com.CxWave.Wave.Framework.Type.LocationId;
import com.CxWave.Wave.Framework.Type.TimerHandle;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Source.SourceUtils;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveCondition;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.FrameworkStatus;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;
import com.CxWave.Wave.Resources.ResourceEnums.WaveMessagePriority;
import com.CxWave.Wave.Resources.ResourceEnums.WaveMessageStatus;

public class WaveThread extends Thread
{
    private WaveServiceId                               m_waveServiceId;

    private WaveMessageQueue<WaveMessage>               m_messages;
    private WaveMessageQueue<WaveMessage>               m_messageResponses;
    private WaveMessageQueue<WaveMessage>               m_highPriorityMessages;
    private WaveMessageQueue<WaveMessage>               m_highPriorityMessageResponses;
    private WaveMessageQueue<WaveMessage>               m_events;
    private WaveMessageQueue<WaveMessage>               m_timerExpirations;
    private WaveMessageQueue<WaveMessage>               m_timerExpirationResponses;
    private WaveMessageQueue<WaveMessage>               m_frameworkMessages;
    private WaveMessageQueue<WaveMessage>               m_frameworkMessageResponses;
    private WaveMessageQueue<WaveMessage>               m_frameworkResumeMessages;

    private WaveMutex                                   m_gateKeeper;
    private WaveMutex                                   m_wakeupCaller;
    private WaveCondition                               m_wakeupCondition;

    private WaveMutex                                   m_messagesMutex;
    private long                                        m_messagesHoldCount;
    private WaveMutex                                   m_highPriorityMessagesMutex;
    private long                                        m_highPriorityMessagesHoldCount;
    private WaveMutex                                   m_eventsMutex;
    private long                                        m_eventsHoldCount;
    private WaveMutex                                   m_frameworkMessagesMutex;
    private long                                        m_frameworkMessagesHoldCount;
    private WaveMutex                                   m_frameworkResumeMessagesMutex;
    private long                                        m_frameworkResumeMessagesHoldCount;

    private List<WaveObjectManager>                     m_waveObjectManagers;

    private static Map<WaveThreadId, WaveObjectManager> s_waveThreadIdToWaveObjectManagerMap      = new HashMap<WaveThreadId, WaveObjectManager> ();
    private static WaveMutex                            s_waveThreadIdToWaveObjectManagerMapMutex = new WaveMutex ();

    private boolean                                     m_terminateThread                         = false;

    private static final long                           s_defaultStackSize                        = 256 * 1024;

    private static WaveServiceMap                       s_waveServiceMap                          = new WaveServiceMap ();

    private WaveThreadId                                m_waveThreadId                            = null;

    private final WaveMutex                             m_isReadyForMessageSubmissionsLock        = new WaveMutex ();
    private boolean                                     m_isReadyForMessageSubmissions            = false;

    private static final WaveMutex                      s_preareObjectManagersForActionMutex      = new WaveMutex ();

    public WaveThread (final String name, final WaveServiceId waveServiceId)
    {
        super (null, null, name, s_defaultStackSize);

        construct (waveServiceId);

        s_waveServiceMap.addServiceMap (m_waveServiceId, this, name);

        initializeHoldCounts ();
    }

    public WaveThread (final String name, final UI32 stackSize, final WaveServiceId waveServiceId)
    {
        super (null, null, name, stackSize.getValue ());

        construct (waveServiceId);

        s_waveServiceMap.addServiceMap (m_waveServiceId, this, name);

        initializeHoldCounts ();
    }

    public WaveThread (final String name, final UI32 stackSize, final WaveServiceId waveServiceId, final WaveObjectManager waveObjectManager)
    {
        super (null, null, name, stackSize.getValue ());

        construct (waveServiceId);

        s_waveServiceMap.addServiceMap (m_waveServiceId, this, name);

        addWaveObjectManager (waveObjectManager);

        initializeHoldCounts ();
    }

    private void construct (final WaveServiceId waveServiceId)
    {
        m_waveServiceId = new WaveServiceId (waveServiceId);

        m_messages = new WaveMessageQueue<WaveMessage> ();
        m_messageResponses = new WaveMessageQueue<WaveMessage> ();
        m_highPriorityMessages = new WaveMessageQueue<WaveMessage> ();
        m_highPriorityMessageResponses = new WaveMessageQueue<WaveMessage> ();
        m_events = new WaveMessageQueue<WaveMessage> ();
        m_timerExpirations = new WaveMessageQueue<WaveMessage> ();
        m_timerExpirationResponses = new WaveMessageQueue<WaveMessage> ();
        m_frameworkMessages = new WaveMessageQueue<WaveMessage> ();
        m_frameworkMessageResponses = new WaveMessageQueue<WaveMessage> ();
        m_frameworkResumeMessages = new WaveMessageQueue<WaveMessage> ();

        m_gateKeeper = new WaveMutex ();
        m_wakeupCaller = new WaveMutex ();
        m_wakeupCondition = new WaveCondition (m_wakeupCaller);

        m_messagesMutex = new WaveMutex ();
        m_messagesHoldCount = 0;
        m_highPriorityMessagesMutex = new WaveMutex ();
        m_highPriorityMessagesHoldCount = 0;
        m_eventsMutex = new WaveMutex ();
        m_eventsHoldCount = 0;
        m_frameworkMessagesMutex = new WaveMutex ();
        m_frameworkMessagesHoldCount = 0;
        m_frameworkResumeMessagesMutex = new WaveMutex ();
        m_frameworkResumeMessagesHoldCount = 0;

        m_waveObjectManagers = new ArrayList<WaveObjectManager> ();

        m_terminateThread = false;

        m_waveThreadId = new WaveThreadId (getId ());
    }

    @Override
    public void run ()
    {
        m_isReadyForMessageSubmissionsLock.lock ();

        final UI32 numberOfWaveObjectManagers = new UI32 (m_waveObjectManagers.size ());
        final WaveThreadId thisThreadId = WaveThreadId.getSelf ();

        WaveAssertUtils.waveAssert (numberOfWaveObjectManagers.equals (new UI32 (1))); // For now, enforce that there is exactly
                                                                                       // on Wave OM per thread.

        while (true)
        {
            if (true == (SourceUtils.getIsInitialized ()))
            {
                break;
            }

            try
            {
                Thread.sleep (10);
            }
            catch (final InterruptedException e)
            {
                WaveAssertUtils.waveAssert ();
            }
        }

        for (final WaveObjectManager waveObjectManager : m_waveObjectManagers)
        {
            WaveAssertUtils.waveAssert (null != waveObjectManager);

            s_preareObjectManagersForActionMutex.lock ();
            waveObjectManager.prepareObjectManagerForAction ();
            s_preareObjectManagersForActionMutex.unlock ();
        }

        m_isReadyForMessageSubmissions = true;

        m_isReadyForMessageSubmissionsLock.unlock ();

        while (true)
        {
            if (true == (FrameworkToolKit.isFrameworkReadyToBoot ()))
            {
                break;
            }

            try
            {
                Thread.sleep (10);
            }
            catch (final InterruptedException e)
            {
                WaveAssertUtils.waveAssert ();
            }
        }

        s_waveThreadIdToWaveObjectManagerMapMutex.lock ();

        s_waveThreadIdToWaveObjectManagerMap.put (WaveThreadId.getWaveThreadIdForThisThread (), m_waveObjectManagers.get (0));

        s_waveThreadIdToWaveObjectManagerMapMutex.unlock ();

        WaveMessage waveMessage = null;

        while (true)
        {
            if (true == m_terminateThread)
            {
                break;
            }

            m_gateKeeper.lock ();

            waveMessage = getNextMessageToProcess ();

            if (null == waveMessage)
            {
                m_wakeupCaller.lock ();
                m_gateKeeper.unlock ();
                m_wakeupCondition.awaitUninterruptibly ();
                m_wakeupCaller.unlock ();
            }
            else
            {
                m_gateKeeper.unlock ();

                // final WaveObjectManager waveObjectManager = null;

                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "Received a message ... :-)");

                final WaveObjectManager waveObjectManager = null;

                switch (waveMessage.getType ())
                {
                    case WAVE_MESSAGE_TYPE_REQUEST:
                        final WaveObjectManager waveObjectManagerToHandleRequest = getWaveObjectManagerForOperationCode (waveMessage.getOperationCode ());

                        if (null != waveObjectManagerToHandleRequest)
                        {
                            waveObjectManagerToHandleRequest.handleWaveMessage (waveMessage);
                        }
                        else
                        {
                            waveMessage.setCompletionStatus (ResourceId.WAVE_THREAD_ERROR_COULD_NOT_FIND_OM);

                            if (0 < m_waveObjectManagers.size ())
                            {
                                (m_waveObjectManagers.get (0)).reply (waveMessage);
                            }
                            else
                            {
                                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "This Service does not have any object managers to handle any requests.");
                                WaveAssertUtils.waveAssert ();
                            }
                        }

                        break;

                    case WAVE_MESSAGE_TYPE_RESPONSE:

                        final WaveObjectManager waveObjectManagerToHandleResponse = getWaveObjectManagerForWaveMessageId (waveMessage.getMessageId ());

                        if (null != waveObjectManagerToHandleResponse)
                        {
                            waveObjectManagerToHandleResponse.handleWaveMessageResponse (FrameworkStatus.FRAMEWORK_SUCCESS, waveMessage);
                        }
                        else
                        {
                            WaveTraceUtils.fatalTracePrintf ("Failed to deliver response : Could not find corresponding Wave Object Manager.");
                            WaveTraceUtils.fatalTracePrintf ("ServiceCode = %s, OperationCode = %s, MessageId = %s", (waveMessage.getServiceCode ()).toString (), (waveMessage.getOperationCode ()).toString (), (waveMessage.getMessageId ()).toString ());

                            WaveAssertUtils.waveAssert ();
                        }

                        break;

                    case WAVE_MESSAGE_TYPE_EVENT:
                        break;

                    default:
                        WaveAssertUtils.waveAssert ();
                        break;
                }
            }
        }
    }

    WaveMessage getNextMessageToProcess ()
    {
        if (false == (m_frameworkResumeMessages.isEmpty ()))
        {
            // This queue shall not be affected by the holdall call and hence we do not need to empty any mutex locking though
            // these are messages (not responses).
            // Replies for these messages will be submitted as normal framework messages and hence there is no corresponding
            // responses queue.

            return (m_frameworkResumeMessages.removeAndGetFromFront ());
        }

        if (false == (m_frameworkMessageResponses.isEmpty ()))
        {
            return (m_frameworkMessageResponses.removeAndGetFromFront ());
        }

        if (false == (m_frameworkMessages.isEmpty ()))
        {
            if (WAVE_MUTEX_SUCCESS == (m_frameworkMessagesMutex.tryLockWithStatus ()))
            {
                final WaveMessage waveMessage = m_frameworkMessages.removeAndGetFromFront ();

                m_frameworkMessagesMutex.unlock ();

                return (waveMessage);
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
            if (WAVE_MUTEX_SUCCESS == (m_highPriorityMessagesMutex.tryLockWithStatus ()))
            {
                final WaveMessage waveMessage = m_highPriorityMessages.removeAndGetFromFront ();

                m_highPriorityMessagesMutex.unlock ();

                return (waveMessage);
            }
        }

        if (false == (m_messageResponses.isEmpty ()))
        {
            return (m_messageResponses.removeAndGetFromFront ());
        }

        if (false == (m_events.isEmpty ()))
        {
            if (WAVE_MUTEX_SUCCESS == (m_eventsMutex.tryLockWithStatus ()))
            {
                final WaveMessage waveMessage = m_events.removeAndGetFromFront ();

                m_eventsMutex.unlock ();

                return (waveMessage);
            }
        }

        if (false == (m_messages.isEmpty ()))
        {
            if (WAVE_MUTEX_SUCCESS == (m_messagesMutex.tryLockWithStatus ()))
            {
                final WaveMessage waveMessage = m_messages.removeAndGetFromFront ();

                m_messagesMutex.unlock ();

                return (waveMessage);
            }
        }

        return (null);
    }

    public void addWaveObjectManager (final WaveObjectManager waveObjectManager)
    {
        m_waveObjectManagers.add (waveObjectManager);
    }

    private void initializeHoldCounts ()
    {
        m_messagesHoldCount = 0;
        m_highPriorityMessagesHoldCount = 0;
        m_eventsHoldCount = 0;
        m_frameworkMessagesHoldCount = 0;
    }

    public void holdMessages ()
    {
        if (0 == m_messagesHoldCount)
        {
            m_messagesMutex.lock ();
        }

        m_messagesHoldCount++;
    }

    public void holdHighPriorityMessages ()
    {
        if (0 == m_highPriorityMessagesHoldCount)
        {
            m_highPriorityMessagesMutex.lock ();
        }

        m_highPriorityMessagesHoldCount++;
    }

    public void holdEvents ()
    {
        if (0 == m_eventsHoldCount)
        {
            m_eventsMutex.lock ();
        }

        m_eventsHoldCount++;
    }

    public void holdFrameworkMessages ()
    {
        if (0 == m_frameworkMessagesHoldCount)
        {
            m_frameworkMessagesMutex.lock ();
        }

        m_frameworkMessagesHoldCount++;
    }

    public void holdAll ()
    {
        holdMessages ();
        holdHighPriorityMessages ();
        holdEvents ();
        holdFrameworkMessages ();
    }

    public void unholdMessages ()
    {
        if (0 == m_messagesHoldCount)
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_FATAL, "unholdMessages: trying to unhold without hold.");
            WaveAssertUtils.waveAssert ();
        }

        m_messagesHoldCount--;

        if (0 == m_messagesHoldCount)
        {
            m_messagesMutex.unlock ();
        }
    }

    public void unholdHighPriorityMessages ()
    {
        if (0 == m_highPriorityMessagesHoldCount)
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_FATAL, "unholdHighPriorityMessages: trying to unhold without hold.");
            WaveAssertUtils.waveAssert ();
        }
        m_highPriorityMessagesHoldCount--;

        if (0 == m_highPriorityMessagesHoldCount)
        {
            m_highPriorityMessagesMutex.unlock ();
        }
    }

    public void unholdEvents ()
    {
        if (0 == m_eventsHoldCount)
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_FATAL, "unholdEvents: trying to unhold without hold.");
            WaveAssertUtils.waveAssert ();
        }
        m_eventsHoldCount--;

        if (0 == m_eventsHoldCount)
        {
            m_eventsMutex.unlock ();
        }
    }

    public void unholdFrameworkMessages ()
    {
        if (0 == m_frameworkMessagesHoldCount)
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_FATAL, "unholdFrameworkMessages: trying to unhold without hold.");
            WaveAssertUtils.waveAssert ();
        }
        m_frameworkMessagesHoldCount--;

        if (0 == m_frameworkMessagesHoldCount)
        {
            m_frameworkMessagesMutex.unlock ();
        }
    }

    public void unholdAll ()
    {
        unholdMessages ();
        unholdHighPriorityMessages ();
        unholdEvents ();
        unholdFrameworkMessages ();
    }

    public static UI32 getDefaultStackSize ()
    {
        return (new UI32 (s_defaultStackSize));
    }

    public WaveObjectManager getWaveObjectManagerForOperationCode (final UI32 operationCode)
    {
        for (final WaveObjectManager waveObjectManager : m_waveObjectManagers)
        {
            WaveAssertUtils.waveAssert (null != waveObjectManager);

            if (waveObjectManager.isOperationCodeSupported (operationCode))
            {
                return (waveObjectManager);
            }
        }

        return (null);
    }

    public static String getWaveServiceNameForServiceId (final WaveServiceId id)
    {
        return (s_waveServiceMap.getWaveServiceNameForServiceId (id));
    }

    public WaveMessageStatus submitMessage (final WaveMessage waveMessage)
    {
        while (true)
        {
            if (getIsReadyForMessageSubmissions ())
            {
                break;
            }

            try
            {
                Thread.sleep (10);
            }
            catch (final InterruptedException e)
            {
                WaveAssertUtils.waveAssert ();
            }
        }

        WaveAssertUtils.waveAssert (null != waveMessage);

        final WaveMessagePriority messagePriority = waveMessage.getPriority ();

        // Check if the message has been submitted to a wrong thread. This done by comparing this thread serviceid
        // to the message serviceid.
        // there is a n exception to this. If the this thread serviceid is WAVE_SERVICE_INTER_LOCATION_MESSAGE_TRANSPORT, then
        // the thread will receive messages destined for other services since the thread has to transport to remote locations.

        if ((!((InterLocationMessageTransportObjectManager.getWaveServiceId ()).equals (m_waveServiceId))) && ((!(HaPeerMessageTransportObjectManager.getWaveServiceId ()).equals (m_waveServiceId))) && (!(m_waveServiceId.equals ((waveMessage.getServiceCode ())))))
        {
            System.err.println ("WaveThread.submitMessage : Internal Error : Submitted message to a wrong Wave Thread.");
            WaveAssertUtils.waveAssert (false);
            return (WaveMessageStatus.WAVE_MESSAGE_ERROR_SUBMIT_TO_INVALID_THREAD);
        }

        // Before proceeding check if the Service has been enabled to accept messages other services.
        // We accept a few messages even before the service is enabled. We accept messages like initialize
        // and enable messages.

        final UI32 operationCode = waveMessage.getOperationCode ();
        final WaveObjectManager waveObjectManager = getWaveObjectManagerForOperationCode (operationCode);

        // by the time we reach here we must not encounter a null WaveObjectManager.

        if (null == waveObjectManager)
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_FATAL, "WaveThread.submitMessage : There is no ObjectManager registered to rceive this operation code (" + operationCode + ").");
            WaveAssertUtils.waveAssert (false);
            return (WaveMessageStatus.WAVE_MESSAGE_ERROR_NO_OM_TO_ACCEPT_MESSAGE);
        }
        else
        {
            if (false == (waveObjectManager.getIsEnabled ()))
            {
                if (true == (waveObjectManager.isOperationAllowedBeforeEnabling (operationCode)))
                {
                    // We cannot use trace method here. It will lead to an infinite recursion because the trace service
                    // might not have been enabled. Also the trace statement causes invoking subMitMessage.

                    // trace (TRACE_LEVEL_DEBUG, string ("WaveThread.submitMessage : Allowing the operation (") + operationCode
                    // + ") before enabling the service.");
                }
                else
                {
                    WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_DEBUG, "WaveThread.submitMessage : The Service (" + (FrameworkToolKit.getServiceNameById (waveObjectManager.getServiceId ())) + ") is not enabled yet.  Try later.");
                    return (WaveMessageStatus.WAVE_MESSAGE_ERROR_SERVICE_NOT_ENABLED);
                }
            }
        }

        WaveMessageStatus status = WaveMessageStatus.WAVE_MESSAGE_SUCCESS;

        m_gateKeeper.lock ();

        m_wakeupCaller.lock ();

        // We treat timer expirations differently. Timer expirations will be handled when they expire.
        // Even if the messages, high priority messages and events are held for the service, still we deliver the
        // timer expiration notifications. To achieve this we have a separate queue dedicated for for Timer Expiration
        // notifications
        // messages. Whenever the Timer service sends such a notification message that messages goes into a separate queue.
        // Otherwise
        // all the messages go into respective queues according to their priority and type.

        if (((FrameworkOpCodes.WAVE_OBJECT_MANAGER_RESUME.getOperationCode ()).equals (operationCode)) || (true == waveMessage.getIsMessageSupportedWhenServiceIsPaused ()))
        {
            m_frameworkResumeMessages.insertAtTheBack (waveMessage);
        }
        else if ((FrameworkOpCodes.WAVE_OBJECT_MANAGER_PAUSE.getOperationCode ()).equals (operationCode))
        {
            m_frameworkMessages.insertAtTheFront (waveMessage);
        }
        else if ((FrameworkOpCodes.WAVE_OBJECT_MANAGER_TIMER_EXPIRED.getOperationCode ()).equals (operationCode)) // For Timer
                                                                                                                  // Expiration
                                                                                                                  // Messages
        {
            m_timerExpirations.insertAtTheBack (waveMessage); // for all the other Framework messages like initialize, enable
                                                              // etc.,
        }
        else if ((operationCode.getValue ()).longValue () >= (UI32.MAXIMUM_LONG_VALUE - FrameworkOpCodes.s_maximumNumberOfOpCodes))
        {
            m_frameworkMessages.insertAtTheBack (waveMessage);

            WaveTraceUtils.infoTracePrintf ("WaveThread.submitMessage : Submitting a Framework Message.");
        }
        else
        {
            if (WaveMessagePriority.WAVE_MESSAGE_PRIORITY_HIGH == messagePriority)
            {
                m_highPriorityMessages.insertAtTheBack (waveMessage);
            }
            else if (WaveMessagePriority.WAVE_MESSAGE_PRIORITY_NORMAL == messagePriority)
            {
                m_messages.insertAtTheBack (waveMessage);
            }
            else
            {
                System.err.println ("WaveThread.submitMessage : Submitting message with unknown priority (" + messagePriority + ").");
                WaveAssertUtils.waveAssert (false);
                status = WaveMessageStatus.WAVE_MESSAGE_ERROR_UNKNOWN_PRIORITY;
            }
        }

        m_wakeupCondition.signal ();

        m_wakeupCaller.unlock ();

        m_gateKeeper.unlock ();

        return (status);
    }

    @NonMessageHandler
    public WaveMessageStatus submitReplyMessage (final WaveMessage waveMessage)
    {
        WaveAssertUtils.waveAssert (null != waveMessage);

        final WaveMessagePriority messagePriority = waveMessage.getPriority ();

        // FIXME : Sagar make sure that the thread is up and ready for receiving messages

        final WaveServiceId senderServiceId = waveMessage.getSenderServiceCode ();

        // In general a thread accepts responses only for the messages that it sent out.

        if (m_waveServiceId != senderServiceId)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveThread.submitReplyMessage : Submitting reply message to a wrong Wave Thread.");
            WaveAssertUtils.waveAssert (false);

            return (WaveMessageStatus.WAVE_MESSAGE_ERROR_SUBMIT_RESPONSE_TO_INVALID_THREAD);
        }

        WaveMessageStatus status = WaveMessageStatus.WAVE_MESSAGE_SUCCESS;

        m_gateKeeper.lock ();

        m_wakeupCaller.lock ();

        final UI32 opertionCode = waveMessage.getOperationCode ();

        if ((FrameworkOpCodes.WAVE_OBJECT_MANAGER_TIMER_EXPIRED).getOperationCode () == opertionCode) // For Timer Expiration
                                                                                                      // Message Responses
        {
            m_timerExpirationResponses.insertAtTheBack (waveMessage); // for Responses to all the other Framework messages like
                                                                      // initialize, enable etc.,
        }
        else if ((opertionCode.getValue ()) >= (UI32.MAXIMUM_LONG_VALUE - FrameworkOpCodes.s_maximumNumberOfOpCodes))
        {
            m_frameworkMessageResponses.insertAtTheBack (waveMessage);
        }
        else
        {
            if (WaveMessagePriority.WAVE_MESSAGE_PRIORITY_HIGH == messagePriority)
            {
                m_highPriorityMessageResponses.insertAtTheBack (waveMessage);
            }
            else if (WaveMessagePriority.WAVE_MESSAGE_PRIORITY_NORMAL == messagePriority)
            {
                m_messageResponses.insertAtTheBack (waveMessage);
            }
            else
            {
                WaveTraceUtils.fatalTracePrintf ("WaveThread.submitReplyMessage : Submitting a reply message with unknown priority %d", messagePriority);
                WaveAssertUtils.waveAssert (false);
                status = WaveMessageStatus.WAVE_MESSAGE_ERROR_RESPONSE_UNKNOWN_PRIORITY;
            }
        }

        m_wakeupCondition.signal ();

        m_wakeupCaller.unlock ();

        m_gateKeeper.unlock ();

        return (status);
    }

    public static WaveObjectManager getWaveObjectManagerForCurrentThread ()
    {
        WaveObjectManager waveObjectManager = null;

        s_waveThreadIdToWaveObjectManagerMapMutex.lock ();

        waveObjectManager = s_waveThreadIdToWaveObjectManagerMap.get (WaveThreadId.getWaveThreadIdForThisThread ());

        s_waveThreadIdToWaveObjectManagerMapMutex.unlock ();

        if (null == waveObjectManager)
        {
            waveObjectManager = ReservedWaveLocalObjectManager.getInstance ();
        }

        return (waveObjectManager);
    }

    public static WaveServiceId getWaveServiceIdForCurrentThread ()
    {
        WaveObjectManager waveObjectManager = null;
        WaveServiceId waveServiceId = null;

        s_waveThreadIdToWaveObjectManagerMapMutex.lock ();

        waveObjectManager = s_waveThreadIdToWaveObjectManagerMap.get (WaveThreadId.getWaveThreadIdForThisThread ());

        s_waveThreadIdToWaveObjectManagerMapMutex.unlock ();

        if (null == waveObjectManager)
        {
            waveObjectManager = ReservedWaveLocalObjectManager.getInstance ();
        }

        waveServiceId = waveObjectManager.getServiceId ();

        return (waveServiceId);
    }

    public static WaveThread getWaveThreadForServiceId (final WaveServiceId waveServiceId)
    {
        return (s_waveServiceMap.getWaveThreadForServiceId (waveServiceId));
    }

    public static WaveThreadId getSelf ()
    {
        return (WaveThreadId.getSelf ());
    }

    public static WaveThread getWaveThreadForMessageHaPeerTransport ()
    {
        return (WaveThread.getWaveThreadForServiceId (HaPeerMessageTransportObjectManager.getWaveServiceId ()));
    }

    public static WaveThread getWaveThreadForMessageRemoteTransport ()
    {
        return (WaveThread.getWaveThreadForServiceId (InterLocationMessageTransportObjectManager.getWaveServiceId ()));
    }

    public boolean hasWaveObjectManagers ()
    {
        if (0 < (m_waveObjectManagers.size ()))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }

    public WaveServiceId getWaveServiceId ()
    {
        return (m_waveServiceId);
    }

    public WaveThreadId getWaveThreadId ()
    {
        return (m_waveThreadId);
    }

    public boolean getIsReadyForMessageSubmissions ()
    {
        m_isReadyForMessageSubmissionsLock.lock ();

        final boolean isReadyForMessageSubmissions = m_isReadyForMessageSubmissions;

        m_isReadyForMessageSubmissionsLock.unlock ();

        return (isReadyForMessageSubmissions);
    }

    public void setIsReadyForMessageSubmissions (final boolean isReadyForMessageSubmissions)
    {
        m_isReadyForMessageSubmissionsLock.lock ();

        m_isReadyForMessageSubmissions = isReadyForMessageSubmissions;

        m_isReadyForMessageSubmissionsLock.unlock ();
    }

    public static WaveServiceId getWaveServiceIdForServiceName (final String serviceName)
    {
        return (s_waveServiceMap.getWaveServiceIdForServiceName (serviceName));
    }

    private WaveObjectManager getWaveObjectManagerForWaveMessageId (final UI32 waveMessageId)
    {
        for (final WaveObjectManager waveObjectManager : m_waveObjectManagers)
        {
            WaveAssertUtils.waveAssert (null != waveObjectManager);

            if (waveObjectManager.isAKnownMessage (waveMessageId))
            {
                return (waveObjectManager);
            }
        }

        return (null);
    }

    public WaveMessageStatus recallMessage (final WaveMessage waveMessage)
    {
        // We need not lock in this method since the message queues have built in locking mechanism.

        WaveMessageStatus status = WaveMessageStatus.WAVE_MESSAGE_SUCCESS;
        final WaveMessagePriority messagePriority = waveMessage.getPriority ();

        if (WaveMessagePriority.WAVE_MESSAGE_PRIORITY_HIGH == messagePriority)
        {
            status = m_highPriorityMessageResponses.remove (waveMessage);
        }
        else if (WaveMessagePriority.WAVE_MESSAGE_PRIORITY_NORMAL == messagePriority)
        {
            status = m_messages.remove (waveMessage);
        }
        else
        {
            WaveTraceUtils.fatalTracePrintf ("WaveThread.recallMessage : Recalling a message with unknown priority (%s)", FrameworkToolKit.localize (messagePriority.getResourceId ()));
            WaveAssertUtils.waveAssert ();
            status = WaveMessageStatus.WAVE_MESSAGE_ERROR_RESPONSE_UNKNOWN_PRIORITY;
        }

        return (status);
    }

    public int recallTimerExpirationMessagesForTimer (final TimerHandle timerHandle)
    {
        // We need not lock in this method since the message queues have built in locking mechanism.

        return (m_timerExpirations.removeTimerExpirationsForTimer (timerHandle));
    }

    public WaveObjectManager getWaveObjectManagerForEventOperationCode (final UI32 eventOpcode)
    {
        for (final WaveObjectManager waveObjectManager : m_waveObjectManagers)
        {
            WaveAssertUtils.waveAssert (null != waveObjectManager);

            if (waveObjectManager.isEventOperationCodeSupported (eventOpcode))
            {
                return (waveObjectManager);
            }
        }

        return (null);
    }

    public WaveMessageStatus submitEvent (final WaveEvent waveEvent)
    {
        WaveAssertUtils.waveAssert (null != waveEvent);

        // Before proceeding check if the Service has been enabled to accept messages other services.
        // We accept a few messages even before the service is enabled. We accept messages like initialize
        // and enable messages.

        final WaveServiceId eventSourceServiceId = waveEvent.getServiceCode ();
        final UI32 eventOperationCode = waveEvent.getOperationCode ();
        final LocationId eventSourceLocationId = waveEvent.getSenderLocationId ();
        final WaveObjectManager waveObjectManager = getWaveObjectManagerForEventOperationCodeForListening (eventSourceLocationId, eventSourceServiceId, eventOperationCode);

        // by the time we reach here we must not encounter a null WaveObjectManager.

        if (null == waveObjectManager)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveThread.submitEvent : There is no ObjectManager registered to rceive this event operation code (%s).", eventOperationCode.toString ());
            WaveAssertUtils.waveAssert ();
            return (WaveMessageStatus.WAVE_EVENT_ERROR_NO_OM_TO_ACCEPT_MESSAGE);
        }
        else
        {
            if (false == (waveObjectManager.getIsEnabled ()))
            {
                if (true == (waveObjectManager.isEventAllowedBeforeEnabling (eventOperationCode)))
                {
                    // We cannot use trace method here. It will lead to an infinite recursion because the trace service
                    // might not have been enabled. Also the trace statement causes invoking subMitMessage.

                    // trace (TRACE_LEVEL_DEBUG, string ("WaveThread.submitMessage : Allowing the operation (") +
                    // eventOperationCode + ") before enabling the service.");
                }
                else
                {
                    WaveTraceUtils.debugTracePrintf ("WaveThread.submitEvent : The Service (%s) is not enabled yet.  Try later.", FrameworkToolKit.getServiceNameById (waveObjectManager.getServiceId ()));
                    return (WaveMessageStatus.WAVE_MESSAGE_ERROR_SERVICE_NOT_ENABLED);
                }
            }
        }

        final WaveMessageStatus status = WaveMessageStatus.WAVE_MESSAGE_SUCCESS;

        m_gateKeeper.lock ();

        m_wakeupCaller.lock ();

        final WaveMessage waveMessage = waveEvent;

        m_events.insertAtTheBack (waveMessage);

        m_wakeupCondition.signal ();

        m_wakeupCaller.unlock ();

        m_gateKeeper.unlock ();

        return (status);
    }

    private WaveObjectManager getWaveObjectManagerForEventOperationCodeForListening (final LocationId eventSourceLocationId, final WaveServiceId eventSourceServiceId, final UI32 eventOperationCode)
    {
        for (final WaveObjectManager waveObjectManager : m_waveObjectManagers)
        {
            WaveAssertUtils.waveAssert (null != waveObjectManager);

            if (waveObjectManager.isEventOperationCodeSupported (eventOperationCode))
            {
                return (waveObjectManager);
            }
        }

        return (null);
    }
}
