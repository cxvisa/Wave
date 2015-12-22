/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core;

public class WaveBasedApplication
{

    public static void waveMain (final String waveMainConfigurationFile)
    {
        Wave.initialize (waveMainConfigurationFile);

        WaveFrameworkObjectManager.bootWave ();
    }
}
