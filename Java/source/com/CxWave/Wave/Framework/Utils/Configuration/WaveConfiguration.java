/***********************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Configuration;

import java.util.Date;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonSerializable;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.XmlWaveXPath;

public class WaveConfiguration extends SerializableObject
{
    @XmlWaveXPath (path = "wave.application.name")
    private String  m_applicationName;

    @XmlWaveXPath (path = "wave.application.daemonize")
    private boolean m_daemonize;

    @NonSerializable
    private Date    m_configurationLoadingTime;

    public String getApplicationName ()
    {
        return m_applicationName;
    }

    public void setApplicationName (final String applicationName)
    {
        m_applicationName = applicationName;
    }

    public Date getConfigurationLoadingTime ()
    {
        return m_configurationLoadingTime;
    }

    public void setConfigurationLoadingTime (final Date configurationLoadingTime)
    {
        m_configurationLoadingTime = configurationLoadingTime;
    }

}
