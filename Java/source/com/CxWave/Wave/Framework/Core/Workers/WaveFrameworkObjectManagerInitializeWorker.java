/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Workers;

import com.CxWave.Wave.Framework.Core.WaveFrameworkObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.OwnerOM;

@OwnerOM (om = WaveFrameworkObjectManager.class)
public class WaveFrameworkObjectManagerInitializeWorker extends WaveWorker
{
    public WaveFrameworkObjectManagerInitializeWorker (final WaveObjectManager waveObjectManager)
    {
        super (waveObjectManager);
    }

}
