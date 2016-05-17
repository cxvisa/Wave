/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.LightHouse;

import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManager;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;

public class LightHouseTransportObjectManager extends WaveLocalObjectManager
{
    private static LightHouseTransportObjectManager s_lightHouseTransportObjectManager = null;

    public LightHouseTransportObjectManager ()
    {
        super (getServiceName ());
    }

    public static String getServiceName ()
    {
        return ("Light House Transport");
    }

    public static LightHouseTransportObjectManager getInstance ()
    {
        if (null == s_lightHouseTransportObjectManager)
        {
            s_lightHouseTransportObjectManager = new LightHouseTransportObjectManager ();
        }

        WaveAssertUtils.waveAssert (null != s_lightHouseTransportObjectManager);

        return (s_lightHouseTransportObjectManager);
    }

    public static WaveServiceId getWaveServiceId ()
    {
        return ((getInstance ()).getServiceId ());
    }
}
