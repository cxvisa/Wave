/***************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave.Framework.MultiThreading;

import static com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutexStatus.WAVE_MUTEX_SUCCESS;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveServiceId;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveCondition;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

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

    private static Map<WaveThreadId, WaveObjectManager> m_waveThreadIdToWaveObjectManagerMap;
    private static WaveMutex                            m_waveThreadIdToWaveObjectManagerMapMutex;

    private boolean                                     m_terminateThread  = false;

    private static final long                           s_defaultStackSize = 256 * 1024;                                                                                                                                                                                                                                                                                                                                 // 256
                                                                                                                                                                                                                                                                                                                                                                                                                         // KB

    public WaveThread (final String name, final WaveServiceId waveServiceId)
    {
        super (null, null, name, s_defaultStackSize);

        construct (waveServiceId);

        initializeHoldCounts ();
    }

    public WaveThread (final String name, final UI32 stackSize, final WaveServiceId waveServiceId)
    {
        super (null, null, name, stackSize.getValue ());

        construct (waveServiceId);

        initializeHoldCounts ();
    }

    public WaveThread (final String name, final UI32 stackSize, final WaveServiceId waveServiceId, final WaveObjectManager waveObjectManager)
    {
        super (null, null, name, stackSize.getValue ());

        construct (waveServiceId);

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

        m_waveThreadIdToWaveObjectManagerMap = new HashMap<WaveThreadId, WaveObjectManager> ();
        m_waveThreadIdToWaveObjectManagerMapMutex = new WaveMutex ();

        m_terminateThread = false;
    }

    @Override
    public void run ()
    {
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

                final WaveObjectManager waveObjectManager = null;

                System.out.printf ("Received a message ... :-)");
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

    private void addWaveObjectManager (final WaveObjectManager waveObjectManager)
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

    void unholdHighPriorityMessages ()
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

    void unholdEvents ()
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

    void unholdFrameworkMessages ()
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

    void unholdAll ()
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
}
