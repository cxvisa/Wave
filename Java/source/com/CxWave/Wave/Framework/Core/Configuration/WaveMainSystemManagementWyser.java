/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Configuration;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.XmlWaveXPath;

public class WaveMainSystemManagementWyser extends SerializableObject
{
    @XmlWaveXPath (path = "yang")
    private WaveMainSystemManagementWyserYang m_waveMainSystemManagementWyserYang = new WaveMainSystemManagementWyserYang ();

    public WaveMainSystemManagementWyserYang getWaveMainSystemManagementWyserYang ()
    {
        return m_waveMainSystemManagementWyserYang;
    }

    public void setWaveMainSystemManagementWyserYang (final WaveMainSystemManagementWyserYang waveMainSystemManagementWyserYang)
    {
        m_waveMainSystemManagementWyserYang = waveMainSystemManagementWyserYang;
    }
}
