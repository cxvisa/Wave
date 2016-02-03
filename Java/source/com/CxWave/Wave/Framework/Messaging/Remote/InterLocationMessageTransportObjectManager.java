/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.Remote;

import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NativeService;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.ObjectManagerPriority;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Resources.ResourceEnums.WaveObjectManagerPriority;

@NativeService
@ObjectManagerPriority (WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_INTER_LOCATION_MESSAGE_TRANSPORT)
public class InterLocationMessageTransportObjectManager extends WaveLocalObjectManager
{
    private static InterLocationMessageTransportObjectManager s_InterLocationMessageTransportObjectManager = null;

    private InterLocationMessageTransportObjectManager ()
    {
        super (getServiceName ());
    }

    public static String getServiceName ()
    {
        return ("Remote Message Transport");
    }

    public static InterLocationMessageTransportObjectManager getInstance ()
    {
        if (null == s_InterLocationMessageTransportObjectManager)
        {
            s_InterLocationMessageTransportObjectManager = new InterLocationMessageTransportObjectManager ();
        }

        WaveAssertUtils.waveAssert (null != s_InterLocationMessageTransportObjectManager);

        return (s_InterLocationMessageTransportObjectManager);
    }

    public static WaveServiceId getWaveServiceId ()
    {
        return ((getInstance ()).getServiceId ());
    }
}
