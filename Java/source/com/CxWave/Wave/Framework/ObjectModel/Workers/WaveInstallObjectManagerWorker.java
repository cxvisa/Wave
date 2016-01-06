/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel.Workers;

import java.util.Vector;

import com.CxWave.Wave.Framework.Core.Messages.WaveInstallObjectManagerMessage;
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
public class WaveInstallObjectManagerWorker extends WaveWorker
{
    public WaveInstallObjectManagerWorker (final WaveObjectManager waveObjectManager)
    {
        super (waveObjectManager);
    }

    private void installMessageHandler (final WaveInstallObjectManagerMessage waveInstallObjectManagerMessage)
    {
        infoTracePrintf ("WaveInstallObjectManagerWorker.installMessageHandler : Entering ... for OM %s: ", (getWaveObjectManager ()).getName ());

        final String[] sequencerSteps =
            {
                            "installInstallWorkersStep",
                            "installInstallSelfStep",
                            "waveLinearSequencerSucceededStep",
                            "waveLinearSequencerFailedStep"
            };

        final WaveLinearSequencerContext waveLinearSequencerContext = new WaveLinearSequencerContext (waveInstallObjectManagerMessage, this, sequencerSteps);

        waveLinearSequencerContext.start ();
    }

    private void installInstallWorkersStep (final WaveLinearSequencerContext waveLinearSequencerContext)
    {
        infoTracePrintf ("WaveInstallObjectManagerWorker.installInstallWorkersStep : Entering ...");

        final WaveInstallObjectManagerMessage waveInstallObjectManagerMessage = (WaveInstallObjectManagerMessage) (waveLinearSequencerContext.getWaveMessage ());

        waveAssert (null != waveInstallObjectManagerMessage);

        final Vector<WaveWorker> workers = m_waveObjectManager.getWorkers ();

        waveAssert (null != workers);

        final int numberOfWorkers = workers.size ();
        int i = 0;

        waveLinearSequencerContext.incrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

        for (i = 0; i < numberOfWorkers; i++)
        {
            final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases = new WaveAsynchronousContextForBootPhases (this, "installInstallWorkersStepCallback", waveLinearSequencerContext);

            waveAssert (null != waveAsynchronousContextForBootPhases);

            waveAsynchronousContextForBootPhases.setBootReason (waveInstallObjectManagerMessage.getReason ());

            waveLinearSequencerContext.incrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

            waveAssert (null != (workers.get (i)));

            (workers.get (i)).install (waveAsynchronousContextForBootPhases);
        }

        waveLinearSequencerContext.decrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

        waveLinearSequencerContext.executeNextStep (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private void installInstallWorkersStepCallback (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("WaveInstallObjectManagerWorker.installInstallWorkersStepCallback : Entering ...");

        final WaveLinearSequencerContext waveLinearSequencerContext = (WaveLinearSequencerContext) (waveAsynchronousContextForBootPhases.getCallerContext ());

        waveAssert (null != waveLinearSequencerContext);

        ResourceId status = waveAsynchronousContextForBootPhases.getCompletionStatus ();

        waveLinearSequencerContext.decrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

        if (ResourceId.WAVE_MESSAGE_SUCCESS != status)
        {
            errorTracePrintf ("WaveInstallObjectManagerWorker.installInstallWorkersStepCallback : Initializing one worker failed.");

            waveLinearSequencerContext.incrementNumberOfFailures ();
            // waveAssert (false);
        }

        if (0 != waveLinearSequencerContext.getNumberOfFailures ())
        {
            status = ResourceId.WAVE_MESSAGE_ERROR;
        }

        waveLinearSequencerContext.executeNextStep (status);
    }

    private void installInstallSelfStep (final WaveLinearSequencerContext waveLinearSequencerContext)
    {
        WaveTraceUtils.infoTracePrintf ("WaveInstallObjectManagerWorker.installInstallSelfStep : Entering ...");

        final WaveInstallObjectManagerMessage waveInstallObjectManagerMessage = (WaveInstallObjectManagerMessage) (waveLinearSequencerContext.getWaveMessage ());

        waveAssert (null != waveInstallObjectManagerMessage);

        final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases = new WaveAsynchronousContextForBootPhases (this, "installInstallSelfStepCallback", waveLinearSequencerContext);

        waveAssert (null != waveAsynchronousContextForBootPhases);

        waveAsynchronousContextForBootPhases.setBootReason (waveInstallObjectManagerMessage.getReason ());

        final WaveObjectManager waveObjectManager = getWaveObjectManager ();

        WaveAssertUtils.waveAssert (null != waveObjectManager);

        waveObjectManager.install (waveAsynchronousContextForBootPhases);
    }

    private void installInstallSelfStepCallback (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("WaveInstallObjectManagerWorker.installInstallSelfStepCallback : Entering ...");

        final WaveLinearSequencerContext waveLinearSequencerContext = (WaveLinearSequencerContext) (waveAsynchronousContextForBootPhases.getCallerContext ());

        waveAssert (null != waveLinearSequencerContext);

        final ResourceId status = waveAsynchronousContextForBootPhases.getCompletionStatus ();

        if (ResourceId.WAVE_MESSAGE_SUCCESS != status)
        {
            errorTracePrintf ("WaveInstallObjectManagerWorker.installInstallSelfStepCallback : Initializing the Object Manager (self) failed.");
        }

        waveLinearSequencerContext.executeNextStep (status);
    }
}
