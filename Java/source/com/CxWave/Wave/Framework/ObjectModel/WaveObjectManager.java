/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import java.lang.annotation.Annotation;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.Vector;

import com.CxWave.Wave.Framework.Core.WaveFrameworkObjectManager;
import com.CxWave.Wave.Framework.Core.Messages.FrameworkObjectManagerConfigurationIntentBufferId;
import com.CxWave.Wave.Framework.Core.Messages.FrameworkObjectManagerRemoveConfigurationIntentMessage;
import com.CxWave.Wave.Framework.Core.Messages.FrameworkObjectManagerStoreConfigurationIntentMessage;
import com.CxWave.Wave.Framework.Core.Messages.WaveObjectManagerRegisterEventListenerMessage;
import com.CxWave.Wave.Framework.Messaging.LightHouse.LightHouseTransportBroadcastLightPulseMessage;
import com.CxWave.Wave.Framework.Messaging.LightHouse.LightPulse;
import com.CxWave.Wave.Framework.Messaging.LightHouse.LightPulseRegistrationMessage;
import com.CxWave.Wave.Framework.Messaging.LightHouse.LightPulseUnregistrationMessage;
import com.CxWave.Wave.Framework.Messaging.Local.WaveEvent;
import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.Messaging.MessageFactory.WaveMessageFactory;
import com.CxWave.Wave.Framework.MultiThreading.WaveThread;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonEventHandler;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonMessageHandler;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonOM;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.ObjectManagerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Boot.WaveAsynchronousContextForBootPhases;
import com.CxWave.Wave.Framework.Persistence.Local.PersistenceLocalObjectManager;
import com.CxWave.Wave.Framework.Timer.TimerObjectManagerAddTimerMessage;
import com.CxWave.Wave.Framework.Timer.TimerObjectManagerDeleteTimerMessage;
import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
import com.CxWave.Wave.Framework.Trace.TraceObjectManager;
import com.CxWave.Wave.Framework.Type.LocationId;
import com.CxWave.Wave.Framework.Type.TimeValue;
import com.CxWave.Wave.Framework.Type.TimerHandle;
import com.CxWave.Wave.Framework.Type.TraceClientId;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Type.UI64;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Source.WaveJavaSourceRepository;
import com.CxWave.Wave.Framework.Utils.Stack.WaveStackUtils;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveCondition;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.FrameworkStatus;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;
import com.CxWave.Wave.Resources.ResourceEnums.WaveMessageStatus;
import com.CxWave.Wave.Resources.ResourceEnums.WaveMessageType;
import com.CxWave.Wave.Resources.ResourceEnums.WaveObjectManagerPriority;
import com.CxWave.Wave.Resources.ResourceEnums.WaveServiceMode;

public class WaveObjectManager extends WaveElement
{
    private class WaveOperationMapContext
    {
        private final WaveMessageHandler m_waveMessageHandler;

        public WaveOperationMapContext (final WaveElement waveElement, final Method method)
        {
            WaveAssertUtils.waveAssert (null != waveElement);
            WaveAssertUtils.waveAssert (null != method);

            m_waveMessageHandler = new WaveMessageHandler (method, waveElement);
        }

        public void executeMessageHandler (final WaveMessage waveMessage)
        {
            WaveAssertUtils.waveAssert (null != m_waveMessageHandler);

            try
            {
                m_waveMessageHandler.execute (waveMessage);
            }
            catch (final Exception e)
            {
                errorTracePrintf ("WaveObjectManager.WaveOperationMapContext.executeMessageHandler : Could not execute message handler.  MessageType : %s, Details : %s", (waveMessage.getClass ()).getName (), e.toString ());

                final Throwable cause = e.getCause ();

                if (null != cause)
                {
                    errorTracePrintf ("WaveObjectManager.WaveOperationMapContext.executeMessageHandler : Could not execute message handler.  Cause : %s", cause.toString ());

                    WaveTraceUtils.fatalTracePrintf ("%s", WaveStackUtils.getStackString (cause));
                }

                WaveTraceUtils.fatalTracePrintf ("%s", WaveStackUtils.getStackString (e));

                waveMessage.setCompletionStatus (ResourceId.WAVE_MESSAGE_ERROR_OPERATION_NOT_SUPPORTED);

                reply (waveMessage);
            }
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

            WaveAssertUtils.waveAssert (null != m_waveElementThatHandlesTheEvent);
            WaveAssertUtils.waveAssert (null != m_waveEventHandler);

            m_waveEventHandler.validateAndCompute (m_waveElementThatHandlesTheEvent);
        }

        public void executeEventHandler (final WaveEvent waveEvent)
        {
            WaveAssertUtils.waveAssert (null != waveEvent);

            m_waveEventHandler.execute (waveEvent);
        }
    };

    private class WaveLightPulseMapContext
    {

        private final WaveElement           m_waveElementThatHandlesTheLightPulse;
        private final WaveLightPulseHandler m_waveLightPulseHandler;

        public WaveLightPulseMapContext (final WaveElement waveElement, final WaveLightPulseHandler waveLightPulseHandler)
        {
            m_waveElementThatHandlesTheLightPulse = waveElement;
            m_waveLightPulseHandler = waveLightPulseHandler;

            WaveAssertUtils.waveAssert (null != m_waveElementThatHandlesTheLightPulse);
            WaveAssertUtils.waveAssert (null != m_waveLightPulseHandler);

            m_waveLightPulseHandler.validateAndCompute (m_waveElementThatHandlesTheLightPulse);
        }

        public void executeLightPulseHandler (final LightPulse lightPulse)
        {
            WaveAssertUtils.waveAssert (null != lightPulse);

            m_waveLightPulseHandler.execute (lightPulse);
        }
    };

    private class WaveMessageResponseContext
    {
        private final WaveMessage                m_waveMessage;
        private final WaveElement                m_waveMessageSender;
        private final WaveMessageResponseHandler m_waveMessageSenderCallback;
        private final Object                     m_waveMessageSenderContext;
        private boolean                          m_isMessageTimedOut             = false;
        private WaveMessage                      m_inputMessageInResponseContext = null;
        private boolean                          m_isTimerStarted                = false;
        private TimerHandle                      m_timerHandle                   = TimerHandle.NullTimerHandle;

        public WaveMessageResponseContext (final WaveMessage waveMessage, final WaveElement waveMessageSender, final WaveMessageResponseHandler waveMessageSenderCallback, final Object waveMessageSenderContext)
        {
            m_waveMessage = waveMessage;
            m_waveMessageSender = waveMessageSender;
            m_waveMessageSenderCallback = waveMessageSenderCallback;
            m_waveMessageSenderContext = waveMessageSenderContext;

            m_waveMessageSenderCallback.validateAndCompute (m_waveMessageSender);
        }

        public void executeResponseCallback (final FrameworkStatus frameworkStatus, final WaveMessage waveMessage, final boolean isMessageRecalled)
        {
            if (null == m_waveMessageSenderCallback)
            {
                // Nothing to do.
            }
            else
            {
                // We treat timed out messages differently. If a message is timed out we simply mark this context
                // to indicate the time out and execute the user callback with a Null Message pointer.

                if (FrameworkStatus.FRAMEWORK_TIME_OUT != frameworkStatus)
                {
                    // We take waveMessage input so that multiple replies with messages copies is also possible. But the current
                    // methodology that we decided to follow is this: If there are multiple replies for a message then the
                    // message
                    // must not be deleted upon receiving intermediate replies. It must be deleted only after receiving the last
                    // reply. Though we have the infrastructure to support multiple replies with message copies, currently we do
                    // not copy the message for the purpose of multiple replies. So when the response comes back it must always
                    // be
                    // the original message. The following waveAssert enforces that.

                    // Update to the above comment (at the time of implementing support for multiple replies feature):
                    // The below enforcement is only done in case of last reply.

                    if (true == (waveMessage.getIsLastReply ()))
                    {
                        WaveAssertUtils.waveAssert (waveMessage == m_waveMessage);

                        if (waveMessage != m_waveMessage)
                        {
                            return;
                        }
                    }

                    // If we decide to support the multiple replies using message copies then the above waveAssert and if block
                    // must be removed.

                    // If the context was previously marked with timed out status, then we must not execute the user context.
                    // We must simply delete the message.

                    if (false == (getIsMessageTimedOut ()))
                    {
                        m_waveMessageSenderCallback.execute (frameworkStatus, waveMessage, m_waveMessageSenderContext);
                    }
                }
                else
                {
                    setIsMessageTimedOut (true);

                    if (true == isMessageRecalled)
                    {
                        m_waveMessageSenderCallback.execute (frameworkStatus, waveMessage, m_waveMessageSenderContext);
                    }
                    else
                    {
                        m_waveMessageSenderCallback.execute (frameworkStatus, null, m_waveMessageSenderContext);
                    }
                }
            }
        }

        public void executeResponseCallback (final FrameworkStatus frameworkStatus, final WaveMessage waveMessage)
        {
            executeResponseCallback (frameworkStatus, waveMessage, false);
        }

