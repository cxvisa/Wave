/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.math.BigInteger;
import java.util.Collections;
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
import com.CxWave.Wave.Framework.ObjectModel.Boot.WaveAsynchronousContextForBootPhases;
import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
import com.CxWave.Wave.Framework.Trace.TraceObjectManager;
import com.CxWave.Wave.Framework.Type.LocationId;
import com.CxWave.Wave.Framework.Type.TimerHandle;
import com.CxWave.Wave.Framework.Type.TraceClientId;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Type.UI64;
import com.CxWave.Wave.Framework.Type.WaveGenericContext;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Source.WaveJavaSourceRepository;
import com.CxWave.Wave.Framework.Utils.Stack.WaveStackUtils;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.FrameworkStatus;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;
import com.CxWave.Wave.Resources.ResourceEnums.WaveMessageStatus;
import com.CxWave.Wave.Resources.ResourceEnums.WaveMessageType;
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

    private static WaveMutex                                           s_waveObjectManagerMutex                         = new WaveMutex ();
    private static WaveServiceId                                       s_nextAvailableWaveServiceId                     = new WaveServiceId (0);
    private static WaveServiceMode                                     s_waveServiceLaunchMode                          = WaveServiceMode.WAVE_SERVICE_ACTIVE;

    private static final Set<UI32>                                     s_operationsAllowedBeforeEnabling                = initializeOperationsAllowedBeforeEnablingSet ();

    private final String                                               m_name;
    private WaveThread                                                 m_associatedWaveThread;
    private final Map<UI32, WaveOperationMapContext>                   m_operationsMap                                  = new HashMap<UI32, WaveOperationMapContext> ();
    private final Map<Class<?>, UI32>                                  m_operationsClassToIdMap                         = new HashMap<Class<?>, UI32> ();
    private final Map<UI32, Class<?>>                                  m_operationsIdToClassMap                         = new HashMap<UI32, Class<?>> ();
    private Map<UI32, BigInteger>                                      m_supportedEvents;
    private Map<LocationId, Map<UI32, Map<UI32, WaveEventMapContext>>> m_eventsMap;
    private Map<UI32, WaveMessageResponseContext>                      m_responsesMap;
    private Map<UI32, Vector<WaveEventListenerMapContext>>             m_eventListenersMap;
    private Map<String, Vector<String>>                                m_postbootManagedObjectNames;
    private WaveMutex                                                  m_responsesMapMutex;
    private WaveMutex                                                  m_sendReplyMutexForResponseMap;
    private final Vector<WaveWorker>                                   m_workers                                        = new Vector<WaveWorker> ();
    private final WaveMutex                                            m_workersMutex                                   = new WaveMutex ();
    private boolean                                                    m_isEnabled                                      = false;
    private final WaveMutex                                            m_isEnabledMutex                                 = new WaveMutex ();
    private final TraceClientId                                        m_traceClientId;
    private final WaveServiceMode                                      m_waveServiceMode;

    private final WaveServiceId                                        m_serviceId;

    private WaveMessage                                                m_inputMessage;

    private final Map<UI32, Map<UI32, UI64>>                           m_nanoSecondsForMessageHandlerSequencerSteps     = new HashMap<UI32, Map<UI32, UI64>> ();

    private final Map<UI32, Map<UI32, UI64>>                           m_realNanoSecondsForMessageHandlerSequencerSteps = new HashMap<UI32, Map<UI32, UI64>> ();

    private final WaveMutex                                            m_createMessageInstanceWrapperMutex              = new WaveMutex ();
    private final Map<UI32, WaveElement>                               m_ownersForCreatingMessageInstances              = new HashMap<UI32, WaveElement> ();

    public void prepareObjectManagerForAction ()
    {
        addWorkers ();
        addSupportedOperations ();
    }

    public void addSupportedOperations ()
    {
        final Map<Class<?>, Method> messageHandlersInInheritanceHierarchyPreferringLatest = WaveJavaSourceRepository.getMessageHandlersInInheritanceHierarchyPreferringLatest ((getClass ()).getName ());

        for (final Map.Entry<Class<?>, Method> entry : messageHandlersInInheritanceHierarchyPreferringLatest.entrySet ())
        {
            addOperationMapForMessageClass (entry.getKey (), entry.getValue (), this);
        }
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

                try
                {
                    constructor = waveWorkerClass.getConstructor (WaveObjectManager.class);
                }
                catch (NoSuchMethodException | SecurityException e)
                {
                    fatalTracePrintf ("WaveObjectManager.addWorkers :        A constructor that takes WaveObjectManager as argument could not be found.  Details :%s", e.toString ());

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
                    fatalTracePrintf ("WaveObjectManager.addWorkers :        A constructor that takes WaveObjectManager as argument could not be executed.  Details : %s", e.toString ());

                    WaveAssertUtils.waveAssert ();
                }
                catch (final InvocationTargetException e1)
                {
                    fatalTracePrintf ("WaveObjectManager.addWorkers :        A constructor that takes WaveObjectManager as argument could not be executed.  Details : %s", WaveStackUtils.getStackString (e1.getCause ()));
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
        infoTracePrintf ("WaveObjectManager.reply : Replying to a message ...");

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
                errorTrace (new String ("WaveObjectManager::reply : No Service registered to accept reply with this service Id ") + tempWaveMessage.getSenderServiceCode () + ". How did we receive this message in the first place.  May be the service went down after submitting the request.  Dropping and destroying the message.");

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
            trace (TraceLevel.TRACE_LEVEL_FATAL, "WaveObjectManager.addWorker : Trying to add a NULL worker from this manager.  Will not add.");

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
        }

        m_workersMutex.unlock ();
    }

    public void removeWorker (final WaveWorker waveWorker)
    {
        if (null == waveWorker)
        {
            trace (TraceLevel.TRACE_LEVEL_FATAL, "WaveObjectManager.removeWorker : Trying to remove a NULL worker from this manager.  Will not remove.");

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
                errorTracePrintf ("WaveObjectManager::createMessageInstanceWrapper : Owner for %d has not implemented dynamically creating the instance of this Message Type.  Implement this functionality to proceed further.", operationCode);
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
                errorTracePrintf ("WaveObjectManager::createMessageInstanceWrapper : Owner for %d via WAVE_OBJECT_MANAGER_ANY_OPCODE has not implemented dynamically creating the instance of this Message Type.  Implement this functionality to proceed further.", operationCode);
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
}
