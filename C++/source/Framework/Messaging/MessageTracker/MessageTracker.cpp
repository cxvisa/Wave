/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/MessageTracker/MessageTracker.h"
#include <Framework/MultiThreading/WaveThread.h>
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/ObjectModel/ReservedWaveLocalObjectManager.h"

#include <algorithm>
// #include <typeinfo> // To print ClassName of message.

namespace WaveNs
{

map<WaveThreadId, map<const WaveMessage *, const WaveMessage *> > MessageTracker::m_currentlyAllocatedMessagesByThread;
map<const WaveMessage *,WaveThreadId>                              MessageTracker::m_currentlyAllocatedMessages;
bool                                                                 MessageTracker::m_trackingMessagesWithBt = false;
map<const WaveMessage *, string>                                    MessageTracker::m_currentlyAllocatedMessagesWithBt;
WaveMutex                                                           MessageTracker::m_messageTrackerMutex;

bool MessageTracker::isAKnownMessage (const WaveMessage *pWaveMessage)
{
    waveAssert (NULL != pWaveMessage, __FILE__, __LINE__);

    map<const WaveMessage *, WaveThreadId>::iterator element    = m_currentlyAllocatedMessages.find (pWaveMessage);
    map<const WaveMessage *, WaveThreadId>::iterator endElement = m_currentlyAllocatedMessages.end ();
    bool                                               found      = false;

    if (endElement != element)
    {
        found = true;
    }

    return (found);
}

void MessageTracker::addToMessageTracker(const WaveMessage* pWaveMessage)
{
    waveAssert (NULL != pWaveMessage, __FILE__, __LINE__);

    m_messageTrackerMutex.lock ();

    if (true == (isAKnownMessage (pWaveMessage)))
    {
        trace (TRACE_LEVEL_FATAL, "MessageTracker::addToMessageTracker : Duplicate Tracking of a message detected.");
        waveAssert (false, __FILE__, __LINE__);

        m_messageTrackerMutex.unlock ();

        return;
    }

    if (true == MessageTracker::m_trackingMessagesWithBt)
    {
        if (true == (isAKnownMessageWithBt (pWaveMessage)))
        {
            trace (TRACE_LEVEL_FATAL, "MessageTracker::addToMessageTracker : Duplicate Tracking of a Message with Bt detected.");
            waveAssert (false, __FILE__, __LINE__);

            m_messageTrackerMutex.unlock ();

            return;
        }
    }

    WaveThreadId thisThread = WaveThread::getSelf ();

    m_currentlyAllocatedMessagesByThread[thisThread][pWaveMessage] = pWaveMessage;
    m_currentlyAllocatedMessages[pWaveMessage]                     = thisThread;

    if (true == MessageTracker::m_trackingMessagesWithBt)
    {
        string btstring;
        FrameworkToolKit::obtainBtString (2, 10, btstring);
        m_currentlyAllocatedMessagesWithBt[pWaveMessage]           = btstring;
    }

    m_messageTrackerMutex.unlock ();
}

void MessageTracker::deleteFromMessageTracker(const WaveMessage* pWaveMessage)
{
    waveAssert (NULL != pWaveMessage, __FILE__, __LINE__);

    m_messageTrackerMutex.lock ();

    if (false == (isAKnownMessage (pWaveMessage)))
    {
        // When bt tracker is turned off, we clear "Message pointer" --> "bt string" map too.
        trace (TRACE_LEVEL_FATAL, "MessageTracker::deleteFromMessageTracker :Deleting of an unknown message. Possible DOUBLE DELETION / MEMORY CORRUPTION Detected.");
        waveAssert (false, __FILE__, __LINE__);

        m_messageTrackerMutex.unlock ();

        return;
    }

    if (true == MessageTracker::m_trackingMessagesWithBt)
    {
        if (true == (isAKnownMessageWithBt (pWaveMessage)))
        {
            m_currentlyAllocatedMessagesWithBt.erase(pWaveMessage);
        }
    }

    m_currentlyAllocatedMessagesByThread[m_currentlyAllocatedMessages[pWaveMessage]].erase (pWaveMessage);
    m_currentlyAllocatedMessages.erase (pWaveMessage);

    m_messageTrackerMutex.unlock ();
}

// private, no-lock.
void MessageTracker::getMessagesForAThread (const WaveThreadId &prismThreadId, vector<WaveServiceId> &messageServiceIds, vector<UI32> &messageOperationCodes, vector<WaveMessageType> &messageTypes, vector<string> &btStrings)
{
    map<WaveThreadId, map<const WaveMessage *, const WaveMessage *> >::const_iterator itr1 = m_currentlyAllocatedMessagesByThread.find (prismThreadId);
    map<WaveThreadId, map<const WaveMessage *, const WaveMessage *> >::const_iterator end1 = m_currentlyAllocatedMessagesByThread.end ();

    if (end1 == itr1)
    {
        return;
    }

    const map<const WaveMessage *, const WaveMessage *> &messageMap = itr1->second;

    map<const WaveMessage *, const WaveMessage *>::const_iterator itr2 = messageMap.begin ();
    map<const WaveMessage *, const WaveMessage *>::const_iterator end2 = messageMap.end ();

    for (; end2 != itr2; itr2++)
    {
        const WaveMessage *pWaveMessage = itr2->second;
        waveAssert (NULL != pWaveMessage, __FILE__, __LINE__);

        messageServiceIds.push_back     (pWaveMessage->getServiceCode ());
        messageOperationCodes.push_back (pWaveMessage->getOperationCode ());
        messageTypes.push_back          (pWaveMessage->getType ());

        string btstring; // = string (typeid (*pWaveMessage).name ()) + "\r\n"; // To print ClassName of message.

        if (true == MessageTracker::m_trackingMessagesWithBt)
        {
            if (isAKnownMessageWithBt (pWaveMessage))
            {
                btstring += m_currentlyAllocatedMessagesWithBt[pWaveMessage];
            }
        }

        btStrings.push_back (btstring);
    }
}

void MessageTracker::getMessages (const WaveServiceId &prismServiceId, vector<WaveServiceId> &messageServiceIds, vector<UI32> &messageOperationCodes, vector<WaveMessageType> &messageTypes, vector<string> &btStrings)
{
    m_messageTrackerMutex.lock ();

    WaveThread *pWaveThread = WaveThread::getWaveThreadForServiceId (prismServiceId);

    if (NULL == pWaveThread)
    {
        tracePrintf (TRACE_LEVEL_ERROR, true, false, "MessageTracker::getMessages : Could not find a Prism Thread that corresponds to Prism Service ID : %u", prismServiceId);

        m_messageTrackerMutex.unlock ();
        return;
    }

    WaveThreadId prismThreadId = pWaveThread->getId ();

    getMessagesForAThread (prismThreadId, messageServiceIds, messageOperationCodes, messageTypes, btStrings);

    WaveServiceId serviceIdForReservedWaveLocalObjectManager = ReservedWaveLocalObjectManager::getWaveServiceId ();

    if (prismServiceId == serviceIdForReservedWaveLocalObjectManager)
    {
        // 1. Get set of all thread ids tracked.

        set<WaveThreadId> setOfAllWaveThreadIds;

        map<WaveThreadId, map<const WaveMessage *, const WaveMessage *> >::const_iterator itr1 = m_currentlyAllocatedMessagesByThread.begin ();
        map<WaveThreadId, map<const WaveMessage *, const WaveMessage *> >::const_iterator end1 = m_currentlyAllocatedMessagesByThread.end ();

        for (; end1 != itr1; itr1++)
        {
            setOfAllWaveThreadIds.insert (itr1->first);
        }


        // 2. Get set of thread ids corresponding to all services.

        set<WaveThreadId> setOfWaveThreadIdsForAllServices;

        vector<WaveServiceId> allWaveServiceIds;

        WaveThread::getListOfServiceIds (allWaveServiceIds);

        vector<WaveServiceId>::const_iterator itr2 = allWaveServiceIds.begin ();
        vector<WaveServiceId>::const_iterator end2 = allWaveServiceIds.end ();

        for (; end2 != itr2; itr2++)
        {
            WaveServiceId prismServiceIdForAService = *itr2;

            WaveThread *pWaveThreadForAService = WaveThread::getWaveThreadForServiceId (prismServiceIdForAService);

            if (NULL != pWaveThreadForAService)
            {
                setOfWaveThreadIdsForAllServices.insert (pWaveThreadForAService->getId ());
            }
        }


        // 3. Prepare a vector of service ids corresponding to thread ids, each of which is 'not related to any service.'
        //    i.e. collect all the thread ids which are in '1.', but not in '2.'

        vector<WaveThreadId> vectorOfNonServiceWaveThreads (setOfAllWaveThreadIds.size ());

        vector<WaveThreadId>::iterator endOfDifference = std::set_difference (setOfAllWaveThreadIds.begin (), setOfAllWaveThreadIds.end (), setOfWaveThreadIdsForAllServices.begin (), setOfWaveThreadIdsForAllServices.end (), vectorOfNonServiceWaveThreads.begin ());

        vectorOfNonServiceWaveThreads.resize (endOfDifference - vectorOfNonServiceWaveThreads.begin ());


        // 4. Get Message tracker information for thread ids obtained in '3.' above.

        vector<WaveThreadId>::const_iterator itr3 = vectorOfNonServiceWaveThreads.begin ();
        vector<WaveThreadId>::const_iterator end3 = vectorOfNonServiceWaveThreads.end ();

        for (; end3 != itr3; itr3++)
        {
            getMessagesForAThread ((*itr3), messageServiceIds, messageOperationCodes, messageTypes, btStrings);
        }
    }

#if 0
    WaveThreadId                                                                  prismThreadId    = (WaveThread::getWaveThreadForServiceId (prismServiceId))->getId ();
    map<WaveThreadId, map<const WaveMessage *, const WaveMessage *> >::iterator threadElement    = m_currentlyAllocatedMessagesByThread.find (prismThreadId);
    map<WaveThreadId, map<const WaveMessage *, const WaveMessage *> >::iterator threadEndElement = m_currentlyAllocatedMessagesByThread.end  ();

    string btstring = "";
    if (threadEndElement != threadElement)
    {
        map<const WaveMessage *, const WaveMessage *>::iterator messageElement    = m_currentlyAllocatedMessagesByThread[prismThreadId].begin ();
        map<const WaveMessage *, const WaveMessage *>::iterator messageEndElement = m_currentlyAllocatedMessagesByThread[prismThreadId].end   ();

        while (messageEndElement != messageElement)
        {
            const WaveMessage *pWaveMessage = messageElement->second;

            waveAssert (NULL != pWaveMessage, __FILE__, __LINE__);

            messageServiceIds.push_back (pWaveMessage->getServiceCode ());
            messageOperationCodes.push_back (pWaveMessage->getOperationCode ());
            messageTypes.push_back (pWaveMessage->getType ());

            if (true == MessageTracker::m_trackingMessagesWithBt)
            {
                if (isAKnownMessageWithBt (pWaveMessage))
                {
                    btstring = m_currentlyAllocatedMessagesWithBt[pWaveMessage];
                }
                else
                {
                    btstring = "";
                }
            }
            else
            {
                btstring = "";
            }
            btStrings.push_back (btstring);

            messageElement++;
        }
    }
#endif

    m_messageTrackerMutex.unlock ();
}

bool MessageTracker::isAKnownMessageWithBt (const WaveMessage *pWaveMessage)
{
    waveAssert (NULL != pWaveMessage, __FILE__, __LINE__);

    map<const WaveMessage *, string>::iterator element    = m_currentlyAllocatedMessagesWithBt.find (pWaveMessage);
    map<const WaveMessage *, string>::iterator endElement = m_currentlyAllocatedMessagesWithBt.end ();
    bool                                        found      = false;

    if (endElement != element)
    {
        found = true;
    }

    return (found);
}

void MessageTracker::changeBtTrackerState (const bool &btTrackerState)
{
    m_messageTrackerMutex.lock ();

    if (true == btTrackerState)
    {
        MessageTracker::m_trackingMessagesWithBt = true;
        trace (TRACE_LEVEL_INFO, "MessageTracker::changeBtTrackerState : Tracking with Bt is enabled.");
    }
    else
    {
        MessageTracker::m_trackingMessagesWithBt = false;
        MessageTracker::clearCurrentlyAllocatedMessagesWithBt ();
        trace (TRACE_LEVEL_INFO, "MessageTracker::changeBtTrackerState : Disabled tracking with Bt and cleared history.");
    }

    m_messageTrackerMutex.unlock ();
}

void MessageTracker::clearCurrentlyAllocatedMessagesWithBt ()
{
    m_currentlyAllocatedMessagesWithBt.erase (m_currentlyAllocatedMessagesWithBt.begin (), m_currentlyAllocatedMessagesWithBt.end ());
}

}
