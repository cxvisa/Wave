/***************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;

public class WaveMessageHandler
{
    private final Method      m_method;
    private final WaveElement m_waveElement;

    public WaveMessageHandler (final Method method, final WaveElement waveElement)
    {
        m_method = method;
        m_waveElement = waveElement;

        if (null == m_waveElement)
        {
            WaveAssertUtils.waveAssert ();
            return;
        }

        if (null == m_method)
        {
            WaveAssertUtils.waveAssert ();
            return;
        }
    }

    void execute (final WaveMessage waveMessage)
    {
        try
        {
            m_method.invoke (m_waveElement, waveMessage);
        }
        catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException e)
        {
            WaveAssertUtils.waveAssert ();
        }
    }
}
