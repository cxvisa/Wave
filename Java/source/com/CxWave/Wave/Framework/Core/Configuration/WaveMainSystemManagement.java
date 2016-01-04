/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Configuration;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.XmlWaveXPath;

public class WaveMainSystemManagement extends SerializableObject
{
    @XmlWaveXPath (path = "wyser")
    private WaveMainSystemManagementWyser m_waveMainSystemManagementWyser = new WaveMainSystemManagementWyser ();

    public WaveMainSystemManagementWyser getWaveMainSystemManagementWyser ()
    {
        return m_waveMainSystemManagementWyser;
    }

    public void setWaveMainSystemManagementWyser (final WaveMainSystemManagementWyser waveMainSystemManagementWyser)
    {
        m_waveMainSystemManagementWyser = waveMainSystemManagementWyser;
    }
}
