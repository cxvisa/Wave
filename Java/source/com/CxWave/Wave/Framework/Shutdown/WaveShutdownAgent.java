/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Shutdown;

import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;

public class WaveShutdownAgent extends WaveWorker
{
    public WaveShutdownAgent (final WaveObjectManager waveObjectManager)
    {
        super (waveObjectManager);
    }

    public ResourceId execute ()
    {
        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }
}
