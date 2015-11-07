/***********************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Configuration;

import java.util.Vector;

import com.CxWave.Wave.Framework.ToolKits.Xml.XmlFile;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

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
    public void reload ()
    {
    }

    public Vector<String> getConfigurationValues (final String waveXmlXPath)
    {
        Vector<String> xmlTextNodeValues = null;

        if (null != m_xmlFile)
        {
            xmlTextNodeValues = m_xmlFile.getTextNodeValuesByWaveXmlXPath (waveXmlXPath);
        }
        else
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "WaveConfigurationFile.getConfigurationValue : Load the XML Configuration file first, for Wave Xml XPath : %s", waveXmlXPath);
            WaveAssertUtils.waveAssert ();
        }

        return (xmlTextNodeValues);
    }

    public String getConfigurationValue (final String waveXmlXPath)
    {
        final Vector<String> configurationValues = getConfigurationValues (waveXmlXPath);

        WaveAssertUtils.waveAssert (null != configurationValues);

        if (0 < (configurationValues.size ()))
        {
            return (configurationValues.get (0));
        }
        else
        {
            return ("");
        }
    }

    public String getLastConfigurationValue (final String waveXmlXPath)
    {
        final Vector<String> configurationValues = getConfigurationValues (waveXmlXPath);

        WaveAssertUtils.waveAssert (null != configurationValues);

        final int numberOfConfigurationValues = configurationValues.size ();

        if (0 < numberOfConfigurationValues)
        {
            return (configurationValues.get (numberOfConfigurationValues - 1));
        }
        else
        {
            return ("");
        }
    }
}
