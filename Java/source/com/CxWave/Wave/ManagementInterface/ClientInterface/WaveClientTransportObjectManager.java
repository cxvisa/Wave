/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.ManagementInterface.ClientInterface;

import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManager;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;

public class WaveClientTransportObjectManager extends WaveLocalObjectManager
{
    private static WaveClientTransportObjectManager s_clientTransportObjectManager = null;

    public WaveClientTransportObjectManager ()
    {
        super (getServiceName ());
    }

    public static String getServiceName ()
    {
        return ("Wave Client Transport");
    }

    public static WaveClientTransportObjectManager getInstance ()
    {
        if (null == s_clientTransportObjectManager)
        {
            s_clientTransportObjectManager = new WaveClientTransportObjectManager ();
        }

        WaveAssertUtils.waveAssert (null != s_clientTransportObjectManager);

        return (s_clientTransportObjectManager);
    }

    public static WaveServiceId getWaveServiceId ()
    {
        return ((getInstance ()).getServiceId ());
    }
}
