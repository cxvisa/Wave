/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.ToolKits.Framework;

import java.util.Vector;

import com.CxWave.Wave.Framework.Core.WaveFrameworkObjectManager;
import com.CxWave.Wave.Framework.LocationManagement.LocationBase;
import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.MultiThreading.WaveThread;
import com.CxWave.Wave.Framework.ObjectModel.ReservedWaveLocalObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.Trace.TraceObjectManager;
import com.CxWave.Wave.Framework.Type.LocationId;
import com.CxWave.Wave.Framework.Type.SI32;
import com.CxWave.Wave.Framework.Type.TraceClientId;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.ManagementInterface.ClientInterface.WaveClientTransportObjectManager;
import com.CxWave.Wave.Resources.Repository.WaveResourcesRepository;
import com.CxWave.Wave.Resources.ResourceEnum.WaveResourceEnumInterface;
import com.CxWave.Wave.Resources.ResourceEnums.LocationRole;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.WaveManagementInterfaceRole;
import com.CxWave.Wave.Resources.ResourceEnums.WaveResourcesRepositoryPopulator;
import com.CxWave.Wave.Shell.ShellDebug;
import com.CxWave.Wave.Shell.Annotations.ShellCommand;

public class FrameworkToolKit
{
    private static SI32                        s_httpInterfaceReceiverPort      = new SI32 (2301);
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

    public static WaveServiceId getServiceIdByName (final String serviceName)
    {
        WaveServiceId waveServiceId = null;
        final WaveManagementInterfaceRole waveManagementInterfaceRole = getManagementInterfaceRole ();

        if ((WaveManagementInterfaceRole.WAVE_MGMT_INTF_ROLE_SERVER == waveManagementInterfaceRole) || (WaveManagementInterfaceRole.WAVE_MGMT_INTF_ROLE_CLI == waveManagementInterfaceRole))
        {
            waveServiceId = WaveThread.getWaveServiceIdForServiceName (serviceName);
        }
        else
        {
            waveServiceId = WaveClientTransportObjectManager.getWaveServiceId ();
        }

        WaveTraceUtils.debugTracePrintf ("FrameworkToolKit.getServiceIdByName : Service Name : %s : %l", serviceName, waveServiceId.getId ());

        return (waveServiceId);
    }

    public static String getLoopbackIpV4AddressForThisMachine ()
    {
        return ("127.0.0.1");
    }

    public static LocationBase getThisLocation ()
    {
        WaveFrameworkObjectManager temp = null;

        if (isFrameworkReadyToBoot ())
        {
            temp = WaveFrameworkObjectManager.getInstance ();
        }

        if (null != temp)
        {
            return (temp.getThisLocation ());
        }
        else
        {
            return (null);
        }
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

    public static boolean isFrameworkReadyToBoot ()
    {
        return (WaveFrameworkObjectManager.getIsFrameworkReadyToBoot ());
    }

    public static String localize (final WaveResourceEnumInterface waveResourceEnumInterface)
    {
        final int effectiveResourceId = waveResourceEnumInterface.getEffectiveResourceId ();

        final WaveResourcesRepository waveResourcesRepository = WaveResourcesRepository.getInstance ();

        if (null != waveResourcesRepository)
        {
            return (waveResourcesRepository.getResourceValueById (effectiveResourceId));
        }
        else
        {
            return (null);
        }
    }

    public static boolean isStandAloneLocation ()
    {
        return (LocationRole.LOCATION_STAND_ALONE == (getThisLocationRole ()));
    }

    public static LocationRole getThisLocationRole ()
    {
        final LocationBase thisLocation = getThisLocation ();

        if (null != thisLocation)
        {
            return (thisLocation.getLocationRole ());
        }
        else
        {
            return (LocationRole.LOCATION_STAND_ALONE);
        }
    }

    public static boolean isPrimaryLocation ()
    {
        return ((LocationRole.LOCATION_PRIMARY == (getThisLocationRole ())) || (LocationRole.LOCATION_PRIMARY_UNCONFIRMED == (getThisLocationRole ())) || (LocationRole.LOCATION_SECONDARY_UNCONFIRMED == (getThisLocationRole ())));
    }

    public static boolean isAKnownLocation (final LocationId locationId)
    {
        final LocationBase thisLocation = getThisLocation ();

        if (null != thisLocation)
        {
            return (thisLocation.isAConnectedLocation (locationId));
        }
        else
        {
            return false;
        }
    }

    @ShellCommand (shell = ShellDebug.class, briefHelp = "Localizes a ResourceId in Decimal / Hex format and prints out the corresponding String.")
    public static void localize (final Vector<String> arguments)
    {
        if (null == arguments)
        {
            return;
        }

        for (final String argument : arguments)
        {
            if (WaveStringUtils.isBlank (argument))
            {
                continue;
            }

            int effectiveResourceId = 0;

            if (argument.startsWith ("0x"))
            {
                final String modifiedArgument = argument.replaceFirst ("0x", "");

                effectiveResourceId = Integer.parseInt (modifiedArgument, 16);
            }
            else if (argument.startsWith ("0X"))
            {
                final String modifiedArgument = argument.replaceFirst ("0X", "");

                effectiveResourceId = Integer.parseInt (modifiedArgument, 16);
            }
            else
            {
                effectiveResourceId = Integer.parseInt (argument);
            }

            final ResourceId resourceId = ResourceId.getResourceIdByEffectiveResourceId (effectiveResourceId);

            if (null != resourceId)
            {
                final String localizedResourceId = FrameworkToolKit.localize (resourceId);

                WaveTraceUtils.infoTracePrintf (true, true, "0x%08x - %s", effectiveResourceId, localizedResourceId);
            }
            else
            {
                WaveTraceUtils.infoTracePrintf (true, true, "0x%08x - %s", effectiveResourceId, "U n k n o w n  R e s o u r c e I d");
            }
        }
    }

    @ShellCommand (shell = ShellDebug.class, briefHelp = "Prints brief infromation about currently loaded services.")
    public static void printServices (final Vector<String> arguments)
    {
        final Vector<WaveServiceId> waveServiceIds = new Vector<WaveServiceId> ();
        int numberOfWaveServices;
        int i;

        WaveThread.getListOfServiceIds (waveServiceIds);
        numberOfWaveServices = waveServiceIds.size ();

        for (i = 0; i < numberOfWaveServices; i++)
        {
            WaveTraceUtils.infoTracePrintf (false, true, "%5d:%50s:%10s:%10s\n", waveServiceIds.get (i).getId (), getServiceNameById (waveServiceIds.get (i)), WaveObjectManager.isServiceEnabled (waveServiceIds.get (i)) ? "Enabled" : "Disabled", isALocalService (waveServiceIds.get (i)) ? "Local" : "Global");
        }
    }

    public static SI32 getHttpInterfaceReceiverPort ()
    {
        return s_httpInterfaceReceiverPort;
    }

    public static void setHttpInterfaceReceiverPort (final SI32 httpInterfaceReceiverPort)
    {
        s_httpInterfaceReceiverPort = httpInterfaceReceiverPort;
    }

    public static String getTraceClientNameById (final TraceClientId traceClientId)
    {
        final TraceObjectManager traceObjectManager = TraceObjectManager.getInstance ();

        if (null == traceObjectManager)
        {
            return ("");
        }

        return (traceObjectManager.getTraceClientName (traceClientId));
    }
}
