/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core;

import com.CxWave.Wave.Framework.Core.Messages.WaveBootObjectManagerMessage;
import com.CxWave.Wave.Framework.Core.Messages.WaveEnableObjectManagerMessage;
import com.CxWave.Wave.Framework.Core.Messages.WaveInitializeObjectManagerMessage;
import com.CxWave.Wave.Framework.Core.Messages.WaveInstallObjectManagerMessage;
import com.CxWave.Wave.Framework.Core.Workers.WaveFrameworkObjectManagerInitializeWorker;
import com.CxWave.Wave.Framework.LocationManagement.Location;
import com.CxWave.Wave.Framework.LocationManagement.LocationBase;
import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NativeService;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonAutoInstantiableService;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.ObjectManagerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.PrePhaseService;
import com.CxWave.Wave.Framework.ObjectModel.Boot.WaveAsynchronousContextForBootPhases;
import com.CxWave.Wave.Framework.ObjectRelationalMapping.OrmRepository;
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
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;
import com.CxWave.Wave.Resources.ResourceEnums.WaveBootReason;
import com.CxWave.Wave.Resources.ResourceEnums.WaveMessageStatus;
import com.CxWave.Wave.Resources.ResourceEnums.WaveObjectManagerPriority;

@NonAutoInstantiableService
@PrePhaseService
@NativeService
@ObjectManagerPriority (WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_FRAMEWORK)
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

    private LocationId                        m_lastUsedLocationId                   = null;

    private static String                     s_ipAddressForThisLocation             = null;

    private static LocationRole               s_locationRole                         = LocationRole.LOCATION_STAND_ALONE;
    private static SI32                       s_locationPort                         = new SI32 (3016);

    private static final WaveMutex            s_pFrameworkReadinessMutex             = new WaveMutex ();
    private static boolean                    s_isFrameworkReadyToBoot               = false;

    private static FrameworkSequenceGenerator s_curentFrameworkSequenceGenerator     = new FrameworkSequenceGenerator ();

    private WaveFrameworkObjectManager ()
    {
        super (getServiceName ());

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

        // Indicate that the Instantiation of WaveObjectManager is complete.

        setIsInstantiated (true);
        setIsEnabled (true);
    }

    private void bootSelfInternal ()
    {
        // Now send a oneway initialize message to self.

        // We know the service id for the Wave framework object manager must be 1. And it must not be anything else. So we use
        // the value 1 in the next statement.

        // We cannot use WaveFrameworkObjectManager::getWaveServiceId () - it will invariably fail since we are inside the
        // getInstance method
        // We always say it is the first time boot, but, this reason is not to be looked at in the initialize for this OM.

        final WaveInitializeObjectManagerMessage waveInitializeObjectManagerMessage = new WaveInitializeObjectManagerMessage (new WaveServiceId (1L), WaveBootReason.WAVE_BOOT_FIRST_TIME_BOOT);

        WaveMessageStatus status = sendOneWay (waveInitializeObjectManagerMessage);

        if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
        {
            System.err.printf ("Cannot Initialize the Framework.  Cannot continue.  Exiting ...\n");
            WaveAssertUtils.waveAssert ();
        }

        final WaveEnableObjectManagerMessage waveEnableObjectManagerMessage = new WaveEnableObjectManagerMessage (new WaveServiceId (1L), WaveBootReason.WAVE_BOOT_FIRST_TIME_BOOT);

        status = sendOneWay (waveEnableObjectManagerMessage);

        if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
        {
            System.err.printf ("Cannot Enable the Framework.  Cannot continue.  Exiting ...\n");
            WaveAssertUtils.waveAssert ();
        }

        final WaveInstallObjectManagerMessage waveInstallObjectManagerMessage = new WaveInstallObjectManagerMessage (new WaveServiceId (1L), WaveBootReason.WAVE_BOOT_FIRST_TIME_BOOT);

        status = sendOneWay (waveInstallObjectManagerMessage);

        if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
        {
            System.err.printf ("Cannot Install the Framework.  Cannot continue.  Exiting ...\n");
            WaveAssertUtils.waveAssert ();
        }

        final WaveBootObjectManagerMessage waveBootObjectManagerMessage = new WaveBootObjectManagerMessage (new WaveServiceId (1L), WaveBootReason.WAVE_BOOT_FIRST_TIME_BOOT);

        status = sendOneWay (waveBootObjectManagerMessage);

        if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
        {
            System.err.printf ("Cannot Boot the Framework.  Cannot continue.  Exiting ...\n");
            WaveAssertUtils.waveAssert ();
        }
    }

    public static void bootSelf ()
    {
        (getInstance ()).bootSelfInternal ();
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

    public static WaveServiceId getWaveServiceId ()
    {
        return ((getInstance ()).getServiceId ());
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

    private static void setIsInstantiated (final boolean isInstantiated)
    {
        s_instantiationMutex.lock ();

        s_isFrameworkInstantiated = isInstantiated;

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

    public static boolean getIsFrameworkReadyToBoot ()
    {
        boolean isFrameworkReadyToBoot = false;

        s_pFrameworkReadinessMutex.lock ();
        isFrameworkReadyToBoot = s_isFrameworkReadyToBoot;
        s_pFrameworkReadinessMutex.unlock ();

        return (isFrameworkReadyToBoot);
    }

    public static void setIsFrameworkReadyToBoot (final boolean isFrameworkReadyToBoot)
    {
        s_pFrameworkReadinessMutex.lock ();
        s_isFrameworkReadyToBoot = isFrameworkReadyToBoot;
        s_pFrameworkReadinessMutex.unlock ();
    }

    public static void bootWave ()
    {
        setIsFrameworkReadyToBoot (true);
    }

    @Override
    public void boot (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        waveAsynchronousContextForBootPhases.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        waveAsynchronousContextForBootPhases.callback ();

        initializeLastUsedLocationId ();

        final OrmRepository ormRepository = OrmRepository.getInstance ();

        waveAssert (null != ormRepository);

        ormRepository.computeTableSpace ();

        validateAndZeroizeAtBoot ();

        final WaveWorker waveWorker = getAWaveWorkerByWorkerClass (WaveFrameworkObjectManagerInitializeWorker.class);

        waveAssert (null != waveWorker);

        final WaveFrameworkObjectManagerInitializeWorker waveFrameworkObjectManagerInitializeWorker = (WaveFrameworkObjectManagerInitializeWorker) waveWorker;

        waveAssert (null != waveFrameworkObjectManagerInitializeWorker);

        waveFrameworkObjectManagerInitializeWorker.startWaveServices ();
    }

    private void initializeLastUsedLocationId ()
    {
        m_lastUsedLocationId = new LocationId (256);
    }

    private void validateAndZeroizeAtBoot ()
    {
        // TBD
    }

    public static FrameworkSequenceGenerator getCurrentFrameworkSequenceGenerator ()
    {
        return (s_curentFrameworkSequenceGenerator);
    }
}
