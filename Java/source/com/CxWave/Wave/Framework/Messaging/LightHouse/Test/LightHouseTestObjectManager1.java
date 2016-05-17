/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.LightHouse.Test;

import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Regression.WaveTestObjectManager;
import com.CxWave.Wave.Regression.Contexts.RegressionTestAsynchronousContext;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class LightHouseTestObjectManager1 extends WaveTestObjectManager
{
    private static LightHouseTestObjectManager1 s_LightHouseTestObjectManager1   = null;
    private static final int                    numberOfLightPulsesToBeBroadcast = 1000;
    private static int                          currentCounter                   = 0;

    public LightHouseTestObjectManager1 ()
    {
        super (getServiceName ());
    }

    private static String getServiceName ()
    {
        return ("Light House Test 1");
    }

    public static LightHouseTestObjectManager1 getInstance ()
    {
        if (null == s_LightHouseTestObjectManager1)
        {
            s_LightHouseTestObjectManager1 = new LightHouseTestObjectManager1 ();
        }

        WaveAssertUtils.waveAssert (null != s_LightHouseTestObjectManager1);

        return (s_LightHouseTestObjectManager1);
    }

    public static WaveServiceId getWaveServiceId ()
    {
        return ((getInstance ()).getServiceId ());
    }

    @Override
    public void handleTestRequest (final RegressionTestAsynchronousContext regressionTestAsynchronousContext)
    {
        develTracePrintf ("FrameworkLocalMessagingTestObjectManager.handleTestRequest : Entering ...");

        final String[] sequencerSteps =
            {
                            "broadcastTestLightPulse1TestStep",
                            "waveLinearSequencerSucceededStep",
                            "waveLinearSequencerFailedStep"
            };

        final LightHouseTestContext lightHouseTestContext = new LightHouseTestContext (regressionTestAsynchronousContext, this, sequencerSteps);

        lightHouseTestContext.holdAll ();
        lightHouseTestContext.start ();
    }

    private void broadcastTestLightPulse1TestStep (final LightHouseTestContext lightHouseTestContext)
    {
        trace (TraceLevel.TRACE_LEVEL_DEVEL, "LightHouseTestObjectManager1::broadcastTestLightPulse1TestStep : Entering ...");

        int i = 0;

        for (i = 0; i < numberOfLightPulsesToBeBroadcast; i++)
        {
            final LightHouseTestLightPulse1 lightHouseTestLightPulse1 = new LightHouseTestLightPulse1 ();

            waveAssert (null != lightHouseTestLightPulse1);

            lightHouseTestLightPulse1.setLightMessage (new String ("Light Message : ") + currentCounter++);

            broadcastLightPulse (lightHouseTestLightPulse1);
        }

        lightHouseTestContext.executeNextStep (ResourceId.WAVE_MESSAGE_SUCCESS);
    }
}
