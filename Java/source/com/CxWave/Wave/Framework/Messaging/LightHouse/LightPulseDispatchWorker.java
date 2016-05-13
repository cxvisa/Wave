/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.LightHouse;

import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorkerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.Cardinality;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.OwnerOM;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.WorkerPriority;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;

@OwnerOM (om = LightPulseDispatchObjectManager.class)
@Cardinality (1)
@WorkerPriority (WaveWorkerPriority.WAVE_WORKER_PRIORITY_0)
public class LightPulseDispatchWorker extends WaveWorker
{
    public LightPulseDispatchWorker (final LightPulseDispatchObjectManager lightPulseDispatchObjectManager)
    {
        super (lightPulseDispatchObjectManager);
    }

    private void dispatchReceivedLightPulseMessageHandler (final LightPulseDispatchMessage lightPulseDispatchMessage)
    {
        infoTracePrintf ("LightPulseDispatchWorker.dispatchReceivedLightPulseMessageHandler : Receied a light Pulse : %s", lightPulseDispatchMessage.getLightPulseSerializedString ());

        lightPulseDispatchMessage.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        reply (lightPulseDispatchMessage);
    }
}