        public void executeResponseCallback (final FrameworkStatus frameworkStatus)
        {
            executeResponseCallback (frameworkStatus, m_waveMessage);
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

    private static WaveMutex                                                          s_waveObjectManagerMutex                         = new WaveMutex ();
    private static WaveServiceId                                                      s_nextAvailableWaveServiceId                     = new WaveServiceId (0);
    private static WaveServiceMode                                                    s_waveServiceLaunchMode                          = WaveServiceMode.WAVE_SERVICE_ACTIVE;

    private static final Set<UI32>                                                    s_operationsAllowedBeforeEnabling                = initializeOperationsAllowedBeforeEnablingSet ();
    private static final WaveMutex                                                    s_mutexForAddingEventListener                    = new WaveMutex ();

    private static final WaveMutex                                                    s_supportedLightPulsesMutex                      = new WaveMutex ();
    private static final Map<String, WaveObjectManager>                               s_lightPulseToWaveObjectManagerMap               = new HashMap<String, WaveObjectManager> ();

    private final String                                                              m_name;
    private WaveThread                                                                m_associatedWaveThread;
    private final Map<UI32, WaveOperationMapContext>                                  m_operationsMap                                  = new HashMap<UI32, WaveOperationMapContext> ();
    private final Map<Class<?>, UI32>                                                 m_operationsClassToIdMap                         = new HashMap<Class<?>, UI32> ();
    private final Map<UI32, Class<?>>                                                 m_operationsIdToClassMap                         = new HashMap<UI32, Class<?>> ();
    private final Map<UI32, UI32>                                                     m_supportedEvents                                = new HashMap<UI32, UI32> ();
    private final WaveMutex                                                           m_supportedEventsMutex                           = new WaveMutex ();
    private final Map<LocationId, Map<WaveServiceId, Map<UI32, WaveEventMapContext>>> m_eventsMap                                      = new HashMap<LocationId, Map<WaveServiceId, Map<UI32, WaveEventMapContext>>> ();
    private final Map<String, String>                                                 m_supportedLightPulses                           = new HashMap<String, String> ();
    private final Map<String, WaveLightPulseMapContext>                               m_lightPulsesMap                                 = new HashMap<String, WaveLightPulseMapContext> ();
    private final Map<UI32, WaveMessageResponseContext>                               m_responsesMap                                   = new HashMap<UI32, WaveMessageResponseContext> ();
    private final Map<UI32, Vector<WaveEventListenerMapContext>>                      m_eventListenersMap                              = new HashMap<UI32, Vector<WaveEventListenerMapContext>> ();
    private Map<String, Vector<String>>                                               m_postbootManagedObjectNames;
    private final WaveMutex                                                           m_responsesMapMutex                              = new WaveMutex ();
    private final WaveMutex                                                           m_sendReplyMutexForResponseMap                   = new WaveMutex ();
    private final Vector<WaveWorker>                                                  m_workers                                        = new Vector<WaveWorker> ();
    private final Map<Class<? extends WaveWorker>, Vector<WaveWorker>>                m_workersMapByWorkerClass                        = new HashMap<Class<? extends WaveWorker>, Vector<WaveWorker>> ();
    private final WaveMutex                                                           m_workersMutex                                   = new WaveMutex ();
    private boolean                                                                   m_isEnabled                                      = false;
    private final WaveMutex                                                           m_isEnabledMutex                                 = new WaveMutex ();
    private final TraceClientId                                                       m_traceClientId;
    private final WaveServiceMode                                                     m_waveServiceMode;

    private final WaveServiceId                                                       m_serviceId;

    private WaveMessage                                                               m_inputMessage;

    private final Map<UI32, Map<UI32, UI64>>                                          m_nanoSecondsForMessageHandlerSequencerSteps     = new HashMap<UI32, Map<UI32, UI64>> ();

    private final Map<UI32, Map<UI32, UI64>>                                          m_realNanoSecondsForMessageHandlerSequencerSteps = new HashMap<UI32, Map<UI32, UI64>> ();

    private final WaveMutex                                                           m_createMessageInstanceWrapperMutex              = new WaveMutex ();
    private final Map<UI32, WaveElement>                                              m_ownersForCreatingMessageInstances              = new HashMap<UI32, WaveElement> ();

    private final WaveMutex                                                           m_createLightPulseInstanceWrapperMutex           = new WaveMutex ();
    private final Map<String, WaveElement>                                            m_ownersForCreatingLightPulseInstances           = new HashMap<String, WaveElement> ();

    private static WaveMutex                                                          s_enabledServicesMutex                           = new WaveMutex ();
    private static Map<WaveServiceId, WaveServiceId>                                  s_enabledServices                                = new HashMap<WaveServiceId, WaveServiceId> ();

    private boolean                                                                   m_allowAutomaticallyUnlistenForEvents            = true;

    public void prepareObjectManagerForAction ()
    {
        addWorkers ();
        addSupportedOperations ();
        addSupportedEvents ();
    }

    public void addSupportedOperations ()
    {
        final Map<Class<?>, Method> messageHandlersInInheritanceHierarchyPreferringLatest = WaveJavaSourceRepository.getMessageHandlersInInheritanceHierarchyPreferringLatest ((getClass ()).getName ());

        for (final Map.Entry<Class<?>, Method> entry : messageHandlersInInheritanceHierarchyPreferringLatest.entrySet ())
        {
            addOperationMapForMessageClass (entry.getKey (), entry.getValue (), this);
        }
    }

    private void addEventType (final UI32 eventOperationCode)
    {
        m_supportedEventsMutex.lock ();

        m_supportedEvents.put (eventOperationCode, eventOperationCode);

        m_supportedEventsMutex.unlock ();
    }

    public boolean isEventOperationCodeSupported (final UI32 eventOperationCode)
    {
        m_supportedEventsMutex.lock ();

        final boolean isSupported = m_supportedEvents.containsKey (eventOperationCode);

        m_supportedEventsMutex.unlock ();

        return (isSupported);
    }

    public boolean isEventOperationCodeSupportedForListening (final LocationId eventSourceLocationId, final WaveServiceId eventSourceServiceId, final UI32 eventOperationCode)
    {
        if (null != (getWaveEventHandler (eventSourceLocationId, eventSourceServiceId, eventOperationCode)))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }

    public void addSupportedEvents ()
    {
        final String waveJavaClassName = (getClass ()).getName ();
        final Set<String> eventClassNames = WaveJavaSourceRepository.getEventClassNamesForClass (waveJavaClassName);

        WaveAssertUtils.waveAssert (null != eventClassNames);

        for (final String eventClassName : eventClassNames)
        {
            Class<?> eventClass = null;

            try
            {
                eventClass = Class.forName (eventClassName);
            }
            catch (final ClassNotFoundException e)
            {
                fatalTracePrintf ("WaveObjectManager.addSupportedEvents : %s event class could not be found.", eventClassName);

                waveAssert ();
            }

            if (null != eventClass)
            {
                final UI32 operationCode = WaveEvent.getOperationCodeForEventClass (eventClass);

                infoTracePrintf ("WaveObjectManager.addSupportedEvents : %s event class with %s operation code is added to OM : %s", eventClassName, operationCode.toString (), m_name);

                addEventType (operationCode);
            }
        }
    }

    public void listenForEventsDefaultImplementation ()
    {
        infoTracePrintf ("WaveObjectManager.listenForEventsDefaultImplementation : Entering for : %s", (getClass ()).getTypeName ());

        final Map<Class<?>, Method> eventHandlersForThisClass = WaveJavaSourceRepository.getEventHandlersInInheritanceHierarchyPreferringLatest ((getClass ()).getTypeName ());

        for (final Map.Entry<Class<?>, Method> entry : eventHandlersForThisClass.entrySet ())
        {
            final Class<?> eventClass = entry.getKey ();
            final Method eventHandlerMethod = entry.getValue ();

            waveAssert (null != eventClass);
            waveAssert (null != eventHandlerMethod);

            infoTracePrintf ("WaveObjectManager.listenForEventsDefaultImplementation : Adding Event Handler %s in OM : %s, for Event : %s, using : %s", eventHandlerMethod.getName (), m_name, eventClass.getTypeName (), (getClass ()).getTypeName ());

            addOperationMapForEventClass (eventClass, eventHandlerMethod, this);
        }

        final Map<Class<?>, Method> lightPulseHandlersForThisClass = WaveJavaSourceRepository.getLightPulseHandlersInInheritanceHierarchyPreferringLatest ((getClass ()).getTypeName ());

        for (final Map.Entry<Class<?>, Method> entry : lightPulseHandlersForThisClass.entrySet ())
        {
            final Class<?> lightPulseClass = entry.getKey ();
            final Method lightPulseHandlerMethod = entry.getValue ();

            waveAssert (null != lightPulseClass);
            waveAssert (null != lightPulseHandlerMethod);

            infoTracePrintf ("WaveObjectManager.listenForEventsDefaultImplementation : Adding Light Pulse Handler %s in OM : %s, for Event : %s, using : %s", lightPulseHandlerMethod.getName (), m_name, lightPulseClass.getTypeName (), (getClass ()).getTypeName ());

            addOperationMapForLightPulseClass (lightPulseClass, lightPulseHandlerMethod, this);
        }
    }

    @Override
    protected void addLightPulseType (final String lightPulseName)
    {
        addLightPulseType (lightPulseName, this);
    }

    @Override
    protected void addLightPulseType (final String lightPulseName, final WaveElement waveElement)
    {
        s_supportedLightPulsesMutex.lock ();

        m_supportedLightPulses.put (lightPulseName, lightPulseName);

        if (!(s_lightPulseToWaveObjectManagerMap.containsKey (lightPulseName)))
        {
            s_lightPulseToWaveObjectManagerMap.put (lightPulseName, this);
        }
        else
        {
            trace (TraceLevel.TRACE_LEVEL_FATAL, "WaveObjectManager.addLightPulseType : Light Pulse Type " + lightPulseName + " has already been registered elsewhere.");
            waveAssert ();
        }

        s_supportedLightPulsesMutex.unlock ();

        m_createLightPulseInstanceWrapperMutex.lock ();

        if (!(m_ownersForCreatingLightPulseInstances.containsKey (lightPulseName)))
        {
            m_ownersForCreatingLightPulseInstances.put (lightPulseName, waveElement);
        }
        else
        {
            trace (TraceLevel.TRACE_LEVEL_FATAL, "WaveObjectManager::addLightPulseType : Trying to set duplicate Owner.  Owner for \"" + lightPulseName + "\" was already set.");
            waveAssert ();
        }

        m_createLightPulseInstanceWrapperMutex.unlock ();
    }

    public boolean isLightPulseNameSupported (final String lightPulseName)
    {
        s_supportedLightPulsesMutex.lock ();

        final boolean isSupported = m_supportedLightPulses.containsKey (lightPulseName);

        s_supportedLightPulsesMutex.unlock ();

        return (isSupported);
    }

    public boolean isLightPulseNameSupportedForListening (final String lightPulseName)
    {
        if (null != (getWaveLightPulseHandler (lightPulseName)))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }

    public void addSupportedLightPulses ()
    {
        final String waveJavaClassName = (getClass ()).getName ();
        final Set<String> lightPulseClassNames = WaveJavaSourceRepository.getLightPulseClassNamesForClass (waveJavaClassName);

        WaveAssertUtils.waveAssert (null != lightPulseClassNames);

        for (final String lightPulseClassName : lightPulseClassNames)
        {
            Class<?> lightPulseClass = null;

            try
            {
                lightPulseClass = Class.forName (lightPulseClassName);
            }
            catch (final ClassNotFoundException e)
            {
                fatalTracePrintf ("WaveObjectManager.addSupportedLightPulses : %s lightpulse class could not be found.", lightPulseClassName);

                waveAssert ();
            }

            if (null != lightPulseClass)
            {
                final String lightPulseName = LightPulse.getLightPulseNameForLightPulseClass (lightPulseClass);

                infoTracePrintf ("WaveObjectManager.addSupportedLightPulses : %s lightpulse class with %s name is added to OM : %s", lightPulseClassName, lightPulseName, m_name);

                addLightPulseType (lightPulseName);
            }
        }
    }

    public LightPulse createLightPulseInstanceWrapper (final String lightPulseName)
    {
        LightPulse lightPulse = null;

        m_createLightPulseInstanceWrapperMutex.lock ();

        final WaveElement waveElement = m_ownersForCreatingLightPulseInstances.get (lightPulseName);

        if (null != waveElement)
        {
            lightPulse = waveElement.createLightPulseInstance (lightPulseName);
        }

        m_createLightPulseInstanceWrapperMutex.unlock ();

        return (lightPulse);
    }

    public static WaveObjectManager getWaveObjectManagerForLightPulseType (final String lightPulseName)
    {
        WaveObjectManager waveObjectManager = null;

        s_supportedLightPulsesMutex.lock ();

        waveObjectManager = s_lightPulseToWaveObjectManagerMap.get (lightPulseName);

        s_supportedLightPulsesMutex.unlock ();

        return (waveObjectManager);
    }

    @Override
    protected LightPulse createLightPulseInstance (final String lightPulseName)
    {
        trace (TraceLevel.TRACE_LEVEL_ERROR, "WaveObjectManager.createLightPulseInstance : NOT IMPLEMENTED.  RETURNS NULL BY DEFAULT.");
        trace (TraceLevel.TRACE_LEVEL_ERROR, "WaveObjectManager.createLightPulseInstance : ObjectManagers and Workers MUST overwrite this virtual function.");
        return (null);
    }

    private void addWorkers ()
    {
        final String waveJavaClassName = (getClass ()).getName ();
        final Vector<String> workerClassNames = WaveJavaSourceRepository.getWorkerClassNamesForClass (waveJavaClassName);

        WaveAssertUtils.waveAssert (null != workerClassNames);

        infoTracePrintf ("WaveObjectManager.addWorkers : Adding Workers for Object Manager : %s", m_name);

        final Map<WaveWorkerPriority, Vector<String>> workersByPriority = new HashMap<WaveWorkerPriority, Vector<String>> ();
        final Map<String, Integer> workersCardinality = new HashMap<String, Integer> ();
        final Vector<WaveWorkerPriority> allUsedPrioritiesForWorkers = new Vector<WaveWorkerPriority> ();

        for (final String workerClassName : workerClassNames)
        {
            final int cardinality = WaveJavaSourceRepository.getWorkerClassCardinality (waveJavaClassName, workerClassName);
            final WaveWorkerPriority priority = WaveJavaSourceRepository.getWorkerClassProiority (waveJavaClassName, workerClassName);

            infoTracePrintf ("WaveObjectManager.addWorkers :     Worker : %s, Cardinality : %d, Priority : %s", workerClassName, cardinality, priority);

            if (workersByPriority.containsKey (priority))
            {
                final Vector<String> workersForThisPriority = workersByPriority.get (priority);

                workersForThisPriority.add (workerClassName);
            }
            else
            {
                final Vector<String> workersForThisPriority = new Vector<String> ();

                workersForThisPriority.add (workerClassName);

                workersByPriority.put (priority, workersForThisPriority);
            }

            workersCardinality.put (workerClassName, cardinality);

            if (!(allUsedPrioritiesForWorkers.contains (priority)))
            {
                allUsedPrioritiesForWorkers.add (priority);
            }
        }

        Collections.sort (allUsedPrioritiesForWorkers);

        for (final WaveWorkerPriority priority : allUsedPrioritiesForWorkers)
        {
            final Vector<String> workersForThisPriority = workersByPriority.get (priority);

            WaveAssertUtils.waveAssert (null != workersForThisPriority);

            infoTracePrintf ("WaveObjectManager.addWorkers :     Now instantiating Workers for Priority %s", priority);

            for (final String workerClassName : workersForThisPriority)
            {
                WaveAssertUtils.waveAssert (WaveStringUtils.isNotBlank (workerClassName));

                infoTracePrintf ("WaveObjectManager.addWorkers :         Now instantiating Worker %s", workerClassName);

                Class<?> waveWorkerClass = null;

                try
                {
                    waveWorkerClass = Class.forName (workerClassName);
                }
                catch (final ClassNotFoundException e)
                {
                    e.printStackTrace ();
                }

                WaveAssertUtils.waveAssert (null != waveWorkerClass);

                Constructor<?> constructor = null;

                final Constructor<?> declaredConstructors[] = waveWorkerClass.getDeclaredConstructors ();

                for (final Constructor<?> declaredConstructor : declaredConstructors)
                {
                    final int numberOfParameters = declaredConstructor.getParameterCount ();

                    if (1 == numberOfParameters)
                    {
                        final Class<?> parameterTypes[] = declaredConstructor.getParameterTypes ();

                        final Class<?> parameterType = parameterTypes[0];

                        final String paramterTypeName = parameterType.getTypeName ();

                        if (WaveJavaSourceRepository.isAderivativeOfWaveObjectManager (paramterTypeName))
                        {
                            constructor = declaredConstructor;
                        }
                    }
                }

                if (null == constructor)
                {
                    infoTracePrintf ("WaveObjectManager.addWorkers :        A constructor that takes WaveObjectManager/descendandant as argument could not be found.");

                    WaveAssertUtils.waveAssert ();
                }

                WaveAssertUtils.waveAssert (null != constructor);

                Object object = null;

                try
                {
                    constructor.setAccessible (true);

                    WaveAssertUtils.waveAssert (null != this);

                    object = constructor.newInstance (this);
                }
                catch (InstantiationException | IllegalAccessException | IllegalArgumentException e)
                {
                    fatalTracePrintf ("WaveObjectManager.addWorkers :        A constructor that takes WaveObjectManager/descendant as argument could not be executed.  Details : %s", e.toString ());

                    WaveAssertUtils.waveAssert ();
                }
                catch (final InvocationTargetException e1)
                {
                    fatalTracePrintf ("WaveObjectManager.addWorkers :        A constructor that takes WaveObjectManager/descendant as argument could not be executed.  Details : %s", WaveStackUtils.getStackString (e1.getCause ()));
                }

                WaveAssertUtils.waveAssert (null != object);

                WaveAssertUtils.waveAssert (object instanceof WaveWorker);

                final WaveWorker waveWorker = (WaveWorker) object;

                WaveAssertUtils.waveAssert (null != waveWorker);

                waveWorker.addSupportedOperations ();
            }
        }
    }

    protected WaveObjectManager (final String waveObjectManagerName, final UI32 stackSize)
    {
        super ();

        setWaveObjectManager (this);

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

        m_associatedWaveThread.addWaveObjectManager (this);

        m_associatedWaveThread.start ();
    }

    protected WaveObjectManager (final String waveObjectManagerName)
    {
        super ();

        setWaveObjectManager (this);

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

        final Set<String> serviceNames = new HashSet<String> ();

        serviceNames.add (WaveFrameworkObjectManager.getServiceName ());

        if (serviceNames.contains (waveServiceName))
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

        m_createMessageInstanceWrapperMutex.lock ();

        if (!(m_ownersForCreatingMessageInstances.containsKey (operationCode)))
        {
            m_ownersForCreatingMessageInstances.put (operationCode, waveElement);
        }
        else
        {
            WaveTraceUtils.fatalTracePrintf ("WaveObjectManager.addOperationMap : Trying to set duplicate Owner.  Owner for %d was already set.", operationCode.getValue ());
            WaveAssertUtils.waveAssert (false);
        }

        m_createMessageInstanceWrapperMutex.unlock ();
    }

    void addOperationMapForMessageClass (final Class<?> messageClass, final Method messageHandlerMethod, final WaveElement waveElement)
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

    public void addOperationMapForEventClass (final Class<?> eventClass, final Method eventHandlerMethod, final WaveElement waveElement)
    {
        final UI32 operationCode = WaveEvent.getOperationCodeForEventClass (eventClass);
        final WaveServiceId serviceCode = WaveEvent.getServiceCodeForEventClass (eventClass);

        listenForEvent (serviceCode, operationCode, eventHandlerMethod.getName (), waveElement, FrameworkToolKit.getThisLocationId ());
    }

    public void addOperationMapForLightPulseClass (final Class<?> lightPulseClass, final Method lightPulseHandlerMethod, final WaveElement waveElement)
    {
        final String lightPulseName = LightPulse.getLightPulseNameForLightPulseClass (lightPulseClass);

        listenForLightPulse (lightPulseName, lightPulseHandlerMethod.getName (), waveElement);
    }

    private void listenForEvent (final WaveServiceId waveServiceCode, final UI32 sourceOperationCode, final String waveEventHandlerMethodName, WaveElement waveElement, final LocationId sourceLocationId)
    {
        WaveServiceId waveServiceId = waveServiceCode;

        if (null == waveElement)
        {
            waveElement = this;
        }

        // If we are listening for WAVE_OBJECT_MANAGER_ANY_EVENT then we do not care about the service code. We treat that we
        // are listening to
        // null service.

        if ((FrameworkOpCodes.WAVE_OBJECT_MANAGER_ANY_EVENT.getOperationCode ()).equals (sourceOperationCode))
        {
            waveServiceId = WaveServiceId.NullServiceId;
        }

        final LocationId thisLocationId = FrameworkToolKit.getThisLocationId ();
        LocationId effectiveLocationId = sourceLocationId;

        // We will change the effectiveLocationId only if the event is not WAVE_OBJECT_MANAGER_ANY_EVENT

        if (!((FrameworkOpCodes.WAVE_OBJECT_MANAGER_ANY_EVENT.getOperationCode ()).equals (sourceOperationCode)))
        {
            if (LocationId.NullLocationId.equals (effectiveLocationId))
            {
                if (true != (FrameworkToolKit.isALocalService (waveServiceId)))
                {
                    effectiveLocationId = FrameworkToolKit.getClusterPrimaryLocationId ();
                }
            }
        }

        if (LocationId.NullLocationId.equals (effectiveLocationId))
        {
            effectiveLocationId = thisLocationId;
        }

        // Add an event map so that when the event arrives we can execute the corresponding event handler.

        if (!(m_eventsMap.containsKey (effectiveLocationId)))
        {
            m_eventsMap.put (effectiveLocationId, new HashMap<WaveServiceId, Map<UI32, WaveEventMapContext>> ());
        }

        final Map<WaveServiceId, Map<UI32, WaveEventMapContext>> eventsMapEntryForEffectiveLocationId = m_eventsMap.get (effectiveLocationId);

        waveAssert (null != eventsMapEntryForEffectiveLocationId);

        if (!(eventsMapEntryForEffectiveLocationId.containsKey (waveServiceId)))
        {
            eventsMapEntryForEffectiveLocationId.put (waveServiceId, new HashMap<UI32, WaveEventMapContext> ());
        }

        final Map<UI32, WaveEventMapContext> eventsMapEntryForEffectiveLocationIdAndWaveServiceId = eventsMapEntryForEffectiveLocationId.get (waveServiceId);

        waveAssert (null != eventsMapEntryForEffectiveLocationIdAndWaveServiceId);

        if (eventsMapEntryForEffectiveLocationIdAndWaveServiceId.containsKey (sourceOperationCode))
        {
            fatalTracePrintf ("WaveObjectManager.listenForEvent : OM : %s, already Listening for Event %s", m_name, sourceOperationCode.toString ());
            waveAssert ();
        }
        else
        {
            final WaveEventHandler waveEventHandler = new WaveEventHandler (waveEventHandlerMethodName);

            final WaveEventMapContext waveEventMapContext = new WaveEventMapContext (waveElement, waveEventHandler);

            eventsMapEntryForEffectiveLocationIdAndWaveServiceId.put (sourceOperationCode, waveEventMapContext);
        }

        // Update the event source service that we are interested to receive the particular events.
        // If the ObjectManager exists locally (meaning event source exists on this location) we simply execute a method on the
        // source object manager.
        // Otherwise we send a message to the remote event source object manager.

        if (thisLocationId.equals (effectiveLocationId))
        {
            WaveObjectManager waveObjectManager = null;

            waveObjectManager = WaveMessageFactory.getWaveObjectManagerForEvent (waveServiceId, sourceOperationCode);

            // The remote transport service listens for any events. The way it achieves listening for any event is that it
            // starts
            // listening
            // for any event that is generated by the null service. So the remote transport service does not have to specify a
            // valid service with an object manager.

            if (((!(WaveServiceId.NullServiceId.equals (waveServiceId))) || ((!(FrameworkOpCodes.WAVE_OBJECT_MANAGER_ANY_EVENT.getOperationCode ()).equals (sourceOperationCode)))) && (null == waveObjectManager))
            {
                fatalTracePrintf ("WaveObjectManager.listenForEvent : There is no Object Manager to generate the specified event. ServiceId = %s, Source OperationCode = %s.", waveServiceId.toString (), sourceOperationCode.toString ());
                waveAssert ();
                return;
            }

            // Now add the listener to the object manager.

            if (null != waveObjectManager)
            {
                waveObjectManager.addEventListener (sourceOperationCode, getServiceId (), FrameworkToolKit.getThisLocationId ());
            }
        }
        else
        {
            // If the event that we are listening to is anything other than WAVE_OBJECT_MANAGER_ANY_EVENT then only send the
            // remote message.
            // If the event to listen is WAVE_OBJECT_MANAGER_ANY_EVENT then it can be never on a remote location. This event is
            // only used
            // by the remote transport service to accept all events so that it can transport to remote location.

            if (((FrameworkOpCodes.WAVE_OBJECT_MANAGER_ANY_EVENT.getOperationCode ()).equals (sourceOperationCode)) && (!(thisLocationId.equals (effectiveLocationId))))
            {
                fatalTracePrintf ("WaveObjectManager.listenForEvent : We can never listen for WAVE_OBJECT_MANAGER_ANY_EVENT from remote locations.");
                waveAssert ();
            }

            if ((!(FrameworkOpCodes.WAVE_OBJECT_MANAGER_ANY_EVENT.getOperationCode ()).equals (sourceOperationCode)))
            {
                final WaveObjectManagerRegisterEventListenerMessage waveObjectManagerRegisterEventListenerMessage = new WaveObjectManagerRegisterEventListenerMessage (waveServiceId, sourceOperationCode, getServiceId (), thisLocationId);

                final WaveMessageStatus status = sendOneWay (waveObjectManagerRegisterEventListenerMessage);

                waveAssert (WaveMessageStatus.WAVE_MESSAGE_SUCCESS == status);
            }
        }
    }

    private void listenForLightPulse (final String lightPulseName, final String lightPulseHandlerMethodName, final WaveElement waveElement)
    {
        if (!(m_lightPulsesMap.containsKey (lightPulseHandlerMethodName)))
        {
            final WaveLightPulseHandler waveLightPulseHandler = new WaveLightPulseHandler (lightPulseHandlerMethodName);

            m_lightPulsesMap.put (lightPulseHandlerMethodName, new WaveLightPulseMapContext (waveElement, waveLightPulseHandler));
        }
        else
        {
            trace (TraceLevel.TRACE_LEVEL_FATAL, "WaveObjectManager.listenForLightPulse : This light pulse name is already registered : " + lightPulseName);

            waveAssert ();
        }

        final LightPulseRegistrationMessage lightPulseRegistrationMessage = new LightPulseRegistrationMessage (lightPulseName);

        final WaveMessageStatus sendStatus = sendSynchronously (lightPulseRegistrationMessage);

        if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS == sendStatus)
        {
            final ResourceId completionStatus = lightPulseRegistrationMessage.getCompletionStatus ();

            if (ResourceId.WAVE_MESSAGE_SUCCESS != completionStatus)
            {
                trace (TraceLevel.TRACE_LEVEL_FATAL, "WaveObjectManager.listenForLightPulse : This light pulse registration could not be successfully completed : " + lightPulseName + ", status : " + (FrameworkToolKit.localize (completionStatus)));

                waveAssert ();
            }
        }
        else
        {
            trace (TraceLevel.TRACE_LEVEL_FATAL, "WaveObjectManager.listenForLightPulse : This light pulse registration could not be sent : " + lightPulseName + ", status : " + (FrameworkToolKit.localize (sendStatus)));

            waveAssert ();
        }
    }

