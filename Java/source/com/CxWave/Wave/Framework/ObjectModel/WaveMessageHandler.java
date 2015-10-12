/***************************************************************************
 *   Copyright (C) 2015-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Reflection.WaveReflectionUtils;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;

public class WaveMessageHandler
{
    private final String m_methodName;

    public WaveMessageHandler (final String methodName)
    {
        m_methodName = methodName;

        if (WaveStringUtils.isBlank (methodName))
        {
            WaveAssertUtils.waveAssert ();
            return;
        }
    }

    String getMethodName ()
    {
        return (m_methodName);
    }

    void execute (final WaveMessage waveMessage, final WaveElement waveElement)
    {
        if (null == waveElement)
        {
            WaveAssertUtils.waveAssert ();
            return;
        }

        Class<? extends WaveElement> waveElementClass = waveElement.getClass ();

        if (null == waveElementClass)
        {
            WaveAssertUtils.waveAssert ();
            return;
        }

        if (WaveStringUtils.isBlank (m_methodName))
        {
            return;
        }

        boolean isMethodPresent = WaveReflectionUtils.isMethodPresent (waveElement.getClass (), m_methodName, WaveMessage.class);

        if (! isMethodPresent)
        {
            WaveAssertUtils.waveAssert ();
            return;
        }

        Method waveElementClassMethod = null;

        try
        {
            waveElementClassMethod = waveElementClass.getMethod (m_methodName, WaveMessage.class);
        }
        catch (NoSuchMethodException noSuchMethodEXception)
        {
            WaveAssertUtils.waveAssert ();
        }
        catch (Exception exception)
        {
            WaveAssertUtils.waveAssert ();
        }

        try
        {
            waveElementClassMethod.invoke (waveElement, waveMessage);
        }
        catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException e)
        {
            WaveAssertUtils.waveAssert ();
        }
    }
}
