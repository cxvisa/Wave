/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.LightHouse.Test;

import com.CxWave.Wave.Framework.ObjectModel.WaveElement;
import com.CxWave.Wave.Framework.Utils.Context.WaveAsynchronousContext;
import com.CxWave.Wave.Framework.Utils.Sequencer.WaveLinearSequencerContext;

public class LightHouseTestContext extends WaveLinearSequencerContext
{
    public LightHouseTestContext (final WaveAsynchronousContext waveAsynchronousContext, final WaveElement waveElement, final String[] steps)
    {
        super (waveAsynchronousContext, waveElement, steps);
    }
}
