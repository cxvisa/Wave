/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Workers;

import com.CxWave.Wave.Framework.Boot.WaveBootPhase;
import com.CxWave.Wave.Framework.Core.WaveBootMode;
import com.CxWave.Wave.Framework.Core.WaveFrameworkObjectManager;
import com.CxWave.Wave.Framework.Core.Contexts.WaveFrameworkInitializeWorkerStartServicesContext;
import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorkerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.Cardinality;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.OwnerOM;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.WorkerPriority;
import com.CxWave.Wave.Framework.Utils.Context.WaveAsynchronousContext;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;

@OwnerOM (om = WaveFrameworkObjectManager.class)
@Cardinality (1)
@WorkerPriority (WaveWorkerPriority.WAVE_WORKER_PRIORITY_0)
public class WaveFrameworkObjectManagerInitializeWorker extends WaveWorker
{
    public WaveFrameworkObjectManagerInitializeWorker (final WaveObjectManager waveObjectManager)
    {
        super (waveObjectManager);
    }

    public void startWaveServices ()
    {
        startWaveServices (WaveBootMode.WAVE_BOOT_UNKNOWN, WaveBootPhase.WAVE_BOOT_PHASE_ALL_PHASES);
    }

    public void startWaveServices (final WaveBootMode waveBootMode, final WaveBootPhase waveBootPhase)
    {
        infoTracePrintf ("WaveFrameworkObjectManagerInitializeWorker.startWaveServices : Entering ...");

        final String[] sequencerSteps =
            {
                            "determineNodeBootModeStep",
                            "chooseABootAgentStep",
                            "runTheBootAgentStep",
                            "saveConfigurationStep",
                            "informServicesToInitializeBeforeBootComplete",
                            "declareBootCompleteStep",
                            "waveSynchronousLinearSequencerSucceededStep",
                            "waveSynchronousLinearSequencerFailedStep"
            };

        final WaveFrameworkInitializeWorkerStartServicesContext waveFrameworkInitializeWorkerStartServicesContext = new WaveFrameworkInitializeWorkerStartServicesContext ((WaveAsynchronousContext) null, this, sequencerSteps);

        waveFrameworkInitializeWorkerStartServicesContext.setWaveBootMode (waveBootMode);
        waveFrameworkInitializeWorkerStartServicesContext.setWaveBootPhase (waveBootPhase);

        waveFrameworkInitializeWorkerStartServicesContext.execute ();
    }

    private ResourceId determineNodeBootModeStep (final WaveFrameworkInitializeWorkerStartServicesContext waveFrameworkInitializeWorkerStartServicesContext)
    {
        infoTracePrintf ("WaveFrameworkObjectManagerInitializeWorker.determineNodeBootModeStep : Entering ...");

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId chooseABootAgentStep (final WaveFrameworkInitializeWorkerStartServicesContext waveFrameworkInitializeWorkerStartServicesContext)
    {
        infoTracePrintf ("WaveFrameworkObjectManagerInitializeWorker.chooseABootAgentStep : Entering ...");

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId runTheBootAgentStep (final WaveFrameworkInitializeWorkerStartServicesContext waveFrameworkInitializeWorkerStartServicesContext)
    {
        infoTracePrintf ("WaveFrameworkObjectManagerInitializeWorker.runTheBootAgentStep : Entering ...");

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId saveConfigurationStep (final WaveFrameworkInitializeWorkerStartServicesContext waveFrameworkInitializeWorkerStartServicesContext)
    {
        infoTracePrintf ("WaveFrameworkObjectManagerInitializeWorker.saveConfigurationStep : Entering ...");

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId informServicesToInitializeBeforeBootComplete (final WaveFrameworkInitializeWorkerStartServicesContext waveFrameworkInitializeWorkerStartServicesContext)
    {
        infoTracePrintf ("WaveFrameworkObjectManagerInitializeWorker.informServicesToInitializeBeforeBootComplete : Entering ...");

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId declareBootCompleteStep (final WaveFrameworkInitializeWorkerStartServicesContext waveFrameworkInitializeWorkerStartServicesContext)
    {
        infoTracePrintf ("WaveFrameworkObjectManagerInitializeWorker.declareBootCompleteStep : Entering ...");

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId waveSynchronousLinearSequencerSucceededStep (final WaveFrameworkInitializeWorkerStartServicesContext waveFrameworkInitializeWorkerStartServicesContext)
    {
        infoTracePrintf ("WaveFrameworkObjectManagerInitializeWorker.waveSynchronousLinearSequencerSucceededStep : Entering ...");

        return (super.waveSynchronousLinearSequencerSucceededStep (waveFrameworkInitializeWorkerStartServicesContext));
    }
}
