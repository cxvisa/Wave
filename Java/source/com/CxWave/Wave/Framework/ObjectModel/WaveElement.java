/***************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public abstract class WaveElement
{
    private WaveObjectManager m_waveObjectManager;

    protected WaveElement ()
    {
    }

    protected WaveElement (final WaveObjectManager waveObjectManager)
    {
        m_waveObjectManager = waveObjectManager;
    }

    protected WaveElement (final WaveElement waveElement)
    {
        m_waveObjectManager = waveElement.m_waveObjectManager;
    }

    protected WaveObjectManager getWaveObjectManager ()
    {
        return (m_waveObjectManager);
    }

    protected void setWaveObjectManager (final WaveObjectManager waveObjectManager)
    {
        m_waveObjectManager = waveObjectManager;
    }

    protected abstract void trace (final TraceLevel requestedTraceLevel, final String stringToTrace, final boolean addNewLine, final boolean suppressPrefix);

    protected abstract void trace (final TraceLevel requestedTraceLevel, final String stringToTrace);

    protected abstract void tracePrintf (final TraceLevel requestedTraceLevel, final boolean addNewLine, final boolean suppressPrefix, final String formatString, Object... objects);

    protected abstract void tracePrintf (final TraceLevel requestedTraceLevel, final String formatString, Object... objects);
}
