/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Regression.Workers;

import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Regression.Contexts.RegressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext;
import com.CxWave.Wave.Regression.Messages.RegressionTestObjectManagerGetTestServiceEntriesMessage;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;

public class RegressionTestObjectManagerGetTestServiceEntriesWorker extends WaveWorker
{
    public RegressionTestObjectManagerGetTestServiceEntriesWorker (final WaveObjectManager waveObjectManager)
    {
        super (waveObjectManager);
    }

    private void getTestServiceEntriesRequestHandler (final RegressionTestObjectManagerGetTestServiceEntriesMessage regressionTestObjectManagerGetTestServiceEntriesMessage)
    {
        infoTracePrintf ("RegressionTestObjectManagerGetTestServiceEntriesWorker.getTestServiceEntriesRequestHandler : Entering ...");

        final String[] sequencerSteps =
            {
                            "getTestServiceEntriesComputeStep",
                            "getTestServiceEntriesSetOutputStep",
                            "waveLinearSequencerSuceededStep",
                            "waveLinearSequencerFailedStep"
            };

        final RegressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext regressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext = new RegressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext (regressionTestObjectManagerGetTestServiceEntriesMessage, this, sequencerSteps);

        waveAssert (null != regressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext);

        regressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext.start ();
    }

    private void getTestServiceEntriesComputeStep (final RegressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext regressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext)
    {
        infoTracePrintf ("RegressionTestObjectManagerGetTestServiceEntriesWorker.getTestServiceEntriesComputeStep : Entering ...");

        regressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext.executeNextStep (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private void getTestServiceEntriesSetOutputStep (final RegressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext regressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext)
    {
        infoTracePrintf ("RegressionTestObjectManagerGetTestServiceEntriesWorker.getTestServiceEntriesSetOutputStep : Entering ...");

        regressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext.executeNextStep (ResourceId.WAVE_MESSAGE_SUCCESS);
    }
}
