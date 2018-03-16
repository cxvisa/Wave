/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/Wave.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/WaveSourceGenerator/WaveSourceGeneratorBase.h"
#include "Framework/Core/FrameworkSequenceGenerator.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Cluster/MultiPartition/Global/MultiPartitionObjectManager.h"
#include "Cluster/MultiPartition/Local/MultiPartitionLocalObjectManager.h"
#include "Framework/DistributedLog/DistributedLogObjectManager.h"
#include "Framework/DistributedLog/Test/DistributedLogTestObjectManager.h"
#include "Framework/Persistence/PersistenceObjectManager.h"
#include "Framework/Persistence/PersistenceLocalObjectManager.h"
#include "Framework/Persistence/Test/PersistenceTestObjectManager.h"
#include "File/Local/Test/FileLocalMessagingTestObjectManager.h"
#include "ManagementInterface/ManagementInterfaceReceiverObjectManager.h"
#include "Framework/Profiling/WaveProfiler.h"
#include "Framework/ObjectRelationalMapping/OrmRepository.h"
#include "Framework/ObjectModel/WaveManagedObject.h"
#include "Framework/ObjectModel/WaveLocalManagedObject.h"
#include "ManagementInterface/ClientInterface/WaveClientReceiverObjectManager.h"
#include "ManagementInterface/ClientInterface/WaveClientTransportObjectManager.h"
#include "ManagementInterface/ClientInterface/WaveUserInterfaceObjectManager.h"
#include "ManagementInterface/ManagementInterfaceObjectManager.h"
#include "Framework/Core/ApplicationSpecificServices.h"
#include "Framework/ObjectModel/ReservedWaveLocalObjectManager.h"
#include "Framework/DistributedDebugInfrastructure/DistributedDebugGlobalObjectManager.h"
#include "Framework/DistributedDebugInfrastructure/DistributedDebugLocalObjectManager.h"
#include "Framework/Utils/TimeZoneToolKit.h"
#include "ManagementInterface/ManagementInterfaceObjectManager.h"
#include "HttpInterface/HttpInterfaceReceiverObjectManager.h"
#include "Framework/Messaging/HaPeer/HaPeerMessageReceiverObjectManager.h"
#include "Framework/Messaging/HaPeer/HaPeerMessageTransportObjectManager.h"
#include "Framework/Core/Test/FrameworkTestability6ObjectManager.h"
#include "SystemManagement/WaveSystemManagementObjectManager.h"
#include "SystemManagement/SystemManagementToolKit.h"
#include "SystemManagement/CommandLineInterface/Server/CommandLineInterfaceReceiverObjectManager.h"
#include "Framework/Messaging/LightHouse/LightPulseDispatchObjectManager.h"
#include "Framework/Messaging/LightHouse/LightHouseReceiverObjectManager.h"
#include "Framework/Messaging/LightHouse/LightHouseTransportObjectManager.h"

#include "ServiceManagement/Global/ServiceManagementObjectManager.h"
#include "ServiceManagement/Local/ServiceManagementLocalObjectManager.h"
#include "Sharding/NetworkDeviceRead/NetworkDeviceReadShardingObjectManager.h"
#include "Sharding/NetworkDeviceWrite/NetworkDeviceWriteShardingObjectManager.h"

#include "Framework/Messaging/LightHouse/Test/LightHouseTestObjectManager1.h"
#include "Framework/Messaging/LightHouse/Test/LightHouseTestObjectManager2.h"
#include "Framework/Messaging/LightHouse/Test/LightHouseTestObjectManager3.h"

#include "gRPC/GrpcGatewayLocalObjectManager.h"

#include "Security/Local/SecurityLocalObjectManager.h"

#include "Framework/Utils/FileUtils.h"

#include <time.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <magic.h>

//Commenting it our for now.  We need to find way to enable it on Solaris.
//extern int daemon (int doNotChangeToRootDir, int doNotCloseFileDescriptors);

static string s_waveTraceFileDirectory         ("");
static string s_waveConfigurationFileDirectory ("");
static string s_waveProfileFileDirectory       ("");

