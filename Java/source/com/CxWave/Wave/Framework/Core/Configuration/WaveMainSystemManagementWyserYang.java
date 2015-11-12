/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Configuration;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.XmlWaveXPath;

public class WaveMainSystemManagementWyserYang extends SerializableObject
{
    @XmlWaveXPath (path = "yin-path")
    private String m_yinPath;

    public String getYinPath ()
    {
        return m_yinPath;
    }

    public void setYinPath (final String yinPath)
    {
        m_yinPath = yinPath;
    }
}
