/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Configuration;

import java.util.Date;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;

public class WaveConfiguration extends SerializableObject
{
    private Date   m_loadedDateTime;
    private String m_configurationName;
    private String m_configurationOrigin;
    private String m_description;

    public WaveConfiguration ()
    {
    }

    public Date getLoadedDateTime ()
    {
        return m_loadedDateTime;
    }

    public void setLoadedDateTime (final Date loadedDateTime)
    {
        m_loadedDateTime = loadedDateTime;
    }

    public String getConfigurationName ()
    {
        return m_configurationName;
    }

    public void setConfigurationName (final String configurationName)
    {
        m_configurationName = configurationName;
    }

    public String getConfigurationOrigin ()
    {
        return m_configurationOrigin;
    }

    public void setConfigurationOrigin (final String configurationOrigin)
    {
        m_configurationOrigin = configurationOrigin;
    }
}
