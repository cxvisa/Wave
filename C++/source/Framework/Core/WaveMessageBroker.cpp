/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/WaveMessageBroker.h"
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
#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveMessagingBroker/WaveMessagingBrokerReceiverObjectManager.h"

#include <time.h>
#include <stdlib.h>
#include <sys/resource.h>

//Commenting it our for now.  We need to find way to enable it on Solaris.
//extern int daemon (int doNotChangeToRootDir, int doNotCloseFileDescriptors);

static string s_waveTraceFileDirectory         ("");
static string s_waveConfigurationFileDirectory ("");
static string s_waveProfileFileDirectory       ("");

namespace WaveNs
{

vector<NativeWaveServiceInstantiator>         WaveMessageBroker::m_nativeWaveServiceInstantiators;
vector<bool>                                   WaveMessageBroker::m_nativeWaveServiceInstantiatorIsForNormalPhase;
vector<NativeMultipleWaveServiceInstantiator> WaveMessageBroker::m_nativeMultipleWaveServiceInstantiators;
vector<NativeWaveServiceInstantiator>         WaveMessageBroker::m_nativeApplicationSpecificWaveServiceInstantiators;
vector<ResourceId>                             WaveMessageBroker::m_nativeWaveServiceInstantiationMode;
bool                                           WaveMessageBroker::m_enablePersistenceSupport;
bool                                           WaveMessageBroker::m_enableClusteringSupport;
bool                                           WaveMessageBroker::m_enableBuiltInSelfTestSupport;
bool                                           WaveMessageBroker::m_enableShellSupport;
bool                                           WaveMessageBroker::m_enableManagementInterfaceSupport;
bool                                           WaveMessageBroker::m_enableLicensingSupport;
bool                                           WaveMessageBroker::m_enableSoftwareManagementSupport;
bool                                           WaveMessageBroker::m_enableTimerSupport;
bool                                           WaveMessageBroker::m_enableHaPeerSupport;
bool                                           WaveMessageBroker::m_enableDistributedLogSupport;
bool                                           WaveMessageBroker::m_enableTraceSupport;
bool                                           WaveMessageBroker::m_enableFileServiceSupport;
bool                                           WaveMessageBroker::m_enableSystemManagementSupport;
PersistencePostBootCheck                       WaveMessageBroker::m_persistencePostBootCheck;
WaveMutex                                     WaveMessageBroker::m_clusterEnabledCheckMutex;
ClusterEnabledCheck                            WaveMessageBroker::m_clusterEnabledCheck  = NULL;
string                                         WaveMessageBroker::m_waveUserClientPath;
string                                         WaveMessageBroker::m_waveUserClientParams;
LogOperationStatusFunction                     WaveMessageBroker::m_logOperationStatusFunction = NULL;
WaveMutex                                     WaveMessageBroker::m_logOperationStatusMutex;
IsWaveClusteringEnabled                        WaveMessageBroker::m_isWaveClusteringEnabled = NULL;
WaveMutex                                     WaveMessageBroker::m_isWaveClusteringEnabledMutex;
GetLinecardReadySlotIdBitMapFunction           WaveMessageBroker::m_linecardReadySlotIdBitMapFunction = NULL;
WaveMutex                                     WaveMessageBroker::m_linecardReadySlotIdBitMapFunctionMutex;

void WaveMessageBroker::enableAllFeatures ()
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
}

void WaveMessageBroker::enablePersistence ()
{
    m_enablePersistenceSupport = true;
}

void WaveMessageBroker::disablePersistence ()
{
    m_enablePersistenceSupport = false;
}

void WaveMessageBroker::enableClustering ()
{
    m_enableClusteringSupport = true;
}

void WaveMessageBroker::disableClustering ()
{
    m_enableClusteringSupport = false;
}

void WaveMessageBroker::enableBuiltInSelfTest ()
{
    m_enableBuiltInSelfTestSupport = true;
}

void WaveMessageBroker::disableBuiltInSelfTest ()
{
    m_enableBuiltInSelfTestSupport = false;
}

void WaveMessageBroker::enableShell ()
{
    m_enableShellSupport = true;
}

void WaveMessageBroker::disableShell ()
{
    m_enableShellSupport = false;
}

