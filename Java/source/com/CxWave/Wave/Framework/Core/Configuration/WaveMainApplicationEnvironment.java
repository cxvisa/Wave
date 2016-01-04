/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Configuration;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.XmlWaveXPath;

public class WaveMainApplicationEnvironment extends SerializableObject
{
    @XmlWaveXPath (path = "working-directory")
    private String m_workingDirectory;

    @XmlWaveXPath (path = "language")
    private String m_languageCode;

    @XmlWaveXPath (path = "country")
    private String m_countryCode;

    public String getWorkingDirectory ()
    {
        return m_workingDirectory;
    }

    public void setWorkingDirectory (final String workingDirectory)
    {
        m_workingDirectory = workingDirectory;
    }

    public String getLanguageCode ()
    {
        return m_languageCode;
    }

    public void setLanguageCode (final String languageCode)
    {
        m_languageCode = languageCode;
    }

    public String getCountryCode ()
    {
        return m_countryCode;
    }

    public void setCountryCode (final String countryCode)
    {
        m_countryCode = countryCode;
    }
}
