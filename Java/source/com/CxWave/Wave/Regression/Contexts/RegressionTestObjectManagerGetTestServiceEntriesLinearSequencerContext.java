/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Regression.Contexts;

import java.util.Vector;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ObjectModel.WaveElement;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Context.WaveAsynchronousContext;
import com.CxWave.Wave.Framework.Utils.Sequencer.WaveLinearSequencerContext;

public class RegressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext extends WaveLinearSequencerContext
{
    private final Vector<WaveServiceId> m_testServiceIds    = new Vector<WaveServiceId> ();
    private final Vector<Boolean>       m_testServiceStates = new Vector<Boolean> ();

    public RegressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext (final WaveMessage waveMessage, final WaveElement waveElement, final String[] steps)
    {
        super (waveMessage, waveElement, steps);
    }

    public RegressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext (final WaveAsynchronousContext waveAsynchronousContext, final WaveElement waveElement, final String[] steps)
    {
        super (waveAsynchronousContext, waveElement, steps);
    }

    public void addTestService (final WaveServiceId testServiceId, final boolean testServiceState)
    {
        m_testServiceIds.add (testServiceId);
        m_testServiceStates.add (testServiceState);
    }

    public Vector<WaveServiceId> getTestServiceIds ()
    {
        return m_testServiceIds;
    }

    public Vector<Boolean> getTestServiceStates ()
    {
        return m_testServiceStates;
    }
}
