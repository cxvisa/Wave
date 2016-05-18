/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.LightHouse.Test;

import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.ObjectManagerPriority;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Resources.ResourceEnums.WaveObjectManagerPriority;

@ObjectManagerPriority (WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_LIGHT_HOUSE_TEST_2)
public class LightHouseTestObjectManager2 extends WaveLocalObjectManager
{
    private static LightHouseTestObjectManager2 s_LightHouseTestObjectManager2 = null;

    public LightHouseTestObjectManager2 ()
    {
        super (getServiceName ());

        addLightPulseType (LightHouseTestLightPulse1.getLightPulseName ());
    }

    private static String getServiceName ()
    {
        return ("Light House Test 2");
    }

    public static LightHouseTestObjectManager2 getInstance ()
    {
        if (null == s_LightHouseTestObjectManager2)
        {
            s_LightHouseTestObjectManager2 = new LightHouseTestObjectManager2 ();
        }

        WaveAssertUtils.waveAssert (null != s_LightHouseTestObjectManager2);

        return (s_LightHouseTestObjectManager2);
    }

    public static WaveServiceId getWaveServiceId ()
    {
        return ((getInstance ()).getServiceId ());
    }
}
