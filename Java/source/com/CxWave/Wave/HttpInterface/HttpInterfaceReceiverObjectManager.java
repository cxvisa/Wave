/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.HttpInterface;

import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManagerForUserSpecificTasks;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.ObjectManagerPriority;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Resources.ResourceEnums.WaveObjectManagerPriority;

@ObjectManagerPriority (WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_HTTP_INTERFACE)
public class HttpInterfaceReceiverObjectManager extends WaveLocalObjectManagerForUserSpecificTasks
{
    private static HttpInterfaceReceiverObjectManager s_httpHttpInterfaceReceiverObjectManager = null;

    public HttpInterfaceReceiverObjectManager ()
    {
        super (getServiceName ());
    }

    public static String getServiceName ()
    {
        return ("HTTP Interface");
    }

    public static HttpInterfaceReceiverObjectManager getInstance ()
    {
        if (null == s_httpHttpInterfaceReceiverObjectManager)
        {
            s_httpHttpInterfaceReceiverObjectManager = new HttpInterfaceReceiverObjectManager ();
        }

        WaveAssertUtils.waveAssert (null != s_httpHttpInterfaceReceiverObjectManager);

        return (s_httpHttpInterfaceReceiverObjectManager);
    }

    public static WaveServiceId getWaveServiceId ()
    {
        return ((getInstance ()).getServiceId ());
    }
}
