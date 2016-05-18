/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel.Workers;

import com.CxWave.Wave.Framework.Core.Messages.WaveDeliverLightPulseMessage;
import com.CxWave.Wave.Framework.Messaging.LightHouse.LightPulse;
import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorkerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.Cardinality;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.OwnerOM;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.WorkerPriority;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;

@OwnerOM (om = WaveObjectManager.class)
@Cardinality (1)
@WorkerPriority (WaveWorkerPriority.WAVE_WORKER_PRIORITY_0)
public class WaveDeliverLightPulseObjectManagerWorker extends WaveWorker
{
    public WaveDeliverLightPulseObjectManagerWorker (final WaveObjectManager waveObjectManager)
    {
        super (waveObjectManager);
    }

    private void deliverLightPulseMessageHandler (final WaveDeliverLightPulseMessage waveDeliverLightPulseMessage)
    {
        waveAssert (null != waveDeliverLightPulseMessage);

        final LightPulse lightPulse = waveDeliverLightPulseMessage.getLightPulse ();

        handleLightPulse (lightPulse);

        waveDeliverLightPulseMessage.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        reply (waveDeliverLightPulseMessage);
    }
}
