/***********************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;

public class ReservedWaveLocalObjectManager extends WaveLocalObjectManager
{
    private static ReservedWaveLocalObjectManager s_reservedWaveLocalObjectManager = null;

    private ReservedWaveLocalObjectManager ()
    {
        super (getClassName ());
    }

    public static String getClassName ()
    {
        return ("_Reserved For Wave Internal Purposes_");
    }

    public static ReservedWaveLocalObjectManager getInstance ()
    {
        if (null == s_reservedWaveLocalObjectManager)
        {
            s_reservedWaveLocalObjectManager = new ReservedWaveLocalObjectManager ();
        }

        WaveAssertUtils.waveAssert (null != s_reservedWaveLocalObjectManager);

        return (s_reservedWaveLocalObjectManager);
    }

    public static WaveServiceId getWaveServiceId ()
    {
        return ((getInstance ()).getServiceId ());
    }
}
