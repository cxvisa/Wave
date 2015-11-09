/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core;

import com.CxWave.Wave.Framework.Core.Configuration.WaveMainConfiguration;

public class WaveBasedApplication
{

    public static void waveMain (final WaveMainConfiguration waveMainConfiguration)
    {
        Wave.initialize (waveMainConfiguration);
    }
}
