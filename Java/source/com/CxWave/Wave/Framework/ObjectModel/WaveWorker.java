/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import java.lang.reflect.Method;
import java.util.Map;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonMessageHandler;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonWorker;
import com.CxWave.Wave.Framework.ObjectModel.Boot.WaveAsynchronousContextForBootPhases;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Utils.Source.WaveJavaSourceRepository;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

@NonWorker
public class WaveWorker extends WaveElement
{
    private final boolean m_linkWorkerToParentObjectManager = true;

    public WaveWorker (final WaveObjectManager waveObjectManager)
    {
        super (waveObjectManager);

        if (m_linkWorkerToParentObjectManager)
        {
            waveObjectManager.addWorker (this);
        }
    }

    @Override
    protected void trace (final TraceLevel requestedTraceLevel, final String stringToTrace, final boolean addNewLine, final boolean suppressPrefix)
    {
        m_waveObjectManager.trace (requestedTraceLevel, stringToTrace, addNewLine, suppressPrefix);
    }

    @Override
    protected void trace (final TraceLevel requestedTraceLevel, final String stringToTrace)
    {
        m_waveObjectManager.trace (requestedTraceLevel, stringToTrace);
    }

    @Override
    protected void tracePrintf (final TraceLevel requestedTraceLevel, final boolean addNewLine, final boolean suppressPrefix, final String formatString, final Object... objects)
    {
        m_waveObjectManager.tracePrintf (requestedTraceLevel, addNewLine, suppressPrefix, formatString, objects);
    }

    @Override
    protected void tracePrintf (final TraceLevel requestedTraceLevel, final String formatString, final Object... objects)
    {
        m_waveObjectManager.tracePrintf (requestedTraceLevel, formatString, objects);
    }

    @Override
    protected void holdMessages ()
    {
        m_waveObjectManager.holdMessages ();
    }

    @Override
    protected void holdHighPriorityMessages ()
    {
        m_waveObjectManager.holdHighPriorityMessages ();
    }

    @Override
    protected void holdEvents ()
    {
        m_waveObjectManager.holdEvents ();
    }

    @Override
    public void holdAll ()
    {
        m_waveObjectManager.holdAll ();
    }

    @Override
    protected void unholdMessages ()
    {
        m_waveObjectManager.unholdMessages ();
    }

    @Override
    protected void unholdHighPriorityMessages ()
    {
        m_waveObjectManager.unholdHighPriorityMessages ();
    }

    @Override
    protected void unholdEvents ()
    {
        m_waveObjectManager.unholdEvents ();
    }

    @Override
    public void unholdAll ()
    {
        m_waveObjectManager.unholdAll ();
    }

    @Override
    public void updateTimeConsumedInThisThread (final UI32 operationCode, final int currentStep, final long lastLapDuration)
    {
        m_waveObjectManager.updateTimeConsumedInThisThread (operationCode, currentStep, lastLapDuration);
    }

    @Override
    public void updateRealTimeConsumedInThisThread (final UI32 operationCode, final int currentStep, final long lastLapDuration)
    {
        m_waveObjectManager.updateRealTimeConsumedInThisThread (operationCode, currentStep, lastLapDuration);
    }

    public void addSupportedOperations ()
    {
        final Map<Class<?>, Method> messageHandlersInInheritanceHierarchyPreferringLatest = WaveJavaSourceRepository.getMessageHandlersInInheritanceHierarchyPreferringLatest ((getClass ()).getName ());

        for (final Map.Entry<Class<?>, Method> entry : messageHandlersInInheritanceHierarchyPreferringLatest.entrySet ())
        {
            infoTracePrintf ("WaveWorker.addSupportedOperations :             Adding worker message handler for  %s : %s", (entry.getKey ()).getName (), (entry.getValue ()).getName ());

            m_waveObjectManager.addOperationMapForMessageClass (entry.getKey (), entry.getValue (), this);
        }
    }

    @Override
    @NonMessageHandler
    protected ResourceId reply (final WaveMessage waveMessage)
    {
        return (m_waveObjectManager.reply (waveMessage));
    }

    @Override
    protected ResourceId commitTransaction ()
    {
        return (m_waveObjectManager.commitTransaction ());
    }

    @Override
    protected void rollbackTransaction ()
    {
        m_waveObjectManager.rollbackTransaction ();
    }

    protected void waveAssert ()
    {
        m_waveObjectManager.waveAssert ();
    }

    protected void waveAssert (final boolean isAssertNotRequired)
    {
        m_waveObjectManager.waveAssert (isAssertNotRequired);
    }

    public void initialize (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("WaveWorker.initialize : Entering for %s ...", (getClass ()).getName ());

        waveAsynchronousContextForBootPhases.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        waveAsynchronousContextForBootPhases.callback ();
    }

    public void enable (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("WaveWorker.enable : Entering for %s ...", (getClass ()).getName ());

        waveAsynchronousContextForBootPhases.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        waveAsynchronousContextForBootPhases.callback ();
    }

    public void install (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("WaveWorker.install : Entering for %s ...", (getClass ()).getName ());

        waveAsynchronousContextForBootPhases.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        waveAsynchronousContextForBootPhases.callback ();
    }

    public void boot (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("WaveWorker.boot : Entering for %s ...", (getClass ()).getName ());

        waveAsynchronousContextForBootPhases.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        waveAsynchronousContextForBootPhases.callback ();
    }

    public void listenForEvents (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("WaveWorker.listenForEvents : Entering for %s ...", (getClass ()).getName ());

        waveAsynchronousContextForBootPhases.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        waveAsynchronousContextForBootPhases.callback ();
    }
}