    private void addEventListener (final UI32 eventOperationCode, final WaveServiceId listenerWaveServiceId, final LocationId listenerWaveLocationId)
    {
        s_mutexForAddingEventListener.lock ();

        if (!(m_eventListenersMap.containsKey (eventOperationCode)))
        {
            m_eventListenersMap.put (eventOperationCode, new Vector<WaveEventListenerMapContext> ());
        }

        final Vector<WaveEventListenerMapContext> waveEventListenerMapContextsForEventOperationCode = m_eventListenersMap.get (eventOperationCode);

        waveAssert (null != waveEventListenerMapContextsForEventOperationCode);

        final WaveEventListenerMapContext waveEventListenerMapContext = new WaveEventListenerMapContext (listenerWaveServiceId, listenerWaveLocationId);

        waveEventListenerMapContextsForEventOperationCode.add (waveEventListenerMapContext);

        infoTracePrintf ("WaveObjectManager.addEventListener : Number Of Event Listeners For Event : %s : %s on Service %s", eventOperationCode.toString (), waveEventListenerMapContextsForEventOperationCode.size (), m_name);

        s_mutexForAddingEventListener.unlock ();
    }

    private void registerEventListenerHandler (final WaveObjectManagerRegisterEventListenerMessage waveObjectManagerRegisterEventListenerMessage)
    {
        final UI32 operationCodeToListenFor = waveObjectManagerRegisterEventListenerMessage.getOperationCodeToListenFor ();
        final WaveServiceId listenerWaveServiceId = waveObjectManagerRegisterEventListenerMessage.getListenerWaveServiceId ();
        final LocationId listenerLocationId = waveObjectManagerRegisterEventListenerMessage.getListenerLocationId ();

        addEventListener (operationCodeToListenFor, listenerWaveServiceId, listenerLocationId);

        waveObjectManagerRegisterEventListenerMessage.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);

        reply (waveObjectManagerRegisterEventListenerMessage);
    }

    @Override
    @NonEventHandler
    protected WaveMessageStatus broadcast (final WaveEvent waveEvent)
    {
        final UI32 eventOperationCode = waveEvent.getOperationCode ();
        final Vector<WaveEventListenerMapContext> eventListeners;
        int numberOfEventListeners = 0;
        int i = 0;
        WaveMessageStatus status = WaveMessageStatus.WAVE_MESSAGE_SUCCESS;

        s_mutexForAddingEventListener.lock ();

        eventListeners = m_eventListenersMap.get (eventOperationCode);

        if (null == eventListeners)
        {
            s_mutexForAddingEventListener.unlock ();

            // delete mem if we don't have any listeners
            // DO NOT CALL reply(waveEvent) AS THIS MAY SEND REPLY FOR WaveMessage!!!
            if (0 == (waveEvent.decrementReferenceCountForEventNotifications ()))
            {
                // Nothing to do.
            }

            return (WaveMessageStatus.WAVE_MESSAGE_SUCCESS);
        }

        numberOfEventListeners = eventListeners.size ();

        debugTracePrintf ("WaveObjectManager.broadcast : Number Of Event Listeners for Event : %s are %d on Service : %s", eventOperationCode.toString (), numberOfEventListeners, m_name);

        waveEvent.m_senderServiceCode = m_associatedWaveThread.getWaveServiceId ();

        // Set the field to indicate the message is a one way message so that when the receiver replies, the framework will
        // not attempt to deliver it back to the original sender. It will simply destroy the event.

        waveEvent.setIsOneWayMessage (true);

        // Set the number of event listeners for the event. This will be used to reference count and delete it when all the
        // listeners are done.

        waveEvent.setReferenceCountForEventNotifications (numberOfEventListeners);

        for (i = 0; i < numberOfEventListeners; i++)
        {
            final WaveEventListenerMapContext waveEventListenerContext = eventListeners.get (i);

            waveAssert (null != waveEventListenerContext);

            WaveThread waveThread = null;
            final LocationId thisLocationId = FrameworkToolKit.getThisLocationId ();
            final WaveServiceId listenerServiceId = waveEventListenerContext.getEventListenerServiceId ();
            LocationId effectiveLocationId = waveEventListenerContext.getEventListenerLocationId ();

            // FIXME : sagar : replace the 0 with NullLocationId

            if (LocationId.NullLocationId.equals (effectiveLocationId))
            {
                if (true != (FrameworkToolKit.isALocalService (listenerServiceId)))
                {
                    effectiveLocationId = FrameworkToolKit.getClusterPrimaryLocationId ();
                }
            }

            if ((LocationId.NullLocationId.equals (effectiveLocationId)) || (thisLocationId.equals (effectiveLocationId)))
            {
                waveThread = WaveThread.getWaveThreadForServiceId (listenerServiceId);
            }
            else
            {
                waveThread = WaveThread.getWaveThreadForMessageRemoteTransport ();
            }

            if (null == waveThread)
            {
                errorTracePrintf ("WaveObjectManager.broadcast : No Service registered to accept this service Id %s", listenerServiceId.toString ());
                reply (waveEvent);
                continue;
            }

            if (false == (waveThread.hasWaveObjectManagers ()))
            {
                errorTracePrintf ("WaveObjectManager.broadcast : Service identified.  But there are no Wave Object Managers registered to process any kind of requests.");
                reply (waveEvent);
                continue;
            }

            // Store the receiver LocationId.
            // Though we store the locationid, this gets overwritten in the next iteraton of the loop.

            waveEvent.m_receiverLocationId = (!(LocationId.NullLocationId.equals (effectiveLocationId))) ? effectiveLocationId : thisLocationId;

            status = waveThread.submitEvent (waveEvent);

            if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
            {
                // Reply so that the event reference count decrements and eventually gets deleted.

                reply (waveEvent);
            }
        }

        s_mutexForAddingEventListener.unlock ();

        return (WaveMessageStatus.WAVE_MESSAGE_SUCCESS);
    }

    @NonEventHandler
    WaveMessageStatus reply (final WaveEvent waveEvent)
    {
        // When all the listeners are done with the event, delete the event.

        if (0 == (waveEvent.decrementReferenceCountForEventNotifications ()))
        {
            // Nothing to do;
        }

        return (WaveMessageStatus.WAVE_MESSAGE_SUCCESS);
    }

