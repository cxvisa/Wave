/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Configuration;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.XmlWaveXPath;
import com.CxWave.Wave.Framework.Type.UI32;

public class WaveMainRasLog extends SerializableObject
{
    @XmlWaveXPath (path = "enable")
    private boolean                      m_enable;

    @XmlWaveXPath (path = "number-of-logs")
    private UI32                         m_numberOfLogs;

    @XmlWaveXPath (path = "audit-log")
    private final WaveMainRasLogAuditLog m_waveMainRasLogAuditLog = new WaveMainRasLogAuditLog ();

    public boolean getEnable ()
    {
        return m_enable;
    }

    public void setEnable (final boolean enable)
    {
        m_enable = enable;
    }

    public UI32 getNumberOfLogs ()
    {
        return m_numberOfLogs;
    }

    public void setNumberOfLogs (final UI32 numberOfLogs)
    {
        m_numberOfLogs = numberOfLogs;
    }

    public WaveMainRasLogAuditLog getWaveMainRasLogAuditLog ()
    {
        return m_waveMainRasLogAuditLog;
    }
}
