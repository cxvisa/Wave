/***************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import java.math.BigInteger;
import java.util.Map;
import java.util.Vector;

import com.CxWave.Wave.Framework.Core.WaveFrameworkObjectManager;
import com.CxWave.Wave.Framework.Messaging.Local.WaveEvent;
import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.MultiThreading.WaveThread;
import com.CxWave.Wave.Framework.Trace.TraceObjectManager;
import com.CxWave.Wave.Framework.Type.LocationId;
import com.CxWave.Wave.Framework.Type.TimerHandle;
import com.CxWave.Wave.Framework.Type.TraceClientId;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Type.WaveGenericContext;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.FrameworkStatus;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;
import com.CxWave.Wave.Resources.ResourceEnums.WaveServiceMode;

public class WaveObjectManager extends WaveElement
{
    private class PrismOperationMapContext
    {
        private final WaveElement        m_waveElementThatHandlesTheMessage;
        private final WaveMessageHandler m_waveMessageHandler;

        public PrismOperationMapContext (final WaveElement waveElement, final WaveMessageHandler waveMessageHandler)
        {
            m_waveElementThatHandlesTheMessage = waveElement;
            m_waveMessageHandler = waveMessageHandler;
        }

        public void executeMessageHandler (final WaveMessage waveMessage)
        {
            m_waveMessageHandler.execute (waveMessage, m_waveElementThatHandlesTheMessage);
        }
    };

    private class WaveEventMapContext
    {

        private final WaveElement      m_waveElementThatHandlesTheEvent;
        private final WaveEventHandler m_waveEventHandler;

        public WaveEventMapContext (final WaveElement waveElement, final WaveEventHandler waveEventHandler)
        {
            m_waveElementThatHandlesTheEvent = waveElement;
            m_waveEventHandler = waveEventHandler;
        }

        public void executeEventHandler (final WaveEvent waveEvent)
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

        public WaveMessageResponseContext (final WaveMessage waveMessage, final WaveElement waveMessageSender, final WaveMessageResponseHandler waveMessageSenderCallback, final WaveGenericContext waveMessageSenderContext)
        {
        }

        public void executeResponseCallback (final FrameworkStatus frameworkStatus, final WaveMessage waveMessage, final boolean isMessageRecalled)
        {
        }

        public void executeResponseCallback (final FrameworkStatus frameworkStatus)
        {

        }

        public void setIsMessageTimedOut (final boolean isMessageTimedOut)
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

        public void setInputMessageInResponseContext (final WaveMessage waveMessage)
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
        private final WaveServiceId m_eventListenerSericeId;
        private final LocationId    m_eventListenerLocationId;

        public WaveEventListenerMapContext (final WaveServiceId eventListenerServiceId, final LocationId eventListenerLocationId)
        {
            m_eventListenerSericeId = eventListenerServiceId;
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

    private static WaveMutex                                                       s_waveObjectManagerMutex     = new WaveMutex ();
    private static WaveServiceId                                                   s_nextAvailableWaveServiceId = new WaveServiceId (0);
    private static WaveServiceMode                                                 s_waveServiceLaunchMode      = WaveServiceMode.WAVE_SERVICE_ACTIVE;

    private final String                                                           m_name;
    private WaveThread                                                             m_associatedWaveThread;
    private Map<BigInteger, PrismOperationMapContext>                              m_operationsMap;
    private Map<BigInteger, BigInteger>                                            m_supportedEvents;
    private Map<LocationId, Map<BigInteger, Map<BigInteger, WaveEventMapContext>>> m_eventsMap;
    private Map<BigInteger, WaveMessageResponseContext>                            m_responsesMap;
    private Map<BigInteger, Vector<WaveEventListenerMapContext>>                   m_eventListenersMap;
    private Map<String, Vector<String>>                                            m_postbootManagedObjectNames;
    private WaveMutex                                                              m_responsesMapMutex;
    private WaveMutex                                                              m_sendReplyMutexForResponseMap;
    private Vector<WaveWorker>                                                     m_workers;
    private boolean                                                                m_isEnabled                  = false;
    private final WaveMutex                                                        m_isEnabledMutex             = new WaveMutex ();
    private final TraceClientId                                                    m_traceClientId;
    private final WaveServiceMode                                                  m_waveServiceMode;

    private final WaveServiceId                                                    m_serviceId;

    protected WaveObjectManager (final String waveObjectManagerName, final UI32 stackSize)
    {
        m_name = new String (waveObjectManagerName);

        m_waveServiceMode = s_waveServiceLaunchMode;

        if (!(canInstantiateServiceAtThisTime (waveObjectManagerName)))
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "WaveObjectManager.WaveObjectManager : Please make sure that the WaveFrameworkObjectManager is the first Object Manager that gets instantated.");
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "                                      Trying to instantiate Service : %s", waveObjectManagerName);
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "CANOT CONTINUE.  EXITING ...");
            WaveAssertUtils.waveAssert ();
        }

        m_traceClientId = TraceObjectManager.addClient (TraceLevel.TRACE_LEVEL_INFO, m_name);

        s_waveObjectManagerMutex.lock ();
        s_nextAvailableWaveServiceId.increment ();
        m_serviceId = new WaveServiceId (s_nextAvailableWaveServiceId);
        s_waveObjectManagerMutex.unlock ();

        final WaveThread associatedWaveThread = new WaveThread (m_name, stackSize, m_serviceId);

        m_associatedWaveThread = associatedWaveThread;

        m_associatedWaveThread.start ();
    }

    protected WaveObjectManager (final String waveObjectManagerName)
    {
        m_name = new String (waveObjectManagerName);

        m_waveServiceMode = s_waveServiceLaunchMode;

        if (!(canInstantiateServiceAtThisTime (waveObjectManagerName)))
        {
            System.err.printf ("WaveObjectManager.WaveObjectManager : Please make sure that the WaveFrameworkObjectManager is the first Object Manager that gets instantated.\n");
            System.err.printf ("                                      Trying to instantiate Service : %s\n", waveObjectManagerName);
            System.err.printf ("CANOT CONTINUE.  EXITING ...\n");

            WaveAssertUtils.waveAssert ();
        }

        m_traceClientId = TraceObjectManager.addClient (TraceLevel.TRACE_LEVEL_INFO, m_name);

        s_waveObjectManagerMutex.lock ();
        s_nextAvailableWaveServiceId.increment ();
        m_serviceId = new WaveServiceId (s_nextAvailableWaveServiceId);
        s_waveObjectManagerMutex.unlock ();

        final WaveThread associatedWaveThread = new WaveThread (m_name, WaveThread.getDefaultStackSize (), m_serviceId);

        m_associatedWaveThread = associatedWaveThread;

        m_associatedWaveThread.start ();

    }

    public WaveServiceId getServiceId ()
    {
        return (m_serviceId);
    }

    protected boolean isALocalWaveService ()
    {
        return (false);
    }

    @Override
    protected void trace (final TraceLevel requestedTraceLevel, final String stringToTrace, final boolean addNewLine, final boolean suppressPrefix)
    {
        TraceObjectManager.traceDirectly (m_traceClientId, requestedTraceLevel, stringToTrace, addNewLine, suppressPrefix);
    }

    @Override
    protected void trace (final TraceLevel requestedTraceLevel, final String stringToTrace)
    {
        trace (requestedTraceLevel, stringToTrace, true, false);
    }

    @Override
    protected void tracePrintf (final TraceLevel requestedTraceLevel, final boolean addNewLine, final boolean suppressPrefix, final String formatString, final Object... objects)
    {
        TraceObjectManager.tracePrintf (m_traceClientId, requestedTraceLevel, addNewLine, suppressPrefix, formatString, objects);
    }

    @Override
    protected void tracePrintf (final TraceLevel requestedTraceLevel, final String formatString, final Object... objects)
    {
        tracePrintf (requestedTraceLevel, true, false, formatString, objects);
    }

    protected boolean canInstantiateServiceAtThisTime (final String waveServiceName)
    {
        // This method ensures that no other service gets instantiated before the Framework Service itself gets instantiated.

        if ("Wave Framework".equals (waveServiceName))
        {
            return (true);
        }
        else
        {
            if (true == (WaveFrameworkObjectManager.getIsInstantiated ()))
            {
                return (true);
            }
            else
            {
                return (false);
            }
        }
    }

    protected void waveAssert ()
    {
        WaveAssertUtils.waveAssert ();
    }

    protected void waveAssert (final boolean isAssertNotRequired)
    {
        WaveAssertUtils.waveAssert (isAssertNotRequired);
    }

    private void setAssociatedWaveThread (final WaveThread associatedWaveThread)
    {
        if (null == associatedWaveThread)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "WaveObjectManager.setAssociatedWaveThread : Cannot associate with a null thread.");
            WaveAssertUtils.waveAssert ();
        }
        else
        {
            if (null == m_associatedWaveThread)
            {
                m_associatedWaveThread = associatedWaveThread;
            }
            else
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "WaveObjectManager.setAssociatedWaveThread : This Object Manager has already been associated with another Wave Thread.");
                WaveAssertUtils.waveAssert ();
            }
        }
    }

    public boolean getIsEnabled ()
    {
        boolean isEnabled = false;

        m_isEnabledMutex.lock ();

        isEnabled = m_isEnabled;

        m_isEnabledMutex.unlock ();

        return (isEnabled);
    }

    public void setIsEnabled (final boolean isEnabled)
    {
        m_isEnabledMutex.lock ();

        m_isEnabled = isEnabled;
        m_isEnabledMutex.unlock ();
    }
}