    public WaveMessage getInputMessage ()
    {
        return (m_inputMessage);
    }

    @Override
    @NonMessageHandler
    protected WaveMessageStatus sendOneWay (final WaveMessage waveMessage)
    {
        return (sendOneWay (waveMessage, LocationId.NullLocationId));
    }

    @Override
    protected WaveMessageStatus sendOneWay (final WaveMessage waveMessage, final LocationId locationId)
    {
        WaveThread waveThread = null;
        final LocationId thisLocationId = FrameworkToolKit.getThisLocationId ();
        LocationId effectiveLocationId = locationId;

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
            // ") + waveMessage.getServiceCode () + ".");

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

    @Override
    @NonMessageHandler
    protected WaveMessageStatus sendSynchronously (final WaveMessage waveMessage)
    {
        return (sendSynchronously (waveMessage, new LocationId (0)));
    }

    @Override
    protected WaveMessageStatus sendSynchronously (final WaveMessage waveMessage, final LocationId locationId)
    {
        // NOTICE :
        // In this method the order of lock, wait and unlock are very very important.
        // It has been coded so that there will be no dead locks.
        // If you are modifying the code - DON'T DO IT. But if you must modify it,
        // PLEASE PLEASE make sure that the existing behavior is not broken.

        WaveThread waveThread = null;
        final LocationId thisLocationId = FrameworkToolKit.getThisLocationId ();
        LocationId effectiveLocationId = locationId;

        if (LocationId.isNull (effectiveLocationId))
        {
            if (true != (FrameworkToolKit.isALocalService (waveMessage.getServiceCode ())))
            {
                effectiveLocationId = FrameworkToolKit.getClusterPrimaryLocationId ();
                final LocationId myLocationId = FrameworkToolKit.getPhysicalLocationId ();

                if (effectiveLocationId.equals (myLocationId))
                {
                    effectiveLocationId = LocationId.NullLocationId;
                }
            }
        }

        if ((LocationId.isNull (effectiveLocationId)) || (thisLocationId.equals (effectiveLocationId)))
        {

            if ((waveMessage.getServiceCode ()).equals (m_serviceId))
            {
                final String serviceName = FrameworkToolKit.getServiceNameById (m_serviceId);
                final UI32 operationCode = waveMessage.getOperationCode ();

                errorTracePrintf ("WaveObjectManager.sendSynchronously : Service [%s] cannot send message [serviceCode=%s, operationCode=%s] synchronously to itself.", serviceName, m_serviceId, operationCode);

                return (WaveMessageStatus.WAVE_MESSAGE_ERROR);
            }

            waveThread = WaveThread.getWaveThreadForServiceId (waveMessage.getServiceCode ());
        }
        else if (effectiveLocationId.equals (new LocationId (1)))
        {
            waveThread = WaveThread.getWaveThreadForMessageHaPeerTransport ();
        }
        else
        {
            waveThread = WaveThread.getWaveThreadForMessageRemoteTransport ();
        }

        if (null == waveThread)
        {
            errorTracePrintf ("WaveObjectManager.sendSynchronously : No Service registered to accept this service Id %s.", waveMessage.getServiceCode ());

            return (WaveMessageStatus.WAVE_MESSAGE_ERROR_NO_SERVICE_TO_ACCEPT_MESSAGE);
        }

        if (false == (waveThread.hasWaveObjectManagers ()))
        {
            errorTracePrintf ("WaveObjectManager.sendSynchronously : Service identified.  But there are no Wave Object Managers registered to process any kind of reqquests.");

            return (WaveMessageStatus.WAVE_MESSAGE_ERROR_NO_OMS_FOR_SERVICE);
        }

        // Set this so the message can be returned. In fact synchronously sent messages can never be returned. This is set so
        // that
        // in case we need to refer it at the receiver end.

        waveMessage.m_senderServiceCode = m_associatedWaveThread.getWaveServiceId ();

        // Set the filed to indicate the message is a synchronously sent message so that when the receiver replies, the
        // framework will
        // not attempt to deliver it back to the original sender. It will simply unlock the sending thread.

        waveMessage.setIsSynchronousMessage (true);

        // The following (WaveMutex creation and locking it) is done by the sending thread:
        // Now Create a WaveMutex and a corresponding WaveCondition. Use the standard Mutex-Condition combination
        // logic to synchronize the sender thread and the receiver thread. The Mutex-Condition logic is very similar
        // to the POSIX equivalents.
        // Store the created WaveMutex and WaveCondition in the WaveMessage. The receiver thread needs to use
        // them when it does a reply on the message after processing it.

        final WaveMutex synchronizingMutex = new WaveMutex ();

        final WaveCondition synchronizingCondition = new WaveCondition (synchronizingMutex);

        waveMessage.setSynchronizingMutex (synchronizingMutex);
        waveMessage.setSynchronizingCondition (synchronizingCondition);

        // Now lock the synchronizing mutex. So that receiver thread cannot acquire it.

        synchronizingMutex.lock ();

        // Store the receiver LocationId.

        waveMessage.m_receiverLocationId = (LocationId.isNotNull (effectiveLocationId)) ? effectiveLocationId : thisLocationId;

        if ((true == waveMessage.getIsALastConfigReplay ()) && ((m_associatedWaveThread.getWaveServiceId ()).equals (WaveFrameworkObjectManager.getWaveServiceId ())))
        {
            // This case is the initial start of the Last Config Replay where the WaveFrameworkPostPersistentBootWorker
            // (WaveFrameworkObjectManager) triggers a last config replay. We do not want to propagate message flags from the
            // input message to output message here. Otherwise, the last configuration replayed intent will have incorrect
            // propagated flags. Only the sendSynchronously () API needs this special handling since triggering the last config
            // replay should only be synchronously replayed.
        }
        else
        {
            if ((null != m_inputMessage) && ((m_associatedWaveThread).equals (waveMessage.getWaveMessageCreatorThreadId ())))
            {
                // Propagate message flags from Incoming Message to Outgoing Message

                waveMessage.setIsConfigurationChanged (m_inputMessage.getIsConfigurationChanged ());
                waveMessage.setIsConfigurationTimeChanged (m_inputMessage.getIsConfigurationTimeChanged ());
                waveMessage.setTransactionCounter (m_inputMessage.getTransactionCounter ());

                if (false == waveMessage.getIsPartitionNameSetByUser ())
                {
                    // Propagate the Partition name from input message

                    waveMessage.setPartitionName (m_inputMessage.getPartitionName ());
                }
                else
                {
                    // pass
                    // Do not overwrite the partition name with partitionName in m_inputMessage.
                }

                waveMessage.setPartitionLocationIdForPropagation (m_inputMessage.getPartitionLocationIdForPropagation ());
                waveMessage.setIsPartitionContextPropagated (m_inputMessage.getIsPartitionContextPropagated ());

                waveMessage.setIsALastConfigReplay (m_inputMessage.getIsALastConfigReplay ());
                waveMessage.addXPathStringsVectorForTimestampUpdate (m_inputMessage.getXPathStringsVectorForTimestampUpdate ());  // if
                                                                                                                                  // receiver
                                                                                                                                  // service
                                                                                                                                  // is
                                                                                                                                  // "management
                                                                                                                                  // interface",
                                                                                                                                  // should
                                                                                                                                  // this
                                                                                                                                  // be
                                                                                                                                  // skipped
                                                                                                                                  // ?

                // This is required because sendToWaveCluster also uses the send method. As send and sendToWaveCluster will be
                // having same m_inputMessage with
                // the flags always set to false. Even if for surrogating message sendToWaveCluster sets the flag, it will be
                // otherwise cleared off here.

                if (false == waveMessage.getIsMessageBeingSurrogatedFlag ())
                {
                    waveMessage.setIsMessageBeingSurrogatedFlag (m_inputMessage.getIsMessageBeingSurrogatedFlag ());
                    waveMessage.setSurrogatingForLocationId (m_inputMessage.getSurrogatingForLocationId ());
                }
            }
        }

        addMessageToMessageHistoryCalledFromSend (waveMessage);

        if ((true == waveMessage.getIsAConfigurationIntent ()) && (true == PersistenceLocalObjectManager.getLiveSyncEnabled ()))
        {
            // Send a configuration intent to the HA peer

            final ResourceId configurationIntentStatus = sendOneWayForStoringConfigurationIntent (waveMessage);

            if (ResourceId.WAVE_MESSAGE_SUCCESS == configurationIntentStatus)
            {
                waveMessage.setIsConfigurationIntentStored (true);
            }
            else
            {
                // Do not penalize the actual configuration. Flag an error for now.

                errorTracePrintf ("WaveObjectManager.sendSynchronously : Failed to store the configuration intent on HA peer for messageId : %s, message operation code : %s, handled by service code : .", waveMessage.getMessageId (), waveMessage.getOperationCode (), waveMessage.getServiceCode ());

                waveMessage.setIsConfigurationIntentStored (false);
            }
        }

        // Now submit the message to the receiver thread. Even if the receiver thread finishes processing
        // the message before we return from the method below, it is perfectly OK. The receiver thread
        // may finish processing but cannot reply to the message as we are holding the synchronizing mutex.

        final WaveMessageStatus status = waveThread.submitMessage (waveMessage);

        if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
        {
            // For some reason the message could not be submitted. We cannot proceed. Release the acquired
            // Synchronizing mutex and return an error to the caller.

            synchronizingMutex.unlock ();

            if (true == waveMessage.getIsConfigurationIntentStored ())
            {
                // Remove configuration intent

                final ResourceId configurationIntentStatus = sendOneWayForRemovingConfigurationIntent (waveMessage.getMessageId ());

                if (ResourceId.WAVE_MESSAGE_SUCCESS != configurationIntentStatus)
                {
                    errorTracePrintf ("WaveObjectManager.sendSynchronously : Failed to remove the configuration intent on HA peer for messageId : %s, message operation code : %s, handled by service code : .", waveMessage.getMessageId (), waveMessage.getOperationCode (), waveMessage.getServiceCode ());
                }
            }

            return (status);
        }

        // Now let us wait for the receiver thread to signal us to resume. The receiver thread could not
        // have called the resume until after we call the following wait method as the receiver thread will
        // be waiting to acquire the synchronizing mutex. It is possible that the receiver can finish processing
        // the message before we return from the above statement but it cannot reply (signal us to continue) until
        // after we call the following statement (wait is invoked).

        synchronizingCondition.awaitUninterruptibly ();

        // Now the receiver thread will be able to acquire the synchronizing mutex (since it will be released
        // as part of the above wait call). So the receiver will be able to do a reply to the message. The receiver
        // does a resume on the synchronizing condition in the reply processing. That causes us to get out of
        // our wait above and also atomically locks the synchronizing mutex again.

        // The following code (unlock) also is executed by the sending thread.

        synchronizingMutex.unlock ();

        // By now we ensured that the receiver actually processed the message and replied to it. This reply is not actually
        // submitting the message back to the original sender.
        // But the receiver thread simply signaled us to continue after finishing processing the message.
        // We can return now.
        // The caller will examine the completion status on the message to obtain the status of completion of processing
        // the message.

        if ((null != m_inputMessage) && (m_associatedWaveThread.equals (waveMessage.getWaveMessageCreatorThreadId ())))
        {
            m_inputMessage.appendNestedSql (waveMessage.getNestedSql ());
        }

        if (true == waveMessage.getIsConfigurationIntentStored ())
        {
            // Remove configuration intent

            final ResourceId configurationIntentStatus = sendOneWayForRemovingConfigurationIntent (waveMessage.getMessageId ());

            if (ResourceId.WAVE_MESSAGE_SUCCESS != configurationIntentStatus)
            {
                errorTracePrintf ("WaveObjectManager.sendSynchronously : Failed to remove the configuration intent on HA peer for messageId : %s, message operation code : %s, handled by service code : .", waveMessage.getMessageId (), waveMessage.getOperationCode (), waveMessage.getServiceCode ());
            }
        }

        return (status);
    }

    private ResourceId sendOneWayForRemovingConfigurationIntent (final UI32 configurationIntentMessageId)
    {
        final WaveThread haPeerTransportWaveThread = WaveThread.getWaveThreadForMessageHaPeerTransport ();

        if (null == haPeerTransportWaveThread)
        {
            errorTracePrintf ("WaveObjectManager.sendOneWayForRemovingConfigurationIntent : Ha Peer Service is not registered to accept configuration intents.");

            return (ResourceId.WAVE_MESSAGE_ERROR_NO_SERVICE_TO_ACCEPT_MESSAGE);
        }

        if (false == (haPeerTransportWaveThread.hasWaveObjectManagers ()))
        {
            errorTracePrintf ("WaveObjectManager.sendOneWayForRemovingConfigurationIntent : Service identified.  But Ha Peer Transport in not registered to process any kind of requests.");

            return (ResourceId.WAVE_MESSAGE_ERROR_NO_OMS_FOR_SERVICE);
        }

        final FrameworkObjectManagerRemoveConfigurationIntentMessage removeConfigurationIntentMessage = new FrameworkObjectManagerRemoveConfigurationIntentMessage ();

        waveAssert (null != removeConfigurationIntentMessage);

        removeConfigurationIntentMessage.setConfigurationIntentMessageId (configurationIntentMessageId);

        removeConfigurationIntentMessage.setIsOneWayMessage (true);
        removeConfigurationIntentMessage.m_senderServiceCode = new WaveServiceId (getServiceId ());
        removeConfigurationIntentMessage.m_receiverLocationId = new LocationId (1);

        addMessageToMessageHistoryCalledFromSend (removeConfigurationIntentMessage);

        final WaveMessageStatus status = haPeerTransportWaveThread.submitMessage (removeConfigurationIntentMessage);

        return (ResourceId.getResourceIdByEffectiveResourceId (status.getEffectiveResourceId ()));
    }

    @NonMessageHandler
    private ResourceId sendOneWayForStoringConfigurationIntent (final WaveMessage waveMessage)
    {
        final WaveThread haPeerTransportWaveThread = WaveThread.getWaveThreadForMessageHaPeerTransport ();
        final UI32 waveMessageId = waveMessage.getMessageId ();
        final StringBuffer serializedConfigurationIntentMessage = new StringBuffer ();

        if (null == haPeerTransportWaveThread)
        {
            errorTracePrintf ("WaveObjectManager.sendOneWayForRemovingConfigurationIntent : Ha Peer Service is not registered to accept configuration intents.");

            return (ResourceId.WAVE_MESSAGE_ERROR_NO_SERVICE_TO_ACCEPT_MESSAGE);
        }

        if (false == (haPeerTransportWaveThread.hasWaveObjectManagers ()))
        {
            errorTracePrintf ("WaveObjectManager.sendOneWayForRemovingConfigurationIntent : Service identified.  But Ha Peer Transport in not registered to process any kind of requests.");

            return (ResourceId.WAVE_MESSAGE_ERROR_NO_OMS_FOR_SERVICE);
        }

        final FrameworkObjectManagerStoreConfigurationIntentMessage storeConfigurationIntentMessage = new FrameworkObjectManagerStoreConfigurationIntentMessage ();

        waveAssert (null != storeConfigurationIntentMessage);

        storeConfigurationIntentMessage.setConfigurationIntentMessageId (waveMessageId);

        waveMessage.serializeTo (serializedConfigurationIntentMessage);

        storeConfigurationIntentMessage.addBuffer (new UI32 (FrameworkObjectManagerConfigurationIntentBufferId.SERIALIZED_CONFIGURATION_INTENT_BUFFER.ordinal ()), (serializedConfigurationIntentMessage.toString ()).getBytes (), false);

        storeConfigurationIntentMessage.setIsOneWayMessage (true);
        storeConfigurationIntentMessage.m_senderServiceCode = new WaveServiceId (getServiceId ());
        storeConfigurationIntentMessage.m_receiverLocationId = new LocationId (1);

        addMessageToMessageHistoryCalledFromSend (storeConfigurationIntentMessage);

        final WaveMessageStatus status = haPeerTransportWaveThread.submitMessage (storeConfigurationIntentMessage);

        return (ResourceId.getResourceIdByEffectiveResourceId (status.getEffectiveResourceId ()));
    }

    @NonMessageHandler
    public void handleWaveMessage (final WaveMessage waveMessage)
    {
        final WaveOperationMapContext waveOperationMapContext = getWaveMessageHandler (waveMessage.getOperationCode (), waveMessage.getServiceCode (), getServiceId ());

        if (null != waveOperationMapContext)
        {
            waveAssert (null == m_inputMessage);
            m_inputMessage = waveMessage;

            addMessageToMessageHistoryCalledFromHandle (waveMessage);

            waveOperationMapContext.executeMessageHandler (waveMessage);
            m_inputMessage = null;
        }
        else
        {
            trace (TraceLevel.TRACE_LEVEL_ERROR, "WaveObjectManager.handleWaveMessage : This type of message is not handled by this Object Manager.");
            WaveAssertUtils.waveAssert ();
            waveMessage.setCompletionStatus (ResourceId.WAVE_MESSAGE_ERROR_OPERATION_NOT_SUPPORTED);
            reply (waveMessage);
        }

    }

    @NonEventHandler
    public void handleWaveEvent (final WaveEvent waveEvent)
    {
        final WaveEventMapContext waveEventMapContext = getWaveEventHandler (waveEvent.getSenderLocationId (), waveEvent.getServiceCode (), waveEvent.getOperationCode ());

        if (null != waveEventMapContext)
        {
            waveAssert (null == m_inputMessage);

            m_inputMessage = null;

            waveEventMapContext.executeEventHandler (waveEvent);

            m_inputMessage = null;
        }
        else
        {
            errorTracePrintf ("WaveObjectManager::handleWaveEvent : This type of event is not handled by this Object Manager.");
            waveAssert (false);

            // waveEvent.setCompletionStatus (WAVE_MESSAGE_ERROR_OPERATION_NOT_SUPPORTED); // No one examines the
            // completionStatus for events.

            // We must reply to the event so that it decrements the reference count for listeners.

            reply (waveEvent);
        }
    }

    private WaveOperationMapContext getWaveMessageHandler (final UI32 operationCode, final WaveServiceId messageHandlerServiceCode, final WaveServiceId thisServiceId)
    {
        WaveOperationMapContext temp = null;

        if (messageHandlerServiceCode.equals (thisServiceId))
        {
            temp = m_operationsMap.get (operationCode);
        }

        // If we could not find the exact match then look for WAVE_OBJECT_MANAGER_ANY_OPCODE opcode.
        // Because, e know that this specific opcode supports any WaveMessage or its derivation.

        if (null == temp)
        {
            temp = m_operationsMap.get (FrameworkOpCodes.WAVE_OBJECT_MANAGER_ANY_OPCODE);
        }

        return (temp);
    }

    private WaveEventMapContext getWaveEventHandler (final LocationId eventSourceLocationId, final WaveServiceId eventSourceServiceId, final UI32 eventOperationCode)
    {
        WaveServiceId effectiveEventSourceServiceId = eventSourceServiceId;

        if (FrameworkOpCodes.WAVE_OBJECT_MANAGER_ANY_EVENT.equals (eventOperationCode))
        {
            effectiveEventSourceServiceId = WaveServiceId.NullServiceId;
        }

        final Map<WaveServiceId, Map<UI32, WaveEventMapContext>> eventsForLocationId = m_eventsMap.get (eventSourceLocationId);

        if (null == eventsForLocationId)
        {
            return (null);
        }

        final Map<UI32, WaveEventMapContext> eventsForLocationIdAndServiceId = eventsForLocationId.get (eventSourceServiceId);

        if (null == eventsForLocationIdAndServiceId)
        {
            return (null);
        }

        final WaveEventMapContext waveEventMapContext = eventsForLocationIdAndServiceId.get (eventOperationCode);

        return (waveEventMapContext);
    }

    private WaveLightPulseMapContext getWaveLightPulseHandler (final String lightPulseName)
    {
        return (m_lightPulsesMap.get (lightPulseName));
    }

    @NonMessageHandler
    private void addMessageToMessageHistoryCalledFromSend (final WaveMessage waveMessage)
    {
        // TODO Auto-generated method stub
    }

    @NonMessageHandler
    private void addMessageToMessageHistoryCalledFromHandle (final WaveMessage waveMessage)
    {
        // TODO Auto-generated method stub
    }

    @Override
    @NonMessageHandler
    public ResourceId reply (final WaveMessage waveMessage)
    {
        // debugTracePrintf ("WaveObjectManager.reply : Replying to a message ...");

        // First check if we need to really deliver the reply.
        // If the message was sent synchronously simply resume the sender thread and return.
        // As part of resuming the sender thread we need to first lock the corresponding synchronizing
        // WaveMutex and then resume the sender thread and then unlock the WaveMutex.
        // Then the sending thread automatically resumes processing.
        // If the message was sent as a one way message, simply destroy it.
        // Do not attempt to deliver it back to the original sender.

        if (true == (waveMessage.getIsSynchronousMessage ()))
        {
            waveAssert (true == (waveMessage.getIsLastReply ()));

            addMessageToMessageHistoryCalledFromReply (waveMessage);

            (waveMessage.getSynchronizingMutex ()).lock ();
            (waveMessage.getSynchronizingCondition ()).signal ();
            (waveMessage.getSynchronizingMutex ()).unlock ();

            m_inputMessage = null;

            return (ResourceId.WAVE_MESSAGE_SUCCESS);
        }
        else if (true == (waveMessage.getIsOneWayMessage ()))
        {
            waveAssert (true == (waveMessage.getIsLastReply ()));

            addMessageToMessageHistoryCalledFromReply (waveMessage);

            m_inputMessage = null;

            return (ResourceId.WAVE_MESSAGE_SUCCESS);
        }
        else
        {
            WaveMessage tempWaveMessage = waveMessage;

            if (false == (waveMessage.getIsLastReply ()))
            {
                tempWaveMessage = waveMessage.cloneThisMessage ();

                tempWaveMessage.setMessageId (waveMessage.getMessageId ());
                tempWaveMessage.setMessageIdAtOriginatingLocation (waveMessage.getMessageIdAtOriginatingLocation ());
                tempWaveMessage.setOriginalMessageId (waveMessage.getOriginalMessageId ());
                tempWaveMessage.setWaveClientMessageId (waveMessage.getWaveClientMessageId ());
                tempWaveMessage.setSenderServiceCode (waveMessage.getSenderServiceCode ());
            }

            WaveThread waveThread = null;

            waveThread = WaveThread.getWaveThreadForServiceId (tempWaveMessage.getSenderServiceCode ());

            if (null == waveThread)
            {
                errorTrace (new String ("WaveObjectManager.reply : No Service registered to accept reply with this service Id ") + tempWaveMessage.getSenderServiceCode () + ". How did we receive this message in the first place.  May be the service went down after submitting the request.  Dropping and destroying the message.");

                if (true == (tempWaveMessage.getIsLastReply ()))
                {
                    m_inputMessage = null;
                }

                return (ResourceId.WAVE_MESSAGE_ERROR_NO_SERVICE_TO_ACCEPT_MESSAGE_RESPONSE);
            }

            tempWaveMessage.setType (WaveMessageType.WAVE_MESSAGE_TYPE_RESPONSE);

            if (true == (tempWaveMessage.getIsLastReply ()))
            {
                m_inputMessage = null;
            }

            addMessageToMessageHistoryCalledFromReply (tempWaveMessage);

            waveThread.submitReplyMessage (tempWaveMessage);

            return (ResourceId.WAVE_MESSAGE_SUCCESS);
        }
    }

    @NonMessageHandler
    private void addMessageToMessageHistoryCalledFromReply (final WaveMessage waveMessage)
    {
        // TODO Auto-generated method stub

    }

    public void addWorker (final WaveWorker waveWorker)
    {
        if (null == waveWorker)
        {
            trace (TraceLevel.TRACE_LEVEL_FATAL, "WaveObjectManager.addWorker : Trying to add a null worker from this manager.  Will not add.");

            WaveAssertUtils.waveAssert ();

            return;
        }

        m_workersMutex.lock ();

        if (m_workers.contains (waveWorker))
        {
            tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "WaveObjectManager.addWorker : Trying to add a duplicate Worker of type : %s", (waveWorker.getClass ()).getName ());
            WaveAssertUtils.waveAssert ();
        }
        else
        {
            m_workers.add (waveWorker);

            final Class<? extends WaveWorker> workerClass = waveWorker.getClass ();

            waveAssert (null != workerClass);

            if (m_workersMapByWorkerClass.containsKey (workerClass))
            {
                final Vector<WaveWorker> waveWorkersForThisWorkerClass = m_workersMapByWorkerClass.get (workerClass);

                waveAssert (null != waveWorkersForThisWorkerClass);

                waveWorkersForThisWorkerClass.add (waveWorker);
            }
            else
            {
                final Vector<WaveWorker> waveWorkersForThisWorkerClass = new Vector<WaveWorker> ();

                waveAssert (null != waveWorkersForThisWorkerClass);

                waveWorkersForThisWorkerClass.add (waveWorker);

                m_workersMapByWorkerClass.put (workerClass, waveWorkersForThisWorkerClass);
            }
        }

        m_workersMutex.unlock ();
    }

