/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Timer;

import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.OwnerOM;

@OwnerOM (om = TimerObjectManager.class)
public class TimerWorker extends WaveWorker
{
    public TimerWorker (final WaveObjectManager waveObjectManager)
    {
        super (waveObjectManager);
    }
}
