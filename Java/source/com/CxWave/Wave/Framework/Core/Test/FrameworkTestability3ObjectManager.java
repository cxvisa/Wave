/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Test;

import com.CxWave.Wave.Framework.Boot.BootCompleteForThisLocationEvent;
import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveTimerExpirationHandler;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NativeService;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.ObjectManagerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Boot.WaveAsynchronousContextForBootPhases;
import com.CxWave.Wave.Framework.Timer.TimerWorker;
import com.CxWave.Wave.Framework.Type.TimeValue;
import com.CxWave.Wave.Framework.Type.TimerHandle;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.WaveObjectManagerPriority;

@NativeService
@ObjectManagerPriority (WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_FRAMEWORK_TESTABILITY3)
public class FrameworkTestability3ObjectManager extends WaveObjectManager
{
    private static FrameworkTestability3ObjectManager s_frameworkTestability3ObjectManager    = null;
    private static int                                s_numberOfPeriodicTimerCallbackReceived = 0;

    protected FrameworkTestability3ObjectManager ()
    {
        super (getServiceName ());
    }

    public static String getServiceName ()
    {
        return ("Framework Testability3");
    }

    public static FrameworkTestability3ObjectManager getInstance ()
    {
        if (null == s_frameworkTestability3ObjectManager)
        {
            s_frameworkTestability3ObjectManager = new FrameworkTestability3ObjectManager ();
        }

        WaveAssertUtils.waveAssert (null != s_frameworkTestability3ObjectManager);

        return (s_frameworkTestability3ObjectManager);
    }

    public static WaveServiceId getWaveServiceId ()
    {
        return ((getInstance ()).getServiceId ());
    }

    @Override
    public void boot (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("FrameworkTestability3ObjectManager.boot : Entering ...");

        final TimerHandle timerHandle = new TimerHandle ();

        final ResourceId status = startTimer (timerHandle, 5000, new WaveTimerExpirationHandler ("timerExpirationCallback"), waveAsynchronousContextForBootPhases, this);

        if (ResourceId.FRAMEWORK_SUCCESS != status)
        {
            errorTracePrintf ("FrameworkTestability3ObjectManager.boot : Failed to arm a timer ...");

            waveAsynchronousContextForBootPhases.setCompletionStatus (status);
            waveAsynchronousContextForBootPhases.callback ();

            return;
        }
        else
        {
            successTracePrintf ("FrameworkTestability3ObjectManager.boot : Armed a timer with id : %s", timerHandle.toString ());
        }

        final TimerHandle timerHandle2 = new TimerHandle ();

        final ResourceId status2 = startTimer (timerHandle2, 7000, 2000, new WaveTimerExpirationHandler ("timerExpirationCallback2"), null, this);

        if (ResourceId.FRAMEWORK_SUCCESS != status2)
        {
            errorTracePrintf ("FrameworkTestability3ObjectManager.boot : Failed to arm a periodic timer ...");

            waveAsynchronousContextForBootPhases.setCompletionStatus (status);
            waveAsynchronousContextForBootPhases.callback ();

            return;
        }
        else
        {
            successTracePrintf ("FrameworkTestability3ObjectManager.boot : Armed a timer with id : %s", timerHandle2.toString ());
        }
    }

    private void timerExpirationCallback (final TimerHandle timerHandle, final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("FrameworkTestability3ObjectManager.timerExpirationCallback : Entering ...");

        waveAsynchronousContextForBootPhases.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        waveAsynchronousContextForBootPhases.callback ();
    }

    private void timerExpirationCallback2 (final TimerHandle timerHandle, final Object object)
    {
        infoTracePrintf ("FrameworkTestability3ObjectManager.timerExpirationCallback2 : Entering for Timer Handle %s", timerHandle.toString ());

        s_numberOfPeriodicTimerCallbackReceived++;

        if (100 == s_numberOfPeriodicTimerCallbackReceived)
        {
            deleteTimer (timerHandle);
        }

        final TimeValue tempCurrentTime = new TimeValue ();

        tempCurrentTime.resetToCurrent ();
        infoTracePrintf ("FrameworkTestability3ObjectManager.timerExpirationCallback : current-time : %s", tempCurrentTime.toString ());
        TimerWorker.showMaxDelay ();
    }

    private void bootCompleteEventHandler (final BootCompleteForThisLocationEvent bootCompleteForThisLocationEvent)
    {
        infoTracePrintf ("FrameworkTestability3ObjectManager.bootCompleteEventHandler : Entering ...");
    }
}
