/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Configuration;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.XmlWaveXPath;

public class WaveMainRas extends SerializableObject
{
    @XmlWaveXPath (path = "sys-log")
    private WaveMainRasSysLog m_waveMainRasSysLog = new WaveMainRasSysLog ();

    @XmlWaveXPath (path = "log")
    private WaveMainRasLog    m_waveMainRasLog    = new WaveMainRasLog ();

    @XmlWaveXPath (path = "trace")
    private WaveMainRasTrace  m_waveMainRasTrace  = new WaveMainRasTrace ();

    public WaveMainRasSysLog getWaveMainRasSysLog ()
    {
        return m_waveMainRasSysLog;
    }

    public void setWaveMainRasSysLog (final WaveMainRasSysLog waveMainRasSysLog)
    {
        m_waveMainRasSysLog = waveMainRasSysLog;
    }

    public WaveMainRasLog getWaveMainRasLog ()
    {
        return m_waveMainRasLog;
    }

    public void setWaveMainRasLog (final WaveMainRasLog waveMainRasLog)
    {
        m_waveMainRasLog = waveMainRasLog;
    }

    public WaveMainRasTrace getWaveMainRasTrace ()
    {
        return m_waveMainRasTrace;
    }

    public void setWaveMainRasTrace (final WaveMainRasTrace waveMainRasTrace)
    {
        m_waveMainRasTrace = waveMainRasTrace;
    }
}
