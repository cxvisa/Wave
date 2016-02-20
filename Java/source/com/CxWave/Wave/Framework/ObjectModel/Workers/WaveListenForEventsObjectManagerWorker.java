/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel.Workers;

import java.util.Vector;

import com.CxWave.Wave.Framework.Core.Messages.WaveListenForEventsObjectManagerMessage;
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
public class WaveListenForEventsObjectManagerWorker extends WaveWorker
{
    public WaveListenForEventsObjectManagerWorker (final WaveObjectManager waveObjectManager)
    {
        super (waveObjectManager);
    }

    private void listenForEventsMessageHandler (final WaveListenForEventsObjectManagerMessage waveListenForEventsObjectManagerMessage)
    {
        infoTracePrintf ("WaveListenForEventsObjectManagerWorker.listenForEventsMessageHandler : Entering ... for OM %s: ", (getWaveObjectManager ()).getName ());

        final String[] sequencerSteps =
            {
                            "listenForEventsListenForEventsWorkersStep",
                            "listenForEventsListenForEventsSelfStep",
                            "waveLinearSequencerSucceededStep",
                            "waveLinearSequencerFailedStep"
            };

        final WaveLinearSequencerContext waveLinearSequencerContext = new WaveLinearSequencerContext (waveListenForEventsObjectManagerMessage, this, sequencerSteps);

        waveLinearSequencerContext.start ();
    }

    private void listenForEventsListenForEventsWorkersStep (final WaveLinearSequencerContext waveLinearSequencerContext)
    {
        infoTracePrintf ("WaveListenForEventsObjectManagerWorker.listenForEventsListenForEventsWorkersStep : Entering ...");

        final WaveListenForEventsObjectManagerMessage waveListenForEventsObjectManagerMessage = (WaveListenForEventsObjectManagerMessage) (waveLinearSequencerContext.getWaveMessage ());

        waveAssert (null != waveListenForEventsObjectManagerMessage);

        final Vector<WaveWorker> workers = m_waveObjectManager.getWorkers ();

        waveAssert (null != workers);

        final int numberOfWorkers = workers.size ();
        int i = 0;

        waveLinearSequencerContext.incrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

        for (i = 0; i < numberOfWorkers; i++)
        {
            final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases = new WaveAsynchronousContextForBootPhases (this, "listenForEventsListenForEventsWorkersStepCallback", waveLinearSequencerContext);

            waveAssert (null != waveAsynchronousContextForBootPhases);

            waveAsynchronousContextForBootPhases.setBootReason (waveListenForEventsObjectManagerMessage.getReason ());

            waveLinearSequencerContext.incrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

            waveAssert (null != (workers.get (i)));

            (workers.get (i)).listenForEvents (waveAsynchronousContextForBootPhases);
        }

        waveLinearSequencerContext.decrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

        waveLinearSequencerContext.executeNextStep (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private void listenForEventsListenForEventsWorkersStepCallback (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("WaveListenForEventsObjectManagerWorker.listenForEventsListenForEventsWorkersStepCallback : Entering ...");

        final WaveLinearSequencerContext waveLinearSequencerContext = (WaveLinearSequencerContext) (waveAsynchronousContextForBootPhases.getCallerContext ());

        waveAssert (null != waveLinearSequencerContext);

        ResourceId status = waveAsynchronousContextForBootPhases.getCompletionStatus ();

        waveLinearSequencerContext.decrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

        if (ResourceId.WAVE_MESSAGE_SUCCESS != status)
        {
            errorTracePrintf ("WaveListenForEventsObjectManagerWorker.listenForEventsListenForEventsWorkersStepCallback : Initializing one worker failed.");

            waveLinearSequencerContext.incrementNumberOfFailures ();
            // waveAssert (false);
        }

        if (0 != waveLinearSequencerContext.getNumberOfFailures ())
        {
            status = ResourceId.WAVE_MESSAGE_ERROR;
        }

        waveLinearSequencerContext.executeNextStep (status);
    }

    private void listenForEventsListenForEventsSelfStep (final WaveLinearSequencerContext waveLinearSequencerContext)
    {
        WaveTraceUtils.infoTracePrintf ("WaveListenForEventsObjectManagerWorker.listenForEventsListenForEventsSelfStep : Entering ...");

        final WaveListenForEventsObjectManagerMessage waveListenForEventsObjectManagerMessage = (WaveListenForEventsObjectManagerMessage) (waveLinearSequencerContext.getWaveMessage ());

        waveAssert (null != waveListenForEventsObjectManagerMessage);

        final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases = new WaveAsynchronousContextForBootPhases (this, "listenForEventsListenForEventsSelfStepCallback", waveLinearSequencerContext);

        waveAssert (null != waveAsynchronousContextForBootPhases);

        waveAsynchronousContextForBootPhases.setBootReason (waveListenForEventsObjectManagerMessage.getReason ());

        final WaveObjectManager waveObjectManager = getWaveObjectManager ();

        WaveAssertUtils.waveAssert (null != waveObjectManager);

        // First do the auto registration. C++ variant does not do this at present.

        waveObjectManager.listenForEventsDefaultImplementation ();

        // Second give a chance to add service specific events

        waveObjectManager.listenForEvents (waveAsynchronousContextForBootPhases);
    }

    private void listenForEventsListenForEventsSelfStepCallback (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("WaveListenForEventsObjectManagerWorker.listenForEventsListenForEventsSelfStepCallback : Entering ...");

        final WaveLinearSequencerContext waveLinearSequencerContext = (WaveLinearSequencerContext) (waveAsynchronousContextForBootPhases.getCallerContext ());

        waveAssert (null != waveLinearSequencerContext);

        final ResourceId status = waveAsynchronousContextForBootPhases.getCompletionStatus ();

        if (ResourceId.WAVE_MESSAGE_SUCCESS != status)
        {
            errorTracePrintf ("WaveListenForEventsObjectManagerWorker.listenForEventsListenForEventsSelfStepCallback : Initializing the Object Manager (self) failed.");
        }

        waveLinearSequencerContext.executeNextStep (status);
    }
}
