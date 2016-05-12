/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.LightHouse;

import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.ObjectManagerPriority;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Resources.ResourceEnums.WaveObjectManagerPriority;

@ObjectManagerPriority (WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_LIGHT_HOUSE_DISPATCHER)
public class LightPulseDispatchObjectManager extends WaveLocalObjectManager
{
    private static LightPulseDispatchObjectManager m_lightPulseDispatchObjectManager = null;

    public LightPulseDispatchObjectManager ()
    {
        super (getServiceName ());
    }

    public static String getServiceName ()
    {
        return ("Light House Dispatch");
    }

    public static LightPulseDispatchObjectManager getInstance ()
    {
        if (null == m_lightPulseDispatchObjectManager)
        {
            m_lightPulseDispatchObjectManager = new LightPulseDispatchObjectManager ();
        }

        WaveAssertUtils.waveAssert (null != m_lightPulseDispatchObjectManager);

        return (m_lightPulseDispatchObjectManager);
    }

    public static WaveServiceId getWaveServiceId ()
    {
        return ((getInstance ()).getServiceId ());
    }
}
