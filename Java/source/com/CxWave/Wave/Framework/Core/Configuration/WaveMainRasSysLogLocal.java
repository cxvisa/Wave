/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Configuration;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.XmlWaveXPath;

public class WaveMainRasSysLogLocal extends SerializableObject
{
    @XmlWaveXPath (path = "enable")
    private boolean m_enable;

    public boolean getEnable ()
    {
        return m_enable;
    }

    public void setEnable (final boolean enable)
    {
        m_enable = enable;
    }
}
