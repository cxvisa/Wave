/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Configuration;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.XmlWaveXPath;

public class WaveMainRasSysLog extends SerializableObject
{
    @XmlWaveXPath (path = "enable")
    private boolean                 m_enable;

    @XmlWaveXPath (path = "local")
    private WaveMainRasSysLogLocal  m_waveMainRasSysLogLocal  = new WaveMainRasSysLogLocal ();

    @XmlWaveXPath (path = "remote")
    private WaveMainRasSysLogRemote m_waveMainRasSysLogRemote = new WaveMainRasSysLogRemote ();

    public boolean getEnable ()
    {
        return m_enable;
    }

    public void setEnable (final boolean enable)
    {
        m_enable = enable;
    }

    public WaveMainRasSysLogLocal getWaveMainRasSysLogLocal ()
    {
        return m_waveMainRasSysLogLocal;
    }

    public void setWaveMainRasSysLogLocal (final WaveMainRasSysLogLocal waveMainRasSysLogLocal)
    {
        m_waveMainRasSysLogLocal = waveMainRasSysLogLocal;
    }

    public WaveMainRasSysLogRemote getWaveMainRasSysLogRemote ()
    {
        return m_waveMainRasSysLogRemote;
    }

    public void setWaveMainRasSysLogRemote (final WaveMainRasSysLogRemote waveMainRasSysLogRemote)
    {
        m_waveMainRasSysLogRemote = waveMainRasSysLogRemote;
    }
}
