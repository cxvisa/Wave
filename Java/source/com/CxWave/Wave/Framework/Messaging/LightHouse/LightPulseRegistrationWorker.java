/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.LightHouse;

import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorkerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.Cardinality;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.OwnerOM;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.WorkerPriority;
import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

@OwnerOM (om = LightPulseDispatchObjectManager.class)
@Cardinality (1)
@WorkerPriority (WaveWorkerPriority.WAVE_WORKER_PRIORITY_0)
public class LightPulseRegistrationWorker extends WaveWorker
{
    public LightPulseRegistrationWorker (final LightPulseDispatchObjectManager lightPulseDispatchObjectManager)
    {
        super (lightPulseDispatchObjectManager);
    }

    private void registerForLightPulseMessageHandler (final LightPulseRegistrationMessage lightPulseRegistrationMessage)
    {
        trace (TraceLevel.TRACE_LEVEL_DEVEL, "LightPulseRegistrationWorker.registerForLightPulseMessageHandler : Entering ...");

        waveAssert (null != lightPulseRegistrationMessage);

        final LightPulseRegistrationRepository lightPulseRegistrationRepository = LightPulseRegistrationRepository.getInstance ();

        waveAssert (null != lightPulseRegistrationRepository);

        final String lightPulseName = lightPulseRegistrationMessage.getLightPulseName ();
        final WaveServiceId waveServiceId = lightPulseRegistrationMessage.getSenderServiceCode ();

        lightPulseRegistrationRepository.addLightPulseRecepientForLightPulseName (lightPulseName, waveServiceId);

        tracePrintf (TraceLevel.TRACE_LEVEL_INFO, true, false, "LightPulseRegistrationWorker.registerForLightPulseMessageHandler : Registered %s for %s", FrameworkToolKit.getServiceNameById (waveServiceId), lightPulseName);

        lightPulseRegistrationMessage.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        reply (lightPulseRegistrationMessage);
    }
}