namespace WaveNs
{

vector<NativeWaveServiceInstantiator>          Wave::m_nativeWaveServiceInstantiators;
vector<bool>                                   Wave::m_nativeWaveServiceInstantiatorIsForNormalPhase;
vector<NativeMultipleWaveServiceInstantiator>  Wave::m_nativeMultipleWaveServiceInstantiators;
vector<NativeWaveServiceInstantiator>          Wave::m_nativeApplicationSpecificWaveServiceInstantiators;
vector<ResourceId>                             Wave::m_nativeWaveServiceInstantiationMode;

bool                                           Wave::m_enablePersistenceSupport                           = true;
bool                                           Wave::m_enableClusteringSupport                            = true;
bool                                           Wave::m_enableBuiltInSelfTestSupport                       = true;
bool                                           Wave::m_enableShellSupport                                 = true;
bool                                           Wave::m_enableManagementInterfaceSupport                   = true;
bool                                           Wave::m_enableLicensingSupport                             = true;
bool                                           Wave::m_enableSoftwareManagementSupport                    = true;
bool                                           Wave::m_enableTimerSupport                                 = true;
bool                                           Wave::m_enableHaPeerSupport                                = true;
bool                                           Wave::m_enableDistributedLogSupport                        = true;
bool                                           Wave::m_enableTraceSupport                                 = true;
bool                                           Wave::m_enableFileServiceSupport                           = true;
bool                                           Wave::m_enableSystemManagementSupport                      = true;
bool                                           Wave::m_enableLightHouseSupport                            = true;
bool                                           Wave::m_enableGrpcSupport                                  = true;
bool Wave::m_enableSecuritySupport = true;

PersistencePostBootCheck                       Wave::m_persistencePostBootCheck;
WaveMutex                                      Wave::m_clusterEnabledCheckMutex;
ClusterEnabledCheck                            Wave::m_clusterEnabledCheck  = NULL;
string                                         Wave::m_waveUserClientPath;
string                                         Wave::m_waveUserClientParams;
LogOperationStatusFunction                     Wave::m_logOperationStatusFunction = NULL;
WaveMutex                                      Wave::m_logOperationStatusMutex;
IsWaveClusteringEnabled                        Wave::m_isWaveClusteringEnabled = NULL;
WaveMutex                                      Wave::m_isWaveClusteringEnabledMutex;
GetLinecardReadySlotIdBitMapFunction           Wave::m_linecardReadySlotIdBitMapFunction = NULL;
WaveMutex                                      Wave::m_linecardReadySlotIdBitMapFunctionMutex;

void Wave::enableAllFeatures ()
{
    enablePersistence         ();
    enableClustering          ();
    enableBuiltInSelfTest     ();
    enableShell               ();
    enableManagementInterface ();
    enableLicense             ();
    enableFileService         ();
    enableSoftwareManagement  ();
    enableTimer               ();
    enableTrace               ();
    enableDistributedLog      ();
    enableHaPeer              ();
    enableSystemManagement    ();
    enableLightHouse          ();
    enableGrpc                ();
    enableSecurity ();
}

void Wave::enablePersistence ()
{
    m_enablePersistenceSupport = true;
}

void Wave::disablePersistence ()
{
    m_enablePersistenceSupport = false;
}

void Wave::enableClustering ()
{
    m_enableClusteringSupport = true;
}

void Wave::disableClustering ()
{
    m_enableClusteringSupport = false;
}

void Wave::enableBuiltInSelfTest ()
{
    m_enableBuiltInSelfTestSupport = true;
}

void Wave::disableBuiltInSelfTest ()
{
    m_enableBuiltInSelfTestSupport = false;
}

void Wave::enableShell ()
{
    m_enableShellSupport = true;
}

void Wave::disableShell ()
{
    m_enableShellSupport = false;
}

void Wave::enableManagementInterface ()
{
    m_enableManagementInterfaceSupport = true;
}

void Wave::disableManagementInterface ()
{
    m_enableManagementInterfaceSupport = false;
}

void Wave::enableLicense ()
{
    m_enableLicensingSupport = true;
}

void Wave::disableLicense ()
{
    m_enableLicensingSupport = false;
}

void Wave::enableSoftwareManagement ()
{
    m_enableSoftwareManagementSupport = true;
}

void Wave::disableSoftwareManagement ()
{
    m_enableSoftwareManagementSupport = false;
}

void Wave::enableTimer ()
{
    m_enableTimerSupport = true;
}

void Wave::disableTimer ()
{
    m_enableTimerSupport = false;
}

void Wave::enableTrace ()
{
    m_enableTraceSupport = true;
}

void Wave::disableTrace ()
{
    m_enableTraceSupport = false;
}

void Wave::enableFileService ()
{
    m_enableFileServiceSupport = true;
}

void Wave::disableFileService ()
{
    m_enableFileServiceSupport = false;
}

void Wave::enableDistributedLog ()
{
    m_enableDistributedLogSupport = true;
}

void Wave::disableDistributedLog ()
{
    m_enableDistributedLogSupport = false;
}

void Wave::enableHaPeer ()
{
    m_enableHaPeerSupport = true;
}

void Wave::disableHaPeer ()
{
    m_enableHaPeerSupport = false;
}

void Wave::enableSystemManagement ()
{
    m_enableSystemManagementSupport = true;
}

void Wave::disableSystemManagement ()
{
    m_enableSystemManagementSupport = false;
}

void Wave::enableLightHouse ()
{
    m_enableLightHouseSupport = true;
}

void Wave::disableLightHouse ()
{
    m_enableLightHouseSupport = false;
}

void Wave::enableGrpc ()
{
    m_enableGrpcSupport = true;
}

void Wave::disableGrpc ()
{
    m_enableGrpcSupport = false;
}

void Wave::enableSecurity ()
{
    m_enableSecuritySupport = true;
}

void Wave::disableSecurity ()
{
    m_enableSecuritySupport = false;
}

void Wave::initialize (const WaveMainConfiguration &waveMainConfiguration)
{
    // First change to user specified directory if any

    SI32 rlimitStatus = 0;
    rlimit rlim;

    rlim.rlim_cur = 1048576 * 8;   // 8 MB
    rlim.rlim_max = 1048576 * 8;

    rlimitStatus = setrlimit (RLIMIT_STACK, &rlim);

    if (0 != rlimitStatus)
    {
        trace (TRACE_LEVEL_WARN, "Wave::initialize not able to set rlimit");
    }

    if ("" != (waveMainConfiguration.getChangeDirectoryTo ()))
    {
        SI32 chDirStatus = chdir ((waveMainConfiguration.getChangeDirectoryTo ()).c_str ());

        if (0 != chDirStatus)
        {
            trace (TRACE_LEVEL_ERROR, "Wave::initialize : Could not Change Directory to " + waveMainConfiguration.getChangeDirectoryTo ());
            trace (TRACE_LEVEL_ERROR, "Wave::initialize : Reason listed below :");
            perror ("WAVE");
            waveAssert (false, __FILE__, __LINE__);
        }
    }

    // Initialize Random Generator

    srand (time (NULL));

    // Set the Management Interface Role

    FrameworkToolKit::setManagementInterfaceRole (WAVE_MGMT_INTF_ROLE_SERVER);

    // Set if the database is to be enabled.

    DatabaseObjectManager::setIsDatabaseEnabled (waveMainConfiguration.getIsDatabaseEnabled ());
    DatabaseObjectManager::setDatabasePort (waveMainConfiguration.getDatabasePort ());

    // First record the current working directory as the directory in which the process was started

    FrameworkToolKit::initialize ();

    // Initialize Files utils for magic numbers etc.

    FileUtils::initialize ();

    //Initialize time zone information

    TimeZoneToolKit::initialize ();

    // Setup the System Management;

    SystemManagementToolKit::setYinPaths          (waveMainConfiguration.getYinPaths ());
    SystemManagementToolKit::setWyserTagsFilePath (waveMainConfiguration.getWyserTagsFilePath ());

    // set the Wave Framework configuration file.

    WaveFrameworkObjectManager::setConfigurationFile ((getConfigurationFileDirectory ()) + "/" + waveMainConfiguration.getApplicationCompactName () + ".cfg");
    WaveFrameworkObjectManager::setGlobalConfigurationFile ((getConfigurationFileDirectory ()) + "/" + waveMainConfiguration.getApplicationCompactName () + ".global.cfg");

#ifdef _X86_COMPILE_
    WaveFrameworkObjectManager::setLockFileForConfigurationFile ((getConfigurationFileDirectory ()) + "/" + waveMainConfiguration.getApplicationCompactName () + ".cfg.tmp");
#else
    WaveFrameworkObjectManager::setLockFileForConfigurationFile ("/tmp/" + waveMainConfiguration.getApplicationCompactName () + ".cfg.tmp");
#endif

    // Set the trace file name first

    TraceObjectManager::setTraceFileName ((getTraceFileDirectory ()) + "/" + waveMainConfiguration.getApplicationCompactName () + ".trc");

    // Set the profile file namespace

    WaveProfiler::setProfileFileName ((getProfileFileDirectory ()) + "/" + waveMainConfiguration.getApplicationCompactName () + ".wpd");

    // Set if logging to syslog is required

    TraceObjectManager::setIsSysLogRequired (waveMainConfiguration.getIsSysLogRequired ());

    // Set database logging information and if logging is required.

    DatabaseObjectManager::setDatabaseLogFileName                      (getTraceFileDirectory () + "/" + waveMainConfiguration.getApplicationCompactName () + "." + waveMainConfiguration.getDatabaseLogFileName () + ".log");
    DatabaseObjectManager::setIsDatabaseLogEnabled                     (waveMainConfiguration.getIsDatabaseLogEnabled ());
    DatabaseObjectManager::setEmptyDatabaseType                        (waveMainConfiguration.getDatabaseEmptyType ());
    DatabaseObjectManager::setEmptyDatabaseAutoDetectionThresholdValue (waveMainConfiguration.getDatabaseEmptyTypeAutoDetectionThresholdValue ());
    // Set database runtime parameters

    DatabaseObjectManager::setDatabaseSharedBuffers (waveMainConfiguration.getDatabaseSharedBuffers ());

    // Run the process in daemon mode if required.

    if (true == (waveMainConfiguration.getIsADaemon ()))
    {
        int rc = daemon (1, 0);

        if (0 != rc)
        {
            // handle the error
        }

        FrameworkToolKit::initializeConsolePrintFunction ();
    }

    // Record if the process is running as a daemon.

    FrameworkToolKit::setIsRunningAsADaemon (waveMainConfiguration.getIsADaemon ());

    // Add ORM Repository Most Base Classes information from Wave.

    OrmRepository::addMostBaseClass (WavePersistableObject::getClassName ());
    OrmRepository::addMostBaseClass (WaveManagedObject::getClassName      ());
    OrmRepository::addMostBaseClass (WaveLocalManagedObject::getClassName ());

    // WaveFrameworkObjectManager must be the first one to be created.

    WaveFrameworkObjectManager::getInstance ();

    // ShellObjectManager must be the next one so that all can register their shells and related shell handlers.

    if (true == m_enableShellSupport)
    {
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (ShellObjectManager::getInstance));
    }