void WaveMessageBroker::enableManagementInterface ()
{
    m_enableManagementInterfaceSupport = true;
}

void WaveMessageBroker::disableManagementInterface ()
{
    m_enableManagementInterfaceSupport = false;
}

void WaveMessageBroker::enableLicense ()
{
    m_enableLicensingSupport = true;
}

void WaveMessageBroker::disableLicense ()
{
    m_enableLicensingSupport = false;
}

void WaveMessageBroker::enableSoftwareManagement ()
{
    m_enableSoftwareManagementSupport = true;
}

void WaveMessageBroker::disableSoftwareManagement ()
{
    m_enableSoftwareManagementSupport = false;
}

void WaveMessageBroker::enableTimer ()
{
    m_enableTimerSupport = true;
}

void WaveMessageBroker::disableTimer ()
{
    m_enableTimerSupport = false;
}

void WaveMessageBroker::enableTrace ()
{
    m_enableTraceSupport = true;
}

void WaveMessageBroker::disableTrace ()
{
    m_enableTraceSupport = false;
}

void WaveMessageBroker::enableFileService ()
{
    m_enableFileServiceSupport = true;
}

void WaveMessageBroker::disableFileService ()
{
    m_enableFileServiceSupport = false;
}

void WaveMessageBroker::enableDistributedLog ()
{
    m_enableDistributedLogSupport = true;
}

void WaveMessageBroker::disableDistributedLog ()
{
    m_enableDistributedLogSupport = false;
}

void WaveMessageBroker::enableHaPeer ()
{
    m_enableHaPeerSupport = true;
}

void WaveMessageBroker::disableHaPeer ()
{
    m_enableHaPeerSupport = false;
}

void WaveMessageBroker::enableSystemManagement ()
{
    m_enableSystemManagementSupport = true;
}

void WaveMessageBroker::disableSystemManagement ()
{
    m_enableSystemManagementSupport = false;
}

