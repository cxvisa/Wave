/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core;

import com.CxWave.Wave.Framework.Core.Configuration.WaveMainApplication;
import com.CxWave.Wave.Framework.Core.Configuration.WaveMainConfiguration;
import com.CxWave.Wave.Framework.Database.DatabaseObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.Serialization.SerializableObjectRepository;
import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
import com.CxWave.Wave.Framework.ToolKits.TimeZone.TimeZoneToolKit;
import com.CxWave.Wave.Framework.Trace.TraceObjectManager;
import com.CxWave.Wave.Framework.Utils.Network.WaveNetworkUtils;
import com.CxWave.Wave.Framework.Utils.Random.WaveRandomGenerator;
import com.CxWave.Wave.Framework.Utils.Source.SourceUtils;
import com.CxWave.Wave.Framework.Utils.Stack.WaveStackUtils;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;
import com.CxWave.Wave.Resources.ResourceEnums.WaveManagementInterfaceRole;
import com.CxWave.Wave.SystemManagement.SystemManagementToolKit;

public class Wave
{
    private static WaveMutex s_waveMutex                      = new WaveMutex ();
    private static String    s_waveConfigurationFileDirectory = null;
    private static String    s_waveTraceFileDirectory         = null;

    private Wave ()
    {
    }

    public static void initialize (final String waveMainConfigurationFile)
    {
        final WaveMainConfiguration waveMainConfiguration = new WaveMainConfiguration ();

        if (SourceUtils.getIsInitialized ())
        {
            if (WaveStringUtils.isNotBlank (waveMainConfigurationFile))
            {
                waveMainConfiguration.loadFromWaveConfigurationFile (waveMainConfigurationFile);
            }
        }

        initialize (waveMainConfiguration, waveMainConfigurationFile);
    }

    public static void initialize (final WaveMainConfiguration waveMainConfiguration, final String waveMainConfigurationFile)
    {
        final String mainClassCompactNameForThisThread = WaveStackUtils.getMainClassCompactNameForThisThread ();

        // Initialize Random Generator

        WaveRandomGenerator.initialize ();

        // Set the Management Interface Role

        FrameworkToolKit.setWaveManagementInterfaceRole (WaveManagementInterfaceRole.WAVE_MGMT_INTF_ROLE_SERVER);

        // Initialize Framework ToolKit.

        FrameworkToolKit.initialize ();

        // Initialize time zone information

        TimeZoneToolKit.initialize ();

        // WaveFrameworkObjectManager must be the first one to be created.

        final WaveFrameworkObjectManager waveFrameworkObjectManager = WaveFrameworkObjectManager.getInstance ();

        // Set if the database is to be enabled.

        DatabaseObjectManager.setIsDatabaseEnabled ((waveMainConfiguration.getDatabase ()).getEnable ());
        DatabaseObjectManager.setDatabasePort ((waveMainConfiguration.getDatabase ()).getPort ());

        // Setup the System Management;

        SystemManagementToolKit.setYinPaths (waveMainConfiguration.getYinPaths ());
        SystemManagementToolKit.setWyserTagsFilePath (waveMainConfiguration.getWyserTagsFilePath ());

        String waveConfigurationFile = null;
        String waveConfigurationFileDirectory = null;
        String waveGlobalConfigurationFile = null;
        String waveLockFileForConfigurationFile = null;
        String waveTraceFileDirectory = null;
        String waveTraceFileName = null;

        if (WaveStringUtils.isBlank (waveMainConfiguration.getConfigurationFile ()))
        {
            waveConfigurationFile = (waveMainConfiguration.getApplicationCompactName ()) + ".cfg";
        }
        else
        {
            waveConfigurationFile = waveMainConfiguration.getConfigurationFile ();
        }

        if (WaveStringUtils.isBlank (waveMainConfiguration.getConfigurationFileDirectory ()))
        {
            waveConfigurationFileDirectory = getConfigurationFileDirectory ();
        }
        else
        {
            waveConfigurationFileDirectory = waveMainConfiguration.getConfigurationFileDirectory ();
        }

        if (WaveStringUtils.isBlank (waveMainConfiguration.getGlobalConfigurationFile ()))
        {
            waveGlobalConfigurationFile = (waveMainConfiguration.getApplicationCompactName ()) + ".global.cfg";
        }
        else
        {
            waveGlobalConfigurationFile = waveMainConfiguration.getGlobalConfigurationFile ();
        }

        if (WaveStringUtils.isBlank (waveMainConfiguration.getLockFileForConfigurationFile ()))
        {
            waveLockFileForConfigurationFile = (waveMainConfiguration.getApplicationCompactName ()) + ".cfg.tmp";
        }
        else
        {
            waveLockFileForConfigurationFile = waveMainConfiguration.getLockFileForConfigurationFile ();
        }

        if (WaveStringUtils.isBlank (waveMainConfiguration.getTraceFileDirectory ()))
        {
            waveTraceFileDirectory = getTraceFileDirectory ();
        }
        else
        {
            waveTraceFileDirectory = waveMainConfiguration.getTraceFileDirectory ();
        }

        if (WaveStringUtils.isBlank (waveMainConfiguration.getTraceFileName ()))
        {
            if (WaveStringUtils.isNotBlank (waveMainConfiguration.getApplicationCompactName ()))
            {
                waveTraceFileName = (waveMainConfiguration.getApplicationCompactName ()) + ".trc";
            }
            else
            {
                waveTraceFileName = mainClassCompactNameForThisThread + ".trc";
            }
        }
        else
        {
            waveTraceFileName = waveMainConfiguration.getTraceFileName ();
        }

        WaveFrameworkObjectManager.setConfigurationFile (waveConfigurationFileDirectory + "/" + waveConfigurationFile);
        WaveFrameworkObjectManager.setGlobalConfigurationFile (waveConfigurationFileDirectory + "/" + waveGlobalConfigurationFile);
        WaveFrameworkObjectManager.setLockFileForConfigurationFile (waveConfigurationFileDirectory + "/" + waveLockFileForConfigurationFile);

        String waveTraceFilePath = waveTraceFileDirectory + "/" + waveTraceFileName;

        TraceObjectManager.setWaveTraceFileName (waveTraceFilePath);

        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_SUCCESS, "Trace file is being set to : " + waveTraceFilePath, true, false);

