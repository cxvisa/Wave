/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Configuration;

import java.util.Vector;

import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonSerializable;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.XmlWaveXPath;
import com.CxWave.Wave.Framework.Utils.Configuration.WaveConfiguration;

@XmlWaveXPath (path = "wave")
public class WaveMainConfiguration extends WaveConfiguration
{
    @XmlWaveXPath (path = "application")
    private final WaveMainApplication m_application = null;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               // =
    private boolean                   m_isSysLogRequired;
    private boolean                   m_isDatabaseEnabled;
    private boolean                   m_isDatabaseLogEnabled;
    private int                       m_port;
    private int                       m_databasePort;
    private String                    m_databaseLogFileName;
    private String                    m_databaseSharedBuffers;
    private int                       m_managementPort;
    @XmlWaveXPath (path = "application.ethernet-interface")
    private String                    m_ethernetInterface;
    private int                       m_managementClientPort;
    private String                    m_changeDirectoryTo;
    @NonSerializable
    private Vector<String>            m_yinPaths;
    private String                    m_wyserTagsFilePath;
    private String                    m_databaseEmptyType;
    private long                      m_databaseEmptyTypeAutoDetectionThresholdValue;
    private String                    m_configurationFile;
    private String                    m_configurationFileDirectory;
    private String                    m_globalConfigurationFile;
    private String                    m_lockFileForConfigurationFile;
    private String                    m_traceFileDirectory;
    private String                    m_traceFileName;
    private String                    m_profileFileName;

    public WaveMainConfiguration ()
    {
    }

    public WaveMainApplication getApplication ()
    {
        return m_application;
    }

    public boolean getIsSysLogRequired ()
    {
        return m_isSysLogRequired;
    }

    public void setIsSysLogRequired (final boolean isSysLogRequired)
    {
        m_isSysLogRequired = isSysLogRequired;
    }

    public boolean getIsDatabaseEnabled ()
    {
        return m_isDatabaseEnabled;
    }

    public void setIsDatabaseEnabled (final boolean isDatabaseEnabled)
    {
        m_isDatabaseEnabled = isDatabaseEnabled;
    }

    public boolean getIsDatabaseLogEnabled ()
    {
        return m_isDatabaseLogEnabled;
    }

    public void setIsDatabaseLogEnabled (final boolean isDatabaseLogEnabled)
    {
        m_isDatabaseLogEnabled = isDatabaseLogEnabled;
    }

    public int getPort ()
    {
        return m_port;
    }

    public void setPort (final int port)
    {
        m_port = port;
    }

    public int getDatabasePort ()
    {
        return m_databasePort;
    }

    public void setDatabasePort (final int databasePort)
    {
        m_databasePort = databasePort;
    }

    public String getDatabaseLogFileName ()
    {
        return m_databaseLogFileName;
    }

    public void setDatabaseLogFileName (final String databaseLogFileName)
    {
        m_databaseLogFileName = databaseLogFileName;
    }

    public String getDatabaseSharedBuffers ()
    {
        return m_databaseSharedBuffers;
    }

    public void setDatabaseSharedBuffers (final String databaseSharedBuffers)
    {
        m_databaseSharedBuffers = databaseSharedBuffers;
    }

    public int getManagementPort ()
    {
        return m_managementPort;
    }

    public void setManagementPort (final int managementPort)
    {
        m_managementPort = managementPort;
    }

    public String getEthernetInterface ()
    {
        return m_ethernetInterface;
    }

    public void setEthernetInterface (final String ethernetInterface)
    {
        m_ethernetInterface = ethernetInterface;
    }

    public int getManagementClientPort ()
    {
        return m_managementClientPort;
    }

    public void setManagementClientPort (final int managementClientPort)
    {
        m_managementClientPort = managementClientPort;
    }

    public String getChangeDirectoryTo ()
    {
        return m_changeDirectoryTo;
    }

    public void setChangeDirectoryTo (final String changeDirectoryTo)
    {
        m_changeDirectoryTo = changeDirectoryTo;
    }

    public Vector<String> getYinPaths ()
    {
        return m_yinPaths;
    }

    public void setYinPaths (final Vector<String> yinPaths)
    {
        m_yinPaths = yinPaths;
    }

    public String getWyserTagsFilePath ()
    {
        return m_wyserTagsFilePath;
    }

    public void setWyserTagsFilePath (final String wyserTagsFilePath)
    {
        m_wyserTagsFilePath = wyserTagsFilePath;
    }

    public String getDatabaseEmptyType ()
    {
        return m_databaseEmptyType;
    }

    public void setDatabaseEmptyType (final String databaseEmptyType)
    {
        m_databaseEmptyType = databaseEmptyType;
    }

    public long getDatabaseEmptyTypeAutoDetectionThresholdValue ()
    {
        return m_databaseEmptyTypeAutoDetectionThresholdValue;
    }

    public void setDatabaseEmptyTypeAutoDetectionThresholdValue (final long databaseEmptyTypeAutoDetectionThresholdValue)
    {
        m_databaseEmptyTypeAutoDetectionThresholdValue = databaseEmptyTypeAutoDetectionThresholdValue;
    }

    public String getConfigurationFile ()
    {
        return m_configurationFile;
    }

    public void setConfigurationFile (final String configurationFile)
    {
        m_configurationFile = configurationFile;
    }

    public String getConfigurationFileDirectory ()
    {
        return m_configurationFileDirectory;
    }

    public void setConfigurationFileDirectory (final String configurationFileDirectory)
    {
        m_configurationFileDirectory = configurationFileDirectory;
    }

    public String getApplicationCompactName ()
    {
        if (null != m_application)
        {
            return (m_application.getApplicationCompactName ());
        }
        else
        {
            return ("");
        }
    }

    public String getGlobalConfigurationFile ()
    {
        return m_globalConfigurationFile;
    }

    public void setGlobalConfigurationFile (final String globalConfigurationFile)
    {
        m_globalConfigurationFile = globalConfigurationFile;
    }

    public String getLockFileForConfigurationFile ()
    {
        return m_lockFileForConfigurationFile;
    }

    public void setLockFileForConfigurationFile (final String lockFileForConfigurationFile)
    {
        m_lockFileForConfigurationFile = lockFileForConfigurationFile;
    }

    public String getTraceFileDirectory ()
    {
        return m_traceFileDirectory;
    }

    public void setTraceFileDirectory (final String traceFileDirectory)
    {
        m_traceFileDirectory = traceFileDirectory;
    }

    public String getTraceFileName ()
    {
        return m_traceFileName;
    }

    public void setTraceFileName (final String traceFileName)
    {
        m_traceFileName = traceFileName;
    }

    public String getProfileFileName ()
    {
        return m_profileFileName;
    }

    public void setProfileFileName (final String profileFileName)
    {
        m_profileFileName = profileFileName;
    }
}
