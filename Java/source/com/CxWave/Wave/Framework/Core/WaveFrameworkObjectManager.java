/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core;

import com.CxWave.Wave.Framework.LocationManagement.Location;
import com.CxWave.Wave.Framework.LocationManagement.LocationBase;
import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManager;
import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
import com.CxWave.Wave.Framework.Type.LocationId;
import com.CxWave.Wave.Framework.Type.SI32;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.LocationRole;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class WaveFrameworkObjectManager extends WaveLocalObjectManager
{
    private static WaveFrameworkObjectManager s_waveFrameworkObjectManager;

    private static String                     s_frameworkConfigurationFile           = null;
    private static String                     s_frameworkConfigurationBackupFile     = null;
    private static String                     s_frameworkGlobalConfigurationFile     = null;
    private static String                     s_frameworkGlobalConfigurationTempFile = null;
    private static String                     s_lockFileForConfigurationFile         = null;

    private static boolean                    s_isFrameworkInstantiated              = false;
    private static WaveMutex                  s_instantiationMutex                   = new WaveMutex ();

    private LocationBase                      m_thisLocation                         = null;

    private static String                     s_ipAddressForThisLocation             = null;

    private static LocationRole               s_locationRole                         = LocationRole.LOCATION_STAND_ALONE;
    private static SI32                       s_locationPort                         = new SI32 (3016);

    private WaveFrameworkObjectManager ()
    {
        super (getServiceName ());

        setIsInstantiated ();

        setIsEnabled (true);

        if (LocationRole.LOCATION_STAND_ALONE == s_locationRole)
        {
            configureThisLocationAsLocation (s_locationPort);

            System.out.printf ("Successfully configured this location as a location.");
        }
        else
        {
            System.err.printf ("Could not configure this location.  Unknown Location Role");
            WaveAssertUtils.waveAssert ();
        }
    }

    public static String getServiceName ()
    {
        return ("Wave Framework");
    }

    public static WaveFrameworkObjectManager getInstance ()
    {
        if (null == s_waveFrameworkObjectManager)
        {
            s_waveFrameworkObjectManager = new WaveFrameworkObjectManager ();
        }

        WaveAssertUtils.waveAssert (null != s_waveFrameworkObjectManager);

        return (s_waveFrameworkObjectManager);
    }

    public WaveServiceId getWaveServiceId ()
    {
        return ((getInstance ()).getWaveServiceId ());
    }

    public static void setConfigurationFile (final String configurationFile)
    {
        s_frameworkConfigurationFile = configurationFile;
        s_frameworkConfigurationBackupFile = s_frameworkConfigurationFile + ".bk";
    }

    public static void setGlobalConfigurationFile (final String globalConfigurationFile)
    {
        s_frameworkGlobalConfigurationFile = globalConfigurationFile;
        s_frameworkGlobalConfigurationTempFile = s_frameworkGlobalConfigurationFile + ".tmp";
    }

    public static String getLockFileForConfigurationFile ()
    {
        return s_lockFileForConfigurationFile;
    }

    public static void setLockFileForConfigurationFile (final String lockFileForConfigurationFile)
    {
        s_lockFileForConfigurationFile = lockFileForConfigurationFile;
    }

    public static boolean getIsInstantiated ()
    {
        boolean isInstantiated = false;

        s_instantiationMutex.lock ();

        isInstantiated = s_isFrameworkInstantiated;

        s_instantiationMutex.unlock ();

        return (isInstantiated);
    }

    private static void setIsInstantiated ()
    {
        s_instantiationMutex.lock ();

        s_isFrameworkInstantiated = true;

        s_instantiationMutex.unlock ();
    }

    private void configureThisLocationAsLocation (final SI32 port)
    {
        if (null != m_thisLocation)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager.configureThisLocationAsLocation : This location is already configured.");
            WaveAssertUtils.waveAssert ();
        }

        String ipAddressForThisLocation = getIpAddressForThisLocation ();

        if (WaveStringUtils.isBlank (ipAddressForThisLocation))
        {
            ipAddressForThisLocation = FrameworkToolKit.getLoopbackIpV4AddressForThisMachine ();
        }

        final LocationId locationId = new LocationId (new UI32 (1L << 8));

        m_thisLocation = new Location (locationId, ipAddressForThisLocation, port);

        if (null == m_thisLocation)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager.configureThisLocationAsLocation : Could not allocate a Location.");

            WaveAssertUtils.waveAssert ();

            return;
        }

        m_thisLocation.setClusterPrimaryLocationId (locationId);
        m_thisLocation.setClusterPrimaryPort (port);
    }

    public static void setIpAddressForThisLocation (final String ipAddressForThisLocation)
    {
        s_ipAddressForThisLocation = ipAddressForThisLocation;
    }

    public static String getIpAddressForThisLocation ()
    {
        return (s_ipAddressForThisLocation);
    }

    public static void configureAsLocation (final SI32 port)
    {
        s_locationRole = LocationRole.LOCATION_STAND_ALONE;
        s_locationPort = port;
    }

    public LocationBase getThisLocation ()
    {
        return (m_thisLocation);
    }
}
