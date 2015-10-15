/***********************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.ToolKits.Framework;

import com.CxWave.Wave.Resources.ResourceEnums.WaveManagementInterfaceRole;

public class FrameworkToolKit
{
    private static boolean                     s_isRunningAsADaemon          = false;
    private static WaveManagementInterfaceRole s_waveManagementInterfaceRole = WaveManagementInterfaceRole.WAVE_MGMT_INTF_ROLE_SERVER;

    private FrameworkToolKit ()
    {
    }

    public static boolean getIsRunningAsADaemon ()
    {
        return (s_isRunningAsADaemon);
    }

    public static void setIsRunningAsADaemon (final boolean isRunningAsADaemon)
    {
        s_isRunningAsADaemon = isRunningAsADaemon;
    }

    public static WaveManagementInterfaceRole getWaveManagementInterfaceRole ()
    {
        return (s_waveManagementInterfaceRole);
    }

    public static void setWaveManagementInterfaceRole (final WaveManagementInterfaceRole waveManagementInterfaceRole)
    {
        s_waveManagementInterfaceRole = waveManagementInterfaceRole;
    }
}
