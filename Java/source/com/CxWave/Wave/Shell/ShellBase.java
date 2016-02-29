/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Shell;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Map;

import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Framework.Utils.LineEditor.WaveLineEditor;
import com.CxWave.Wave.Framework.Utils.Source.WaveJavaSourceRepository;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;

public class ShellBase extends WaveWorker
{
    private final String                m_name;
    private final Map<String, Method>   m_commandHandlersMap = null;
    private final Map<String, Class<?>> m_subordinatesMap    = null;

    public ShellBase (final String name)
    {
        super (ShellObjectManager.getInstance ());

        final Class<?> thisShellClass = getClass ();

        final String shellClassName = thisShellClass.getSimpleName ();

        if (WaveStringUtils.isBlank (name))
        {
            m_name = shellClassName;
        }
        else
        {
            m_name = name;
        }

        infoTracePrintf ("ShellBase.ShellBase : Name : %s", m_name);

        final Map<String, Method> m_commandHandlersMap = WaveJavaSourceRepository.getShellCommandHandlerMethodsForClass (thisShellClass);
        final Map<String, Class<?>> m_subordinatesMap = WaveJavaSourceRepository.getShellSubordinnatesForClass (thisShellClass);

        infoTracePrintf ("ShellBase.ShellBase : %s Command Handlers :", m_name);

        if (null != m_commandHandlersMap)
        {
            for (final Map.Entry<String, Method> commandHandlerEntry : m_commandHandlersMap.entrySet ())
            {
                final String commandHandlerToken = commandHandlerEntry.getKey ();
                final Method commandHandlerMethod = commandHandlerEntry.getValue ();

                waveAssert (WaveStringUtils.isNotBlank (commandHandlerToken));
                waveAssert (null != commandHandlerMethod);

                infoTracePrintf ("ShellBase.ShellBase :     %s : %s", commandHandlerToken, commandHandlerMethod.toString ());
            }
        }

        infoTracePrintf ("ShellBase.ShellBase : %s Subordinate Shells :", m_name);

        if (null != m_subordinatesMap)
        {
            for (final Map.Entry<String, Class<?>> subordinateShellEntry : m_subordinatesMap.entrySet ())
            {
                final String shellToken = subordinateShellEntry.getKey ();
                final Class<?> shellClass = subordinateShellEntry.getValue ();

                waveAssert (WaveStringUtils.isNotBlank (shellToken));
                waveAssert (null != shellClass);

                infoTracePrintf ("ShellBase.ShellBase :     %s : %s", shellToken, shellClass.toString ());

                final Constructor<?>[] declaredConstructors = shellClass.getDeclaredConstructors ();
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
                    fatalTracePrintf ("ShellObjectManager.bootCompleteForThisLocationEventHandler : Shell Root clould not be instantiated sicne there is not constructor which takes name parameter.");
                    waveAssert ();
                }

                Object shellObject = null;

                try
                {
                    shellObject = declaredConstructorWithNameParamerter.newInstance (shellToken);
                }
                catch (InstantiationException | IllegalAccessException | IllegalArgumentException | InvocationTargetException e)
                {
                    fatalTracePrintf ("ShellObjectManager.ShellBase : Could not instantiate shell root class : %s.  Details : %s", shellClass.getTypeName (), e.toString ());

                    final Throwable cause = e.getCause ();

                    if (null != cause)
                    {
                        fatalTracePrintf ("ShellObjectManager.ShellBase : Cause : %s", cause.toString ());
                    }

                    waveAssert ();
                }

                final ShellBase shellBaseForRoot = (ShellBase) shellObject;
            }
        }
    }

    public String getName ()
    {
        return (m_name);
    }

    public boolean isRootShell ()
    {
        return (false);
    }

    public void shellExecuteHanler ()
    {
        final WaveLineEditor waveLineEditor = new WaveLineEditor ();

        waveAssert (null != waveLineEditor);

        if (null != m_commandHandlersMap)
        {
            for (final Map.Entry<String, Method> commandHandlerEntry : m_commandHandlersMap.entrySet ())
            {
                final String commandHandlerToken = commandHandlerEntry.getKey ();
                final Method commandHandlerMethod = commandHandlerEntry.getValue ();

                waveAssert (WaveStringUtils.isNotBlank (commandHandlerToken));
                waveAssert (null != commandHandlerMethod);

                waveLineEditor.addValidCommand (commandHandlerToken);
            }
        }

        infoTracePrintf ("ShellBase.ShellBase : %s Subordinate Shells :", m_name);

        if (null != m_subordinatesMap)
        {
            for (final Map.Entry<String, Class<?>> subordinateShellEntry : m_subordinatesMap.entrySet ())
            {
                final String shellToken = subordinateShellEntry.getKey ();
                final Class<?> shellClass = subordinateShellEntry.getValue ();

                waveAssert (WaveStringUtils.isNotBlank (shellToken));
                waveAssert (null != shellClass);

                waveLineEditor.addValidCommand (shellToken);
            }
        }

        while (true)
        {
            final String commandLine = waveLineEditor.getUserInputLine (m_name);

            if ("Quit".equals (commandLine))
            {
                return;
            }
        }
    }
}
