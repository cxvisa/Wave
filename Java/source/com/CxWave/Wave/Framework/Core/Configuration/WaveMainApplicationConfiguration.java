/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Configuration;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.XmlWaveXPath;

public class WaveMainApplicationConfiguration extends SerializableObject
{
    @XmlWaveXPath (path = "directory-name")
    private String                                 m_directory;

    @XmlWaveXPath (path = "config-file-extension")
    private String                                 m_configFileExtension;

    @XmlWaveXPath (path = "backup-file-extension")
    private String                                 m_backupFileExtension;

    @XmlWaveXPath (path = "temp-file-extension")
    private String                                 m_tempFileExtension;

    @XmlWaveXPath (path = "local")
    private WaveMainApplicationConfigurationLocal  m_waveMainApplicationConfigurationLocal;

    @XmlWaveXPath (path = "global")
    private WaveMainApplicationConfigurationGlobal m_waveMainApplicationConfigurationGlobal;

    public String getDirectory ()
    {
        return m_directory;
    }

    public void setDirectory (final String directory)
    {
        m_directory = directory;
    }

    public String getConfigFileExtension ()
    {
        return m_configFileExtension;
    }

    public void setConfigFileExtension (final String configFileExtension)
    {
        m_configFileExtension = configFileExtension;
    }

    public String getBackupFileExtension ()
    {
        return m_backupFileExtension;
    }

    public void setBackupFileExtension (final String backupFileExtension)
    {
        m_backupFileExtension = backupFileExtension;
    }

    public String getTempFileExtension ()
    {
        return m_tempFileExtension;
    }

    public void setTempFileExtension (final String tempFileExtension)
    {
        m_tempFileExtension = tempFileExtension;
    }

    public WaveMainApplicationConfigurationLocal getWaveMainApplicationConfigurationLocal ()
    {
        return m_waveMainApplicationConfigurationLocal;
    }

    public void setWaveMainApplicationConfigurationLocal (final WaveMainApplicationConfigurationLocal waveMainApplicationConfigurationLocal)
    {
        m_waveMainApplicationConfigurationLocal = waveMainApplicationConfigurationLocal;
    }

    public WaveMainApplicationConfigurationGlobal getWaveMainApplicationConfigurationGlobal ()
    {
        return m_waveMainApplicationConfigurationGlobal;
    }

    public void setWaveMainApplicationConfigurationGlobal (final WaveMainApplicationConfigurationGlobal waveMainApplicationConfigurationGlobal)
    {
        m_waveMainApplicationConfigurationGlobal = waveMainApplicationConfigurationGlobal;
    }
}
