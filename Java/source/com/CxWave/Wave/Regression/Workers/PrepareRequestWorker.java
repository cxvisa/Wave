/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Regression.Workers;

import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorkerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.Cardinality;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.OwnerOM;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.WorkerPriority;
import com.CxWave.Wave.Framework.Utils.Sequencer.WaveLinearSequencerContext;
import com.CxWave.Wave.Regression.WaveTestObjectManager;
import com.CxWave.Wave.Regression.Contexts.RegressionPrepareAsynchronousContext;
import com.CxWave.Wave.Regression.Messages.RegressionPrepareMessage;

@OwnerOM (om = WaveTestObjectManager.class)
@Cardinality (1)
@WorkerPriority (WaveWorkerPriority.WAVE_WORKER_PRIORITY_0)
public class PrepareRequestWorker extends WaveWorker
{
    public PrepareRequestWorker (final WaveObjectManager waveObjectManager)
    {
        super (waveObjectManager);
    }

    private void prepareRequestHandler (final RegressionPrepareMessage regressionPrepareMessage)
    {
        infoTracePrintf ("PrepareRequestWorker.prepareRequestHandler : Entering ...");

        final String[] sequencerSteps =
            {
                            "prepareRequestHandlePrepareStep",
                            "waveLinearSequencerSucceededStep",
                            "waveLinearSequencerFailedStep"
            };

        final WaveLinearSequencerContext waveLinearSequencerContext = new WaveLinearSequencerContext (regressionPrepareMessage, this, sequencerSteps);

        waveAssert (null != waveLinearSequencerContext);

        waveLinearSequencerContext.start ();
    }

    private void prepareRequestHandlePrepareStep (final WaveLinearSequencerContext waveLinearSequencerContext)
    {
        infoTracePrintf ("PrepareRequestWorker.prepareRequestHandlePrepareStep : Entering ...");

        final WaveObjectManager waveObjectManager = getWaveObjectManager ();

        final WaveTestObjectManager waveTestObjectManager = (WaveTestObjectManager) waveObjectManager;

        waveAssert (null != waveTestObjectManager);

        final RegressionPrepareAsynchronousContext regressionPrepareAsynchronousContext = new RegressionPrepareAsynchronousContext (this, "prepareRequestHandlePrepareCallback", waveLinearSequencerContext);

        waveAssert (null != regressionPrepareAsynchronousContext);

        final RegressionPrepareMessage regressionPrepareMessage = (RegressionPrepareMessage) waveLinearSequencerContext.getWaveMessage ();

        waveAssert (null != regressionPrepareMessage);

        regressionPrepareAsynchronousContext.setInputStrings (regressionPrepareMessage.getInputStrings ());

        waveTestObjectManager.handlePrepareRequest (regressionPrepareAsynchronousContext);
    }

    private void prepareRequestHandlePrepareCallback (final RegressionPrepareAsynchronousContext regressionPrepareAsynchronousContext)
    {
        infoTracePrintf ("PrepareRequestWorker.prepareRequestHandlePrepareCallback : Entering ...");

        final WaveLinearSequencerContext waveLinearSequencerContext = (WaveLinearSequencerContext) regressionPrepareAsynchronousContext.getCallerContext ();

        waveAssert (null != waveLinearSequencerContext);

        waveLinearSequencerContext.executeNextStep (regressionPrepareAsynchronousContext.getCompletionStatus ());
        return;
    }
}
