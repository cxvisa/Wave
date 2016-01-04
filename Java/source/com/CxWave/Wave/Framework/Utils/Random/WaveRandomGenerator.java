/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Random;

import java.util.Random;

public class WaveRandomGenerator
{
    private static Random s_random = new Random (System.currentTimeMillis ());

    private WaveRandomGenerator ()
    {
    }

    public static void initialize ()
    {
    }

    public static int generate ()
    {
        return (s_random.nextInt ());
    }
}
