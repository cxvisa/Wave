/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Configuration;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.XmlWaveXPath;

public class WaveMainApplicationConfigurationLocal extends SerializableObject
{
    @XmlWaveXPath (path = "file-name")
    private String m_file;

    @XmlWaveXPath (path = "backup-file-name")
    private String backupFile;

    @XmlWaveXPath (path = "lock-file-name")
    private String lockFile;

    public String getFile ()
    {
        return m_file;
    }

    public void setFile (final String file)
    {
        m_file = file;
    }

    public String getBackupFile ()
    {
        return backupFile;
    }

    public void setBackupFile (final String backupFile)
    {
        this.backupFile = backupFile;
    }

    public String getLockFile ()
    {
        return lockFile;
    }

    public void setLockFile (final String lockFile)
    {
        this.lockFile = lockFile;
    }
}
