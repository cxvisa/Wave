/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Configuration;

import java.util.Vector;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.XmlWaveXPath;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;

@XmlWaveXPath (path = "application")
public class WaveMainApplication extends SerializableObject
{
    @XmlWaveXPath (path = "name")
    private String  m_applicationName;

    @XmlWaveXPath (absolutePath = "wave.application.daemonize")
    private boolean m_isADaemon;

    @XmlWaveXPath (path = "ethernet-interface")
    private String  m_ethernetInterface;

    @XmlWaveXPath (path = "initial-working-directory")
    private String  m_initialWorkingDirectory;

    private WaveMainApplication ()
    {
    }

    public String getApplicationName ()
    {
        return m_applicationName;
    }

    public void setApplicationName (final String applicationName)
    {
        m_applicationName = applicationName;
    }

    public boolean getIsADaemon ()
    {
        return m_isADaemon;
    }

    public void setIsADaemon (final boolean isADaemon)
    {
        m_isADaemon = isADaemon;
    }

    public String getInitialWorkingDirectory ()
    {
        return m_initialWorkingDirectory;
    }

    public void setInitialWorkingDirectory (final String initialWorkingDirectory)
    {
        m_initialWorkingDirectory = initialWorkingDirectory;
    }

    public String getEthernetInterface ()
    {
        return m_ethernetInterface;
    }

    public void setEthernetInterface (final String ethernetInterface)
    {
        m_ethernetInterface = ethernetInterface;
    }

    public String getApplicationCompactName ()
    {
        if (WaveStringUtils.isBlank (m_applicationName))
        {
            return ("");
        }

        final Vector<String> tokensInApplicationName = new Vector<String> ();

        WaveStringUtils.tokenize (m_applicationName, tokensInApplicationName, '/');

        final int numberOfTokens = tokensInApplicationName.size ();

        if (0 < numberOfTokens)
        {
            return (tokensInApplicationName.get (numberOfTokens - 1));
        }
        else
        {
            return (new String (""));
        }
    }
}
