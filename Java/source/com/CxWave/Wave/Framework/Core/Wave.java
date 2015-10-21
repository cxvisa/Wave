/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core;

import com.CxWave.Wave.Framework.Database.DatabaseObjectManager;
import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
import com.CxWave.Wave.Framework.ToolKits.TimeZone.TimeZoneToolKit;
import com.CxWave.Wave.Framework.Utils.Random.WaveRandomGenerator;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;
import com.CxWave.Wave.Resources.ResourceEnums.WaveManagementInterfaceRole;
import com.CxWave.Wave.SystemManagement.SystemManagementToolKit;

public class Wave
{
    private static WaveMutex s_waveMutex                      = new WaveMutex ();
    private static String    s_waveConfigurationFileDirectory = null;

    private Wave ()
    {
    }

    public static void initialize (final WaveMainConfiguration waveMainConfiguration)
    {
        // Initialize Random Generator

        WaveRandomGenerator.initialize ();

        // Set the Management Interface Role

        FrameworkToolKit.setWaveManagementInterfaceRole (WaveManagementInterfaceRole.WAVE_MGMT_INTF_ROLE_SERVER);

        // Set if the database is to be enabled.

        DatabaseObjectManager.setIsDatabaseEnabled (waveMainConfiguration.getIsDatabaseEnabled ());
        DatabaseObjectManager.setDatabasePort (waveMainConfiguration.getDatabasePort ());

        // Initialize Framework ToolKit.

        FrameworkToolKit.initialize ();

        // Initialize time zone information

        TimeZoneToolKit.initialize ();

        // Setup the System Management;

        SystemManagementToolKit.setYinPaths (waveMainConfiguration.getYinPaths ());
        SystemManagementToolKit.setWyserTagsFilePath (waveMainConfiguration.getWyserTagsFilePath ());

        String waveConfigurationFile = null;
        String waveConfigurationFileDirectory = null;

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

        WaveFrameworkObjectManager.setConfigurationFile (waveConfigurationFileDirectory + "/" + waveConfigurationFile);
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
}
