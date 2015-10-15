/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core;

import com.CxWave.Wave.Framework.Utils.Random.WaveRandomGenerator;

public class Wave
{
    private Wave ()
    {
    }

    public void initialize ()
    {
        // Initialize Random Generator

        WaveRandomGenerator.initialize ();
    }
}
