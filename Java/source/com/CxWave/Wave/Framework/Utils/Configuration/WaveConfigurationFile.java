/***********************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Configuration;

import com.CxWave.Wave.Framework.ToolKits.Xml.XmlFile;

public class WaveConfigurationFile implements WaveConfigurationFileInterface
{
    private String  m_waveConfigurationFilePath;

    private XmlFile m_xmlFile;

    public WaveConfigurationFile (final String waveConfigurationFilePath)
    {
        m_waveConfigurationFilePath = waveConfigurationFilePath;

        load ();
    }

    public String getWaveConfigurationFilePath ()
    {
        return m_waveConfigurationFilePath;
    }

    public void setWaveConfigurationFilePath (final String waveConfigurationFilePath)
    {
        m_waveConfigurationFilePath = waveConfigurationFilePath;
    }

    @Override
    public void load ()
    {
        m_xmlFile = new XmlFile (m_waveConfigurationFilePath);
    }

    @Override
    public WaveConfiguration getWaveConfiguration ()
    {
        final WaveConfiguration waveConfiguration = new WaveConfiguration ();

        return waveConfiguration;
    }

    @Override
    public void reload ()
    {
    }
}
