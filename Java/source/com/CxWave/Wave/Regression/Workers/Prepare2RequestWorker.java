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
import com.CxWave.Wave.Regression.Contexts.RegressionPrepare2AsynchronousContext;
import com.CxWave.Wave.Regression.Messages.RegressionPrepare2Message;

@OwnerOM (om = WaveTestObjectManager.class)
@Cardinality (1)
@WorkerPriority (WaveWorkerPriority.WAVE_WORKER_PRIORITY_0)
public class Prepare2RequestWorker extends WaveWorker
{
    public Prepare2RequestWorker (final WaveObjectManager waveObjectManager)
    {
        super (waveObjectManager);
    }

    private void prepareRequestHandler (final RegressionPrepare2Message regressionPrepare2Message)
    {
        infoTracePrintf ("Prepare2RequestWorker.prepareRequestHandler : Entering ...");

        final String[] sequencerSteps =
            {
                            "prepareRequestHandlePrepare2Step",
                            "waveLinearSequencerSucceededStep",
                            "waveLinearSequencerFailedStep"
            };

        final WaveLinearSequencerContext waveLinearSequencerContext = new WaveLinearSequencerContext (regressionPrepare2Message, this, sequencerSteps);

        waveAssert (null != waveLinearSequencerContext);

        waveLinearSequencerContext.start ();
    }

    private void prepareRequestHandlePrepare2Step (final WaveLinearSequencerContext waveLinearSequencerContext)
    {
        infoTracePrintf ("Prepare2RequestWorker.prepareRequestHandlePrepare2Step : Entering ...");

        final WaveObjectManager waveObjectManager = getWaveObjectManager ();

        final WaveTestObjectManager waveTestObjectManager = (WaveTestObjectManager) waveObjectManager;

        waveAssert (null != waveTestObjectManager);

        final RegressionPrepare2AsynchronousContext regressionPrepare2AsynchronousContext = new RegressionPrepare2AsynchronousContext (this, "prepareRequestHandlePrepare2Callback", waveLinearSequencerContext);

        waveAssert (null != regressionPrepare2AsynchronousContext);

        final RegressionPrepare2Message regressionPrepare2Message = (RegressionPrepare2Message) waveLinearSequencerContext.getWaveMessage ();

        waveAssert (null != regressionPrepare2Message);

        regressionPrepare2AsynchronousContext.setInputStrings (regressionPrepare2Message.getInputStrings ());

        waveTestObjectManager.handlePrepare2Request (regressionPrepare2AsynchronousContext);
    }

    private void prepareRequestHandlePrepare2Callback (final RegressionPrepare2AsynchronousContext regressionPrepare2AsynchronousContext)
    {
        infoTracePrintf ("Prepare2RequestWorker.prepareRequestHandlePrepare2Callback : Entering ...");

        final WaveLinearSequencerContext waveLinearSequencerContext = (WaveLinearSequencerContext) regressionPrepare2AsynchronousContext.getCallerContext ();

        waveAssert (null != waveLinearSequencerContext);

        waveLinearSequencerContext.executeNextStep (regressionPrepare2AsynchronousContext.getCompletionStatus ());
        return;
    }
}
