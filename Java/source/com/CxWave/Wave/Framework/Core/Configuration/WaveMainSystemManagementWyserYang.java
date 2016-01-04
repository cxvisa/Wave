/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Configuration;

import java.util.Vector;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.XmlWaveXPath;

public class WaveMainSystemManagementWyserYang extends SerializableObject
{
    @XmlWaveXPath (path = "yin-path")
    private Vector<String> m_yinPaths;

    public Vector<String> getYinPaths ()
    {
        return m_yinPaths;
    }

    public void setYinPath (final Vector<String> yinPaths)
    {
        m_yinPaths = yinPaths;
    }
}
