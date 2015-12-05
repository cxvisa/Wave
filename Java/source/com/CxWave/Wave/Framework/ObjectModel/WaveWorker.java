/***************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonWorker;
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
        // TODO Auto-generated method stub

    }

    @Override
    protected void trace (final TraceLevel requestedTraceLevel, final String stringToTrace)
    {
        // TODO Auto-generated method stub

    }

    @Override
    protected void tracePrintf (final TraceLevel requestedTraceLevel, final boolean addNewLine, final boolean suppressPrefix, final String formatString, final Object... objects)
    {
        // TODO Auto-generated method stub

    }

    @Override
    protected void tracePrintf (final TraceLevel requestedTraceLevel, final String formatString, final Object... objects)
    {
        // TODO Auto-generated method stub

    }

}
