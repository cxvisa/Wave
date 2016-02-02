/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Boot;

import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;

public class WaveBootAgent extends WaveWorker
{
    public WaveBootAgent (final WaveObjectManager waveObjectManager)
    {
        super (waveObjectManager);
    }

    public ResourceId execute (final WaveBootPhase waveBootPhase)
    {
        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }
}
