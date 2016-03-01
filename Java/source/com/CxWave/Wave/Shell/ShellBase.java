/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Shell;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.LineEditor.WaveLineEditor;
import com.CxWave.Wave.Framework.Utils.Source.WaveJavaSourceRepository;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;

public class ShellBase extends WaveWorker
{
    private final String                           m_name;
    private final Map<String, ShellCommandHandler> m_commandHandlersMap = new HashMap<String, ShellCommandHandler> ();
    private final Map<String, ShellBase>           m_subordinatesMap    = new HashMap<String, ShellBase> ();

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

        final Map<String, Method> commandHandlersMap = WaveJavaSourceRepository.getShellCommandHandlerMethodsForClass (thisShellClass);
        final Map<String, Class<?>> subordinatesMap = WaveJavaSourceRepository.getShellSubordinnatesForClass (thisShellClass);

        infoTracePrintf ("ShellBase.ShellBase : %s Command Handlers :", m_name);

        if (null != commandHandlersMap)
        {
            for (final Map.Entry<String, Method> commandHandlerEntry : commandHandlersMap.entrySet ())
            {
                final String commandHandlerToken = commandHandlerEntry.getKey ();
                final Method commandHandlerMethod = commandHandlerEntry.getValue ();

                waveAssert (WaveStringUtils.isNotBlank (commandHandlerToken));
                waveAssert (null != commandHandlerMethod);

                infoTracePrintf ("ShellBase.ShellBase :     %s : %s", commandHandlerToken, commandHandlerMethod.toString ());

                m_commandHandlersMap.put (commandHandlerToken, new ShellCommandHandler (commandHandlerToken, commandHandlerMethod));
            }
        }

        infoTracePrintf ("ShellBase.ShellBase : %s Subordinate Shells :", m_name);

        if (null != subordinatesMap)
        {
            for (final Map.Entry<String, Class<?>> subordinateShellEntry : subordinatesMap.entrySet ())
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
                    fatalTracePrintf ("ShellBase.ShellBase : Shell clould not be instantiated sicne there is no constructor which takes name parameter.");
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

                final ShellBase shellBase = (ShellBase) shellObject;

                m_subordinatesMap.put (shellToken, shellBase);
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

    public void shellExecuteHanler (final Vector<String> incomingArguments)
    {
        int numberOfIncomingArguments = 0;

        if (null != incomingArguments)
        {
            numberOfIncomingArguments = incomingArguments.size ();
        }

        final WaveLineEditor waveLineEditor = new WaveLineEditor ();

        waveAssert (null != waveLineEditor);

        if (null != m_commandHandlersMap)
        {
            for (final Map.Entry<String, ShellCommandHandler> commandHandlerEntry : m_commandHandlersMap.entrySet ())
            {
                final String commandHandlerToken = commandHandlerEntry.getKey ();
                final ShellCommandHandler commandHandler = commandHandlerEntry.getValue ();

                waveAssert (WaveStringUtils.isNotBlank (commandHandlerToken));
                waveAssert (null != commandHandler);

                waveLineEditor.addValidCommand (commandHandlerToken);
            }
        }

        if (null != m_subordinatesMap)
        {
            for (final Map.Entry<String, ShellBase> subordinateShellEntry : m_subordinatesMap.entrySet ())
            {
                final String shellToken = subordinateShellEntry.getKey ();
                final ShellBase shellBase = subordinateShellEntry.getValue ();

                waveAssert (WaveStringUtils.isNotBlank (shellToken));
                waveAssert (null != shellBase);

                waveLineEditor.addValidCommand (shellToken);
            }
        }

        while (true)
        {
            final Vector<String> commandLineTokens = new Vector<String> ();

            if (0 == numberOfIncomingArguments)
            {
                final String commandLine = waveLineEditor.getUserInputLine (m_name);

                if (WaveStringUtils.isBlank (commandLine))
                {
                    continue;
                }

                WaveStringUtils.tokenizeConsideringStringQuotes (commandLine, commandLineTokens, ' ');
            }
            else
            {
                commandLineTokens.addAll (incomingArguments);
            }

            final int numberOfCommandLineTokens = commandLineTokens.size ();
            String commandToken = "";

            if (0 < numberOfCommandLineTokens)
            {
                commandToken = commandLineTokens.get (0);
            }

            if (WaveStringUtils.isBlank (commandToken))
            {
                continue;
            }

            if ("Quit".equals (commandToken))
            {
                return;
            }

            if (m_subordinatesMap.containsKey (commandToken))
            {
                final ShellBase shellBase = m_subordinatesMap.get (commandToken);

                WaveAssertUtils.waveAssert (null != shellBase);

                commandLineTokens.remove (0);

                shellBase.shellExecuteHanler (commandLineTokens);
            }
            else if (m_commandHandlersMap.containsKey (commandToken))
            {
                final ShellCommandHandler commandHandler = m_commandHandlersMap.get (commandToken);

                WaveAssertUtils.waveAssert (null != commandHandler);

                commandLineTokens.remove (0);

                final ResourceId status = commandHandler.execute (commandLineTokens);
            }
            else
            {
                WaveTraceUtils.errorTracePrintf (true, true, "Invalid command : %s", commandToken);
            }

            numberOfIncomingArguments = 0;
        }
    }
}
