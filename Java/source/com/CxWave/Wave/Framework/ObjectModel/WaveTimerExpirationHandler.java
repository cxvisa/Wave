/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import com.CxWave.Wave.Framework.Type.TimerHandle;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Source.WaveJavaSourceRepository;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;

public class WaveTimerExpirationHandler
{
    private final String m_name;
    private Method       m_method      = null;
    private WaveElement  m_waveElement = null;

    public WaveTimerExpirationHandler (final String name)
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

        final Method waveMessageCallbackMethod = WaveJavaSourceRepository.getMethodForWaveTimerExpirationHandlerInWaveJavaClass (waveElementClass.getTypeName (), m_name);

        if (null == waveMessageCallbackMethod)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveTimerExpirationHandler.validateAndCompute : Could not compute the wave timer expiration handler in class %s formethod name %s.", waveElementClass.getTypeName (), m_name);
            WaveAssertUtils.waveAssert ();
        }

        m_method = waveMessageCallbackMethod;
    }

    public void execute (final TimerHandle timerHandle, final Object context)
    {
        try
        {
            m_method.invoke (m_waveElement, timerHandle, context);
        }
        catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException e)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveTimerExpirationHandler.execute : Failed to invoke method : %s, Details : %s", m_method.getName (), e.toString ());
        }
    }
}
