/***********************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Configuration;

public interface WaveConfigurationFileInterface
{
    void load ();

    WaveConfiguration getWaveConfiguration ();

    void reload ();
}