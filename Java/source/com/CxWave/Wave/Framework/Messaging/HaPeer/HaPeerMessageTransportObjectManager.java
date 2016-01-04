/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.HaPeer;

import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManager;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;

public class HaPeerMessageTransportObjectManager extends WaveLocalObjectManager
{
    private static HaPeerMessageTransportObjectManager s_haPeerMessageTransportObjectManager = null;

    private HaPeerMessageTransportObjectManager ()
    {
        super (getServiceName ());
    }

    public static String getServiceName ()
    {
        return ("Ha Peer Message Transport");
    }

    public static HaPeerMessageTransportObjectManager getInstance ()
    {
        if (null == s_haPeerMessageTransportObjectManager)
        {
            s_haPeerMessageTransportObjectManager = new HaPeerMessageTransportObjectManager ();
        }

        WaveAssertUtils.waveAssert (null != s_haPeerMessageTransportObjectManager);

        return (s_haPeerMessageTransportObjectManager);
    }

    public static WaveServiceId getWaveServiceId ()
    {
        return ((getInstance ()).getServiceId ());
    }
}
