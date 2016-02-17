/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Test;

import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveTimerExpirationHandler;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NativeService;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.ObjectManagerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Boot.WaveAsynchronousContextForBootPhases;
import com.CxWave.Wave.Framework.Type.TimerHandle;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.WaveObjectManagerPriority;

@NativeService
@ObjectManagerPriority (WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_FRAMEWORK_TESTABILITY3)
public class FrameworkTestability3ObjectManager extends WaveObjectManager
{
    private static FrameworkTestability3ObjectManager s_frameworkTestability3ObjectManager = null;

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

        final ResourceId status = startTimer (timerHandle, 5000, new WaveTimerExpirationHandler ("timerExpirationCallbak"), waveAsynchronousContextForBootPhases, this);

        if (ResourceId.FRAMEWORK_SUCCESS != status)
        {
            errorTracePrintf ("FrameworkTestability3ObjectManager.boot : Failed to arm a timer ...");

            waveAsynchronousContextForBootPhases.setCompletionStatus (status);
            waveAsynchronousContextForBootPhases.callback ();
        }
        else
        {
            successTracePrintf ("FrameworkTestability3ObjectManager.boot : Armed a timer with id : %s", timerHandle.toString ());
        }
    }

    private void timerExpirationCallbak (final TimerHandle timerHandle, final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("FrameworkTestability3ObjectManager.timerExpirationCallbak : Entering ...");

        waveAsynchronousContextForBootPhases.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        waveAsynchronousContextForBootPhases.callback ();
    }
}
