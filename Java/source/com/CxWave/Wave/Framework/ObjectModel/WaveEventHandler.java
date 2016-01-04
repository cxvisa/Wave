/***************************************************************************
 *   Copyright (C) 2015-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import com.CxWave.Wave.Framework.Messaging.Local.WaveEvent;

public class WaveEventHandler
{
    private final String m_methodName;

    public WaveEventHandler (final String methodName)
    {
        m_methodName = methodName;
    }

    public String getMethodName ()
    {
        return (m_methodName);
    }

    void execute (final WaveEvent waveEvent, final WaveElement waveElement)
    {

    }
}
