/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Workers;

import com.CxWave.Wave.Framework.Core.WaveFrameworkObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorkerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.Cardinality;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.OwnerOM;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.WorkerPriority;

@OwnerOM (om = WaveFrameworkObjectManager.class)
@Cardinality (1)
@WorkerPriority (WaveWorkerPriority.WAVE_WORKER_PRIORITY_0)
public class WaveFrameworkObjectManagerInitializeWorker extends WaveWorker
{
    public WaveFrameworkObjectManagerInitializeWorker (final WaveObjectManager waveObjectManager)
    {
        super (waveObjectManager);
    }

}
