/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.MultiThreading;

import com.CxWave.Wave.Framework.Type.UI32;

public class WaveThreadBase extends Thread
{
    private static final long s_defaultStackSize = 256 * 1024;

    public WaveThreadBase (final String threadName, final UI32 stackSize)
    {
        super (null, null, threadName, stackSize.getValue ());
    }

    public WaveThreadBase (final String threadName)
    {
        super (null, null, threadName, s_defaultStackSize);
    }

    public static UI32 getDefaultStackSize ()
    {
        return (new UI32 (s_defaultStackSize));
    }
}
