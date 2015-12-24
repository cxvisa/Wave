/***********************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonWorker;
import com.CxWave.Wave.Framework.Type.UI32;
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
}