        // Initialize Source Utils

        SourceUtils.initialize ();

        // If the waveMainConfiguration is already not loaded, then since we have initialized SourceUtils, we should try to
        // reload it again
        // In this case, initially the trace file will be .trc file and in the following if block it will be reset using the
        // values form the WaveMainConfiguration.

        if ((WaveStringUtils.isNotBlank (waveMainConfigurationFile)) && (!(waveMainConfiguration.isPreparedForSerialization ())))
        {
            waveMainConfiguration.loadFromWaveConfigurationFile (waveMainConfigurationFile);

            if (WaveStringUtils.isBlank (waveMainConfiguration.getConfigurationFile ()))
            {
                waveConfigurationFile = (waveMainConfiguration.getApplicationCompactName ()) + ".cfg";
            }
            else
            {
                waveConfigurationFile = waveMainConfiguration.getConfigurationFile ();
            }

            if (WaveStringUtils.isBlank (waveMainConfiguration.getConfigurationFileDirectory ()))
            {
                waveConfigurationFileDirectory = getConfigurationFileDirectory ();
            }
            else
            {
                waveConfigurationFileDirectory = waveMainConfiguration.getConfigurationFileDirectory ();
            }

            if (WaveStringUtils.isBlank (waveMainConfiguration.getGlobalConfigurationFile ()))
            {
                waveGlobalConfigurationFile = (waveMainConfiguration.getApplicationCompactName ()) + ".global.cfg";
            }
            else
            {
                waveGlobalConfigurationFile = waveMainConfiguration.getGlobalConfigurationFile ();
            }

            if (WaveStringUtils.isBlank (waveMainConfiguration.getLockFileForConfigurationFile ()))
            {
                waveLockFileForConfigurationFile = (waveMainConfiguration.getApplicationCompactName ()) + ".cfg.tmp";
            }
            else
            {
                waveLockFileForConfigurationFile = waveMainConfiguration.getLockFileForConfigurationFile ();
            }

            if (WaveStringUtils.isBlank (waveMainConfiguration.getTraceFileDirectory ()))
            {
                waveTraceFileDirectory = getTraceFileDirectory ();
            }
            else
            {
                waveTraceFileDirectory = waveMainConfiguration.getTraceFileDirectory ();
            }

            if (WaveStringUtils.isBlank (waveMainConfiguration.getTraceFileName ()))
            {
                if (WaveStringUtils.isNotBlank (waveMainConfiguration.getApplicationCompactName ()))
                {
                    waveTraceFileName = (waveMainConfiguration.getApplicationCompactName ()) + ".trc";
                }
                else
                {
                    waveTraceFileName = mainClassCompactNameForThisThread + ".trc";
                }
            }
            else
            {
                waveTraceFileName = waveMainConfiguration.getTraceFileName ();
            }

            WaveFrameworkObjectManager.setConfigurationFile (waveConfigurationFileDirectory + "/" + waveConfigurationFile);
            WaveFrameworkObjectManager.setGlobalConfigurationFile (waveConfigurationFileDirectory + "/" + waveGlobalConfigurationFile);
            WaveFrameworkObjectManager.setLockFileForConfigurationFile (waveConfigurationFileDirectory + "/" + waveLockFileForConfigurationFile);

            waveTraceFilePath = waveTraceFileDirectory + "/" + waveTraceFileName;

            if (!(WaveStringUtils.endsWith (waveTraceFilePath, ".trc")))
            {
                waveTraceFilePath = waveTraceFilePath + ".trc";
            }

            final String alreadyExistingWaveTraceFileName = TraceObjectManager.getWaveTraceFileName ();

            if (!(waveTraceFilePath.equals (alreadyExistingWaveTraceFileName)))
            {
                TraceObjectManager.resetWaveTraceFileName (waveTraceFilePath);
            }

            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_SUCCESS, "Trace file is being set to : " + waveTraceFilePath, true, false);
        }

        WaveFrameworkObjectManager.bootSelf ();

        // Initialize Serialization for the System

        (SerializableObjectRepository.getInstance ()).initialize ();

        // Set the ip address for the system.

        final WaveMainApplication waveMainApplication = waveMainConfiguration.getApplication ();
        final String ethernetInterface = null;

        if (null != waveMainApplication)
        {
            waveMainApplication.getEthernetInterface ();
        }

        String ipAddress = null;

        if (WaveStringUtils.isNotBlank (ethernetInterface))
        {
            ipAddress = WaveNetworkUtils.getAIpV4PublicAddressForInterface (ethernetInterface);
        }

        if (WaveStringUtils.isBlank (ipAddress))
        {
            ipAddress = WaveNetworkUtils.getIpV4LoopbackAddress ();
        }

        WaveFrameworkObjectManager.setIpAddressForThisLocation (ipAddress);
    }

    private static String getConfigurationFileDirectory ()
    {
        String waveConfigurationFileDirectory = null;

        s_waveMutex.lock ();

        if (WaveStringUtils.isNotBlank (s_waveConfigurationFileDirectory))
        {
            waveConfigurationFileDirectory = s_waveConfigurationFileDirectory;
        }
        else
        {
            waveConfigurationFileDirectory = s_waveConfigurationFileDirectory = FrameworkToolKit.getProcessInitialWorkingDirectory ();
        }

        s_waveMutex.unlock ();

        return (waveConfigurationFileDirectory);
    }

    private static String getTraceFileDirectory ()
    {
        String waveTraceFileDirectory = null;

        s_waveMutex.lock ();

        if (WaveStringUtils.isNotBlank (s_waveTraceFileDirectory))
        {
            waveTraceFileDirectory = s_waveTraceFileDirectory;
        }
        else
        {
            waveTraceFileDirectory = s_waveTraceFileDirectory = FrameworkToolKit.getProcessInitialWorkingDirectory ();
        }

        s_waveMutex.unlock ();

        return (waveTraceFileDirectory);
    }
}