    public void removeWorker (final WaveWorker waveWorker)
    {
        if (null == waveWorker)
        {
            trace (TraceLevel.TRACE_LEVEL_FATAL, "WaveObjectManager.removeWorker : Trying to remove a null worker from this manager.  Will not remove.");

            WaveAssertUtils.waveAssert ();

            return;
        }

        m_workersMutex.lock ();

        if (!(m_workers.contains (waveWorker)))
        {
            tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "WaveObjectManager.removeWorker : Trying to remove a non existing Worker of type : %s", (waveWorker.getClass ()).getName ());
            WaveAssertUtils.waveAssert ();
        }
        else
        {
            final Class<? extends WaveWorker> workerClass = waveWorker.getClass ();

            waveAssert (null != workerClass);

            if (m_workersMapByWorkerClass.containsKey (workerClass))
            {
                final Vector<WaveWorker> waveWorkersForThisWorkerClass = m_workersMapByWorkerClass.get (workerClass);

                waveAssert (null != waveWorkersForThisWorkerClass);

                waveWorkersForThisWorkerClass.remove (waveWorker);

                if (0 == (waveWorkersForThisWorkerClass.size ()))
                {
                    m_workersMapByWorkerClass.remove (workerClass);
                }
            }
            else
            {
                waveAssert ();
            }

            m_workers.remove (waveWorker);
        }

