/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Shell;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Vector;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;

public class ShellCommandHandler
{
    private final String m_handlerName;
    private final Method m_handlerMethod;

    public ShellCommandHandler (final String handlerName, final Method handlerMethod)
    {
        m_handlerName = handlerName;
        m_handlerMethod = handlerMethod;

        WaveAssertUtils.waveAssert (null != m_handlerName);
        WaveAssertUtils.waveAssert (null != handlerMethod);
    }

    public ResourceId execute (final Vector<String> arguments)
    {
        try
        {
            m_handlerMethod.invoke (null, arguments);
        }
        catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException e)
        {
            WaveTraceUtils.fatalTracePrintf ("ShellCommandHandler.execute : Failed to execute : %s, Details : %s", m_handlerName, e.toString ());

            final Throwable cause = e.getCause ();

            if (null != cause)
            {
                WaveTraceUtils.fatalTracePrintf ("ShellCommandHandler.execute : Cause : %s", cause.toString ());
            }

            return (ResourceId.WAVE_MESSAGE_ERROR);
        }

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }
}
