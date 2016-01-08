/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Regression.Contexts;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ObjectModel.WaveElement;
import com.CxWave.Wave.Framework.Utils.Context.WaveAsynchronousContext;
import com.CxWave.Wave.Framework.Utils.Sequencer.WaveLinearSequencerContext;

public class RegressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext extends WaveLinearSequencerContext
{

    public RegressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext (final WaveMessage waveMessage, final WaveElement waveElement, final String[] steps)
    {
        super (waveMessage, waveElement, steps);
    }

    public RegressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext (final WaveAsynchronousContext waveAsynchronousContext, final WaveElement waveElement, final String[] steps)
    {
        super (waveAsynchronousContext, waveElement, steps);
    }
}
