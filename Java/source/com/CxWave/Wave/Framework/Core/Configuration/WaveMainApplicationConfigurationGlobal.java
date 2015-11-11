/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Configuration;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.XmlWaveXPath;

public class WaveMainApplicationConfigurationGlobal extends SerializableObject
{
    @XmlWaveXPath (path = "file-name")
    private String m_file;

    @XmlWaveXPath (path = "temp-file-name")
    private String m_tempFile;

    public String getFile ()
    {
        return m_file;
    }

    public void setFile (final String file)
    {
        m_file = file;
    }

    public String getTempFile ()
    {
        return m_tempFile;
    }

    public void setTempFile (final String tempFile)
    {
        m_tempFile = tempFile;
    }
}
