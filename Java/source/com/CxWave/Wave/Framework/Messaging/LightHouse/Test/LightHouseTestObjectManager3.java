/*************************************************************************************************************************
 * Copyright (C) 3015-3016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.LightHouse.Test;

import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.ObjectManagerPriority;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;
import com.CxWave.Wave.Resources.ResourceEnums.WaveObjectManagerPriority;

@ObjectManagerPriority (WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_LIGHT_HOUSE_TEST_3)
public class LightHouseTestObjectManager3 extends WaveLocalObjectManager
{
    private static LightHouseTestObjectManager3 s_LightHouseTestObjectManager3 = null;

    public LightHouseTestObjectManager3 ()
    {
        super (getServiceName ());
    }

    private static String getServiceName ()
    {
        return ("Light House Test 3");
    }

    public static LightHouseTestObjectManager3 getInstance ()
    {
        if (null == s_LightHouseTestObjectManager3)
        {
            s_LightHouseTestObjectManager3 = new LightHouseTestObjectManager3 ();
        }

        WaveAssertUtils.waveAssert (null != s_LightHouseTestObjectManager3);

        return (s_LightHouseTestObjectManager3);
    }

    public static WaveServiceId getWaveServiceId ()
    {
        return ((getInstance ()).getServiceId ());
    }

    private void lightHouseTestLightPulse1Handler (final LightHouseTestLightPulse1 lightHouseTestLightPulse1)
    {
        waveAssert (null != lightHouseTestLightPulse1);

        final String lightMessage = lightHouseTestLightPulse1.getLightMessage ();
        final String senderIpAddressFromClientPerspective = lightHouseTestLightPulse1.getSenderIpAddressFromClientPerspective ();

        trace (TraceLevel.TRACE_LEVEL_INFO, "LightHouseTestObjectManager3::lightHouseTestLightPulse1Handler : Light Message Received : " + lightMessage + ", from ip address : " + senderIpAddressFromClientPerspective);
    }
}
