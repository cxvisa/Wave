/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Regression.Workers;

import java.lang.annotation.Annotation;
import java.util.Set;
import java.util.Vector;

import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorkerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.Cardinality;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.OwnerOM;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.WorkerPriority;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Source.WaveJavaSourceRepository;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Regression.RegressionTestEntry;
import com.CxWave.Wave.Regression.RegressionTestObjectManager;
import com.CxWave.Wave.Regression.WaveTestObjectManager;
import com.CxWave.Wave.Regression.Annotations.NonTestOM;
import com.CxWave.Wave.Regression.Contexts.RegressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext;
import com.CxWave.Wave.Regression.Messages.RegressionTestObjectManagerGetTestServiceEntriesMessage;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;

@OwnerOM (om = RegressionTestObjectManager.class)
@Cardinality (1)
@WorkerPriority (WaveWorkerPriority.WAVE_WORKER_PRIORITY_0)
public class RegressionTestObjectManagerGetTestServiceEntriesWorker extends WaveWorker
{
    public RegressionTestObjectManagerGetTestServiceEntriesWorker (final WaveObjectManager waveObjectManager)
    {
        super (waveObjectManager);
    }

    private void getTestServiceEntriesRequestHandler (final RegressionTestObjectManagerGetTestServiceEntriesMessage regressionTestObjectManagerGetTestServiceEntriesMessage)
    {
        develTracePrintf ("RegressionTestObjectManagerGetTestServiceEntriesWorker.getTestServiceEntriesRequestHandler : Entering ...");

        final String[] sequencerSteps =
            {
                            "getTestServiceEntriesComputeStep",
                            "getTestServiceEntriesSetOutputStep",
                            "waveLinearSequencerSucceededStep",
                            "waveLinearSequencerFailedStep"
            };

        final RegressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext regressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext = new RegressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext (regressionTestObjectManagerGetTestServiceEntriesMessage, this, sequencerSteps);

        waveAssert (null != regressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext);

        regressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext.start ();
    }

    private void getTestServiceEntriesComputeStep (final RegressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext regressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext)
    {
        develTracePrintf ("RegressionTestObjectManagerGetTestServiceEntriesWorker.getTestServiceEntriesComputeStep : Entering ...");

        final Set<String> allDescendantsOfWaveTestObjectManager = WaveJavaSourceRepository.getAllDescendantsForClass (WaveTestObjectManager.class.getName ());

        for (final String descendantOfWaveTestObjectManager : allDescendantsOfWaveTestObjectManager)
        {
            waveAssert (WaveStringUtils.isNotBlank (descendantOfWaveTestObjectManager));

            final Vector<Class<? extends Annotation>> excludingAnnotations = new Vector<Class<? extends Annotation>> ();

            excludingAnnotations.add (NonTestOM.class);

            final WaveObjectManager waveObjectManager = WaveObjectManager.getInstanceByClassNameIfSingleton (descendantOfWaveTestObjectManager, excludingAnnotations);

            waveAssert (null != waveObjectManager);

            final WaveTestObjectManager waveTestObjectManager = (WaveTestObjectManager) waveObjectManager;

            waveAssert (null != waveTestObjectManager);

            final WaveServiceId waveTestServiceId = waveTestObjectManager.getServiceId ();
            final boolean isTestEnabled = waveTestObjectManager.getIsTestEnabled ();

            regressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext.addTestService (waveTestServiceId, isTestEnabled);
        }

        regressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext.executeNextStep (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private void getTestServiceEntriesSetOutputStep (final RegressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext regressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext)
    {
        develTracePrintf ("RegressionTestObjectManagerGetTestServiceEntriesWorker.getTestServiceEntriesSetOutputStep : Entering ...");

        final Vector<WaveServiceId> testServiceIds = regressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext.getTestServiceIds ();
        final Vector<Boolean> testServiceStates = regressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext.getTestServiceStates ();

        final int numberOfTestServiceIds = testServiceIds.size ();
        final int numberOfTestServiceStates = testServiceStates.size ();

        waveAssert (numberOfTestServiceIds == numberOfTestServiceStates);

        final RegressionTestObjectManagerGetTestServiceEntriesMessage regressionTestObjectManagerGetTestServiceEntriesMessage = (RegressionTestObjectManagerGetTestServiceEntriesMessage) regressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext.getWaveMessage ();

        waveAssert (null != regressionTestObjectManagerGetTestServiceEntriesMessage);

        regressionTestObjectManagerGetTestServiceEntriesMessage.setNumberOfTestServiceEntries (new UI32 (numberOfTestServiceIds));

        for (int i = 0; i < numberOfTestServiceIds; i++)
        {
            regressionTestObjectManagerGetTestServiceEntriesMessage.addTestServiceEntry (new RegressionTestEntry (testServiceIds.get (i), testServiceStates.get (i)));
        }

        regressionTestObjectManagerGetTestServiceEntriesLinearSequencerContext.executeNextStep (ResourceId.WAVE_MESSAGE_SUCCESS);
    }
}
