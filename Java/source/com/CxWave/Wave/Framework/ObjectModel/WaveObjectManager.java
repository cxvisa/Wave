/***************************************************************************
 *   Copyright (C) 2015-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import java.math.BigInteger;
import java.util.Map;
import java.util.Vector;

import com.CxWave.Wave.Framework.Messaging.Local.WaveEvent;
import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.MultiThreading.WaveThread;
import com.CxWave.Wave.Framework.Trace.TraceObjectManager;
import com.CxWave.Wave.Framework.Type.LocationId;
import com.CxWave.Wave.Framework.Type.TimerHandle;
import com.CxWave.Wave.Framework.Type.TraceClientId;
import com.CxWave.Wave.Framework.Type.WaveGenericContext;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;
import com.CxWave.Wave.Resources.ResourceEnums.FrameworkStatus;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class WaveObjectManager extends WaveElement
{
    private class PrismOperationMapContext
    {
        private WaveElement        m_waveElementThatHandlesTheMessage;
        private WaveMessageHandler m_waveMessageHandler;

        public PrismOperationMapContext   (WaveElement waveElement, WaveMessageHandler waveMessageHandler)
        {
            m_waveElementThatHandlesTheMessage = waveElement;
            m_waveMessageHandler               = waveMessageHandler;
        }

        public void executeMessageHandler (WaveMessage waveMessage)
        {
            m_waveMessageHandler.execute (waveMessage, m_waveElementThatHandlesTheMessage);
        }
    };

    private class WaveEventMapContext
    {

        private WaveElement      m_waveElementThatHandlesTheEvent;
        private WaveEventHandler m_waveEventHandler;

        public WaveEventMapContext (WaveElement waveElement, WaveEventHandler waveEventHandler)
        {
            m_waveElementThatHandlesTheEvent = waveElement;
            m_waveEventHandler               = waveEventHandler;
        }

        public void executeEventHandler  (final WaveEvent waveEvent)
        {
            m_waveEventHandler.execute (waveEvent, m_waveElementThatHandlesTheEvent);
        }
    };

    private class WaveMessageResponseContext
    {
        private WaveMessage                m_waveMessage;
        private WaveElement                m_waveMessageSender;
        private WaveMessageResponseHandler m_waveMessageSenderCallback;
        private WaveGenericContext         m_waveMessageSenderContext;
        private boolean                    m_isMessageTimedOut;
        private WaveMessage                m_inputMessageInResponseContext;
        private boolean                    m_isTimerStarted;
        private TimerHandle                m_timerHandle;

        public WaveMessageResponseContext (WaveMessage waveMessage, WaveElement waveMessageSender, WaveMessageResponseHandler waveMessageSenderCallback, WaveGenericContext waveMessageSenderContext)
        {
        }

        public void executeResponseCallback (FrameworkStatus frameworkStatus, WaveMessage waveMessage, boolean isMessageRecalled)
        {
        }

        public void executeResponseCallback (FrameworkStatus frameworkStatus)
        {

        }

        public void setIsMessageTimedOut (boolean isMessageTimedOut)
        {
            m_isMessageTimedOut = isMessageTimedOut;
        }

        public boolean getIsMessageTimedOut ()
        {
            return (m_isMessageTimedOut);
        }

        public WaveMessage getWaveMessage ()
        {
            return (m_waveMessage);
        }

        public WaveMessage getInputMessageInResponseContext ()
        {
            return (m_inputMessageInResponseContext);
        }

        public void setInputMessageInResponseContext (WaveMessage waveMessage)
        {
            m_inputMessageInResponseContext = waveMessage;
        }

        public boolean getIsTimerStarted ()
        {
            return (m_isTimerStarted);
        }

        public void setIsTimerStarted (final boolean isTimerStarted)
        {
            m_isTimerStarted = isTimerStarted;
        }

        public TimerHandle getTimerHandle ()
        {
            return (m_timerHandle);
        }

        public void setTimerHandle (final TimerHandle timerHandle)
        {
            m_timerHandle = timerHandle;
        }
    };

    private class WaveEventListenerMapContext
    {
        private WaveServiceId m_eventListenerSericeId;
        private LocationId    m_eventListenerLocationId;

        public WaveEventListenerMapContext (final WaveServiceId eventListenerServiceId, final LocationId eventListenerLocationId)
        {
            m_eventListenerSericeId   = eventListenerServiceId;
            m_eventListenerLocationId = eventListenerLocationId;
        }

        public WaveServiceId getEventListenerServiceId ()
        {
            return (m_eventListenerSericeId);
        }

        public LocationId getEventListenerLocationId ()
        {
            return (m_eventListenerLocationId);
        }
    };

    private static WaveMutex s_waveObjectManagerMutex = new WaveMutex ();
    private static WaveServiceId s_nextAvailableWaveServiceId = new WaveServiceId (0);

    private String                                                                 m_name;
    private WaveThread                                                             m_associatedWaveThread;
    private Map<BigInteger, PrismOperationMapContext>                              m_operationsMap;
    private Map<BigInteger, BigInteger>                                            m_supportedEvents;
    private Map<LocationId, Map<BigInteger, Map<BigInteger, WaveEventMapContext>>> m_eventsMap;
    private Map<BigInteger, WaveMessageResponseContext>                            m_responsesMap;
    private Map<BigInteger, Vector<WaveEventListenerMapContext>>                   m_eventListenersMap;
    private Map<String, Vector<String> >                                           m_postbootManagedObjectNames;
    private WaveMutex                                                              m_responsesMapMutex;
    private WaveMutex                                                              m_sendReplyMutexForResponseMap;
    private Vector<WaveWorker>                                                     m_workers;
    private boolean                                                                m_isEnabled;
    private WaveMutex                                                              m_isEnabledMutex;
    private TraceClientId                                                          m_traceClientId;

    private WaveServiceId                                                          m_serviceId;

    protected WaveObjectManager (final String waveObjectManagerName)
    {
        m_name = new String (waveObjectManagerName);

        m_traceClientId = TraceObjectManager.addClient (TraceLevel.TRACE_LEVEL_INFO, m_name);

        s_waveObjectManagerMutex.lock ();
        s_nextAvailableWaveServiceId.increment ();
        m_serviceId = new WaveServiceId (s_nextAvailableWaveServiceId);
        s_waveObjectManagerMutex.unlock ();
    }

    public WaveServiceId getServiceId ()
    {
        return (m_serviceId);
    }

    protected boolean isALocalWaveService ()
    {
        return (false);
    }
}
