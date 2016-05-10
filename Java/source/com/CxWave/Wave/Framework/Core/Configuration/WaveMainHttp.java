/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Configuration;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.XmlWaveXPath;
import com.CxWave.Wave.Framework.Type.SI32;

public class WaveMainHttp extends SerializableObject
{
    @XmlWaveXPath (path = "enable")
    private boolean m_enable = true;

    @XmlWaveXPath (path = "port")
    private SI32     m_port   = new SI32 (2301);

    public boolean getEnable ()
    {
        return m_enable;
    }

    public void setEnable (final boolean enable)
    {
        m_enable = enable;
    }

    public SI32 getPort ()
    {
        return m_port;
    }

    public void setPort (final SI32 port)
    {
        m_port = port;
    }
}
