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
import com.CxWave.Wave.Regression.Contexts.RegressionTestAsynchronousContext;
import com.CxWave.Wave.Regression.Messages.RegressionTestMessage;

@OwnerOM (om = WaveTestObjectManager.class)
@Cardinality (1)
@WorkerPriority (WaveWorkerPriority.WAVE_WORKER_PRIORITY_0)
public class TestRequestWorker extends WaveWorker
{
    public TestRequestWorker (final WaveObjectManager waveObjectManager)
    {
        super (waveObjectManager);
    }

    private void testRequestHandler (final RegressionTestMessage regressionTestMessage)
    {
        // develTracePrintf ("TestRequestWorker.testRequestHandler : Entering ...");

        final String[] sequencerSteps =
            {
                            "testRequestHandleTestStep",
                            "waveLinearSequencerSucceededStep",
                            "waveLinearSequencerFailedStep"
            };

        final WaveLinearSequencerContext waveLinearSequencerContext = new WaveLinearSequencerContext (regressionTestMessage, this, sequencerSteps);

        waveAssert (null != waveLinearSequencerContext);

        waveLinearSequencerContext.start ();
    }

    private void testRequestHandleTestStep (final WaveLinearSequencerContext waveLinearSequencerContext)
    {
        // develTracePrintf ("TestRequestWorker.testRequestHandleTestStep : Entering ...");

        final WaveObjectManager waveObjectManager = getWaveObjectManager ();

        final WaveTestObjectManager waveTestObjectManager = (WaveTestObjectManager) waveObjectManager;

        waveAssert (null != waveTestObjectManager);

        final RegressionTestAsynchronousContext regressionTestAsynchronousContext = new RegressionTestAsynchronousContext (this, "testRequestHandleTestCallback", waveLinearSequencerContext);

        waveAssert (null != regressionTestAsynchronousContext);

        waveTestObjectManager.handleTestRequest (regressionTestAsynchronousContext);
    }

    private void testRequestHandleTestCallback (final RegressionTestAsynchronousContext regressionTestAsynchronousContext)
    {
        // develTracePrintf ("TestRequestWorker.testRequestHandleTestCallback : Entering ...");

        final WaveLinearSequencerContext waveLinearSequencerContext = (WaveLinearSequencerContext) regressionTestAsynchronousContext.getCallerContext ();

        waveAssert (null != waveLinearSequencerContext);

        waveLinearSequencerContext.executeNextStep (regressionTestAsynchronousContext.getCompletionStatus ());
        return;
    }
}