void WaveMessageBroker::initialize (const WaveMainConfiguration &waveMainConfiguration)
{
    // First change to user specified directory if any

    SI32 rlimitStatus = 0;
    rlimit rlim;

    rlim.rlim_cur = 1048576 * 8;   // 8 MB
    rlim.rlim_max = 1048576 * 8;

    rlimitStatus = setrlimit (RLIMIT_STACK, &rlim);

    if (0 != rlimitStatus)
    {
        trace (TRACE_LEVEL_WARN, "WaveMessageBroker::initialize not able to set rlimit");
    }

    if ("" != (waveMainConfiguration.getChangeDirectoryTo ()))
    {
        SI32 chDirStatus = chdir ((waveMainConfiguration.getChangeDirectoryTo ()).c_str ());

        if (0 != chDirStatus)
        {
            trace (TRACE_LEVEL_ERROR, "WaveMessageBroker::initialize : Could not Change Directory to " + waveMainConfiguration.getChangeDirectoryTo ());
            trace (TRACE_LEVEL_ERROR, "WaveMessageBroker::initialize : Reason listed below :");
            perror ("WAVE");
            waveAssert (false, __FILE__, __LINE__);
        }
    }

    // Initialize Random Generator
#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveMessagingBroker/WaveMessagingBrokerReceiverObjectManager.h"
    srand (time (NULL));

    // Set the Management Interface Role

    FrameworkToolKit::setManagementInterfaceRole (WAVE_MGMT_INTF_ROLE_SERVER);

    // First record the current working directory as the directory in which the process was started

    FrameworkToolKit::initialize ();

    //Initialize time zone information

    TimeZoneToolKit::initialize ();

    // Setup the System Management;

    SystemManagementToolKit::setYinPaths          (waveMainConfiguration.getYinPaths ());
    SystemManagementToolKit::setWyserTagsFilePath (waveMainConfiguration.getWyserTagsFilePath ());

    // set the WaveMessageBroker Framework configuration file.

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


    // Run the process in daemon mode if required.

    if (true == (waveMainConfiguration.getIsADaemon ()))
    {
        int rc = daemon (1, 0);

        if (0 != rc)
        {
            // handle the error.
        }

        FrameworkToolKit::initializeConsolePrintFunction ();
    }

    // Record if the process is running as a daemon.

    FrameworkToolKit::setIsRunningAsADaemon (waveMainConfiguration.getIsADaemon ());

    // Add ORM Repository Most Base Classes information from WaveMessageBroker.

    OrmRepository::addMostBaseClass (WavePersistableObject::getClassName ());
    OrmRepository::addMostBaseClass (WaveManagedObject::getClassName      ());
    OrmRepository::addMostBaseClass (WaveLocalManagedObject::getClassName ());

    // WaveFrameworkObjectManager must be the first one to be created.

    WaveFrameworkObjectManager::getInstance ();

    // ShellObjectManager must be the next one so that all can register their shells and related shell handlers.

    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (ShellObjectManager::getInstance));

    FrameworkToolKit::registerDebugShellEntries ();
    WaveSourceGeneratorBase::registerDebugShellEntries ();
    InterLocationMessageReceiverObjectManager::registerDebugShellEntries ();
    ManagementInterfaceReceiverObjectManager::registerDebugShellEntries ();
    // ManagementInterfaceObjectManager::registerDebugShellEntries ();

    // WARNING! WARNING! WARNING!
    // DO NOT CHANGE ABOVE THIS LINE

    // FrameworkToolKit must be initialized before we call any trace.
    // Trace functionality uses FrameworkToolKit for different directory paths.
    trace(TRACE_LEVEL_PERF_START, "WaveMessageBroker Bootup.");

    // Below this one the services are registered in reverse order.  The last one will be on top of the list.

    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (WaveMessagingBrokerReceiverObjectManager::getInstance));

    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (ManagementInterfaceReceiverObjectManager::getInstance));
    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (ManagementInterfaceObjectManager::getInstance));

    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (TraceObjectManager::getInstance));

    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (ReservedWaveLocalObjectManager::getInstance), false);

    // WARNING! WARNING! WARNING!
    // Always keep the Timer Object Manager as the last registered internal native service.
    // All services will cancel their timers with the Timer Object Manager during shutdown so this service must be the last to shutdown.

    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (TimerObjectManager::getInstance), false);
    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (TimerSignalObjectManager::getInstance), false);

    // Instantiate Native WaveMessageBroker Services here

    instantiateNativeWaveServices ();

    // Start the ObjectManager s corresponding to Application Services

    ApplicationService::createNewApplicationServices ();

    // start the ObjectManager s corresponding to Application Local Services

    ApplicationLocalService::createNewApplicationLocalServices ();

    // Starting Application specific Object managers.

    AppObjectManager::createAppObjectMangers ();
}

string WaveMessageBroker::getTraceFileDirectory ()
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

string WaveMessageBroker::getConfigurationFileDirectory ()
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

string WaveMessageBroker::getProfileFileDirectory ()
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

void WaveMessageBroker::registerNativeService (NativeWaveServiceInstantiator pNativeWaveServiceInstantiator, const bool &isForNormalPhase, const ResourceId &serviceMode)
{
    m_nativeWaveServiceInstantiators.push_back                (pNativeWaveServiceInstantiator);
    m_nativeWaveServiceInstantiatorIsForNormalPhase.push_back (isForNormalPhase);
    m_nativeWaveServiceInstantiationMode.push_back            (serviceMode);
}

void WaveMessageBroker::registerApplicationSpecificNativeServices (NativeWaveServiceInstantiator pNativeWaveServiceInstantiator, const bool &isForNormalPhase, const ResourceId &serviceMode)
{
    m_nativeApplicationSpecificWaveServiceInstantiators.push_back (pNativeWaveServiceInstantiator);

    registerNativeService (pNativeWaveServiceInstantiator, isForNormalPhase, serviceMode);
}

void WaveMessageBroker::registerNativeServiceInternal (NativeWaveServiceInstantiator pNativeWaveServiceInstantiator, const bool &isForNormalPhase, const ResourceId &serviceMode)
{
    m_nativeWaveServiceInstantiators.insert                (m_nativeWaveServiceInstantiators.begin (), pNativeWaveServiceInstantiator);
    m_nativeWaveServiceInstantiatorIsForNormalPhase.insert (m_nativeWaveServiceInstantiatorIsForNormalPhase.begin (), isForNormalPhase);
    m_nativeWaveServiceInstantiationMode.insert            (m_nativeWaveServiceInstantiationMode.begin (), serviceMode);
}

