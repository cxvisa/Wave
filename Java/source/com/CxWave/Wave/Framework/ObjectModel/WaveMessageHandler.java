/***************************************************************************
 *   Copyright (C) 2015-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;

public class WaveMessageHandler
{
    private final String m_methodName;

    public WaveMessageHandler (final String methodName)
    {
        m_methodName = methodName;
    }

    String getMethodName ()
    {
        return (m_methodName);
    }

    void execute (final WaveMessage waveMessage, final WaveElement waveElement)
    {

    }
}
