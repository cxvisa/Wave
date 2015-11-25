/***********************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.ToolKits.Framework;

import com.CxWave.Wave.Framework.Core.WaveFrameworkObjectManager;
import com.CxWave.Wave.Framework.LocationManagement.LocationBase;
import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.MultiThreading.WaveThread;
import com.CxWave.Wave.Framework.ObjectModel.ReservedWaveLocalObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.Type.LocationId;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
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

    public static String getServiceNameById (final WaveServiceId id)
    {
        return (WaveThread.getWaveServiceNameForServiceId (id));
    }

    public static String getLoopbackIpV4AddressForThisMachine ()
    {
        return ("127.0.0.1");
    }

    public static LocationBase getThisLocation ()
    {
        return ((WaveFrameworkObjectManager.getInstance ()).getThisLocation ());
    }

    public static LocationId getPhysicalLocationId ()
    {
        final LocationBase locationBase = getThisLocation ();

        if (null != locationBase)
        {
            return (locationBase.getLocationId ());
        }
        else
        {
            return (LocationId.NullLocationId);
        }
    }

    public static WaveManagementInterfaceRole getManagementInterfaceRole ()
    {
        return (s_waveManagementInterfaceRole);
    }

    public static LocationId getThisLocationId ()
    {
        LocationId locationid = getPhysicalLocationId ();
        final WaveManagementInterfaceRole waveManagementInterfaceRole = getManagementInterfaceRole ();

        if (WaveManagementInterfaceRole.WAVE_MGMT_INTF_ROLE_SERVER == waveManagementInterfaceRole)
        {
            final WaveObjectManager waveObjectManagerForCurrentThread = WaveThread.getWaveObjectManagerForCurrentThread ();

            if (!((WaveThread.getSelf ()).equals ((WaveThread.getWaveThreadForServiceId (ReservedWaveLocalObjectManager.getWaveServiceId ())).getId ())))
            {
                final WaveMessage waveMessage = waveObjectManagerForCurrentThread.getInputMessage ();
                if ((null != waveMessage) && (waveMessage.getIsMessageBeingSurrogatedFlag ()))
                {
                    locationid = waveMessage.getSurrogatingForLocationId ();
                }
            }
        }

        return (locationid);
    }

    public static boolean isALocalService (final WaveServiceId waveServiceId)
    {
        return (WaveLocalObjectManager.isALocalService (waveServiceId));
    }

    public static LocationId getClusterPrimaryLocationId ()
    {
        final LocationBase locationBase = getThisLocation ();

        if (null != locationBase)
        {
            return (locationBase.getClusterPrimaryLocationId ());
        }
        else
        {
            return (LocationId.NullLocationId);
        }
    }
}
