/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel.Workers;

import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorkerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.Cardinality;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.OwnerOM;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.Priority;

@OwnerOM (om = WaveObjectManager.class)
@Cardinality (1)
@Priority (WaveWorkerPriority.WAVE_WORKER_PRIORITY_0)
public class WaveEnableObjectManagerWorker extends WaveWorker
{
    public WaveEnableObjectManagerWorker (final WaveObjectManager waveObjectManager)
    {
        super (waveObjectManager);
    }
}
