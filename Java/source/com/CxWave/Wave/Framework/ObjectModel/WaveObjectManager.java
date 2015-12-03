/***********************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import java.lang.reflect.Method;
import java.math.BigInteger;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.Vector;

import com.CxWave.Wave.Framework.Core.WaveFrameworkObjectManager;
import com.CxWave.Wave.Framework.Messaging.Local.WaveEvent;
import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.MultiThreading.WaveThread;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonMessageHandler;
import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
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
import com.CxWave.Wave.Resources.ResourceEnums.WaveMessageStatus;
import com.CxWave.Wave.Resources.ResourceEnums.WaveServiceMode;

public class WaveObjectManager extends WaveElement
{
    private class WaveOperationMapContext
    {
        private final WaveMessageHandler m_waveMessageHandler;

        public WaveOperationMapContext (final WaveElement waveElement, final Method method)
        {
            m_waveMessageHandler = new WaveMessageHandler (method, waveElement);
        }

        public void executeMessageHandler (final WaveMessage waveMessage)
        {
            m_waveMessageHandler.execute (waveMessage);
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

    private static WaveMutex                                           s_waveObjectManagerMutex          = new WaveMutex ();
    private static WaveServiceId                                       s_nextAvailableWaveServiceId      = new WaveServiceId (0);
    private static WaveServiceMode                                     s_waveServiceLaunchMode           = WaveServiceMode.WAVE_SERVICE_ACTIVE;

    private static final Set<UI32>                                     s_operationsAllowedBeforeEnabling = initializeOperationsAllowedBeforeEnablingSet ();

    private final String                                               m_name;
    private WaveThread                                                 m_associatedWaveThread;
    private final Map<UI32, WaveOperationMapContext>                   m_operationsMap                   = new HashMap<UI32, WaveOperationMapContext> ();
    private final Map<Class<?>, UI32>                                  m_operationsClassToIdMap          = new HashMap<Class<?>, UI32> ();
    private final Map<UI32, Class<?>>                                  m_operationsIdToClassMap          = new HashMap<UI32, Class<?>> ();
    private Map<UI32, BigInteger>                                      m_supportedEvents;
    private Map<LocationId, Map<UI32, Map<UI32, WaveEventMapContext>>> m_eventsMap;
    private Map<UI32, WaveMessageResponseContext>                      m_responsesMap;
    private Map<UI32, Vector<WaveEventListenerMapContext>>             m_eventListenersMap;
    private Map<String, Vector<String>>                                m_postbootManagedObjectNames;
    private WaveMutex                                                  m_responsesMapMutex;
    private WaveMutex                                                  m_sendReplyMutexForResponseMap;
    private Vector<WaveWorker>                                         m_workers;
    private boolean                                                    m_isEnabled                       = false;
    private final WaveMutex                                            m_isEnabledMutex                  = new WaveMutex ();
    private final TraceClientId                                        m_traceClientId;
    private final WaveServiceMode                                      m_waveServiceMode;

    private final WaveServiceId                                        m_serviceId;

    private WaveMessage                                                m_inputMessage;

    private void addSupportedOperations ()
    {
        // addOperationMap (FrameworkOpCodes.WAVE_OBJECT_MANAGER_INITIALIZE, "_non_existing_", this);
    }

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

        addSupportedOperations ();

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

        m_associatedWaveThread.addWaveObjectManager (this);

        addSupportedOperations ();

        m_associatedWaveThread.start ();

    }

    private static Set<UI32> initializeOperationsAllowedBeforeEnablingSet ()
    {
        final Set<UI32> operationsAllowedBeforeEnabling = new HashSet<UI32> ();

        operationsAllowedBeforeEnabling.add (FrameworkOpCodes.WAVE_OBJECT_MANAGER_INITIALIZE.getOperationCode ());
        operationsAllowedBeforeEnabling.add (FrameworkOpCodes.WAVE_OBJECT_MANAGER_ENABLE.getOperationCode ());
        operationsAllowedBeforeEnabling.add (FrameworkOpCodes.WAVE_OBJECT_MANAGER_UNINITIALIZE.getOperationCode ());
        operationsAllowedBeforeEnabling.add (FrameworkOpCodes.WAVE_OBJECT_MANAGER_DESTRUCT.getOperationCode ());
        operationsAllowedBeforeEnabling.add (FrameworkOpCodes.WAVE_OBJECT_MANAGER_DATABASE_SANITY_CHECK.getOperationCode ());

        return (operationsAllowedBeforeEnabling);
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

    private void addOperationMap (final UI32 operationCode, final Method messageHandlerMethod, final WaveElement waveElement)
    {
        WaveAssertUtils.waveAssert (null != operationCode);

        if (m_operationsMap.containsKey (operationCode))
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_FATAL, "WaveObjectManager.addOperationMap : OperationMap already found for this operation code : " + operationCode);

            WaveAssertUtils.waveAssert ();

            return;
        }
        else
        {
            m_operationsMap.put (operationCode, new WaveOperationMapContext (waveElement, messageHandlerMethod));
        }
    }

    private void addOperationMapForMessageClass (final Class<? extends WaveMessage> messageClass, final Method messageHandlerMethod, final WaveElement waveElement)
    {
        final UI32 operationCode = WaveMessage.getOperationCodeForMessageClass (messageClass);

        addOperationMap (operationCode, messageHandlerMethod, waveElement);

        if (m_operationsClassToIdMap.containsKey (messageClass))
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_FATAL, "WaveObjectManager.addOperationMapForMessageClass : OperationMap already found for this Class : " + messageClass.getName ());

            WaveAssertUtils.waveAssert ();
        }
        else
        {
            m_operationsClassToIdMap.put (messageClass, operationCode);
        }

        if (m_operationsIdToClassMap.containsKey (operationCode))
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_FATAL, "WaveObjectManager.addOperationMapForMessageClass : OperationMap already found for this OperationCode : " + operationCode.toString ());

            WaveAssertUtils.waveAssert ();
        }
        else
        {
            m_operationsIdToClassMap.put (operationCode, messageClass);
        }
    }

    public boolean isOperationCodeSupported (final UI32 waveOperationCode)
    {
        return (m_operationsMap.containsKey (waveOperationCode));
    }

    public boolean isOperationAllowedBeforeEnabling (final UI32 operationCode)
    {
        return (s_operationsAllowedBeforeEnabling.contains (operationCode));
    }

    public WaveMessage getInputMessage ()
    {
        return (m_inputMessage);
    }

    @NonMessageHandler
    protected WaveMessageStatus sendOneWay (final WaveMessage waveMessage)
    {
        return (sendOneWay (waveMessage, LocationId.NullLocationId));
    }

    protected WaveMessageStatus sendOneWay (final WaveMessage waveMessage, final LocationId locationId)
    {
        WaveThread waveThread = null;
        final LocationId thisLocationId = FrameworkToolKit.getThisLocationId ();
        LocationId effectiveLocationId = locationId;

        // FIXME : sagar : replace the 0 with NullLocationId

        if (LocationId.isNull (effectiveLocationId))
        {
            if (true != (FrameworkToolKit.isALocalService (waveMessage.getServiceCode ())))
            {
                effectiveLocationId = FrameworkToolKit.getClusterPrimaryLocationId ();
            }
        }

        if ((LocationId.isNull (effectiveLocationId)) || (thisLocationId.equals (effectiveLocationId)))
        {
            waveThread = WaveThread.getWaveThreadForServiceId (waveMessage.getServiceCode ());
        }
        else if (effectiveLocationId.equals (LocationId.HaPeerLocationId))
        {
            waveThread = WaveThread.getWaveThreadForMessageHaPeerTransport ();
        }
        else
        {
            waveThread = WaveThread.getWaveThreadForMessageRemoteTransport ();
        }

        if (null == waveThread)
        {
            // trace (TRACE_LEVEL_ERROR, string ("WaveObjectManager.sendOneWay : No Service registered to accept this service Id
            // ") + waveMessage->getServiceCode () + ".");

            return (WaveMessageStatus.WAVE_MESSAGE_ERROR_NO_SERVICE_TO_ACCEPT_MESSAGE);
        }

        if (false == (waveThread.hasWaveObjectManagers ()))
        {
            // trace (TRACE_LEVEL_ERROR, "WaveObjectManager.sendOneWay : Service identified. But there are no Wave Object
            // Managers registered to process any kind of requests.");
            return (WaveMessageStatus.WAVE_MESSAGE_ERROR_NO_OMS_FOR_SERVICE);
        }

        // Set this so the message can be returned. In fact one way messages can never be returned. This is set so that
        // in case we need to refer it at the receiver end.

        waveMessage.setSenderServiceCode (m_associatedWaveThread.getWaveServiceId ());

        // Store the receiver LocationId.

        waveMessage.setReceiverLocationId ((LocationId.isNotNull (effectiveLocationId)) ? effectiveLocationId : thisLocationId);

        // Set the field to indicate the message is a one way message so that when the receiver replies, the framework will
        // not attempt to deliver it back to the original sender. It will simply destroy the message.

        waveMessage.setIsOneWayMessage (true);

        if ((null != m_inputMessage) && ((m_associatedWaveThread.getWaveThreadId ()).equals (waveMessage.getWaveMessageCreatorThreadId ())))
        {
            // Propagate message flags from Incoming Message to Outgoing Message

            waveMessage.setIsConfigurationChanged (m_inputMessage.getIsConfigurationChanged ());
            waveMessage.setIsConfigurationTimeChanged (m_inputMessage.getIsConfigurationTimeChanged ());
        }

        addMessageToMessageHistoryCalledFromSend (waveMessage);

        final WaveMessageStatus status = waveThread.submitMessage (waveMessage);

        return (status);
    }

    @NonMessageHandler
    private void addMessageToMessageHistoryCalledFromSend (final WaveMessage waveMessage)
    {
        // TODO Auto-generated method stub
    }
}
