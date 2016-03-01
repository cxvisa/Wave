/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Shell;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;

import com.CxWave.Wave.Framework.Boot.BootCompleteForThisLocationEvent;
import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManagerForUserSpecificTasks;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.ObjectManagerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Boot.WaveAsynchronousContextForBootPhases;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Source.WaveJavaSourceRepository;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.WaveObjectManagerPriority;

@ObjectManagerPriority (WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_SHELL)
public class ShellObjectManager extends WaveLocalObjectManagerForUserSpecificTasks
{
    private static ShellObjectManager s_shellObjectManager = null;

    private static String             s_shellRootPrompt    = "Wave";

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

        // Get the Root Shell and instantiate it.

        final Class<?> shellRootClass = WaveJavaSourceRepository.getShellRootClass ();

        if (null != shellRootClass)
        {
            infoTracePrintf ("ShellObjectManager.bootCompleteForThisLocationEventHandler : Shell Root is handled by class : %s", shellRootClass.getTypeName ());
        }
        else
        {
            warnTracePrintf ("ShellObjectManager.bootCompleteForThisLocationEventHandler : Shell Root is not available and hence not spawning Shell.");

            return;
        }

        // Then instantiate and execute the root shell

        final Constructor<?>[] declaredConstructors = shellRootClass.getDeclaredConstructors ();
        Constructor<?> declaredConstructorWithNameParamerter = null;

        for (final Constructor<?> declaredConstructor : declaredConstructors)
        {
            if (1 == (declaredConstructor.getParameterCount ()))
            {
                declaredConstructorWithNameParamerter = declaredConstructor;

                break;
            }
        }

        if (null == declaredConstructorWithNameParamerter)
        {
            fatalTracePrintf ("ShellObjectManager.bootCompleteForThisLocationEventHandler : Shell Root clould not be instantiated sicne there is no constructor which takes name parameter.");
            waveAssert ();
        }

        Object shellObject = null;

        try
        {
            shellObject = declaredConstructorWithNameParamerter.newInstance (s_shellRootPrompt);
        }
        catch (InstantiationException | IllegalAccessException | IllegalArgumentException | InvocationTargetException e)
        {
            fatalTracePrintf ("ShellObjectManager.bootCompleteForThisLocationEventHandler : Could not instantiate shell root class : %s.  Details : %s", shellRootClass.getTypeName (), e.toString ());

            final Throwable cause = e.getCause ();

            if (null != cause)
            {
                fatalTracePrintf ("ShellObjectManager.bootCompleteForThisLocationEventHandler : Cause : %s:\n\r%s", cause.toString ());
            }

            waveAssert ();
        }

        final ShellBase shellBaseForRoot = (ShellBase) shellObject;

        shellBaseForRoot.shellExecuteHanler (null);
    }
}
