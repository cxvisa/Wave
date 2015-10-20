/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core;

import com.CxWave.Wave.Framework.Database.DatabaseObjectManager;
import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
import com.CxWave.Wave.Framework.ToolKits.TimeZone.TimeZoneToolKit;
import com.CxWave.Wave.Framework.Utils.Random.WaveRandomGenerator;
import com.CxWave.Wave.Resources.ResourceEnums.WaveManagementInterfaceRole;
import com.CxWave.Wave.SystemManagement.SystemManagementToolKit;

public class Wave
{
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

    }
}
