/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Configuration;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.XmlWaveXPath;
import com.CxWave.Wave.Framework.Type.SI32;

public class WaveMainDatabase extends SerializableObject
{
    @XmlWaveXPath (path = "enable")
    private boolean m_enable           = true;

    @XmlWaveXPath (path = "port")
    private SI32    m_port             = new SI32 (9013L);

    @XmlWaveXPath (path = "detect-corruption")
    private boolean m_detectCorruption = true;

    @XmlWaveXPath (path = "handle-corruption")
    private boolean m_handleCorruption = true;

    @XmlWaveXPath (path = "enable-log")
    private boolean m_enableLog        = true;

    @XmlWaveXPath (path = "log-file")
    private String  m_logFile;

    @XmlWaveXPath (path = "shared-buffers")
    private String  m_sharedBuffers    = "128MB";

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

    public boolean getDetectCorruption ()
    {
        return m_detectCorruption;
    }

    public void setDetectCorruption (final boolean detectCorruption)
    {
        m_detectCorruption = detectCorruption;
    }

    public boolean getHandleCorruption ()
    {
        return m_handleCorruption;
    }

    public void setHandleCorruption (final boolean handleCorruption)
    {
        m_handleCorruption = handleCorruption;
    }

    public boolean getEnableLog ()
    {
        return m_enableLog;
    }

    public void setEnableLog (final boolean enableLog)
    {
        m_enableLog = enableLog;
    }

    public String getLogFile ()
    {
        return m_logFile;
    }

    public void setLogFile (final String logFile)
    {
        m_logFile = logFile;
    }

    public String getSharedBuffers ()
    {
        return m_sharedBuffers;
    }

    public void setSharedBuffers (final String sharedBuffers)
    {
        m_sharedBuffers = sharedBuffers;
    }
}
