/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Context;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import com.CxWave.Wave.Framework.ObjectModel.WaveElement;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;

public class WaveAsynchronousContext
{
    private WaveElement m_caller             = null;
    private String      m_callbackMethodName = null;
    private Object      m_callerContext      = null;

    private Method      m_callbackMethod     = null;

    private ResourceId  m_completionStatus   = ResourceId.WAVE_MESSAGE_ERROR;

    public WaveAsynchronousContext (final WaveElement caller, final String callbackMethodName, final Object callerContext)
    {
        m_caller = caller;
        m_callbackMethodName = callbackMethodName;
        m_callerContext = callerContext;

        final boolean isValid = validateAndCompute ();

        if (!isValid)
        {
            WaveAssertUtils.waveAssert ();
        }
    }

    public WaveAsynchronousContext (final WaveAsynchronousContext waveAsynchronousContext)
    {
        WaveTraceUtils.fatalTracePrintf ("WaveAsynchronousContext.WaveAsynchronousContext : Cannot copy construct a WaveAsynchronousContext.");
        WaveAssertUtils.waveAssert ();
    }

    public boolean validateAndCompute ()
    {
        if (null == m_caller)
        {
            return (false);
        }

        if (WaveStringUtils.isBlank (m_callbackMethodName))
        {
            return (false);
        }

        final Class<?> callerClass = m_caller.getClass ();

        WaveAssertUtils.waveAssert (null != callerClass);

        try
        {
            m_callbackMethod = callerClass.getDeclaredMethod (m_callbackMethodName, getClass ());

            m_callbackMethod.setAccessible (true);
        }
        catch (NoSuchMethodException | SecurityException e)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveAsynchronousContext.validateAndCompute : Could not obtain the callback method %s on class %s, Details : %s", m_callbackMethodName, callerClass.getName (), e.toString ());
            WaveAssertUtils.waveAssert ();

            return (false);
        }

        return (true);
    }

    public void setCompletionStatus (final ResourceId completionStatus)
    {
        m_completionStatus = completionStatus;
    }

    public ResourceId getCompletionStatus ()
    {
        return (m_completionStatus);
    }

    public Object getCallerContext ()
    {
        return (m_callerContext);
    }

    public void callback ()
    {
        WaveAssertUtils.waveAssert (null != m_caller);
        WaveAssertUtils.waveAssert (null != m_callbackMethod);

        try
        {
            m_callbackMethod.invoke (m_caller, this);
        }
        catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException e)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveAsynchronousContext.callback : Could not invoke callback method %s on class %s, Details : %s", m_callbackMethodName, (m_caller.getClass ()).getName (), e.toString ());
            WaveAssertUtils.waveAssert ();
        }
    }
}