void WaveMessageBroker::registerNativeService (NativeMultipleWaveServiceInstantiator pNativeMultipleWaveServiceInstantiator)
{
    m_nativeMultipleWaveServiceInstantiators.push_back (pNativeMultipleWaveServiceInstantiator);
}

void WaveMessageBroker::registerPersistencePostBootCheck (PersistencePostBootCheck pPersistencePostBootCheck)
{
    m_persistencePostBootCheck = pPersistencePostBootCheck;
}

ResourceId WaveMessageBroker::persistencePostBootCheck ()
{
    return ((m_persistencePostBootCheck ()));
}

void WaveMessageBroker::registerClusterEnabledCheck (ClusterEnabledCheck pClusterEnabledCheck)
{
    m_clusterEnabledCheckMutex.lock ();

    m_clusterEnabledCheck = pClusterEnabledCheck;

    m_clusterEnabledCheckMutex.unlock ();
}

bool WaveMessageBroker::clusterEnabledCheck ()
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

void WaveMessageBroker::registerIsWaveClusteringEnabledFunction (IsWaveClusteringEnabled pIsWaveClusteringEnabled)
{
    m_isWaveClusteringEnabledMutex.lock ();
    m_isWaveClusteringEnabled = pIsWaveClusteringEnabled ;
    m_isWaveClusteringEnabledMutex.unlock ();
}

bool WaveMessageBroker::isWaveClusteringEnabled ()
{
    bool mode = false;
    m_isWaveClusteringEnabledMutex.lock ();
    mode = m_isWaveClusteringEnabled();
    m_isWaveClusteringEnabledMutex.unlock ();

    return mode;
}

void WaveMessageBroker::registerLogOperationStatusFunction (LogOperationStatusFunction pLogOperationStatusFunction)
{
    m_logOperationStatusMutex.lock ();

    m_logOperationStatusFunction = pLogOperationStatusFunction;

    m_logOperationStatusMutex.unlock ();
}

void WaveMessageBroker::logOperationStatus (ResourceId status)
{
    trace (TRACE_LEVEL_DEBUG, string("WaveMessageBroker::logOperationStatus : status = ") + status);

    m_logOperationStatusMutex.lock ();
    m_logOperationStatusFunction (status);
    m_logOperationStatusMutex.unlock ();
}

void WaveMessageBroker::registerGetLinecardReadySlotIdBitMapFunction ( GetLinecardReadySlotIdBitMapFunction plinecardReadySlotIdBitMapFunction )
{
    m_linecardReadySlotIdBitMapFunctionMutex.lock();

    m_linecardReadySlotIdBitMapFunction = plinecardReadySlotIdBitMapFunction;

    m_linecardReadySlotIdBitMapFunctionMutex.unlock();
}

void WaveMessageBroker::getLinecardReadySlotIdBitMap ( BitMap &linecardReadySlotIdBitMap , UI32 &maxLinecards )
{
    m_linecardReadySlotIdBitMapFunctionMutex.lock();

    if ( NULL != m_linecardReadySlotIdBitMapFunction )
    {
        m_linecardReadySlotIdBitMapFunction ( linecardReadySlotIdBitMap, maxLinecards );
    }

    m_linecardReadySlotIdBitMapFunctionMutex.unlock();
}

void WaveMessageBroker::setWaveUserClientPath (const string &path)
{
    m_waveUserClientPath = path;
}

string WaveMessageBroker::getWaveUserClientPath ()
{
    return (m_waveUserClientPath);
}

void WaveMessageBroker::setWaveUserClientParams (const string &params)
{
    m_waveUserClientParams = params;
}

string WaveMessageBroker::getWaveUserClientParams ()
{
    return (m_waveUserClientParams);
}

void WaveMessageBroker::instantiateNativeWaveServices ()
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

    trace (TRACE_LEVEL_INFO, string ("Instantiated ") + numberOfNativeWaveServciesToInstantiate + " Native WaveMessageBroker Services");
}

void WaveMessageBroker::waveExit ()
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
