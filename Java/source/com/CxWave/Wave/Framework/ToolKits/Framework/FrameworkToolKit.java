/***********************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.ToolKits.Framework;

import com.CxWave.Wave.Resources.ResourceEnums.WaveManagementInterfaceRole;
import com.CxWave.Wave.Resources.ResourceEnums.WaveResourcesRepositoryPopulator;

public class FrameworkToolKit
{
    private static boolean                     s_isRunningAsADaemon             = false;
    private static WaveManagementInterfaceRole s_waveManagementInterfaceRole    = WaveManagementInterfaceRole.WAVE_MGMT_INTF_ROLE_SERVER;
    private static String                      s_processInitialWorkingDirectory = "";

    private FrameworkToolKit ()
    {
    }

    public static void initialize ()
    {
        initializeEnvironment ();

        s_processInitialWorkingDirectory = System.getProperty ("user.dir");

        WaveResourcesRepositoryPopulator.initializeWaveResourceIds ();
    }

    private static void initializeEnvironment ()
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

    public static int getNumberOfCpus ()
    {
        return ((Runtime.getRuntime ()).availableProcessors ());
    }

    public static String getProcessInitialWorkingDirectory ()
    {
        return s_processInitialWorkingDirectory;
    }

    public static void setProcessInitialWorkingDirectory (final String processInitialWorkingDirectory)
    {
        s_processInitialWorkingDirectory = processInitialWorkingDirectory;
    }
}
