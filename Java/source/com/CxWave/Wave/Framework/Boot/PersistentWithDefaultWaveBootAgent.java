/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Boot;

import com.CxWave.Wave.Framework.Core.FrameworkSequenceGenerator;
import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;

public class PersistentWithDefaultWaveBootAgent extends WaveBootAgent
{
    public PersistentWithDefaultWaveBootAgent (final WaveObjectManager waveObjectManager, final FrameworkSequenceGenerator frameworkSequenceGenerator)
    {
        super (waveObjectManager, frameworkSequenceGenerator);
    }
}
