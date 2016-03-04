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
import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Regression.RegressionTestObjectManager;
import com.CxWave.Wave.Regression.Contexts.RegressionTestObjectManagerRunTestForAServiceLinearSequencerContext;
import com.CxWave.Wave.Regression.Messages.RegressionTestMessage;
import com.CxWave.Wave.Regression.Messages.RegressionTestObjectManagerRunTestForAServiceMessage;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.WaveMessageStatus;

@OwnerOM (om = RegressionTestObjectManager.class)
@Cardinality (1)
@WorkerPriority (WaveWorkerPriority.WAVE_WORKER_PRIORITY_0)
public class RegressionTestObjectManagerRunTestForAServiceWorker extends WaveWorker
{
    public RegressionTestObjectManagerRunTestForAServiceWorker (final WaveObjectManager waveObjectManager)
    {
        super (waveObjectManager);
    }

    private void runTestForAServiceRequestHandler (final RegressionTestObjectManagerRunTestForAServiceMessage regressionTestObjectManagerRunTestForAServiceMessage)
    {
        develTracePrintf ("RegressionTestObjectManagerRunTestForAServiceWorker.runTestForAServiceRequestHandler : Entering ...");

        final String[] sequencerSteps =
            {
                            "runTestForAServiceComputeStep",
                            "runTestForAServiceSetOutputStep",
                            "waveLinearSequencerSucceededStep",
                            "waveLinearSequencerFailedStep"
            };

        final RegressionTestObjectManagerRunTestForAServiceLinearSequencerContext regressionTestObjectManagerRunTestForAServiceLinearSequencerContext = new RegressionTestObjectManagerRunTestForAServiceLinearSequencerContext (regressionTestObjectManagerRunTestForAServiceMessage, this, sequencerSteps);

        waveAssert (null != regressionTestObjectManagerRunTestForAServiceLinearSequencerContext);

        regressionTestObjectManagerRunTestForAServiceLinearSequencerContext.start ();
    }

    private void runTestForAServiceComputeStep (final RegressionTestObjectManagerRunTestForAServiceLinearSequencerContext regressionTestObjectManagerRunTestForAServiceLinearSequencerContext)
    {
        develTracePrintf ("RegressionTestObjectManagerRunTestForAServiceWorker.runTestForAServiceComputeStep : Entering ...");

        final RegressionTestObjectManagerRunTestForAServiceMessage regressionTestObjectManagerRunTestForAServiceMessage = (RegressionTestObjectManagerRunTestForAServiceMessage) (regressionTestObjectManagerRunTestForAServiceLinearSequencerContext.getWaveMessage ());

        final WaveServiceId testServiceId = regressionTestObjectManagerRunTestForAServiceMessage.getTestServiceCode ();
        final int numberOfIterations = ((regressionTestObjectManagerRunTestForAServiceMessage.getNumberOfTimesToRunServiceTest ()).getValue ()).intValue ();
        final String testServiceName = FrameworkToolKit.getServiceNameById (testServiceId);

        for (int i = 0; i < numberOfIterations; i++)
        {
            final RegressionTestMessage regressionTestMessage = new RegressionTestMessage (testServiceId);

            final WaveMessageStatus sendStatus = sendSynchronously (regressionTestMessage);

            if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS == sendStatus)
            {
                final ResourceId completionStatus = regressionTestMessage.getCompletionStatus ();

                if (ResourceId.WAVE_MESSAGE_SUCCESS == completionStatus)
                {
                    successTracePrintf ("Succeeded to run regression for Service %s, iteration %d.", testServiceName, i);
                }
                else
                {
                    errorTracePrintf ("Failed to run regression for Service %s, iteration %d, Completion Status : %s.", testServiceName, i, FrameworkToolKit.localize (completionStatus));
                }
            }
            else
            {
                errorTracePrintf ("Failed to run regression for Service %s, Send Status : %s.", testServiceName, i, FrameworkToolKit.localize (sendStatus));
            }
        }

        regressionTestObjectManagerRunTestForAServiceLinearSequencerContext.executeNextStep (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private void runTestForAServiceSetOutputStep (final RegressionTestObjectManagerRunTestForAServiceLinearSequencerContext regressionTestObjectManagerRunTestForAServiceLinearSequencerContext)
    {
        develTracePrintf ("RegressionTestObjectManagerRunTestForAServiceWorker.runTestForAServiceSetOutputStep : Entering ...");

        regressionTestObjectManagerRunTestForAServiceLinearSequencerContext.executeNextStep (ResourceId.WAVE_MESSAGE_SUCCESS);
    }
}
