/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import com.CxWave.Wave.Framework.Messaging.LightHouse.LightPulse;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Source.WaveJavaSourceRepository;
import com.CxWave.Wave.Framework.Utils.Stack.WaveStackUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;

public class WaveLightPulseHandler
{
    private final String m_methodName;
    private Method       m_method      = null;
    private WaveElement  m_waveElement = null;

    public WaveLightPulseHandler (final String methodName)
    {
        m_methodName = methodName;
    }

    public String getMethodName ()
    {
        return (m_methodName);
    }

    public void validateAndCompute (final WaveElement waveElement)
    {
        WaveAssertUtils.waveAssert (null != waveElement);

        m_waveElement = waveElement;

        final Class<?> waveElementClass = waveElement.getClass ();

        WaveAssertUtils.waveAssert (null != waveElementClass);

        final Method waveLightPulseHandlerMethod = WaveJavaSourceRepository.getMethodForWaveLightPulseHandlerInWaveJavaClass (waveElementClass.getTypeName (), m_methodName);

        if (null == waveLightPulseHandlerMethod)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveLightPulseHandler.validateAndCompute : Could not compute the wave LightPulse handler in class %s formethod name %s.", waveElementClass.getTypeName (), m_methodName);
            WaveAssertUtils.waveAssert ();
        }

        m_method = waveLightPulseHandlerMethod;
    }

    void execute (final LightPulse waveLightPulse)
    {
        try
        {
            m_method.invoke (m_waveElement, waveLightPulse);
        }
        catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException e)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveLightPulseHandler.execute : Failed to invoke method : %s, Details : %s", m_method.getName (), e.toString ());

            final Throwable cause = e.getCause ();

            if (null != cause)
            {
                WaveTraceUtils.fatalTracePrintf ("WaveLightPulseHandler.execute : Cause : %s", cause.toString ());

                WaveTraceUtils.fatalTracePrintf ("%s", WaveStackUtils.getStackString (cause));
            }

            WaveTraceUtils.fatalTracePrintf ("%s", WaveStackUtils.getStackString (e));
        }
    }
}
