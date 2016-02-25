/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Shell;

import java.lang.reflect.Method;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;

public class ShellCommandHandler
{
    private final String   m_handlerName;
    private final Class<?> m_handlerClass;
    private Method         m_handlerMethod;

    public ShellCommandHandler (final String handlerName, final Class<?> handlerClass)
    {
        m_handlerName = handlerName;
        m_handlerClass = handlerClass;

        WaveAssertUtils.waveAssert (null != m_handlerName);
        WaveAssertUtils.waveAssert (null != m_handlerClass);
    }
}