        m_workersMutex.unlock ();
    }

    @Override
    protected void holdMessages ()
    {
        m_associatedWaveThread.holdMessages ();
    }

    @Override
    protected void holdHighPriorityMessages ()
    {
        m_associatedWaveThread.holdHighPriorityMessages ();
    }

    @Override
    protected void holdEvents ()
    {
        m_associatedWaveThread.holdEvents ();
    }

    @Override
    public void holdAll ()
    {
        m_associatedWaveThread.holdAll ();
    }

    @Override
    protected void unholdMessages ()
    {
        m_associatedWaveThread.unholdMessages ();
    }

    @Override
    protected void unholdHighPriorityMessages ()
    {
        m_associatedWaveThread.unholdHighPriorityMessages ();
    }

    @Override
    protected void unholdEvents ()
    {
        m_associatedWaveThread.unholdEvents ();
    }

    @Override
    public void unholdAll ()
    {
        m_associatedWaveThread.unholdAll ();
    }

    @Override
    public void updateTimeConsumedInThisThread (final UI32 operationCode, final int currentStep, final long lastLapDuration)
    {
        if (m_nanoSecondsForMessageHandlerSequencerSteps.containsKey (new UI32 (operationCode)))
        {
            final Map<UI32, UI64> sequencerStepMapForOperationCode = m_nanoSecondsForMessageHandlerSequencerSteps.get (new UI32 (operationCode));

            if (sequencerStepMapForOperationCode.containsKey (new UI32 (currentStep)))
            {
                final UI64 nanoSecondsForOperationCodeStep = sequencerStepMapForOperationCode.get (new UI32 (currentStep));

                WaveAssertUtils.waveAssert (null != nanoSecondsForOperationCodeStep);

                nanoSecondsForOperationCodeStep.increment (lastLapDuration);
            }
            else
            {
                sequencerStepMapForOperationCode.put (new UI32 (currentStep), new UI64 (lastLapDuration));
            }
        }
        else
        {
            final Map<UI32, UI64> sequencerStepMapForOperationCode = new HashMap<UI32, UI64> ();

            sequencerStepMapForOperationCode.put (new UI32 (currentStep), new UI64 (lastLapDuration));

            m_nanoSecondsForMessageHandlerSequencerSteps.put (new UI32 (operationCode), sequencerStepMapForOperationCode);
        }
    }

    @Override
    public void updateRealTimeConsumedInThisThread (final UI32 operationCode, final int currentStep, final long lastLapDuration)
    {
        if (m_realNanoSecondsForMessageHandlerSequencerSteps.containsKey (new UI32 (operationCode)))
        {
            final Map<UI32, UI64> sequencerStepMapForOperationCode = m_realNanoSecondsForMessageHandlerSequencerSteps.get (new UI32 (operationCode));

            if (sequencerStepMapForOperationCode.containsKey (new UI32 (currentStep)))
            {
                final UI64 nanoSecondsForOperationCodeStep = sequencerStepMapForOperationCode.get (new UI32 (currentStep));

                WaveAssertUtils.waveAssert (null != nanoSecondsForOperationCodeStep);

                nanoSecondsForOperationCodeStep.increment (lastLapDuration);
            }
            else
            {
                sequencerStepMapForOperationCode.put (new UI32 (currentStep), new UI64 (lastLapDuration));
            }
        }
        else
        {
            final Map<UI32, UI64> sequencerStepMapForOperationCode = new HashMap<UI32, UI64> ();

            sequencerStepMapForOperationCode.put (new UI32 (currentStep), new UI64 (lastLapDuration));

            m_realNanoSecondsForMessageHandlerSequencerSteps.put (new UI32 (operationCode), sequencerStepMapForOperationCode);
        }
    }

    public String getName ()
    {
        return (m_name);
    }

    @Override
    protected ResourceId commitTransaction ()
    {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    protected void rollbackTransaction ()
    {
        // TODO Auto-generated method stub
    }

    public WaveMessage createMessageInstanceWrapper (final UI32 operationCode)
    {
        WaveMessage waveMessage = null;

        m_createMessageInstanceWrapperMutex.lock ();

        if (m_ownersForCreatingMessageInstances.containsKey (operationCode))
        {
            final WaveElement waveElement = m_ownersForCreatingMessageInstances.get (operationCode);

            if (null != waveElement)
            {
                waveMessage = waveElement.createMessageInstance (operationCode);
            }
            else
            {
                errorTracePrintf ("WaveObjectManager.createMessageInstanceWrapper : A null owner has been registered for operation code %d.", operationCode);
            }

            if (null == waveMessage)
            {
                errorTracePrintf ("WaveObjectManager.createMessageInstanceWrapper : Owner for %d has not implemented dynamically creating the instance of this Message Type.  Implement this functionality to proceed further.", operationCode);
            }
        }
        else
        {
            final WaveElement waveElement = m_ownersForCreatingMessageInstances.get (FrameworkOpCodes.WAVE_OBJECT_MANAGER_ANY_OPCODE);

            if (null != waveElement)
            {
                waveMessage = waveElement.createMessageInstance (operationCode);
            }
            else
            {
                errorTracePrintf ("WaveObjectManager.createMessageInstanceWrapper : A null owner has been registered for operation code WAVE_OBJECT_MANAGER_ANY_OPCODE.");
            }

            if (null == waveMessage)
            {
                errorTracePrintf ("WaveObjectManager.createMessageInstanceWrapper : Owner for %d via WAVE_OBJECT_MANAGER_ANY_OPCODE has not implemented dynamically creating the instance of this Message Type.  Implement this functionality to proceed further.", operationCode);
            }
        }

        m_createMessageInstanceWrapperMutex.unlock ();

        return (waveMessage);
    }

    @Override
    public WaveMessage createMessageInstance (final UI32 operationCode)
    {
        final Class<?> messageClass = m_operationsIdToClassMap.get (operationCode);

        if (null != messageClass)
        {
            Object object = null;

            try
            {
                object = messageClass.newInstance ();
            }
            catch (final Exception exception)
            {
                WaveTraceUtils.fatalTracePrintf ("WaveObjectManager.createMessageInstance : %s message class could not be instantiated.  Details : %s", messageClass.getName (), exception.toString ());

                WaveAssertUtils.waveAssert ();
            }

            final WaveMessage waveMessage = (WaveMessage) object;

            WaveAssertUtils.waveAssert (null != waveMessage);

            return (waveMessage);
        }
        else
        {
            return (null);
        }
    }

    public Vector<WaveWorker> getWorkers ()
    {
        return (m_workers);
    }

    public void initialize (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("WaveObjectManager.initialize : Entering for %s ...", (getClass ()).getName ());

        waveAsynchronousContextForBootPhases.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        waveAsynchronousContextForBootPhases.callback ();
    }

    public void enable (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("WaveObjectManager.enable : Entering for %s ...", (getClass ()).getName ());

        waveAsynchronousContextForBootPhases.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        waveAsynchronousContextForBootPhases.callback ();
    }

    public void install (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("WaveObjectManager.install : Entering for %s ...", (getClass ()).getName ());

        waveAsynchronousContextForBootPhases.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        waveAsynchronousContextForBootPhases.callback ();
    }

    public void boot (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("WaveObjectManager.boot : Entering for %s ...", (getClass ()).getName ());

        waveAsynchronousContextForBootPhases.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        waveAsynchronousContextForBootPhases.callback ();
    }

    public void listenForEvents (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("WaveObjectManager.listenForEvents : Entering for %s ...", (getClass ()).getName ());

        waveAsynchronousContextForBootPhases.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        waveAsynchronousContextForBootPhases.callback ();
    }

    public static WaveObjectManager getInstanceByClassNameIfSingleton (final String objectManagerClassName, final Vector<Class<? extends Annotation>> exclusingAnnotationClasses)
    {
        final boolean isADerivativeOfWaveObjectManager = WaveJavaSourceRepository.isAderivativeOfWaveObjectManager (objectManagerClassName);

        if (!isADerivativeOfWaveObjectManager)
        {
            return (null);
        }

        Class<?> classForObjectManager = null;

        try
        {
            classForObjectManager = Class.forName (objectManagerClassName);
        }
        catch (final ClassNotFoundException e)
        {
            WaveTraceUtils.errorTracePrintf ("WaveObjectManager.getInstanceByClassNameIfSingleton : Could not get Java Class information for %s.  Details : %s", objectManagerClassName, e.toString ());
        }

        if (null == classForObjectManager)
        {
            return (null);
        }

        // if any of the excluding annotations are found on this class, then return null.

        for (final Class<? extends Annotation> excludingAnnotationClass : exclusingAnnotationClasses)
        {
            WaveAssertUtils.waveAssert (null != excludingAnnotationClass);

            final Annotation annotation = classForObjectManager.getAnnotation (excludingAnnotationClass);

            if (null != annotation)
            {
                return (null);
            }
        }

        Method getInstanceMethod = null;

        try
        {
            getInstanceMethod = classForObjectManager.getMethod ("getInstance");
        }
        catch (NoSuchMethodException | SecurityException e)
        {
            WaveTraceUtils.errorTracePrintf ("WaveObjectManager.getInstanceByClassNameIfSingleton : Could not get getInstance method for %s.  Details : %s", objectManagerClassName, e.toString ());
        }

        if (null == getInstanceMethod)
        {
            return (null);
        }

        Object objectForWaveObjectManager = null;

        try
        {
            objectForWaveObjectManager = getInstanceMethod.invoke (null);
        }
        catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException | NullPointerException e)
        {
            WaveTraceUtils.errorTracePrintf ("WaveObjectManager.getInstanceByClassNameIfSingleton : Could not invoke getInstance method for %s.  Details : %s", objectManagerClassName, e.toString ());

            final Throwable cause = e.getCause ();

            if (null != cause)
            {
                WaveTraceUtils.errorTracePrintf ("WaveObjectManager.getInstanceByClassNameIfSingleton : Cause : %s,  Stack : \r\n%s", cause.toString (), WaveStackUtils.getStackString (cause));
            }
        }

        if (null == objectForWaveObjectManager)
        {
            return (null);
        }

        final WaveObjectManager waveObjectManager = (WaveObjectManager) objectForWaveObjectManager;

        WaveAssertUtils.waveAssert (null != waveObjectManager);

        return (waveObjectManager);
    }

    public static WaveObjectManagerPriority getObjectManagerPriorityForObjectManager (final String objectManagerClassName)
    {
        final boolean isADerivativeOfWaveObjectManager = WaveJavaSourceRepository.isAderivativeOfWaveObjectManager (objectManagerClassName);

        if (!isADerivativeOfWaveObjectManager)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveObjectManager.getObjectManagerPriorityForObjectManager : %s is not a derivative of Wave Object Manager.", objectManagerClassName);

            WaveAssertUtils.waveAssert ();

            return (WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_DEFAULT);
        }

        Class<?> classForObjectManager = null;

        try
        {
            classForObjectManager = Class.forName (objectManagerClassName);
        }
        catch (final ClassNotFoundException e)
        {
            WaveTraceUtils.errorTracePrintf ("WaveObjectManager.getObjectManagerPriorityForObjectManager : Could not get Java Class information for %s.  Details : %s", objectManagerClassName, e.toString ());
        }

        if (null == classForObjectManager)
        {
            return (WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_DEFAULT);
        }

        final ObjectManagerPriority objectManagerPriority = classForObjectManager.getAnnotation (ObjectManagerPriority.class);

        if (null != objectManagerPriority)
        {
            return (objectManagerPriority.value ());
        }
        else
        {
            return (WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_DEFAULT);
        }
    }

    public static boolean isAnnotatedWithNonOM (final String objectManagerClassName)
    {
        final boolean isADerivativeOfWaveObjectManager = WaveJavaSourceRepository.isAderivativeOfWaveObjectManager (objectManagerClassName);

        if (!isADerivativeOfWaveObjectManager)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveObjectManager.isAnnotatedWithNonOM : %s is not a derivative of Wave Object Manager.", objectManagerClassName);

            WaveAssertUtils.waveAssert ();

            return (false);
        }

        Class<?> classForObjectManager = null;

        try
        {
            classForObjectManager = Class.forName (objectManagerClassName);
        }
        catch (final ClassNotFoundException e)
        {
            WaveTraceUtils.errorTracePrintf ("WaveObjectManager.isAnnotatedWithNonOM : Could not get Java Class information for %s.  Details : %s", objectManagerClassName, e.toString ());
        }

        if (null == classForObjectManager)
        {
            return (false);
        }

        final NonOM nonOm = classForObjectManager.getAnnotation (NonOM.class);

        if (null != nonOm)
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }

    public WaveWorker getAWaveWorkerByWorkerClass (final Class<? extends WaveWorker> workerClass)
    {
        waveAssert (null != workerClass);

        WaveWorker waveWorker = null;

        m_workersMutex.lock ();

        final Vector<WaveWorker> workersForThisWorkerClass = m_workersMapByWorkerClass.get (workerClass);

        if (null != workersForThisWorkerClass)
        {
            if (0 != (workersForThisWorkerClass.size ()))
            {
                waveWorker = workersForThisWorkerClass.get (0);

                waveAssert (null != waveWorker);
            }
        }

        m_workersMutex.unlock ();

        return (waveWorker);
    }

    public void addServiceToEnabledServicesList (final WaveServiceId waveServiceId)
    {
        s_enabledServicesMutex.lock ();
        s_enabledServices.put (waveServiceId, waveServiceId);
        s_enabledServicesMutex.unlock ();
    }

    public void removeServiceFromEnabledServicesList (final WaveServiceId waveServiceId)
    {
        s_enabledServicesMutex.lock ();

        if (s_enabledServices.containsKey (waveServiceId))
        {
            s_enabledServices.remove (waveServiceId);
        }

        s_enabledServicesMutex.unlock ();
    }

    public void getListOfEnabledServices (final Vector<WaveServiceId> enabledServices)
    {
        s_enabledServicesMutex.lock ();

        enabledServices.addAll (s_enabledServices.keySet ());

        s_enabledServicesMutex.unlock ();
    }

    public static boolean isServiceEnabled (final WaveServiceId waveServiceId)
    {
        s_enabledServicesMutex.lock ();

        final boolean serviceEnabled = s_enabledServices.containsKey (waveServiceId);

        s_enabledServicesMutex.unlock ();

        return (serviceEnabled);
    }

    protected void addResponseMap (final UI32 waveMessageId, final WaveMessageResponseContext waveMessageResponseContext)
    {
        m_responsesMapMutex.lock ();

        m_responsesMap.put (waveMessageId, waveMessageResponseContext);

        m_responsesMapMutex.unlock ();
    }

    protected WaveMessageResponseContext getResponseContext (final UI32 waveMessageId)
    {
        WaveMessageResponseContext waveMessageResponseContext = null;

        m_responsesMapMutex.lock ();

        waveMessageResponseContext = m_responsesMap.get (waveMessageId);

        m_responsesMapMutex.unlock ();

        return (waveMessageResponseContext);
    }

    public boolean isAKnownMessage (final UI32 waveMessageId)
    {
        // Please refer to the comment in the send method just above the corresponding locking
        // method. The corresponding lock line looks just like the line below

        m_sendReplyMutexForResponseMap.lock ();

        final WaveMessageResponseContext waveMessageResponseContext = getResponseContext (waveMessageId);
        boolean isKnown = false;

        if (null != waveMessageResponseContext)
        {
            isKnown = true;
        }

        m_sendReplyMutexForResponseMap.unlock ();

        return (isKnown);
    }

    protected WaveMessageResponseContext removeResponseMap (final UI32 waveMessageId)
    {
        WaveMessageResponseContext waveMessageResponseContext = null;

        m_responsesMapMutex.lock ();

        waveMessageResponseContext = m_responsesMap.remove (waveMessageId);

        m_responsesMapMutex.unlock ();

        return (waveMessageResponseContext);
    }

    @Override
    protected WaveMessageStatus send (final WaveMessage waveMessage, final WaveMessageResponseHandler waveMessageCallback, final Object waveMessageContext)
    {
        return (send (waveMessage, waveMessageCallback, waveMessageContext, 0, LocationId.NullLocationId, this));
    }

    @Override
    protected WaveMessageStatus send (final WaveMessage waveMessage, final WaveMessageResponseHandler waveMessageCallback, final Object waveMessageContext, final long timeOutInMilliSeconds, final LocationId locationId, final WaveElement waveMessageSender)
    {
        if (null == waveMessage)
        {
            trace (TraceLevel.TRACE_LEVEL_ERROR, "WaveObjectManager.send : Trying to send a message with null message.");

            return (WaveMessageStatus.WAVE_MESSAGE_ERROR_NULL_MESSAGE);
        }

        if ((null == waveMessage) || ((null) == waveMessageCallback))
        {
            trace (TraceLevel.TRACE_LEVEL_ERROR, "WaveObjectManager.send : Trying to send a message with null callback.  If you do not want to register a callback send it as a one way message.");

            return (WaveMessageStatus.WAVE_MESSAGE_ERROR_NULL_CALLBACK);
        }

        WaveThread waveThread = null;

        final LocationId thisLocationId = FrameworkToolKit.getThisLocationId ();
        LocationId effectiveLocationId = locationId;

        // FIXME : declare a NullLocationId instead of using 0

        if (LocationId.NullLocationId.equals (effectiveLocationId))
        {
            if (true != (FrameworkToolKit.isALocalService (waveMessage.getServiceCode ())))
            {
                effectiveLocationId = FrameworkToolKit.getClusterPrimaryLocationId ();
                final LocationId myLocationId = FrameworkToolKit.getPhysicalLocationId ();
                if (effectiveLocationId == myLocationId)
                {
                    effectiveLocationId = new LocationId (0);
                }
            }
        }

        if ((!(LocationId.NullLocationId.equals (effectiveLocationId))) && (!(effectiveLocationId.equals (thisLocationId))) && (false == FrameworkToolKit.isAKnownLocation (effectiveLocationId)) && (!(effectiveLocationId.equals (LocationId.HaPeerLocationId))))

        {
            errorTracePrintf ("WaveObjectManager.send: Location is invalid: Loc : %s", locationId.toString ());

            return (WaveMessageStatus.WAVE_MESSAGE_ERROR);
        }

        if ((LocationId.NullLocationId.equals (effectiveLocationId)) || (thisLocationId.equals (effectiveLocationId)))
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
            errorTracePrintf ("WaveObjectManager.send : No Service registered to accept this service Id %s.", (waveMessage.getServiceCode ()).toString ());

            return (WaveMessageStatus.WAVE_MESSAGE_ERROR_NO_SERVICE_TO_ACCEPT_MESSAGE);
        }

        if (false == (waveThread.hasWaveObjectManagers ()))
        {
            trace (TraceLevel.TRACE_LEVEL_ERROR, "WaveObjectManager.send : Service identified.  But there are no Wave Object Managers registered to process any kind of requests.");

            return (WaveMessageStatus.WAVE_MESSAGE_ERROR_NO_OMS_FOR_SERVICE);
        }

        // Set this so that the message can be returned after getting processed.

        waveMessage.m_senderServiceCode = getServiceId ();

        // Store the receiver LocationId.

        final UI32 waveMessageId = waveMessage.getMessageId ();

        waveMessage.m_receiverLocationId = (!(effectiveLocationId.equals (LocationId.NullLocationId))) ? effectiveLocationId : thisLocationId;

        if (null != (getResponseContext (waveMessageId)))
        {
            errorTracePrintf ("WaveObjectManager.send : This message (with id : %s was already registered.", waveMessageId.toString ());
            return (WaveMessageStatus.WAVE_MESSAGE_ERROR_DUPLICATE_MESSAGE_SEND);
        }

        addMessageToMessageHistoryCalledFromSend (waveMessage);

        // The following lock is used so that the response for the submitted message does not arrive before we finish adding the
        // messages
        // Response context. If the message response arrive before we add the response context, we will fail the response
        // delivery.
        // This does not happen in normal cases since the same thread is submitting the messages and the same thread picks up
        // the response
        // for processing. But in some cases, Multiple threads use the send of the same object manager's send. In this case the
        // threads
        // are typically different the the object manager's thread. But the reply is received on the object manager's thread. If
        // there is
        // no co-ordination between the send and reply threads for the same message, it is possible that we can receive a
        // response before
        // the message response context has been added to the response map. It is very rare but we have already seen it happen
        // under heavy
        // stress on the system.

        m_sendReplyMutexForResponseMap.lock ();

        if ((null != m_inputMessage) && (m_associatedWaveThread.equals (waveMessage.getWaveMessageCreatorThreadId ())))
        {
            // Propagate message flags from Incoming Message to Outgoing Message

            waveMessage.setIsConfigurationChanged (m_inputMessage.getIsConfigurationChanged ());
            waveMessage.setIsConfigurationTimeChanged (m_inputMessage.getIsConfigurationTimeChanged ());
            waveMessage.setTransactionCounter (m_inputMessage.getTransactionCounter ());

            if (false == waveMessage.getIsPartitionNameSetByUser ())
            {
                waveMessage.setPartitionName (m_inputMessage.getPartitionName ()); // Propagate the Partition name from Input
                                                                                   // Message.
            }
            else
            {
                // pass
                // Do not overwrite the partition name with partitionName in m_inputMessage.
            }

            waveMessage.setPartitionLocationIdForPropagation (m_inputMessage.getPartitionLocationIdForPropagation ());
            waveMessage.setIsPartitionContextPropagated (m_inputMessage.getIsPartitionContextPropagated ());

            waveMessage.setIsALastConfigReplay (m_inputMessage.getIsALastConfigReplay ());
            waveMessage.addXPathStringsVectorForTimestampUpdate (m_inputMessage.getXPathStringsVectorForTimestampUpdate ());  // if
                                                                                                                              // receiver
                                                                                                                              // service
                                                                                                                              // is
                                                                                                                              // "management
                                                                                                                              // interface",
                                                                                                                              // should
                                                                                                                              // this
                                                                                                                              // be
                                                                                                                              // skipped
                                                                                                                              // ?

            // This is required because sendToWaveCluster also uses the send method. As send and sendToWaveCluster will be
            // having same m_inputMessage with
            // the flags always set to false. Even if for surrogating message sendToWaveCluster sets the flag, it will be
            // otherwise cleared off here.

            if (false == waveMessage.getIsMessageBeingSurrogatedFlag ())
            {
                waveMessage.setIsMessageBeingSurrogatedFlag (m_inputMessage.getIsMessageBeingSurrogatedFlag ());
                waveMessage.setSurrogatingForLocationId (m_inputMessage.getSurrogatingForLocationId ());
            }
        }

        if ((true == waveMessage.getIsAConfigurationIntent ()) && (true == PersistenceLocalObjectManager.getLiveSyncEnabled ()))
        {
            // Send a configuration intent to the HA peer

            final ResourceId configurationIntentStatus = sendOneWayForStoringConfigurationIntent (waveMessage);

            if (ResourceId.WAVE_MESSAGE_SUCCESS == configurationIntentStatus)
            {
                waveMessage.setIsConfigurationIntentStored (true);
            }
            else
            {
                // Do not penalize the actual configuration. Flag an error for now.

                errorTracePrintf ("WaveObjectManager.send : Failed to store the configuration intent on HA peer for messageId : %s, handled by service code : %s.", (waveMessage.getMessageId ()).toString (), (waveMessage.getServiceCode ()).toString ());

                waveMessage.setIsConfigurationIntentStored (false);
            }
        }

        WaveMessageStatus status = waveThread.submitMessage (waveMessage);

        if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS == status)
        {
            // Now store the details related to callback so that we can call the appropriate callback when the reply to this
            // message arrives.

            final WaveMessageResponseContext waveMessageResponseContext = new WaveMessageResponseContext (waveMessage, waveMessageSender != null ? waveMessageSender : this, waveMessageCallback, waveMessageContext);

            waveAssert (null != waveMessageResponseContext);

            if (m_associatedWaveThread.equals (waveMessage.getWaveMessageCreatorThreadId ()))
            {
                waveMessageResponseContext.setInputMessageInResponseContext (m_inputMessage);
            }

            if (null == waveMessageResponseContext)
            {
                status = WaveMessageStatus.WAVE_MESSAGE_ERROR_MEMORY_EXHAUSTED;
            }
            else
            {
                addResponseMap (waveMessageId, waveMessageResponseContext);
            }

            // If user requested for a message timeout then start the timer.

            if (0 != timeOutInMilliSeconds)
            {
                final TimerHandle timerHandle = new TimerHandle ();

                final ResourceId timeStatus = startTimer (timerHandle, timeOutInMilliSeconds, new WaveTimerExpirationHandler ("sendTimerExpiredCallback"), waveMessageId);

                if (ResourceId.FRAMEWORK_SUCCESS != timeStatus)
                {
                    fatalTracePrintf ("WaveObjectManager.send : Could not arm a timer to enforce send timeout.  Status : %s", FrameworkToolKit.localize (timeStatus));

                    waveAssert (false);
                }
                else
                {
                    waveMessageResponseContext.setIsTimerStarted (true);
                    waveMessageResponseContext.setTimerHandle (timerHandle);
                }
            }
        }

        m_sendReplyMutexForResponseMap.unlock ();

        return (status);
    }

    public void handleWaveMessageResponse (final FrameworkStatus frameworkStatus, final WaveMessage waveMessage)
    {
        handleWaveMessageResponse (frameworkStatus, waveMessage, false);
    }

    public void handleWaveMessageResponse (final FrameworkStatus frameworkStatus, final WaveMessage waveMessage, final boolean isMessageRecalled)
    {
        final UI32 waveMessageId = waveMessage.getMessageId ();
        final boolean isLastReply = waveMessage.getIsLastReply ();
        WaveMessageResponseContext waveMessageResponseContext = null;

        addMessageToMessageHistoryCalledFromHandle (waveMessage);

        // if (((FrameworkStatus.FRAMEWORK_TIME_OUT != frameworkStatus) && (true == isLastReply)) ||
        // ((FrameworkStatus.FRAMEWORK_TIME_OUT ==
        // frameworkStatus) && (true == isMessageRecalled)))
        if (true == isLastReply)
        {
            waveMessageResponseContext = removeResponseMap (waveMessageId);
        }
        else
        {
            waveMessageResponseContext = getResponseContext (waveMessageId);
        }

        if (null != waveMessageResponseContext)
        {
            if (true == (waveMessageResponseContext.getIsTimerStarted ()))
            {
                // FIXME
                // deleteTimer (waveMessageResponseContext.getTimerHandle ());
            }

            waveAssert (null == m_inputMessage);

            if (false == (waveMessageResponseContext.getIsMessageTimedOut ()))
            {
                m_inputMessage = waveMessageResponseContext.getInputMessageInResponseContext ();
            }

            if (null != m_inputMessage)
            {
                m_inputMessage.appendNestedSql (waveMessage.getNestedSql ());
            }

            if ((true == isLastReply) && (true == waveMessage.getIsConfigurationIntentStored ()))
            {
                // Remove configuration intent

                final ResourceId configurationIntentStatus = sendOneWayForRemovingConfigurationIntent (waveMessage.getMessageId ());

                if (ResourceId.WAVE_MESSAGE_SUCCESS != configurationIntentStatus)
                {
                    errorTracePrintf ("WaveObjectManager.handleWaveMessageResponse : Failed to remove the configuration intent from HA peer for messageId : %s, handled by service code : %s.", (waveMessage.getMessageId ()).toString (), (waveMessage.getServiceCode ()).toString ());
                }
            }

            waveMessageResponseContext.executeResponseCallback (frameworkStatus, waveMessage, isMessageRecalled);

            m_inputMessage = null;
        }
        else
        {
            waveAssert ();
        }
    }

    private void handleWaveMessageResponseWhenTimeOutExpired (final FrameworkStatus frameworkStatus, final UI32 waveMessageId)
    {
        final WaveMessageResponseContext waveMessageResponseContext = getResponseContext (waveMessageId);

        if (null != waveMessageResponseContext)
        {
            waveMessageResponseContext.setIsTimerStarted (false);
            waveMessageResponseContext.setTimerHandle (TimerHandle.NullTimerHandle);

            final WaveMessage waveMessage = waveMessageResponseContext.getWaveMessage ();
            final WaveMessageStatus status = recallButDoNotDeleteResponseMap (waveMessage);
            final WaveMessage tempInputMessage = m_inputMessage;

            m_inputMessage = null;

            if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS == status)
            {
                waveMessage.setCompletionStatus (ResourceId.WAVE_MESSAGE_ERROR_RECALLED_DUE_TO_TIME_OUT);
                handleWaveMessageResponse (frameworkStatus, waveMessage, true); // Indicate that message has been recalled
            }
            else
            {
                waveMessageResponseContext.executeResponseCallback (frameworkStatus);
            }

            m_inputMessage = tempInputMessage;
        }
        else
        {
            // Nothing to be done. The response must have arrived earlier.
        }
    }

    @NonMessageHandler
    protected WaveMessageStatus recallButDoNotDeleteResponseMap (final WaveMessage waveMessage)
    {
        if (null == waveMessage)
        {
            errorTracePrintf ("WaveObjectManager.recall : Trying to recall a null message.");
            return (WaveMessageStatus.WAVE_MESSAGE_ERROR_NULL_MESSAGE);
        }

        WaveThread waveThread = null;
        final LocationId thisLocationId = FrameworkToolKit.getThisLocationId ();
        final LocationId locationId = waveMessage.getReceiverLocationId ();
        LocationId effectiveLocationId = locationId;

        if (LocationId.NullLocationId.equals (effectiveLocationId))
        {
            if (true != (FrameworkToolKit.isALocalService (waveMessage.getServiceCode ())))
            {
                effectiveLocationId = FrameworkToolKit.getClusterPrimaryLocationId ();
            }
        }

        if ((LocationId.NullLocationId.equals (effectiveLocationId)) || (thisLocationId.equals (effectiveLocationId)))
        {
            waveThread = WaveThread.getWaveThreadForServiceId (waveMessage.getServiceCode ());
        }
        else
        {
            waveThread = WaveThread.getWaveThreadForMessageRemoteTransport ();
        }

        if (null == waveThread)
        {
            errorTracePrintf ("WaveObjectManager.recall : No Service registered to accept this service Id %s.", (waveMessage.getServiceCode ()).toString ());

            return (WaveMessageStatus.WAVE_MESSAGE_ERROR_NO_SERVICE_TO_ACCEPT_MESSAGE);
        }

        return (waveThread.recallMessage (waveMessage));
    }

    @NonMessageHandler
    protected WaveMessageStatus recall (final WaveMessage waveMessage)
    {
        final WaveMessageStatus recallStatus = recallButDoNotDeleteResponseMap (waveMessage);

        if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS == recallStatus)
        {
            WaveMessageResponseContext waveMessageResponseContext = null;

            waveMessageResponseContext = removeResponseMap (waveMessage.getMessageId ());

            waveAssert (null != waveMessageResponseContext);
        }

        return (recallStatus);
    }

    @Override
    protected ResourceId startTimer (final TimerHandle timerHandle, final TimeValue startInterval, final WaveTimerExpirationHandler waveTimerExpirationCallback, final Object waveTimerExpirationContext, final WaveElement waveTimerSender)
    {
        return (startTimer (timerHandle, startInterval, new TimeValue (0, 0), waveTimerExpirationCallback, waveTimerExpirationContext, waveTimerSender));
    }

    @Override
    protected ResourceId startTimer (final TimerHandle timerHandle, final TimeValue startInterval, final WaveTimerExpirationHandler waveTimerExpirationCallback, final Object waveTimerExpirationContext)
    {
        return (startTimer (timerHandle, startInterval, waveTimerExpirationCallback, waveTimerExpirationContext, this));
    }

    @Override
    protected ResourceId startTimer (final TimerHandle timerHandle, final TimeValue startInterval, final TimeValue periodicInterval, final WaveTimerExpirationHandler waveTimerExpirationCallback, final Object waveTimerExpirationContext)
    {
        return (startTimer (timerHandle, startInterval, periodicInterval, waveTimerExpirationCallback, waveTimerExpirationContext, this));
    }

    @Override
    protected ResourceId startTimer (final TimerHandle timerHandle, final TimeValue startInterval, final TimeValue periodicInterval, final WaveTimerExpirationHandler waveTimerExpirationCallback, final Object waveTimerExpirationContext, final WaveElement waveTimerSender)
    {
        final TimeValue currentTimeValue = new TimeValue ();

        currentTimeValue.resetToCurrent ();

        if (!(currentTimeValue.isValid ()))
        {
            errorTracePrintf ("WaveObjectManager.startTimer : error getting current time.");

            return (ResourceId.FRAMEWORK_TIMER_CAN_NOT_START);
        }

        if (!(startInterval.isNonImmediate ()))
        {
            return (ResourceId.FRAMEWORK_TIMER_INVALID_START_INTERVAL);
        }

        if (!(periodicInterval.isValid ()))
        {
            return (ResourceId.FRAMEWORK_TIMER_INVALID_PERIODIC_INTERVAL);
        }

        if (null == waveTimerExpirationCallback)
        {
            return (ResourceId.FRAMEWORK_TIMER_INVALID_CALLBACK);
        }

        final TimerObjectManagerAddTimerMessage startTimerMessage = new TimerObjectManagerAddTimerMessage (startInterval, periodicInterval, currentTimeValue, waveTimerExpirationCallback, waveTimerExpirationContext, (null == waveTimerSender) ? this : waveTimerSender);

        waveAssert (null != startTimerMessage);

        final WaveMessageStatus status = sendSynchronously (startTimerMessage);

        if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
        {
            errorTracePrintf ("WaveObjectManager.startTimer : TimerObjectManagerAddTimerMessage failed.  Status : %s", FrameworkToolKit.localize (status));

            return (ResourceId.FRAMEWORK_TIMER_CAN_NOT_START);
        }

        if (ResourceId.TIMER_SUCCESS == (startTimerMessage.getCompletionStatus ()))
        {
            timerHandle.setHandle (startTimerMessage.getTimerId ());

            return (ResourceId.FRAMEWORK_SUCCESS);
        }
        else
        {
            timerHandle.setValue (0);

            return (ResourceId.FRAMEWORK_TIMER_CAN_NOT_START);
        }
    }

    @Override
    protected ResourceId startTimer (final TimerHandle timerHandle, final long startIntervalMilliSeconds, final long periodicIntervalMilliSeconds, final WaveTimerExpirationHandler waveTimerExpirationCallback, final Object waveTimerExpirationContext, final WaveElement waveTimerSender)
    {
        final TimeValue startInterval = new TimeValue (startIntervalMilliSeconds, 0);
        final TimeValue periodicInterval = new TimeValue (periodicIntervalMilliSeconds, 0);

        return (startTimer (timerHandle, startInterval, periodicInterval, waveTimerExpirationCallback, waveTimerExpirationContext, waveTimerSender));
    }

    @Override
    protected ResourceId startTimer (final TimerHandle timerHandle, final long startIntervalMilliSeconds, final long periodicIntervalMilliSeconds, final WaveTimerExpirationHandler waveTimerExpirationCallback, final Object waveTimerExpirationContext)
    {
        return (startTimer (timerHandle, startIntervalMilliSeconds, periodicIntervalMilliSeconds, waveTimerExpirationCallback, waveTimerExpirationContext, this));
    }

    @Override
    protected ResourceId startTimer (final TimerHandle timerHandle, final long startIntervalMilliSeconds, final WaveTimerExpirationHandler waveTimerExpirationCallback, final Object waveTimerExpirationContext, final WaveElement waveTimerSender)
    {
        return (startTimer (timerHandle, startIntervalMilliSeconds, 0, waveTimerExpirationCallback, waveTimerExpirationContext, waveTimerSender));
    }

    @Override
    protected ResourceId startTimer (final TimerHandle timerHandle, final long startIntervalMilliSeconds, final WaveTimerExpirationHandler waveTimerExpirationCallback, final Object waveTimerExpirationContext)
    {
        return (startTimer (timerHandle, startIntervalMilliSeconds, waveTimerExpirationCallback, waveTimerExpirationContext, this));
    }

    @Override
    protected ResourceId deleteTimer (final TimerHandle timerHandle)
    {
        ResourceId returnCode;

        final TimerObjectManagerDeleteTimerMessage timerObjectManagerDeleteTimerMessage = new TimerObjectManagerDeleteTimerMessage (timerHandle);

        // if (null == timerObjectManagerDeleteTimerMessage)
        // {
        // errorTracePrintf ("WaveObjectManager.deleteTimer : Error allocating delete Timer Msg.");
        //
        // return (ResourceId.FRAMEWORK_TIMER_NO_MEMORY);
        // }

        final WaveMessageStatus status = sendSynchronously (timerObjectManagerDeleteTimerMessage);

        if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
        {
            errorTracePrintf ("WaveObjectManager.deleteTimer : delete timer message failed.");

            return (ResourceId.FRAMEWORK_TIMER_CAN_NOT_DELETE);
        }
        else
        {
            returnCode = timerObjectManagerDeleteTimerMessage.getCompletionStatus ();

            if (ResourceId.TIMER_SUCCESS != returnCode)
            {
                return (ResourceId.FRAMEWORK_TIMER_CAN_NOT_DELETE);
            }
            else
            {
                returnCode = ResourceId.FRAMEWORK_SUCCESS;
            }

            return (returnCode);
        }
    }

    public boolean isEventAllowedBeforeEnabling (final UI32 eventOperationCode)
    {
        // At present we do not allow any events to be passed to any service with out enabling the service.

        return (false);
    }

    public boolean getAllowAutomaticallyUnlistenForEvents ()
    {
        return m_allowAutomaticallyUnlistenForEvents;
    }

    public void setAllowAutomaticallyUnlistenForEvents (final boolean allowAutomaticallyUnlistenForEvents)
    {
        m_allowAutomaticallyUnlistenForEvents = allowAutomaticallyUnlistenForEvents;
    }

    public void unlistenEvents ()
    {
        LocationId eventSourceLocationId;
        WaveServiceId eventSourceServiceId;
        UI32 eventOperationCode;

        final LocationId thisLocationId = FrameworkToolKit.getThisLocationId ();

        for (final Map.Entry<LocationId, Map<WaveServiceId, Map<UI32, WaveEventMapContext>>> waveEventsMapForLocationIdEntry : m_eventsMap.entrySet ())
        {
            eventSourceLocationId = waveEventsMapForLocationIdEntry.getKey ();

            waveAssert (null != eventSourceLocationId);

            final Map<WaveServiceId, Map<UI32, WaveEventMapContext>> waveEventsMapForLocationId = waveEventsMapForLocationIdEntry.getValue ();

            waveAssert (null != waveEventsMapForLocationId);

            for (final Map.Entry<WaveServiceId, Map<UI32, WaveEventMapContext>> waveEventsMapForLocationIdAndServiceIdEntry : waveEventsMapForLocationId.entrySet ())
            {
                eventSourceServiceId = waveEventsMapForLocationIdAndServiceIdEntry.getKey ();

                waveAssert (null != eventSourceServiceId);

                final Map<UI32, WaveEventMapContext> waveEventsMapForLocationIdAndServiceId = waveEventsMapForLocationIdAndServiceIdEntry.getValue ();

                waveAssert (null != waveEventsMapForLocationIdAndServiceId);

                for (final Map.Entry<UI32, WaveEventMapContext> waveEventsMapForLocationIdAndServiceIdAndOperationIdEntry : waveEventsMapForLocationIdAndServiceId.entrySet ())
                {
                    eventOperationCode = waveEventsMapForLocationIdAndServiceIdAndOperationIdEntry.getKey ();

                    waveAssert (null != eventOperationCode);

                    final WaveEventMapContext waveEventMapContext = waveEventsMapForLocationIdAndServiceIdAndOperationIdEntry.getValue ();

                    waveAssert (null != waveEventMapContext);

                    if (thisLocationId.equals (eventSourceLocationId))
                    {
                        final WaveObjectManager waveObjectManager = WaveMessageFactory.getWaveObjectManagerForEvent (eventSourceServiceId, eventOperationCode);

                        // The remote transport service listens for any events. The way it achieves listening for any event is
                        // that it starts listening
                        // for any event that is generated by the null service. So the remote transport service does not have to
                        // specify a valid service with an object manager.

                        if (((!(WaveServiceId.NullServiceId.equals (eventSourceServiceId))) || ((!(FrameworkOpCodes.WAVE_OBJECT_MANAGER_ANY_EVENT.getOperationCode ()).equals (eventOperationCode)))) && (null == waveObjectManager))
                        {
                            fatalTracePrintf ("WaveObjectManager.unlistenEvents : There is no Object Manager to generate the specified event. ServiceId = %s, Source OperationCode = %s.", eventSourceServiceId.toString (), eventOperationCode.toString ());
                            waveAssert ();
                            return;
                        }

                        // Now add the listener to the object manager.

                        if (null != waveObjectManager)
                        {
                            waveObjectManager.removeEventListener (eventOperationCode, getServiceId (), FrameworkToolKit.getThisLocationId ());
                        }
                    }
                    else
                    {
                        // FIXME : sagar : send remote message to remove event listener.
                    }
                }
            }
        }

        m_eventsMap.clear ();

        debugTracePrintf ("WaveObjectManager.unlistenEvents : Finished unlistening all the events for this service.");

        // Also unlisten for the light pulses.

        unlistenLightPulses ();
    }

    protected void unlistenLightPulses ()
    {
        for (final String lightPulseName : m_lightPulsesMap.keySet ())
        {
            final LightPulseUnregistrationMessage lightPulseUnregistrationMessage = new LightPulseUnregistrationMessage (lightPulseName);

            final WaveMessageStatus sendStatus = sendSynchronously (lightPulseUnregistrationMessage);

            if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS == sendStatus)
            {
                final ResourceId completionStatus = lightPulseUnregistrationMessage.getCompletionStatus ();

                if (ResourceId.WAVE_MESSAGE_SUCCESS != completionStatus)
                {
                    trace (TraceLevel.TRACE_LEVEL_FATAL, "WaveObjectManager.listenForLightPulse : This light pulse un-registration could not be successfully completed : " + lightPulseName + ", status : " + (FrameworkToolKit.localize (completionStatus)));

                    waveAssert ();
                }
            }
            else
            {
                trace (TraceLevel.TRACE_LEVEL_FATAL, "WaveObjectManager.listenForLightPulse : This light pulse un-registration could not be sent : " + lightPulseName + ", status : " + (FrameworkToolKit.localize (sendStatus)));

                waveAssert ();
            }
        }

        m_lightPulsesMap.clear ();
    }

    protected void removeEventListener (final UI32 eventOperationCode, final WaveServiceId listenerWaveServiceId, final LocationId listenerLocationId)
    {
        // This member function can be called from multiple threads. So we need to make it thread safe.

        s_mutexForAddingEventListener.lock ();

        final Vector<WaveEventListenerMapContext> listenersForEvent = m_eventListenersMap.get (eventOperationCode);

        final Iterator<WaveEventListenerMapContext> iterator = listenersForEvent.iterator ();

        while (iterator.hasNext ())
        {
            final WaveEventListenerMapContext waveEventListenerMapContext = iterator.next ();

            waveAssert (null != waveEventListenerMapContext);

            final WaveServiceId waveServiceId = waveEventListenerMapContext.getEventListenerServiceId ();
            final LocationId locationId = waveEventListenerMapContext.getEventListenerLocationId ();

            waveAssert (null != waveServiceId);
            waveAssert (null != locationId);

            if ((waveServiceId.equals (listenerWaveServiceId)) && (locationId.equals (listenerLocationId)))
            {
                iterator.remove ();

                debugTracePrintf ("WaveObjectManager.removeEventListener : Removing an event Listener : ServiceId : %s : LocationId : %s", listenerWaveServiceId.toString (), listenerLocationId.toString ());

                break;
            }
        }

        s_mutexForAddingEventListener.unlock ();
    }

    protected long getNumberOfPendingTimerExpirationMessages ()
    {
        return (m_associatedWaveThread.getNumberOfPendingTimerExpirationMessages ());
    }

    protected long getNumberOfPendingNormalMessages ()
    {
        return (m_associatedWaveThread.getNumberOfPendingNormalMessages ());
    }

    protected long getNumberOfPendingHighPriorityMessages ()
    {
        return (m_associatedWaveThread.getNumberOfPendingHighPriorityMessages ());
    }

    @Override
    protected WaveMessageStatus broadcastLightPulse (final LightPulse lightPulse)
    {
        waveAssert (null != lightPulse);

        final LightHouseTransportBroadcastLightPulseMessage lightHouseTransportBroadcastLightPulseMessage = new LightHouseTransportBroadcastLightPulseMessage (lightPulse);

        waveAssert (null != lightHouseTransportBroadcastLightPulseMessage);

        final WaveMessageStatus sendStatus = sendOneWay (lightHouseTransportBroadcastLightPulseMessage);

        return (sendStatus);
    }
}
