/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Timer.Test;

import com.CxWave.Wave.Framework.ObjectModel.WaveTimerExpirationHandler;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.ObjectManagerPriority;
import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
import com.CxWave.Wave.Framework.Type.TimerHandle;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Random.WaveRandomGenerator;
import com.CxWave.Wave.Regression.WaveTestObjectManager;
import com.CxWave.Wave.Regression.Contexts.RegressionTestAsynchronousContext;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.WaveObjectManagerPriority;

@ObjectManagerPriority (WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_TIMER_TEST)
public class TimerTestObjectManager extends WaveTestObjectManager
{
    private static TimerTestObjectManager s_TimerTestObjectManager = null;
    private static final int              s_numberOfOneTimeTimers  = 100000;

    public TimerTestObjectManager ()
    {
        super (getServiceName ());
    }

    public static String getServiceName ()
    {
        return ("Framwork Timer Test");
    }

    public static TimerTestObjectManager getInstance ()
    {
        if (null == s_TimerTestObjectManager)
        {
            s_TimerTestObjectManager = new TimerTestObjectManager ();
        }

        WaveAssertUtils.waveAssert (null != s_TimerTestObjectManager);

        return (s_TimerTestObjectManager);
    }

    public static WaveServiceId getWaveServiceId ()
    {
        return ((getInstance ()).getServiceId ());
    }

    @Override
    public void handleTestRequest (final RegressionTestAsynchronousContext regressionTestAsynchronousContext)
    {
        develTracePrintf ("TimerTestObjectManager.handleTestRequest : Entering ...");

        final String[] sequencerSteps =
            {
                            "oneTimeTimerAccuracyTestStep",
                            "waveLinearSequencerSucceededStep",
                            "waveLinearSequencerFailedStep"
            };

        final FrameworkTimerTestContext frameworkTimerTestContext = new FrameworkTimerTestContext (regressionTestAsynchronousContext, this, sequencerSteps);

        frameworkTimerTestContext.holdAll ();
        frameworkTimerTestContext.start ();
    }

    private void oneTimeTimerAccuracyTestStep (final FrameworkTimerTestContext frameworkTimerTestContext)
    {
        infoTracePrintf ("TimerTestObjectManager.oneTimeTimerAccuracyTestStep : Starting One Time Timer Test.");

        frameworkTimerTestContext.incrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

        int i = 0;

        for (i = 0; i < s_numberOfOneTimeTimers; i++)
        {
            final TimerHandle timerHandle = new TimerHandle ();
            int startTimeInterval = (WaveRandomGenerator.generate ()) % 10000;

            if (0 > startTimeInterval)
            {
                startTimeInterval *= -1;
            }

            startTimeInterval += 1;

            final ResourceId timerStatus = startTimer (timerHandle, startTimeInterval, new WaveTimerExpirationHandler ("oneTimeTimerCallback"), frameworkTimerTestContext);

            if (ResourceId.FRAMEWORK_SUCCESS != timerStatus)
            {
                errorTracePrintf ("TimerTestObjectManager.oneTimeTimerAccuracyTestStep : Failed to arm a timer : %s, startTimeInterval : %d", FrameworkToolKit.localize (timerStatus), startTimeInterval);

                frameworkTimerTestContext.incrementNumberOfFailures ();
            }
            else
            {
                frameworkTimerTestContext.incrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();
            }

            if (0 == ((i + 1) % 10000))
            {
                infoTracePrintf ("TimerTestObjectManager.oneTimeTimerAccuracyTestStep :     Finished arming %06d timers.", i + 1);
            }
        }

        infoTracePrintf ("TimerTestObjectManager.oneTimeTimerAccuracyTestStep :     Finished arming timers.");

        frameworkTimerTestContext.decrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

        frameworkTimerTestContext.executeNextStep (((frameworkTimerTestContext.getNumberOfFailures ()) > 0) ? ResourceId.WAVE_MESSAGE_ERROR : ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private void oneTimeTimerCallback (final TimerHandle timerHandle, final FrameworkTimerTestContext frameworkTimerTestContext)
    {
        frameworkTimerTestContext.decrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

        frameworkTimerTestContext.executeNextStep (((frameworkTimerTestContext.getNumberOfFailures ()) > 0) ? ResourceId.WAVE_MESSAGE_ERROR : ResourceId.WAVE_MESSAGE_SUCCESS);
    }
}
