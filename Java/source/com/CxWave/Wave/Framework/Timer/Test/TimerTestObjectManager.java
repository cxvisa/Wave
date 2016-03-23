/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Timer.Test;

import com.CxWave.Wave.Framework.ObjectModel.WaveTimerExpirationHandler;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.ObjectManagerPriority;
import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
import com.CxWave.Wave.Framework.Type.TimeValue;
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
    private static final int              s_numberOfPeriodicTimers = 1000;

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
                            // "oneTimeTimerAccuracyTestStep",
                            // "oneTimeTimerAccuracyWithTimeValueTestStep",
                            "periodicTimerAccuracyWithTimeValueTestStep", "waveLinearSequencerSucceededStep", "waveLinearSequencerFailedStep"
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

    private void oneTimeTimerAccuracyWithTimeValueTestStep (final FrameworkTimerTestContext frameworkTimerTestContext)
    {
        infoTracePrintf ("TimerTestObjectManager.oneTimeTimerAccuracyWithTimeValueTestStep : Starting One Time Timer with TimeValue Test.");

        frameworkTimerTestContext.incrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

        int i = 0;

        for (i = 0; i < s_numberOfOneTimeTimers; i++)
        {
            final TimerHandle timerHandle = new TimerHandle ();
            int startTimeIntervalMillis = (WaveRandomGenerator.generate ()) % 10000;
            int startTimeIntervalNanos = (WaveRandomGenerator.generate ()) % TimeValue.NANOS_IN_MILLI;

            if (0 > startTimeIntervalMillis)
            {
                startTimeIntervalMillis = Math.abs (startTimeIntervalMillis);
            }

            startTimeIntervalMillis += 1;

            if (0 > startTimeIntervalNanos)
            {
                startTimeIntervalNanos = Math.abs (startTimeIntervalNanos);
            }

            final TimerTestData timerTestData = new TimerTestData ();

            final TimeValue startTimeValue = new TimeValue ();

            startTimeValue.resetToCurrent ();

            final TimeValue startInterval = new TimeValue (startTimeIntervalMillis, startTimeIntervalNanos);
            final TimeValue expirationTime = new TimeValue (startTimeValue);

            expirationTime.add (startInterval);

            timerTestData.setStartTime (startTimeValue);
            timerTestData.setStartInterval (startInterval);
            timerTestData.setExpirationTime (expirationTime);
            timerTestData.setFrameworkTimerTestContext (frameworkTimerTestContext);

            final ResourceId timerStatus = startTimer (timerHandle, startInterval, new WaveTimerExpirationHandler ("oneTimeTimerWithTimeValueCallback"), timerTestData);

            if (ResourceId.FRAMEWORK_SUCCESS != timerStatus)
            {
                errorTracePrintf ("TimerTestObjectManager.oneTimeTimerAccuracyTestStep : Failed to arm a timer : %s, startTimeInterval : %s", FrameworkToolKit.localize (timerStatus), startInterval.toString ());

                frameworkTimerTestContext.incrementNumberOfFailures ();
            }
            else
            {
                frameworkTimerTestContext.incrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();
            }

            if (0 == ((i + 1) % 10000))
            {
                infoTracePrintf ("TimerTestObjectManager.oneTimeTimerAccuracyWithTimeValueTestStep :     Finished arming %06d timers.", i + 1);
            }
        }

        infoTracePrintf ("TimerTestObjectManager.oneTimeTimerAccuracyWithTimeValueTestStep :     Finished arming timers.");

        frameworkTimerTestContext.decrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

        frameworkTimerTestContext.executeNextStep (((frameworkTimerTestContext.getNumberOfFailures ()) > 0) ? ResourceId.WAVE_MESSAGE_ERROR : ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private void oneTimeTimerWithTimeValueCallback (final TimerHandle timerHandle, final TimerTestData timerTestData)
    {
        final FrameworkTimerTestContext frameworkTimerTestContext = timerTestData.getFrameworkTimerTestContext ();

        waveAssert (null != frameworkTimerTestContext);

        frameworkTimerTestContext.decrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

        frameworkTimerTestContext.executeNextStep (((frameworkTimerTestContext.getNumberOfFailures ()) > 0) ? ResourceId.WAVE_MESSAGE_ERROR : ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private void periodicTimerAccuracyWithTimeValueTestStep (final FrameworkTimerTestContext frameworkTimerTestContext)
    {
        infoTracePrintf ("TimerTestObjectManager.oneTimeTimerAccuracyWithTimeValueTestStep : Starting Periodic Timer with TimeValue Test.");

        frameworkTimerTestContext.incrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

        int i = 0;

        for (i = 0; i < s_numberOfPeriodicTimers; i++)
        {
            final TimerHandle timerHandle = new TimerHandle ();
            int startTimeIntervalMillis = (WaveRandomGenerator.generate ()) % 10000;
            int startTimeIntervalNanos = (WaveRandomGenerator.generate ()) % TimeValue.NANOS_IN_MILLI;
            int periodicTimeIntervalMillis = (WaveRandomGenerator.generate ()) % 1000;
            int periodicTimeIntervalNanos = (WaveRandomGenerator.generate ()) % TimeValue.NANOS_IN_MILLI;
            int nTimes = (WaveRandomGenerator.generate ()) % 10;

            if (0 > startTimeIntervalMillis)
            {
                startTimeIntervalMillis = Math.abs (startTimeIntervalMillis);
            }

            startTimeIntervalMillis += 1;

            if (0 > startTimeIntervalNanos)
            {
                startTimeIntervalNanos = Math.abs (startTimeIntervalNanos);
            }

            if (0 > periodicTimeIntervalMillis)
            {
                periodicTimeIntervalMillis = Math.abs (periodicTimeIntervalMillis);
            }

            periodicTimeIntervalMillis += 1;

            if (0 > periodicTimeIntervalNanos)
            {
                periodicTimeIntervalNanos = Math.abs (periodicTimeIntervalNanos);
            }

            if (0 > nTimes)
            {
                nTimes = Math.abs (nTimes);
            }

            nTimes += 1;

            final TimerTestData timerTestData = new TimerTestData ();

            final TimeValue startTimeValue = new TimeValue ();

            startTimeValue.resetToCurrent ();

            final TimeValue startInterval = new TimeValue (startTimeIntervalMillis, startTimeIntervalNanos);
            final TimeValue periodicInterval = new TimeValue (periodicTimeIntervalMillis, periodicTimeIntervalNanos);
            final TimeValue expirationTime = new TimeValue (startTimeValue);

            expirationTime.add (startInterval);

            timerTestData.setStartTime (startTimeValue);
            timerTestData.setPeriodicInterval (periodicInterval);
            timerTestData.setStartInterval (startInterval);
            timerTestData.setExpirationTime (expirationTime);
            timerTestData.setFrameworkTimerTestContext (frameworkTimerTestContext);
            timerTestData.setNTimes (nTimes);

            final ResourceId timerStatus = startTimer (timerHandle, startInterval, periodicInterval, new WaveTimerExpirationHandler ("periodicTimerWithTimeValueCallback"), timerTestData);

            if (ResourceId.FRAMEWORK_SUCCESS != timerStatus)
            {
                errorTracePrintf ("TimerTestObjectManager.periodicTimerAccuracyWithTimeValueTestStep : Failed to arm a timer : %s, startTimeInterval : %s, periodicInterval : %s", FrameworkToolKit.localize (timerStatus), startInterval.toString (), periodicInterval.toString ());

                frameworkTimerTestContext.incrementNumberOfFailures ();
            }
            else
            {
                frameworkTimerTestContext.incrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();
            }

            if (0 == ((i + 1) % 100))
            {
                infoTracePrintf ("TimerTestObjectManager.periodicTimerAccuracyWithTimeValueTestStep :     Finished arming %06d timers.", i + 1);
            }
        }

        infoTracePrintf ("TimerTestObjectManager.periodicTimerAccuracyWithTimeValueTestStep :     Finished arming timers.");

        frameworkTimerTestContext.decrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

        frameworkTimerTestContext.executeNextStep (((frameworkTimerTestContext.getNumberOfFailures ()) > 0) ? ResourceId.WAVE_MESSAGE_ERROR : ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private void periodicTimerWithTimeValueCallback (final TimerHandle timerHandle, final TimerTestData timerTestData)
    {
        // infoTracePrintf ("TimerTestObjectManager.periodicTimerWithTimeValueCallback : Entering for Timer Handle : %s",
        // timerHandle.toString ());

        final FrameworkTimerTestContext frameworkTimerTestContext = timerTestData.getFrameworkTimerTestContext ();

        waveAssert (null != frameworkTimerTestContext);

        int nTimes = timerTestData.getNTimes ();

        nTimes--;

        timerTestData.setNTimes (nTimes);

        if (0 == nTimes)
        {
            // infoTracePrintf ("TimerTestObjectManager.periodicTimerWithTimeValueCallback : Deleting for Timer Handle : %s",
            // timerHandle.toString ());

            final ResourceId timerStatus = deleteTimer (timerHandle);

            if (ResourceId.FRAMEWORK_SUCCESS != timerStatus)
            {
                fatalTracePrintf ("TimerTestObjectManager.periodicTimerWithTimeValueCallback : Could not delete a periodic timer.  Status : %s", FrameworkToolKit.localize (timerStatus));
                waveAssert ();
            }

            frameworkTimerTestContext.decrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();
        }

        frameworkTimerTestContext.executeNextStep (((frameworkTimerTestContext.getNumberOfFailures ()) > 0) ? ResourceId.WAVE_MESSAGE_ERROR : ResourceId.WAVE_MESSAGE_SUCCESS);
    }
}
