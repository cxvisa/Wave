/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core;

import com.CxWave.Wave.Framework.Database.DatabaseObjectManager;
import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
import com.CxWave.Wave.Framework.Utils.Random.WaveRandomGenerator;
import com.CxWave.Wave.Resources.ResourceEnums.WaveManagementInterfaceRole;

public class Wave
{
    private Wave ()
    {
    }

    public void initialize (final WaveMainConfiguration waveMainConfiguration)
    {
        // Initialize Random Generator

        WaveRandomGenerator.initialize ();

        // Set the Management Interface Role

        FrameworkToolKit.setWaveManagementInterfaceRole (WaveManagementInterfaceRole.WAVE_MGMT_INTF_ROLE_SERVER);

        // Set if the database is to be enabled.

        DatabaseObjectManager.setIsDatabaseEnabled (waveMainConfiguration.getIsDatabaseEnabled ());
        DatabaseObjectManager.setDatabasePort (waveMainConfiguration.getDatabasePort ());
    }
}
