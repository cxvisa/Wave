/***************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;

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

    void execute (final WaveMessage waveMessage) throws IllegalAccessException, IllegalArgumentException, InvocationTargetException
    {
        try
        {
            m_method.invoke (m_waveElement, waveMessage);
        }
        catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException e)
        {
            WaveTraceUtils.errorTracePrintf ("WaveMessageHandler.execute : Could not execute the message.  WaveElement Type : %s, Wave Message Type : %s, Details : %s", (m_waveElement.getClass ()).getName (), (waveMessage.getClass ()).getName (), e.toString ());

            throw (e);
        }
    }
}
