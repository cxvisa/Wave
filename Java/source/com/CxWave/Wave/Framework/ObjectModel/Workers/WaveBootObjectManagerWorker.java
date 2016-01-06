/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel.Workers;

import java.util.Vector;

import com.CxWave.Wave.Framework.Core.Messages.WaveBootObjectManagerMessage;
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
public class WaveBootObjectManagerWorker extends WaveWorker
{
    public WaveBootObjectManagerWorker (final WaveObjectManager waveObjectManager)
    {
        super (waveObjectManager);
    }

    private void bootMessageHandler (final WaveBootObjectManagerMessage waveBootObjectManagerMessage)
    {
        infoTracePrintf ("WaveBootObjectManagerWorker.bootMessageHandler : Entering ... for OM %s: ", (getWaveObjectManager ()).getName ());

        final String[] sequencerSteps =
            {
                            "bootBootWorkersStep",
                            "bootBootSelfStep",
                            "waveLinearSequencerSucceededStep",
                            "waveLinearSequencerFailedStep"
            };

        final WaveLinearSequencerContext waveLinearSequencerContext = new WaveLinearSequencerContext (waveBootObjectManagerMessage, this, sequencerSteps);

        waveLinearSequencerContext.start ();
    }

    private void bootBootWorkersStep (final WaveLinearSequencerContext waveLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootObjectManagerWorker.bootBootWorkersStep : Entering ...");

        final WaveBootObjectManagerMessage waveBootObjectManagerMessage = (WaveBootObjectManagerMessage) (waveLinearSequencerContext.getWaveMessage ());

        waveAssert (null != waveBootObjectManagerMessage);

        final Vector<WaveWorker> workers = m_waveObjectManager.getWorkers ();

        waveAssert (null != workers);

        final int numberOfWorkers = workers.size ();
        int i = 0;

        waveLinearSequencerContext.incrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

        for (i = 0; i < numberOfWorkers; i++)
        {
            final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases = new WaveAsynchronousContextForBootPhases (this, "bootBootWorkersStepCallback", waveLinearSequencerContext);

            waveAssert (null != waveAsynchronousContextForBootPhases);

            waveAsynchronousContextForBootPhases.setBootReason (waveBootObjectManagerMessage.getReason ());

            waveLinearSequencerContext.incrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

            waveAssert (null != (workers.get (i)));

            (workers.get (i)).boot (waveAsynchronousContextForBootPhases);
        }

        waveLinearSequencerContext.decrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

        waveLinearSequencerContext.executeNextStep (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private void bootBootWorkersStepCallback (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("WaveBootObjectManagerWorker.bootBootWorkersStepCallback : Entering ...");

        final WaveLinearSequencerContext waveLinearSequencerContext = (WaveLinearSequencerContext) (waveAsynchronousContextForBootPhases.getCallerContext ());

        waveAssert (null != waveLinearSequencerContext);

        ResourceId status = waveAsynchronousContextForBootPhases.getCompletionStatus ();

        waveLinearSequencerContext.decrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

        if (ResourceId.WAVE_MESSAGE_SUCCESS != status)
        {
            errorTracePrintf ("WaveBootObjectManagerWorker.bootBootWorkersStepCallback : Initializing one worker failed.");

            waveLinearSequencerContext.incrementNumberOfFailures ();
            // waveAssert (false);
        }

        if (0 != waveLinearSequencerContext.getNumberOfFailures ())
        {
            status = ResourceId.WAVE_MESSAGE_ERROR;
        }

        waveLinearSequencerContext.executeNextStep (status);
    }

    private void bootBootSelfStep (final WaveLinearSequencerContext waveLinearSequencerContext)
    {
        WaveTraceUtils.infoTracePrintf ("WaveBootObjectManagerWorker.bootBootSelfStep : Entering ...");

        final WaveBootObjectManagerMessage waveBootObjectManagerMessage = (WaveBootObjectManagerMessage) (waveLinearSequencerContext.getWaveMessage ());

        waveAssert (null != waveBootObjectManagerMessage);

        final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases = new WaveAsynchronousContextForBootPhases (this, "bootBootSelfStepCallback", waveLinearSequencerContext);

        waveAssert (null != waveAsynchronousContextForBootPhases);

        waveAsynchronousContextForBootPhases.setBootReason (waveBootObjectManagerMessage.getReason ());

        final WaveObjectManager waveObjectManager = getWaveObjectManager ();

        WaveAssertUtils.waveAssert (null != waveObjectManager);

        waveObjectManager.boot (waveAsynchronousContextForBootPhases);
    }

    private void bootBootSelfStepCallback (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("WaveBootObjectManagerWorker.bootBootSelfStepCallback : Entering ...");

        final WaveLinearSequencerContext waveLinearSequencerContext = (WaveLinearSequencerContext) (waveAsynchronousContextForBootPhases.getCallerContext ());

        waveAssert (null != waveLinearSequencerContext);

        final ResourceId status = waveAsynchronousContextForBootPhases.getCompletionStatus ();

        if (ResourceId.WAVE_MESSAGE_SUCCESS != status)
        {
            errorTracePrintf ("WaveBootObjectManagerWorker.bootBootSelfStepCallback : Initializing the Object Manager (self) failed.");
        }

        waveLinearSequencerContext.executeNextStep (status);
    }
}
