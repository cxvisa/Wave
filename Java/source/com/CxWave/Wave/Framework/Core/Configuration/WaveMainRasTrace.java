/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Configuration;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.XmlWaveXPath;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class WaveMainRasTrace extends SerializableObject
{
    @XmlWaveXPath (path = "enable")
    private final boolean    m_enable        = true;

    @XmlWaveXPath (path = "directory-name")
    private String           m_directory;

    @XmlWaveXPath (path = "file-name")
    private String           m_file;

    @XmlWaveXPath (path = "file-size")
    private final String     m_size          = "5MB";

    @XmlWaveXPath (path = "number-of-files")
    private final UI32       m_numberOfFiles = new UI32 (10);

    @XmlWaveXPath (path = "default-level")
    private final TraceLevel m_traceLevel    = TraceLevel.TRACE_LEVEL_INFO;

    public String getDirectory ()
    {
        return m_directory;
    }

    public void setDirectory (final String directory)
    {
        m_directory = directory;
    }

    public String getFile ()
    {
        return m_file;
    }

    public void setFile (final String file)
    {
        m_file = file;
    }

    public boolean getEnable ()
    {
        return m_enable;
    }

    public String getSize ()
    {
        return m_size;
    }

    public UI32 getNumberOfFiles ()
    {
        return m_numberOfFiles;
    }

    public TraceLevel getTraceLevel ()
    {
        return m_traceLevel;
    }
}
