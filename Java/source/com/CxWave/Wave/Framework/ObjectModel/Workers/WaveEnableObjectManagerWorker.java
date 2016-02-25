/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel.Workers;

import java.util.Vector;

import com.CxWave.Wave.Framework.Core.Messages.WaveEnableObjectManagerMessage;
import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorkerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.Cardinality;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.OwnerOM;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.WorkerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Boot.WaveAsynchronousContextForBootPhases;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Sequencer.WaveLinearSequencerContext;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;

@OwnerOM (om = WaveObjectManager.class)
@Cardinality (1)
@WorkerPriority (WaveWorkerPriority.WAVE_WORKER_PRIORITY_0)
public class WaveEnableObjectManagerWorker extends WaveWorker
{
    public WaveEnableObjectManagerWorker (final WaveObjectManager waveObjectManager)
    {
        super (waveObjectManager);
    }

    private void enableMessageHandler (final WaveEnableObjectManagerMessage waveEnableObjectManagerMessage)
    {
        infoTracePrintf ("WaveEnableObjectManagerWorker.enableMessageHandler : Entering ... for OM %s: ", (getWaveObjectManager ()).getName ());

        final String[] sequencerSteps =
            {
                            "enableEnableWorkersStep",
                            "enableEnableSelfStep",
                            "waveLinearSequencerSucceededStep",
                            "waveLinearSequencerFailedStep"
            };

        final WaveLinearSequencerContext waveLinearSequencerContext = new WaveLinearSequencerContext (waveEnableObjectManagerMessage, this, sequencerSteps);

        waveLinearSequencerContext.start ();
    }

    private void enableEnableWorkersStep (final WaveLinearSequencerContext waveLinearSequencerContext)
    {
        infoTracePrintf ("WaveEnableObjectManagerWorker.enableEnableWorkersStep : Entering ...");

        final WaveEnableObjectManagerMessage waveEnableObjectManagerMessage = (WaveEnableObjectManagerMessage) (waveLinearSequencerContext.getWaveMessage ());

        waveAssert (null != waveEnableObjectManagerMessage);

        final Vector<WaveWorker> workers = m_waveObjectManager.getWorkers ();

        waveAssert (null != workers);

        final int numberOfWorkers = workers.size ();
        int i = 0;

        waveLinearSequencerContext.incrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

        for (i = 0; i < numberOfWorkers; i++)
        {
            final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases = new WaveAsynchronousContextForBootPhases (this, "enableEnableWorkersStepCallback", waveLinearSequencerContext);

            waveAssert (null != waveAsynchronousContextForBootPhases);

            waveAsynchronousContextForBootPhases.setBootReason (waveEnableObjectManagerMessage.getReason ());

            waveLinearSequencerContext.incrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

            waveAssert (null != (workers.get (i)));

            (workers.get (i)).enable (waveAsynchronousContextForBootPhases);
        }

        waveLinearSequencerContext.decrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

        waveLinearSequencerContext.executeNextStep (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private void enableEnableWorkersStepCallback (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("WaveEnableObjectManagerWorker.enableEnableWorkersStepCallback : Entering ...");

        final WaveLinearSequencerContext waveLinearSequencerContext = (WaveLinearSequencerContext) (waveAsynchronousContextForBootPhases.getCallerContext ());

        waveAssert (null != waveLinearSequencerContext);

        ResourceId status = waveAsynchronousContextForBootPhases.getCompletionStatus ();

        waveLinearSequencerContext.decrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

        if (ResourceId.WAVE_MESSAGE_SUCCESS != status)
        {
            errorTracePrintf ("WaveEnableObjectManagerWorker.enableEnableWorkersStepCallback : Initializing one worker failed.");

            waveLinearSequencerContext.incrementNumberOfFailures ();
            // waveAssert (false);
        }

        if (0 != waveLinearSequencerContext.getNumberOfFailures ())
        {
            status = ResourceId.WAVE_MESSAGE_ERROR;
        }

        waveLinearSequencerContext.executeNextStep (status);
    }

    private void enableEnableSelfStep (final WaveLinearSequencerContext waveLinearSequencerContext)
    {
        WaveTraceUtils.infoTracePrintf ("WaveEnableObjectManagerWorker.enableEnableSelfStep : Entering ...");

        final WaveEnableObjectManagerMessage waveEnableObjectManagerMessage = (WaveEnableObjectManagerMessage) (waveLinearSequencerContext.getWaveMessage ());

        waveAssert (null != waveEnableObjectManagerMessage);

        final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases = new WaveAsynchronousContextForBootPhases (this, "enableEnableSelfStepCallback", waveLinearSequencerContext);

        waveAssert (null != waveAsynchronousContextForBootPhases);

        waveAsynchronousContextForBootPhases.setBootReason (waveEnableObjectManagerMessage.getReason ());

        final WaveObjectManager waveObjectManager = getWaveObjectManager ();

        WaveAssertUtils.waveAssert (null != waveObjectManager);

        waveObjectManager.enable (waveAsynchronousContextForBootPhases);
    }

    private void enableEnableSelfStepCallback (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("WaveEnableObjectManagerWorker.enableEnableSelfStepCallback : Entering ...");

        final WaveLinearSequencerContext waveLinearSequencerContext = (WaveLinearSequencerContext) (waveAsynchronousContextForBootPhases.getCallerContext ());

        waveAssert (null != waveLinearSequencerContext);

        final ResourceId status = waveAsynchronousContextForBootPhases.getCompletionStatus ();

        if (ResourceId.WAVE_MESSAGE_SUCCESS != status)
        {
            errorTracePrintf ("WaveEnableObjectManagerWorker.enableEnableSelfStepCallback : Initializing the Object Manager (self) failed.");
        }
        else
        {
            // Indicate that now we are ready to accept Messages to provide services.

            setIsEnabled (true);

            // Add it to the services that are enabled.

            final WaveServiceId thisServiceId = getServiceId ();

            addServiceToEnabledServicesList (thisServiceId);
        }

        waveLinearSequencerContext.executeNextStep (status);
    }

    private void addServiceToEnabledServicesList (final WaveServiceId waveServiceId)
    {
        m_waveObjectManager.addServiceToEnabledServicesList (waveServiceId);
    }
}
