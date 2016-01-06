/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel.Workers;

import java.util.Vector;

import com.CxWave.Wave.Framework.Core.Messages.WaveInitializeObjectManagerMessage;
import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorkerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.Cardinality;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.OwnerOM;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.WorkerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Boot.WaveAsynchronousContextForBootPhases;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
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
        infoTracePrintf ("WaveInitializeObjectManagerWorker.initializeInitializeWorkersStep : Entering ...");

        final WaveInitializeObjectManagerMessage waveInitializeObjectManagerMessage = (WaveInitializeObjectManagerMessage) (waveLinearSequencerContext.getWaveMessage ());

        waveAssert (null != waveInitializeObjectManagerMessage);

        final Vector<WaveWorker> workers = m_waveObjectManager.getWorkers ();

        waveAssert (null != workers);

        final int numberOfWorkers = workers.size ();
        int i = 0;

        waveLinearSequencerContext.incrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

        for (i = 0; i < numberOfWorkers; i++)
        {
            final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases = new WaveAsynchronousContextForBootPhases (this, "initializeInitializeWorkersStepCallback", waveLinearSequencerContext);

            waveAssert (null != waveAsynchronousContextForBootPhases);

            waveAsynchronousContextForBootPhases.setBootReason (waveInitializeObjectManagerMessage.getReason ());

            waveLinearSequencerContext.incrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

            waveAssert (null != (workers.get (i)));

            (workers.get (i)).initialize (waveAsynchronousContextForBootPhases);
        }

        waveLinearSequencerContext.decrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

        waveLinearSequencerContext.executeNextStep (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private void initializeInitializeWorkersStepCallback (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("WaveInitializeObjectManagerWorker.initializeInitializeWorkersStepCallback : Entering ...");

        final WaveLinearSequencerContext waveLinearSequencerContext = (WaveLinearSequencerContext) (waveAsynchronousContextForBootPhases.getCallerContext ());

        waveAssert (null != waveLinearSequencerContext);

        ResourceId status = waveAsynchronousContextForBootPhases.getCompletionStatus ();

        waveLinearSequencerContext.decrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

        if (ResourceId.WAVE_MESSAGE_SUCCESS != status)
        {
            errorTracePrintf ("WaveInitializeObjectManagerWorker.initializeInitializeWorkersStepCallback : Initializing one worker failed.");

            waveLinearSequencerContext.incrementNumberOfFailures ();
            // waveAssert (false);
        }

        if (0 != waveLinearSequencerContext.getNumberOfFailures ())
        {
            status = ResourceId.WAVE_MESSAGE_ERROR;
        }

        waveLinearSequencerContext.executeNextStep (status);
    }

    private void initializeInitializeSelfStep (final WaveLinearSequencerContext waveLinearSequencerContext)
    {
        WaveTraceUtils.infoTracePrintf ("WaveInitializeObjectManagerWorker.initializeInitializeSelfStep : Entering ...");

        final WaveInitializeObjectManagerMessage waveInitializeObjectManagerMessage = (WaveInitializeObjectManagerMessage) (waveLinearSequencerContext.getWaveMessage ());

        waveAssert (null != waveInitializeObjectManagerMessage);

        final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases = new WaveAsynchronousContextForBootPhases (this, "initializeInitializeSelfStepCallback", waveLinearSequencerContext);

        waveAssert (null != waveAsynchronousContextForBootPhases);

        waveAsynchronousContextForBootPhases.setBootReason (waveInitializeObjectManagerMessage.getReason ());

        final WaveObjectManager waveObjectManager = getWaveObjectManager ();

        WaveAssertUtils.waveAssert (null != waveObjectManager);

        waveObjectManager.initialize (waveAsynchronousContextForBootPhases);
    }

    private void initializeInitializeSelfStepCallback (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("WaveInitializeObjectManagerWorker.initializeInitializeSelfStepCallback : Entering ...");

        final WaveLinearSequencerContext waveLinearSequencerContext = (WaveLinearSequencerContext) (waveAsynchronousContextForBootPhases.getCallerContext ());

        waveAssert (null != waveLinearSequencerContext);

        final ResourceId status = waveAsynchronousContextForBootPhases.getCompletionStatus ();

        if (ResourceId.WAVE_MESSAGE_SUCCESS != status)
        {
            errorTracePrintf ("WaveInitializeObjectManagerWorker.initializeInitializeSelfStepCallback : Initializing the Object Manager (self) failed.");
        }

        waveLinearSequencerContext.executeNextStep (status);
    }
}
