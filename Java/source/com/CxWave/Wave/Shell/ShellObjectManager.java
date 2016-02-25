/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Shell;

import com.CxWave.Wave.Framework.Boot.BootCompleteForThisLocationEvent;
import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManagerForUserSpecificTasks;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.ObjectManagerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Boot.WaveAsynchronousContextForBootPhases;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.WaveObjectManagerPriority;

@ObjectManagerPriority (WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_SHELL)
public class ShellObjectManager extends WaveLocalObjectManagerForUserSpecificTasks
{
    private static ShellObjectManager s_shellObjectManager = null;

    public ShellObjectManager ()
    {
        super (getServiceName ());

        setAllowAutomaticallyUnlistenForEvents (false);
    }

    public static String getServiceName ()
    {
        return ("Shell");
    }

    public static ShellObjectManager getInstance ()
    {
        if (null == s_shellObjectManager)
        {
            s_shellObjectManager = new ShellObjectManager ();
        }

        WaveAssertUtils.waveAssert (null != s_shellObjectManager);

        return (s_shellObjectManager);
    }

    public static WaveServiceId getWaveServiceId ()
    {
        return ((getInstance ()).getServiceId ());
    }

    @Override
    public void initialize (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        waveAsynchronousContextForBootPhases.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        waveAsynchronousContextForBootPhases.callback ();
    }

    @Override
    public void boot (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        waveAsynchronousContextForBootPhases.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        waveAsynchronousContextForBootPhases.callback ();
    }

    @Override
    public void listenForEvents (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        waveAsynchronousContextForBootPhases.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        waveAsynchronousContextForBootPhases.callback ();
    }

    private void bootCompleteForThisLocationEventHandler (final BootCompleteForThisLocationEvent bootCompleteForThisLocationEvent)
    {
        unlistenEvents ();

        infoTracePrintf ("ShellObjectManager.bootCompleteForThisLocationEventHandler : Entering ...");

        reply (bootCompleteForThisLocationEvent);
    }
}
