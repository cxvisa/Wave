/***************************************************************************
 *   Copyright (C) 2015-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.Wave.Framework.MultiThreading;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveCondition;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;

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

    private boolean                                     m_terminateThread;

    private static final long                           s_defaultStackSize                          = 256 * 1024; // 256 KB

    public WaveThread (final String name)
    {
        super (null, null, name, s_defaultStackSize);

        construct (0);
    }

    public WaveThread (final String name, final long stackSize)
    {
        super (null, null, name, stackSize);

        construct (0);
    }

    private void construct (final long waveServiceId)
    {
        m_waveServiceId = new WaveServiceId (waveServiceId);

        m_messages                                  = new WaveMessageQueue<WaveMessage> ();
        m_messageResponses                          = new WaveMessageQueue<WaveMessage> ();
        m_highPriorityMessages                      = new WaveMessageQueue<WaveMessage> ();
        m_highPriorityMessageResponses              = new WaveMessageQueue<WaveMessage> ();
        m_events                                    = new WaveMessageQueue<WaveMessage> ();
        m_timerExpirations                          = new WaveMessageQueue<WaveMessage> ();
        m_timerExpirationResponses                  = new WaveMessageQueue<WaveMessage> ();
        m_frameworkMessages                         = new WaveMessageQueue<WaveMessage> ();
        m_frameworkMessageResponses                 = new WaveMessageQueue<WaveMessage> ();
        m_frameworkResumeMessages                   = new WaveMessageQueue<WaveMessage> ();

        m_gateKeeper                                = new WaveMutex ();
        m_wakeupCaller                              = new WaveMutex ();
        m_wakeupCondition                           = new WaveCondition (m_wakeupCaller);

        m_messagesMutex                             = new WaveMutex ();
        m_messagesHoldCount                         = 0;
        m_highPriorityMessagesMutex                 = new WaveMutex ();
        m_highPriorityMessagesHoldCount             = 0;
        m_eventsMutex                               = new WaveMutex ();
        m_eventsHoldCount                           = 0;
        m_frameworkMessagesMutex                    = new WaveMutex ();
        m_frameworkMessagesHoldCount                = 0;
        m_frameworkResumeMessagesMutex              = new WaveMutex ();
        m_frameworkResumeMessagesHoldCount          = 0;

        m_waveObjectManagers                        = new ArrayList<WaveObjectManager> ();

        m_waveThreadIdToWaveObjectManagerMap        = new HashMap<WaveThreadId, WaveObjectManager> ();
        m_waveThreadIdToWaveObjectManagerMapMutex   = new WaveMutex ();

        m_terminateThread                           = false;
    }

    public void run ()
    {

    }
}
