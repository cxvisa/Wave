/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Boot;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Framework.Utils.Sequencer.WaveSynchronousLinearSequencerContext;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;

public class WaveBootAgent extends WaveWorker
{
    public WaveBootAgent (final WaveObjectManager waveObjectManager)
    {
        super (waveObjectManager);
    }

    public ResourceId execute (final WaveBootPhase waveBootPhase)
    {
        infoTracePrintf ("WaveBootAgent.execute : Entering ...");

        final String[] synchronousSequencerSteps =
            {
                            "initializeWaveServicesDuringPrePhaseStep",
                            "enableWaveServicesDuringPrePhaseStep",
                            "listenForEventsWaveServicesDuringPrePhaseStep",
                            "installWaveServicesDuringPrePhaseStep",
                            "bootWaveServicesDuringPrePhaseStep",

                            "initializeLocalWaveServicesStep",
                            "enableLocalWaveServicesStep",
                            "listenForEventsLocalWaveServicesStep",
                            "installLocalWaveServicesStep",
                            "bootLocalWaveServicesStep",

                            "initializeGlobalWaveServicesStep",
                            "enableGlobalWaveServicesStep",
                            "listenForEventsGlobalWaveServicesStep",
                            "installGlobalWaveServicesStep",
                            "bootGlobalWaveServicesStep",

                            "waveSynchronousLinearSequencerSucceededStep",
                            "waveSynchronousLinearSequencerFailedStep"
            };

        final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext = new WaveSynchronousLinearSequencerContext ((WaveMessage) null, this, synchronousSequencerSteps);

        final ResourceId status = waveSynchronousLinearSequencerContext.execute ();

        return (status);
    }

    private ResourceId initializeWaveServicesDuringPrePhaseStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.initializeWaveServicesDuringPrePhaseStep : Entering ...");

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId enableWaveServicesDuringPrePhaseStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.enableWaveServicesDuringPrePhaseStep : Entering ...");

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId listenForEventsWaveServicesDuringPrePhaseStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.enableWaveServicesDuringPrePhaseStep : Entering ...");

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId installWaveServicesDuringPrePhaseStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.installWaveServicesDuringPrePhaseStep : Entering ...");

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId bootWaveServicesDuringPrePhaseStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.bootWaveServicesDuringPrePhaseStep : Entering ...");

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId initializeLocalWaveServicesStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.initializeLocalWaveServicesStep : Entering ...");

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId enableLocalWaveServicesStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.enableLocalWaveServicesStep : Entering ...");

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId listenForEventsLocalWaveServicesStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.listenForEventsLocalWaveServicesStep : Entering ...");

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId installLocalWaveServicesStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.installLocalWaveServicesStep : Entering ...");

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId bootLocalWaveServicesStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.bootLocalWaveServicesStep : Entering ...");

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId initializeGlobalWaveServicesStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.initializeGlobalWaveServicesStep : Entering ...");

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId enableGlobalWaveServicesStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.enableGlobalWaveServicesStep : Entering ...");

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId listenForEventsGlobalWaveServicesStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.listenForEventsGlobalWaveServicesStep : Entering ...");

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId installGlobalWaveServicesStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.installGlobalWaveServicesStep : Entering ...");

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId bootGlobalWaveServicesStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.bootGlobalWaveServicesStep : Entering ...");

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }
}