    FrameworkToolKit::registerDebugShellEntries ();
    WaveSourceGeneratorBase::registerDebugShellEntries ();
    InterLocationMessageReceiverObjectManager::registerDebugShellEntries ();
    ManagementInterfaceReceiverObjectManager::registerDebugShellEntries ();
    // ManagementInterfaceObjectManager::registerDebugShellEntries ();

    // WARNING! WARNING! WARNING!
    // DO NOT CHANGE ABOVE THIS LINE

    // FrameworkToolKit must be initialized before we call any trace.
    // Trace functionality uses FrameworkToolKit for different directory paths.
    trace(TRACE_LEVEL_PERF_START, "Wave Bootup.");

    // Below this one the services are registered in reverse order.  The last one will be on top of the list.

    if (true == m_enableBuiltInSelfTestSupport)
    {
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (LightHouseTestObjectManager3::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (LightHouseTestObjectManager2::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (LightHouseTestObjectManager1::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (FrameworkTestability6ObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (DistributedLogTestObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (FileLocalMessagingTestObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (PersistenceTestObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (ClusterTestObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (TimerTestObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (TraceTestObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (LicenseTestObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (FrameworkRemoteMessagingTestObjectManager2::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (FrameworkRemoteMessagingTestObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (FrameworkLocalMessagingTestObjectManager2::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (FrameworkLocalMessagingTestObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (FrameworkTestability5ObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (FrameworkTestability4ObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (FrameworkTestability3ObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (FrameworkTestability2ObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (FrameworkTestability1ObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (FrameworkCoreTestObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (RegressionTestObjectManager::getInstance));
    }


    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (NetworkDeviceWriteShardingObjectManager::getInstance));
    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (NetworkDeviceReadShardingObjectManager::getInstance));

    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (ServiceManagementObjectManager::getInstance));
    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (ServiceManagementLocalObjectManager::getInstance));

    if (true == m_enableLightHouseSupport)
    {
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (LightPulseDispatchObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (LightHouseTransportObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (LightHouseReceiverObjectManager::getInstance));
    }

    if (true == m_enableSystemManagementSupport)
    {
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (CommandLineInterfaceReceiverObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (WaveSystemManagementObjectManager::getInstance));
    }

    if (true == m_enablePersistenceSupport)
    {
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (MultiPartitionObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (MultiPartitionLocalObjectManager::getInstance));
    }

    if (true == m_enableClusteringSupport)
    {
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (DistributedDebugGlobalObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (DistributedDebugLocalObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (LockManagementObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (InterLocationMessageReceiverObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (InterLocationMessageTransportObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (CentralClusterConfigObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (ClusterLocalObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (LocalClusterConfigObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (ClusterInterfaceObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (HeartBeatObjectManager::getInstance));
    }

    if (true == m_enableGrpcSupport)
    {
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (GrpcGatewayLocalObjectManager::getInstance));
    }

    if (true == m_enableManagementInterfaceSupport)
    {

        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (HttpInterfaceReceiverObjectManager::getInstance));

        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (ManagementInterfaceReceiverObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (ManagementInterfaceObjectManager::getInstance));

        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (WaveUserInterfaceObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (WaveClientTransportObjectManager::getInstance));
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (WaveClientReceiverObjectManager::getInstance));
    }

    if (true == m_enableFileServiceSupport)
    {
         registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (FileObjectManager::getInstance),false);
         registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (FileLocalObjectManager::getInstance),false);
    }

    if (true == m_enableHaPeerSupport)
    {
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (HaPeerMessageTransportObjectManager::getInstance),false);
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (HaPeerMessageReceiverObjectManager::getInstance),false);
    }

    if (true == m_enableTraceSupport)
    {
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (TraceObjectManager::getInstance));
    }

    if (true == m_enableSoftwareManagementSupport)
    {
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (SoftwareManagementObjectManager::getInstance));
    }

    if (true == m_enableLicensingSupport)
    {
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (LicenseObjectManager::getInstance));
    }

    if (true == m_enableDistributedLogSupport)
    {
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (DistributedLogObjectManager::getInstance));
    }

    if (true == m_enablePersistenceSupport)
    {
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (PersistenceObjectManager::getInstance), false);
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (PersistenceLocalObjectManager::getInstance), false);
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (DatabaseObjectManager::getInstance), false);
    }

    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (ReservedWaveLocalObjectManager::getInstance), false);

    // WARNING! WARNING! WARNING!
    // Always keep the Timer Object Manager as the last registered internal native service.
    // All services will cancel their timers with the Timer Object Manager during shutdown so this service must be the last to shutdown.

    if (true == m_enableTimerSupport)
    {
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (TimerObjectManager::getInstance), false);
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (TimerSignalObjectManager::getInstance), false);
    }

    if (true == m_enableSecuritySupport)
    {
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (SecurityLocalObjectManager::getInstance), false);
    }

    // Instantiate Native Wave Services here

    instantiateNativeWaveServices ();

    // Start the ObjectManager s corresponding to Application Services

    ApplicationService::createNewApplicationServices ();

    // start the ObjectManager s corresponding to Application Local Services

    ApplicationLocalService::createNewApplicationLocalServices ();

    // Starting Application specfic Object managers.

    AppObjectManager::createAppObjectMangers ();
}

string Wave::getTraceFileDirectory ()
{
    static WaveMutex traceFileDirectoryMutex;

    traceFileDirectoryMutex.lock ();

    if ("" != s_waveTraceFileDirectory)
    {
        traceFileDirectoryMutex.unlock ();
        return (s_waveTraceFileDirectory);
    }
    else
    {
        s_waveTraceFileDirectory = FrameworkToolKit::getProcessInitialWorkingDirectory ();

        if ("" == s_waveTraceFileDirectory)
        {
            s_waveTraceFileDirectory = "/tmp";
        }
    }

    traceFileDirectoryMutex.unlock ();

    return (s_waveTraceFileDirectory);
}

string Wave::getConfigurationFileDirectory ()
{
    static WaveMutex configurationFileDirectoryMutex;

    configurationFileDirectoryMutex.lock ();

    if ("" != s_waveConfigurationFileDirectory)
    {
        configurationFileDirectoryMutex.unlock ();
        return (s_waveConfigurationFileDirectory);
    }
    else
    {
        s_waveConfigurationFileDirectory = FrameworkToolKit::getProcessInitialWorkingDirectory ();

        if ("" == s_waveConfigurationFileDirectory)
        {
            s_waveConfigurationFileDirectory = "/tmp";
        }
    }

    configurationFileDirectoryMutex.unlock ();

    return (s_waveConfigurationFileDirectory);
}

string Wave::getProfileFileDirectory ()
{
    static WaveMutex profileFileDirectoryMutex;

    profileFileDirectoryMutex.lock ();

    if ("" != s_waveProfileFileDirectory)
    {
        profileFileDirectoryMutex.unlock ();
        return (s_waveProfileFileDirectory);
    }
    else
    {
        s_waveProfileFileDirectory = FrameworkToolKit::getProcessInitialWorkingDirectory ();

        if ("" == s_waveProfileFileDirectory)
        {
            s_waveProfileFileDirectory = "/tmp";
        }
    }

    profileFileDirectoryMutex.unlock ();

    return (s_waveProfileFileDirectory);
}

void Wave::registerNativeService (NativeWaveServiceInstantiator pNativeWaveServiceInstantiator, const bool &isForNormalPhase, const ResourceId &serviceMode)
{
    m_nativeWaveServiceInstantiators.push_back                (pNativeWaveServiceInstantiator);
    m_nativeWaveServiceInstantiatorIsForNormalPhase.push_back (isForNormalPhase);
    m_nativeWaveServiceInstantiationMode.push_back            (serviceMode);
}

void Wave::registerApplicationSpecificNativeServices (NativeWaveServiceInstantiator pNativeWaveServiceInstantiator, const bool &isForNormalPhase, const ResourceId &serviceMode)
{
    m_nativeApplicationSpecificWaveServiceInstantiators.push_back (pNativeWaveServiceInstantiator);

    registerNativeService (pNativeWaveServiceInstantiator, isForNormalPhase, serviceMode);
}

void Wave::registerNativeServiceInternal (NativeWaveServiceInstantiator pNativeWaveServiceInstantiator, const bool &isForNormalPhase, const ResourceId &serviceMode)
{
    m_nativeWaveServiceInstantiators.insert                (m_nativeWaveServiceInstantiators.begin (), pNativeWaveServiceInstantiator);
    m_nativeWaveServiceInstantiatorIsForNormalPhase.insert (m_nativeWaveServiceInstantiatorIsForNormalPhase.begin (), isForNormalPhase);
    m_nativeWaveServiceInstantiationMode.insert            (m_nativeWaveServiceInstantiationMode.begin (), serviceMode);
}

void Wave::registerNativeService (NativeMultipleWaveServiceInstantiator pNativeMultipleWaveServiceInstantiator)
{
    m_nativeMultipleWaveServiceInstantiators.push_back (pNativeMultipleWaveServiceInstantiator);
}

void Wave::registerPersistencePostBootCheck (PersistencePostBootCheck pPersistencePostBootCheck)
{
    m_persistencePostBootCheck = pPersistencePostBootCheck;
}

ResourceId Wave::persistencePostBootCheck ()
{
    return ((m_persistencePostBootCheck ()));
}

void Wave::registerClusterEnabledCheck (ClusterEnabledCheck pClusterEnabledCheck)
{
    m_clusterEnabledCheckMutex.lock ();

    m_clusterEnabledCheck = pClusterEnabledCheck;

    m_clusterEnabledCheckMutex.unlock ();
}

bool Wave::clusterEnabledCheck ()
{
    bool clusterEnabled = false;

    m_clusterEnabledCheckMutex.lock ();

    if (NULL != m_clusterEnabledCheck)
    {
        clusterEnabled = m_clusterEnabledCheck ();
    }

    m_clusterEnabledCheckMutex.unlock ();

    return clusterEnabled;
}

void Wave::registerIsWaveClusteringEnabledFunction (IsWaveClusteringEnabled pIsWaveClusteringEnabled)
{
    m_isWaveClusteringEnabledMutex.lock ();
    m_isWaveClusteringEnabled = pIsWaveClusteringEnabled ;
    m_isWaveClusteringEnabledMutex.unlock ();
}

bool Wave::isWaveClusteringEnabled ()
{
    bool mode = false;
    m_isWaveClusteringEnabledMutex.lock ();
    mode = m_isWaveClusteringEnabled();
    m_isWaveClusteringEnabledMutex.unlock ();

    return mode;
}

void Wave::registerLogOperationStatusFunction (LogOperationStatusFunction pLogOperationStatusFunction)
{
    m_logOperationStatusMutex.lock ();

    m_logOperationStatusFunction = pLogOperationStatusFunction;

    m_logOperationStatusMutex.unlock ();
}

void Wave::logOperationStatus (ResourceId status)
{
    trace (TRACE_LEVEL_DEBUG, string("Wave::logOperationStatus : status = ") + status);

    m_logOperationStatusMutex.lock ();
    m_logOperationStatusFunction (status);
    m_logOperationStatusMutex.unlock ();
}

void Wave::registerGetLinecardReadySlotIdBitMapFunction ( GetLinecardReadySlotIdBitMapFunction plinecardReadySlotIdBitMapFunction )
{
    m_linecardReadySlotIdBitMapFunctionMutex.lock();

    m_linecardReadySlotIdBitMapFunction = plinecardReadySlotIdBitMapFunction;

    m_linecardReadySlotIdBitMapFunctionMutex.unlock();
}

void Wave::getLinecardReadySlotIdBitMap ( BitMap &linecardReadySlotIdBitMap , UI32 &maxLinecards )
{
    m_linecardReadySlotIdBitMapFunctionMutex.lock();

    maxLinecards = 0;

    if ( NULL != m_linecardReadySlotIdBitMapFunction )
    {
        m_linecardReadySlotIdBitMapFunction ( linecardReadySlotIdBitMap, maxLinecards );
    }

    m_linecardReadySlotIdBitMapFunctionMutex.unlock();
}

void Wave::setWaveUserClientPath (const string &path)
{
    m_waveUserClientPath = path;
}

string Wave::getWaveUserClientPath ()
{
    return (m_waveUserClientPath);
}

void Wave::setWaveUserClientParams (const string &params)
{
    m_waveUserClientParams = params;
}

string Wave::getWaveUserClientParams ()
{
    return (m_waveUserClientParams);
}

void Wave::instantiateNativeWaveServices ()
{
    FrameworkSequenceGenerator &frameworkSequenceGenerator                       = WaveFrameworkObjectManager::getCurrentFrameworkSequenceGenerator ();
    UI32                        numberOfNativeWaveServciesToInstantiate         = m_nativeWaveServiceInstantiators.size ();
    UI32                        numberOfNativeMultipleWaveServciesToInstantiate = m_nativeMultipleWaveServiceInstantiators.size ();
    UI32                        numberOfNativeApplicationSpecificWaveServices   = m_nativeApplicationSpecificWaveServiceInstantiators.size ();
    UI32                        i                                                = 0;
    UI32                        j                                                = 0;
    WaveObjectManager         *pWaveObjectManager                              = NULL;

    for (i = 0; i < numberOfNativeWaveServciesToInstantiate; i++)
    {

        WaveObjectManager::m_waveServiceLaunchMode = (WaveServiceMode) (m_nativeWaveServiceInstantiationMode[i]);

        pWaveObjectManager = (*(m_nativeWaveServiceInstantiators[i])) ();

        waveAssert (NULL != pWaveObjectManager, __FILE__, __LINE__);

        if (WAVE_SERVICE_ACTIVE == m_nativeWaveServiceInstantiationMode[i])
        {
            frameworkSequenceGenerator.addWaveServiceIdToAll (pWaveObjectManager->getServiceId (), m_nativeWaveServiceInstantiatorIsForNormalPhase[i]);

        }
    }

    for (i = 0; i < numberOfNativeMultipleWaveServciesToInstantiate; i++)
    {
        vector<WaveObjectManager *> objectManagers         = (*(m_nativeMultipleWaveServiceInstantiators[i])) ();
        UI32                         numberOfObjectManagers = objectManagers.size ();

        for (j = 0; j < numberOfObjectManagers; j++)
        {
            pWaveObjectManager = objectManagers[j];

            waveAssert (NULL != pWaveObjectManager, __FILE__, __LINE__);

            frameworkSequenceGenerator.addWaveServiceIdToAll (pWaveObjectManager->getServiceId ());
        }
    }

    for (i = 0; i < numberOfNativeApplicationSpecificWaveServices; i++)
    {

        pWaveObjectManager = (*(m_nativeApplicationSpecificWaveServiceInstantiators[i])) ();

        ApplicationSpecificServices *pApplicationSpecificServices = ApplicationSpecificServices::getInstance ();

        pApplicationSpecificServices->setWaveServiceId (pWaveObjectManager->getServiceId ());

        trace (TRACE_LEVEL_DEBUG, string ("ApplicationSpecificWaveServices service ID ") + pWaveObjectManager->getServiceId ());
    }

    trace (TRACE_LEVEL_INFO, string ("Instantiated ") + numberOfNativeWaveServciesToInstantiate + " Native Wave Services");
}

void Wave::waveExit ()
{
#if 0
    map<WaveThreadId, WaveThreadId> mapOfCurrentWaveThreads;

    WaveFrameworkObjectManager::getAllWaveThreads (mapOfCurrentWaveThreads);

    map<WaveThreadId, WaveThreadId>::iterator  threadIterator;

    for (threadIterator = mapOfCurrentWaveThreads.begin (); threadIterator != mapOfCurrentWaveThreads.end (); threadIterator++)
    {
        pthread_cancel (threadIterator->first);
    }

    for (threadIterator = mapOfCurrentWaveThreads.begin (); threadIterator != mapOfCurrentWaveThreads.end (); threadIterator++)
    {
        void *pContext = NULL;

        pthread_join (threadIterator->first, &pContext);
    }
#endif
    WaveFrameworkObjectManager::deleteAllWaveThreads ();

    exit (0);
}

}

extern "C" void setWaveTraceFileDirectory (const char *pWaveTraceFileDirectory)
{
    s_waveTraceFileDirectory = pWaveTraceFileDirectory;
}

extern "C" void setWaveConfigurationFileDirectory (const char *pWaveConfigurationFileDirectory)
{
    s_waveConfigurationFileDirectory = pWaveConfigurationFileDirectory;
}
