/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Source.WaveJavaSourceRepository;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.FrameworkStatus;

public class WaveMessageResponseHandler
{
    private final String m_name;
    private Method       m_method      = null;
    private WaveElement  m_waveElement = null;

    public WaveMessageResponseHandler (final String name)
    {
        m_name = name;

        WaveAssertUtils.waveAssert (WaveStringUtils.isNotBlank (m_name));
    }

    public String getName ()
    {
        return (m_name);
    }

    public void validateAndCompute (final WaveElement waveElement)
    {
        WaveAssertUtils.waveAssert (null != waveElement);

        m_waveElement = waveElement;

        final Class<?> waveElementClass = waveElement.getClass ();

        WaveAssertUtils.waveAssert (null != waveElementClass);

        final Method waveMessageCallbackMethod = WaveJavaSourceRepository.getMethodForWaveMessageCallbackInWaveJavaClass (waveElementClass.getTypeName (), m_name);

        if (null == waveMessageCallbackMethod)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveMessageResponseHandler.validateAndCompute : Could not compute the wave message callback in class %s formethod name %s.", waveElementClass.getTypeName (), m_name);
            WaveAssertUtils.waveAssert ();
        }

        m_method = waveMessageCallbackMethod;
    }

    public void execute (final FrameworkStatus frameworkStatus, final WaveMessage waveMessage, final Object context)
    {
        try
        {
            m_method.invoke (m_waveElement, frameworkStatus, waveMessage, context);
        }
        catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException e)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveMessageResponseHandler.execute : Failed to invoke method : %s, Details : %s", m_method.getName (), e.toString ());
        }
    }
}
