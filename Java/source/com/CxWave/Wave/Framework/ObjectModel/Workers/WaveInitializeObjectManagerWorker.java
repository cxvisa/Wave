/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel.Workers;

import com.CxWave.Wave.Framework.Core.Messages.WaveInitializeObjectManagerMessage;
import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorkerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.Cardinality;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.OwnerOM;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.WorkerPriority;
import com.CxWave.Wave.Framework.Utils.Sequencer.WaveLinearSequencerContext;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;

@OwnerOM (om = WaveObjectManager.class)
@Cardinality (1)
@WorkerPriority (WaveWorkerPriority.WAVE_WORKER_PRIORITY_0)
public class WaveInitializeObjectManagerWorker extends WaveWorker
{
    public WaveInitializeObjectManagerWorker (final WaveObjectManager waveObjectManager)
    {
        super (waveObjectManager);
    }

    private void initializeMessageHandler (final WaveInitializeObjectManagerMessage waveInitializeObjectManagerMessage)
    {
        infoTracePrintf ("WaveInitializeObjectManagerWorker.initializeMessageHandler : Entering ... for OM %s: ", (getWaveObjectManager ()).getName ());

        final String[] sequencerSteps =
            {
                            "initializeInitializeWorkersStep",
                            "initializeInitializeSelfStep",
                            "waveLinearSequencerSucceededStep",
                            "waveLinearSequencerFailedStep"
            };

        final WaveLinearSequencerContext waveLinearSequencerContext = new WaveLinearSequencerContext (waveInitializeObjectManagerMessage, this, sequencerSteps);

        waveLinearSequencerContext.start ();
    }

    private void initializeInitializeWorkersStep (final WaveLinearSequencerContext waveLinearSequencerContext)
    {
        WaveTraceUtils.infoTracePrintf ("WaveInitializeObjectManagerWorker.initializeInitializeWorkersStep : Entering ...");

        waveLinearSequencerContext.executeNextStep (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private void initializeInitializeSelfStep (final WaveLinearSequencerContext waveLinearSequencerContext)
    {
        WaveTraceUtils.infoTracePrintf ("WaveInitializeObjectManagerWorker.initializeInitializeSelfStep : Entering ...");

        waveLinearSequencerContext.executeNextStep (ResourceId.WAVE_MESSAGE_SUCCESS);
    }
}
