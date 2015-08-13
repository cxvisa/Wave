/***************************************************************************
 *   Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc             *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.Wave.Framework.Utils.Assert;

public class WaveAssertUtils
{
    public static void waveAssert (boolean isAssertNotRequired)
    {
        Thread.dumpStack ();
        (Runtime.getRuntime()).halt (-1);
    }

    public static void waveAssert ()
    {
        waveAssert (false);
    }
}
