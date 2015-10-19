/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include <time.h>
#include <signal.h>
#include "Framework/OsLayer/WaveOsLayer.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Core/WaveFrameworkObjectManagerInitializeWorker.h"
#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/Core/SecondaryNodeClusterContext.h"
#include "Framework/Core/SecondaryNodeClusterPhase2Context.h"
#include "Framework/Core/SecondaryNodeClusterPhase3Context.h"
#include "Framework/Core/WaveFrameworkMessages.h"
#include "FrameworkObjectManagerMessages.h"
#include "Framework/Trace/TraceMessages.h"
#include "Framework/LocationManagement/LocationBase.h"
#include "Framework/LocationManagement/Location.h"
#include "Framework/LocationManagement/SubLocation.h"
#include "Framework/Core/FrameworkSequenceGenerator.h"
#include "Framework/Utils/WaveMutex.h"
#include "Framework/Utils/WaveCondition.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/ConfigFileManagementToolKit.h"
#include "Framework/Utils/AssertUtils.h"
#include "Cluster/ClusterMessages.h"
#include "Cluster/CentralClusterConfigObjectManager.h"
#include "Cluster/Test/ClusterTestObjectManager.h"
#include "Framework/Core/CreateClusterWithNodesContext.h"
#include "Framework/Core/AddNodesToClusterContext.h"
#include "Framework/Core/DeleteNodesFromClusterContext.h"
#include "Framework/Core/DeleteNodeOnSecondaryContext.h"
#include "Framework/Messaging/Remote/InterLocationMessageTransportObjectManager.h"
#include "Framework/Core/RejoinNodesToClusterContext.h"
#include "Framework/Core/DestroyClusterContext.h"
#include "Framework/Messaging/Remote/InterLocationMessageReceiverObjectManager.h"
#include "Framework/Core/WaveFrameworkConfigurationWorker.h"
#include "Framework/Shutdown/WaveFinalizeWorker.h"
#include "Framework/Timer/TimerSignalObjectManager.h"
#include "Framework/Trace/TraceObjectManager.h"
#include "Shell/ShellObjectManager.h"
#include "Regression/RegressionTestObjectManager.h"
#include "App/AppObjectManager.h"
#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"
#include "Version/WaveVersion.h"
#include "Framework/Core/HeartBeatLostContext.h"
#include "Framework/Core/DestroyClusterAsynchronousContext.h"
#include "Framework/Core/DetachFromClusterAsynchronousContext.h"
#include "Framework/Core/WaveFrameworkConfigurationWorker.h"
#include "Framework/Core/WaveFrameworkFailoverWorker.h"
#include "Framework/Core/WaveFrameworkFailoverWorkerContext.h"
#include "Framework/Core/WaveFrameworkConfiguration.h"
#include "Framework/Core/DetachFromClusterContext.h"
#include "Cluster/Local/HeartBeat/HeartBeatMessages.h"
#include "Framework/ObjectModel/WaveManagedObject.h"
#include "Framework/Database/DatabaseObjectManagerBackupMessage.h"
#include "Framework/Database/DatabaseObjectManagerCleanPreparedTransactionsMessage.h"
#include "Framework/Database/DatabaseObjectManagerEmptyMessage.h"
#include "Framework/Database/DatabaseObjectManagerRestoreMessage.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Database/DatabaseStandaloneTransaction.h"
#include "Framework/Persistence/PersistenceObjectManager.h"
#include "Framework/Core/UpdateListOfSecondariesContext.h"
#include "Framework/Core/WaveFrameworkObjectManagerServiceControlWorker.h"
#include "Framework/Core/WaveFrameworkObjectManagerPostbootWorker.h"
#include "Framework/Core/WaveFrameworkObjectManagerPostPersistentBootWorker.h"
#include "Framework/Core/WaveFrameworkObjectManagerHaSyncWorker.h"
#include "Cluster/Local/WaveNode.h"
#include "Cluster/WaveCluster.h"
#include <sys/types.h>
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"
#include "Cluster/Local/ClusterLocalReportPrimaryNodeChangedMessage.h"
#include "Cluster/Local/ClusterLocalReportRemovedNodeFromClusterMessage.h"
#include "Cluster/Local/ClusterLocalReportReplaceMessage.h"

#include "Framework/ExternalStateSynchronization/WaveExternalStateSynchronizationAgent.h"
#include "Framework/SlotFailover/SlotFailoverAgent.h"
#include "Framework/Core/WaveNewNodesAddedEvent.h"
#include "Framework/Core/WaveNodesAdditionToClusterCompletedEvent.h"
#include "Framework/Core/WaveNodeDeleteClusterEvent.h"
#include "Framework/Core/WaveNodeLocalNodeDeletedEvent.h"
#include "Framework/Core/ClusterPhase3StartEvent.h"
#include "Framework/Core/ClusterPhase3CompleteEvent.h"
#include "Framework/Core/PrimaryChangedEvent.h"
#include "Framework/Postboot/WavePostbootMessages.h"
 #include "Framework/Postboot/WavePostPersistentBootWorkerClusterContext.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContext.h"
#include "Framework/Persistence/PersistenceObjectManagerExecuteTransactionMessage.h"
#include "Framework/ObjectRelationalMapping/OrmRepository.h"
#include "Framework/ObjectModel/WaveManagedObjectToolKit.h"
#include <set>
#include "Framework/Zeroize/ZeroizeForFIPSLinearSequencerContext.h"
#include "Framework/Zeroize/ZeroizeForFIPSMessage.h"
#include "Framework/Zeroize/WaveZeroizeAgent.h"
#include "Framework/Core/Wave.h"
#include "Framework/Core/VcsClusterConfiguration.h"
#include "ManagementInterface/ClientInterface/WaveClientTransportObjectManager.h"
#include "Framework/ConfigReplayEnd/FileReplayEndAgent.h"
#include "Framework/Core/WaveFrameworkServiceIndependentMessages.h"
#include "Framework/Core/WaveConfigurationIntentRepository.h"
#include "Framework/Persistence/PersistenceToolKit.h"
#include "Framework/Core/WaveFrameworkReplayConfigMessage.h"
#include "Framework/CliBlockManagement/CliBlockManagementToolKit.h"

namespace WaveNs
{

static bool                                 s_isFrameworkReadyToBoot                                         = false;
static WaveMutex            *              s_pFrameworkReadinessMutex                                       = NULL;
static WaveMutex                           s_disconnectMutex;
static WaveMutex                           s_instantiationMutex;
static WaveMutex                           s_startupValidMutex;
static WaveMutex                           s_startupFileMutex;
static WaveMutex                           s_startupFileTypeMutex;
static string                               s_startupFileName                                                = "startupFile";
static bool                                 s_isFrameworkInstantiated                                        = false;

static FrameworkSequenceType                s_frameworkSequenceType                                          = FRAMEWORK_SEQUENCE_TYPE0;

static string                               s_frameworkConfigurationFile                                     = "";
static string                               s_frameworkConfigurationBackupFile                               = "";

static string                               s_frameworkGlobalConfigurationFile                               = "";
static string                               s_frameworkGlobalConfigurationTempFile                           = "";

static string                               s_lockFileForConfigurationFile                                   = "";     

static UI32                                 s_offSetForValidationResults                                     = 0x0000FFFF;

static LocationRole                         s_locationRole                                                   = LOCATION_STAND_ALONE;
static LocationId                           s_locationParentLocationId                                       = 0;
static string                               s_locationParentIpAddress                                        = "";
static SI32                                 s_locationParentPort                                             = 3016;
static LocationId                           s_locationLocationId                                             = 0;
static string                               s_locationIpAddress                                              = "";
static SI32                                 s_locationPort                                                   = 3016;

static WaveMutex                           s_bootSynchronizationMutex;
static WaveMutex                           s_dbRestoreMutex;
static WaveMutex                           s_dbConversionStatusMutex;

static map<WaveThreadId, WaveThreadId>    s_prismThreadIdRepository;
static WaveMutex                           s_prismThredIdRepositoryMutex;

static const UI32                           s_clusterPhase0TimeoutInMilliseconds                             = 900000; // 15 * 60 * 1000 
static const UI32                           s_clusterPhase1TimeoutInMilliseconds                             = 900000; // 15 * 60 * 1000 
static const UI32                           s_clusterPhase2TimeoutInMilliseconds                             = 900000; // 15 * 60 * 1000
static const UI32                           s_clusterPhase3TimeoutInMilliseconds                             = 900000; // 15 * 60 * 1000

WaveMutex                                  WaveFrameworkObjectManager::m_externalStateSynchronizationRequiredListLock;
vector<WaveServiceId>                      WaveFrameworkObjectManager::m_externalStateSynchronizationRequiredList;

string                                      WaveFrameworkObjectManager::m_ipAddressForThisLocation;
WaveMutex                                  WaveFrameworkObjectManager::m_ipAddressForThisLocationMutex;
string                                      WaveFrameworkObjectManager::m_ethernetInterfaceForThisLocation;

GetInstancesFunction                        WaveFrameworkObjectManager::m_getInstancesFunction                     = NULL;
GetInstancesAndSubInstancesFunction         WaveFrameworkObjectManager::m_getInstancesAndSubInstancesFunction      = NULL;
GetThisSlotInstanceFunction                 WaveFrameworkObjectManager::m_getThisSlotInstanceFunction              = NULL;
CreateDummySlotFunction                     WaveFrameworkObjectManager::m_createDummySlotFunction                  = NULL;
RaslogAssertFunction                        WaveFrameworkObjectManager::m_raslogAssertFunction                     = NULL;

GetFirmwareVersionFunction                  WaveFrameworkObjectManager::m_getFirmwareVersionFunction          = NULL;
HandleDcmFssConfigUpdateFunction            WaveFrameworkObjectManager::m_handleDcmFssConfigUpdateFunction = NULL;
SetVcsClusterConfigHandlerFunction          WaveFrameworkObjectManager::m_setVcsClusterConfigHandlerFunction          = NULL;
GetVcsClusterConfigHandlerFunction          WaveFrameworkObjectManager::m_getVcsClusterConfigHandlerFunction          = NULL;
NotifySyncUpdateFailureFunction             WaveFrameworkObjectManager::m_notifySyncUpdateFailureFunction  = NULL;
NotifyClusterReadyStateFunction             WaveFrameworkObjectManager::m_notifyClusterReadyStateFunction  = NULL;

void WaveFrameworkObjectManager::setIsInstantiated (const bool &isInstantiated)
{
    s_instantiationMutex.lock ();
    s_isFrameworkInstantiated = isInstantiated;
    s_instantiationMutex.unlock ();
}

bool WaveFrameworkObjectManager::getIsInstantiated ()
{
    bool isInstantiated;

    s_instantiationMutex.lock ();
    isInstantiated = s_isFrameworkInstantiated;
    s_instantiationMutex.unlock ();

    return (isInstantiated);
}

void WaveFrameworkObjectManager::setConfigurationFile (const string &configurationFile)
{
    s_frameworkConfigurationFile        = configurationFile;
    s_frameworkConfigurationBackupFile  = s_frameworkConfigurationFile + ".bk";
}

void WaveFrameworkObjectManager::setGlobalConfigurationFile (const string &globalConfigurationFile)
{
    s_frameworkGlobalConfigurationFile        = globalConfigurationFile;
    s_frameworkGlobalConfigurationTempFile    = s_frameworkGlobalConfigurationFile + ".tmp";
}

void WaveFrameworkObjectManager::setLockFileForConfigurationFile (const string &lockFile)
{
    s_lockFileForConfigurationFile = lockFile;
}

LocationId WaveFrameworkObjectManager::getLastUsedLocationIdInWaveFrameworkObjectManager () const
{
    return (m_lastUsedLocationId);
}

void WaveFrameworkObjectManager::setLastUsedLocationIdInWaveFrameworkObjectManager (const LocationId &locationId)
{
    m_lastUsedLocationId = locationId;
}

bool WaveFrameworkObjectManager::getWaveConfigurationValidity ()
{
    return (m_pConfigurationWorker)->getWaveConfigurationValidity ();
}

WaveFrameworkObjectManager::WaveFrameworkObjectManager ()
    : WaveLocalObjectManager (getServiceName ()),
      m_pThisLocation (NULL),
      m_isStartupValid (false),
      m_secondaryNodeClusterCreationFlag (false),
      m_primaryNodeClusterOperationFlag (false),
      m_activationCompleted (false), 
      m_postBootStarted (false),
      m_postBootCompleted (false),
      m_configReplayStarted (false),      
      m_configReplayCompleted (false),
      m_nodeReadyForAllCommands (false),
      m_clusterPhaseTimerHandler (0),
      m_isPostBootNeededDuringRejoin (false),
      m_needNotifyClusterReadyState (false),
      m_nodeZeroized(false),
      m_isDBRestoreIncomplete (false),
      m_dbConversionStatus (DATABASE_SCHEMA_CONVERSION_NOT_ATTEMPTED),
      m_tableIdsChangedForSchemaCompatibility (false),
      m_isWarmHaRecoveryPreparationInProgress (false)
{

    acquireBootSynchronizationMutex ();
    m_externalStateSynchronizationRequiredList.clear ();
    // First configure this location

    if (LOCATION_STAND_ALONE == s_locationRole)
    {
        configureThisLocationAsLocation (s_locationPort);
    }
    else if (LOCATION_SUB_LOCATION == s_locationRole)
    {
        configureThisLocationAsSubLocation (s_locationParentLocationId, s_locationParentIpAddress, s_locationParentPort, s_locationLocationId, s_locationIpAddress, s_locationPort);
    }
    else
    {
        // Cannot use tracing at this point in time.
        cerr << "WaveFrameworkObjectManager::WaveFrameworkObjectManager : Invalid type of Location Configuration.  Cannot Continue" << endl;
        exit (-1);
    }

    waveAssert (NULL != s_pFrameworkReadinessMutex, __FILE__, __LINE__);

    s_isFrameworkReadyToBoot = false;

    m_pInitializeWorker = new WaveFrameworkObjectManagerInitializeWorker (this);

    waveAssert (NULL != m_pInitializeWorker, __FILE__, __LINE__);

    m_pWaveFinalizeWorker = new WaveFinalizeWorker (this);

    waveAssert (NULL != m_pWaveFinalizeWorker, __FILE__, __LINE__);

    m_pConfigurationWorker = new WaveFrameworkConfigurationWorker (this);

    waveAssert (NULL != m_pConfigurationWorker, __FILE__, __LINE__);

    m_pWaveFrameworkFailoverWorker = new WaveFrameworkFailoverWorker (this);

    waveAssert (NULL != m_pWaveFrameworkFailoverWorker, __FILE__, __LINE__);

    m_pWaveFrameworkObjectManagerServiceControlWorker = new WaveFrameworkObjectManagerServiceControlWorker (this);

    waveAssert (NULL != m_pWaveFrameworkObjectManagerServiceControlWorker, __FILE__, __LINE__);

    m_pWaveFrameworkObjectManagerPostbootWorker = new WaveFrameworkObjectManagerPostbootWorker (this);

    waveAssert (NULL != m_pWaveFrameworkObjectManagerPostbootWorker, __FILE__, __LINE__);

    m_pWaveFrameworkObjectManagerPostPersistentBootWorker = new WaveFrameworkObjectManagerPostPersistentBootWorker (this);

    waveAssert (NULL != m_pWaveFrameworkObjectManagerPostPersistentBootWorker, __FILE__, __LINE__);

    m_pWaveFrameworkObjectManagerHaSyncWorker = new WaveFrameworkObjectManagerHaSyncWorker (this);

    waveAssert (NULL != m_pWaveFrameworkObjectManagerHaSyncWorker, __FILE__, __LINE__);

    //waveAssert (NULL != m_dbStandaloneTransaction, __FILE__, __LINE__);*/
//Temporarily disabled all xerces related code.
#if 0
    try
    {
        XMLPlatformUtils::Initialize ();
    }
    catch (const XMLException &exception)
    {
        cout << " E R R O R in Initializing the XMLPlatformUtils." << endl;
        waveAssert (0, __FILE__, __LINE__);
        exit (-1);
    }
#endif
    // Indicate that the Instatiation of WaveObjectManager is complete.

    setIsInstantiated (true);
    setIsEnabled (true);

    // Now send a oneway initialize message to self.

    // We know the service id for the Wave framework object manager must be 1.  And it must not be anything else.  So we use the value 1 in the next statement.

    WaveInitializeObjectManagerMessage *pWaveInitializeObjectManagerMessage = new WaveInitializeObjectManagerMessage (1, WAVE_BOOT_FIRST_TIME_BOOT); // We cannot use WaveFrameworkObjectManager::getWaveServiceId () - it iwill invariably fail since we are inside the getInstance method
                                                                                                                                                        // We always say it is the first time boot, but, this reason is not to be looked into in the initialize for this OM.

    WaveMessageStatus status = sendOneWay (pWaveInitializeObjectManagerMessage);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        cerr << "Cannot Initialize the Framework.  Cannot continue.  Exiting ..." << endl;
        exit (-2);
    }

    WaveEnableObjectManagerMessage *pWaveEnableObjectManagerMessage = new WaveEnableObjectManagerMessage (1, WAVE_BOOT_FIRST_TIME_BOOT); // We cannot use WaveFrameworkObjectManager::getWaveServiceId () - it iwill invariably fail since we are inside the getInstance method
                                                                                                                                            // We always say it is the first time boot, but, this reason is not to be looked into in the enable for this OM.

    status = sendOneWay (pWaveEnableObjectManagerMessage);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        cerr << "Cannot Enable the Framework.  Cannot continue.  Exiting ..." << endl;
        exit (-3);
    }

    WaveInstallObjectManagerMessage *pWaveInstallObjectManagerMessage = new WaveInstallObjectManagerMessage (1, WAVE_BOOT_FIRST_TIME_BOOT); // We cannot use WaveFrameworkObjectManager::getWaveServiceId () - it iwill invariably fail since we are inside the getInstance method
                                                                                                                                               // We always say it is the first time boot, but, this reason is not to be looked into in the install for this OM.

    status = sendOneWay (pWaveInstallObjectManagerMessage);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        cerr << "Cannot Install the Framework.  Cannot continue.  Exiting ..." << endl;
        exit (-4);
    }

    WaveBootObjectManagerMessage *pWaveBootObjectManagerMessage = new WaveBootObjectManagerMessage (1, WAVE_BOOT_FIRST_TIME_BOOT); // We cannot use WaveFrameworkObjectManager::getWaveServiceId () - it iwill invariably fail since we are inside the getInstance method
                                                                                                                                      // We always say it is the first time boot, but, this reason is not to be looked into in the boot for this OM.

    status = sendOneWay (pWaveBootObjectManagerMessage);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        cerr << "Cannot Boot the Framework.  Cannot continue.  Exiting ..." << endl;
        exit (-5);
    }

    addOperationMap (FRAMEWORK_OBJECT_MANAGER_CREATE_CLUSTER_WITH_NODES,           reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::createClusterWithNodesMessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_CONFIGURE_CLUSTER_SECONDARY,         reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::configureSecondaryNodeMessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_CONFIGURE_CLUSTER_SECONDARY_PHASE_1, reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::configureSecondaryNodePhase1MessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_CONFIGURE_CLUSTER_SECONDARY_PHASE_2, reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::configureSecondaryNodePhase2MessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_CONFIGURE_CLUSTER_SECONDARY_PHASE_3, reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::configureSecondaryNodePhase3MessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_UPDATE_LIST_OF_CLUSTER_SECONDARIES,  reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::updateListOfSecondariesMessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_ADD_NODES_TO_CLUSTER,                reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::addNodesToClusterMessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_DELETE_NODES_FROM_CLUSTER,           reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::deleteNodesFromClusterMessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_UNCONFIGURE_CLUSTER_SECONDARY,       reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::unconfigureClusterSecondaryMessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_DESTORY_CLUSTER,                     reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::destroyClusterMessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_REJOIN_NODES_TO_CLUSTER,             reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::rejoinNodesToClusterMessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_REJOIN_CLUSTER_SECONDARY,            reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::rejoinClusterSecondaryMessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_REJOIN_CLUSTER_SECONDARY_PHASE_1,    reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::rejoinClusterSecondaryPhase1MessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_REJOIN_CLUSTER_SECONDARY_PHASE_2,    reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::rejoinClusterSecondaryPhase2MessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_REJOIN_CLUSTER_SECONDARY_PHASE_3,    reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::rejoinClusterSecondaryPhase3MessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_DETACH_FROM_CLUSTER,                 reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::detachFromClusterMessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_LOST_HEART_BEAT_MESSAGE,             reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::lostHeartBeatMessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_PRIMARY_CHANGED_MESSAGE,             reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::primaryChangedMessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_PRIMARY_CHANGED_PHASE_1_MESSAGE,     reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::primaryChangedPhase1MessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_PRIMARY_CHANGED_PHASE_2_MESSAGE,     reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::primaryChangedPhase2MessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_PRIMARY_CHANGED_PHASE_3_MESSAGE,     reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::primaryChangedPhase3MessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_START_EXTERNAL_STATE_SYNCHRONIZATION,reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::startExternalStateSynchronizationHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_START_SLOT_FAILOVER,                 reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::startSlotFailoverHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_NEW_PRINCIPAL_ESTABLISHED_AFTER_FAILOVER, reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::newPrincipalSelectedAfterFaioverMessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_SECONDARY_NODE_FAILURE_NOTIFICATION, reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::secondaryNodeFailureNotificationMessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_DISCONNECT_FROM_ALL_NODES,           reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::disconnectFromAllNodesHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_ESTABLISH_PRINCIPAL_AFTER_CLUSTER_REBOOT, reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::establishPrincipalAfterClusterRebootHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_RESET_NODE_FOR_CLUSTER_MERGE,reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::resetNodeForClusterMergeHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_REMOVE_KNOWN_LOCATIONS_MESSAGE,reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::removeFailedLocationsFromKnownLocationsHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_FIPS_ZEROIZE,                      reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::zeroizeForFIPSMessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_DISCONNECT_FROM_ALL_INSTANCE_CLIENTS, reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::disconnectFromAllInstanceClientsHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_PREPARE_FOR_WARM_RECOV_WITH_DEFAULT_CONFIG_MESSAGE, reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::prepareNodeForWarmRecoveryWithDefaultConfiguration));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_STORE_CONFIGURATION_INTENT, reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::storeConfigurationIntentMessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_REMOVE_CONFIGURATION_INTENT, reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::removeConfigurationIntentMessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_PREPARE_FOR_HA_RECOV_WITH_PERSISTENT_CONFIG_MESSAGE, reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::prepareFrameworkForHaRecoveryMessageHandler));

    addOperationMap (FRAMEWORK_OBJECT_MANAGER_CONFIGURE_CLUSTER_SECONDARY_HA_PEER,         reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::configureSecondaryNodeHaPeerMessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_CONFIGURE_CLUSTER_SECONDARY_HA_PEER_PHASE_1, reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::configureSecondaryNodeHaPeerPhase1MessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_CONFIGURE_CLUSTER_SECONDARY_HA_PEER_PHASE_3, reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::configureSecondaryNodeHaPeerPhase3MessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_REJOIN_CLUSTER_SECONDARY_HA_PEER,            reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::rejoinClusterSecondaryHaPeerMessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_REJOIN_CLUSTER_SECONDARY_HA_PEER_PHASE_1,    reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::rejoinClusterSecondaryHaPeerPhase1MessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_REJOIN_CLUSTER_SECONDARY_HA_PEER_PHASE_3,    reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::rejoinClusterSecondaryHaPeerPhase3MessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_PRIMARY_CHANGED_MESSAGE_HA_PEER,             reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::primaryChangedHaPeerMessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_PRIMARY_CHANGED_PHASE_1_HA_PEER_MESSAGE,     reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::primaryChangedHaPeerPhase1MessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_PRIMARY_CHANGED_PHASE_3_HA_PEER_MESSAGE,     reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::primaryChangedHaPeerPhase3MessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_ROLLBACK_STANDBY_ON_ACTIVE_ROLLBACK,         reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::rollbackStandbyOnActiveRollbackHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_REPLAY_CONFIG_FILE,                          reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManager::replayConfigFileMessageHandler));

    addServiceIndependentOperationMap (FRAMEWORK_OBJECT_MANAGER_STORE_CONFIGURATION_INTENT, reinterpret_cast<WaveServiceIndependentMessageHandler> (&WaveFrameworkObjectManager::storeConfigurationIntentStaticMessageHandler));
    addServiceIndependentOperationMap (FRAMEWORK_OBJECT_MANAGER_REMOVE_CONFIGURATION_INTENT, reinterpret_cast<WaveServiceIndependentMessageHandler> (&WaveFrameworkObjectManager::removeConfigurationIntentStaticMessageHandler));
}

WaveFrameworkObjectManager *WaveFrameworkObjectManager::getInstance ()
{
    // First create the framework readiness mutex.  By the time we enter the constructor for WaveFrameworkObjectManager
    // it might be too late to create the mutex.  Depending on the pthread implementation, a thread might have already started
    // which needs to access the mutex.

    if (NULL == s_pFrameworkReadinessMutex)
    {
        s_pFrameworkReadinessMutex = new WaveMutex ();
        WaveNs::waveAssert (NULL != s_pFrameworkReadinessMutex, __FILE__, __LINE__);
    }

    static WaveFrameworkObjectManager *pWaveFrameworkObjectManager = NULL;

    if (NULL == pWaveFrameworkObjectManager)
    {
        pWaveFrameworkObjectManager = new WaveFrameworkObjectManager ();
        WaveNs::waveAssert (NULL != pWaveFrameworkObjectManager, __FILE__, __LINE__);
    }

    return (pWaveFrameworkObjectManager);
}

string WaveFrameworkObjectManager::getServiceName ()
{
    return ("Wave Framework");
}

WaveFrameworkObjectManager::~WaveFrameworkObjectManager ()
{
    if (NULL != m_pInitializeWorker)
    {
        delete m_pInitializeWorker;
    }

    if (NULL != m_pWaveFinalizeWorker)
    {
        delete m_pWaveFinalizeWorker;
    }

    if (NULL != m_pConfigurationWorker)
    {
        delete m_pConfigurationWorker;
    }

    if (NULL != m_pWaveFrameworkFailoverWorker)
    {
        delete m_pWaveFrameworkFailoverWorker;
    }

    if (NULL != m_pThisLocation)
    {
        delete m_pThisLocation;
    }

    if (NULL != m_pWaveFrameworkObjectManagerServiceControlWorker)
    {
        delete m_pWaveFrameworkObjectManagerServiceControlWorker;
    }

    if (NULL != m_pWaveFrameworkObjectManagerPostbootWorker)
    {
        delete m_pWaveFrameworkObjectManagerPostbootWorker;
    }

    if (NULL != m_pWaveFrameworkObjectManagerPostPersistentBootWorker)
    {
        delete m_pWaveFrameworkObjectManagerPostPersistentBootWorker;
    }

    if (NULL != m_pWaveFrameworkObjectManagerHaSyncWorker)
    {
        delete m_pWaveFrameworkObjectManagerHaSyncWorker;
    }

//Temporarily disabled all xerces related code.
#if 0
    // Terminating the XMLPlatformUtils must be the last one.

    XMLPlatformUtils::Terminate ();
#endif
}

WaveMessage *WaveFrameworkObjectManager::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case FRAMEWORK_OBJECT_MANAGER_UPDATE_LIST_OF_CLUSTER_SECONDARIES :
            pWaveMessage = new FrameworkObjectManagerUpdateListOfSecondariesMessage;
            break;

        case FRAMEWORK_OBJECT_MANAGER_CONFIGURE_CLUSTER_SECONDARY :
            pWaveMessage = new WaveConfigureClusterSecondaryMessage;
            break;

        case FRAMEWORK_OBJECT_MANAGER_CONFIGURE_CLUSTER_SECONDARY_PHASE_1 :
            pWaveMessage = new WaveConfigureClusterSecondaryPhase1Message;
            break;

        case FRAMEWORK_OBJECT_MANAGER_CONFIGURE_CLUSTER_SECONDARY_PHASE_2 :
            pWaveMessage = new WaveConfigureClusterSecondaryPhase2Message;
            break;

        case FRAMEWORK_OBJECT_MANAGER_CONFIGURE_CLUSTER_SECONDARY_PHASE_3 :
            pWaveMessage = new WaveConfigureClusterSecondaryPhase3Message;
            break;

        case FRAMEWORK_OBJECT_MANAGER_UNCONFIGURE_CLUSTER_SECONDARY :
            pWaveMessage = new FrameworkObjectManagerUnconfigureClusterSecondaryMessage;
            break;

        case FRAMEWORK_OBJECT_MANAGER_REJOIN_CLUSTER_SECONDARY :
            pWaveMessage = new FrameworkObjectManagerRejoinClusterSecondaryMessage;
            break;

        case FRAMEWORK_OBJECT_MANAGER_REJOIN_CLUSTER_SECONDARY_PHASE_1 :
            pWaveMessage = new WaveRejoinClusterSecondaryPhase1Message();
            break;

        case FRAMEWORK_OBJECT_MANAGER_REJOIN_CLUSTER_SECONDARY_PHASE_2 :
            pWaveMessage = new WaveRejoinClusterSecondaryPhase2Message();
            break;

        case FRAMEWORK_OBJECT_MANAGER_REJOIN_CLUSTER_SECONDARY_PHASE_3 :
            pWaveMessage = new WaveRejoinClusterSecondaryPhase3Message();
            break;

        case FRAMEWORK_OBJECT_MANAGER_PRIMARY_CHANGED_MESSAGE :
            pWaveMessage = new FrameworkObjectManagerPrimaryChangedMessage;
            break;

        case FRAMEWORK_OBJECT_MANAGER_PRIMARY_CHANGED_PHASE_1_MESSAGE:
            pWaveMessage = new FrameworkObjectManagerPrimaryChangedPhase1Message;
            break;

        case FRAMEWORK_OBJECT_MANAGER_PRIMARY_CHANGED_PHASE_2_MESSAGE:
            pWaveMessage = new FrameworkObjectManagerPrimaryChangedPhase2Message;
            break;

        case FRAMEWORK_OBJECT_MANAGER_PRIMARY_CHANGED_PHASE_3_MESSAGE:
            pWaveMessage = new FrameworkObjectManagerPrimaryChangedPhase3Message;
            break;
        case FRAMEWORK_OBJECT_MANAGER_FIPS_ZEROIZE:
            pWaveMessage = new ZeroizeForFIPSMessage;
            break;

        case FRAMEWORK_OBJECT_MANAGER_REMOVE_KNOWN_LOCATIONS_MESSAGE:
            pWaveMessage = new FrameworkObjectManagerRemoveKnownLocationsMessage;
            break;

        case FRAMEWORK_OBJECT_MANAGER_DISCONNECT_FROM_ALL_INSTANCE_CLIENTS :
            pWaveMessage = new FrameworkObjectManagerDisconnectFromAllInstanceClientsMessage;
            break;

        case FRAMEWORK_OBJECT_MANAGER_STORE_CONFIGURATION_INTENT :
            pWaveMessage = new FrameworkObjectManagerStoreConfigurationIntentMessage;
            break;

        case FRAMEWORK_OBJECT_MANAGER_REMOVE_CONFIGURATION_INTENT :
            pWaveMessage = new FrameworkObjectManagerRemoveConfigurationIntentMessage;
            break;

        case FRAMEWORK_OBJECT_MANAGER_CONFIGURE_CLUSTER_SECONDARY_HA_PEER:
            pWaveMessage = new WaveConfigureClusterSecondaryHaPeerMessage;
            break;

        case FRAMEWORK_OBJECT_MANAGER_CONFIGURE_CLUSTER_SECONDARY_HA_PEER_PHASE_1:
            pWaveMessage = new WaveConfigureClusterSecondaryHaPeerPhase1Message;
            break;

        case FRAMEWORK_OBJECT_MANAGER_CONFIGURE_CLUSTER_SECONDARY_HA_PEER_PHASE_3:
            pWaveMessage = new WaveConfigureClusterSecondaryHaPeerPhase3Message;
            break;

        case FRAMEWORK_OBJECT_MANAGER_REJOIN_CLUSTER_SECONDARY_HA_PEER:
            pWaveMessage = new FrameworkObjectManagerRejoinClusterSecondaryHaPeerMessage;
            break;

        case FRAMEWORK_OBJECT_MANAGER_REJOIN_CLUSTER_SECONDARY_HA_PEER_PHASE_1:
            pWaveMessage = new WaveRejoinClusterSecondaryHaPeerPhase1Message;
            break;

        case FRAMEWORK_OBJECT_MANAGER_REJOIN_CLUSTER_SECONDARY_HA_PEER_PHASE_3:
            pWaveMessage = new WaveRejoinClusterSecondaryHaPeerPhase3Message;
            break;

        case FRAMEWORK_OBJECT_MANAGER_PRIMARY_CHANGED_MESSAGE_HA_PEER:
            pWaveMessage = new FrameworkObjectManagerPrimaryChangedHaPeerMessage;
            break;

        case FRAMEWORK_OBJECT_MANAGER_PRIMARY_CHANGED_PHASE_1_HA_PEER_MESSAGE:
            pWaveMessage = new FrameworkObjectManagerPrimaryChangedHaPeerPhase1Message;
            break;

        case FRAMEWORK_OBJECT_MANAGER_PRIMARY_CHANGED_PHASE_3_HA_PEER_MESSAGE:
            pWaveMessage = new FrameworkObjectManagerPrimaryChangedHaPeerPhase3Message;
            break;

        case FRAMEWORK_OBJECT_MANAGER_ROLLBACK_STANDBY_ON_ACTIVE_ROLLBACK:
            pWaveMessage = new FrameworkObjectManagerRollbackStandbyOnActiveRollbackMessage;
            break;

        case FRAMEWORK_OBJECT_MANAGER_REPLAY_CONFIG_FILE:
            pWaveMessage = new WaveFrameworkReplayConfigMessage ();
            break;

        default :
            pWaveMessage = NULL;
    }

    return (pWaveMessage);
}

WaveServiceId WaveFrameworkObjectManager::getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

void WaveFrameworkObjectManager::boot (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    // First reply to it.  Initializemessage is sent to us by ourselves.
    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();

    // Initialize the last used location Id.

    initializeLastUsedLocationId ();

    OrmRepository* pOrmRepository = OrmRepository::getInstance();

    pOrmRepository->computeTableSpace();

    /* zeroize if previous zeroize was incomplete */
    validateAndZeroizeAtBoot();

    // Start the Initialization sequnce.

    ResourceId status = m_pInitializeWorker->startWaveServices ();

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::boot Initial Boot of Services should Never Fail");
        waveAssert (false, __FILE__, __LINE__);
    }

}

void  WaveFrameworkObjectManager::validateAndZeroizeAtBoot()
{
    ifstream zeroizeStream(getFIPSZeroizeFile().c_str());
    bool noShutdownAtZeroize = true;
    if(zeroizeStream.is_open())
    {
        /*File exists, zeroize was not complete. So complete now.
         */
        zeroizeStream.close();
        trace(TRACE_LEVEL_INFO,"WaveFrameworkObjectManager::validateAndZeroizeAtBoot: Previous zeroize was incomplete. Clearing now..\n");
        Wave::logOperationStatus (FIPS_OPERATION_TRIGGER_CLEANUP_FOR_ZEROIZE);
    
        FrameworkSequenceGenerator &frameworkSequenceGenerator = getCurrentFrameworkSequenceGenerator ();
        WaveZeroizeAgent *pZAgent = new WaveZeroizeAgent(this, frameworkSequenceGenerator,noShutdownAtZeroize);

        waveAssert(NULL != pZAgent, __FILE__,__LINE__);
    
        ResourceId status = pZAgent->execute();
        if(status != WAVE_MESSAGE_SUCCESS)
        {
            trace(TRACE_LEVEL_FATAL,"WaveFrameworkObjectManager::validateAndZeroizeAtBoot: one or more services failed to zeroize\n");
            waveAssert(false,__FILE__,__LINE__);
        }
    }
    else
    {
        trace(TRACE_LEVEL_INFO,"WaveFrameworkObjectManager::validateAndZeroizeAtBoot: state is clean.\n");
    }
    

}

void WaveFrameworkObjectManager::bootWave ()
{
    setIsFrameworkReadyToBoot (true);
}

void WaveFrameworkObjectManager::waitForWaveServicesToFinish ()
{
    WaveMutex mutexForAllWaveServices;

	// double lock to ensure this function doesn't complete
    mutexForAllWaveServices.lock ();
    mutexForAllWaveServices.lock ();
}

void WaveFrameworkObjectManager::configureThisLocationAsLocation (SI32 port)
{
    if (NULL != m_pThisLocation)
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::configureThisLocationAsLocation : This location is already configured");
        waveAssert (false, __FILE__, __LINE__);
        return;
    }

    string ipAddress = getIpAddressForThisLocation ();

    if ("" == ipAddress)
    {
        ipAddress = FrameworkToolKit::getLoopBackIpAddressForThisMachine ();
    }

    LocationId locationId = (UI32) (1 << 8);

    m_pThisLocation = new Location (locationId, ipAddress, port);

    if (NULL == m_pThisLocation)
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::configureThisLocationAsLocation : Could not allocate a Location.");
        waveAssert (false, __FILE__, __LINE__);
        return;
    }

    m_pThisLocation->setClusterPrimaryLocationId (locationId);
    m_pThisLocation->setClusterPrimaryPort       (port);
}

void WaveFrameworkObjectManager::configureThisLocationAsSubLocation (LocationId parentLocationId, string &parentIpAddress, SI32 parentPort, LocationId locationId, string &ipAddress, SI32 port)
{
    if (NULL != m_pThisLocation)
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::configureThisLocationAsSubLocation : This location is already configured");
        waveAssert (false, __FILE__, __LINE__);
    }

    SubLocation *pSubLocation = new SubLocation (parentLocationId, parentIpAddress, parentPort, locationId, ipAddress, port);

    if (NULL == pSubLocation)
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::configureThisLocationAsSubLocation : Could not allocate a Sub Location.");
        waveAssert (false, __FILE__, __LINE__);
    }

    Location *pLocation = new Location (parentLocationId, parentIpAddress, parentPort);

    if (NULL == pLocation)
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::configureThisLocationAsSubLocation : Could not allocate a Location.");
        waveAssert (false, __FILE__, __LINE__);
    }

    pSubLocation->setPParentLocation (pLocation);
    pSubLocation->setClusterPrimaryLocationId (parentLocationId);
    pSubLocation->setClusterPrimaryPort       (parentPort);

    m_pThisLocation = pSubLocation;
}

bool WaveFrameworkObjectManager::addSubLocation (LocationId locationId, string &ipAddress, SI32 port)
{
    if (NULL == m_pThisLocation)
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::addSubLocation : This location is not configured yet.");
        waveAssert (false, __FILE__, __LINE__);
    }

    if (true == (m_pThisLocation->supportsSubLocations ()))
    {
        m_pThisLocation->addSubLocation (locationId, ipAddress, port);
        return (true);
    }
    else
    {
        return (false);
    }
}

void WaveFrameworkObjectManager::setFrameworkSequenceType (FrameworkSequenceType frameworkSequenceType)
{
    s_frameworkSequenceType = frameworkSequenceType;
}

void WaveFrameworkObjectManager::initializeServerCommunications ()
{
    static const UI32 retryCount = 120;
                 UI32 i          = 0;

    if (NULL != m_pThisLocation)
    {
        ServerStreamingSocketStatus status = SERVER_STREAMING_SOCKET_ERROR_COULD_NOT_BIND;

        while (SERVER_STREAMING_SOCKET_SUCCESS != status)
        {
            status = m_pThisLocation->initializeServerCommunications ();

            i++;

            if (SERVER_STREAMING_SOCKET_SUCCESS != status)
            {
                if (i >= retryCount)
                {
                    if (SERVER_STREAMING_SOCKET_ERROR_COULD_NOT_BIND == status)
                    {
                        trace (TRACE_LEVEL_ERROR, "Could not bind to Local TCP/IP Socket.  Please make sure that there is no other instance of this program is currently active.");
                    }
                    else if (SERVER_STREAMING_SOCKET_ERROR_COULD_NOT_LISTEN == status)
                    {
                        trace (TRACE_LEVEL_ERROR, "Could not listen on a Local TCP/IP Socket.  Please make sure that there is no other instance of this program is currently active.");
                    }
                    else
                    {
                        trace (TRACE_LEVEL_ERROR, "Server Socket error.  Please make sure that there is no other instance of this program is currently active.");
                    }

                    // For now, if we cannot start Server communications we exit.

                    exit (2);
                }
                else
                {
                    trace (TRACE_LEVEL_WARN, "Still Waiting for TCP/IP Layer to allow us to bind on Server Socket ...");

                    prismSleep (1);
                }
            }
            else
            {
                trace (TRACE_LEVEL_SUCCESS, "Succeeded in binding on Server Socket.");
                return;
            }
        }
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::initializeServerCommunications : This Locations is not configured yet.");
        waveAssert (false, __FILE__, __LINE__);
    }
}

void WaveFrameworkObjectManager::initializeClientCommunications ()
{
    if (NULL != m_pThisLocation)
    {
        m_pThisLocation->initializeClientCommunications ();
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::initializeClientCommunications : This Locations is not configured yet.");
        waveAssert (false, __FILE__, __LINE__);
    }
}

bool WaveFrameworkObjectManager::acceptNewConnection (ServerStreamingSocket &newSocket)
{
    bool successfullyAcceptedNewConnection = false;

    if (NULL != m_pThisLocation)
    {
        successfullyAcceptedNewConnection = m_pThisLocation->acceptNewConnection (newSocket);
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::acceptNewConnection : This Locations is not configured yet.");
        waveAssert (false, __FILE__, __LINE__);
    }

    return (successfullyAcceptedNewConnection);
}

void WaveFrameworkObjectManager::disconnectFromLocation (LocationId locationId, const bool &closePeerServerSocket)
{
    s_disconnectMutex.lock ();

    if (0 != locationId)
    {
        string ipAddress = FrameworkToolKit::getIpAddressForLocationId (locationId);
        SI32   port      = FrameworkToolKit::getPortForLocationId      (locationId);

        trace (TRACE_LEVEL_WARN, "WaveFrameworkObjectManager::disconnectFromLocation : Disconnecting from Location : " + ipAddress + string (", Port : ") + port);

        if (true == closePeerServerSocket)
        {
            InterLocationMessageReceiverObjectManager::closePeerServerStreamingSocketAndRemoveInterLocationMessageReceiverThreadFromCache (ipAddress, port);
        }

        m_pThisLocation->invalidateClientStreamingSocketForRemoteLocation (locationId);
        (InterLocationMessageTransportObjectManager::getInstance ())->replyToRemoteMessagesPendingOnLocation (locationId, WAVE_MESSAGE_ERROR_REMOTE_LOCATION_UNAVAILABLE);
    }

    s_disconnectMutex.unlock ();
}

void WaveFrameworkObjectManager::disconnectFromLocation (const string &ipAddress, const SI32 &port, const bool &closePeerServerSocket)
{
    if (0 == (FrameworkToolKit::getLocationIdForIpAddressAndPort (ipAddress, port)))
    {
        trace (TRACE_LEVEL_WARN, "WaveFrameworkObjectManager::disconnectFromLocation : We have already disconnected from Location : " + ipAddress);
    }
    else
    {
        disconnectFromLocation (m_pThisLocation->getLocationIdForIpAddressAndPort (ipAddress, port), closePeerServerSocket);
    }
}

void WaveFrameworkObjectManager::removeKnownLocation (const LocationId &locationId)
{
    s_disconnectMutex.lock ();

    if (0 != locationId)
    {
        trace (TRACE_LEVEL_WARN, "WaveFrameworkObjectManager::removeKnownLocation : Disconnecting from Location : " + FrameworkToolKit::getIpAddressForLocationId (locationId));
        m_pThisLocation->invalidateClientStreamingSocketForRemoteLocation (locationId);
        (InterLocationMessageTransportObjectManager::getInstance ())->replyToRemoteMessagesPendingOnLocation (locationId, WAVE_MESSAGE_ERROR_REMOTE_LOCATION_UNAVAILABLE);
        m_pThisLocation->removeKnownLocation (locationId);
    }

    s_disconnectMutex.unlock ();
}

ResourceId WaveFrameworkObjectManager::connectToLocation (const string &ipAddress, const SI32 &port)
{
    static const UI32 maximumNumberOfRetriesToConnectToARemoteLocation  = 10;
    static const UI32 maximumNumberOfSecondsToWaitToConnect             = 10;

    return (m_pThisLocation->connectToRemoteLocation (m_pThisLocation->getLocationIdForIpAddressAndPort (ipAddress, port), maximumNumberOfRetriesToConnectToARemoteLocation, maximumNumberOfSecondsToWaitToConnect));
}

LocationBase *WaveFrameworkObjectManager::getThisLocation () const
{
    return (m_pThisLocation);
}

const UI32 WaveFrameworkObjectManager::getThisLocationId () const
{
    return ((getThisLocation ())->getLocationId ());
}

void WaveFrameworkObjectManager::setIsFrameworkReadyToBoot (bool isFrameworkReadyToBoot)
{
    s_pFrameworkReadinessMutex->lock ();
    s_isFrameworkReadyToBoot = isFrameworkReadyToBoot;
    s_pFrameworkReadinessMutex->unlock ();
}

bool WaveFrameworkObjectManager::getIsFrameworkReadyToBoot ()
{
    bool isFrameworkReadyToBoot = false;

    s_pFrameworkReadinessMutex->lock ();
    isFrameworkReadyToBoot = s_isFrameworkReadyToBoot;
    s_pFrameworkReadinessMutex->unlock ();

    return (isFrameworkReadyToBoot);
}

void WaveFrameworkObjectManager::addWaveThreadId (const WaveThreadId &prismThreadId)
{
    s_prismThredIdRepositoryMutex.lock ();

    s_prismThreadIdRepository [prismThreadId] = prismThreadId;

    s_prismThredIdRepositoryMutex.unlock ();
}

void WaveFrameworkObjectManager::removeWaveThreadId (const WaveThreadId &prismThreadId)
{
    s_prismThredIdRepositoryMutex.lock ();

    map<WaveThreadId, WaveThreadId>::iterator  element = s_prismThreadIdRepository.find (prismThreadId);
    map<WaveThreadId, WaveThreadId>::iterator  end     = s_prismThreadIdRepository.end (); 

    if (end != element)
    {   
        s_prismThreadIdRepository.erase (element);
    }
    else
    {
        WaveNs::trace (TRACE_LEVEL_WARN, string ("WaveFrameworkObjectManager::removeWaveThreadId This thread Id does not exist"));
    } 

    s_prismThredIdRepositoryMutex.unlock ();    
}

void WaveFrameworkObjectManager::getAllWaveThreads (map<WaveThreadId, WaveThreadId> &prismThreadsMap)
{
    s_prismThredIdRepositoryMutex.lock ();

    prismThreadsMap = s_prismThreadIdRepository;

    s_prismThredIdRepositoryMutex.unlock ();
}
        
void WaveFrameworkObjectManager::deleteAllWaveThreads ()
{
    map<WaveThreadId, WaveThreadId>::iterator  threadIterator;
    UI32 retVal = 0;
    s_prismThredIdRepositoryMutex.lock ();

    // This code has been added so that we test the existence of the thread id that is pthread_cancel'ed before proceeding to kill other pthreads
    // Also, at the end of the function we do not unlock the mutex so that no other deleteAllWaveThreads call is made to kill the same set of threads again

    for (threadIterator = s_prismThreadIdRepository.begin (); threadIterator != s_prismThreadIdRepository.end (); threadIterator++)
    {   
        retVal = pthread_cancel (threadIterator->first);
        
        while (1)
        {
            retVal = pthread_kill (threadIterator->first, 0);
            if (!retVal)
            {
                WaveNs::tracePrintf (TRACE_LEVEL_DEBUG, false, false, "WaveFrameworkObjectManager::deleteAllWaveThreads : Thread successfully canceled \n");
                break;
            }
            else
            {
                prismUSleep (100000);
            }
        }
    }   

    //s_prismThredIdRepositoryMutex.unlock ();
}

ResourceId WaveFrameworkObjectManager::createBufferForFileToSync ( const string &filenameToSync, char* &pfileBuffer, UI32 &sizeOfFileBuffer )
{
    ResourceId status = WAVE_MESSAGE_SUCCESS;

    trace (TRACE_LEVEL_DEVEL, string("WaveFrameworkObjectManager::createBufferForFileToSync : filename - ") + filenameToSync );
    ifstream file;
    file.open ( (filenameToSync).c_str() );

    if ( true == file.is_open() )
    {
        file.seekg (0, ios::end);
        UI32 fileSize = file.tellg ();
        char * pBuffer = NULL;
        if ( 0 < fileSize )
        {
            pBuffer = new char [fileSize];
            waveAssert ( NULL != pBuffer, __FILE__, __LINE__ );         
            file.seekg (0, ios::beg);
            file.read ( pBuffer, fileSize );
            pfileBuffer = pBuffer;
            sizeOfFileBuffer= fileSize;   
        }
        else
        {
            trace (TRACE_LEVEL_ERROR, string("WaveFrameworkObjectManager::createBufferForFileToSync : Empty file - \"") + filenameToSync + ("\"") );
        }
    } 
    else
    {
        status = WAVE_MESSAGE_ERROR;
        trace (TRACE_LEVEL_ERROR, string("WaveFrameworkObjectManager::createBufferForFileToSync : Unable to open file - \"") + filenameToSync + ("\"") );    
    }
    file.close();

    return (status);
} 

ResourceId WaveFrameworkObjectManager::createFileForSyncBuffer ( const string &filenameToSync, char* &pfileBuffer, UI32 &sizeOfFileBuffer )
{
    ResourceId status = WAVE_MESSAGE_SUCCESS;
    
    waveAssert ( NULL != pfileBuffer, __FILE__, __LINE__ );

    trace (TRACE_LEVEL_DEVEL, string("WaveFrameworkObjectManager::createFileForSyncBuffer : filename - ") + filenameToSync );
    ofstream file;
    file.open ( (filenameToSync).c_str() );

    if ( true == file.is_open() )
    {   
        if ( 0 < sizeOfFileBuffer )
        {  
            file.write ( pfileBuffer, sizeOfFileBuffer );
        }
        else
        {
            trace (TRACE_LEVEL_ERROR, string("WaveFrameworkObjectManager::createFileForSyncBuffer : Empty file - \"") + filenameToSync + ("\"") );
        }
    }
    else
    {
        status = WAVE_MESSAGE_ERROR;   
        trace (TRACE_LEVEL_ERROR, string("WaveFrameworkObjectManager::createFileForSyncBuffer : Unable to open file - \"") + filenameToSync + ("\"") );
    }
    file.close();

    return (status);
}

void WaveFrameworkObjectManager::createDatabaseBackupBuffer(char * &pDatabaseBackupBuffer, SI32 &sizeOfBackupFile)
{
    ifstream  databaseBackupFile;


    string sBackupFilename = FrameworkToolKit::getProcessInitialWorkingDirectory() + "/" + FrameworkToolKit::getDatabaseBackupFileName ();
    databaseBackupFile.open (sBackupFilename.c_str (), ios::binary);
    databaseBackupFile.seekg (0, ios::end);
    sizeOfBackupFile = databaseBackupFile.tellg ();

    waveAssert (0 != sizeOfBackupFile, __FILE__, __LINE__);

    if (0 < sizeOfBackupFile)
    {
        pDatabaseBackupBuffer = new char[sizeOfBackupFile];

        waveAssert (NULL != pDatabaseBackupBuffer, __FILE__, __LINE__);

        databaseBackupFile.seekg (0, ios::beg);
        databaseBackupFile.read (pDatabaseBackupBuffer, sizeOfBackupFile);
    }

    databaseBackupFile.close ();
}

void WaveFrameworkObjectManager::createClusterWithNodesMessageHandler (WaveCreateClusterWithNodesMessage *pWaveCreateClusterWithNodesMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::stopClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rollbackNodeIfRequiredStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesValidateLocationRoleStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesValidateStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesCollectValidationDataStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesReplayGlobalOnlyConfigIfRequiredStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesPausePersistenceStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesAddKnownLocationsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesConnectToNewKnownLocationsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase1Step),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesResumeDatabaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase2Step),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesSendValidationResultsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesSendListOfSecondariesToAllNodesStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::broadcastNewNodesAddedEventOnPrimaryStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::sendReplyBackToClusterGlobalService),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::failoverforNodesFailedInPhase2),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase3Step),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::startHeartBeatToSecondaryNodes),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::broadcastClusterPhase3CompleteEvent),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::broadcastNodesAdditionToClusterCompletedEvent),

        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::primaryNodeClusterSuccessStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::primaryNodeClusterFailureStep),
    };

    CreateClusterWithNodesContext *pCreateClusterWithNodesContext = new CreateClusterWithNodesContext (pWaveCreateClusterWithNodesMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pCreateClusterWithNodesContext->setIsCreateClusterContext (true);

    // Set an indication that cluster operation is in progress on primary node
    setPrimaryNodeClusterOperationFlag (true);
    
    // Setting the flag here instead of setting in the context constructor to help in the following case:
    // When a primary node is becoming secondary(flag is set TRUE), primary controlled failover is done
    // followed by destroy cluster which resets the flag to FALSE in base class context (CreateClusterWithNodesContext)
    // The flag should always be TRUE on a secondary node joining the cluster and should not be reset upon failover.
    // This causes issue when operations are allowed based on the status of the flag on a secondary node
    setSecondaryNodeClusterCreationFlag (false);

    pCreateClusterWithNodesContext->holdAll ();
    pCreateClusterWithNodesContext->start ();
}

void WaveFrameworkObjectManager::createClusterWithNodesValidateLocationRoleStep (CreateClusterWithNodesContext *pCreateClusterWithNodesContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::createClusterWithNodesValidateLocationRoleStep : Starting ...");

    WaveCreateClusterWithNodesMessage *pWaveCreateClusterWithNodesMessage = reinterpret_cast<WaveCreateClusterWithNodesMessage *> (pCreateClusterWithNodesContext->getPWaveMessage ());
    LocationRole                        currentRole                         = m_pThisLocation->getLocationRole ();
    ResourceId                          status                              = WAVE_MESSAGE_SUCCESS;

    // FIXME : Sagar : Once we implement shutting down location services prior to configuring a location as part of a cluster
    //                 will make things easier.  Until then we must have following statement to adjust the sender locationid
    //                 in the cluster creation message.  Since the message has been generated, we might have changed our locationId.
    //                 Also we know that this request can only come from the CEntral cluster that is local to us.

    pWaveCreateClusterWithNodesMessage->setSenderLocationId (FrameworkToolKit::getThisLocationId ());

    if (LOCATION_PRIMARY == currentRole)
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::createClusterWithNodesValidateLocationRoleStep : We are already Primary of a cluster.  Will not honor the request to create a cluster.  Will not reply.");
        status = FRAMEWORK_ERROR_LOCATION_ALREADY_CONFIGURED;
    }
    if (LOCATION_SECONDARY == currentRole)
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::createClusterWithNodesValidateLocationRoleStep : We are already Secondary of a cluster.  Will not honor the request to create a cluster.  Will not reply.");
        status = FRAMEWORK_ERROR_LOCATION_ALREADY_CONFIGURED;
    }
    else if (currentRole == LOCATION_SUB_LOCATION)
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::createClusterWithNodesValidateLocationRoleStep : SubLocations cannot create clusters.  Will not reply.");
        status = FRAMEWORK_ERROR_SUB_LOCATION_CANNOT_BECOME_MEMBER_OF_A_CLUSTER;
    }

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        // In this case we do not want the reply to be sent over to the remote location that requested.
        // If we respond it may cause the response to be delivered to a wrong location as the requesting
        // location is considered to be an imposter.

        pWaveCreateClusterWithNodesMessage->setDropReplyAcrossLocations (true);
    }

    pCreateClusterWithNodesContext->executeNextStep (status);
    return;
}

void WaveFrameworkObjectManager::createClusterWithNodesValidateStep (CreateClusterWithNodesContext *pCreateClusterWithNodesContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::createClusterWithNodesValidateStep : Starting ...");

    WaveCreateClusterWithNodesMessage *pWaveCreateClusterWithNodesMessage = reinterpret_cast<WaveCreateClusterWithNodesMessage *> (pCreateClusterWithNodesContext->getPWaveMessage ());
    UI32                                numberOfNewNodes                    = pWaveCreateClusterWithNodesMessage->getNumberOfNewNodes ();
    UI32                                i                                   = 0;
    string                              thisLocationIpAddress               = FrameworkToolKit::getThisLocationIpAddress ();
    SI32                                thisLocationPort                    = FrameworkToolKit::getThisLocationPort ();

    if (NULL == m_pThisLocation)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::createClusterWithNodesValidateStep : Trying to create a cluster without configuring this location first.");
        waveAssert (false, __FILE__, __LINE__);
        pCreateClusterWithNodesContext->executeNextStep (FRAMEWORK_ERROR_LOCATION_NOT_CONFIGURED);
        return;
    }
    else
    {
        if (true != (FrameworkToolKit::isThisALocation ()))
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::createClusterWithNodesValidateStep : Trying to create a cluster using a sub location");
            waveAssert (false, __FILE__, __LINE__);
            pCreateClusterWithNodesContext->executeNextStep (FRAMEWORK_ERROR_SUB_LOCATION_CANNOT_CREATE_CLUSTER);
            return;
        }

        // FIXME : sagar : validate if this is a Stand alone location.
    }

    for (i = 0; i < numberOfNewNodes; i++)
    {
        string ipAddress = pWaveCreateClusterWithNodesMessage->getNodeAt (i);
        SI32   port             = pWaveCreateClusterWithNodesMessage->getNodePortAt (i);

        if ("" == ipAddress)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::createClusterWithNodesValidateStep : Trying to create a cluster using NULL ipAddress (" + ipAddress + ")");
            pCreateClusterWithNodesContext->executeNextStep (FRAMEWORK_ERROR_NULL_IPADDRESS);
            return;
        }

        // Check if the ipaddress represents a valid ipaddress in number and dots format.

        sockaddr_in socketAddress;

        SI32 status = inet_pton (AF_INET, ipAddress.c_str (), &socketAddress.sin_addr);

        if (0 >= status)
        {
            trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::createClusterWithNodesValidateStep : Trying to create a cluster using an invalid ipAddress (" + ipAddress + ")");
            pCreateClusterWithNodesContext->executeNextStep (FRAMEWORK_ERROR_INVALID_IPADDRESS);
            return;
        }

        if (true == (FrameworkToolKit::isAnIpAddressForThisMachine (ipAddress)))
        {
            if (thisLocationPort == port)
            {
                trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::createClusterWithNodesValidateStep : Trying to create a cluster using self as partner (" + ipAddress + ")");
                pCreateClusterWithNodesContext->executeNextStep (FRAMEWORK_ERROR_CANNOT_CREATE_HA_WITH_SELF);
                return;
            }
        }
    }

    pCreateClusterWithNodesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    return;
}

void WaveFrameworkObjectManager::createClusterWithNodesCollectValidationDataStep (CreateClusterWithNodesContext *pCreateClusterWithNodesContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::createClusterWithNodesCollectValidationDataStep : Starting ...");

    vector<WaveServiceId>  waveServiceIds;
    UI32                    numberOfWaveServiceIds;
    UI32                    i;
    LocationId              thisLocationId               = FrameworkToolKit::getThisLocationId ();
    ResourceId              status                       = WAVE_MESSAGE_SUCCESS;
    vector<WaveServiceId> &waveServiceIdsToCommunicate = pCreateClusterWithNodesContext->getWaveServiceIdsToCommunicate ();

    WaveThread::getListOfServiceIds (waveServiceIds);
    numberOfWaveServiceIds = waveServiceIds.size ();

    for (i = 0; i < numberOfWaveServiceIds; i++)
    {
        trace (TRACE_LEVEL_DEBUG, string ("WaveFrameworkObjectManager::createClusterWithNodesCollectValidationDataStep : Collecting Validation Information from Service : ") + waveServiceIds[i]);

        if (true == (isServiceToBeExcludedInClusterCommunications (waveServiceIds[i])))
        {
            continue;
        }

        // Collect the list of services so that we use the list later.

        waveServiceIdsToCommunicate.push_back (waveServiceIds[i]);

        WaveObjectManagerCollectValidationDataMessage message (waveServiceIds[i]);

        status  = sendSynchronously (&message, thisLocationId);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            status = FRAMEWORK_ERROR_COULD_NOT_COLLECT_VALIDATION_DATA;
            trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::createClusterWithNodesCollectValidationDataStep : Failed to obtain Validation Details for Service (") + FrameworkToolKit::getServiceNameById (waveServiceIds[i]) + "), Status : " + FrameworkToolKit::localize (status));
            break;
        }

        status = message.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            status = FRAMEWORK_ERROR_COULD_NOT_COLLECT_VALIDATION_DATA;
            trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::createClusterWithNodesCollectValidationDataStep : Failed to obtain Validation Details for Service (") + FrameworkToolKit::getServiceNameById (waveServiceIds[i]) + "), Completion Status : " + FrameworkToolKit::localize (status));
            break;
        }

        void *pData = NULL;
        UI32  size  = 0;

        message.getValidationDetails (pData, size);

        if ((0 != size) && (NULL != pData))
        {
            trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::createClusterWithNodesCollectValidationDataStep : Obtained Validation Data for Service : " + FrameworkToolKit::getServiceNameById (waveServiceIds[i]));

            pCreateClusterWithNodesContext->addValidationDetailsForService (waveServiceIds[i], pData, size);
        }
        else
        {
            trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::createClusterWithNodesCollectValidationDataStep : No Validation details are obtained for Service : " + FrameworkToolKit::getServiceNameById (waveServiceIds[i]));
        }
    }

    pCreateClusterWithNodesContext->executeNextStep (status);
}

void WaveFrameworkObjectManager::createClusterWithNodesAddKnownLocationsStep (CreateClusterWithNodesContext *pCreateClusterWithNodesContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::createClusterWithNodesAddKnownLocationsStep : Starting ...");

    WaveCreateClusterWithNodesMessage *pWaveCreateClusterWithNodesMessage = reinterpret_cast<WaveCreateClusterWithNodesMessage *> (pCreateClusterWithNodesContext->getPWaveMessage ());
    UI32                                numberOfNewNodes                    = pWaveCreateClusterWithNodesMessage->getNumberOfNewNodes ();
    UI32                                i                                   = 0;
    UI32                                numberOfFailures                    = 0;
    string                              ipAddress                           = "";
    SI32                                port                                = 0;
    LocationId                          newLocationId                       = 0;

    for (i = 0; i < numberOfNewNodes; i++)
    {
        ipAddress = pWaveCreateClusterWithNodesMessage->getNodeAt (i);
        port      = pWaveCreateClusterWithNodesMessage->getNodePortAt (i);

        if (false == (FrameworkToolKit::isAKnownLocation (ipAddress, port)))
        {
            newLocationId = getNextLocationId ();

            if (0 != newLocationId)
            {
                m_pThisLocation->addKnownLocation (newLocationId, ipAddress, port);
                pCreateClusterWithNodesContext->addNewLocationId (newLocationId);
            }
            else
            {
                numberOfFailures++;
                trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::createClusterWithNodesAddKnownLocationsStep Location Ids are not Available");
                pWaveCreateClusterWithNodesMessage->setNewNodeStatus (ipAddress, port, FRAMEWORK_ERROR_NO_UNUSED_LOCATION_IDS_AVAILABLE);
            }
        }
        else
        {
            numberOfFailures++;
            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::createClusterWithNodesAddKnownLocationsStep Already a member of cluster");
            pWaveCreateClusterWithNodesMessage->setNewNodeStatus (ipAddress, port, FRAMEWORK_ERROR_IPADDRESS_ALREADY_MEMBER_OF_CLUSTER);
        }
    }

    if (numberOfFailures == numberOfNewNodes)
    {
        trace (TRACE_LEVEL_INFO, string ("Number of failures = ") + numberOfFailures);

        resumePersistence ();
        pCreateClusterWithNodesContext->executeNextStep (FRAMEWORK_ERROR_CANNOT_CREATE_CLUSTER_NO_VALID_RESOURCES);
    }
    else
    {
        pCreateClusterWithNodesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
}

void WaveFrameworkObjectManager::createClusterWithNodesConnectToNewKnownLocationsStep (CreateClusterWithNodesContext *pCreateClusterWithNodesContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::createClusterWithNodesConnectToNewKnownLocationsStep : Starting ...");

    static const UI32                                maximumNumberOfRetriesToConnectToARemoteLocation  = 30;
    static const UI32                                maximumNumberOfSecondsToWaitToConnect             = 30;
                 WaveCreateClusterWithNodesMessage *pWaveCreateClusterWithNodesMessage               = reinterpret_cast<WaveCreateClusterWithNodesMessage *> (pCreateClusterWithNodesContext->getPWaveMessage ());
                 UI32                                numberOfNewLocationIds                            = pCreateClusterWithNodesContext->getNumberOfNewLocationIds ();
                 LocationId                          newLocationId                                     = 0;
                 SI32                                i                                                 = 0;
                 string                              ipAddress                                         = "";
                 SI32                                port                                              = 0;
                 ResourceId                          status                                            = FRAMEWORK_SUCCESS;
                 UI32                                numberOfFailures                                  = 0;

    for (i = numberOfNewLocationIds - 1; i >= 0; i--)
    {
        newLocationId = pCreateClusterWithNodesContext->getNewLocationIdAt ((UI32) i);
        ipAddress     = FrameworkToolKit::getIpAddressForLocationId (newLocationId);
        port          = FrameworkToolKit::getPortForLocationId (newLocationId);

        if (0 != newLocationId)
        {
            status = m_pThisLocation->connectToRemoteLocation (newLocationId, maximumNumberOfRetriesToConnectToARemoteLocation, maximumNumberOfSecondsToWaitToConnect);

            if (FRAMEWORK_SUCCESS != status)
            {
                trace (TRACE_LEVEL_ERROR, string("WaveFrameworkObjectManager::createClusterWithNodesConnectToNewKnownLocationsStep : failed to connect IP = ") + ipAddress + 
                    " Port = " + port + " newLocation = " + newLocationId);
                // Indicate that the status saying that we could not connect to the location.
                // For this location we will not send a message to configure itself as a secondary.

                pWaveCreateClusterWithNodesMessage->setNewNodeStatus (ipAddress, port, status);

                // Since we are not able to connect to the location remove it from the known locations.

                removeKnownLocation (newLocationId);
                pCreateClusterWithNodesContext->removeNewLocationId (newLocationId);
                numberOfFailures++;
            }
        }
        else
        {
            numberOfFailures++;
        }
    }

    if (numberOfFailures == numberOfNewLocationIds)
    {
        resumePersistence ();
        pCreateClusterWithNodesContext->executeNextStep (FRAMEWORK_ERROR_FAILED_TO_CONECT_TO_ALL_NEW_LOCATIONS);
    }
    else
    {
        pCreateClusterWithNodesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
}

void WaveFrameworkObjectManager::createClusterWithNodesReplayGlobalOnlyConfigIfRequiredStep (CreateClusterWithNodesContext *pCreateClusterWithNodesContext)
{
    ResourceId status = WAVE_MESSAGE_SUCCESS;

    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::createClusterWithNodesReplayGlobalOnlyConfigIfRequiredStep : Starting ...");

    string configFilePath           = ConfigFileManagementToolKit::getConfigFileManagementScriptsDirectory ();
    string configFilename           = ConfigFileManagementToolKit::getConfigFileManagementGlobalOnlyFilename ();
    string fullConfigFilename       = configFilePath + "/" + configFilename;
    string preConfigReplayCommands  = "bypassCliValidations cluster-formation";

    if (true == ConfigFileManagementToolKit::isFileExisting (fullConfigFilename))
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::createClusterWithNodesReplayGlobalOnlyConfigIfRequiredStep : Replay global-only config file on principal node...");

        status = ConfigFileManagementToolKit::replayConfigurationFile (configFilePath, configFilename, preConfigReplayCommands);

        
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::createClusterWithNodesReplayGlobalOnlyConfigIfRequiredStep : Replay of global-only config file on principal node completed with status: " + FrameworkToolKit::localize (status));

        if (WAVE_MESSAGE_SUCCESS == status)
        {
            string newConfigFilename = fullConfigFilename + "." + FrameworkToolKit::getThisLocationIpAddress () + ".backup";

            ConfigFileManagementToolKit::renameConfigurationFile (fullConfigFilename, newConfigFilename);
        }
    }
    else
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::createClusterWithNodesReplayGlobalOnlyConfigIfRequiredStep : Skipping this step. " + fullConfigFilename + " does not exist.");
    }

    pCreateClusterWithNodesContext->executeNextStep (status);
}

void WaveFrameworkObjectManager::backUpDatabaseAfterSendingClusterPhase0Message ()
{
    string backupFileName = string (FrameworkToolKit::getProcessInitialWorkingDirectory () + "/" + FrameworkToolKit::getDatabaseBackupFileName ());

    DatabaseObjectManagerBackupMessage message (backupFileName);
    message.setDataOnlyBackup (true);

    ResourceId status  = sendSynchronously (&message);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::backUpDatabaseAfterSendingClusterPhase0Message : Could not send message to backup database.  Status : " + FrameworkToolKit::localize (status));
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        status = message.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::backUpDatabaseAfterSendingClusterPhase0Message : Message to backup database failed.  Completion Status : " + FrameworkToolKit::localize (status));
            waveAssert (false, __FILE__, __LINE__);
        }     
        else  
        {     
             trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::backUpDatabaseAfterSendingClusterPhase0Message : Successfully backed up the database.");
        }     
    }
}

void WaveFrameworkObjectManager::createClusterWithNodesPausePersistenceStep (CreateClusterWithNodesContext *pCreateClusterWithNodesContext)
{
    // Pause the persistence object manager before taking a backup of the DB.

    pausePersistence ();

    pCreateClusterWithNodesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsStep (CreateClusterWithNodesContext *pCreateClusterWithNodesContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsStep : Starting ...");

    WaveCreateClusterWithNodesMessage *pWaveCreateClusterWithNodesMessage = reinterpret_cast<WaveCreateClusterWithNodesMessage *> (pCreateClusterWithNodesContext->getPWaveMessage ());
    UI32                                numberOfNewLocationIds              = pCreateClusterWithNodesContext->getNumberOfNewLocationIds ();
    UI32                                i                                   = 0;
    LocationId                          thisLocationId                      = FrameworkToolKit::getThisLocationId ();
    SI32                                thisLocationPort                    = FrameworkToolKit::getThisLocationPort ();
    LocationId                          newLocationId                       = 0;
    string                              thisLocationIpAddress               = FrameworkToolKit::getThisLocationIpAddress ();
    string                              ipAddress                           = "";
    SI32                                port                                = 0;
    UI32                                numberOfFailures                    = 0;
    string                              prismVersionString                  = WaveVersion::getVersionString ();



    waveAssert (NULL != pWaveCreateClusterWithNodesMessage, __FILE__, __LINE__);

    ++(*pCreateClusterWithNodesContext);

    for (i = 0; i < numberOfNewLocationIds; i++)
    {
        newLocationId = pCreateClusterWithNodesContext->getNewLocationIdAt ((UI32) i);
        ipAddress     = FrameworkToolKit::getIpAddressForLocationId (newLocationId);
        port          = FrameworkToolKit::getPortForLocationId (newLocationId);

        // We will send configure message only to the locations that are known to us at this point.  If user supplied
        // a bogus ipaddress, we would have timed out trying to add that location in the previous step
        // and hence that location will not be known to us at this time.

        if (true == (FrameworkToolKit::isAKnownLocation (ipAddress, port)))
        {
            WaveConfigureClusterSecondaryMessage *pMessage = new WaveConfigureClusterSecondaryMessage (prismVersionString, thisLocationIpAddress, thisLocationPort, thisLocationId, ipAddress, port, newLocationId);

            // Add all the validation buffers to the message before sending out

            vector<WaveServiceId> &waveServiceIds                = pCreateClusterWithNodesContext->getWaveServiceIdsVector ();
            vector<void *>         &validationDetailsVector        = pCreateClusterWithNodesContext->getValidationDetailsVector ();
            vector<UI32>           &validationDetailsSizesVector   = pCreateClusterWithNodesContext->getValidationDetailsSizesVector ();

            UI32                    numberOfWaveServiceIds        = waveServiceIds.size ();
            UI32                    numberOfValidationDetails      = validationDetailsVector.size ();
            UI32                    numberOfValidationDetailsSizes = validationDetailsSizesVector.size ();
            UI32                    j                              = 0;

            waveAssert (numberOfWaveServiceIds == numberOfValidationDetails, __FILE__, __LINE__);
            waveAssert (numberOfWaveServiceIds == numberOfValidationDetailsSizes, __FILE__, __LINE__);

            for (j = 0; j < numberOfWaveServiceIds; j++)
            {
                if ((0 != validationDetailsSizesVector[j]) && (NULL != validationDetailsVector[j]))
                {
                    pMessage->addBuffer (waveServiceIds[j], validationDetailsSizesVector[j], validationDetailsVector[j]);
                }
                else
                {
                    trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsStep : We could not have added an entry with 0 size and/or NULL validation buffer.");
                    waveAssert (false, __FILE__, __LINE__);
                }
            }

            pMessage->setSchemaChangeVectors ();

            pMessage->setIsAddNodeForSpecialCaseFlag (pWaveCreateClusterWithNodesMessage->getIsAddNodeForSpecialCaseFlag ());

            pMessage->setToAllowSendForOneWayCommunication (true);

            WaveMessageStatus status = send (pMessage, reinterpret_cast<WaveMessageResponseHandler> (&WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsCallback), pCreateClusterWithNodesContext, s_clusterPhase0TimeoutInMilliseconds, newLocationId);

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                removeKnownLocation (newLocationId);
                pWaveCreateClusterWithNodesMessage->setNewNodeStatus (ipAddress, port, status);
                trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsStep : Not able to configure one secondary location : ") + newLocationId + string (" Error Code : ") + status);
                numberOfFailures++;

                delete pMessage;
            }
            else
            {
                ++(*pCreateClusterWithNodesContext);
            }
        }
        else
        {
            numberOfFailures++;
        }
    }

    backUpDatabaseAfterSendingClusterPhase0Message ();

    --(*pCreateClusterWithNodesContext);

    if (numberOfFailures == numberOfNewLocationIds)
    {
        resumeDatabaseOperation ();
        
        pCreateClusterWithNodesContext->executeNextStep (FRAMEWORK_ERROR_FAILED_TO_CONFIGURE_ALL_NEW_LOCATIONS);
    }
    else
    {
        pCreateClusterWithNodesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
}

void WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsCallback (FrameworkStatus frameworkStatus, WaveConfigureClusterSecondaryMessage *pWaveConfigureClusterSecondaryMessage, void *pContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsCallback : Starting ...");

    CreateClusterWithNodesContext      *pCreateClusterWithNodesContext      = reinterpret_cast<CreateClusterWithNodesContext *> (pContext);
    WaveCreateClusterWithNodesMessage *pWaveCreateClusterWithNodesMessage = reinterpret_cast<WaveCreateClusterWithNodesMessage *> (pCreateClusterWithNodesContext->getPWaveMessage ());
    LocationId                          newLocationId;
    string                              ipAddress;
    SI32                                port;

    --(*pCreateClusterWithNodesContext);

    if (NULL != pWaveConfigureClusterSecondaryMessage)
    {
        newLocationId = pWaveConfigureClusterSecondaryMessage->getLocationId ();
        ipAddress     = FrameworkToolKit::getIpAddressForLocationId (newLocationId);
        port          = FrameworkToolKit::getPortForLocationId (newLocationId);

        pCreateClusterWithNodesContext->addValidaionResultsLocation (ipAddress, port);

        vector<WaveServiceId> &waveServiceIdsToCommunicate = pCreateClusterWithNodesContext->getWaveServiceIdsToCommunicate ();
        UI32                    numberOfWaveServices        = waveServiceIdsToCommunicate.size ();
        UI32                    i                            = 0;

        for (i = 0; i < numberOfWaveServices; i++)
        {
            void *pValidationResults    = NULL;
            UI32  validationResultsSize = 0;

            pValidationResults = pWaveConfigureClusterSecondaryMessage->transferBufferToUser (s_offSetForValidationResults + waveServiceIdsToCommunicate[i], validationResultsSize);

            pCreateClusterWithNodesContext->addValidationResultsForService (ipAddress, port, waveServiceIdsToCommunicate[i], pValidationResults, validationResultsSize);
        }

        if (FRAMEWORK_SUCCESS == frameworkStatus)
        {
            waveAssert (NULL != pWaveConfigureClusterSecondaryMessage, __FILE__, __LINE__);

            ResourceId completionStatus = pWaveConfigureClusterSecondaryMessage->getCompletionStatus ();

            pWaveCreateClusterWithNodesMessage->setNewNodeStatus (ipAddress, port, completionStatus);

            if (WAVE_MESSAGE_SUCCESS != completionStatus)
            {
                trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsCallback : Configuring ") + ipAddress + " failed : " + completionStatus);
                removeKnownLocation (newLocationId);
            }
        }
        else
        {
            if (NULL != pWaveConfigureClusterSecondaryMessage)
            {
                LocationId newLocationId1 = pWaveConfigureClusterSecondaryMessage->getLocationId ();
                string     ipAddress1     = FrameworkToolKit::getIpAddressForLocationId (newLocationId1);
                SI32       port1          = FrameworkToolKit::getPortForLocationId (newLocationId1);

                pWaveCreateClusterWithNodesMessage->setNewNodeStatus (ipAddress1, port1, frameworkStatus);
    
                removeKnownLocation (newLocationId1);
            }
        }

    }

    if (NULL != pWaveConfigureClusterSecondaryMessage)
    {
        delete pWaveConfigureClusterSecondaryMessage;
    }

    if (0 == (pCreateClusterWithNodesContext->getNumberOfCallbacksBeforeAdvancingToNextStep ()))
    {
        UI32       numberOfNewIpAddresses  = pWaveCreateClusterWithNodesMessage->getNumberOfNewNodes ();
        UI32       i                       = 0;
        LocationId newLocationId1          = 0;
        string     ipAddress1              = "";
        SI32       port1                   = 0;
        UI32       numberOfFailures        = 0;

        for (i = 0; i < numberOfNewIpAddresses; i++)
        {
            ipAddress1     = pWaveCreateClusterWithNodesMessage->getNodeAt ((UI32) i);
            port1          = pWaveCreateClusterWithNodesMessage->getNodePortAt ((UI32) i);
            newLocationId1 = FrameworkToolKit::getLocationIdForIpAddressAndPort (ipAddress1, port1);

            if (true != (pWaveCreateClusterWithNodesMessage->isNewNodeStatusSet (ipAddress1, port1)))
            {
                pWaveCreateClusterWithNodesMessage->setNewNodeStatus (ipAddress1, port1, FRAMEWORK_ERROR_CREATE_CLUSTER_CONFIGURE_SECONDARY_TIMED_OUT);

                if (0 != newLocationId1)
                {
                    removeKnownLocation (newLocationId1);
                }

                numberOfFailures++;
            }
            else
            {
                if (WAVE_MESSAGE_SUCCESS != (pWaveCreateClusterWithNodesMessage->getNewNodeStatus (ipAddress1, port1)))
                {
                    numberOfFailures++;
                }
            }
        }

        if (numberOfFailures == numberOfNewIpAddresses)
        {
            resumeDatabaseOperation ();
            
            pCreateClusterWithNodesContext->executeNextStep (FRAMEWORK_ERROR_FAILED_TO_CONFIGURE_ALL_NEW_LOCATIONS);
        }
        else
        {
            m_pThisLocation->setLocationRole (LOCATION_PRIMARY);
            pCreateClusterWithNodesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        }
    }
}

void WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase1Step (CreateClusterWithNodesContext *pCreateClusterWithNodesContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase1Step : Starting ...");

    WaveCreateClusterWithNodesMessage *pWaveCreateClusterWithNodesMessage = reinterpret_cast<WaveCreateClusterWithNodesMessage *> (pCreateClusterWithNodesContext->getPWaveMessage ());

    waveAssert (NULL != pWaveCreateClusterWithNodesMessage, __FILE__, __LINE__);

    UI32                                i                                   = 0;
    UI32                                numberOfNewIpAddresses              = pWaveCreateClusterWithNodesMessage->getNumberOfNewNodes ();
    LocationId                          newLocationId1                      = 0;
    string                              ipAddress1                          = "";     SI32                                port1                               = 0;
    UI32                                numberOfFailures                    = 0;
    SI32                                sizeOfBackupFile                    = 0;
    char                               *pDatabaseBackupBuffer               = NULL;
    vector<string>                      filenamesToSync;
    ResourceId                          status                              = WAVE_MESSAGE_SUCCESS;
    bool                                fileSyncRequired                    = false;
    
    ++(*pCreateClusterWithNodesContext);


    pWaveCreateClusterWithNodesMessage->getFilenamesToSync ( filenamesToSync );    
    
    if ( filenamesToSync.size() == numberOfNewIpAddresses )
    {
        fileSyncRequired = true ;
    }     
        
    createDatabaseBackupBuffer(pDatabaseBackupBuffer, sizeOfBackupFile);
    
    for (i = 0; i < numberOfNewIpAddresses; i++)
    {
        ipAddress1     = pWaveCreateClusterWithNodesMessage->getNodeAt ((UI32) i);
        port1          = pWaveCreateClusterWithNodesMessage->getNodePortAt ((UI32) i);
        newLocationId1 = FrameworkToolKit::getLocationIdForIpAddressAndPort (ipAddress1, port1);

        // We will send configure phase1 message only to the locations that are known to us at this point.
        // Only to those locations that are succeeded as part of phase 0.
        // If user supplied a bogus ipaddress, we would have timed out trying to add that location in the prior steps
        // and hence that location will not be known to us at this time.

        if (WAVE_MESSAGE_SUCCESS == (pWaveCreateClusterWithNodesMessage->getNewNodeStatus (ipAddress1, port1)))
        {
            WaveConfigureClusterSecondaryPhase1Message *pMessage = new WaveConfigureClusterSecondaryPhase1Message ();

            if (NULL != pDatabaseBackupBuffer)
            {
                pMessage->addBuffer (pMessage->getDatabaseBackupBufferTag (), sizeOfBackupFile, pDatabaseBackupBuffer, false);
            }
            else
            {
                trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase1Step : No Database Backup is being sent to the lcoation.");
            }
   
            if ( (true == fileSyncRequired) && (false == filenamesToSync[i].empty()) )
            {    
                char *pfileBuffer = NULL ;
                UI32  sizeOfFileBuffer;

                trace (TRACE_LEVEL_DEVEL, string("WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase1Step : Adding file buffers. FileNum - ") + i );
                //using tag starting from 11 for now.        
                status = createBufferForFileToSync ( filenamesToSync[i], pfileBuffer, sizeOfFileBuffer );
                if ( WAVE_MESSAGE_SUCCESS != status )
                {
                    trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase1Step : Unable to create buffer for file = \"") + filenamesToSync[i] + ("\"") );
                    waveAssert ( false, __FILE__, __LINE__ );
                }                        

                pMessage->addBuffer ( 11, sizeOfFileBuffer, pfileBuffer, false );
                pMessage->setFilenameToSync ( filenamesToSync[i] );
                delete[] (pfileBuffer);
                pfileBuffer = NULL;
            }

            status = send (pMessage, reinterpret_cast<WaveMessageResponseHandler> (&WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase1Callback), pCreateClusterWithNodesContext, s_clusterPhase1TimeoutInMilliseconds, newLocationId1);

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                removeKnownLocation (newLocationId1);
                pWaveCreateClusterWithNodesMessage->updateNewNodeStatus (ipAddress1, port1, status);
                trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase1Step : Not able to configure one secondary location During Phase 2: ") + newLocationId1 + string (" Status : ") + FrameworkToolKit::localize (status));
                numberOfFailures++;

                delete pMessage;
            }
            else
            {
                pWaveCreateClusterWithNodesMessage->updateNewNodeStatus (ipAddress1, port1, FRAMEWORK_ERROR_CREATE_CLUSTER_CONFIGURE_SECONDARY_PHASE1_UNKNOWN);
                ++(*pCreateClusterWithNodesContext);
            }
        }
        else
        {
            numberOfFailures++;
        }
    }

    --(*pCreateClusterWithNodesContext);

    if (NULL != pDatabaseBackupBuffer)
    {
        delete[] pDatabaseBackupBuffer;
    }

    if ( numberOfFailures == numberOfNewIpAddresses )
    {
        trace (TRACE_LEVEL_ERROR, string("WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase1Step : , numberOfFailures - ") + numberOfFailures );
        resumeDatabaseOperation ();
        
        if (true == pCreateClusterWithNodesContext->getIsCreateClusterContext ())
        {
           m_pThisLocation->setLocationRole (LOCATION_STAND_ALONE);        
        }

        pCreateClusterWithNodesContext->executeNextStep (FRAMEWORK_ERROR_FAILED_TO_CONFIGURE_ALL_NEW_LOCATIONS);
    }
    else
    {
        pCreateClusterWithNodesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
}


void WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase1Callback (FrameworkStatus frameworkStatus, WaveConfigureClusterSecondaryPhase1Message *pWaveConfigureClusterSecondaryPhase1Message, void *pContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase1Callback : Starting ...");

    CreateClusterWithNodesContext      *pCreateClusterWithNodesContext      = reinterpret_cast<CreateClusterWithNodesContext *> (pContext);
    WaveCreateClusterWithNodesMessage *pWaveCreateClusterWithNodesMessage = reinterpret_cast<WaveCreateClusterWithNodesMessage *> (pCreateClusterWithNodesContext->getPWaveMessage ());
    LocationId                          newLocationId;
    string                              ipAddress;
    SI32                                port;

    --(*pCreateClusterWithNodesContext); 

    if (FRAMEWORK_SUCCESS == frameworkStatus)
    {
        waveAssert (NULL != pWaveConfigureClusterSecondaryPhase1Message, __FILE__, __LINE__);

        newLocationId = pWaveConfigureClusterSecondaryPhase1Message->getReceiverLocationId ();
        ipAddress     = FrameworkToolKit::getIpAddressForLocationId (newLocationId);
        port          = FrameworkToolKit::getPortForLocationId (newLocationId);

        ResourceId completionStatus = pWaveConfigureClusterSecondaryPhase1Message->getCompletionStatus ();

        pWaveCreateClusterWithNodesMessage->updateNewNodeStatus (ipAddress, port, completionStatus);

        if (WAVE_MESSAGE_SUCCESS != completionStatus)
        {
            trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase1Callback : Case 1 - Configuring ") + ipAddress + " failed : " + completionStatus);
            removeKnownLocation (newLocationId);
        }
    }
    else
    {
        if (NULL != pWaveConfigureClusterSecondaryPhase1Message)
        {
            LocationId newLocationId1 = pWaveConfigureClusterSecondaryPhase1Message->getReceiverLocationId ();
            string     ipAddress1     = FrameworkToolKit::getIpAddressForLocationId (newLocationId1);
            SI32       port1          = FrameworkToolKit::getPortForLocationId (newLocationId1);

            pWaveCreateClusterWithNodesMessage->updateNewNodeStatus (ipAddress1, port1, frameworkStatus);

            trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase1Callback : Case 2 - Configuring ") + ipAddress + " failed : " + frameworkStatus);
            removeKnownLocation (newLocationId1);
        }
    }

    if (NULL != pWaveConfigureClusterSecondaryPhase1Message)
    {
        delete pWaveConfigureClusterSecondaryPhase1Message;
    }

    if (0 == (pCreateClusterWithNodesContext->getNumberOfCallbacksBeforeAdvancingToNextStep ()))
    {
        UI32       numberOfNewIpAddresses  = pWaveCreateClusterWithNodesMessage->getNumberOfNewNodes ();
        UI32       i                       = 0;
        LocationId newLocationId1          = 0;
        string     ipAddress1              = "";
        SI32       port1                   = 0;
        UI32       numberOfFailures        = 0;

        for (i = 0; i < numberOfNewIpAddresses; i++)
        {
            ipAddress1     = pWaveCreateClusterWithNodesMessage->getNodeAt ((UI32) i);
            port1          = pWaveCreateClusterWithNodesMessage->getNodePortAt ((UI32) i);
            newLocationId1 = FrameworkToolKit::getLocationIdForIpAddressAndPort (ipAddress1, port1);

            if (FRAMEWORK_ERROR_CREATE_CLUSTER_CONFIGURE_SECONDARY_PHASE1_UNKNOWN == (pWaveCreateClusterWithNodesMessage->getNewNodeStatus (ipAddress1, port1)))
            {
                pWaveCreateClusterWithNodesMessage->updateNewNodeStatus (ipAddress1, port1, FRAMEWORK_ERROR_CREATE_CLUSTER_CONFIGURE_SECONDARY_PHASE1_TIMED_OUT);

                if (0 != newLocationId1)
                {
                    trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase1Callback : Case 3 - Configuring ") + ipAddress + " Timeout ");
                    removeKnownLocation (newLocationId1);
                }

                numberOfFailures++;
            }
            else
            {
                if (WAVE_MESSAGE_SUCCESS != (pWaveCreateClusterWithNodesMessage->getNewNodeStatus (ipAddress1, port1)))
                {
                    numberOfFailures++;
                }
            }
        }

        if (numberOfFailures == numberOfNewIpAddresses)
        {
            resumeDatabaseOperation ();
            
            if (true == pCreateClusterWithNodesContext->getIsCreateClusterContext ())
            {
               m_pThisLocation->setLocationRole (LOCATION_STAND_ALONE);
            }

            pCreateClusterWithNodesContext->executeNextStep (FRAMEWORK_ERROR_FAILED_TO_CONFIGURE_ALL_NEW_LOCATIONS);
        }
        else
        {
            pCreateClusterWithNodesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        }
    }       
}

void WaveFrameworkObjectManager::resumeDatabase ()
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::resumeDatabase : Starting ...");

    WaveResumeObjectManagerMessage message (DatabaseObjectManager::getWaveServiceId ());
    ResourceId                      status  = sendSynchronously (&message);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::resumeDatabase : Could not resume Database.  Status : " + FrameworkToolKit::localize (status));
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        status = message.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::resumeDatabase : Could not resume Database.  Completion Status : " + FrameworkToolKit::localize (status));
            waveAssert (false, __FILE__, __LINE__);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::resumeDatabase : Successfully resumed Database.");
        }
    }
}

void WaveFrameworkObjectManager::pausePersistence ()
{

    CliBlockManagementToolKit::lock ();

    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::pausePersistence : Starting ...");

    WavePauseObjectManagerMessage message (PersistenceObjectManager::getWaveServiceId ());
    ResourceId                      status  = sendSynchronously (&message);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::pausePersistence : Could not pause Persistence.  Status : " + FrameworkToolKit::localize (status));
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        status = message.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::pausePersistence : Could not pause Persistence.  Completion Status : " + FrameworkToolKit::localize (status));            
            waveAssert (false, __FILE__, __LINE__);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::pausePersistence : Successfully paused Persistence.");
        }
    }
}

void WaveFrameworkObjectManager::resumePersistence ()
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::resumePersistence : Starting ...");

    WaveResumeObjectManagerMessage message (PersistenceObjectManager::getWaveServiceId ());
    ResourceId                      status  = sendSynchronously (&message);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::resumePersistence : Could not resume Persistence.  Status : " + FrameworkToolKit::localize (status));
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        status = message.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::resumePersistence : Could not resume Persistence.  Completion Status : " + FrameworkToolKit::localize (status));
            waveAssert (false, __FILE__, __LINE__);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::resumePersistence : Successfully resumed Persistence.");
        }
    }

    CliBlockManagementToolKit::unlock ();
}

void WaveFrameworkObjectManager::resumeDatabaseOperation ()
{
    resumeDatabase ();
    resumePersistence ();
}

void WaveFrameworkObjectManager::createClusterWithNodesResumeDatabaseStep (CreateClusterWithNodesContext *pCreateClusterWithNodesContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::createClusterWithNodesResumeDatabaseStep : Starting ...");

    resumeDatabaseOperation ();
    
    pCreateClusterWithNodesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase2Step (CreateClusterWithNodesContext *pCreateClusterWithNodesContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase2Step : Starting ...");

    WaveCreateClusterWithNodesMessage *pWaveCreateClusterWithNodesMessage = reinterpret_cast<WaveCreateClusterWithNodesMessage *> (pCreateClusterWithNodesContext->getPWaveMessage ());

    waveAssert (NULL != pWaveCreateClusterWithNodesMessage, __FILE__, __LINE__);

    UI32                                i                                   = 0;
    UI32                                numberOfNewIpAddresses              = pWaveCreateClusterWithNodesMessage->getNumberOfNewNodes ();
    LocationId                          newLocationId1                      = 0;
    string                              ipAddress1                          = "";
    SI32                                port1                               = 0;
    UI32                                numberOfFailures                    = 0;
    UI32                                numberOfNewLocationIds              = pCreateClusterWithNodesContext->getNumberOfNewLocationIds ();

    ++(*pCreateClusterWithNodesContext);

    for (i = 0; i < numberOfNewIpAddresses; i++)
    {
        ipAddress1     = pWaveCreateClusterWithNodesMessage->getNodeAt ((UI32) i);
        port1          = pWaveCreateClusterWithNodesMessage->getNodePortAt ((UI32) i);
        newLocationId1 = FrameworkToolKit::getLocationIdForIpAddressAndPort (ipAddress1, port1);

        // We will send configure phase2 message only to the locations that are known to us at this point.
        // Only to those locations that are succeeded as part of phase 1.
        // If user supplied a bogus ipaddress, we would have timed out trying to add that location in the prior steps
        // and hence that location will not be known to us at this time.

        if (WAVE_MESSAGE_SUCCESS == (pWaveCreateClusterWithNodesMessage->getNewNodeStatus (ipAddress1, port1)))
        {
            WaveConfigureClusterSecondaryPhase2Message *pMessage = new WaveConfigureClusterSecondaryPhase2Message ();

            WaveMessageStatus status = send (pMessage, reinterpret_cast<WaveMessageResponseHandler> (&WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase2Callback), pCreateClusterWithNodesContext, 120000, newLocationId1);

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                removeKnownLocation (newLocationId1);
                pWaveCreateClusterWithNodesMessage->updateNewNodeStatus (ipAddress1, port1, status);
                trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase2Step : Not able to configure one secondary location During Phase 2: ") + newLocationId1 + string (" Status : ") + FrameworkToolKit::localize (status));
                numberOfFailures++;

                delete pMessage;
            }
            else
            {
                pWaveCreateClusterWithNodesMessage->updateNewNodeStatus (ipAddress1, port1, FRAMEWORK_ERROR_CREATE_CLUSTER_CONFIGURE_SECONDARY_PHASE2_UNKNOWN);

                ++(*pCreateClusterWithNodesContext);
            }
        }
        else
        {
            numberOfFailures++;
        }
    }

    --(*pCreateClusterWithNodesContext);

    if (numberOfFailures == numberOfNewLocationIds)
    {
//        resumeDatabaseOperation ();               already done successfully as last step.

        if (true == pCreateClusterWithNodesContext->getIsCreateClusterContext ())
        {
           m_pThisLocation->setLocationRole (LOCATION_STAND_ALONE);
        }


        pCreateClusterWithNodesContext->executeNextStep (FRAMEWORK_ERROR_FAILED_TO_CONFIGURE_ALL_NEW_LOCATIONS);
    }
    else
    {
        pCreateClusterWithNodesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
}

void WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase2Callback (FrameworkStatus frameworkStatus, WaveConfigureClusterSecondaryPhase2Message *pWaveConfigureClusterSecondaryPhase2Message, void *pContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase2Callback : Starting ...");

    CreateClusterWithNodesContext      *pCreateClusterWithNodesContext      = reinterpret_cast<CreateClusterWithNodesContext *> (pContext);
    WaveCreateClusterWithNodesMessage *pWaveCreateClusterWithNodesMessage = reinterpret_cast<WaveCreateClusterWithNodesMessage *> (pCreateClusterWithNodesContext->getPWaveMessage ());
    LocationId                          newLocationId;
    string                              ipAddress;
    SI32                                port;

    --(*pCreateClusterWithNodesContext);

    if (FRAMEWORK_SUCCESS == frameworkStatus)
    {
        waveAssert (NULL != pWaveConfigureClusterSecondaryPhase2Message, __FILE__, __LINE__);

        newLocationId = pWaveConfigureClusterSecondaryPhase2Message->getReceiverLocationId ();
        ipAddress     = FrameworkToolKit::getIpAddressForLocationId (newLocationId);
        port          = FrameworkToolKit::getPortForLocationId (newLocationId);

        ResourceId completionStatus = pWaveConfigureClusterSecondaryPhase2Message->getCompletionStatus ();

        pWaveCreateClusterWithNodesMessage->updateNewNodeStatus (ipAddress, port, completionStatus);

        if (WAVE_MESSAGE_SUCCESS != completionStatus)
        {
            trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase2Callback : Case 1 - Configuring ") + ipAddress + " failed : " + completionStatus);

            disconnectFromLocation (newLocationId);
            removeKnownLocation (newLocationId);

            pCreateClusterWithNodesContext->addToFailedLocationIdVector (newLocationId);
        }
    }
    else
    {
        if (NULL != pWaveConfigureClusterSecondaryPhase2Message)
        {
            LocationId newLocationId1 = pWaveConfigureClusterSecondaryPhase2Message->getReceiverLocationId ();
            string     ipAddress1     = FrameworkToolKit::getIpAddressForLocationId (newLocationId1);
            SI32       port1          = FrameworkToolKit::getPortForLocationId (newLocationId1);

            pWaveCreateClusterWithNodesMessage->updateNewNodeStatus (ipAddress1, port1, frameworkStatus);

            trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase2Callback : Case 2 - Configuring ") + ipAddress + " failed : " + frameworkStatus);

            disconnectFromLocation (newLocationId1);
            removeKnownLocation (newLocationId1);

            pCreateClusterWithNodesContext->addToFailedLocationIdVector (newLocationId1);
        }
    }

    if (NULL != pWaveConfigureClusterSecondaryPhase2Message)
    {
        delete pWaveConfigureClusterSecondaryPhase2Message;
    }

    if (0 == (pCreateClusterWithNodesContext->getNumberOfCallbacksBeforeAdvancingToNextStep ()))
    {
        UI32       numberOfNewIpAddresses  = pWaveCreateClusterWithNodesMessage->getNumberOfNewNodes ();
        UI32       i                       = 0;
        LocationId newLocationId1          = 0;
        string     ipAddress1              = "";
        SI32       port1                   = 0;
        UI32       numberOfFailures        = 0;

        for (i = 0; i < numberOfNewIpAddresses; i++)
        {
            ipAddress1     = pWaveCreateClusterWithNodesMessage->getNodeAt ((UI32) i);
            port1          = pWaveCreateClusterWithNodesMessage->getNodePortAt ((UI32) i);
            newLocationId1 = FrameworkToolKit::getLocationIdForIpAddressAndPort (ipAddress1, port1);

            if (FRAMEWORK_ERROR_CREATE_CLUSTER_CONFIGURE_SECONDARY_PHASE2_UNKNOWN == (pWaveCreateClusterWithNodesMessage->getNewNodeStatus (ipAddress1, port1)))
            {
                pWaveCreateClusterWithNodesMessage->updateNewNodeStatus (ipAddress1, port1, FRAMEWORK_ERROR_CREATE_CLUSTER_CONFIGURE_SECONDARY_PHASE2_TIMED_OUT);

                if (0 != newLocationId1)
                {
                    trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase2Callback : Case 3 - Configuring ") + ipAddress + " Timeout ");

                    disconnectFromLocation (newLocationId1);
                    removeKnownLocation (newLocationId1);

                    pCreateClusterWithNodesContext->addToFailedLocationIdVector (newLocationId1);
                }

                numberOfFailures++;
            }
            else
            {
                if (WAVE_MESSAGE_SUCCESS != (pWaveCreateClusterWithNodesMessage->getNewNodeStatus (ipAddress1, port1)))
                {
                    numberOfFailures++;
                }
            }

            if (WAVE_MESSAGE_SUCCESS == pWaveCreateClusterWithNodesMessage->getNewNodeStatus (ipAddress1, port1))
            {
                pCreateClusterWithNodesContext->addToSuccessfullyAddedLocationIdVector (newLocationId1);
            }
        }

        if (numberOfFailures == numberOfNewIpAddresses)
        {
            if (true == pCreateClusterWithNodesContext->getIsCreateClusterContext ())
            {
               m_pThisLocation->setLocationRole (LOCATION_STAND_ALONE);
            }

            vector<LocationId> failedLocationIdsVector            = pCreateClusterWithNodesContext->getFailedLocationIdVector ();
            UI32               numberOffailedLocationIdsVector    = failedLocationIdsVector.size ();

            if (0 < numberOffailedLocationIdsVector)
            {

                WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext = new WaveFrameworkFailoverWorkerContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveFrameworkObjectManager::failoverforNodesFailedInPhase2Callback), pCreateClusterWithNodesContext);

                for (UI32 k = 0; k < numberOffailedLocationIdsVector; k++)
                {
                    pWaveFrameworkFailoverWorkerContext->addFailedLocationId (failedLocationIdsVector[k]);
                }

                pWaveFrameworkFailoverWorkerContext->setThisLocationRole (LOCATION_PRIMARY);
                pWaveFrameworkFailoverWorkerContext->setFailoverReason (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_CONTROLLED);

                tracePrintf (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::Phase 2 Call Back Invoking failover for %u nodes", numberOffailedLocationIdsVector);

                m_pWaveFrameworkFailoverWorker->executeFailover (pWaveFrameworkFailoverWorkerContext);
            }
        }
        else
        {
            m_pThisLocation->setLocationRole (LOCATION_PRIMARY);

            pCreateClusterWithNodesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        }
    }
}

void WaveFrameworkObjectManager::failoverforNodesFailedInPhase2 (CreateClusterWithNodesContext *pCreateClusterWithNodesContext)
{
    vector<LocationId> failedLocationIdsVector            = pCreateClusterWithNodesContext->getFailedLocationIdVector ();
    UI32               numberOffailedLocationIdsVector    = failedLocationIdsVector.size ();

    if (0 < numberOffailedLocationIdsVector)
    {
        WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext = new WaveFrameworkFailoverWorkerContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveFrameworkObjectManager::failoverforNodesFailedInPhase2Callback), pCreateClusterWithNodesContext);

        for (UI32 k = 0; k < numberOffailedLocationIdsVector; k++)
        {
            pWaveFrameworkFailoverWorkerContext->addFailedLocationId (failedLocationIdsVector[k]);
        }

        pWaveFrameworkFailoverWorkerContext->setThisLocationRole (LOCATION_PRIMARY);
        pWaveFrameworkFailoverWorkerContext->setFailoverReason (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_CONTROLLED);

        tracePrintf (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::failoverforNodesFailedInPhase2 Invoking failover for %u nodes", numberOffailedLocationIdsVector);

        m_pWaveFrameworkFailoverWorker->executeFailover (pWaveFrameworkFailoverWorkerContext);
    }
    else
    {
        pCreateClusterWithNodesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }

}

void WaveFrameworkObjectManager::failoverforNodesFailedInPhase2Callback (WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::failoverforNodesFailedInPhase2Callback : Entering ...");

    waveAssert (NULL != pWaveFrameworkFailoverWorkerContext, __FILE__, __LINE__);

    CreateClusterWithNodesContext  *pCreateClusterWithNodesContext = reinterpret_cast<CreateClusterWithNodesContext *> (pWaveFrameworkFailoverWorkerContext->getPCallerContext ());

    delete pWaveFrameworkFailoverWorkerContext;

    waveAssert (NULL != pCreateClusterWithNodesContext, __FILE__, __LINE__);

    //clear the failed location vector setup in previous phases as failover is triggered for those locations.
    pCreateClusterWithNodesContext->clearFailedLocationIdVector ();

    vector<LocationId>      successfullyAddedLocationIdVector = pCreateClusterWithNodesContext->getSuccessfullyAddedLocationIdVector ();
                 UI32       numberOfSuccessfullyAddedNode     = successfullyAddedLocationIdVector.size ();

    if (0 == numberOfSuccessfullyAddedNode)
    {
        if (true == pCreateClusterWithNodesContext->getIsCreateClusterContext ())
        {
            m_pThisLocation->setLocationRole (LOCATION_STAND_ALONE);

            saveConfiguration (true);
        }

        pCreateClusterWithNodesContext->executeNextStep (FRAMEWORK_ERROR_FAILED_TO_CONFIGURE_ALL_NEW_LOCATIONS);
    }
    else 
    { 
        pCreateClusterWithNodesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }


}

/*
Name: startHeartBeatToSecondaryNodes
Description: Start HeartBeat from Primary to Secondary Node After Phase 2 completes
@param1 CreateClusterWithNodesContext: This is the base class context. This function is called from Create Cluster, Add Node, Rejoin with respective Context.

*/
void WaveFrameworkObjectManager::startHeartBeatToSecondaryNodes (CreateClusterWithNodesContext *pCreateClusterWithNodesContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::startHeartBeatToSecondaryNodes Entring");

    vector<LocationId>  successfullyAddedLocationIdVector = pCreateClusterWithNodesContext->getSuccessfullyAddedLocationIdVector ();
    UI32                numberOfSuccessfullyAddedNode     = successfullyAddedLocationIdVector.size ();
    LocationId          locationId;
    string              ipAddress;
    SI32                port;
    ResourceId          status                            = WAVE_MESSAGE_SUCCESS;

    for (UI32 i = 0; i < numberOfSuccessfullyAddedNode; i++)
    {
        locationId = successfullyAddedLocationIdVector[i];

        if (true == pCreateClusterWithNodesContext->isAFailedLocation (locationId))
        {
            continue;
        }

        ipAddress  = FrameworkToolKit::getIpAddressForLocationId (locationId);
        port       = FrameworkToolKit::getPortForLocationId (locationId);

        StartHeartBeatMessage *pMessage = new StartHeartBeatMessage ();

        pMessage->setDstIpAddress               (ipAddress);
        pMessage->setDstPortNumber              (port);
        pMessage->setHeartBeatInterval          (DEFAULT_HEART_BEAT_PERIOD);
        pMessage->setHeartBeatFailureThreshold  (DEFAULT_MAX_LOST_HEARTBEATS);

        status = sendSynchronously (pMessage);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveFrameworkObjectManager::startHeartBeatToSecondaryNodes: Could not start heart beating with Node : ") + ipAddress + string (", Port : ") + port + string (", Status = ") + FrameworkToolKit::localize (status));

            waveAssert (false, __FILE__, __LINE__);
        }
        else
        {
            status = pMessage->getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveFrameworkObjectManager::startHeartBeatToSecondaryNodes : Could not start heart beating with Node : ") + ipAddress + string (", Port : ") + port + string (", Completion Status = ") + FrameworkToolKit::localize (status));
                waveAssert (false, __FILE__, __LINE__);
            }

            trace (TRACE_LEVEL_INFO, string ("Started HeartBeat with node ") + ipAddress + string (":") + port);
        }

        delete pMessage;
    }

    pCreateClusterWithNodesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase3Step (CreateClusterWithNodesContext *pCreateClusterWithNodesContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase3Step : Starting ...");

    WaveCreateClusterWithNodesMessage *pWaveCreateClusterWithNodesMessage = reinterpret_cast<WaveCreateClusterWithNodesMessage *> (pCreateClusterWithNodesContext->getPWaveMessage ());
    vector<LocationId>                  successfullyAddedLocationIdVector   = pCreateClusterWithNodesContext->getSuccessfullyAddedLocationIdVector ();
                 UI32                   numberOfSuccessfullyAddedNode       = successfullyAddedLocationIdVector.size ();
                 UI32                   numberOfFailures                    = 0;
           LocationId                   locationId;    

    ++(*pCreateClusterWithNodesContext);

    for (UI32 i = 0; i < numberOfSuccessfullyAddedNode; i++)
    {

        locationId = successfullyAddedLocationIdVector[i];

        WaveConfigureClusterSecondaryPhase3Message *pWaveConfigureClusterSecondaryPhase3Message = new WaveConfigureClusterSecondaryPhase3Message ();

        WaveMessageStatus status = send (pWaveConfigureClusterSecondaryPhase3Message, reinterpret_cast<WaveMessageResponseHandler> (&WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase3Callback), pCreateClusterWithNodesContext, 0, locationId);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            if (NULL != pWaveCreateClusterWithNodesMessage)
            {
                pWaveCreateClusterWithNodesMessage->updateNewNodeStatus (FrameworkToolKit::getIpAddressForLocationId (locationId), FrameworkToolKit::getPortForLocationId (locationId), status);
            }

            disconnectFromLocation (locationId);
            removeKnownLocation (locationId);

            pCreateClusterWithNodesContext->addToFailedLocationIdVector (locationId);

            trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase3Step : Not able to configure one secondary location During Phase 3: ") + locationId + string (" Status : ") + FrameworkToolKit::localize (status));

            numberOfFailures++;

            delete (pWaveConfigureClusterSecondaryPhase3Message);
        }
        else
        {
            ++(*pCreateClusterWithNodesContext);
        }
    }

    --(*pCreateClusterWithNodesContext);

    // Replay the local-only configuration file on principal node only in the case of a cluster transition.

    string configFilePath           = ConfigFileManagementToolKit::getConfigFileManagementScriptsDirectory ();
    string configFilename           = ConfigFileManagementToolKit::getConfigFileManagementLocalOnlyFilename ();
    string fullConfigFilename       = configFilePath + "/" + configFilename;
    string preConfigReplayCommands  = "bypassCliValidations cluster-formation";

    if (true == ConfigFileManagementToolKit::isFileExisting (fullConfigFilename))
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase3Step : Replay local-only config file on principal node...");

        ResourceId status = ConfigFileManagementToolKit::replayConfigurationFile (configFilePath, configFilename, preConfigReplayCommands);

        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase3Step : Replay of local-only config file on principal node completed with status: " + FrameworkToolKit::localize (status));

        if (WAVE_MESSAGE_SUCCESS ==  status)
        {
            string newConfigFilename = fullConfigFilename + "." + FrameworkToolKit::getThisLocationIpAddress () + ".backup";

            ConfigFileManagementToolKit::renameConfigurationFile (fullConfigFilename, newConfigFilename);
        }
    }
    else
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase3Step : Skipping this step. " + fullConfigFilename + " does not exist.");
    }

    // Do failover if all nodes failed to be added in phase3.

    if (numberOfFailures == numberOfSuccessfullyAddedNode)
    {
        vector<LocationId> failedLocationIdsVectorInPhase3                   = pCreateClusterWithNodesContext->getFailedLocationIdVector ();
                      UI32 numberOffailedLocationIdsVectorInPhase3           = failedLocationIdsVectorInPhase3.size ();

            WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext = new WaveFrameworkFailoverWorkerContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveFrameworkObjectManager::failoverforNodesFailedInPhase3Callback), pCreateClusterWithNodesContext);

            for (UI32 j = 0; j < numberOffailedLocationIdsVectorInPhase3; j++)
            {
                pWaveFrameworkFailoverWorkerContext->addFailedLocationId (failedLocationIdsVectorInPhase3[j]);
            }

            pWaveFrameworkFailoverWorkerContext->setThisLocationRole (LOCATION_PRIMARY);
            pWaveFrameworkFailoverWorkerContext->setFailoverReason (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_CONTROLLED);

            tracePrintf (TRACE_LEVEL_INFO, "Invoking failover for %u nodes", numberOffailedLocationIdsVectorInPhase3);

            m_pWaveFrameworkFailoverWorker->executeFailover (pWaveFrameworkFailoverWorkerContext);
    }
    else
    {
        pCreateClusterWithNodesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
}

void WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase3Callback (FrameworkStatus frameworkStatus, WaveConfigureClusterSecondaryPhase3Message *pWaveConfigureClusterSecondaryPhase3Message, void *pContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase3Callback : Starting ...");

    CreateClusterWithNodesContext      *pCreateClusterWithNodesContext      = reinterpret_cast<CreateClusterWithNodesContext *> (pContext);
    WaveCreateClusterWithNodesMessage *pWaveCreateClusterWithNodesMessage = reinterpret_cast<WaveCreateClusterWithNodesMessage *> (pCreateClusterWithNodesContext->getPWaveMessage ());

    waveAssert (NULL != pWaveConfigureClusterSecondaryPhase3Message, __FILE__, __LINE__);
 
    LocationId locationId = pWaveConfigureClusterSecondaryPhase3Message->getReceiverLocationId ();
    
    --(*pCreateClusterWithNodesContext);

    if (FRAMEWORK_SUCCESS == frameworkStatus)
    {
        ResourceId completionStatus = pWaveConfigureClusterSecondaryPhase3Message->getCompletionStatus ();

        if (NULL != pWaveCreateClusterWithNodesMessage)
        {
            pWaveCreateClusterWithNodesMessage->updateNewNodeStatus (FrameworkToolKit::getIpAddressForLocationId (locationId), FrameworkToolKit::getPortForLocationId (locationId), completionStatus);
        }

        if (WAVE_MESSAGE_SUCCESS != completionStatus)
        {
            trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase3Callback : Failed to configure Location Id ") + locationId + " status : " + completionStatus);
            disconnectFromLocation (locationId);
            removeKnownLocation (locationId);

            pCreateClusterWithNodesContext->addToFailedLocationIdVector (locationId);
        }
    }
    else
    {
         trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase3Callback : Failed to configure Location Id ") + locationId + " status : " + frameworkStatus);

        if (NULL != pWaveCreateClusterWithNodesMessage)
        {
            pWaveCreateClusterWithNodesMessage->updateNewNodeStatus (FrameworkToolKit::getIpAddressForLocationId (locationId), FrameworkToolKit::getPortForLocationId (locationId), frameworkStatus);
        }

        disconnectFromLocation (locationId);
        removeKnownLocation (locationId);

        pCreateClusterWithNodesContext->addToFailedLocationIdVector (locationId);
    }

    if (0 == (pCreateClusterWithNodesContext->getNumberOfCallbacksBeforeAdvancingToNextStep ()))
    {
        vector<LocationId> failedLocationIdsVectorInPhase3                   = pCreateClusterWithNodesContext->getFailedLocationIdVector ();
                      UI32 numberOffailedLocationIdsVectorInPhase3           = failedLocationIdsVectorInPhase3.size ();
        
        if (false == pCreateClusterWithNodesContext->getIsCreateClusterContext ())
        {
            vector<WaveManagedObject *> *pResults = querySynchronously (WaveCluster::getClassName ());

            waveAssert (NULL != pResults, __FILE__, __LINE__);

            if (0 == pResults->size ())
            {
                if (NULL != pWaveConfigureClusterSecondaryPhase3Message)
                {
                    delete pWaveConfigureClusterSecondaryPhase3Message;
                }

                WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector(pResults);

                pCreateClusterWithNodesContext->executeNextStep (WAVE_MESSAGE_ERROR);
                return;
            }
            else
            {
                WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector(pResults);
            }
        }

        // check if any node is failed, then trigger failover for those nodes.
        if (0 < numberOffailedLocationIdsVectorInPhase3)
        {
            
            WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext = new WaveFrameworkFailoverWorkerContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveFrameworkObjectManager::failoverforNodesFailedInPhase3Callback), pCreateClusterWithNodesContext);

            for (UI32 j = 0; j < numberOffailedLocationIdsVectorInPhase3; j++)
            {
                pWaveFrameworkFailoverWorkerContext->addFailedLocationId (failedLocationIdsVectorInPhase3[j]);
            }

            pWaveFrameworkFailoverWorkerContext->setThisLocationRole (LOCATION_PRIMARY);
            pWaveFrameworkFailoverWorkerContext->setFailoverReason (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_CONTROLLED);

            tracePrintf (TRACE_LEVEL_INFO, "Invoking failover for %u nodes", numberOffailedLocationIdsVectorInPhase3);

            m_pWaveFrameworkFailoverWorker->executeFailover (pWaveFrameworkFailoverWorkerContext);
        }
        else
        {
            pCreateClusterWithNodesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        }
    }

    delete (pWaveConfigureClusterSecondaryPhase3Message);
}

void WaveFrameworkObjectManager::failoverforNodesFailedInPhase3Callback (WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::failoverforNodesFailedInPhase3Callback : Entering ...");

    waveAssert (NULL != pWaveFrameworkFailoverWorkerContext, __FILE__, __LINE__);

    CreateClusterWithNodesContext  *pCreateClusterWithNodesContext = reinterpret_cast<CreateClusterWithNodesContext *> (pWaveFrameworkFailoverWorkerContext->getPCallerContext ());
    vector<LocationId> failedLocationIds;
    vector<LocationId> connectedLocationsVector;

    FrameworkToolKit::getConnectedLocations (connectedLocationsVector);
    UI32 totalNodes = connectedLocationsVector.size ();

    pWaveFrameworkFailoverWorkerContext->getFailedLocationIds (failedLocationIds);

    for (UI32 i = 0; i < totalNodes; i++)
    {
        FrameworkObjectManagerRemoveKnownLocationsMessage *pFrameworkObjectManagerRemoveKnownLocationsMessage = new FrameworkObjectManagerRemoveKnownLocationsMessage ();

        
        pFrameworkObjectManagerRemoveKnownLocationsMessage->setFailedLocations (failedLocationIds);

        ResourceId status = sendOneWay (pFrameworkObjectManagerRemoveKnownLocationsMessage, connectedLocationsVector[i]);

        waveAssert (WAVE_MESSAGE_SUCCESS == status, __FILE__, __LINE__);
    }

    delete pWaveFrameworkFailoverWorkerContext;

    waveAssert (NULL != pCreateClusterWithNodesContext, __FILE__, __LINE__);

    pCreateClusterWithNodesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);

    
}

void WaveFrameworkObjectManager::setWarmHaRecoveryPreparationInProgress (const bool &isWarmRecovery)
{
    m_warmHaRecoveryPreparationInProgressMutex.lock ();
    m_isWarmHaRecoveryPreparationInProgress = isWarmRecovery;
    m_warmHaRecoveryPreparationInProgressMutex.unlock ();
}

bool WaveFrameworkObjectManager::isWarmHaRecoveryPreparationInProgress ()
{
    bool isWarmRecovery = false;

    m_warmHaRecoveryPreparationInProgressMutex.lock ();
    isWarmRecovery = m_isWarmHaRecoveryPreparationInProgress;
    m_warmHaRecoveryPreparationInProgressMutex.unlock ();

    return (isWarmRecovery);
}

void WaveFrameworkObjectManager::setActivationCompleted (bool isActivationCompleted)
{
    m_activationCompletedMutex.lock();
    m_activationCompleted = isActivationCompleted;
    generateTimeStamp (m_activationCompletedTimeStamp);
    m_activationCompletedMutex.unlock();
}

bool  WaveFrameworkObjectManager::getActivationCompleted ()
{
    m_activationCompletedMutex.lock();
    bool isActivationCompleted =  m_activationCompleted;
    m_activationCompletedMutex.unlock();
    return isActivationCompleted;
}

string WaveFrameworkObjectManager::getActivationCompletedTimeStamp()
{
    m_activationCompletedMutex.lock ();
    string activationCompletedTimeStamp = m_activationCompletedTimeStamp;
    m_activationCompletedMutex.unlock ();
    return activationCompletedTimeStamp;
}

void WaveFrameworkObjectManager::incrementLineCardPostBootCount ()
{
    m_lineCardPostBootMutex.lock ();

    m_numberOfLineCardPostBootInProgress++;

    m_lineCardPostBootMutex.unlock ();
}

UI32 WaveFrameworkObjectManager::getNumberOfLineCardPostBootCurrentlyRunning ()
{
    UI32 numberOfLineCardPostbootInProgress = 0;

    m_lineCardPostBootMutex.lock ();

    numberOfLineCardPostbootInProgress = m_numberOfLineCardPostBootInProgress;

    m_lineCardPostBootMutex.unlock ();

    return (numberOfLineCardPostbootInProgress);
}

void WaveFrameworkObjectManager::decrementLineCardPostBootCount ()
{
    m_lineCardPostBootMutex.lock ();

    if (m_numberOfLineCardPostBootInProgress)
    {
        m_numberOfLineCardPostBootInProgress--;
    }
    else
    {
        //Decrementing when there are no LC postboot in progress hence assert
        waveAssert (false, __FILE__, __LINE__);
    }

     m_lineCardPostBootMutex.unlock ();
}

void WaveFrameworkObjectManager::setPostBootStarted (bool isPostBootStarted)
{
    m_postBootProgressMutex.lock();
    m_postBootStarted = isPostBootStarted;
    generateTimeStamp(m_postBootStartedTimeStamp);
    m_postBootProgressMutex.unlock();
}

bool WaveFrameworkObjectManager::getPostBootStarted ()
{
    m_postBootProgressMutex.lock();
    bool isPostBootStarted = m_postBootStarted;
    m_postBootProgressMutex.unlock();
    return isPostBootStarted;
}

string WaveFrameworkObjectManager::getPostBootStartedTimeStamp()
{  
    m_postBootProgressMutex.lock ();
    string postBootStartedTimeStamp = m_postBootStartedTimeStamp;
    m_postBootProgressMutex.unlock ();
    return postBootStartedTimeStamp;
}

void WaveFrameworkObjectManager::setPostBootCompleted (bool isPostBootCompleted)
{
    m_postBootProgressMutex.lock();
    m_postBootCompleted = isPostBootCompleted;
    generateTimeStamp(m_postBootCompletedTimeStamp);
    m_postBootProgressMutex.unlock();
}

bool WaveFrameworkObjectManager::getPostBootCompleted() 
{
    m_postBootProgressMutex.lock();
    bool isPostBootCompleted = m_postBootCompleted;
    m_postBootProgressMutex.unlock();
    return isPostBootCompleted;
}

string WaveFrameworkObjectManager::getPostBootCompletedTimeStamp()
{  
    m_postBootProgressMutex.lock ();
    string postBootCompletedTimeStamp = m_postBootCompletedTimeStamp;
    m_postBootProgressMutex.unlock ();

    return postBootCompletedTimeStamp;
}

void  WaveFrameworkObjectManager::setFileReplayStarted (bool isFileReplayStarted)
{
    m_fileReplayInProgressMutex.lock ();
    
    m_fileReplayStarted = isFileReplayStarted;
    if (true == m_fileReplayStarted)
    {
        generateTimeStamp(m_fileReplayStartedTimeStamp);
    }
    else
    {
        m_fileReplayStartedTimeStamp = "";
    }

    m_fileReplayInProgressMutex.unlock ();
}

bool  WaveFrameworkObjectManager::getFileReplayStarted ()
{
 m_fileReplayInProgressMutex.lock ();
 bool isFileReplayStarted = m_fileReplayStarted;
 m_fileReplayInProgressMutex.unlock ();

 return isFileReplayStarted;
}
string WaveFrameworkObjectManager::getFileReplayStartedTimeStamp()
{  
    m_fileReplayInProgressMutex.lock ();
    string fileReplayStartedTimeStamp = m_fileReplayStartedTimeStamp;
    m_fileReplayInProgressMutex.unlock ();
    return fileReplayStartedTimeStamp;
}


void  WaveFrameworkObjectManager::setFileReplayCompleted (bool isFileReplayCompleted)
{
   m_fileReplayInProgressMutex.lock ();
   m_fileReplayCompleted = isFileReplayCompleted;
   if (true == m_fileReplayCompleted)
   {
       generateTimeStamp(m_fileReplayCompletedTimeStamp);
   }
   else
   {
       m_fileReplayCompletedTimeStamp = "";
   }

   m_fileReplayInProgressMutex.unlock ();
}

bool  WaveFrameworkObjectManager::getFileReplayCompleted ()
{
   m_fileReplayInProgressMutex.lock ();
   bool isFileReplayCompleted = m_fileReplayCompleted;
   m_fileReplayInProgressMutex.unlock ();
   return isFileReplayCompleted;
}

string WaveFrameworkObjectManager::getFileReplayCompletedTimeStamp()
{  
    m_fileReplayInProgressMutex.lock ();
    string fileReplayCompletedTimeStamp = m_fileReplayCompletedTimeStamp;
    m_fileReplayInProgressMutex.unlock ();
    return fileReplayCompletedTimeStamp;
}

bool WaveFrameworkObjectManager::getFileReplayInProgress()
{

  m_fileReplayInProgressMutex.lock();
  bool isFileReplayInProgress =  false;

  if(false == m_fileReplayCompleted &&  true == m_fileReplayStarted) 
  {
      isFileReplayInProgress = true;
  }

  m_fileReplayInProgressMutex.unlock();

  return isFileReplayInProgress;
}

void WaveFrameworkObjectManager::startFileReplayEndAgent ()
{
   // Call the File Replay End Agent. This is a synchronous call. Should this call be made from within the mutex lock ? Its not necessary since all the "copy file to running" commands are serialized from the top level. 

   /* Call the virtual function FileReplayEnd */
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::setFileReplayCompleted : Start the File Replay End Agent.... ");

    FileReplayEndAgent *pWaveFileReplayEnd = new FileReplayEndAgent (m_pWaveObjectManager);

    pWaveFileReplayEnd->execute ();

    delete pWaveFileReplayEnd;

    // Print the FileReplay Started and Ended timestamp 

    tracePrintf (TRACE_LEVEL_INFO, false, false, "WaveFrameworkObjectManager::setFileReplayCompleted : File Replay Started Timestamp : %s \n\n", getFileReplayStartedTimeStamp().c_str ());
    tracePrintf (TRACE_LEVEL_INFO, false, false, "WaveFrameworkObjectManager::setFileReplayCompleted : File Replay Completed Timestamp : %s \n\n", (getFileReplayCompletedTimeStamp ()).c_str ());

    // After calling the Agent, reset the values of fileReplayStarted and fileReplayCompleted

    setFileReplayStarted (false);
    setFileReplayCompleted (false);
}

void WaveFrameworkObjectManager::fileReplayCompletedProcessing (bool fileReplayCompleted)
{
    if (true == fileReplayCompleted)
    {
        setFileReplayCompleted (fileReplayCompleted);
        startFileReplayEndAgent ();
    }
    else
    {
        setFileReplayCompleted (fileReplayCompleted);
    }
}


void  WaveFrameworkObjectManager::setConfigReplayStarted (bool isConfigreplayStarted)
{
  m_configReplayInProgressMutex.lock ();
  m_configReplayStarted = isConfigreplayStarted;
  generateTimeStamp(m_configReplayStartedTimeStamp);
  m_configReplayInProgressMutex.unlock ();

}

bool  WaveFrameworkObjectManager::getConfigReplayStarted ()
{
 m_configReplayInProgressMutex.lock ();
 bool isConfigreplayStarted = m_configReplayStarted;
 m_configReplayInProgressMutex.unlock ();

 return isConfigreplayStarted;
}
string WaveFrameworkObjectManager::getConfigReplayStartedTimeStamp()
{  
    m_configReplayInProgressMutex.lock ();
    string configReplayStartedTimeStamp = m_configReplayStartedTimeStamp;
    m_configReplayInProgressMutex.unlock ();
    return configReplayStartedTimeStamp;
}


void  WaveFrameworkObjectManager::setConfigReplayCompleted (bool isConfigReplayCompleted)
{
   m_configReplayInProgressMutex.lock ();
   m_configReplayCompleted = isConfigReplayCompleted;
   generateTimeStamp(m_configReplayCompletedTimeStamp);
   m_configReplayInProgressMutex.unlock ();
}
bool  WaveFrameworkObjectManager::getConfigReplayCompleted ()
{
   m_configReplayInProgressMutex.lock ();
   bool isConfigReplayCompleted = m_configReplayCompleted;
   m_configReplayInProgressMutex.unlock ();
   return isConfigReplayCompleted;
}

string WaveFrameworkObjectManager::getConfigReplayCompletedTimeStamp()
{  
    m_configReplayInProgressMutex.lock ();
    string configReplayCompletedTimeStamp = m_configReplayCompletedTimeStamp;
    m_configReplayInProgressMutex.unlock ();
    return configReplayCompletedTimeStamp;
}

bool WaveFrameworkObjectManager::getConfigReplayInProgress()
{
    m_configReplayInProgressMutex.lock();
    bool isConfigReplayInProgress =  false;

    if (false == m_configReplayCompleted &&  true == m_configReplayStarted) 
    {
        isConfigReplayInProgress = true;
    }

    m_configReplayInProgressMutex.unlock();

    return isConfigReplayInProgress;
}


void  WaveFrameworkObjectManager::setNodeReadyForAllCommands (bool isNodeReadyForAllCommands)
{
    m_nodeReadyForAllCommandsMutex.lock();
    m_nodeReadyForAllCommands = isNodeReadyForAllCommands;
    generateTimeStamp (m_nodeReadyForAllCommandsTimeStamp);

    m_nodeReadyForAllCommandsMutex.unlock();

}

bool  WaveFrameworkObjectManager::getNodeReadyForAllCommands ()
{
  m_nodeReadyForAllCommandsMutex.lock();
  bool isNodeReadyForAllCommands =  m_nodeReadyForAllCommands;
  m_nodeReadyForAllCommandsMutex.unlock();

  return isNodeReadyForAllCommands;

}

void WaveFrameworkObjectManager::setNodeZeroized (bool nodeZeroized)
{
    m_nodeZeroizedMutex.lock();
    m_nodeZeroized = nodeZeroized;
    m_nodeZeroizedMutex.unlock();

}

bool  WaveFrameworkObjectManager::isNodeZeroized ()
{
    m_nodeZeroizedMutex.lock();
    bool nodeZeroized=  m_nodeZeroized;
    m_nodeZeroizedMutex.unlock();
    return nodeZeroized;

}

string WaveFrameworkObjectManager::getNodeReadyForAllCommandsTimeStamp()
{

    m_nodeReadyForAllCommandsMutex.lock();
    string nodeReadyForAllCommandsTimeStamps = m_nodeReadyForAllCommandsTimeStamp;
    m_nodeReadyForAllCommandsMutex.unlock();

    return nodeReadyForAllCommandsTimeStamps;
}

void   WaveFrameworkObjectManager::generateTimeStamp (string & timeString)
{
  time_t local_time = time(NULL);
  timeString = (ctime(&local_time));
}

void WaveFrameworkObjectManager::deleteObjects (vector<WaveManagedObject *> *pResults)
{
    int i;
    if (NULL == pResults) return;
    int count = pResults->size ();

    for (i = 0; i < count; i++)
    {
        if (NULL != ((*pResults)[i])) delete ((*pResults)[i]);
    }
    delete pResults;
}
void WaveFrameworkObjectManager::cleanupManageObject (LocationId locationId)
{
    WaveManagedObjectSynchronousQueryContext synchronousQueryContext(WaveNode::getClassName ());
    synchronousQueryContext.addAndAttribute (new AttributeLocationId (locationId, "locationId"));
    vector<WaveManagedObject *> *pResults = querySynchronously (&synchronousQueryContext);
    waveAssert (NULL != pResults, __FILE__, __LINE__);
    vector<ObjectId> deleteObjectIds;
    vector<string> tableNames;
    ResourceId status = FRAMEWORK_SUCCESS;
    UI32 count = pResults->size ();

    deleteObjectIds.clear();
    trace (TRACE_LEVEL_INFO, string("WaveFrameworkObjectManager::cleanupManageObject : cleanup MO associated with LocationId = ") + locationId);
    waveAssert (1 >= count,__FILE__, __LINE__);

    if (count == 1) {
        string sql;
        WaveManagedObject *pWaveManagedObject = dynamic_cast<WaveManagedObject *> ((*pResults)[0]);
        ObjectId waveNodeObjectId = pWaveManagedObject->getObjectId();
        trace(TRACE_LEVEL_INFO, string("WaveFrameworkObjectManager::cleanupManageObject: Wave Node OID = ") + waveNodeObjectId.toString());

        /* Get all table in database */
        tableNames = (OrmRepository::getInstance ())->getTableNames(false);
        UI32 tableSizes = tableNames.size();
        UI32 i = 0;
        /* Go through all tables to look for Object ID that has ownerwavenodeobjectidclassid and ownerwavenodeobjectidinstanceid matched 
                * with the WaveNode Object Id */
        trace(TRACE_LEVEL_INFO, string("WaveFrameworkObjectManager::cleanupManageObject: Table size = ") + tableSizes);
        for (i = 0; i < tableSizes; i++) {
            WaveManagedObjectSynchronousQueryContext synchronousQueryContext1(tableNames[i]);
            synchronousQueryContext1.addAndAttribute (new AttributeUI32(waveNodeObjectId.getClassId(), "ownerWaveNodeObjectIdClassId"));
            synchronousQueryContext1.addAndAttribute (new AttributeUI64 (waveNodeObjectId.getInstanceId(), "ownerWaveNodeObjectIdInstanceId"));
            vector<WaveManagedObject *> *pMOResults = querySynchronously (&synchronousQueryContext1);
            waveAssert (NULL != pMOResults, __FILE__, __LINE__);
            UI32 j = 0;
            UI32 countMOResults = pMOResults->size();
            trace(TRACE_LEVEL_INFO, string("WaveFrameworkObjectManager::cleanupManageObject: Table = ") + tableNames[i] + " Number = " + countMOResults);
            for (j = 0; j < countMOResults; j ++) {
                WaveManagedObject *pManagedObject = dynamic_cast<WaveManagedObject *> ((*pMOResults)[j]);
                trace(TRACE_LEVEL_DEVEL, string("WaveFrameworkObjectManager::cleanupManageObject: OID = ") + (pManagedObject->getObjectId()).toString());
                deleteObjectIds.push_back(pManagedObject->getObjectId());
            }
            deleteObjects(pMOResults);
        }
        
        UI32 numberOfObjectsDeleted = deleteObjectIds.size();
        trace(TRACE_LEVEL_INFO, string("WaveFrameworkObjectManager::cleanupManageObject: Number of Delete Objects = ") + numberOfObjectsDeleted);

        for (i = 0; i < numberOfObjectsDeleted; i++)
        {
            (OrmRepository::getInstance ())->getSqlForDelete (deleteObjectIds[i], sql, OrmRepository::getWaveCurrentSchema ());
        }

        if (true == sql.empty ())
        {
            trace(TRACE_LEVEL_INFO, string("WaveFrameworkObjectManager::cleanupManageObject: No thing to delete "));
            deleteObjects(pResults);
            return;
        }

        PersistenceObjectManagerExecuteTransactionMessage message (sql);

        status = sendSynchronously (&message);

        if (status != WAVE_MESSAGE_SUCCESS)
        {
            trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::cleanupManageObject : Could not send message to Persistence Service.  Status : " + FrameworkToolKit::localize (status));
        }
        else
        {
            status = message.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::cleanupManageObject : Failed to execute the transaction.  Completion Status : " + FrameworkToolKit::localize (status));
            }
            else
            {
                trace(TRACE_LEVEL_SUCCESS, string("WaveFrameworkObjectManager::cleanupManageObject: Successfully cleanup ") + numberOfObjectsDeleted + string(" Management Objects "));
                status = FRAMEWORK_SUCCESS;
            }
        }
    }
    deleteObjects(pResults);
}

void WaveFrameworkObjectManager::createClusterWithNodesSendValidationResultsStep (CreateClusterWithNodesContext *pCreateClusterWithNodesContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::createClusterWithNodesSendValidationResultsStep : Starting ...");

    vector<WaveServiceId> &waveServiceIdsToCommunicate = pCreateClusterWithNodesContext->getWaveServiceIdsToCommunicate ();
    UI32                    numberOfWaveServices        = waveServiceIdsToCommunicate.size ();
    UI32                    i                            = 0;

    UI32                    numberOfResultsLocations     = pCreateClusterWithNodesContext->getNumberOfResultsLocations ();
    UI32                    j                            = 0;
    string                  resultLocationIpAddress      = "";
    SI32                    resultLocationPort           = 0;

    void                   *pValidationResults           = NULL;
    UI32                    validationResultsSize        = 0;

    for (i = 0; i < numberOfWaveServices; i++)
    {
        WaveObjectManagerSendValidationResultsMessage *pMessage = new WaveObjectManagerSendValidationResultsMessage (waveServiceIdsToCommunicate[i]);

        for (j = 0; j < numberOfResultsLocations; j++)
        {
            pCreateClusterWithNodesContext->getResultsLocationAt (j, resultLocationIpAddress, resultLocationPort);
            pCreateClusterWithNodesContext->getValidationResultsForService (resultLocationIpAddress, resultLocationPort, waveServiceIdsToCommunicate[i], pValidationResults, validationResultsSize);

            if ((NULL != pValidationResults) && (0 != validationResultsSize))
            {
                trace (TRACE_LEVEL_DEBUG, string ("WaveFrameworkObjectManager::createClusterWithNodesSendValidationResultsStep : Sending Validation Results to Servcie (") + FrameworkToolKit::getServiceNameById (waveServiceIdsToCommunicate[i]) + ") For One Location.");

                pMessage->addValidationResults (resultLocationIpAddress, resultLocationPort, pValidationResults, validationResultsSize);
            }
        }

        trace (TRACE_LEVEL_DEBUG, string ("WaveFrameworkObjectManager::createClusterWithNodesSendValidationResultsStep : Sending Validation Results to Servcie (") + FrameworkToolKit::getServiceNameById (waveServiceIdsToCommunicate[i]) + ").");

        ResourceId status = sendOneWay (pMessage);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::createClusterWithNodesSendValidationResultsStep : Sending Validation Results to Servcie (") + FrameworkToolKit::getServiceNameById (waveServiceIdsToCommunicate[i]) + ") Failed. Status = " + FrameworkToolKit::localize (status));
        }
    }

    pCreateClusterWithNodesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::createClusterWithNodesSendListOfSecondariesToAllNodesStep (CreateClusterWithNodesContext *pCreateClusterWithNodesContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::createClusterWithNodesSendListOfSecondariesToAllNodesStep : Entering ...");

    vector<LocationId> currentlyKnownLocations;
    vector<LocationId> currentlyConnectedLocations;
    UI32               numberOfCurrentlyKnownLocations = 0;
    UI32               i                               = 0;
    UI32               j                               = 0;
    LocationId         locationId;
    string             ipAddress;
    UI32               port;
    ResourceId         status;
    UI32               numberOfFailures                = 0;

    FrameworkToolKit::getKnownLocations (currentlyKnownLocations);
    numberOfCurrentlyKnownLocations = currentlyKnownLocations.size ();
 
    FrameworkToolKit::getFullyConnectedLocations (currentlyConnectedLocations);

//    ++(*pCreateClusterWithNodesContext);

    WaveCreateClusterWithNodesMessage *pWaveCreateClusterWithNodesMessage = 0;
    if(pCreateClusterWithNodesContext->getPWaveMessage()) 
    {
     pWaveCreateClusterWithNodesMessage =  dynamic_cast<WaveCreateClusterWithNodesMessage *> (pCreateClusterWithNodesContext->getPWaveMessage ());
    waveAssert(NULL != pWaveCreateClusterWithNodesMessage, __FILE__, __LINE__);
    }


    for (i = 0; i < numberOfCurrentlyKnownLocations; i++)
    {
        FrameworkObjectManagerUpdateListOfSecondariesMessage *pFrameworkObjectManagerUpdateListOfSecondariesMessage = new FrameworkObjectManagerUpdateListOfSecondariesMessage ();

        pFrameworkObjectManagerUpdateListOfSecondariesMessage->setConnectedLocationIds (currentlyConnectedLocations);

        for (j = 0; j < numberOfCurrentlyKnownLocations; j++)
        {
            locationId = currentlyKnownLocations[j];
            ipAddress  = FrameworkToolKit::getIpAddressForLocationId (locationId);
            port       = FrameworkToolKit::getPortForLocationId (locationId);

            //determine whether info for a node  being sent in the message is 
            // for a newlyadded node
            bool isNewlyAddedNode = false; 
            if(pWaveCreateClusterWithNodesMessage) 
            {
                 UI32 numberOfNewIpAddresses = pWaveCreateClusterWithNodesMessage->getNumberOfNewNodes ();
            //Loop through each node in the message
                for(UI32 k = 0; k <numberOfNewIpAddresses; ++k) 
                {
                    string      tempIpAddress     = pWaveCreateClusterWithNodesMessage->getNodeAt ((UI32) k);
                    UI32        tempPort          = pWaveCreateClusterWithNodesMessage->getNodePortAt ((UI32) k);
                    LocationId  tempLocationId = FrameworkToolKit::getLocationIdForIpAddressAndPort (tempIpAddress, tempPort);

                    if((locationId == tempLocationId)  && (WAVE_MESSAGE_SUCCESS == pWaveCreateClusterWithNodesMessage->getNewNodeStatus(tempIpAddress,tempPort))) 
                    {
                        isNewlyAddedNode = true;
                        break;
                    }
                }
            }

            pFrameworkObjectManagerUpdateListOfSecondariesMessage->addSecondaryNodeDetails (locationId, ipAddress, port,isNewlyAddedNode);
       }

       //For now we will suppress broadcasts in case of deletes. Set the field here so that the secondary can determine
       // whether to suppress the broadcasts
       pFrameworkObjectManagerUpdateListOfSecondariesMessage->setIsDeletion(pCreateClusterWithNodesContext->getIsDeletion());

       pFrameworkObjectManagerUpdateListOfSecondariesMessage->setLastUsedLocationId (FrameworkToolKit::getLastUsedLocationId ());
    
        status = sendOneWay (pFrameworkObjectManagerUpdateListOfSecondariesMessage, currentlyKnownLocations[i]);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            numberOfFailures++;

            trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::createClusterWithNodesSendListOfSecondariesToAllNodesStep : Error in informing " + ipAddress + string (":") + port);
        }
        else
        {
//            ++(*pCreateClusterWithNodesContext);
        }
    }

//    --(*pCreateClusterWithNodesContext);

    pCreateClusterWithNodesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::createClusterWithNodesSendListOfSecondariesToAllNodesCallback (FrameworkStatus frameworkStatus, FrameworkObjectManagerUpdateListOfSecondariesMessage *pFrameworkObjectManagerUpdateListOfSecondariesMessage, void *pContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::createClusterWithNodesSendListOfSecondariesToAllNodesCallback : Entering ...");

    CreateClusterWithNodesContext *pCreateClusterWithNodesContext = reinterpret_cast<CreateClusterWithNodesContext *> (pContext);
    ResourceId                     status;

    --(*pCreateClusterWithNodesContext);

    if (FRAMEWORK_SUCCESS != frameworkStatus)
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::createClusterWithNodesSendListOfSecondariesToAllNodesCallback : Error in informing a location. Framework Status : " + FrameworkToolKit::localize (frameworkStatus));
    }
    else
    {
        status = pFrameworkObjectManagerUpdateListOfSecondariesMessage->getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::createClusterWithNodesSendListOfSecondariesToAllNodesCallback : Error in informing a location. Completion Status : " + FrameworkToolKit::localize (status));
        }
    }

    if (NULL != pFrameworkObjectManagerUpdateListOfSecondariesMessage)
    {
        delete pFrameworkObjectManagerUpdateListOfSecondariesMessage;
    }

    pCreateClusterWithNodesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    return;
}
/// Name
/// broadcastNewNodesAddedEventOnPrimaryStep
/// Description
/// Broadcasts lists of all new nodes added as part of addnode 
/// or create cluster
/// Input
/// CreateClusterWithNodesContext *: Used by the f/w
/// Output
/// none
/// Return
/// none

void WaveFrameworkObjectManager::broadcastNewNodesAddedEventOnPrimaryStep(CreateClusterWithNodesContext *pCreateClusterWithNodesContext)
{

    trace(TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::broadcastNewNodesAddedEventOnPrimary: Entering..");

    //Extract the message
    WaveCreateClusterWithNodesMessage *pWaveCreateClusterWithNodesMessage = dynamic_cast<WaveCreateClusterWithNodesMessage *> (pCreateClusterWithNodesContext->getPWaveMessage ());
    waveAssert(NULL != pWaveCreateClusterWithNodesMessage,__FILE__, __LINE__);

    //Number of nodes in the message received from the cluster service
    UI32 numberOfNewIpAddresses = pWaveCreateClusterWithNodesMessage->getNumberOfNewNodes ();

    WaveNewNodesAddedEvent* pWaveNewNodesAddedEvent = new WaveNewNodesAddedEvent();
    for(UI32 i = 0; i<numberOfNewIpAddresses; ++i)
    {
       string ipAddress     = pWaveCreateClusterWithNodesMessage->getNodeAt ((UI32) i);
       UI32    port         = pWaveCreateClusterWithNodesMessage->getNodePortAt ((UI32) i);

       //Only nodes that were successfully added
       if(WAVE_MESSAGE_SUCCESS == pWaveCreateClusterWithNodesMessage->getNewNodeStatus(ipAddress, port))
        {
           LocationId locationId = FrameworkToolKit::getLocationIdForIpAddressAndPort (ipAddress, port);
           pWaveNewNodesAddedEvent->addNewNodeDetails(locationId,ipAddress,port);
        } else {
            // For the node that is added failed, we should remove MO

        }

    }

    //Broadcast the event
    ResourceId status = broadcast(pWaveNewNodesAddedEvent);

    if(status != WAVE_MESSAGE_SUCCESS)
    {
       trace(TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::broadcastNewNodesAddedEventOnPrimary: Failure during broadcast..");
       pCreateClusterWithNodesContext->executeNextStep (status);
       return;
    }

    pCreateClusterWithNodesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    trace(TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::broadcastNewNodesAddedEventOnPrimary: Exiting..");
    return;

}


void WaveFrameworkObjectManager::configureSecondaryNodeMessageHandler (WaveConfigureClusterSecondaryMessage *pWaveConfigureClusterSecondaryMessage)
{
    SecondaryNodeClusterContext *pSecondaryNodeClusterContext = NULL;
    
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryNodeMessageHandler: (ACTIVE)");

    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::stopClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeValidateDefaultConfigurationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rollbackNodeIfRequiredStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::removePreviousDatabaseBackupFile),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prepareNodeForAddNodeIfRequired),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeValidateStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeValidateVersionStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeValidateServicesStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeShutdownServicesStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeAddNewKnownLocationsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeConnectToNewKnownLocationsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeConfigureMyLocationIdStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeBootServicesPrePhaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeNotifyHaPeerStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeBackupCurrentDatabaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeCleanPreparedTransactionsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeEmptyDatabaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::startClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::checkHaPeerSyncStatusStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::secondaryNodeClusterFailureStep),
    };

    pSecondaryNodeClusterContext = new SecondaryNodeClusterContext (pWaveConfigureClusterSecondaryMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pSecondaryNodeClusterContext->setClusterPrimaryIpAddress  (pWaveConfigureClusterSecondaryMessage->getClusterPrimaryIpAddress ());
    pSecondaryNodeClusterContext->setClusterPrimaryPort       (pWaveConfigureClusterSecondaryMessage->getClusterPrimaryPort ());
    pSecondaryNodeClusterContext->setClusterPrimaryLocationId (pWaveConfigureClusterSecondaryMessage->getClusterPrimaryLocationId ());

    pSecondaryNodeClusterContext->holdAll ();
    pSecondaryNodeClusterContext->start ();
}

void WaveFrameworkObjectManager::configureSecondaryNodeHaPeerMessageHandler (WaveConfigureClusterSecondaryHaPeerMessage *pWaveConfigureClusterSecondaryHaPeerMessage)
{
    SecondaryNodeClusterContext *pSecondaryNodeClusterContext = NULL;

    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryNodeHaPeerMessageHandler: (STANDBY)");

    // Timers are not required on standby since active triggers rollback on standby
    WaveLinearSequencerStep sequencerSteps[] =
    {
        //reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::stopClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::removePreviousDatabaseBackupFile),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeShutdownServicesStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeBootServicesPrePhaseForStandbyStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeBackupCurrentDatabaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeSetLocationRoleOnStandbyStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeCleanPreparedTransactionsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeEmptyDatabaseStep),
        //reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::startClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerFailedStep),
    };

    pSecondaryNodeClusterContext = new SecondaryNodeClusterContext (pWaveConfigureClusterSecondaryHaPeerMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pSecondaryNodeClusterContext->holdAll ();
    pSecondaryNodeClusterContext->start ();
}

void WaveFrameworkObjectManager::configureSecondaryNodePhase1MessageHandler (WaveConfigureClusterSecondaryPhase1Message *pWaveConfigureClusterSecondaryPhase1Message)
{
    SecondaryNodeClusterContext *pSecondaryNodeClusterContext = NULL;

    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryNodePhase1MessageHandler: (ACTIVE)");

    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::stopClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::updateLocationRoleStepInPhase1),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryHaPeerPrePhaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeLoadDatabaseFromPrimaryDatabaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeUpdateInstanceIdsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::startClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::checkHaPeerSyncStatusStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::secondaryNodeClusterFailureStep),
    };

    pSecondaryNodeClusterContext = new SecondaryNodeClusterContext (pWaveConfigureClusterSecondaryPhase1Message, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pSecondaryNodeClusterContext->holdAll ();
    pSecondaryNodeClusterContext->start ();
}

void WaveFrameworkObjectManager::configureSecondaryNodeHaPeerPhase1MessageHandler (WaveConfigureClusterSecondaryHaPeerPhase1Message *pWaveConfigureClusterSecondaryHaPeerPhase1Message)
{
    SecondaryNodeClusterContext *pSecondaryNodeClusterContext = NULL;

    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryNodeHaPeerPhase1MessageHandler: (STANDBY)");

    WaveLinearSequencerStep sequencerSteps[] =
    {
        //reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::stopClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeLoadDatabaseFromPrimaryDatabaseStep),
        //reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::startClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerFailedStep),
    };

    pSecondaryNodeClusterContext = new SecondaryNodeClusterContext (pWaveConfigureClusterSecondaryHaPeerPhase1Message, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pSecondaryNodeClusterContext->holdAll ();
    pSecondaryNodeClusterContext->start ();

}

void WaveFrameworkObjectManager::updateLocationRoleStepInPhase1 (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    LocationRole locationRole = m_pThisLocation->getLocationRole ();

    if (LOCATION_SECONDARY_CLUSTER_PHASE_0 == locationRole)
    {
    m_pThisLocation->setLocationRole (LOCATION_SECONDARY_CLUSTER_PHASE_1);
    pSecondaryNodeClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}
    else
    {
        trace (TRACE_LEVEL_WARN, "WaveFrameworkObjectManager::updateLocationRoleStepInPhase1 received Message in incorrect location role, return with error");
        pSecondaryNodeClusterContext->executeNextStep (WAVE_MESSAGE_ERROR);
    }
}

void WaveFrameworkObjectManager::rollbackNodeIfRequiredStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    LocationRole                           thisLocationRole                       = m_pThisLocation->getLocationRole ();
    ResourceId                             status                                 = WAVE_MESSAGE_SUCCESS;
        
    if ((LOCATION_SECONDARY_CLUSTER_PHASE_0 == thisLocationRole) || (LOCATION_SECONDARY_CLUSTER_PHASE_1 == thisLocationRole) || (LOCATION_SECONDARY_REJOIN_PHASE_1 == thisLocationRole) || (LOCATION_SECONDARY_REJOIN_PHASE_0 == thisLocationRole))
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rollbackNodeIfRequiredStep : Rolling back as the node is in phase 0/1");

        status = m_pInitializeWorker->startWaveServices (WAVE_BOOT_PERSISTENT, WAVE_BOOT_ROLL_BACK_BOOT_PHASE);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::rollbackNodeIfRequiredStep : Roll Back should Never Fail");
            waveAssert (false, __FILE__, __LINE__);
        }
        
    }
    else if ((LOCATION_SECONDARY_CLUSTER_PHASE_2 == thisLocationRole) || (LOCATION_SECONDARY_REJOIN_PHASE_2 == thisLocationRole))
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rollbackNodeIfRequiredStep : Rolling back as the node is in phase 2");

        status = m_pWaveFinalizeWorker->shutdownWaveServices (WAVE_SHUTDOWN_SECONDARY_ROLLBACK);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::rollbackNodeIfRequiredStep : shutdown should Never Fail");
            waveAssert (false, __FILE__, __LINE__);
        }

        status = m_pInitializeWorker->startWaveServices (WAVE_BOOT_PERSISTENT, WAVE_BOOT_ROLL_BACK_BOOT_PHASE_AFTER_PHASE_2);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::rollbackNodeIfRequiredStep : Roll Back should Never Fail");
            waveAssert (false, __FILE__, __LINE__);
        }
        
    }

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::prepareNodeForAddNodeIfRequired (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    LocationRole                           currentRole                            = m_pThisLocation->getLocationRole ();
    ResourceId                             status                                 = WAVE_MESSAGE_SUCCESS;

    // this function should be called when this node is in Primary or Secondary Role and If some other node is inviting this node for cluster formation/Add Node

    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::prepareNodeForAddNodeIfRequired Location Role" + FrameworkToolKit::localize (currentRole));

    if (LOCATION_STAND_ALONE == currentRole)
    {
        pSecondaryNodeClusterContext->executeNextStep (status);
    }
    
    if ((LOCATION_SECONDARY == currentRole) || (LOCATION_PRIMARY_UNCONFIRMED == currentRole) || (LOCATION_SECONDARY_UNCONFIRMED == currentRole))
    {
        WaveLinearSequencerStep sequencerSteps[] =
        {
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::unconfigureClusterSecondaryValidateStep),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::unconfigureClusterSecondarySendStopHeartBeat),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::unconfigureClusterSecondaryDisconnectFromConnectedLocationStep),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::unconfigureClusterSecondaryUpdateThisLocationStep),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::unconfigureClusterSecondaryNodeBootServicesStep),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::unconfigureClusterSecondaryUnconfigureThisLocationStep),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::unconfigureClusterSecondaryRunFailoverStep),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerFailedStep),
        };

        WaveAsynchronousContext *pWaveAsynchronousContext = new WaveAsynchronousContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveFrameworkObjectManager::prepareSecondaryNodeForAddNodeIfRequiredCallback), pSecondaryNodeClusterContext);

        DeleteNodeOnSecondaryContext *pDeleteNodeOnSecondaryContext = new DeleteNodeOnSecondaryContext (pWaveAsynchronousContext, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

        pDeleteNodeOnSecondaryContext->holdAll ();
        pDeleteNodeOnSecondaryContext->start ();
    }    

    if (LOCATION_PRIMARY == currentRole)
    {
        //Disconnect from all the nodes, before sending destroy cluster as in this case we do not want to unconfigure all the attached secondaries
        disconnectFromAllConnectedNodes ();

        //Destroy cluster 
        //Note: This will not send unconfigure to all secondary nodes
        DestroyClusterAsynchronousContext *pDestroyClusterAsynchronousContext = new DestroyClusterAsynchronousContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveFrameworkObjectManager::preparePrimaryNodeForAddNodeIfRequiredCallBack), pSecondaryNodeClusterContext);

        pDestroyClusterAsynchronousContext->setPreparingForAddNode        (true);
        pDestroyClusterAsynchronousContext->setReasonForDestroyingCluster (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_CONTROLLED);
        pDestroyClusterAsynchronousContext->setOriginalRequester          (WaveFrameworkObjectManager::getWaveServiceId ());
        pDestroyClusterAsynchronousContext->setIsRebootRequired           (false);

        destroyClusterAsynchronousHandler (pDestroyClusterAsynchronousContext);
    }
}

void WaveFrameworkObjectManager::prepareSecondaryNodeForAddNodeIfRequiredCallback (WaveAsynchronousContext *pWaveAsynchronousContext)
{
    waveAssert (NULL != pWaveAsynchronousContext, __FILE__, __LINE__);

    SecondaryNodeClusterContext *pSecondaryNodeClusterContext = reinterpret_cast<SecondaryNodeClusterContext *> (pWaveAsynchronousContext->getPCallerContext ());
    ResourceId                   status                       = pWaveAsynchronousContext->getCompletionStatus ();

    waveAssert (NULL != pSecondaryNodeClusterContext, __FILE__, __LINE__);

    delete pWaveAsynchronousContext;

    pSecondaryNodeClusterContext->executeNextStep (status);
}

void WaveFrameworkObjectManager::preparePrimaryNodeForAddNodeIfRequiredCallBack (DestroyClusterAsynchronousContext *pDestroyClusterAsynchronousContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::prepareNodeForAddNodeIfRequiredCallBack : Entering ...");

    waveAssert (NULL !=  pDestroyClusterAsynchronousContext, __FILE__, __LINE__);

    ResourceId                   status                       = pDestroyClusterAsynchronousContext->getCompletionStatus ();
    SecondaryNodeClusterContext *pSecondaryNodeClusterContext = reinterpret_cast<SecondaryNodeClusterContext *> (pDestroyClusterAsynchronousContext->getPCallerContext ());

    delete pDestroyClusterAsynchronousContext;

    if (FrameworkToolKit::getSecondaryClusterFormationFlag ())
    {
        trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::prepareNodeForAddNodeIfRequiredCallback: Flag is TRUE.");
    }
    else
    {
        trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::prepareNodeForAddNodeIfRequiredCallback: Flag is FALSE.");
    }

    pSecondaryNodeClusterContext->executeNextStep (status);
}

void WaveFrameworkObjectManager::configureSecondaryNodeValidateDefaultConfigurationStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    ResourceId status = WAVE_MESSAGE_SUCCESS;

    if (true == FrameworkToolKit::isConfigurationCompatibilityCheckRequired ())
    {
        UI64      configurationTransactionId  = 0;  
        DateTime  configurationTime;
        DateTime  latestUpdateTime;
      
        PersistenceToolKit::getConfigurationManagedObjectInformation (configurationTransactionId, configurationTime, latestUpdateTime); 

        if (0 != configurationTransactionId)
        {
            // Add node request is received by a node which is not in default configuration, hence erroring out the request
            trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::configureSecondaryNodeValidateDefaultConfigurationStep check failed");

            status = WAVE_MESSAGE_ERROR_CONFIGURATION_MISMATCH;
        }
    }

    pSecondaryNodeClusterContext->executeNextStep (status);
}

void WaveFrameworkObjectManager::configureSecondaryNodeValidateStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    WaveConfigureClusterSecondaryMessage *pWaveConfigureClusterSecondaryMessage = reinterpret_cast<WaveConfigureClusterSecondaryMessage *> (pSecondaryNodeClusterContext->getPWaveMessage ());
    LocationRole                           currentRole                            = m_pThisLocation->getLocationRole ();
    ResourceId                             status                                 = WAVE_MESSAGE_SUCCESS;

    if (LOCATION_PRIMARY == currentRole)
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::configureSecondaryNodeValidateStep : Some one else is trying to hijack our Location Id.  Will not reply to this message.");
        status = FRAMEWORK_ERROR_LOCATION_ALREADY_CONFIGURED;
    }
    else if (LOCATION_SECONDARY == currentRole)
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::configureSecondaryNodeValidateStep : Some one else is trying to hijack the Primary Location Id we already know.  Will not reply to this message.");
        status = FRAMEWORK_ERROR_LOCATION_ALREADY_CONFIGURED;
    }
    else if (currentRole == LOCATION_SUB_LOCATION)
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::configureSecondaryNodeValidateStep : Sub Locations cannot play Primary / Secondary Role.  Will not reply");
        status = FRAMEWORK_ERROR_SUB_LOCATION_CANNOT_BECOME_MEMBER_OF_A_CLUSTER;
    }

    // Check if the requesting location is still connected to us.  Otherwise simply drop the request request.
    //  This situation can arise if a requesting location dies or aborts the request before we get a chance to
    // process the message.

    if (false == (InterLocationMessageReceiverObjectManager::isACurrentlyConnectedLocation (pSecondaryNodeClusterContext->getClusterPrimaryIpAddress (), pSecondaryNodeClusterContext->getClusterPrimaryPort ())))
    {
        trace (TRACE_LEVEL_WARN, "WaveFrameworkObjectManager::configureSecondaryNodeValidateStep : Requesting location is not interested us any more.  Dropping the request.");
        status = FRAMEWORK_ERROR_CANNOT_BECOME_SECONDARY_REQUESTING_LOCATION_UNAVAILABLE;
    }

    string ipAddressForThisLocation = pWaveConfigureClusterSecondaryMessage->getIpAddress ();

    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryNodeValidateStep : Currently assumed IP Address for this location : " + m_pThisLocation->getIpAddress ());
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryNodeValidateStep : Requested         IP Address for this Location : " + ipAddressForThisLocation);

    if (false == (FrameworkToolKit::isAnIpAddressForThisMachine (ipAddressForThisLocation)))
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::configureSecondaryNodeValidateStep : Invalid IP Address is specified for this location : " + ipAddressForThisLocation);

        string ethernetInterface = getEthernetInterfaceForThisLocation ();
        string interfaceState = getStateForInterface(ethernetInterface);
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryNodeValidateStep : StateForInterface " + ethernetInterface + " : " + interfaceState);
        status = FRAMEWORK_ERROR_CANNOT_BECOME_SECONDARY_NOT_A_VALID_IPADDRESS_FOR_THIS_LOCATION;
    }
    else
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryNodeValidateStep : Resetting         IP Address for this Location");

        // Right away set our new ipaddress to the Location.
        m_pThisLocation->resetIpAddress (ipAddressForThisLocation);
    }

    pSecondaryNodeClusterContext->executeNextStep (status);
}

// revertTableIdsIfRequired () : This function helps in reverting back the table-ids for the tables in case changed.
// Currently, not being used any place. Will be called in case required.

#if 0
void WaveFrameworkObjectManager::revertTableIdsIfRequired ()
{
    if (false == getTableIdsChangedForSchemaCompatibilityFlag ())
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::revertTableIdsIfRequired: No changes in tableIds for Schema compatibility.");
        return;
    }
    
    // 1. restore tableIds.
    OrmRepository * pOrmRepository = OrmRepository::getInstance();
    pOrmRepository->restoreOldTableIds ();
    
    pOrmRepository->buildMoSchemaRepository ();

    // 2. Handle AuxilliaryTables and their constraints.
    vector<string> oldAuxilliaryTableNames, newAuxilliaryTableNames, parentTableNames, relatedToTableNames;

    getAuxilliaryTableDetailsForSchemaConversion (oldAuxilliaryTableNames, newAuxilliaryTableNames, parentTableNames, relatedToTableNames);

    string sqlToAlterTables = generateSqlToAlterAuxilliaryTableNames (newAuxilliaryTableNames, oldAuxilliaryTableNames, parentTableNames, relatedToTableNames);

    DatabaseStandaloneTransaction dbStandaloneTransaction;
    if (!dbStandaloneTransaction.execute (sqlToAlterTables))
    {   
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager : Error in applying SQL to alter auxillary table names");
        pOrmRepository->restoreOldTableIds (); 
    }
    else
    {
        setTableIdsChangedForSchemaCompatibilityFlag (false);
    }

    return;
}
#endif
/*
string WaveFrameworkObjectManager::handleConstraintsForAuxilliaryTable (string waveSchema, string& oldAuxilliaryTableName, string& newAuxilliaryTableName, string& parentTableName, string &relatedToTableName)
{
    string sqlPrefix        = "ALTER TABLE ONLY " + waveSchema +"."+newAuxilliaryTableName;
    // 1. get sql to drop all existing constraints
    string sqlForConstraint = sqlPrefix + " DROP CONSTRAINT " + oldAuxilliaryTableName + "_ownerclassid_fkey; \n"
                            + sqlPrefix + " DROP CONSTRAINT " + oldAuxilliaryTableName + "_ownerinstanceid_fkey;\n"
                            + sqlPrefix + " DROP CONSTRAINT " + oldAuxilliaryTableName + "_relatedtoclassid_fkey;\n" 
                            + sqlPrefix + " DROP CONSTRAINT " + oldAuxilliaryTableName + "_relatedtoinstanceid_fkey;\n"; 
    
    // Add sql to add constraints.
           sqlForConstraint += sqlPrefix +" ADD CONSTRAINT "+newAuxilliaryTableName + "_ownerclassid_fkey FOREIGN KEY (ownerclassid) REFERENCES " 
                            + waveSchema + "." + parentTableName + "derivations(objectidclassid) DEFERRABLE INITIALLY DEFERRED;\n"
                            + sqlPrefix +" ADD CONSTRAINT "+newAuxilliaryTableName +"_ownerinstanceid_fkey FOREIGN KEY (ownerinstanceid) REFERENCES " 
                            + waveSchema + "." + parentTableName + "derivationsinstances(objectidinstanceid) DEFERRABLE INITIALLY DEFERRED;\n"
                            + sqlPrefix +" ADD CONSTRAINT "+newAuxilliaryTableName +"_relatedtoclassid_fkey FOREIGN KEY (relatedtoclassid) REFERENCES " 
                            + waveSchema + "." + relatedToTableName + "derivations(objectidclassid) DEFERRABLE INITIALLY DEFERRED;\n"
                            + sqlPrefix +" ADD CONSTRAINT "+newAuxilliaryTableName +"_relatedtoinstanceid_fkey FOREIGN KEY (relatedtoinstanceid) REFERENCES " 
                            + waveSchema + "." + relatedToTableName + "derivationsinstances(objectidinstanceid) DEFERRABLE INITIALLY DEFERRED;\n";
    
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::handleConstraintsForAuxilliaryTable: sql for constraints = " + sqlForConstraint);
    return (sqlForConstraint);
}

string WaveFrameworkObjectManager::generateSqlToAlterAuxilliaryTableNames (vector<string>& oldAuxilliaryTableNames,vector<string>& newAuxilliaryTableNames, vector<string>& parentTableNames, vector<string>& relatedToTableNames)
{
    string sqlToChangeAuxilliaryTableNames;
    UI32   numberOfAuxilliaryTables         = oldAuxilliaryTableNames.size ();

    for(UI32 i = 0; i<numberOfAuxilliaryTables; ++i) 
    {
        if (0 != oldAuxilliaryTableNames[i].compare (newAuxilliaryTableNames[i]))
        {
            tracePrintf (TRACE_LEVEL_INFO, true, false, "WaveFrameworkObjectManager::generateSqlToAlterAuxilliaryTableNames : Updating sql to alter name of table [%s] to [%s]", oldAuxilliaryTableNames[i].c_str(), newAuxilliaryTableNames[i].c_str());
            sqlToChangeAuxilliaryTableNames+= "ALTER TABLE " +OrmRepository::getWaveCurrentSchema() + "."+ oldAuxilliaryTableNames[i] +" RENAME TO " + newAuxilliaryTableNames[i] +";";
            sqlToChangeAuxilliaryTableNames+= "ALTER TABLE " +OrmRepository::getWaveStartSchema () + "."+ oldAuxilliaryTableNames[i] +" RENAME TO " + newAuxilliaryTableNames[i] +";";
            sqlToChangeAuxilliaryTableNames+= handleConstraintsForAuxilliaryTable (OrmRepository::getWaveCurrentSchema(), oldAuxilliaryTableNames[i], newAuxilliaryTableNames[i], parentTableNames[i], relatedToTableNames[i]);
            sqlToChangeAuxilliaryTableNames+= handleConstraintsForAuxilliaryTable (OrmRepository::getWaveStartSchema(), oldAuxilliaryTableNames[i], newAuxilliaryTableNames[i], parentTableNames[i], relatedToTableNames[i]);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::generateSqlToAlterAuxilliaryTableNames : no change for table " + oldAuxilliaryTableNames[i]);
        }
    }

    return sqlToChangeAuxilliaryTableNames;
}


ResourceId WaveFrameworkObjectManager::updateTableIdsInOrmWithSchemaInfoReceivedFromPrimary (const vector<string>& managedObjectNamesForSchemaChange, const vector<UI32>& classIds, const vector<UI32>& parentTableIds)
{
    ResourceId      status          = FRAMEWORK_SUCCESS;
    OrmRepository*  pOrmRepository  = OrmRepository::getInstance ();

    vector<string>  oldAuxilliaryTableNames, newAuxilliaryTableNames, parentTablesNames, relatedToTableNames;

    pOrmRepository->updateTableIdsWithTableIdsReceivedFromPrimary (managedObjectNamesForSchemaChange, classIds, parentTableIds,oldAuxilliaryTableNames,newAuxilliaryTableNames, parentTablesNames, relatedToTableNames);
    string sqlToAlterTables = generateSqlToAlterAuxilliaryTableNames (oldAuxilliaryTableNames,newAuxilliaryTableNames, parentTablesNames, relatedToTableNames);

    DatabaseStandaloneTransaction dbStandaloneTransaction;
    if (!dbStandaloneTransaction.execute (sqlToAlterTables))
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager : Error in applying SQL to alter auxillary table names");
        //pOrmRepository->restoreOldTableIds ();
        status = FRAMEWORK_ERROR;
    }
    else
    {
        setTableIdsChangedForSchemaCompatibilityFlag (true);
        setAuxilliaryTableDetailsForSchemaConversion (oldAuxilliaryTableNames, newAuxilliaryTableNames, parentTablesNames, relatedToTableNames);
    }

    return status;
}
*/
bool WaveFrameworkObjectManager::isSchemaReceivedFromPrimaryCompatible(const vector<string> & managedObjectNamesForSchemaChange,const vector<string> & fieldNamesStringsForSchemaChange,const vector<string> & fieldNamesTypesForSchemaChange,const vector<UI32> & classIds,const vector<UI32>  & parentTableIds)
{
    //setTableIdsChangedForSchemaCompatibilityFlag (false);    

	bool                                isCompatible            = true;
    bool                                hasTableIdsChanged      = false;
	OrmRepository*                      pOrmRepository          = OrmRepository::getInstance();
	ManagedObjectSchemaInfoRepository&  moSchemaInfoRepository  = pOrmRepository->getMOSchemaInfoRepository();

    UI32 numberOfManagedObjectsInSchema  = moSchemaInfoRepository.getNumberOfInfoObjectsInRepository ();
	UI32 numberOfElementsInPrimarySchema = managedObjectNamesForSchemaChange.size ();
	

        tracePrintf (TRACE_LEVEL_INFO,true, false, "WaveFrameworkObjectManager::isSchemaReceivedFromPrimaryCompatible: number of MO in Primary = %u and this node numberOfManagedObjectsInSchema = %u.", numberOfElementsInPrimarySchema, numberOfManagedObjectsInSchema);

    if (numberOfManagedObjectsInSchema != numberOfElementsInPrimarySchema)
    {
        trace (TRACE_LEVEL_WARN, "WaveFrameworkObjectManager::isSchemaReceivedFromPrimaryCompatible: number of MO in Primary and this node differs.");
        return (false);
    }

	for(UI32 i = 0; i<numberOfElementsInPrimarySchema; ++i) 
	{
		string                   managedObjectName        = managedObjectNamesForSchemaChange[i];
		ManagedObjectSchemaInfo* pManagedObjectSchemaInfo = moSchemaInfoRepository.findSchemaInfoObject(managedObjectName);

        trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::isSchemaReceivedFromPrimaryCompatible: " + managedObjectName);

		if(!pManagedObjectSchemaInfo) 
		{		 
			tracePrintf (TRACE_LEVEL_WARN, "WaveFrameworkObjectManager::isSchemaReceivedFromPrimaryCompatible: [%s] doesn't exist in schema.", managedObjectName.c_str()); 
	        isCompatible = false;
			break;
		}

        // check if tableId has changed.
        if (!hasTableIdsChanged && (classIds [i] != pManagedObjectSchemaInfo->getTableId ()))
        {
            hasTableIdsChanged = true;
            tracePrintf (TRACE_LEVEL_FATAL, true, false, "WaveFrameworkObjectManager::isSchemaReceivedFromPrimaryCompatible: ClassId mismatch found. classId on local node = %u, table-id on Primary (pManagedObjectSchemaInfo->getTableId) = %u ", classIds [i], pManagedObjectSchemaInfo->getTableId ());
            waveAssert (false, __FILE__, __LINE__);
        }

        // check if the fields in MO matches.
		string fieldNames = fieldNamesStringsForSchemaChange[i];
		string fieldTypes = fieldNamesTypesForSchemaChange [i];

        trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::isSchemaReceivedFromPrimaryCompatible: fieldTypes" + fieldTypes);
		vector<string> fieldNamesInPrimarySchema;
		vector<string> fieldTypesInPrimarySchema;

		tokenize(fieldNamesStringsForSchemaChange[i],fieldNamesInPrimarySchema,':');
		tokenize(fieldNamesTypesForSchemaChange [i],fieldTypesInPrimarySchema, ':');

		map<string,string>	simpleFields	= pManagedObjectSchemaInfo->getSimpleFields();
		map<string, string> relationFields  = pManagedObjectSchemaInfo->getRelationFields();

        if ((fieldNamesInPrimarySchema.size ()) != (simpleFields.size () + relationFields.size ()))
        {
            tracePrintf (TRACE_LEVEL_WARN, true, false, "WaveFrameworkObjectManager::isSchemaReceivedFromPrimaryCompatible: no. of fields in [%s] doesn't match with Primary's object.", managedObjectName.c_str());
	        isCompatible = false;
            break;
        }

		for (UI32 j = 0; j<fieldNamesInPrimarySchema.size(); ++j) 
		{
            trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::isSchemaReceivedFromPrimaryCompatible: fieldTypesInPrimarySchema : " + fieldTypesInPrimarySchema [j]);
			 map<string,string>::iterator simpleFieldsIterator = simpleFields.find (fieldNamesInPrimarySchema[j]);

			 if(simpleFieldsIterator != simpleFields.end()) 
			 {
                 trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::isSchemaReceivedFromPrimaryCompatible: simpleField :" + simpleFieldsIterator->second); 
        		 if(simpleFieldsIterator->second != fieldTypesInPrimarySchema [j])
	        	 {
		            isCompatible = false;
				    break;
				 }
			 }
			 else
			 {
				 map<string,string>::iterator relationFieldsIterator = relationFields.find (fieldNamesInPrimarySchema[j]);

				 if(relationFieldsIterator != relationFields.end()) 
				 {
                 trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::isSchemaReceivedFromPrimaryCompatible: relationField :" + relationFieldsIterator->second); 
        			 if(relationFieldsIterator->second != fieldTypesInPrimarySchema[j])
	        		 {
		    			 isCompatible = false;
		    			 break;
		  			 }
				 }
				 else 
				 {
		        	 isCompatible = false;
			         break;
				 }
			 }
		}

		if(!isCompatible) 
		{
            tracePrintf (TRACE_LEVEL_WARN, true, false, "WaveFrameworkObjectManager::isSchemaReceivedFromPrimaryCompatible: atleast a field doesn't found in [%s]", managedObjectName.c_str());
			break;
		}
	}

/*
    // update tableIds if required.
    if (isCompatible && hasTableIdsChanged)
    {   
        if (FRAMEWORK_SUCCESS != updateTableIdsInOrmWithSchemaInfoReceivedFromPrimary (managedObjectNamesForSchemaChange, classIds, parentTableIds))
        {   
            trace (TRACE_LEVEL_WARN, "WaveFrameworkObjectManager::isSchemaReceivedFromPrimaryCompatible: failed to update tableIds received from Primary.");
            isCompatible = false;
        }
        else
        {
            pOrmRepository->buildMoSchemaRepository ();

            //save UpgradeMO in the database as Orm has changed.
            m_pInitializeWorker->populateSchemaUpgradeTableInDb ();
        }
    }
*/
    tracePrintf (TRACE_LEVEL_INFO, true, false, "WaveFrameworkObjectManager::isSchemaReceivedFromPrimaryCompatible: returning %u", isCompatible); 
    return (isCompatible);
}

void WaveFrameworkObjectManager::configureSecondaryNodeValidateVersionStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    WaveConfigureClusterSecondaryMessage *pWaveConfigureClusterSecondaryMessage = reinterpret_cast<WaveConfigureClusterSecondaryMessage *> (pSecondaryNodeClusterContext->getPWaveMessage ());
    string                                 primaryWaveVersionString              = pWaveConfigureClusterSecondaryMessage->getClusterPrimaryWaveVersion ();
    string                                 thisLocationWavePrimaryVersionString  = WaveVersion::getVersionString ();
    ResourceId                             status                                 = WAVE_MESSAGE_SUCCESS;

    if (getNumberOfLineCardPostBootCurrentlyRunning ())
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::configureSecondaryNodeValidateVersionStep :LC Postboot in progress. Returning error.");
        pSecondaryNodeClusterContext->executeNextStep (FRAMEWORK_LINECARD_POSTBOOT_IN_PROGRESS);
        return;
    }

    trace (TRACE_LEVEL_INFO, "This       Location Wave Version : " + thisLocationWavePrimaryVersionString);
    trace (TRACE_LEVEL_INFO, "Requesting Location Wave Version : " + primaryWaveVersionString);

    if (0 == thisLocationWavePrimaryVersionString.compare (primaryWaveVersionString))
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryNodeValidateVersionStep : Version Check succeeded.\n");

        status = WAVE_MESSAGE_SUCCESS;
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::configureSecondaryNodeValidateVersionStep : Version Check failed.\n");

        status = FRAMEWORK_ERROR_CANNOT_BECOME_SECONDARY_WAVE_VERSION_MISMATCH;
    }


    vector<string>  managedObjectNamesForSchemaChange;
    vector<string>  fieldNamesStringsForSchemaChange;
    vector<string>  fieldNamesTypesForSchemaChange;
    vector<UI32>    classIds;
    vector<UI32>    parentTableIds;

    pWaveConfigureClusterSecondaryMessage->getSchemaChangeVectors (managedObjectNamesForSchemaChange,fieldNamesStringsForSchemaChange,fieldNamesTypesForSchemaChange,classIds,parentTableIds); 

    if (!isSchemaReceivedFromPrimaryCompatible (managedObjectNamesForSchemaChange,fieldNamesStringsForSchemaChange,fieldNamesTypesForSchemaChange,classIds,parentTableIds))
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::configureSecondaryNodeValidateVersionStep : Detected schema incompatible between the Primary and this node. These nods must be running the different firmwares.");
        status = WAVE_MESSAGE_ERROR_SCHEMA_MISMATCH;
    }

    pSecondaryNodeClusterContext->executeNextStep (status);
}

void WaveFrameworkObjectManager::configureSecondaryNodeValidateServicesStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    vector<WaveServiceId> waveServiceIds;
    UI32                   numberOfWaveServiceIds;
    UI32                   i;
    LocationId             thisLocationId           = FrameworkToolKit::getThisLocationId ();
    ResourceId             status                   = WAVE_MESSAGE_SUCCESS;

    WaveThread::getListOfServiceIds (waveServiceIds);
    numberOfWaveServiceIds = waveServiceIds.size ();

    WaveConfigureClusterSecondaryMessage *pWaveConfigureClusterSecondaryMessage = reinterpret_cast<WaveConfigureClusterSecondaryMessage *> (pSecondaryNodeClusterContext->getPWaveMessage ());
    waveAssert (NULL != pWaveConfigureClusterSecondaryMessage, __FILE__, __LINE__);

    for (i = 0; i < numberOfWaveServiceIds; i++)
    {
        trace (TRACE_LEVEL_DEBUG, string ("WaveFrameworkObjectManager::configureSecondaryNodeValidateServicesStep : Validating Service : ") + waveServiceIds[i]);

        if (true == (isServiceToBeExcludedInClusterCommunications (waveServiceIds[i])))
        {
            continue;
        }

        //WaveConfigureClusterSecondaryMessage *pWaveConfigureClusterSecondaryMessage = reinterpret_cast<WaveConfigureClusterSecondaryMessage *> (pSecondaryNodeClusterContext->getPWaveMessage ());
        void                                  *pValidationData                        = NULL;
        UI32                                   size                                   = 0;

        pValidationData = pWaveConfigureClusterSecondaryMessage->transferBufferToUser (waveServiceIds[i], size);

        WaveObjectManagerValidateClusterCreationMessage message (waveServiceIds[i]);

        // If we have got some validation data then attach it and send it to the service.

        if ((NULL != pValidationData) && (0 != size))
        {
            trace (TRACE_LEVEL_DEBUG, string ("WaveFrameworkObjectManager::configureSecondaryNodeValidateServicesStep : Sending Validation details to Service : ") + FrameworkToolKit::getServiceNameById (waveServiceIds[i]));

            message.setValidationDetails (pValidationData, size, true);
        }

        status = sendSynchronously (&message, thisLocationId);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            status = FRAMEWORK_ERROR_SERVICE_VALIDATION_FAILED;
            trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::configureSecondaryNodeValidateServicesStep : Failed to Validate Service (") + FrameworkToolKit::getServiceNameById (waveServiceIds[i]) + "), Status : " + FrameworkToolKit::localize (status));
            break;
        }

        status = message.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            status = FRAMEWORK_ERROR_SERVICE_VALIDATION_FAILED;
            trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::configureSecondaryNodeValidateServicesStep : Failed to Validate Service (") + FrameworkToolKit::getServiceNameById (waveServiceIds[i]) + "), Completion Status : " + FrameworkToolKit::localize (status));
            break;
        }

        void *pValidationResults = NULL;

        message.getValidationResults (pValidationResults, size);

        if ((0 != size) && (NULL != pValidationResults))
        {
            trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::configureSecondaryNodeValidateServicesStep : Obtained Validation Results for Service : " + FrameworkToolKit::getServiceNameById (waveServiceIds[i]));

            pWaveConfigureClusterSecondaryMessage->addBuffer (waveServiceIds[i] + s_offSetForValidationResults, size, pValidationResults, true);
        }
        else
        {
            trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::configureSecondaryNodeValidateServicesStep : No Validation Results are obtained for Service : " + FrameworkToolKit::getServiceNameById (waveServiceIds[i]));
        }
    }

    pSecondaryNodeClusterContext->executeNextStep (status);
}

void WaveFrameworkObjectManager::configureSecondaryNodeNotifyHaPeerStep(SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryNodeNotifyHaPeerStep Entering"); 

    if (true == FrameworkToolKit::isConfigurationCompatibilityCheckRequired ())
    {
        // For LC mode Notify HA that secondary joining cluster to start, so HA sync to be stopped.
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryNodeNotifyHaPeerStep: Notify on ClusterUnReady event for secondary firsttime join event ");

        FrameworkToolKit::disableLiveSync ();
        setSyncState (OUT_OF_SYNC);
        setNeedNotifyClusterReadyState (true);
        bool readyState = false;
        notifyClusterReadyState (readyState);
        pSecondaryNodeClusterContext->setClusterHaSyncInProgress (false);
    }
    else if ( (WAVE_MESSAGE_SUCCESS == FrameworkToolKit::isConnectedToHaPeerLocation ()) && (true == FrameworkToolKit::getIsLiveSyncEnabled ()) )
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryNodeNotifyHaPeerStep: Ha Peer is connected and Live Sync enabled.");

        WaveConfigureClusterSecondaryMessage *pWaveConfigureClusterSecondaryMessage = reinterpret_cast<WaveConfigureClusterSecondaryMessage *> (pSecondaryNodeClusterContext->getPWaveMessage ());
        waveAssert (NULL != pWaveConfigureClusterSecondaryMessage, __FILE__, __LINE__);

        WaveConfigureClusterSecondaryHaPeerMessage *pWaveConfigureClusterSecondaryHaPeerMessage = new WaveConfigureClusterSecondaryHaPeerMessage ();
        waveAssert (NULL != pWaveConfigureClusterSecondaryHaPeerMessage, __FILE__, __LINE__);

        pWaveConfigureClusterSecondaryHaPeerMessage->copyBuffersFrom (*pWaveConfigureClusterSecondaryMessage);

        ResourceId haPeerSendStatus = send (pWaveConfigureClusterSecondaryHaPeerMessage, reinterpret_cast<WaveMessageResponseHandler> (&WaveFrameworkObjectManager::configureClusterSecondaryHaPeerMessageCallback), pSecondaryNodeClusterContext, 200000, FrameworkToolKit::getHaPeerLocationId ());
            
        if (WAVE_MESSAGE_SUCCESS != haPeerSendStatus)
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryNodeNotifyHaPeerStep: Send to Ha Peer failed.");
            delete pWaveConfigureClusterSecondaryHaPeerMessage;
            FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
        }
        else
        {
            if (false == pSecondaryNodeClusterContext->getClusterHaSyncInProgress ())
            {
                trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryNodeNotifyHaPeerStep: Cluster Phase 0 to Ha Peer start.");
                pSecondaryNodeClusterContext->setClusterHaSyncInProgress (true);
            }
        }
    }
    else if ((FrameworkToolKit::getSyncState () == IN_SYNC) && (false == FrameworkToolKit::getIsLiveSyncEnabled ()))
    {
        // DB previously in sync from sync dump. but live transaction sync not supported. So set out of sync and notify on sync update fail
        trace (TRACE_LEVEL_WARN, "WaveFrameworkObjectManager::configureSecondaryNodeNotifyHaPeerStep: Live sync disabled. Notify sync update failure on first update after sync dump."); 
        FrameworkToolKit::notifySyncUpdateFailure(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_NOT_SUPPORTED);
    }
    else
    {         
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryNodeNotifyHaPeerStep: Ha Peer is unavailable OR live sync disabled.");
    }

    pSecondaryNodeClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::configureClusterSecondaryHaPeerMessageCallback (FrameworkStatus frameworkStatus, WaveConfigureClusterSecondaryHaPeerMessage *pWaveConfigureClusterSecondaryHaPeerMessage, void *pContext)
{
    //trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureClusterSecondaryHaPeerMessageCallback: Begin.");

    if (FRAMEWORK_SUCCESS != frameworkStatus)
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::configureClusterSecondaryHaPeerMessageCallback: Failed to configure Peer, Framework Status: " + FrameworkToolKit::localize (frameworkStatus));
        FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
    }
    else
    {
        ResourceId status = pWaveConfigureClusterSecondaryHaPeerMessage->getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::configureClusterSecondaryHaPeerMessageCallback: Failed to configure Peer, Completion Status: " + FrameworkToolKit::localize (status));
            FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
        }
    }

    if (NULL != pWaveConfigureClusterSecondaryHaPeerMessage)
    {
        delete pWaveConfigureClusterSecondaryHaPeerMessage;
    }

    SecondaryNodeClusterContext *pSecondaryNodeClusterContext = reinterpret_cast<SecondaryNodeClusterContext *> (pContext);

    if (true == pSecondaryNodeClusterContext->getClusterHaSyncInProgress ())
    {
        pSecondaryNodeClusterContext->setClusterHaSyncInProgress (false);

        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureClusterSecondaryHaPeerMessageCallback: Cluster Phase 0 to Ha Peer end.");

        if ( (pSecondaryNodeClusterContext->getNumberOfCallbacksBeforeAdvancingToNextStep ()) > 0)
        {
            --(*pSecondaryNodeClusterContext);
            pSecondaryNodeClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        }
    }
}

void WaveFrameworkObjectManager::checkHaPeerSyncStatusStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    //trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::checkHaPeerSyncStatusStep");

    if (true == pSecondaryNodeClusterContext->getClusterHaSyncInProgress ())
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::checkHaPeerSyncStatusStep: Cluster sync to HaPeer in-progress");
        ++(*pSecondaryNodeClusterContext);
    }

    pSecondaryNodeClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::checkHaPeerSyncPostPhaseStep (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context)
{
    //trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::checkHaPeerSyncPostPhaseStep");

    if (true == pSecondaryNodeClusterPhase3Context->getClusterHaSyncInProgress ())
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::checkHaPeerSyncPostPhaseStep: Cluster sync to HaPeer in-progress");
        ++(*pSecondaryNodeClusterPhase3Context);
    }

    pSecondaryNodeClusterPhase3Context->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::configureSecondaryHaPeerPrePhaseStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    WaveConfigureClusterSecondaryPhase1Message *pWaveConfigureClusterSecondaryPhase1Message = reinterpret_cast<WaveConfigureClusterSecondaryPhase1Message *> (pSecondaryNodeClusterContext->getPWaveMessage ());
    waveAssert (NULL != pWaveConfigureClusterSecondaryPhase1Message, __FILE__, __LINE__);

    if ( (WAVE_MESSAGE_SUCCESS == FrameworkToolKit::isConnectedToHaPeerLocation ()) && (true == FrameworkToolKit::getIsLiveSyncEnabled ()) )
    {
        WaveConfigureClusterSecondaryHaPeerPhase1Message *pWaveConfigureClusterSecondaryHaPeerPhase1Message = new WaveConfigureClusterSecondaryHaPeerPhase1Message;
        waveAssert (NULL != pWaveConfigureClusterSecondaryHaPeerPhase1Message, __FILE__, __LINE__);

        pWaveConfigureClusterSecondaryHaPeerPhase1Message->copyBuffersFrom (*pWaveConfigureClusterSecondaryPhase1Message);

        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryHaPeerPrePhaseStep: Ha Peer is connected and Live Sync enabled.");

        ResourceId haPeerSendStatus = send (pWaveConfigureClusterSecondaryHaPeerPhase1Message, reinterpret_cast<WaveMessageResponseHandler> (&WaveFrameworkObjectManager::configureSecondaryHaPeerPrePhaseCallback), pSecondaryNodeClusterContext, 200000, FrameworkToolKit::getHaPeerLocationId ());

        if (WAVE_MESSAGE_SUCCESS != haPeerSendStatus)
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryHaPeerPrePhaseStep: Send to Ha Peer failed.");
            delete pWaveConfigureClusterSecondaryHaPeerPhase1Message;
            FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
        }
        else
        {
            if (false == pSecondaryNodeClusterContext->getClusterHaSyncInProgress ())
            {
                trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryHaPeerPrePhaseStep: Cluster Pre-phase to Ha Peer start.");
                pSecondaryNodeClusterContext->setClusterHaSyncInProgress (true);
            }
        }
    }
    else
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryHaPeerPrePhaseStep: Ha Peer is unavailable OR Live sync is disabled.");
    }

    pSecondaryNodeClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::configureSecondaryHaPeerPrePhaseCallback (FrameworkStatus frameworkStatus, WaveConfigureClusterSecondaryHaPeerPhase1Message *pWaveConfigureClusterSecondaryHaPeerPhase1Message, void *pContext)
{
    //trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryHaPeerPrePhaseCallback: Begin.");

    if (FRAMEWORK_SUCCESS != frameworkStatus)
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::configureSecondaryHaPeerPrePhaseCallback: Failed to configure Peer, Framework Status: " + FrameworkToolKit::localize (frameworkStatus));
        FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
    }
    else
    {
        ResourceId status = pWaveConfigureClusterSecondaryHaPeerPhase1Message->getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::configureSecondaryHaPeerPrePhaseCallback: Failed to configure Peer, Completion Status: " + FrameworkToolKit::localize (status));
            FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
        }
    }

    if (NULL != pWaveConfigureClusterSecondaryHaPeerPhase1Message)
    {
        delete pWaveConfigureClusterSecondaryHaPeerPhase1Message;
    }

    SecondaryNodeClusterContext *pSecondaryNodeClusterContext = reinterpret_cast<SecondaryNodeClusterContext *> (pContext);

    if (true == pSecondaryNodeClusterContext->getClusterHaSyncInProgress ())
    {
        pSecondaryNodeClusterContext->setClusterHaSyncInProgress (false);

        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryHaPeerPrePhaseCallback: Cluster Pre-phase to Ha Peer end.");

        if ( (pSecondaryNodeClusterContext->getNumberOfCallbacksBeforeAdvancingToNextStep ()) > 0)
        {
            --(*pSecondaryNodeClusterContext);
            pSecondaryNodeClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        }
    }
}

void WaveFrameworkObjectManager::configureSecondaryHaPeerPostPhaseStep (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context)
{
    WaveConfigureClusterSecondaryPhase3Message *pWaveConfigureClusterSecondaryPhase3Message = reinterpret_cast<WaveConfigureClusterSecondaryPhase3Message *> (pSecondaryNodeClusterPhase3Context->getPWaveMessage ());
    waveAssert (NULL != pWaveConfigureClusterSecondaryPhase3Message, __FILE__, __LINE__);

    if ( (WAVE_MESSAGE_SUCCESS == FrameworkToolKit::isConnectedToHaPeerLocation ()) && (true == FrameworkToolKit::getIsLiveSyncEnabled ()) )
    {
        WaveConfigureClusterSecondaryHaPeerPhase3Message *pWaveConfigureClusterSecondaryHaPeerPhase3Message = new WaveConfigureClusterSecondaryHaPeerPhase3Message;
        waveAssert (NULL != pWaveConfigureClusterSecondaryHaPeerPhase3Message, __FILE__, __LINE__);

        pWaveConfigureClusterSecondaryHaPeerPhase3Message->copyBuffersFrom (*pWaveConfigureClusterSecondaryPhase3Message);

        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryHaPeerPostPhaseStep: Ha Peer is connected and Live Sync enabled.");

        ResourceId haPeerSendStatus = send (pWaveConfigureClusterSecondaryHaPeerPhase3Message, reinterpret_cast<WaveMessageResponseHandler> (&WaveFrameworkObjectManager::configureSecondaryHaPeerPostPhaseCallback), pSecondaryNodeClusterPhase3Context, s_clusterPhase3TimeoutInMilliseconds, FrameworkToolKit::getHaPeerLocationId ());

        if (WAVE_MESSAGE_SUCCESS != haPeerSendStatus)
        {
            trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::configureSecondaryHaPeerPostPhaseStep: Send to Ha Peer failed.");
            delete pWaveConfigureClusterSecondaryHaPeerPhase3Message;
            FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
        }
        else
        {
            if (false == pSecondaryNodeClusterPhase3Context->getClusterHaSyncInProgress ())
            {
                trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryHaPeerPostPhaseStep: Cluster Post-phase to Ha Peer start.");
                pSecondaryNodeClusterPhase3Context->setClusterHaSyncInProgress (true);
            }
        }
    }
    else
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryHaPeerPostPhaseStep: Ha Peer is unavailable OR Live sync is disabled.");
    }

    pSecondaryNodeClusterPhase3Context->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::configureSecondaryHaPeerPostPhaseCallback (FrameworkStatus frameworkStatus, WaveConfigureClusterSecondaryHaPeerPhase3Message *pWaveConfigureClusterSecondaryHaPeerPhase3Message, void *pContext)
{
    //trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryHaPeerPostPhaseCallback: Begin.");
 
    if (FRAMEWORK_SUCCESS != frameworkStatus)
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::configureSecondaryHaPeerPostPhaseCallback: Failed to configure Peer, Framework Status: " + FrameworkToolKit::localize (frameworkStatus));
        FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
    }
    else
    {
        ResourceId status = pWaveConfigureClusterSecondaryHaPeerPhase3Message->getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::configureSecondaryHaPeerPostPhaseCallback: Failed to configure Peer, Completion Status: " + FrameworkToolKit::localize (status));
            FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
        }
    }

    if (NULL != pWaveConfigureClusterSecondaryHaPeerPhase3Message)
    {
        delete pWaveConfigureClusterSecondaryHaPeerPhase3Message;
    }

    SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context = reinterpret_cast<SecondaryNodeClusterPhase3Context *> (pContext); 

    if (true == pSecondaryNodeClusterPhase3Context->getClusterHaSyncInProgress ())
    {
        pSecondaryNodeClusterPhase3Context->setClusterHaSyncInProgress (false);

        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryHaPeerPostPhaseCallback: Cluster Post-phase to Ha Peer end.");

        if ( (pSecondaryNodeClusterPhase3Context->getNumberOfCallbacksBeforeAdvancingToNextStep ()) > 0)
        {
            --(*pSecondaryNodeClusterPhase3Context);
            pSecondaryNodeClusterPhase3Context->executeNextStep (WAVE_MESSAGE_SUCCESS);
        }
    }
}

void WaveFrameworkObjectManager::configureSecondaryNodeAddNewKnownLocationsStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    string     clusterPrimaryIpAddress  = pSecondaryNodeClusterContext->getClusterPrimaryIpAddress ();
    SI32       clusterPrimaryPort       = pSecondaryNodeClusterContext->getClusterPrimaryPort ();
    LocationId clusterPrimaryLocationId = pSecondaryNodeClusterContext->getClusterPrimaryLocationId ();

    m_pThisLocation->addKnownLocation (clusterPrimaryLocationId, clusterPrimaryIpAddress, clusterPrimaryPort);

    trace (TRACE_LEVEL_INFO, string ("WaveFrameworkObjectManager::configureSecondaryNodeAddNewKnownLocationsStep : Added Primary Location to known locations : ") + clusterPrimaryLocationId);
    trace (TRACE_LEVEL_INFO, string ("WaveFrameworkObjectManager::configureSecondaryNodeAddNewKnownLocationsStep : Primary IP Address : ") + clusterPrimaryIpAddress);

    pSecondaryNodeClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::configureSecondaryNodeConnectToNewKnownLocationsStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
                 WaveConfigureClusterSecondaryMessage *pWaveConfigureClusterSecondaryMessage           = reinterpret_cast<WaveConfigureClusterSecondaryMessage *> (pSecondaryNodeClusterContext->getPWaveMessage ());
                 LocationId                             clusterPrimaryLocationId                         = pWaveConfigureClusterSecondaryMessage->getClusterPrimaryLocationId ();
    static const UI32                                   maximumNumberOfRetriesToConnectToARemoteLocation = 30;
    static const UI32                                   maximumNumberOfSecondsToWaitToConnect            = 30;


    m_pThisLocation->connectToRemoteLocation (clusterPrimaryLocationId, maximumNumberOfRetriesToConnectToARemoteLocation, maximumNumberOfSecondsToWaitToConnect);

    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryNodeConnectToNewKnownLocationsStep : Now connected to Primary Location.");

    pSecondaryNodeClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::configureSecondaryNodeBackupCurrentDatabaseStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::configureSecondaryNodeBackupCurrentDatabaseStep : Entering ...");

    string backupFileName = string (FrameworkToolKit::getProcessInitialWorkingDirectory () + "/" + FrameworkToolKit::getDatabaseBackupFileName2 ());

    DatabaseObjectManagerBackupMessage message (backupFileName, false); // Request not to pause the service.  By default it pauses the service.
    message.setDataOnlyBackup (true);

    ResourceId status  = sendSynchronously (&message);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::configureSecondaryNodeBackupCurrentDatabaseStep : Could not send message to backup database.  Status : " + FrameworkToolKit::localize (status));
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        status = message.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::configureSecondaryNodeBackupCurrentDatabaseStep : Message to backup database failed.  Completion Status : " + FrameworkToolKit::localize (status));
            waveAssert (false, __FILE__, __LINE__);
        }
    }

    pSecondaryNodeClusterContext->executeNextStep (status);
}

void WaveFrameworkObjectManager::configureSecondaryNodeCleanPreparedTransactionsStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryNodeCleanPreparedTransactionsStep: Entering ...");

    DatabaseObjectManagerCleanPreparedTransactionsMessage databaseObjectManagerCleanPreparedTransactionsMessage;
    ResourceId                                            cleanPreparedTransactionsStatus                        = WAVE_MESSAGE_SUCCESS;

    cleanPreparedTransactionsStatus = sendSynchronously (&databaseObjectManagerCleanPreparedTransactionsMessage);

    if (WAVE_MESSAGE_SUCCESS != cleanPreparedTransactionsStatus)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::configureSecondaryNodeCleanPreparedTransactionsStep: Could not send message to Clean the Prepared Transactions. Status : " + FrameworkToolKit::localize (cleanPreparedTransactionsStatus));
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        cleanPreparedTransactionsStatus = databaseObjectManagerCleanPreparedTransactionsMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS == cleanPreparedTransactionsStatus)
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryNodeCleanPreparedTransactionsStep: Succeeded in cleaning the previously Prepared Transactions.");
        }
        else
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::configureSecondaryNodeCleanPreparedTransactionsStep: Failed to Clean the previously Prepared Transactions. Status : " + FrameworkToolKit::localize (cleanPreparedTransactionsStatus));
            waveAssert (false, __FILE__, __LINE__);
        }
    }

    pSecondaryNodeClusterContext->executeNextStep (cleanPreparedTransactionsStatus);
}

void WaveFrameworkObjectManager::configureSecondaryNodeEmptyDatabaseStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::configureSecondaryNodeEmptyDatabaseStep : Entering ...");

    DatabaseObjectManagerEmptyMessage message;
    ResourceId                        status  = sendSynchronously (&message);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::configureSecondaryNodeEmptyDatabaseStep : Could not send message to empty database.  Status : " + FrameworkToolKit::localize (status));
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        status = message.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::configureSecondaryNodeEmptyDatabaseStep : Message to empty database failed.  Completion Status : " + FrameworkToolKit::localize (status));
            waveAssert (false, __FILE__, __LINE__);
        }
    }

    pSecondaryNodeClusterContext->executeNextStep (status);
}

void WaveFrameworkObjectManager::configureSecondaryNodeLoadDatabaseFromPrimaryDatabaseStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::configureSecondaryNodeLoadDatabaseFromPrimaryDatabaseStep : Entering ...");
    WaveConfigureClusterSecondaryPhase1Message *pWaveConfigureClusterSecondaryPhase1Message = reinterpret_cast<WaveConfigureClusterSecondaryPhase1Message *> (pSecondaryNodeClusterContext->getPWaveMessage ());
    UI32                                   sizeOfTheDatabaseBackupFromPrimary     = 0;
    char                                  *pBuffer                                = reinterpret_cast<char *> (pWaveConfigureClusterSecondaryPhase1Message->findBuffer (pWaveConfigureClusterSecondaryPhase1Message->getDatabaseBackupBufferTag (), sizeOfTheDatabaseBackupFromPrimary));

    string backupFileName = string (FrameworkToolKit::getProcessInitialWorkingDirectory () + "/" + FrameworkToolKit::getDatabaseBackupFileName3 ());

    string filenameToSync;

    pWaveConfigureClusterSecondaryPhase1Message->getFilenameToSync (filenameToSync);

    ResourceId status = WAVE_MESSAGE_SUCCESS;

    if ( false == filenameToSync.empty())
    {
        UI32   sizeOfFileBuffer;
        char *pFileBuffer = (reinterpret_cast<char *> (pWaveConfigureClusterSecondaryPhase1Message->findBuffer ( 11, sizeOfFileBuffer) ));
        waveAssert ( NULL != pFileBuffer, __FILE__, __LINE__);

        string configMgmtScriptsPath = ConfigFileManagementToolKit::getConfigFileManagementScriptsDirectory ();
        string configMgmtFileName = configMgmtScriptsPath + "/" + ConfigFileManagementToolKit::getConfigFileManagementLocalOnlyFilename ();

        status = createFileForSyncBuffer ( configMgmtFileName, pFileBuffer, sizeOfFileBuffer);

        if (WAVE_MESSAGE_SUCCESS != status)
        {   
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::configureSecondaryNodeLoadDatabaseFromPrimaryDatabaseStep : Could not create file sent from primary.  Status : " + FrameworkToolKit::localize (status));
            waveAssert (false, __FILE__, __LINE__);
        }
    }

    if (NULL != pBuffer)
    {
        ofstream                               databaseBackupFile;

        databaseBackupFile.open (backupFileName.c_str (), ios::binary);
        databaseBackupFile.write (pBuffer, sizeOfTheDatabaseBackupFromPrimary);
        databaseBackupFile.close ();
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::configureSecondaryNodeLoadDatabaseFromPrimaryDatabaseStep : No Database backup has been received ???");
    }

    // Request the Database service to restore itself from the backup file that we created based on the buffer we obtained from the primary.

    DatabaseObjectManagerRestoreMessage message (backupFileName);
    message.setDataOnlyRestore (true);

    status  = sendSynchronously (&message);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::configureSecondaryNodeLoadDatabaseFromPrimaryDatabaseStep : Could not send message to restore database.  Status : " + FrameworkToolKit::localize (status));
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        status = message.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::configureSecondaryNodeLoadDatabaseFromPrimaryDatabaseStep : Message to restore database failed.  Completion Status : " + FrameworkToolKit::localize (status));
            waveAssert (false, __FILE__, __LINE__);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryNodeLoadDatabaseFromPrimaryDatabaseStep : SUCCESSFULLY Synced up local database with that of Primary.");
        }
    }

    pSecondaryNodeClusterContext->executeNextStep (status);
}

void WaveFrameworkObjectManager::configureSecondaryNodeUpdateInstanceIdsStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    PersistenceLocalObjectManagerUpdateInstanceIdMesssage message;

    ResourceId status  = sendSynchronously (&message);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::configureSecondaryNodeUpdateInstanceIdsStep: Could not send message to update Instance Ids.  Status : " + FrameworkToolKit::localize (status));
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        status = message.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::configureSecondaryNodeUpdateInstanceIdsStep: Message to update instance Ids failed.  Completion Status : " + FrameworkToolKit::localize (status));
            waveAssert (false, __FILE__, __LINE__);
        }
    }

    pSecondaryNodeClusterContext->executeNextStep (status);
}

void WaveFrameworkObjectManager::configureSecondaryNodeShutdownServicesStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::configureSecondaryNodeShutdownServicesStep : Entering ...");

    ResourceId status = WAVE_MESSAGE_SUCCESS;

    status = m_pWaveFinalizeWorker->shutdownWaveServices (WAVE_SHUTDOWN_SECONDARY_CONFIGURE);

    pSecondaryNodeClusterContext->executeNextStep (status);
}

void WaveFrameworkObjectManager::configureSecondaryNodeConfigureMyLocationIdStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::configureSecondaryNodeConfigureMyLocationIdStep : Entering ...");

    WaveConfigureClusterSecondaryMessage *pWaveConfigureClusterSecondaryMessage = reinterpret_cast<WaveConfigureClusterSecondaryMessage *> (pSecondaryNodeClusterContext->getPWaveMessage ());
    LocationId                             myNewLocationId                        = pWaveConfigureClusterSecondaryMessage->getLocationId ();
    SI32                                   clusterPrimaryPort                     = pWaveConfigureClusterSecondaryMessage->getClusterPrimaryPort ();
    LocationId                             clusterPrimaryLocationId               = pWaveConfigureClusterSecondaryMessage->getClusterPrimaryLocationId ();

    // First set my new locationId.  Because, when we inform the localclusterservice it might try to use remote communication
    // for heartbeat purposes.
    // Also All event registration related entities must use the correct location id.

    // Set my new location id

    m_pThisLocation->setLocationId (myNewLocationId);

    // Set the cluster primary locationId

    m_pThisLocation->setClusterPrimaryLocationId (clusterPrimaryLocationId);
    m_pThisLocation->setClusterPrimaryPort       (clusterPrimaryPort);

    // Configure the location Role.

    m_pThisLocation->setLocationRole (LOCATION_SECONDARY_CLUSTER_PHASE_0);

    pSecondaryNodeClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::configureSecondaryNodeBootServicesPrePhaseStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::configureSecondaryNodeBootServicesPrePhaseStep : Entering ...");

    ResourceId status = m_pInitializeWorker->startWaveServices (WAVE_BOOT_SECONDARY_CONFIGURE, WAVE_BOOT_PHASE_PRE_PHASE);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::configureSecondaryNodeBootServicesPrePhaseStep : Booting Secondary immediately after configuring must NEVER fail.");
        waveAssert (false, __FILE__, __LINE__);
    }

    pSecondaryNodeClusterContext->executeNextStep (status);
}

void WaveFrameworkObjectManager::configureSecondaryNodeBootServicesPrePhaseForStandbyStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::configureSecondaryNodeBootServicesPrePhaseForStandbyStep : Entering ...");

    ResourceId status = m_pInitializeWorker->startWaveServices (WAVE_BOOT_HASTANDBY, WAVE_BOOT_PHASE_PRE_PHASE);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::configureSecondaryNodeBootServicesPrePhaseForStandbyStep : Booting Secondary immediately after configuring must NEVER fail.");
        waveAssert (false, __FILE__, __LINE__);
    }

    pSecondaryNodeClusterContext->executeNextStep (status);
}

void WaveFrameworkObjectManager::configureSecondaryNodeSetLocationRoleOnStandbyStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::configureSecondaryNodeSetLocationRoleOnStandbyStep: Entering ...");

    // Setting the location role is done here to handle the scenario when active goes away before syncing the location role
    // to standby(via saveConfigurationStep), the location role on standby should be correct inorder to perform necessary
    // recovery actions upon active failure, this is observed during slotpoweron/off on a chassis in the middle of add node

    m_pThisLocation->setLocationRole (LOCATION_SECONDARY_CLUSTER_PHASE_0);

    // Save the location role in configuration file on standby to ensure it comes in appropriate role even
    // if something unexpected happens on standby
    FrameworkToolKit::saveWaveConfiguration (false);
    
    pSecondaryNodeClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::rejoinSecondaryNodeSetLocationRoleOnStandbyStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::rejoinSecondaryNodeSetLocationRoleOnStandbyStep: Entering ...");

    // Setting the location role is done here to handle the scenario when active goes away before syncing the location role
    // to standby(via saveConfigurationStep), the location role on standby should be correct inorder to perform necessary
    // recovery actions upon active failure, this is observed during slotpoweron/off on a chassis with rejoin/primary change in progress

    m_pThisLocation->setLocationRole (LOCATION_SECONDARY_REJOIN_PHASE_0);

    // Save the location role in configuration file on standby to ensure it comes in appropriate role even
    // if something unexpected happens on standby
    FrameworkToolKit::saveWaveConfiguration (false);

    pSecondaryNodeClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::primaryNodeClusterSuccessStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    WaveFrameworkObjectManager::prismLinearSequencerSucceededStep (pWaveLinearSequencerContext);

    setPrimaryNodeClusterOperationFlag (false);
    resumePostponedMessages ();
}

void WaveFrameworkObjectManager::primaryNodeClusterFailureStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    WaveFrameworkObjectManager::prismLinearSequencerFailedStep (pWaveLinearSequencerContext);

    setPrimaryNodeClusterOperationFlag (false);
    resumePostponedMessages ();
}

void WaveFrameworkObjectManager::secondaryNodeClusterFailureStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    trace (TRACE_LEVEL_INFO, string ("WaveFrameworkObjectManager::secondaryNodeClusterFailureStep connecting back to primary to return error back to primary"));

    WaveMessage *pMessage = reinterpret_cast<WaveMessage *> (pSecondaryNodeClusterContext->getPWaveMessage ());

    SI32       currentPrimaryPort       = pSecondaryNodeClusterContext->getClusterPrimaryPort       ();
    LocationId currentPrimaryLocationId = pSecondaryNodeClusterContext->getClusterPrimaryLocationId ();
    string     currentPrimaryIpAddress  = pSecondaryNodeClusterContext->getClusterPrimaryIpAddress  ();


    if (0 != currentPrimaryLocationId)
    {
        if (false == isAKnownLocation (currentPrimaryLocationId))
        {
            m_pThisLocation->addKnownLocation (currentPrimaryLocationId, currentPrimaryIpAddress, currentPrimaryPort);

            pMessage->setRemoveNodeFromKnownLocationAfterReply (true);
        }
    }
    else
    {
        currentPrimaryLocationId = FrameworkToolKit::getClusterPrimaryLocationId ();
        currentPrimaryIpAddress  = FrameworkToolKit::getClusterPrimaryIpAddress  ();
        currentPrimaryPort       = FrameworkToolKit::getClusterPrimaryPort ();
    }

    if (false == FrameworkToolKit::isAConnectedLocation (currentPrimaryLocationId))
    {
        ResourceId connectionStatus = m_pThisLocation->connectToRemoteLocation (currentPrimaryLocationId, 30, 30);
    
        if (FRAMEWORK_SUCCESS != connectionStatus)
        {
            trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::secondaryNodeClusterFailureStep : Could not connect to Current Primary : ") + currentPrimaryIpAddress + string (", Status = ") + FrameworkToolKit::localize (connectionStatus));
        }
    }

    pMessage->setDisconnectFromLocationAfterReply (true);

    WaveFrameworkObjectManager::prismLinearSequencerFailedStep (pSecondaryNodeClusterContext);

    setSecondaryNodeClusterCreationFlag (false);
    if (true == getNeedNotifyClusterReadyState())
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::secondaryNodeClusterFailureStep: Notify on ClusterReady event for secondary join falure event");
        bool readyState = true; 
        notifyClusterReadyState (readyState);
        setNeedNotifyClusterReadyState (false);
    }
    resumePostponedMessages ();
}

void WaveFrameworkObjectManager::startClusterPhaseTimer (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_INFO, " WaveFrameworkObjectManager::startClusterPhaseTimer ");

    if (0 != m_clusterPhaseTimerHandler)
    {
        trace (TRACE_LEVEL_INFO, "Previous Timer is still not expired, so cancelling previous Timer before Starting Timer Again");

        deleteTimer (m_clusterPhaseTimerHandler);
        m_clusterPhaseTimerHandler = 0;
    }

    startTimer (m_clusterPhaseTimerHandler, 300000, reinterpret_cast<WaveTimerExpirationHandler> (&WaveFrameworkObjectManager::clusterPhaseTimerCallback));

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::stopClusterPhaseTimer(WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_INFO, "Stopping Cluster Phase Timer as expected phase is received");

    if (0 != m_clusterPhaseTimerHandler)
    {
        deleteTimer (m_clusterPhaseTimerHandler);

        m_clusterPhaseTimerHandler = 0;
    }

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::clusterPhaseTimerCallback (TimerHandle timerHandle, void * pContext)
{
    LocationRole thisLocationRole = m_pThisLocation->getLocationRole ();

    m_clusterPhaseTimerHandler = 0;

    disconnectFromAllConnectedNodes ();

    if ((LOCATION_SECONDARY_CLUSTER_PHASE_0 == thisLocationRole) || (LOCATION_SECONDARY_CLUSTER_PHASE_1 == thisLocationRole) || (LOCATION_SECONDARY_REJOIN_PHASE_1 == thisLocationRole) || (LOCATION_SECONDARY_REJOIN_PHASE_0 == thisLocationRole))
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::WaveFrameworkObjectManager::clusterPhaseTimerCallback : Timer expired as Expected Phase 2 is not Received");

        ResourceId status = m_pInitializeWorker->startWaveServices (WAVE_BOOT_PERSISTENT, WAVE_BOOT_ROLL_BACK_BOOT_PHASE);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::clusterPhaseTimerCallback : Roll Back should Never Fail");
            waveAssert (false, __FILE__, __LINE__);
        }
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::clusterPhaseTimerCallback : Roll Back complete hence resetting cluster creation flag in framework");    
        WaveFrameworkObjectManager::setSecondaryNodeClusterCreationFlag (false);
        if (true == getNeedNotifyClusterReadyState())
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::clusterPhaseTimerCallback: Notify on ClusterReady event for clusterPhaseTimeout event");
            bool readyState = true;
            notifyClusterReadyState (readyState);
            setNeedNotifyClusterReadyState (false);
        }
        resumePostponedMessages ();
    }
    else if ((LOCATION_SECONDARY_CLUSTER_PHASE_2 == thisLocationRole) || (LOCATION_SECONDARY_REJOIN_PHASE_2 == thisLocationRole))
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::WaveFrameworkObjectManager::clusterPhaseTimerCallback : Timer expired as expected phase 3 is not received");

        ResourceId status = WAVE_MESSAGE_SUCCESS;
    
        status = m_pWaveFinalizeWorker->shutdownWaveServices (WAVE_SHUTDOWN_SECONDARY_ROLLBACK);
        
        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::clusterPhaseTimerCallback : shutdown should Never Fail");
            waveAssert (false, __FILE__, __LINE__);
        }
        
        status = m_pInitializeWorker->startWaveServices (WAVE_BOOT_PERSISTENT, WAVE_BOOT_ROLL_BACK_BOOT_PHASE_AFTER_PHASE_2);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::clusterPhaseTimerCallback : Roll Back should Never Fail");
            waveAssert (false, __FILE__, __LINE__);
        }
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::clusterPhaseTimerCallback : Roll Back from phase2 complete hence resetting cluster creation flag in framework");
        WaveFrameworkObjectManager::setSecondaryNodeClusterCreationFlag (false);
        if (true == getNeedNotifyClusterReadyState())
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::clusterPhaseTimerCallback: Notify on ClusterReady event for clusterPhaseTimeout event");
            bool readyState = true;
            notifyClusterReadyState (readyState);
            setNeedNotifyClusterReadyState (false);
        }
        resumePostponedMessages ();
    }

}

void WaveFrameworkObjectManager::configureSecondaryNodePhase2MessageHandler (WaveConfigureClusterSecondaryPhase2Message *pWaveConfigureClusterSecondaryPhase2Message)
{
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::stopClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::updateLocationRoleStepInPhase2),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),  
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodePhase2BootServicesPostPhaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodePhase2ConfigureThisLocationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::startClusterPhaseTimer),
//        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodePhase3ExecutePostBootStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::secondaryNodeClusterFailureStep),
    };

    SecondaryNodeClusterPhase2Context *pSecondaryNodeClusterPhase2Context = new SecondaryNodeClusterPhase2Context (pWaveConfigureClusterSecondaryPhase2Message, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]), false);

    pSecondaryNodeClusterPhase2Context->holdAll ();
    pSecondaryNodeClusterPhase2Context->start ();
}

void WaveFrameworkObjectManager::updateLocationRoleStepInPhase2 (SecondaryNodeClusterPhase2Context *pSecondaryNodeClusterPhase2Context)
{
    LocationRole locationRole = m_pThisLocation->getLocationRole ();

    if (LOCATION_SECONDARY_CLUSTER_PHASE_1 == locationRole)
    {
        m_pThisLocation->setLocationRole (LOCATION_SECONDARY_CLUSTER_PHASE_2);
        pSecondaryNodeClusterPhase2Context->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
    else
    {
        trace (TRACE_LEVEL_WARN, "WaveFrameworkObjectManager::updateLocationRoleStepInPhase2 received Message in incorrect location role, return with error");
        pSecondaryNodeClusterPhase2Context->executeNextStep (WAVE_MESSAGE_ERROR);
    }
}

void WaveFrameworkObjectManager::configureSecondaryNodePhase2BootServicesPostPhaseStep (SecondaryNodeClusterPhase2Context *pSecondaryNodeClusterPhase2Context)
{
    trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::configureSecondaryNodePhase2BootServicesPostPhaseStep : Entering ...");

    ResourceId status = m_pInitializeWorker->startWaveServices (WAVE_BOOT_SECONDARY_CONFIGURE, WAVE_BOOT_PHASE_POST_PHASE);

    // Instead of asserting, rollback to last known good state.

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_INFO, "configureSecondaryNodePhase2BootServicesPostPhaseStep: Rollback to last known state");

        disconnectFromAllConnectedNodes ();

        ResourceId rollbackStatus = m_pWaveFinalizeWorker->shutdownWaveServices (WAVE_SHUTDOWN_SECONDARY_ROLLBACK);

        if (WAVE_MESSAGE_SUCCESS != rollbackStatus)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::configureSecondaryNodePhase2BootServicesPostPhaseStep : shutdown should Never Fail");
            waveAssert (false, __FILE__, __LINE__);
        }

        rollbackStatus = m_pInitializeWorker->startWaveServices (WAVE_BOOT_PERSISTENT, WAVE_BOOT_ROLL_BACK_BOOT_PHASE_AFTER_PHASE_2);

        if (WAVE_MESSAGE_SUCCESS != rollbackStatus)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::configureSecondaryNodePhase2BootServicesPostPhaseStep : Roll Back should Never Fail");
            waveAssert (false, __FILE__, __LINE__);
        }
    }
    
#if 0
    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::configureSecondaryNodePhase2BootServicesPostPhaseStep : Booting Secondary immediately after configuring must NEVER fail.");
        waveAssert (false, __FILE__, __LINE__);
    }
#endif
    pSecondaryNodeClusterPhase2Context->executeNextStep (status);
}


/// Name
/// configureSecondaryNodePhase2ReplaceNodeIfNeededStep
/// Description
/// This function sends a message to the local cluster service
/// to inform of a new primary node and the local cluster service
/// to inform of replaced node 
///  Input
///  SecondaryNodeClusterContext*:Pointer to phas2context 
/// Output
/// none
/// Return
/// none
void WaveFrameworkObjectManager::configureSecondaryNodePhase2ReplaceNodeIfNeededStep (SecondaryNodeClusterPhase2Context *pSecondaryNodeClusterPhase2Context)
{
    trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::configureSecondaryNodePhase2ReplaceNodeIfNeededStep : Entering ...");

    WaveRejoinClusterSecondaryPhase2Message *pWaveRejoinClusterSecondaryPhase2Message = reinterpret_cast<WaveRejoinClusterSecondaryPhase2Message *> (pSecondaryNodeClusterPhase2Context->getPWaveMessage ());
    ResourceId         processingStatus = WAVE_MESSAGE_SUCCESS;   

    if (true == pWaveRejoinClusterSecondaryPhase2Message->getIsReplaceRejoin ())
    {
        // Inform the local cluster configuration service that the node was replaced so that it can configure itself
        ClusterLocalReportReplaceMessage message;

        LocationId         thisLocationId       = m_pThisLocation->getLocationId();

        message.setThisNodeIpAddress    (m_pThisLocation->getIpAddress ());
        message.setThisNodePort         (m_pThisLocation->getPort());
        message.setThisNodeLocationId   (thisLocationId);

        WaveMessageStatus  status = sendSynchronously (&message, thisLocationId);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            processingStatus = status;
        }
        else
        {
            ResourceId completionStatus = message.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != completionStatus)
            {
                processingStatus = completionStatus;
            }
        }

        if (WAVE_MESSAGE_SUCCESS != processingStatus)
        {
            trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::configureSecondaryNodePhase2ReplaceNodeIfNeededStep : Configuring this location failed : ") + FrameworkToolKit::localize(processingStatus));
        }
    }

    pSecondaryNodeClusterPhase2Context->executeNextStep(processingStatus);
   
}

/// Name
/// configureSecondaryNodePhase2ConfigureThisLocationStep
/// Description
/// This function sends a message to the local cluster service
/// should then update its node status
///  Input
///  SecondaryNodeClusterContext*:Pointer to phas2context 
/// Output
/// none
/// Return
/// none
void WaveFrameworkObjectManager::configureSecondaryNodePhase2ConfigureThisLocationStep (SecondaryNodeClusterPhase2Context *pSecondaryNodeClusterPhase2Context)
{
    trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::configureSecondaryNodePhase2ConfigureThisLocationStep : Entering ...");

    // Now inform the local cluster configuration service that the primary changed so that it can configure itself
    ClusterLocalReportPrimaryNodeChangedMessage message;

    //In phase1 of secondary node confguration m_pThisLocation has already been populated
    //Here we will just copy fields from m_pThisLocation to populate the message being sent
    // to the local cluster service

    message.setThisNodeIpAddress    (m_pThisLocation->getIpAddress ());
    message.setThisNodePort         (m_pThisLocation->getPort());

    LocationId thisLocationId = m_pThisLocation->getLocationId();
    message.setThisNodeLocationId   (thisLocationId);

    WaveMessageStatus  status = sendSynchronously (&message, thisLocationId);
    ResourceId         processingStatus = WAVE_MESSAGE_SUCCESS;   

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        processingStatus = status;
    }
    else
    {
        ResourceId completionStatus = message.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != completionStatus)
        {
            processingStatus = completionStatus;
        }
    }

    if (WAVE_MESSAGE_SUCCESS != processingStatus)
    {
        trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::configureSecondaryNodePhase2ConfigureThisLocationStep : Configuring this location failed : ") + FrameworkToolKit::localize(processingStatus));
    }

    pSecondaryNodeClusterPhase2Context->executeNextStep(processingStatus);
   
}

void WaveFrameworkObjectManager::configureSecondaryNodePhase3SendStartHearBeat (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context)
{
    string primaryNodeIpAddress = FrameworkToolKit::getClusterPrimaryIpAddress();
    UI32   primaryNodePort      = FrameworkToolKit::getClusterPrimaryPort();

    StartHeartBeatMessage  *pMessage = new StartHeartBeatMessage ();
    pMessage->setDstIpAddress (primaryNodeIpAddress);
    pMessage->setDstPortNumber (primaryNodePort);
    pMessage->setHeartBeatInterval (DEFAULT_HEART_BEAT_PERIOD);
    pMessage->setHeartBeatFailureThreshold (DEFAULT_MAX_LOST_HEARTBEATS);

    trace (TRACE_LEVEL_DEBUG, string("configureSecondaryNodePhase3SendStartHearBeat: ") + primaryNodeIpAddress + string(" Port :") +  primaryNodePort);

    WaveMessageStatus status =  sendSynchronously (pMessage);
    ResourceId       processingStatus = WAVE_MESSAGE_SUCCESS;

    if(WAVE_MESSAGE_SUCCESS != status) 
    {
    processingStatus = status;
    }
    else 
    {
        ResourceId completionStatus = pMessage->getCompletionStatus();
        if (WAVE_MESSAGE_SUCCESS != completionStatus)
        {
            processingStatus = completionStatus;
        }
    }

    delete (pMessage);

    if (WAVE_MESSAGE_SUCCESS != processingStatus)
    {
        trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::configureSecondaryNodePhase3SendStartHearBeat : Send StartHeartBeatMessage Failed: ") + FrameworkToolKit::localize(processingStatus));
    }

    pSecondaryNodeClusterPhase3Context->executeNextStep(processingStatus);
}

void WaveFrameworkObjectManager::configureSecondaryNodePhase3ExecutePostBootStep (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context)
{
    ResourceId status = WAVE_MESSAGE_SUCCESS ;

    if ( NULL == m_pWaveFrameworkObjectManagerPostPersistentBootWorker )
    {   
        trace (TRACE_LEVEL_FATAL, string("WaveFrameworkObjectManager::configureSecondaryNodePhase3ExecutePostBootStep : postboot worker pointer is NULL") );
        pSecondaryNodeClusterPhase3Context->executeNextStep( WAVE_MESSAGE_ERROR );
    }

    // During cluster reformation since DB is replaced we trigger COLD recovery
    ResourceId recoveryType = WAVE_HA_COLD_RECOVERY;

    WavePostPersistentBootWorkerClusterContext *pPostPersistentBootWorkerClusterContext = new WavePostPersistentBootWorkerClusterContext();
    pPostPersistentBootWorkerClusterContext->setRecoveryType( recoveryType );

    status = m_pWaveFrameworkObjectManagerPostPersistentBootWorker->triggerPostBootPassTableForAll ( pPostPersistentBootWorkerClusterContext );

    if ( WAVE_MESSAGE_SUCCESS != status )
    {   
        trace (TRACE_LEVEL_FATAL, string("WaveFrameworkObjectManager::configureSecondaryNodePhase3ExecutePostBootStep : postboot failed with status -") + FrameworkToolKit::localize ( status ) );
    }

    delete ( pPostPersistentBootWorkerClusterContext );
    pSecondaryNodeClusterPhase3Context->executeNextStep(status);
}

void WaveFrameworkObjectManager::configureSecondaryNodePhase3MessageHandler (WaveConfigureClusterSecondaryPhase3Message *pWaveConfigureClusterSecondaryPhase3Message)
{
    SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context = NULL;

    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryNodePhase3MessageHandler: (ACTIVE)");

    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::stopClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::broadcastClusterPhase3StartEvent),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::updateLocationRoleStepInPhase3),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryHaPeerPostPhaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodePhase3BootServicesAfterPostPhaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodePhase3ExecutePostBootStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodePhase3ReplayLocalOnlyConfigIfRequiredStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::updateLocationRoleStepPhase3Complete),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::broadcastClusterPhase3CompleteEvent),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodePhase3SendStartHearBeat),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::checkHaPeerSyncPostPhaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerFailedStep),
    };

    pSecondaryNodeClusterPhase3Context = new SecondaryNodeClusterPhase3Context (pWaveConfigureClusterSecondaryPhase3Message, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pSecondaryNodeClusterPhase3Context->holdAll ();
    pSecondaryNodeClusterPhase3Context->start ();
}

void WaveFrameworkObjectManager::configureSecondaryNodeHaPeerPhase3MessageHandler (WaveConfigureClusterSecondaryHaPeerPhase3Message *pWaveConfigureClusterSecondaryHaPeerPhase3Message)
{
    SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context = NULL;

    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryNodePhase3MessageHandler: (STANDBY)");

    WaveLinearSequencerStep sequencerSteps[] =
    {
        //reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::stopClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prepareStandbyAfterClusterPhaseSync),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerFailedStep),
    };

    pSecondaryNodeClusterPhase3Context = new SecondaryNodeClusterPhase3Context (pWaveConfigureClusterSecondaryHaPeerPhase3Message, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pSecondaryNodeClusterPhase3Context->holdAll ();
    pSecondaryNodeClusterPhase3Context->start ();

}

void WaveFrameworkObjectManager::updateLocationRoleStepInPhase3 (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context)
{

    LocationRole locationRole = m_pThisLocation->getLocationRole ();

    if (LOCATION_SECONDARY_CLUSTER_PHASE_2 == locationRole)
    {
    m_pThisLocation->setLocationRole (LOCATION_SECONDARY_CLUSTER_PHASE_3);
    pSecondaryNodeClusterPhase3Context->executeNextStep (WAVE_MESSAGE_SUCCESS);
}
    else
    {
        trace (TRACE_LEVEL_WARN, "WaveFrameworkObjectManager::updateLocationRoleStepInPhase3 received Message in incorrect location role, return with error");
        pSecondaryNodeClusterPhase3Context->executeNextStep (WAVE_MESSAGE_ERROR);
    }
}

void WaveFrameworkObjectManager::updateLocationRoleStepPhase3Complete (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context)
{
    m_pThisLocation->setLocationRole (LOCATION_SECONDARY);
    pSecondaryNodeClusterPhase3Context->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::configureSecondaryNodePhase3BootServicesAfterPostPhaseStep (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryNodePhase3BootServicesAfterPostPhaseStep : Entering ...");

    ResourceId status = m_pInitializeWorker->startWaveServices (WAVE_BOOT_SECONDARY_CONFIGURE, WAVE_BOOT_PHASE_AFTER_POST_PHASE);

    // Instead of asserting, rollback to last known good state.

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_INFO, "configureSecondaryNodePhase3BootServicesAfterPostPhaseStep: Rollback to last known state");

        disconnectFromAllConnectedNodes ();

        ResourceId rollbackStatus = m_pWaveFinalizeWorker->shutdownWaveServices (WAVE_SHUTDOWN_SECONDARY_ROLLBACK);

        if (WAVE_MESSAGE_SUCCESS != rollbackStatus)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::configureSecondaryNodePhase3BootServicesAfterPostPhaseStep : shutdown should Never Fail");
            waveAssert (false, __FILE__, __LINE__);
        }

        rollbackStatus = m_pInitializeWorker->startWaveServices (WAVE_BOOT_PERSISTENT, WAVE_BOOT_ROLL_BACK_BOOT_PHASE_AFTER_PHASE_2);

        if (WAVE_MESSAGE_SUCCESS != rollbackStatus)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::configureSecondaryNodePhase3BootServicesAfterPostPhaseStep : Roll Back should Never Fail");
            waveAssert (false, __FILE__, __LINE__);
        }
    }

#if 0
    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::configureSecondaryNodePhase3BootServicesAfterPostPhaseStep : Configuring Boot Phases for Phase 3 Fails");
        waveAssert (false, __FILE__, __LINE__);
    }
#endif
    pSecondaryNodeClusterPhase3Context->executeNextStep (status);
}

void WaveFrameworkObjectManager::configureSecondaryNodePhase3ReplayLocalOnlyConfigIfRequiredStep (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context)
{
    ResourceId status = WAVE_MESSAGE_SUCCESS;

    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::configureSecondaryNodePhase3ReplayLocalOnlyConfigIfRequiredStep : Starting ...");

    string configFileForReplay (ConfigFileManagementToolKit::getConfigFileManagementScriptsDirectory () + "/" + ConfigFileManagementToolKit::getConfigFileManagementLocalOnlyFilename ());

    string configFilePath           = ConfigFileManagementToolKit::getConfigFileManagementScriptsDirectory ();
    string localOnlyFilename        = ConfigFileManagementToolKit::getConfigFileManagementLocalOnlyFilename ();
    string fullLocalOnlyFilename    = configFilePath + "/" + localOnlyFilename;
    string preConfigReplayCommands  = "bypassCliValidations cluster-formation\nbypassCliValidations principal-only";
    string globalOnlyFilename       = ConfigFileManagementToolKit::getConfigFileManagementGlobalOnlyFilename ();
    string fullGlobalOnlyFilename   = configFilePath + "/" + globalOnlyFilename;


    if (true == ConfigFileManagementToolKit::isFileExisting (fullLocalOnlyFilename))
    {
        // replay the local only configuration file

        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryNodePhase3ReplayLocalOnlyConfigIfRequiredStep : Replay local-only config file on secondary node... ");

        status = ConfigFileManagementToolKit::replayConfigurationFile (configFilePath, localOnlyFilename, preConfigReplayCommands);

        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::configureSecondaryNodePhase3ReplayLocalOnlyConfigIfRequiredStep : Replay of local-only config file on secondary node completed with status: " + FrameworkToolKit::localize (status));

        if (WAVE_MESSAGE_SUCCESS == status)
        {
            // rename the local only configuration file

            string newLocalOnlyFilename = fullLocalOnlyFilename + "." + FrameworkToolKit::getThisLocationIpAddress () + ".backup";
        
            ConfigFileManagementToolKit::renameConfigurationFile (fullLocalOnlyFilename, newLocalOnlyFilename);
        }
    }

    if (true == ConfigFileManagementToolKit::isFileExisting (fullGlobalOnlyFilename))
    {
        // rename the global only configuration file

        string newGlobalOnlyFilename = fullGlobalOnlyFilename + "." + FrameworkToolKit::getThisLocationIpAddress () + ".backup";

        ConfigFileManagementToolKit::renameConfigurationFile (fullGlobalOnlyFilename, newGlobalOnlyFilename);
    }

    pSecondaryNodeClusterPhase3Context->executeNextStep (status);
}

void WaveFrameworkObjectManager::updateListOfSecondariesMessageHandler (FrameworkObjectManagerUpdateListOfSecondariesMessage *pFrameworkObjectManagerUpdateListOfSecondariesMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::updateListOfSecondariesSetupContextStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::updateListOfSecondariesAddKnownLocationsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::updateListOfSecondariesConnectToNewKnownLocationsStep),        
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),  
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::broadcastListOfNewlyAddedNodesStep),

        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerFailedStep),
    };

    UpdateListOfSecondariesContext *pUpdateListOfSecondariesContext = new UpdateListOfSecondariesContext (pFrameworkObjectManagerUpdateListOfSecondariesMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pUpdateListOfSecondariesContext->holdAll ();
    pUpdateListOfSecondariesContext->start ();
}

void WaveFrameworkObjectManager::updateListOfSecondariesSetupContextStep (UpdateListOfSecondariesContext *pUpdateListOfSecondariesContext)
{

    LocationRole locationRole = m_pThisLocation->getLocationRole ();

    if (LOCATION_SECONDARY_CLUSTER_PHASE_2 != locationRole && LOCATION_SECONDARY_REJOIN_PHASE_2 != locationRole && LOCATION_SECONDARY != locationRole)
    {    
        trace (TRACE_LEVEL_WARN, "WaveFrameworkObjectManager::updateListOfSecondariesSetupContextStep received Message in incorrect location role, return with error");
        pUpdateListOfSecondariesContext->executeNextStep (WAVE_MESSAGE_ERROR);

        return;
    }    

    FrameworkObjectManagerUpdateListOfSecondariesMessage *pFrameworkObjectManagerUpdateListOfSecondariesMessage = reinterpret_cast<FrameworkObjectManagerUpdateListOfSecondariesMessage *> (pUpdateListOfSecondariesContext->getPWaveMessage ());
    UI32                                                  numberOfNewSecondaryLocations                         = pFrameworkObjectManagerUpdateListOfSecondariesMessage->getNumberOfSecondaryLocations ();
    UI32                                                  i                                                     = 0;
    LocationId                                            locationId;
    string                                                ipAddress;
    UI32                                                  port;
    LocationId                                            thisLocationId                                        = FrameworkToolKit::getThisLocationId ();
    bool                                                  isNodeNew                                             = false;
    vector<LocationId>                                    connectedLocationIds;

    for (i = 0; i < numberOfNewSecondaryLocations; i++)
    {
        locationId = pFrameworkObjectManagerUpdateListOfSecondariesMessage->getLocationIdAtIndex (i);
        ipAddress  = pFrameworkObjectManagerUpdateListOfSecondariesMessage->getIpAddressAtIndex (i);
        port       = pFrameworkObjectManagerUpdateListOfSecondariesMessage->getPortAtIndex (i);
        isNodeNew  = pFrameworkObjectManagerUpdateListOfSecondariesMessage->isNodeNewAtIndex (i);

        if (thisLocationId != locationId)
        {
            pUpdateListOfSecondariesContext->addSecondaryNodeDetails (locationId, ipAddress, port, isNodeNew);
        }
        //If location id  of this location matches some location id received in the message and the node is newly added
        //then update this information in the context. Later on this information is used to populate the lists 
        // in the broadcast event
        else if(isNodeNew) 
        {
            pUpdateListOfSecondariesContext->setIsThisNodeNew(true); 
        }
    }

    pFrameworkObjectManagerUpdateListOfSecondariesMessage->getConnectedLocationIds (connectedLocationIds);

    pUpdateListOfSecondariesContext->setConnectedLocationsAtPrimary (connectedLocationIds);

    FrameworkToolKit::setLastUsedLocationId (pFrameworkObjectManagerUpdateListOfSecondariesMessage->getLastUsedLocationId ());

    pUpdateListOfSecondariesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::updateListOfSecondariesAddKnownLocationsStep (UpdateListOfSecondariesContext *pUpdateListOfSecondariesContext)
{
    UI32       numberOfNewSecondaryLocations = pUpdateListOfSecondariesContext->getNumberOfSecondaryLocations ();
    UI32       i                             = 0;
    UI32       j                             = 0;
    LocationId locationId;
    string     ipAddress;
    UI32       port;
    UI32       numberOfKnownLocations    = 0;
    vector<LocationId> knownLocationIdsVector;            
    bool       removeFlag                    = true;
    LocationId currentPrimaryLocationId      = FrameworkToolKit::getClusterPrimaryLocationId ();

    FrameworkToolKit::getKnownLocations (knownLocationIdsVector);
    numberOfKnownLocations = knownLocationIdsVector.size ();

    for (i = 0; i < numberOfNewSecondaryLocations; i++)
    {
        locationId = pUpdateListOfSecondariesContext->getLocationIdAtIndex (i);
        ipAddress  = pUpdateListOfSecondariesContext->getIpAddressAtIndex (i);
        port       = pUpdateListOfSecondariesContext->getPortAtIndex (i);

        if (false == (FrameworkToolKit::isAKnownLocation (ipAddress, port)))
        {
            m_pThisLocation->addKnownLocation (locationId, ipAddress, port);

            trace (TRACE_LEVEL_INFO, string ("WaveFrameworkObjectManager::updateListOfSecondariesAddKnownLocationsStep : Added New Known Location : LocationId : ") + locationId + string (", ") + ipAddress + string (":") + port);
        }

    }

    for (j = 0; j < numberOfKnownLocations; j++)
    {
        for (i = 0; i < numberOfNewSecondaryLocations; i++)
        {

            if (pUpdateListOfSecondariesContext->getLocationIdAtIndex (i) == knownLocationIdsVector [j])
            {
                removeFlag = false;
                break;
            }
        }

        if (true == removeFlag && (currentPrimaryLocationId != knownLocationIdsVector [j]))
        {
           disconnectFromLocation (knownLocationIdsVector[j]);
           removeKnownLocation (knownLocationIdsVector[j]);
        }
        else
        {
            removeFlag = true;
        }

    }

    pUpdateListOfSecondariesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::updateListOfSecondariesConnectToNewKnownLocationsStep (UpdateListOfSecondariesContext *pUpdateListOfSecondariesContext)
{
                 vector<LocationId> primaryConnectedLocations;        
                 UI32               i                                                = 0;
                 LocationId         locationId;
    static const UI32               maximumNumberOfRetriesToConnectToARemoteLocation = 30;
    static const UI32               maximumNumberOfSecondsToWaitToConnect            = 30;
         vector<LocationId>         remoteLocationIdsVector;
                 //UI32               numberOfRemoteLocationIds;
                 UI32               numberOfLocationConnectedToPrimary;
    
    FrameworkToolKit::getConnectedLocations (remoteLocationIdsVector);
    //numberOfRemoteLocationIds = remoteLocationIdsVector.size ();

    pUpdateListOfSecondariesContext->getConnectedLocationsAtPrimary (primaryConnectedLocations);
    numberOfLocationConnectedToPrimary = primaryConnectedLocations.size ();

    for (i = 0; i < numberOfLocationConnectedToPrimary; i++)
    {
        locationId = primaryConnectedLocations [i];

        if (false == FrameworkToolKit::isAConnectedLocation (locationId))
        {
            trace (TRACE_LEVEL_INFO, string ("WaveFrameworkObjectManager::updateListOfSecondariesAddKnownLocationsStep : Connecting to New Known Location : LocationId : ") + locationId);
            m_pThisLocation->connectToRemoteLocation (locationId, maximumNumberOfRetriesToConnectToARemoteLocation, maximumNumberOfSecondsToWaitToConnect);
        }
    }

    pUpdateListOfSecondariesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}
/// Name
/// broadcastListOfNewlyAddedNodesStep
/// Description
/// Broadcasts (on the secondary) list of all new nodes 
/// added as part of addnode or create cluster 
/// Input
/// pdateListOfSecondariesContext *: Used by the f/w
/// Output
/// none
/// Return
/// none

void WaveFrameworkObjectManager::broadcastListOfNewlyAddedNodesStep(UpdateListOfSecondariesContext *pUpdateListOfSecondariesContext)
{
  
   trace(TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::broadcastListOfNewlyAddedNodesStep: Entering.."); 

   FrameworkObjectManagerUpdateListOfSecondariesMessage *pFrameworkObjectManagerUpdateListOfSecondariesMessage = dynamic_cast<FrameworkObjectManagerUpdateListOfSecondariesMessage *> (pUpdateListOfSecondariesContext->getPWaveMessage ());

   waveAssert( NULL != pFrameworkObjectManagerUpdateListOfSecondariesMessage, __FILE__, __LINE__);

   //For now broadcast is suppressed for deletion
   if(pFrameworkObjectManagerUpdateListOfSecondariesMessage->isDeletion()) 
   {
     trace(TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::broadcastListOfNewlyAddedNodesStep:Suppressing broadcast for delete");
     pUpdateListOfSecondariesContext->executeNextStep(WAVE_MESSAGE_SUCCESS);
     return;
   }
   UI32 numberOfNewSecondaryLocations = pUpdateListOfSecondariesContext->getNumberOfSecondaryLocations ();
   WaveNewNodesAddedEvent* pWaveNewNodesAddedEvent = new WaveNewNodesAddedEvent();

   //if it is a new node broadcast should contain all nodes received in the message
   // as well as the primary node
   if(pUpdateListOfSecondariesContext->isThisNodeNew())
   {
     //this means that this node is also new and we need to add 
     //the primary to the broadcast event's list.
     string     primaryIpAddress  = FrameworkToolKit::getClusterPrimaryIpAddress();
     UI32       primaryPort       = FrameworkToolKit::getClusterPrimaryPort();
     LocationId primaryLocationId = FrameworkToolKit::getClusterPrimaryLocationId();

     pWaveNewNodesAddedEvent->addNewNodeDetails(primaryLocationId, primaryIpAddress, primaryPort);

     //We need to add all nodes
     for(UI32 i = 0; i < numberOfNewSecondaryLocations; ++i) 
      {
         LocationId locationId = pUpdateListOfSecondariesContext->getLocationIdAtIndex(i);
         string ipAddress = pUpdateListOfSecondariesContext->getIpAddressAtIndex(i);
         UI32   port      = pUpdateListOfSecondariesContext->getPortAtIndex(i);
         pWaveNewNodesAddedEvent->addNewNodeDetails(locationId, ipAddress, port);
      }


   }

   //If this node is not new, then add only the nodes that have been newly added 
   else {
       for(UI32 i = 0; i < numberOfNewSecondaryLocations; ++i) 
       {
       if(pUpdateListOfSecondariesContext->isNodeNewAtIndex(i)) 
       {
          LocationId locationId = pUpdateListOfSecondariesContext->getLocationIdAtIndex(i);
          string ipAddress = pUpdateListOfSecondariesContext->getIpAddressAtIndex(i);
          UI32   port      = pUpdateListOfSecondariesContext->getPortAtIndex(i);
          pWaveNewNodesAddedEvent->addNewNodeDetails(locationId, ipAddress, port);
           
       }
       }
   }


    ResourceId status = broadcast(pWaveNewNodesAddedEvent);

    if(status != WAVE_MESSAGE_SUCCESS) 
    {
       trace(TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::broadcastListOfNewlyAddedNodesStep: Failure during broadcast..");
       pUpdateListOfSecondariesContext->executeNextStep (status);
       return;
    }

    trace(TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::broadcastListOfNewlyAddedNodesStep: Exiting..");
    pUpdateListOfSecondariesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    return;
}

void WaveFrameworkObjectManager::getKnownRemoteLocations (vector<LocationId> &remoteLocationsVector)
{
    if (NULL != m_pThisLocation)
    {
        m_pThisLocation->getKnownRemoteLocations (remoteLocationsVector);
    }
}

void WaveFrameworkObjectManager::getKnownLocations (vector<LocationId> &knownLocationsVector)
{
    if (NULL != m_pThisLocation)
    {
        m_pThisLocation->getKnownLocations (knownLocationsVector);
    }
}

void WaveFrameworkObjectManager::getConnectedLocations (vector<LocationId> &connectedLocationsVector)
{
    if (NULL != m_pThisLocation)
    {
        m_pThisLocation->getConnectedLocations (connectedLocationsVector);
    }
}

void WaveFrameworkObjectManager::getKnownSubLocations (vector<LocationId> &knownSubLocationsVector)
{
    if (NULL != m_pThisLocation)
    {
        m_pThisLocation->getKnownSubLocations (knownSubLocationsVector);
    }
}

bool WaveFrameworkObjectManager::isAKnownLocation (LocationId locationId)
{
    if (NULL != m_pThisLocation)
    {
        return (m_pThisLocation->isAKnownLocation (locationId));
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, "Trying to check if a location is known before this location is configured.");
        waveAssert (false, __FILE__, __LINE__);
        return (false);
    }
}

void WaveFrameworkObjectManager::initializeLastUsedLocationId ()
{
    m_lastUsedLocationId = 256;
}

LocationId WaveFrameworkObjectManager::getNextLocationId ()
{
    UI32 numberOfTries = 0;

    while (true)
    {
        trace (TRACE_LEVEL_INFO, string ("last known locationId: ") + m_lastUsedLocationId);

        m_lastUsedLocationId += 0x00000100;

        if (0 != m_lastUsedLocationId)
        {
            if (false == (isAKnownLocation (m_lastUsedLocationId)))
            {
                trace (TRACE_LEVEL_INFO, string ("return last known locationId: ") + m_lastUsedLocationId);
                return (m_lastUsedLocationId);
            }
        }

        numberOfTries += 0x100;

        if (UINT_MAX == numberOfTries)
        {
            return (0);
        }
    }

    return (0);
}

void WaveFrameworkObjectManager::addNodesToClusterMessageHandler (FrameworkObjectManagerAddNodesToClusterMessage *pFrameworkObjectManagerAddNodesToClusterMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::stopClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rollbackNodeIfRequiredStep),        
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::addNodesToClusterValidateStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesCollectValidationDataStep), // Reuse Sequencer Step
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesPausePersistenceStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesAddKnownLocationsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesConnectToNewKnownLocationsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase1Step),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesResumeDatabaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase2Step),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesSendValidationResultsStep), // Reuse Sequencer Step
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesSendListOfSecondariesToAllNodesStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::broadcastNewNodesAddedEventOnPrimaryStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::sendReplyBackToClusterGlobalService),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::failoverforNodesFailedInPhase2),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesConfigureNewKnownLocationsPhase3Step),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::startHeartBeatToSecondaryNodes),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::broadcastClusterPhase3CompleteEvent),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::broadcastNodesAdditionToClusterCompletedEvent),

        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::primaryNodeClusterSuccessStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::primaryNodeClusterFailureStep),
    };

    AddNodesToClusterContext *pAddNodesToClusterContext = new AddNodesToClusterContext (pFrameworkObjectManagerAddNodesToClusterMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    // Set an indication that cluster operation is in progress on primary node
    setPrimaryNodeClusterOperationFlag (true);

    // The flag is set here to avoid the default setting in base cluster context creation
    // which causes the previous state of the flag to be lost upon controlled failover.
    // Please refer the class hierarchy for various contexts used in cluster operations
    setSecondaryNodeClusterCreationFlag (false);

    pAddNodesToClusterContext->holdAll ();
    pAddNodesToClusterContext->start ();
}

void WaveFrameworkObjectManager::addNodesToClusterValidateStep (AddNodesToClusterContext *pAddNodesToClusterContext)
{
    FrameworkObjectManagerAddNodesToClusterMessage *pFrameworkObjectManagerAddNodesToClusterMessage = reinterpret_cast<FrameworkObjectManagerAddNodesToClusterMessage *> (pAddNodesToClusterContext->getPWaveMessage ());
    UI32                                            numberOfNewNodes                                = pFrameworkObjectManagerAddNodesToClusterMessage->getNumberOfNewNodes ();
    UI32                                            i                                               = 0;
    string                                          thisLocationIpAddress                           = FrameworkToolKit::getThisLocationIpAddress ();
    SI32                                            thisLocationPort                                = FrameworkToolKit::getThisLocationPort ();

    if (NULL == m_pThisLocation)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::addNodesToClusterValidateStep : Configure this location first.");
        waveAssert (false, __FILE__, __LINE__);
        pAddNodesToClusterContext->executeNextStep (FRAMEWORK_ERROR_LOCATION_NOT_CONFIGURED);
        return;
    }
    else
    {
        if (true != (FrameworkToolKit::isThisALocation ()))
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::addNodesToClusterValidateStep : Trying to add a node to cluster using a sub location");
            waveAssert (false, __FILE__, __LINE__);
            pAddNodesToClusterContext->executeNextStep (FRAMEWORK_ERROR_SUB_LOCATION_CANNOT_ADD_NODES_TO_CLUSTER);
            return;
        }

        if (LOCATION_PRIMARY != (m_pThisLocation->getRole ()))
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::addNodesToClusterValidateStep : Trying to add a node to cluster using a secondary location.");
            waveAssert (false, __FILE__, __LINE__);
            pAddNodesToClusterContext->executeNextStep (FRAMEWORK_ERROR_SECONDARY_LOCATION_CANNOT_ADD_NODES_TO_CLUSTER);
            return;
        }
    }

    for (i = 0; i < numberOfNewNodes; i++)
    {
        string ipAddress = pFrameworkObjectManagerAddNodesToClusterMessage->getNodeAt (i);
        SI32   port      = pFrameworkObjectManagerAddNodesToClusterMessage->getNodePortAt (i);

        if ("" == ipAddress)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::addNodesToClusterValidateStep : Trying to add a node to cluster using a NULL ipAddress (" + ipAddress + ")");
            waveAssert (false, __FILE__, __LINE__);
            pAddNodesToClusterContext->executeNextStep (FRAMEWORK_ERROR_NULL_IPADDRESS);
            return;
        }

        sockaddr_in socketAddress;

        SI32 status = inet_pton (AF_INET, ipAddress.c_str (), &socketAddress.sin_addr);

        if (0 >= status)
        {
            trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::addNodesToClusterValidateStep : Trying to create a cluster using an invalid ipAddress (" + ipAddress + ")");
            pAddNodesToClusterContext->executeNextStep (FRAMEWORK_ERROR_INVALID_IPADDRESS);
            return;
        }


        if (true == (FrameworkToolKit::isAnIpAddressForThisMachine (ipAddress)))
        {
            if (thisLocationPort == port)
            {
                trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::addNodesToClusterValidateStep : Trying to add self as a node to cluster (" + ipAddress + ").  We are already the primary of teh cluster.");
                waveAssert (false, __FILE__, __LINE__);
                pAddNodesToClusterContext->executeNextStep (FRAMEWORK_ERROR_CANNOT_ADD_SELF_TO_CLUSTER);
                return;
            }
        }
    }

    pAddNodesToClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    return;
}

void WaveFrameworkObjectManager::addNodesToClusterAddKnownLocationsStep (AddNodesToClusterContext *pAddNodesToClusterContext)
{
    FrameworkObjectManagerAddNodesToClusterMessage *pFrameworkObjectManagerAddNodesToClusterMessage = reinterpret_cast<FrameworkObjectManagerAddNodesToClusterMessage *> (pAddNodesToClusterContext->getPWaveMessage ());
    UI32                                            numberOfNewNodes                                = pFrameworkObjectManagerAddNodesToClusterMessage->getNumberOfNewNodes ();
    UI32                                            i                                               = 0;
    UI32                                            numberOfFailures                                = 0;
    string                                          ipAddress                                       = "";
    SI32                                            port                                            = 0;
    LocationId                                      newLocationId                                   = 0;

    for (i = 0; i < numberOfNewNodes; i++)
    {
        ipAddress = pFrameworkObjectManagerAddNodesToClusterMessage->getNodeAt (i);
        port      = pFrameworkObjectManagerAddNodesToClusterMessage->getNodePortAt (i);

        if (false == (FrameworkToolKit::isAKnownLocation (ipAddress, port)))
        {
            newLocationId = getNextLocationId ();

            if (0 != newLocationId)
            {
                m_pThisLocation->addKnownLocation (newLocationId, ipAddress, port);
                pAddNodesToClusterContext->addNewLocationId (newLocationId);
            }
            else
            {
                numberOfFailures++;
                pFrameworkObjectManagerAddNodesToClusterMessage->setNewNodeStatus (ipAddress, port, FRAMEWORK_ERROR_NO_UNUSED_LOCATION_IDS_AVAILABLE);
            }
        }
        else
        {
            numberOfFailures++;
            pFrameworkObjectManagerAddNodesToClusterMessage->setNewNodeStatus (ipAddress, port, FRAMEWORK_ERROR_IPADDRESS_ALREADY_MEMBER_OF_CLUSTER);
        }
    }

    if (numberOfFailures == numberOfNewNodes)
    {
        pAddNodesToClusterContext->executeNextStep (FRAMEWORK_ERROR_CANNOT_ADD_NODES_TO_CLUSTER_NO_VALID_RESOURCES);
    }
    else
    {
        pAddNodesToClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
}

void WaveFrameworkObjectManager::addNodesToClusterConnectToNewKnownLocationsStep (AddNodesToClusterContext *pAddNodesToClusterContext)
{
    static const UI32                                            maximumNumberOfRetriesToConnectToARemoteLocation  = 30;
    static const UI32                                            maximumNumberOfSecondsToWaitToConnect             = 30;
                 FrameworkObjectManagerAddNodesToClusterMessage *pFrameworkObjectManagerAddNodesToClusterMessage   = reinterpret_cast<FrameworkObjectManagerAddNodesToClusterMessage *> (pAddNodesToClusterContext->getPWaveMessage ());
                 UI32                                            numberOfNewLocationIds                            = pAddNodesToClusterContext->getNumberOfNewLocationIds ();
                 LocationId                                      newLocationId                                     = 0;
                 SI32                                            i                                                 = 0;
                 string                                          ipAddress                                         = "";
                 SI32                                            port                                              = 0;
                 ResourceId                                      status                                            = FRAMEWORK_SUCCESS;
                 UI32                                            numberOfFailures                                  = 0;

    for (i = numberOfNewLocationIds - 1; i >= 0; i--)
    {
        newLocationId = pAddNodesToClusterContext->getNewLocationIdAt ((UI32) i);
        ipAddress     = FrameworkToolKit::getIpAddressForLocationId (newLocationId);
        port          = FrameworkToolKit::getPortForLocationId (newLocationId);

        if (0 != newLocationId)
        {
            status = m_pThisLocation->connectToRemoteLocation (newLocationId, maximumNumberOfRetriesToConnectToARemoteLocation, maximumNumberOfSecondsToWaitToConnect);

            if (FRAMEWORK_SUCCESS != status)
            {
                // Indicate that the status saying that we could not connect to the location.
                // For this location we will not send a message to configure itself as a secondary.

                pFrameworkObjectManagerAddNodesToClusterMessage->setNewNodeStatus (ipAddress, port, status);

                // Since we are not able to connect to the location remove it from the known locations.

                removeKnownLocation (newLocationId);
                pAddNodesToClusterContext->removeNewLocationId (newLocationId);
                numberOfFailures++;
            }
        }
        else
        {
            numberOfFailures++;
        }
    }

    if (numberOfFailures == numberOfNewLocationIds)
    {
        pAddNodesToClusterContext->executeNextStep (FRAMEWORK_ERROR_FAILED_TO_CONECT_TO_ALL_NEW_LOCATIONS);
    }
    else
    {
        pAddNodesToClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
}

void WaveFrameworkObjectManager::addNodesToClusterConfigureNewKnownLocationsStep (AddNodesToClusterContext *pAddNodesToClusterContext)
{
    FrameworkObjectManagerAddNodesToClusterMessage *pFrameworkObjectManagerAddNodesToClusterMessage = reinterpret_cast<FrameworkObjectManagerAddNodesToClusterMessage *> (pAddNodesToClusterContext->getPWaveMessage ());
    UI32                              numberOfNewLocationIds            = pAddNodesToClusterContext->getNumberOfNewLocationIds ();
    UI32                              i                                 = 0;
    LocationId                        thisLocationId                    = FrameworkToolKit::getThisLocationId ();
    SI32                              thisLocationPort                  = FrameworkToolKit::getThisLocationPort ();
    LocationId                        newLocationId                     = 0;
    string                            thisLocationIpAddress             = FrameworkToolKit::getThisLocationIpAddress ();
    string                            ipAddress                         = "";
    SI32                              port                              = 0;
    UI32                              numberOfFailures                  = 0;
    string                            prismVersionString                = WaveVersion::getVersionString ();

    waveAssert (NULL != pFrameworkObjectManagerAddNodesToClusterMessage, __FILE__, __LINE__);

    ++(*pAddNodesToClusterContext);

    for (i = 0; i < numberOfNewLocationIds; i++)
    {
        newLocationId = pAddNodesToClusterContext->getNewLocationIdAt ((UI32) i);
        ipAddress     = FrameworkToolKit::getIpAddressForLocationId (newLocationId);
        port          = FrameworkToolKit::getPortForLocationId (newLocationId);

        // We will send configure message only to the locations that are known to us at this point.  If user supplied
        // a bogus ipaddress, we would have timed out trying to add that location in the previous step
        // and hence that location will not be known to us at this time.

        if (true == (FrameworkToolKit::isAKnownLocation (ipAddress, port)))
        {
            WaveConfigureClusterSecondaryMessage *pMessage = new WaveConfigureClusterSecondaryMessage (prismVersionString, thisLocationIpAddress, thisLocationPort, thisLocationId, ipAddress, port, newLocationId);

            // Add all the validation buffers to the message before sending out

            vector<WaveServiceId> &waveServiceIds                = pAddNodesToClusterContext->getWaveServiceIdsVector ();
            vector<void *>         &validationDetailsVector        = pAddNodesToClusterContext->getValidationDetailsVector ();
            vector<UI32>           &validationDetailsSizesVector   = pAddNodesToClusterContext->getValidationDetailsSizesVector ();

            UI32                    numberOfWaveServiceIds        = waveServiceIds.size ();
            UI32                    numberOfValidationDetails      = validationDetailsVector.size ();
            UI32                    numberOfValidationDetailsSizes = validationDetailsSizesVector.size ();
            UI32                    j                              = 0;

            waveAssert (numberOfWaveServiceIds == numberOfValidationDetails, __FILE__, __LINE__);
            waveAssert (numberOfWaveServiceIds == numberOfValidationDetailsSizes, __FILE__, __LINE__);

            for (j = 0; j < numberOfWaveServiceIds; j++)
            {
                if ((0 != validationDetailsSizesVector[j]) && (NULL != validationDetailsVector[j]))
                {
                    pMessage->addBuffer (waveServiceIds[j], validationDetailsSizesVector[j], validationDetailsVector[j]);
                }
                else
                {
                    trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::addNodesToClusterConfigureNewKnownLocationsStep : We could not have added an entry with 0 size and/or NULL validation buffer.");
                    waveAssert (false, __FILE__, __LINE__);
                }
            }

            WaveMessageStatus status = send (pMessage, reinterpret_cast<WaveMessageResponseHandler> (&WaveFrameworkObjectManager::addNodesToClusterConfigureNewKnownLocationsCallback), pAddNodesToClusterContext, s_clusterPhase0TimeoutInMilliseconds, newLocationId);

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                removeKnownLocation (newLocationId);
                pFrameworkObjectManagerAddNodesToClusterMessage->setNewNodeStatus (ipAddress, port, status);
                trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::addNodesToClusterConfigureNewKnownLocationsStep : Not able to configure one secondary location : ") + newLocationId + string (" Error Code : ") + status);
                numberOfFailures++;

                delete pMessage;
            }
            else
            {
                ++(*pAddNodesToClusterContext);
            }
        }
        else
        {
            numberOfFailures++;
        }
    }

    --(*pAddNodesToClusterContext);

    if (numberOfFailures == numberOfNewLocationIds)
    {
        pAddNodesToClusterContext->executeNextStep (FRAMEWORK_ERROR_FAILED_TO_CONFIGURE_ALL_NEW_LOCATIONS);
    }
    else
    {
        pAddNodesToClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
}

void WaveFrameworkObjectManager::addNodesToClusterConfigureNewKnownLocationsCallback (FrameworkStatus frameworkStatus, WaveConfigureClusterSecondaryMessage *pWaveConfigureClusterSecondaryMessage, void *pContext)
{
    AddNodesToClusterContext                       *pAddNodesToClusterContext                       = reinterpret_cast<AddNodesToClusterContext *> (pContext);
    FrameworkObjectManagerAddNodesToClusterMessage *pFrameworkObjectManagerAddNodesToClusterMessage = reinterpret_cast<FrameworkObjectManagerAddNodesToClusterMessage *> (pAddNodesToClusterContext->getPWaveMessage ());
    LocationId                                      newLocationId;
    string                                          ipAddress;
    SI32                                            port;

    --(*pAddNodesToClusterContext);

    if (NULL != pWaveConfigureClusterSecondaryMessage)
    {
        newLocationId = pWaveConfigureClusterSecondaryMessage->getLocationId ();
        ipAddress     = FrameworkToolKit::getIpAddressForLocationId (newLocationId);
        port          = FrameworkToolKit::getPortForLocationId (newLocationId);

        pAddNodesToClusterContext->addValidaionResultsLocation (ipAddress, port);

        vector<WaveServiceId> &waveServiceIdsToCommunicate = pAddNodesToClusterContext->getWaveServiceIdsToCommunicate ();
        UI32                    numberOfWaveServices        = waveServiceIdsToCommunicate.size ();
        UI32                    i                            = 0;

        for (i = 0; i < numberOfWaveServices; i++)
        {
            void *pValidationResults    = NULL;
            UI32  validationResultsSize = 0;

            pValidationResults = pWaveConfigureClusterSecondaryMessage->transferBufferToUser (s_offSetForValidationResults + waveServiceIdsToCommunicate[i], validationResultsSize);

            pAddNodesToClusterContext->addValidationResultsForService (ipAddress, port, waveServiceIdsToCommunicate[i], pValidationResults, validationResultsSize);
        }

        if (FRAMEWORK_SUCCESS == frameworkStatus)
        {
            waveAssert (NULL != pWaveConfigureClusterSecondaryMessage, __FILE__, __LINE__);

            ResourceId completionStatus = pWaveConfigureClusterSecondaryMessage->getCompletionStatus ();

            pFrameworkObjectManagerAddNodesToClusterMessage->setNewNodeStatus (ipAddress, port, completionStatus);

            if (WAVE_MESSAGE_SUCCESS != completionStatus)
            {
                removeKnownLocation (newLocationId);
            }
        }
        else
        {
            if (NULL != pWaveConfigureClusterSecondaryMessage)
            {
                LocationId newLocationId1 = pWaveConfigureClusterSecondaryMessage->getLocationId ();
                string     ipAddress1     = FrameworkToolKit::getIpAddressForLocationId (newLocationId1);
                SI32       port1          = FrameworkToolKit::getPortForLocationId (newLocationId1);

                pFrameworkObjectManagerAddNodesToClusterMessage->setNewNodeStatus (ipAddress1, port1, frameworkStatus);

                removeKnownLocation (newLocationId1);
            }
        }

    }

    if (NULL != pWaveConfigureClusterSecondaryMessage)
    {
        delete pWaveConfigureClusterSecondaryMessage;
    }

    if (0 == (pAddNodesToClusterContext->getNumberOfCallbacksBeforeAdvancingToNextStep ()))
    {
        UI32       numberOfNewIpAddresses  = pFrameworkObjectManagerAddNodesToClusterMessage->getNumberOfNewNodes ();
        UI32       i                       = 0;
        LocationId newLocationId1          = 0;
        string     ipAddress1              = "";
        SI32       port1                   = 0;
        UI32       numberOfFailures        = 0;

        for (i = 0; i < numberOfNewIpAddresses; i++)
        {
            ipAddress1     = pFrameworkObjectManagerAddNodesToClusterMessage->getNodeAt ((UI32) i);
            port1          = pFrameworkObjectManagerAddNodesToClusterMessage->getNodePortAt ((UI32) i);
            newLocationId1 = FrameworkToolKit::getLocationIdForIpAddressAndPort (ipAddress1, port1);

            if (true != (pFrameworkObjectManagerAddNodesToClusterMessage->isNewNodeStatusSet (ipAddress1, port1)))
            {
                pFrameworkObjectManagerAddNodesToClusterMessage->setNewNodeStatus (ipAddress1, port1, FRAMEWORK_ERROR_CREATE_CLUSTER_CONFIGURE_SECONDARY_TIMED_OUT);

                if (0 != newLocationId1)
                {
                    removeKnownLocation (newLocationId1);
                }

                numberOfFailures++;
            }
            else
            {
                if (WAVE_MESSAGE_SUCCESS != (pFrameworkObjectManagerAddNodesToClusterMessage->getNewNodeStatus (ipAddress1, port1)))
                {
                    numberOfFailures++;
                }
            }
        }

        if (numberOfFailures == numberOfNewIpAddresses)
        {
            pAddNodesToClusterContext->executeNextStep (FRAMEWORK_ERROR_FAILED_TO_CONFIGURE_ALL_NEW_LOCATIONS);
        }
        else
        {
            pAddNodesToClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        }
    }
}

void WaveFrameworkObjectManager::deleteNodesFromClusterMessageHandler (FrameworkObjectManagerDeleteNodesFromClusterMessage *pFrameworkObjectManagerDeleteNodesFromClusterMessage)
{
 
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::deleteNodesFromClusterValidateStep),
// reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::deleteNodesFromClusterUnconfigureKnownLocationsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::deleteNodesFromClusterRemoveKnownLocationsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::deleteNodesFromClusterRunFailoverStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesSendListOfSecondariesToAllNodesStep),        
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerFailedStep),
    };

    DeleteNodesFromClusterContext *pDeleteNodesFromClusterContext = new DeleteNodesFromClusterContext (pFrameworkObjectManagerDeleteNodesFromClusterMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pDeleteNodesFromClusterContext->setIsDeletion(true);

    pDeleteNodesFromClusterContext->setIsConfigurationChange (pFrameworkObjectManagerDeleteNodesFromClusterMessage->getIsConfigurationChange ());

    pDeleteNodesFromClusterContext->holdAll ();
    pDeleteNodesFromClusterContext->start ();
}

void WaveFrameworkObjectManager::deleteNodesFromClusterValidateStep (DeleteNodesFromClusterContext *pDeleteNodesFromClusterContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::deleteNodesFromClusterValidateStep : Entering ...");

    FrameworkObjectManagerDeleteNodesFromClusterMessage *pFrameworkObjectManagerDeleteNodesFromClusterMessage = reinterpret_cast<FrameworkObjectManagerDeleteNodesFromClusterMessage *> (pDeleteNodesFromClusterContext->getPWaveMessage ());
    UI32                                                 numberOfNodes                                        = pFrameworkObjectManagerDeleteNodesFromClusterMessage->getNumberOfNodes ();
    UI32                                                 i                                                    = 0;
    string                                               ipAddress                                            = "";
    SI32                                                 port                                                 = 0;
    UI32                                                 numberOfFailures                                     = 0;
    LocationRole                                         thisLocationRole                                     = m_pThisLocation->getLocationRole ();

    if (LOCATION_PRIMARY != thisLocationRole)
    {
        for (i = 0; i < numberOfNodes; i++)
        {
            ipAddress = pFrameworkObjectManagerDeleteNodesFromClusterMessage->getNodeAt (i);
            port      = pFrameworkObjectManagerDeleteNodesFromClusterMessage->getNodePortAt (i);

            pFrameworkObjectManagerDeleteNodesFromClusterMessage->setNodeStatus (ipAddress, port, FRAMEWORK_ERROR_CANNOT_DELETE_NODES_FROM_CLUSTER_ON_SECONDARY);
        }

        pDeleteNodesFromClusterContext->executeNextStep (FRAMEWORK_ERROR_CANNOT_DELETE_NODES_FROM_CLUSTER_ON_SECONDARY);
        return;
    }

    for (i = 0; i < numberOfNodes; i++)
    {
        ipAddress = pFrameworkObjectManagerDeleteNodesFromClusterMessage->getNodeAt (i);
        port      = pFrameworkObjectManagerDeleteNodesFromClusterMessage->getNodePortAt (i);

        if (true == (FrameworkToolKit::isAKnownLocation (ipAddress, port)))
        {
            pDeleteNodesFromClusterContext->addLocationId (FrameworkToolKit::getLocationIdForIpAddressAndPort (ipAddress, port));
        }
        else
        {
            pFrameworkObjectManagerDeleteNodesFromClusterMessage->setNodeStatus (ipAddress, port, FRAMEWORK_ERROR_CANNOT_DELETE_NODES_FROM_CLUSTER_NOT_A_KNOWN_LOCATION);
            numberOfFailures++;
        }
    }

    if (numberOfFailures == numberOfNodes)
    {
        pDeleteNodesFromClusterContext->executeNextStep (FRAMEWORK_ERROR_CANNOT_DELETE_NODES_FROM_CLUSTER_NO_VALID_RESOURCES);
    }
    else
    {
        pDeleteNodesFromClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
}

void WaveFrameworkObjectManager::deleteNodesFromClusterUnconfigureKnownLocationsStep (DeleteNodesFromClusterContext *pDeleteNodesFromClusterContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::deleteNodesFromClusterUnconfigureKnownLocationsStep : Entering ...");

    FrameworkObjectManagerDeleteNodesFromClusterMessage *pFrameworkObjectManagerDeleteNodesFromClusterMessage = reinterpret_cast<FrameworkObjectManagerDeleteNodesFromClusterMessage *> (pDeleteNodesFromClusterContext->getPWaveMessage ());
    UI32                                                 numberOfLocationIds                                  = pDeleteNodesFromClusterContext->getNumberOfLocationIds ();
    LocationId                                           locationId                                           = 0;
    UI32                                                 i                                                    = 0;
    WaveMessageStatus                                   messageStatus                                        = WAVE_MESSAGE_SUCCESS;
    string                                               ipAddress                                            = "";
    SI32                                                 port                                                 = 0;

    ++(*pDeleteNodesFromClusterContext);

    for (i = 0; i < numberOfLocationIds; i++)
    {
        locationId = pDeleteNodesFromClusterContext->getLocationIdAt (i);
        ipAddress  = FrameworkToolKit::getIpAddressForLocationId (locationId);
        port       = FrameworkToolKit::getPortForLocationId (locationId);

        FrameworkObjectManagerUnconfigureClusterSecondaryMessage *pMessage = new FrameworkObjectManagerUnconfigureClusterSecondaryMessage (ipAddress, port);

        waveAssert (NULL != pMessage, __FILE__, __LINE__);

        messageStatus = send (pMessage, reinterpret_cast<WaveMessageResponseHandler> (&WaveFrameworkObjectManager::deleteNodesFromClusterUnconfigureKnownLocationsCallback), pDeleteNodesFromClusterContext, 10000, locationId);

        if (WAVE_MESSAGE_SUCCESS == messageStatus)
        {
            ++(*pDeleteNodesFromClusterContext);
        }
        else
        {
            pFrameworkObjectManagerDeleteNodesFromClusterMessage->setNodeStatus (ipAddress, port, messageStatus);
            delete pMessage;
        }
    }

    --(*pDeleteNodesFromClusterContext);
    pDeleteNodesFromClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::deleteNodesFromClusterUnconfigureKnownLocationsCallback (FrameworkStatus frameworkStatus, FrameworkObjectManagerUnconfigureClusterSecondaryMessage *pFrameworkObjectManagerUnconfigureClusterSecondaryMessage, void *pContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::deleteNodesFromClusterUnconfigureKnownLocationsCallback : Entering ...");

    DeleteNodesFromClusterContext                       *pDeleteNodesFromClusterContext                       = reinterpret_cast<DeleteNodesFromClusterContext *> (pContext);
    FrameworkObjectManagerDeleteNodesFromClusterMessage *pFrameworkObjectManagerDeleteNodesFromClusterMessage = reinterpret_cast<FrameworkObjectManagerDeleteNodesFromClusterMessage *> (pDeleteNodesFromClusterContext->getPWaveMessage ());
    string                                               ipAddress                                            = "";
    SI32                                                 port                                                 = 0;
    ResourceId                                           completionStatus                                     = WAVE_MESSAGE_SUCCESS;

    --(*pDeleteNodesFromClusterContext);

    if (FRAMEWORK_SUCCESS == frameworkStatus)
    {
        waveAssert (NULL != pFrameworkObjectManagerUnconfigureClusterSecondaryMessage, __FILE__, __LINE__);

        ipAddress        = pFrameworkObjectManagerUnconfigureClusterSecondaryMessage->getClusterSecondaryIpAddress ();
        port             = pFrameworkObjectManagerUnconfigureClusterSecondaryMessage->getClusterSecondaryPort ();
        completionStatus = pFrameworkObjectManagerUnconfigureClusterSecondaryMessage->getCompletionStatus ();

        if ((WAVE_MESSAGE_SUCCESS == completionStatus) || (WAVE_MESSAGE_ERROR_REMOTE_LOCATION_UNAVAILABLE == completionStatus))
        {
            trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::deleteNodesFromClusterUnconfigureKnownLocationsCallback : Succeeded to unconfigure a location (" + ipAddress + ").");
            pFrameworkObjectManagerDeleteNodesFromClusterMessage->setNodeStatus (ipAddress, port, WAVE_MESSAGE_SUCCESS);
        }
        else
        {
            trace (TRACE_LEVEL_WARN, "WaveFrameworkObjectManager::deleteNodesFromClusterUnconfigureKnownLocationsCallback : Failed to unconfigure a location (" + ipAddress + "). Status = " + completionStatus);
            pFrameworkObjectManagerDeleteNodesFromClusterMessage->setNodeStatus (ipAddress, port, completionStatus);
        }
    }
    else
    {
        trace (TRACE_LEVEL_WARN, "WaveFrameworkObjectManager::deleteNodesFromClusterUnconfigureKnownLocationsCallback : Failed to unconfigure a location.");
    }

    if (NULL != pFrameworkObjectManagerUnconfigureClusterSecondaryMessage)
    {
        delete pFrameworkObjectManagerUnconfigureClusterSecondaryMessage;
    }

    pDeleteNodesFromClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::deleteNodesFromClusterRemoveKnownLocationsStep (DeleteNodesFromClusterContext *pDeleteNodesFromClusterContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::deleteNodesFromClusterRemoveKnownLocationsStep : Entering ...");

    FrameworkObjectManagerDeleteNodesFromClusterMessage *pFrameworkObjectManagerDeleteNodesFromClusterMessage = reinterpret_cast<FrameworkObjectManagerDeleteNodesFromClusterMessage *> (pDeleteNodesFromClusterContext->getPWaveMessage ());
    UI32                                                 numberOfLocationIds                                  = pDeleteNodesFromClusterContext->getNumberOfLocationIds ();
    LocationId                                           locationId                                           = 0;
    UI32                                                 i                                                    = 0;
    string                                               ipAddress                                            = "";
    SI32                                                 port                                                 = 0;

    for (i = 0; i < numberOfLocationIds; i++)
    {
        locationId = pDeleteNodesFromClusterContext->getLocationIdAt (i);
        ipAddress  = FrameworkToolKit::getIpAddressForLocationId (locationId);
        port       = FrameworkToolKit::getPortForLocationId (locationId);

        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::deleteNodesFromClusterRemoveKnownLocationsStep : 111 ...");

        // In case of deletion of a disconnected node, we need not do disconnectFromLocation again as it would have been
        // done during HB loss itself. 
        if (false == pFrameworkObjectManagerDeleteNodesFromClusterMessage->getIsDisconnected())
        {
            disconnectFromLocation (locationId);

            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::deleteNodesFromClusterRemoveKnownLocationsStep : 222 ...");

        }

        removeKnownLocation (locationId);

        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::deleteNodesFromClusterRemoveKnownLocationsStep : 333 ...");

        if (false == (pFrameworkObjectManagerDeleteNodesFromClusterMessage->isNodeStatusSet (ipAddress, port)))
        {
            pFrameworkObjectManagerDeleteNodesFromClusterMessage->setNodeStatus (ipAddress, port, FRAMEWORK_ERROR_DELETE_NODES_FROM_CLUSTER_UNCONFIGURE_SECONDARY_TIMED_OUT);
        }
    }

    pDeleteNodesFromClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::deleteNodesFromClusterRunFailoverStep (DeleteNodesFromClusterContext *pDeleteNodesFromClusterContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::deleteNodesFromClusterRunFailoverStep : Entering ...");

    WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext = new WaveFrameworkFailoverWorkerContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveFrameworkObjectManager::deleteNodesFromClusterRunFailoverCallback), pDeleteNodesFromClusterContext);
    UI32                                 numberOfLocationIds                  = pDeleteNodesFromClusterContext->getNumberOfLocationIds ();
    UI32                                 i                                    = 0;
    LocationId                           locationId                           = 0;

    waveAssert (NULL != pWaveFrameworkFailoverWorkerContext, __FILE__, __LINE__);
    waveAssert (NULL != m_pWaveFrameworkFailoverWorker, __FILE__, __LINE__);

    for (i = 0;i < numberOfLocationIds; i++)
    {
        locationId = pDeleteNodesFromClusterContext->getLocationIdAt (i);
        pWaveFrameworkFailoverWorkerContext->addFailedLocationId (locationId);
    }

    pWaveFrameworkFailoverWorkerContext->setThisLocationRole (LOCATION_PRIMARY);
    pWaveFrameworkFailoverWorkerContext->setFailoverReason (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_CONTROLLED);
    pWaveFrameworkFailoverWorkerContext->setIsConfigurationChange (pDeleteNodesFromClusterContext->getIsConfigurationChange ());

    // FIXME : sagar : Appropriately set the nodes that are removed so that failover can notify the list of failed nodes to the services.

    m_pWaveFrameworkFailoverWorker->executeFailover (pWaveFrameworkFailoverWorkerContext);
}

void WaveFrameworkObjectManager::deleteNodesFromClusterRunFailoverCallback (WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::deleteNodesFromClusterRunFailoverCallback : Entering ...");

    waveAssert (NULL != pWaveFrameworkFailoverWorkerContext, __FILE__, __LINE__);

    DeleteNodesFromClusterContext *pDeleteNodesFromClusterContext = reinterpret_cast<DeleteNodesFromClusterContext *> (pWaveFrameworkFailoverWorkerContext->getPCallerContext ());
    ResourceId                     status                         = pWaveFrameworkFailoverWorkerContext->getCompletionStatus ();

    delete pWaveFrameworkFailoverWorkerContext;

    waveAssert (NULL != pDeleteNodesFromClusterContext, __FILE__, __LINE__);


    pDeleteNodesFromClusterContext->executeNextStep (status);
}


void WaveFrameworkObjectManager::unconfigureClusterSecondaryMessageHandler (FrameworkObjectManagerUnconfigureClusterSecondaryMessage *pFrameworkObjectManagerUnconfigureClusterSecondaryMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::unconfigureClusterSecondaryValidateStep),      
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::unconfigureClusterSecondarySendStopHeartBeat),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::unconfigureClusterSecondaryDisconnectFromKnownLocationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::unconfigureClusterSecondaryUpdateThisLocationStep), 
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::unconfigureClusterSecondaryNodeBootServicesStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::unconfigureClusterSecondaryUnconfigureThisLocationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::unconfigureClusterSecondaryRunFailoverStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::unconfigureClusterBroadcastLocalNodeDeletedEventStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerFailedStep),
    };

    DeleteNodeOnSecondaryContext *pDeleteNodeOnSecondaryContext = new DeleteNodeOnSecondaryContext (pFrameworkObjectManagerUnconfigureClusterSecondaryMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    if (true == pFrameworkObjectManagerUnconfigureClusterSecondaryMessage->getIsPerformWarmRecovery ())
    {
        m_pThisLocation->setLocationRole (LOCATION_SECONDARY_UNCONFIRMED);

        m_pThisLocation->setClusterPrimaryLocationId (FrameworkToolKit::getThisLocationId ());
        m_pThisLocation->setClusterPrimaryPort       (FrameworkToolKit::getThisLocationPort());
    }

    pDeleteNodeOnSecondaryContext->holdAll ();
    pDeleteNodeOnSecondaryContext->start ();

}

void WaveFrameworkObjectManager::unconfigureClusterSecondaryValidateStep (DeleteNodeOnSecondaryContext *pDeleteNodeOnSecondaryContext)
{
    LocationRole currentLocationRole = m_pThisLocation->getLocationRole ();
    ResourceId   status              = WAVE_MESSAGE_SUCCESS;

    if ((LOCATION_SECONDARY == currentLocationRole) || (LOCATION_PRIMARY_UNCONFIRMED == currentLocationRole) || (LOCATION_SECONDARY_UNCONFIRMED == currentLocationRole))
    {
        trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::unconfigureClusterSecondaryValidateStep : Proceeding with unconfiguring the cluster secondary.");

        if (LOCATION_SECONDARY != currentLocationRole)
        {
            pDeleteNodeOnSecondaryContext->setIsStartServiceIsRequired (false);
        }
    }
    else
    {
        if (LOCATION_SUB_LOCATION == currentLocationRole)
        {
            trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::unconfigureClusterSecondaryValidateStep : Sub Location coannot be unconfigured from a cluster.");
            status = FRAMEWORK_ERROR_CANNOT_UNCONFIGURE_SUB_LOCATION;
        }
        else if (LOCATION_STAND_ALONE == currentLocationRole)
        {
            trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::unconfigureClusterSecondaryValidateStep : Stand Alone node cannot be unconfigured from Cluster.");
            status = FRAMEWORK_ERROR_CANNOT_UNCONFIGURE_STAND_ALONE_NODE;
        }
        else if ((LOCATION_SECONDARY_CLUSTER_PHASE_0 == currentLocationRole) || (LOCATION_SECONDARY_CLUSTER_PHASE_1 == currentLocationRole) || (LOCATION_SECONDARY_CLUSTER_PHASE_2 == currentLocationRole) || (LOCATION_SECONDARY_CLUSTER_PHASE_3 == currentLocationRole) || 
                (LOCATION_SECONDARY_REJOIN_PHASE_0 == currentLocationRole) || (LOCATION_SECONDARY_REJOIN_PHASE_1 == currentLocationRole) || (LOCATION_SECONDARY_REJOIN_PHASE_2 == currentLocationRole) || (LOCATION_SECONDARY_REJOIN_PHASE_3 == currentLocationRole))
        {
            trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::unconfigureClusterSecondaryValidateStep : Node is in the middle of cluster operation and cannot be unconfigured.");
            status = FRAMEWORK_ERROR_CANNOT_UNCONFIGURE_LOCATION_WITH_IN_CLUSTER_PHASES_ROLE;
        }
        else
        {
            trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::unconfigureClusterSecondaryValidateStep : Location with unknown role cannot be unconfigured from cluster.");
            status = FRAMEWORK_ERROR_CANNOT_UNCONFIGURE_LOCATION_WITH_UNKNOWN_ROLE;
        }
    }

    pDeleteNodeOnSecondaryContext->executeNextStep (status);
}

void WaveFrameworkObjectManager::unconfigureClusterSecondarySendStopHeartBeat (DeleteNodeOnSecondaryContext *pDeleteNodeOnSecondaryContext)
{
    LocationId primaryNodeLocationId = m_pThisLocation->getClusterPrimaryLocationId();
    string     primaryNodeIpAddress  = m_pThisLocation->getIpAddressForLocationId(primaryNodeLocationId);
    UI32       primaryNodePort       = m_pThisLocation->getClusterPrimaryPort();

    StopHeartBeatMessage *pStopHeartBeatMessage = new StopHeartBeatMessage();
    pStopHeartBeatMessage->setDstIpAddress(primaryNodeIpAddress);
    pStopHeartBeatMessage->setDstPortNumber(primaryNodePort);
   
    WaveMessageStatus status = sendSynchronously(pStopHeartBeatMessage);
    ResourceId        processingStatus = WAVE_MESSAGE_SUCCESS;

    if(WAVE_MESSAGE_SUCCESS != status) 
    {
       processingStatus = status;
    }
    else 
    {
       ResourceId    completionStatus = pStopHeartBeatMessage->getCompletionStatus();
       if(completionStatus != WAVE_MESSAGE_SUCCESS) 
       {
         processingStatus = completionStatus;
       }
    }

    if(WAVE_MESSAGE_SUCCESS !=  processingStatus) 
    {
        /* log error and continue */
        trace(TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::unconfigureClusterSecondarySendStopHeartBeat:Failure sending StopHeartBeatMessage: status: " + FrameworkToolKit::localize(processingStatus));
        processingStatus = WAVE_MESSAGE_SUCCESS;
    }

    delete pStopHeartBeatMessage;
    pDeleteNodeOnSecondaryContext->executeNextStep(processingStatus);
}

void WaveFrameworkObjectManager::unconfigureClusterSecondaryDisconnectFromKnownLocationStep (DeleteNodeOnSecondaryContext *pDeleteNodeOnSecondaryContext)
{
    vector<LocationId> knownLocationsVector;
    LocationId         nodeLocationId;
    UI32               nodeCount;
    UI32               totalNodes               = 0;

    FrameworkToolKit::getKnownLocations (knownLocationsVector);
    totalNodes = knownLocationsVector.size ();

    for (nodeCount = 0; nodeCount < totalNodes; nodeCount++)
    {
        nodeLocationId = knownLocationsVector[nodeCount];
        disconnectFromLocation (nodeLocationId);
        removeKnownLocation    (nodeLocationId);

        pDeleteNodeOnSecondaryContext->addKnownLocationId (nodeLocationId);

        trace (TRACE_LEVEL_INFO, string ("WaveFrameworkObjectManager::unconfigureClusterSecondaryDisconnectFromKnownLocation ") + nodeLocationId);
    }


    pDeleteNodeOnSecondaryContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::unconfigureClusterSecondaryDisconnectFromConnectedLocationStep (DeleteNodeOnSecondaryContext *pDeleteNodeOnSecondaryContext)
{
    vector<LocationId> connectedLocationsVector;
    LocationId         nodeLocationId;
    UI32               nodeCount;
    UI32               totalNodes               = 0;

    FrameworkToolKit::getConnectedLocations (connectedLocationsVector);
    totalNodes = connectedLocationsVector.size ();

    for (nodeCount = 0; nodeCount < totalNodes; nodeCount++)
    {
        nodeLocationId = connectedLocationsVector[nodeCount];
        disconnectFromLocation (nodeLocationId);
        removeKnownLocation    (nodeLocationId);

        pDeleteNodeOnSecondaryContext->addKnownLocationId (nodeLocationId);

        trace (TRACE_LEVEL_INFO, string ("WaveFrameworkObjectManager::unconfigureClusterSecondaryDisconnectFromConnectedLocation ")+nodeLocationId);
    }

    vector<LocationId> knownLocationsVector;

    FrameworkToolKit::getKnownLocations (knownLocationsVector);
    totalNodes = knownLocationsVector.size ();
    
    for (nodeCount = 0; nodeCount < totalNodes; nodeCount++)
    {
        nodeLocationId = knownLocationsVector[nodeCount];
        removeKnownLocation    (nodeLocationId);
        pDeleteNodeOnSecondaryContext->addKnownLocationId (nodeLocationId);

        trace (TRACE_LEVEL_INFO, string ("WaveFrameworkObjectManager::unconfigureClusterSecondaryRemovedFromKnownLocation ")+nodeLocationId);

    }

    pDeleteNodeOnSecondaryContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::unconfigureClusterSecondaryUpdateThisLocationStep (DeleteNodeOnSecondaryContext *pDeleteNodeOnSecondaryContext)
{
    LocationId         thisLocationId           = FrameworkToolKit::getThisLocationId ();

    m_pThisLocation->resetLocationToStandAlone (thisLocationId);

    pDeleteNodeOnSecondaryContext->executeNextStep (WAVE_MESSAGE_SUCCESS);

}
void WaveFrameworkObjectManager::unconfigureClusterSecondaryNodeBootServicesStep (DeleteNodeOnSecondaryContext *pDeleteNodeOnSecondaryContext)
{
    ResourceId status = WAVE_MESSAGE_SUCCESS;

    if (true == pDeleteNodeOnSecondaryContext->getIsStartServiceIsRequired ())
    {
        status = m_pInitializeWorker->startWaveServices (WAVE_BOOT_SECONDARY_UNCONFIGURE);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::unconfigureClusterSecondaryNodeBootServicesStep starting of service should never fail");
            waveAssert (false, __FILE__, __LINE__);
        }
    }

    pDeleteNodeOnSecondaryContext->executeNextStep (status);
}
void WaveFrameworkObjectManager::unconfigureClusterBroadcastLocalNodeDeletedEventStep (DeleteNodeOnSecondaryContext *pDeleteNodeOnSecondaryContext)
{
    trace(TRACE_LEVEL_DEVEL, "Entering rismFrameworkObjectManager::unconfigureClusterBroadcastLocalNodeDeletedEventStep");
    WaveNodeLocalNodeDeletedEvent* pWaveNodeLocalNodeDeletedEvent = new WaveNodeLocalNodeDeletedEvent();

    ResourceId status =  broadcast(pWaveNodeLocalNodeDeletedEvent);

    if (WAVE_MESSAGE_SUCCESS != status) 
    {
       trace(TRACE_LEVEL_ERROR, "Entering rismFrameworkObjectManager::unconfigureClusterBroadcastLocalNodeDeletedEventStep:Broadcast Failed");
    }

    pDeleteNodeOnSecondaryContext->executeNextStep (status);
}

void WaveFrameworkObjectManager::unconfigureClusterSecondaryUnconfigureThisLocationStep (DeleteNodeOnSecondaryContext *pDeleteNodeOnSecondaryContext)
{
    LocationId         thisNodeLocationId           = FrameworkToolKit::getThisLocationId ();
    string             thisNodeIpAddress            = FrameworkToolKit::getThisLocationIpAddress();
    UI32               thisNodePort                 = FrameworkToolKit::getThisLocationPort();

    ClusterLocalReportRemovedNodeFromClusterMessage message(thisNodeIpAddress, thisNodePort, thisNodeLocationId);

    //Sending the message to Local Cluster Service
    WaveMessageStatus status = sendSynchronously (&message, thisNodeLocationId);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::unconfigureClusterSecondaryUnconfigureThisLocationStep : Local Cluster failed to process report indicting that the node is removed from the cluster.  Proceeding anyway. Status = ") + status);
    }
    else
    {
        ResourceId completionStatus = message.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS == completionStatus)
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::unconfigureClusterSecondaryUnconfigureThisLocationStep : Local Cluster succeeded to process report indicting that the node is removed from the cluster.");
        }
        else
        {
            trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::unconfigureClusterSecondaryUnconfigureThisLocationStep : Local Cluster failed to process report indicting that the node is removed from the cluster.  Proceeding anyway. Completion Status = ") + completionStatus);
        }
    }

    pDeleteNodeOnSecondaryContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::unconfigureClusterSecondaryRunFailoverStep (DeleteNodeOnSecondaryContext *pDeleteNodeOnSecondaryContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::unconfigureClusterSecondaryRunFailoverStep : Entering ...");
    
    WaveNode                        *pNode = NULL;
    set<LocationId>                 locationIdSet;
    set<LocationId>::iterator       it;
    UI32                            i = 0; 
    
    WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext = new WaveFrameworkFailoverWorkerContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveFrameworkObjectManager::unconfigureClusterSecondaryRunFailoverCallback), pDeleteNodeOnSecondaryContext);

    waveAssert (NULL != pWaveFrameworkFailoverWorkerContext, __FILE__, __LINE__);
    waveAssert (NULL != m_pWaveFrameworkFailoverWorker, __FILE__, __LINE__);

    vector<WaveManagedObject *> *pResults = querySynchronously (WaveNode::getClassName ());
    waveAssert (NULL != pResults, __FILE__, __LINE__);    

    UI32 totalWaveNodes = pResults->size ();
    vector<LocationId> locationIdVector    = pDeleteNodeOnSecondaryContext->getKnownLocationId();
    UI32               noOfFailedLocations = locationIdVector.size ();

    if (totalWaveNodes != noOfFailedLocations)
    {
        trace (TRACE_LEVEL_WARN, "WaveFrameworkObjectManager::unconfigureClusterSecondaryRunFailoverStep: Total wave nodes does not match with the known locations");
    }

    if (1 > totalWaveNodes)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::unconfigureClusterSecondaryRunFailoverStep: Wave node does not have itself in the database");
        waveAssert (false, __FILE__, __LINE__);
    }

    //Perform a union of locationId from known location and wave node
    //set will not allow duplicate entries, so it is ok to insert the same locationId twice
    for (i = 0; i < noOfFailedLocations; i++)
    {
        locationIdSet.insert (locationIdVector[i]);
    }

    for (i = 0; i < totalWaveNodes; i++)
    {
        pNode       = dynamic_cast<WaveNode *> ((*pResults)[i]);

        locationIdSet.insert (pNode->getLocationId ());
    }

    WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector (pResults);

    LocationId locationId = 0;
    for (it = locationIdSet.begin (); it != locationIdSet.end (); it++)
    {
        locationId = *it;

        if (locationId != FrameworkToolKit::getThisLocationId ())
        {
            pWaveFrameworkFailoverWorkerContext->addFailedLocationId (locationId);
        }
    }

    WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector (pResults);

    pWaveFrameworkFailoverWorkerContext->setThisLocationRole (LOCATION_SECONDARY);
    pWaveFrameworkFailoverWorkerContext->setFailoverReason (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_CONTROLLED);

    m_pWaveFrameworkFailoverWorker->executeFailover (pWaveFrameworkFailoverWorkerContext);

}

void WaveFrameworkObjectManager::unconfigureClusterSecondaryRunFailoverCallback (WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::unconfigureClusterSecondaryRunFailoverCallback : Entering ...");

    waveAssert (NULL != pWaveFrameworkFailoverWorkerContext, __FILE__, __LINE__);

    DeleteNodeOnSecondaryContext *pDeleteNodeOnSecondaryContext = reinterpret_cast<DeleteNodeOnSecondaryContext *> (pWaveFrameworkFailoverWorkerContext->getPCallerContext ());
    ResourceId                   status                       = pWaveFrameworkFailoverWorkerContext->getCompletionStatus ();

    delete pWaveFrameworkFailoverWorkerContext;

    waveAssert (NULL != pDeleteNodeOnSecondaryContext, __FILE__, __LINE__);

    pDeleteNodeOnSecondaryContext->executeNextStep (status);
}

void WaveFrameworkObjectManager::destroyClusterMessageHandler (FrameworkObjectManagerDestroyClusterMessage *pFrameworkObjectManagerDestroyClusterMessage)
{
    DestroyClusterAsynchronousContext *pDestroyClusterAsynchronousContext = new DestroyClusterAsynchronousContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveFrameworkObjectManager::destroyClusterMessageHandlerCallback), pFrameworkObjectManagerDestroyClusterMessage);

    pDestroyClusterAsynchronousContext->setReasonForDestroyingCluster (pFrameworkObjectManagerDestroyClusterMessage->getReasonForDestroyingCluster ());
    pDestroyClusterAsynchronousContext->setOriginalRequester          (pFrameworkObjectManagerDestroyClusterMessage->getOriginalRequester ());
    pDestroyClusterAsynchronousContext->setIsRebootRequired           (pFrameworkObjectManagerDestroyClusterMessage->getIsRebootRequired ());

    destroyClusterAsynchronousHandler (pDestroyClusterAsynchronousContext);
}

void WaveFrameworkObjectManager::destroyClusterMessageHandlerCallback (DestroyClusterAsynchronousContext *pDestroyClusterAsynchronousContext)
{
    waveAssert (NULL !=  pDestroyClusterAsynchronousContext, __FILE__, __LINE__);

    FrameworkObjectManagerDestroyClusterMessage *pFrameworkObjectManagerDestroyClusterMessage = reinterpret_cast<FrameworkObjectManagerDestroyClusterMessage *> (pDestroyClusterAsynchronousContext->getPCallerContext ());

    waveAssert (NULL != pFrameworkObjectManagerDestroyClusterMessage, __FILE__, __LINE__);

    pFrameworkObjectManagerDestroyClusterMessage->setCompletionStatus (pDestroyClusterAsynchronousContext->getCompletionStatus ());

    delete pDestroyClusterAsynchronousContext;

    reply (pFrameworkObjectManagerDestroyClusterMessage);
}

void WaveFrameworkObjectManager::destroyClusterAsynchronousHandler (DestroyClusterAsynchronousContext *pDestroyClusterAsynchronousContext)
{
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::destroyClusterValidateStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::destroyClusterGetKnownLocationsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::destroyClusterUnconfigureKnownLocationsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::destroyClusterDeleteHeartBeatToKnownLocationsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::destroyClusterTerminateClientConnectionsForKnownLocationsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::destroyClusterRemoveKnownLocationsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::destroyClusterUnconfigureSelfStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::destroyClusterRunFailoverStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::destroyClusterBroadcastDeleteClusterEventStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerFailedStep),
    };

    DestroyClusterContext *pDestroyClusterContext = new DestroyClusterContext (pDestroyClusterAsynchronousContext, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pDestroyClusterContext->setReasonForDestroyingCluster       (pDestroyClusterAsynchronousContext->getReasonForDestroyingCluster ());
    pDestroyClusterContext->setIsRebootRequired                 (pDestroyClusterAsynchronousContext->getIsRebootRequired ());

    pDestroyClusterContext->holdAll ();
    pDestroyClusterContext->start ();
}

void WaveFrameworkObjectManager::destroyClusterValidateStep (DestroyClusterContext *pDestroyClusterContext)
{
    LocationRole locationRole = m_pThisLocation->getLocationRole ();

    pDestroyClusterContext->setThisLocationRoleBeforeDestroy (locationRole);

    if (LOCATION_PRIMARY != locationRole)
    {
        if (LOCATION_STAND_ALONE == locationRole)
        {
            pDestroyClusterContext->executeNextStep (WAVE_CLUSTER_DELETE_STATUS_CLUSTER_NOT_FOUND);
        }
        else
        {
            pDestroyClusterContext->executeNextStep (FRAMEWORK_ERROR_ONLY_PRIMARY_LOCATION_CAN_DESTROY_CLUSTER);
        }
    }
    else
    {
        pDestroyClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
}

void WaveFrameworkObjectManager::destroyClusterGetKnownLocationsStep (DestroyClusterContext *pDestroyClusterContext)
{
    vector<LocationId> remoteLocationIdsVector;
    UI32               numberOfRemoteLocationIds;
    UI32               i;

    FrameworkToolKit::getKnownRemoteLocations (remoteLocationIdsVector);
    numberOfRemoteLocationIds = remoteLocationIdsVector.size ();

    for (i = 0; i < numberOfRemoteLocationIds; i++)
    {
        pDestroyClusterContext->addLocationId (remoteLocationIdsVector[i]);
    }

    pDestroyClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::destroyClusterUnconfigureKnownLocationsStep (DestroyClusterContext *pDestroyClusterContext)
{
    UI32             numberOfLocationIds = pDestroyClusterContext->getNumberOfLocationIds ();
    LocationId       locationId          = 0;
    UI32             i                   = 0;
    WaveMessageStatus messageStatus       = WAVE_MESSAGE_SUCCESS;
    string           ipAddress           = "";
    SI32             port                = 0 ;

    ++(*pDestroyClusterContext);

    for (i = 0; i < numberOfLocationIds; i++)
    {
        locationId = pDestroyClusterContext->getLocationIdAt (i);
        ipAddress  = FrameworkToolKit::getIpAddressForLocationId (locationId);
        port       = FrameworkToolKit::getPortForLocationId (locationId);

        FrameworkObjectManagerUnconfigureClusterSecondaryMessage *pMessage = new FrameworkObjectManagerUnconfigureClusterSecondaryMessage (ipAddress, port);

        waveAssert (NULL != pMessage, __FILE__, __LINE__);

        messageStatus = send (pMessage, reinterpret_cast<WaveMessageResponseHandler> (&WaveFrameworkObjectManager::destroyClusterUnconfigureKnownLocationsCallback), pDestroyClusterContext, 10000, locationId);

        if (WAVE_MESSAGE_SUCCESS == messageStatus)
        {
            ++(*pDestroyClusterContext);
        }
        else
        {
            trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::destroyClusterUnconfigureKnownLocationsStep : Could not send a message to unconfigure a known location : ") + locationId + string (" : Status : ") + messageStatus);
            delete pMessage;
        }
    }

    --(*pDestroyClusterContext);
    pDestroyClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);

}

void WaveFrameworkObjectManager::destroyClusterUnconfigureKnownLocationsCallback (FrameworkStatus frameworkStatus, FrameworkObjectManagerUnconfigureClusterSecondaryMessage *pFrameworkObjectManagerUnconfigureClusterSecondaryMessage, void *pContext)
{
    DestroyClusterContext *pDestroyClusterContext = reinterpret_cast<DestroyClusterContext *> (pContext);

    if (FRAMEWORK_SUCCESS == frameworkStatus)
    {
        ResourceId completionStatus = pFrameworkObjectManagerUnconfigureClusterSecondaryMessage->getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != completionStatus)
        {
            trace (TRACE_LEVEL_WARN, string ("WaveFrameworkObjectManager::destroyClusterUnconfigureKnownLocationsCallback : Error in unconfiguring a location. Completion Status : ") + completionStatus);
        }
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::destroyClusterUnconfigureKnownLocationsCallback : Error in unconfiguring a location. Framework Status : ") + frameworkStatus);
    }

    if (NULL != pFrameworkObjectManagerUnconfigureClusterSecondaryMessage)
    {
        delete pFrameworkObjectManagerUnconfigureClusterSecondaryMessage;
    }

    --(*pDestroyClusterContext);
    pDestroyClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::destroyClusterDeleteHeartBeatToKnownLocationsStep (DestroyClusterContext *pDestroyClusterContext)
{
    UI32        numberOfLocationIds = pDestroyClusterContext->getNumberOfLocationIds ();
    LocationId  locationId          = 0;
    UI32        i                   = 0;
    string      ipAddress           = "";
    SI32        port                = 0;
    ResourceId  status              = WAVE_MESSAGE_SUCCESS;
    LocationId  thisLocationId      = FrameworkToolKit::getThisLocationId ();

    for (i = 0; i < numberOfLocationIds; i++)
    {
        locationId = pDestroyClusterContext->getLocationIdAt     (i);
        ipAddress  = FrameworkToolKit::getIpAddressForLocationId (locationId);
        port       = FrameworkToolKit::getPortForLocationId      (locationId);

        StopHeartBeatMessage stopHeartBeatMessage;
        IpV4Address          ip (ipAddress);

        stopHeartBeatMessage.setDstIpAddress       (ip);
        stopHeartBeatMessage.setDstPortNumber      (port);

        status = sendSynchronously (&stopHeartBeatMessage, thisLocationId);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::destroyClusterDeleteHeartBeatToKnownLocationsStep : Could not send a message to stop heart beat message for " + ipAddress + ":" + port + ", Error = " + FrameworkToolKit::localize (status));
        }

        status = stopHeartBeatMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::destroyClusterDeleteHeartBeatToKnownLocationsStep : Could not stop Heart Beat to " + ipAddress + ":" + port + ", Error = " + FrameworkToolKit::localize (status));
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::destroyClusterDeleteHeartBeatToKnownLocationsStep :  stopped Heart Beat to " + ipAddress + ":" + port);
        }
    }

    pDestroyClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::destroyClusterTerminateClientConnectionsForKnownLocationsStep (DestroyClusterContext *pDestroyClusterContext)
{
    UI32       numberOfLocationIds      = pDestroyClusterContext->getNumberOfLocationIds ();
    LocationId locationId               = 0;
    UI32       i                        = 0;
    string     ipAddress                = "";
    SI32       port                     = 0;
    string     clusterPrimaryIpAddress  = "";
    SI32       clusterPrimaryPort       = -1;
    bool       isPreparingForAddNode    = false;

    DestroyClusterAsynchronousContext *pDestroyClusterAsynchronousContext = reinterpret_cast<DestroyClusterAsynchronousContext *> (pDestroyClusterContext->getPWaveAsynchronousContext ());

    isPreparingForAddNode = pDestroyClusterAsynchronousContext->getIsPreparingForAddNode ();

    if (true == isPreparingForAddNode)
    {
        SecondaryNodeClusterContext *pSecondaryNodeClusterContext = reinterpret_cast<SecondaryNodeClusterContext *> (pDestroyClusterAsynchronousContext->getPCallerContext ()); 

        WaveConfigureClusterSecondaryMessage *pWaveConfigureClusterSecondaryMessage = reinterpret_cast<WaveConfigureClusterSecondaryMessage *> (pSecondaryNodeClusterContext->getPWaveMessage ());

        clusterPrimaryIpAddress = pWaveConfigureClusterSecondaryMessage->getClusterPrimaryIpAddress ();
        clusterPrimaryPort      = pWaveConfigureClusterSecondaryMessage->getClusterPrimaryPort ();
    }

    for (i = 0; i < numberOfLocationIds; i++)
    {
        locationId = pDestroyClusterContext->getLocationIdAt (i);
        ipAddress  = FrameworkToolKit::getIpAddressForLocationId (locationId);
        port       = FrameworkToolKit::getPortForLocationId (locationId);

        if (false == isPreparingForAddNode || (clusterPrimaryIpAddress != ipAddress && clusterPrimaryPort != port))
        {
            InterLocationMessageReceiverObjectManager::terminateAndRemoveInterLocationMessageReceiverThreadFromCache (ipAddress, port);
        }
    }

    pDestroyClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::destroyClusterRemoveKnownLocationsStep (DestroyClusterContext *pDestroyClusterContext)
{
    UI32       numberOfLocationIds      = pDestroyClusterContext->getNumberOfLocationIds ();
    LocationId locationId               = 0;
    UI32       i                        = 0;
    string     ipAddress                = "";
    string     clusterPrimaryIpAddress  = "";
    SI32       clusterPrimaryPort       = -1;
    bool       isPreparingForAddNode    = false;

    DestroyClusterAsynchronousContext *pDestroyClusterAsynchronousContext = reinterpret_cast<DestroyClusterAsynchronousContext *> (pDestroyClusterContext->getPWaveAsynchronousContext ()); 

    isPreparingForAddNode = pDestroyClusterAsynchronousContext->getIsPreparingForAddNode ();

    if (true == isPreparingForAddNode)
    {    
        SecondaryNodeClusterContext *pSecondaryNodeClusterContext = reinterpret_cast<SecondaryNodeClusterContext *> (pDestroyClusterAsynchronousContext->getPCallerContext ()); 

        WaveConfigureClusterSecondaryMessage *pWaveConfigureClusterSecondaryMessage = reinterpret_cast<WaveConfigureClusterSecondaryMessage *> (pSecondaryNodeClusterContext->getPWaveMessage ()); 

        clusterPrimaryIpAddress = pWaveConfigureClusterSecondaryMessage->getClusterPrimaryIpAddress ();
        clusterPrimaryPort      = pWaveConfigureClusterSecondaryMessage->getClusterPrimaryPort ();
    }    

    for (i = 0; i < numberOfLocationIds; i++)
    {
        locationId = pDestroyClusterContext->getLocationIdAt (i);
        ipAddress  = FrameworkToolKit::getIpAddressForLocationId (locationId);
        SI32 port  = FrameworkToolKit::getPortForLocationId (locationId);

        if (false == isPreparingForAddNode || (clusterPrimaryIpAddress != ipAddress && clusterPrimaryPort != port))
        {
           disconnectFromLocation (locationId);
        }

        removeKnownLocation (locationId);
    }

    pDestroyClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::destroyClusterUnconfigureSelfStep (DestroyClusterContext *pDestroyClusterContext)
{
    LocationId thisLocationId = FrameworkToolKit::getThisLocationId ();

    m_pThisLocation->resetLocationToStandAlone (thisLocationId);

    pDestroyClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::destroyClusterRunFailoverStep (DestroyClusterContext *pDestroyClusterContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::destroyClusterRunFailoverStep : Entering ...");

    DestroyClusterAsynchronousContext *pDestroyClusterAsynchronousContext = reinterpret_cast<DestroyClusterAsynchronousContext *> (pDestroyClusterContext->getPWaveAsynchronousContext ());

    WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext = new WaveFrameworkFailoverWorkerContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveFrameworkObjectManager::destroyClusterRunFailoverCallback), pDestroyClusterContext);

    waveAssert (NULL != pWaveFrameworkFailoverWorkerContext, __FILE__, __LINE__);
    waveAssert (NULL != m_pWaveFrameworkFailoverWorker, __FILE__, __LINE__);

    UI32 numberOfLocationIds = pDestroyClusterContext->getNumberOfLocationIds ();
    UI32 i                   = 0;
    LocationId locationId;


    for (i = 0; i < numberOfLocationIds; i++)
    {
        locationId = pDestroyClusterContext->getLocationIdAt (i);
        pWaveFrameworkFailoverWorkerContext->addFailedLocationId (locationId);
    }

    pWaveFrameworkFailoverWorkerContext->setThisLocationRole (pDestroyClusterContext->getThisLocationRoleBeforeDestroy ());
    pWaveFrameworkFailoverWorkerContext->setFailoverReason (pDestroyClusterContext->getReasonForDestroyingCluster ());
    pWaveFrameworkFailoverWorkerContext->setServiceToBeIgnored (pDestroyClusterAsynchronousContext->getOriginalRequester ());

    m_pWaveFrameworkFailoverWorker->executeFailover (pWaveFrameworkFailoverWorkerContext);
}

void WaveFrameworkObjectManager::destroyClusterRunFailoverCallback (WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::destroyClusterRunFailoverCallback : Entering ...");

    waveAssert (NULL != pWaveFrameworkFailoverWorkerContext, __FILE__, __LINE__);

    DestroyClusterContext *pDestroyClusterContext = reinterpret_cast<DestroyClusterContext *> (pWaveFrameworkFailoverWorkerContext->getPCallerContext ());
    ResourceId             status                 = pWaveFrameworkFailoverWorkerContext->getCompletionStatus ();

    delete pWaveFrameworkFailoverWorkerContext;

    waveAssert (NULL != pDestroyClusterContext, __FILE__, __LINE__);

    pDestroyClusterContext->executeNextStep (status);
}

void WaveFrameworkObjectManager::destroyClusterBroadcastDeleteClusterEventStep (DestroyClusterContext *pDestroyClusterContext)
{
    trace(TRACE_LEVEL_INFO, "Entering WaveFrameworkObjectManager::destroyClusterBroadcastDeleteClusterEventStep");

    WaveNodeDeleteClusterEvent* pWaveNodeDeleteClusterEvent = new WaveNodeDeleteClusterEvent ();

    pWaveNodeDeleteClusterEvent->setIsRebootRequired (pDestroyClusterContext->getIsRebootRequired ());

    ResourceId status =  broadcast(pWaveNodeDeleteClusterEvent);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
       trace(TRACE_LEVEL_ERROR, "Entering WaveFrameworkObjectManager::destroyClusterBroadcastDeleteClusterEventStep Broadcast Failed");
    }

    pDestroyClusterContext->executeNextStep (status);

}

/// Name
/// rejoinNodesToClusterMessageHandler
/// Description
/// This function lays down the steps for procssing (within the f/w) the Rejoin 
/// request received from the Cluster service on the Primary. It also creates the context 
/// and starts the processing.
///  Input
/// FrameworkObjectManagerRejoinNodesToClusterMessage: Pointer to message
/// received from the Global Cluster service 
/// Output
/// none
/// Return
/// none
void WaveFrameworkObjectManager::rejoinNodesToClusterMessageHandler (FrameworkObjectManagerRejoinNodesToClusterMessage *pFrameworkObjectManagerRejoinNodesToClusterMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinNodesToClusterValidateStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesCollectValidationDataStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesPausePersistenceStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinNodesToClusterConnectToNodesStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesPhase1Step),


        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesResumeDatabaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesPhase2Step),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesSendValidationResultsStep), 
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::createClusterWithNodesSendListOfSecondariesToAllNodesStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::broadcastNewNodesAddedEventOnPrimaryStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::sendReplyBackToClusterGlobalService),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::failoverforNodesFailedInRejoinPhase2),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesPhase3Step),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::startHeartBeatToSecondaryNodes),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::broadcastClusterPhase3CompleteEvent),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::broadcastNodesAdditionToClusterCompletedEvent),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::primaryNodeClusterSuccessStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::primaryNodeClusterFailureStep),
    };

    //This memory is freed within the Framework as part of prsimLinearSequencerSucceeded or
    //prismLinearSequencerFailedStep
    RejoinNodesToClusterContext *pRejoinNodesToClusterContext = new RejoinNodesToClusterContext (pFrameworkObjectManagerRejoinNodesToClusterMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));
    // Set an indication that cluster operation is in progress on primary node
    setPrimaryNodeClusterOperationFlag (true);

    // The flag is set here to avoid the default setting in base cluster context creation
    // which causes the previous state of the flag to be lost upon controlled failover.
    setSecondaryNodeClusterCreationFlag (false);
    
    pRejoinNodesToClusterContext->holdAll ();
    pRejoinNodesToClusterContext->start ();
}

/// Name
/// rejoinNodesToClusterValidateStep
/// Description
/// This function validates the rejoin Node request received from the cluster.
/// It essentially looks at every node in the request and adds it to the context 
/// only if it is a know location
///  Input
/// RejoinNodesToClusterContext:pointer for  context for rejoin created in
/// in the handler
/// Output
/// none
/// Return
/// none
/// 
void WaveFrameworkObjectManager::rejoinNodesToClusterValidateStep (RejoinNodesToClusterContext *pRejoinNodesToClusterContext)
{
    FrameworkObjectManagerRejoinNodesToClusterMessage *pFrameworkObjectManagerRejoinNodesToClusterMessage = dynamic_cast<FrameworkObjectManagerRejoinNodesToClusterMessage *> (pRejoinNodesToClusterContext->getPWaveMessage ());

    waveAssert(NULL != pFrameworkObjectManagerRejoinNodesToClusterMessage, __FILE__, __LINE__);

    UI32                                               numberOfNodes                                      = pFrameworkObjectManagerRejoinNodesToClusterMessage->getNumberOfNodes (); 
    UI32                                               numberOfFailures                                   = 0;

    //The location of all nodes in the message should already be known to the primary
    // as the REjoining node was part of the cluster earlier
    for (UI32 i = 0; i < numberOfNodes; i++)
    {
        string ipAddress = pFrameworkObjectManagerRejoinNodesToClusterMessage->getNodeAt (i);
        UI32 port = pFrameworkObjectManagerRejoinNodesToClusterMessage->getNodePortAt (i);

        if (true == (FrameworkToolKit::isAKnownLocation (ipAddress, port)))
        {
            pRejoinNodesToClusterContext->addLocationId (FrameworkToolKit::getLocationIdForIpAddressAndPort (ipAddress, port));
        }
        else
        {
            if (true == pFrameworkObjectManagerRejoinNodesToClusterMessage->getIsReplaceRejoin ())
            {
                LocationId replacedLocationId = pFrameworkObjectManagerRejoinNodesToClusterMessage->getNodeLocationId (i);

                // Remove the old binding of location to IP address
                removeKnownLocation (replacedLocationId);

                // Recreate binding of same location to IP address
                m_pThisLocation->addKnownLocation (replacedLocationId, ipAddress, port);
                pRejoinNodesToClusterContext->addLocationId (replacedLocationId);

                #if 0
                // Create a new location with new IP and port
                LocationId newLocationId = getNextLocationId ();

                if (0 != newLocationId)
                {
                    m_pThisLocation->addKnownLocation (newLocationId, ipAddress, port);
                    pRejoinNodesToClusterContext->addLocationId (newLocationId);
                }
                else
                {
                    pFrameworkObjectManagerRejoinNodesToClusterMessage->setNodeStatus (ipAddress, port, FRAMEWORK_ERROR_NO_UNUSED_LOCATION_IDS_AVAILABLE);
                    numberOfFailures++;
                }
                #endif
            }
            else
            {
                pFrameworkObjectManagerRejoinNodesToClusterMessage->setNodeStatus (ipAddress, port, FRAMEWORK_ERROR_CANNOT_REJOIN_NODE_TO_CLUSTER_NOT_A_KNOWN_LOCATION);
                numberOfFailures++;
            }
        }
    }

    //If there is no known  node in the request signal a failure. Even if one node is valid we will
    //process the request
    if (numberOfFailures == numberOfNodes)
    {
        pRejoinNodesToClusterContext->executeNextStep (FRAMEWORK_ERROR_CANNOT_REJOIN_NODES_TO_CLUSTER_NO_VALID_RESOURCES);
    }
    else
    {
        pRejoinNodesToClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }

    return;
}


/// Name
/// rejoinNodesToClusterConnectToNodesStep
/// Description
/// This function establishes a connection with every known location in the
/// RejoinContext
///  Input
/// RejoinNodesToClusterContext:pointer for  context for rejoin created in
/// in the handler
/// Output
/// none
/// Return
/// none

void WaveFrameworkObjectManager::rejoinNodesToClusterConnectToNodesStep (RejoinNodesToClusterContext *pRejoinNodesToClusterContext)
{
    static const UI32  maximumNumberOfRetriesToConnectToARemoteLocation   = 30;
    static const UI32  maximumNumberOfSecondsToWaitToConnect              = 30;

    FrameworkObjectManagerRejoinNodesToClusterMessage *pFrameworkObjectManagerRejoinNodesToClusterMessage = dynamic_cast<FrameworkObjectManagerRejoinNodesToClusterMessage *> (pRejoinNodesToClusterContext->getPWaveMessage ());

    waveAssert(NULL != pFrameworkObjectManagerRejoinNodesToClusterMessage, __FILE__, __LINE__);

    UI32  numberOfLocationIds = pRejoinNodesToClusterContext->getNumberOfLocationIds ();    
    UI32  numberOfFailures    = 0;

    for (UI32 i = 0; i< numberOfLocationIds; ++i)
    {
        LocationId locationId = pRejoinNodesToClusterContext->getLocationIdAt (i);

        waveAssert (0 != locationId, __FILE__, __LINE__);

        string  ipAddress   = FrameworkToolKit::getIpAddressForLocationId (locationId);
        UI32    port        = FrameworkToolKit::getPortForLocationId (locationId);

        if (false == pFrameworkObjectManagerRejoinNodesToClusterMessage->isNewNodeStatusSet (ipAddress, port))
        {
            ResourceId status = m_pThisLocation->connectToRemoteLocation (locationId, maximumNumberOfRetriesToConnectToARemoteLocation, maximumNumberOfSecondsToWaitToConnect);

            if (FRAMEWORK_SUCCESS != status)
            {
                pFrameworkObjectManagerRejoinNodesToClusterMessage->setNodeStatus (ipAddress, port, status);
                numberOfFailures++;
            }
        }
        else
        {
            string traceString = string ("WaveFrameworkObjectManager::rejoinNodesToClusterConnectToNodesStep : locationId : ") + locationId + string ("already set with error status :") + FrameworkToolKit::localize (pFrameworkObjectManagerRejoinNodesToClusterMessage->getNewNodeStatus (ipAddress, port));
            trace (TRACE_LEVEL_INFO, traceString);
            numberOfFailures++;
        }
    }

    if (numberOfFailures == numberOfLocationIds)
    {
        resumePersistence ();

        pRejoinNodesToClusterContext->executeNextStep (FRAMEWORK_ERROR_FAILED_TO_CONECT_TO_ALL_NEW_LOCATIONS);
    }
    else
    {
        pRejoinNodesToClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
}


/// Name
/// rejoinNodesToClusterRejoinClusterSecondariesStep
/// Description
/// This function creates a rejoin message and sends it to the wave framework on 
/// every secondary node in the rejoin message. Along with the rejon message
/// it also sends the validation data for each service and the primary Database.
///  Input
/// RejoinNodesToClusterContext:pointer for  context for rejoin created in
/// in the handler
/// Output
/// none
/// Return
/// none

void WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesStep (RejoinNodesToClusterContext *pRejoinNodesToClusterContext)
{
    FrameworkObjectManagerRejoinNodesToClusterMessage *pFrameworkObjectManagerRejoinNodesToClusterMessage = dynamic_cast<FrameworkObjectManagerRejoinNodesToClusterMessage *> (pRejoinNodesToClusterContext->getPWaveMessage ());
 
    waveAssert (NULL != pFrameworkObjectManagerRejoinNodesToClusterMessage, __FILE__, __LINE__);

    WaveMessageStatus status  = WAVE_MESSAGE_ERROR;  
    string prismVersionString = WaveVersion::getVersionString ();

    ++(*pRejoinNodesToClusterContext);

    UI32        numberOfLocationIds     = pRejoinNodesToClusterContext->getNumberOfLocationIds ();
    string      thisLocationIpAddress   = FrameworkToolKit::getThisLocationIpAddress ();
    SI32        thisLocationPort        = FrameworkToolKit::getThisLocationPort ();
    LocationId  thisLocationId          = FrameworkToolKit::getThisLocationId ();
    UI32        numberOfFailures        = 0;

    // Add all the validation buffers to the message before sending out
    vector<WaveServiceId> &waveServiceIds                = pRejoinNodesToClusterContext->getWaveServiceIdsVector ();
    vector<void *>         &validationDetailsVector        = pRejoinNodesToClusterContext->getValidationDetailsVector ();
    vector<UI32>           &validationDetailsSizesVector   = pRejoinNodesToClusterContext->getValidationDetailsSizesVector ();
    UI32                    numberOfWaveServiceIds        = waveServiceIds.size ();
    UI32                    numberOfValidationDetails      = validationDetailsVector.size ();
    UI32                    numberOfValidationDetailsSizes = validationDetailsSizesVector.size ();

    waveAssert (numberOfWaveServiceIds == numberOfValidationDetails, __FILE__, __LINE__);
    waveAssert (numberOfWaveServiceIds == numberOfValidationDetailsSizes, __FILE__, __LINE__);

    //Sending the request to each secondary location
    for (UI32 i = 0; i < numberOfLocationIds; i++)
    {
        LocationId locationId = pRejoinNodesToClusterContext->getNewLocationIdAt ((UI32) i);
        string ipAddress     = FrameworkToolKit::getIpAddressForLocationId (locationId);
        SI32 port          = FrameworkToolKit::getPortForLocationId (locationId);

        // Rejoin messages sent only locations known to the primary. 

        if (true == (FrameworkToolKit::isAKnownLocation (ipAddress, port)) && (false == pFrameworkObjectManagerRejoinNodesToClusterMessage->isNewNodeStatusSet (ipAddress, port)))
        {
            FrameworkObjectManagerRejoinClusterSecondaryMessage *pMessage = new FrameworkObjectManagerRejoinClusterSecondaryMessage (prismVersionString, thisLocationIpAddress, thisLocationPort, thisLocationId, ipAddress, port, locationId);

            pMessage->setSchemaChangeVectors ();

            pMessage->setIsReplaceRejoin (pFrameworkObjectManagerRejoinNodesToClusterMessage->getIsReplaceRejoin ());

            if (true == FrameworkToolKit::isConfigurationCompatibilityCheckRequired ())
            {
                UI64      configurationTransactionId  = 0;
                DateTime  configurationTime;
                DateTime  latestUpdateTime;
                
                PersistenceToolKit::getConfigurationManagedObjectInformation (configurationTransactionId, configurationTime, latestUpdateTime); 

                vector<UI64> configurationNumber;

                configurationNumber.push_back (configurationTransactionId);

                pMessage->setConfigurationNumber (configurationNumber);
            }

            //For each location go through each serviceId and attach the validation data for each service 
            //to the message
            for (UI32 j = 0; j < numberOfWaveServiceIds; j++)
            {
                if ((0 != validationDetailsSizesVector[j]) && (NULL != validationDetailsVector[j]))
                {
                    pMessage->addBuffer (waveServiceIds[j], validationDetailsSizesVector[j], validationDetailsVector[j]);
                }
                else
                {
                    trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesStep : We could not have added an entry with 0 size and/or NULL validation buffer.");
                    waveAssert (false, __FILE__, __LINE__);
                }
            }

            pMessage->setToAllowSendForOneWayCommunication (true);

            //send the message and lodge a callback. Note that the processing is Asynchronous here
            status = send (pMessage, reinterpret_cast<WaveMessageResponseHandler> (&WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondaryCallback), pRejoinNodesToClusterContext, s_clusterPhase0TimeoutInMilliseconds, locationId);

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                //QUESTION: ASK SAGAR:No need to remove location
                pFrameworkObjectManagerRejoinNodesToClusterMessage->setNewNodeStatus (ipAddress, port, status);
                trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesStep: Not able to configure one secondary location : ") + locationId + string (" Error Code : ") + status);
                numberOfFailures++;
                delete pMessage;
            }
            else
            {
                 ++(*pRejoinNodesToClusterContext);
            }
        }
        else
        {
            numberOfFailures++;
        }
    }

    backUpDatabaseAfterSendingClusterPhase0Message ();

    --(*pRejoinNodesToClusterContext);

    //If there is a failure in sending a message to all locations
    //then mark a failure.
    if (numberOfFailures == numberOfLocationIds)
    {
        resumeDatabaseOperation ();
        
        pRejoinNodesToClusterContext->executeNextStep (FRAMEWORK_ERROR_FAILED_TO_CONFIGURE_ALL_NEW_LOCATIONS);
    }
    else
    {
        pRejoinNodesToClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }

}
/// Name
/// rejoinNodesToClusterRejoinClusterSecondaryCallback
/// Description
/// When the framework receives a reply from the secondary
/// it calls this callback.
///  Input
/// FrameworkStatus: success/failure in framework
/// FrameworkObjectManagerRejoinClusterSecondaryMessage: pointer to the message received back from the 
/// secondary in reply
/// RejoinNodesToClusterContext:pointer for  context for rejoin created in
/// the handler
/// Output
/// none
/// Return
/// none

void WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondaryCallback (FrameworkStatus frameworkStatus, FrameworkObjectManagerRejoinClusterSecondaryMessage *pFrameworkObjectManagerRejoinClusterSecondaryMessage, void *pContext)
{
    RejoinNodesToClusterContext  *pRejoinNodesToClusterContext = reinterpret_cast<RejoinNodesToClusterContext *> (pContext);

    FrameworkObjectManagerRejoinNodesToClusterMessage *pFrameworkObjectManagerRejoinNodesToClusterMessage = dynamic_cast<FrameworkObjectManagerRejoinNodesToClusterMessage *> (pRejoinNodesToClusterContext->getPWaveMessage ());

    waveAssert(NULL != pFrameworkObjectManagerRejoinNodesToClusterMessage,__FILE__,__LINE__);

    tracePrintf(TRACE_LEVEL_DEVEL,"WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondaryCallback:FrameworkStatus received:0x%x",frameworkStatus);
  
    --(*pRejoinNodesToClusterContext);

    if (FRAMEWORK_SUCCESS == frameworkStatus)
    {
        waveAssert (NULL != pFrameworkObjectManagerRejoinClusterSecondaryMessage, __FILE__, __LINE__);

        LocationId newLocationId    = pFrameworkObjectManagerRejoinClusterSecondaryMessage->getLocationId ();
        string     ipAddress        = FrameworkToolKit::getIpAddressForLocationId (newLocationId);
        SI32       port             = FrameworkToolKit::getPortForLocationId (newLocationId);
        ResourceId completionStatus = pFrameworkObjectManagerRejoinClusterSecondaryMessage->getCompletionStatus ();

        pFrameworkObjectManagerRejoinNodesToClusterMessage->setNodeStatus (ipAddress, port, completionStatus);

        if (WAVE_MESSAGE_SUCCESS == completionStatus) 
        {
            tracePrintf(TRACE_LEVEL_DEVEL,"WaveFrameworkObjectManager:rejoinNodesToClusterRejoinClusterSecondaryCallback:Wave Success received for Location Id %d",newLocationId);
        }
        else
        {
            trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager:rejoinNodesToClusterRejoinClusterSecondaryCallback, not able rejoin node ") + newLocationId + string (" failure reason is ") + FrameworkToolKit::localize (completionStatus));
        }
    }
    else
    {   
       trace(TRACE_LEVEL_DEVEL,"WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondaryCallback:Framework Failure received");

        //Note that a NULL message pointer can be received in case of a timeout. 
        if (NULL != pFrameworkObjectManagerRejoinClusterSecondaryMessage)
        {
           LocationId newLocationId    = pFrameworkObjectManagerRejoinClusterSecondaryMessage->getLocationId ();
           string     ipAddress        = FrameworkToolKit::getIpAddressForLocationId (newLocationId);
           SI32       port             = FrameworkToolKit::getPortForLocationId (newLocationId);

           pFrameworkObjectManagerRejoinNodesToClusterMessage->setNodeStatus (ipAddress, port, frameworkStatus);

           tracePrintf(TRACE_LEVEL_DEVEL,"WaveFrameworkObjectManager:rejoinNodesToClusterRejoinClusterSecondaryCallback:Framework Failure received for Location Id %d",newLocationId);
        }
    }

    //Release memory of the secondary message
    if (NULL != pFrameworkObjectManagerRejoinClusterSecondaryMessage)
    {
        delete pFrameworkObjectManagerRejoinClusterSecondaryMessage;
    }

    //If responses have been received from each secondary  then we are ready to evaluate 
    //whether the operation succeeded or not
    if (0 == (pRejoinNodesToClusterContext->getNumberOfCallbacksBeforeAdvancingToNextStep ()))
    {
        UI32 numberOfIpAddresses = pFrameworkObjectManagerRejoinNodesToClusterMessage->getNumberOfNodes (); 
        UI32 numberOfFailures = 0;

        //Loop thru all the nodes  and count the number of failures
        for (UI32 i = 0; i < numberOfIpAddresses; i++)
        {
            string ipAddress = pFrameworkObjectManagerRejoinNodesToClusterMessage->getNodeAt     ((UI32) i);
            SI32   port      = pFrameworkObjectManagerRejoinNodesToClusterMessage->getNodePortAt ((UI32) i);

            if (true != (pFrameworkObjectManagerRejoinNodesToClusterMessage->isNodeStatusSet (ipAddress, port)))
            {
                pFrameworkObjectManagerRejoinNodesToClusterMessage->setNodeStatus (ipAddress, port, FRAMEWORK_ERROR_REJOIN_NODES_TO_CLUSTER_REJOIN_SECONDARY_TIMED_OUT);
                disconnectFromLocation(ipAddress, port, true);

                numberOfFailures++;
            }
            else
            {
                if (WAVE_MESSAGE_SUCCESS != (pFrameworkObjectManagerRejoinNodesToClusterMessage->getNodeStatus (ipAddress, port)))
                {
                    disconnectFromLocation(ipAddress, port, true);
                    numberOfFailures++;
                }
            }
        }

        if (numberOfFailures == numberOfIpAddresses)
        {
            resumeDatabaseOperation ();
            
            pRejoinNodesToClusterContext->executeNextStep (FRAMEWORK_ERROR_FAILED_TO_REJOIN_ALL_LOCATIONS);
        }
        else
        {
            pRejoinNodesToClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        }
    }

}

void WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesPhase1Step (RejoinNodesToClusterContext *pRejoinNodesToClusterContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterecondariesPhase1Step : Entering ...");

    FrameworkObjectManagerRejoinNodesToClusterMessage *pFrameworkObjectManagerRejoinNodesToClusterMessage = dynamic_cast<FrameworkObjectManagerRejoinNodesToClusterMessage *> (pRejoinNodesToClusterContext->getPWaveMessage ());

    waveAssert (NULL != pFrameworkObjectManagerRejoinNodesToClusterMessage, __FILE__, __LINE__);

    SI32   sizeOfBackupFile                    = 0;
    char  *pDatabaseBackupBuffer               = NULL;
    ResourceId                          status                              = WAVE_MESSAGE_SUCCESS;
    UI32                                numberOfFailures                    = 0;
    UI32                                numberOfNewIpAddresses              = pFrameworkObjectManagerRejoinNodesToClusterMessage->getNumberOfNodes ();

    ++(*pRejoinNodesToClusterContext);

    createDatabaseBackupBuffer(pDatabaseBackupBuffer, sizeOfBackupFile);

    for (UI32 i = 0; i < numberOfNewIpAddresses; i++)
    {
        string ipAddress1         = pFrameworkObjectManagerRejoinNodesToClusterMessage->getNodeAt ((UI32) i);
        SI32 port1                = pFrameworkObjectManagerRejoinNodesToClusterMessage->getNodePortAt ((UI32) i);
        LocationId newLocationId1 = FrameworkToolKit::getLocationIdForIpAddressAndPort (ipAddress1, port1);

        // We will send  phase1 message only to the locations that are known to us at this point.
        // Only to those locations that are succeeded as part of phase 0.

        if (WAVE_MESSAGE_SUCCESS == (pFrameworkObjectManagerRejoinNodesToClusterMessage->getNewNodeStatus (ipAddress1, port1)))
        {
            WaveRejoinClusterSecondaryPhase1Message *pMessage = new WaveRejoinClusterSecondaryPhase1Message ();

            if (NULL != pDatabaseBackupBuffer)
            {
                pMessage->addBuffer (pMessage->getDatabaseBackupBufferTag (), sizeOfBackupFile, pDatabaseBackupBuffer, false);
            }
            else
            {
                trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesPhase1Step : No Database Backup is being sent to the lcoation.");
            }
   
            status = send (pMessage, reinterpret_cast<WaveMessageResponseHandler> (&WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesPhase1StepCallback), pRejoinNodesToClusterContext, s_clusterPhase1TimeoutInMilliseconds, newLocationId1);
    
            if (WAVE_MESSAGE_SUCCESS != status)
            {
                pFrameworkObjectManagerRejoinNodesToClusterMessage->updateNewNodeStatus (ipAddress1, port1, status);

                trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesPhase1Step : Not able to configure one secondary location During Phase 1: ") + newLocationId1 + string (" Status : ") + FrameworkToolKit::localize (status));

                numberOfFailures++;
                delete pMessage;
            }
            else
            {
                pFrameworkObjectManagerRejoinNodesToClusterMessage->updateNewNodeStatus (ipAddress1, port1, FRAMEWORK_ERROR_CREATE_CLUSTER_CONFIGURE_SECONDARY_PHASE1_UNKNOWN);

                ++(*pRejoinNodesToClusterContext);
            }
        }
        else
        {
            numberOfFailures++;
        }
    }

    --(*pRejoinNodesToClusterContext);

    if (NULL != pDatabaseBackupBuffer)
    {
        delete[] pDatabaseBackupBuffer;
    }

    if ( numberOfFailures == numberOfNewIpAddresses)
    {
        trace (TRACE_LEVEL_ERROR, string("WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesPhase1Step : numberOfFailures - ") + numberOfFailures );
        resumeDatabaseOperation ();
        
        pRejoinNodesToClusterContext->executeNextStep (FRAMEWORK_ERROR_FAILED_TO_CONFIGURE_ALL_NEW_LOCATIONS);
    }
    else
    {
        pRejoinNodesToClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }

}


void WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesPhase1StepCallback(FrameworkStatus frameworkStatus, WaveRejoinClusterSecondaryPhase1Message *pWaveRejoinClusterSecondaryPhase1Message, void *pContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager:: rejoinNodesToClusterRejoinClusterSecondariesPhase1StepCallback: Starting ...");

    RejoinNodesToClusterContext *pRejoinNodesToClusterContext = reinterpret_cast<RejoinNodesToClusterContext *> (pContext);

    FrameworkObjectManagerRejoinNodesToClusterMessage *pFrameworkObjectManagerRejoinNodesToClusterMessage = dynamic_cast<FrameworkObjectManagerRejoinNodesToClusterMessage *> (pRejoinNodesToClusterContext->getPWaveMessage ());

    waveAssert(NULL != pFrameworkObjectManagerRejoinNodesToClusterMessage,__FILE__,__LINE__);

    --(*pRejoinNodesToClusterContext);

    if (FRAMEWORK_SUCCESS == frameworkStatus)
    {
        waveAssert (NULL != pWaveRejoinClusterSecondaryPhase1Message, __FILE__, __LINE__);

        LocationId  newLocationId = pWaveRejoinClusterSecondaryPhase1Message->getReceiverLocationId ();
        string      ipAddress     = FrameworkToolKit::getIpAddressForLocationId (newLocationId);
        SI32        port          = FrameworkToolKit::getPortForLocationId (newLocationId);

        ResourceId completionStatus = pWaveRejoinClusterSecondaryPhase1Message->getCompletionStatus ();

        pFrameworkObjectManagerRejoinNodesToClusterMessage->updateNewNodeStatus(ipAddress, port, completionStatus);

        if (WAVE_MESSAGE_SUCCESS != completionStatus)
        {
            trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesPhase1StepCallback : Case 1 Configuring ") + ipAddress + " failed : " + completionStatus);
        }
    }
    else
    {
        if (NULL != pWaveRejoinClusterSecondaryPhase1Message)
        {
            LocationId newLocationId1 = pWaveRejoinClusterSecondaryPhase1Message->getReceiverLocationId();
            string     ipAddress1     = FrameworkToolKit::getIpAddressForLocationId (newLocationId1);
            SI32       port1          = FrameworkToolKit::getPortForLocationId (newLocationId1);

            pFrameworkObjectManagerRejoinNodesToClusterMessage->updateNewNodeStatus (ipAddress1, port1, frameworkStatus);

            trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesPhase1StepCallback : Case 2 Configuring ") + ipAddress1 + " failed : " + frameworkStatus);
        }
    }

    if (NULL != pWaveRejoinClusterSecondaryPhase1Message)
    {
        delete pWaveRejoinClusterSecondaryPhase1Message;
    }

    if (0 == (pRejoinNodesToClusterContext->getNumberOfCallbacksBeforeAdvancingToNextStep ()))
    {
        UI32       numberOfNewIpAddresses  = pFrameworkObjectManagerRejoinNodesToClusterMessage->getNumberOfNewNodes ();
        UI32       i                       = 0;
        LocationId newLocationId1          = 0;
        string     ipAddress1              = "";
        SI32       port1                   = 0;
        UI32       numberOfFailures        = 0;

        for (i = 0; i < numberOfNewIpAddresses; i++)
        {
            ipAddress1     = pFrameworkObjectManagerRejoinNodesToClusterMessage->getNodeAt      ((UI32) i);
            port1          = pFrameworkObjectManagerRejoinNodesToClusterMessage->getNodePortAt  ((UI32) i);
            newLocationId1 = FrameworkToolKit::getLocationIdForIpAddressAndPort (ipAddress1, port1);

            if (FRAMEWORK_ERROR_CREATE_CLUSTER_CONFIGURE_SECONDARY_PHASE1_UNKNOWN == (pFrameworkObjectManagerRejoinNodesToClusterMessage->getNewNodeStatus (ipAddress1, port1)))
            {
                pFrameworkObjectManagerRejoinNodesToClusterMessage->updateNewNodeStatus (ipAddress1, port1, FRAMEWORK_ERROR_CREATE_CLUSTER_CONFIGURE_SECONDARY_PHASE1_TIMED_OUT);

                if (0 != newLocationId1)
                {
                    trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager:: rejoinNodesToClusterRejoinClusterSecondariesPhase1StepCallback : Case 3 - Configuring ") + ipAddress1 + " Timeout ");
                }

                numberOfFailures++;
            }
            else
            {
                if (WAVE_MESSAGE_SUCCESS != (pFrameworkObjectManagerRejoinNodesToClusterMessage->getNewNodeStatus (ipAddress1, port1)))
                {
                    numberOfFailures++;
                }
            }
        }
            
        if (numberOfFailures == numberOfNewIpAddresses)
        {
            resumeDatabaseOperation ();
            
            pRejoinNodesToClusterContext->executeNextStep (FRAMEWORK_ERROR_FAILED_TO_CONFIGURE_ALL_NEW_LOCATIONS);
        }
        else
        {
            pRejoinNodesToClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        }
    } 
}

/// Name
/// rejoinNodesToClusterRejoinClusterSecondariesPhase2Step
/// Description
/// When the framework receives a reply from each secondary
/// the it calls this method. This method sends a message to
/// each secondary to start the phase2 which involves restarting
/// all the services on the secondary.
///  Input
/// RejoinNodesToClusterContext:pointer for  context for rejoin created in
/// in the handler
/// Output
/// none
/// Return
/// none

void WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesPhase2Step(RejoinNodesToClusterContext *pRejoinNodesToClusterContext)
{
    trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterecondariesPhase2Step : Entering ...");

    FrameworkObjectManagerRejoinNodesToClusterMessage *pFrameworkObjectManagerRejoinNodesToClusterMessage = dynamic_cast<FrameworkObjectManagerRejoinNodesToClusterMessage *> (pRejoinNodesToClusterContext->getPWaveMessage ());

  
    waveAssert (NULL != pFrameworkObjectManagerRejoinNodesToClusterMessage, __FILE__, __LINE__);
    UI32                                numberOfFailures                    = 0;
    UI32                                numberOfNewLocationIds              = pRejoinNodesToClusterContext->getNumberOfNewLocationIds ();

    ++(*pRejoinNodesToClusterContext);


    UI32 numberOfNewIpAddresses = pFrameworkObjectManagerRejoinNodesToClusterMessage->getNumberOfNodes ();
    for (UI32 i = 0; i < numberOfNewIpAddresses; i++)
    {
        string ipAddress1         = pFrameworkObjectManagerRejoinNodesToClusterMessage->getNodeAt ((UI32) i);
        SI32 port1                = pFrameworkObjectManagerRejoinNodesToClusterMessage->getNodePortAt ((UI32) i);
        LocationId newLocationId1 = FrameworkToolKit::getLocationIdForIpAddressAndPort (ipAddress1, port1);

        // We will send  phase2 message only to the locations that are known to us at this point.
        // Only to those locations that are succeeded as part of phase 1.


        if (WAVE_MESSAGE_SUCCESS == (pFrameworkObjectManagerRejoinNodesToClusterMessage->getNewNodeStatus (ipAddress1, port1)))
        {
            WaveRejoinClusterSecondaryPhase2Message *pMessage = new WaveRejoinClusterSecondaryPhase2Message ();

            pMessage->setIsReplaceRejoin (pFrameworkObjectManagerRejoinNodesToClusterMessage->getIsReplaceRejoin ());

        //Note that a callback is being passed since the processing is Asynchronous
            WaveMessageStatus status = send (pMessage, reinterpret_cast<WaveMessageResponseHandler> (&WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesPhase2StepCallback), pRejoinNodesToClusterContext, 120000, newLocationId1);

            if (WAVE_MESSAGE_SUCCESS != status)
            {

         #if 0
         //QUESTION: CHECK WITH SAGAR:In case of rejoin we should not remove this location
                removeKnownLocation (newLocationId1);
         #endif
                pFrameworkObjectManagerRejoinNodesToClusterMessage->updateNewNodeStatus (ipAddress1, port1, status);
         
                trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesPhase2Step : Not able to configure one secondary location During Phase 2: ") + newLocationId1 + string (" Status : ") + FrameworkToolKit::localize (status));
                numberOfFailures++;
                delete pMessage;
            }
            else
            {
                pFrameworkObjectManagerRejoinNodesToClusterMessage->updateNewNodeStatus (ipAddress1, port1, FRAMEWORK_ERROR_CREATE_CLUSTER_CONFIGURE_SECONDARY_PHASE2_UNKNOWN);

                ++(*pRejoinNodesToClusterContext);
            }
        }
        else
        {
            numberOfFailures++;
        }
    }

    --(*pRejoinNodesToClusterContext);

    //Send for every secondary location failed
    if (numberOfFailures == numberOfNewLocationIds)
    {
        pRejoinNodesToClusterContext->executeNextStep (FRAMEWORK_ERROR_FAILED_TO_CONFIGURE_ALL_NEW_LOCATIONS);
    }
    else
    {
        pRejoinNodesToClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }


}


/// Name
/// rejoinNodesToClusterRejoinClusterSecondariesPhase2StepCallback
/// Description
/// When the framework receives a reply for the phase 2 rejoin message from
/// a secondary then it calls this callback.This method does the bookkeeping
/// of all responses. Once it has received a response from each node it decides
/// whether the entire processing was scuccessful or not.
///  Input
/// FrameworkStatus: success/failure in framework
/// WaveRejoinClusterSecondaryPhase2Message: pointer to the phase 2 message 
/// received back from the secondary in reply
/// RejoinNodesToClusterContext:pointer for  context for rejoin created in
/// the handler
/// Output
/// none
/// Return
/// none

void WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesPhase2StepCallback(FrameworkStatus frameworkStatus, WaveRejoinClusterSecondaryPhase2Message *pWaveRejoinClusterSecondaryPhase2Message, void *pContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager:: rejoinNodesToClusterRejoinClusterSecondariesPhase2StepCallback: Starting ...");

    RejoinNodesToClusterContext                       *pRejoinNodesToClusterContext                       = reinterpret_cast<RejoinNodesToClusterContext *> (pContext);
    FrameworkObjectManagerRejoinNodesToClusterMessage *pFrameworkObjectManagerRejoinNodesToClusterMessage = dynamic_cast<FrameworkObjectManagerRejoinNodesToClusterMessage *> (pRejoinNodesToClusterContext->getPWaveMessage ());

    waveAssert(NULL != pFrameworkObjectManagerRejoinNodesToClusterMessage,__FILE__,__LINE__);

    UI32 numberOfFailures = 0;

    --(*pRejoinNodesToClusterContext);

    if (FRAMEWORK_SUCCESS == frameworkStatus)
    {
        waveAssert (NULL != pWaveRejoinClusterSecondaryPhase2Message, __FILE__, __LINE__);

        LocationId  newLocationId = pWaveRejoinClusterSecondaryPhase2Message->getReceiverLocationId ();
        string      ipAddress     = FrameworkToolKit::getIpAddressForLocationId (newLocationId);
        SI32        port          = FrameworkToolKit::getPortForLocationId (newLocationId);       
        ResourceId completionStatus = pWaveRejoinClusterSecondaryPhase2Message->getCompletionStatus ();

        pFrameworkObjectManagerRejoinNodesToClusterMessage->updateNewNodeStatus(ipAddress, port, completionStatus);

        if (WAVE_MESSAGE_SUCCESS != completionStatus)
        {
            trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesPhase2StepCallback : Configuring ") + ipAddress + " failed : " + completionStatus);     

            disconnectFromLocation (newLocationId);
            pRejoinNodesToClusterContext->addToFailedLocationIdVector (newLocationId);
        }
    }
    else
    {
        if (NULL != pWaveRejoinClusterSecondaryPhase2Message)
        {
            LocationId newLocationId1 = pWaveRejoinClusterSecondaryPhase2Message->getReceiverLocationId();
            string     ipAddress1     = FrameworkToolKit::getIpAddressForLocationId (newLocationId1);
            SI32       port1          = FrameworkToolKit::getPortForLocationId (newLocationId1);

            pFrameworkObjectManagerRejoinNodesToClusterMessage->updateNewNodeStatus (ipAddress1, port1, frameworkStatus);

            disconnectFromLocation (newLocationId1);
            pRejoinNodesToClusterContext->addToFailedLocationIdVector (newLocationId1);
        }
    }

    if (NULL != pWaveRejoinClusterSecondaryPhase2Message)
    {
        delete pWaveRejoinClusterSecondaryPhase2Message;
    }

    //All responses have been received
    if (0 == (pRejoinNodesToClusterContext->getNumberOfCallbacksBeforeAdvancingToNextStep ()))
    {
        UI32       numberOfNewIpAddresses  = pFrameworkObjectManagerRejoinNodesToClusterMessage->getNumberOfNewNodes ();
      
        for (UI32 i = 0; i < numberOfNewIpAddresses; i++)
        {
            string     ipAddress1     = pFrameworkObjectManagerRejoinNodesToClusterMessage->getNodeAt ((UI32) i);
            SI32       port1          = pFrameworkObjectManagerRejoinNodesToClusterMessage->getNodePortAt ((UI32) i);
            LocationId newLocationId1 = FrameworkToolKit::getLocationIdForIpAddressAndPort (ipAddress1, port1);

            if (FRAMEWORK_ERROR_CREATE_CLUSTER_CONFIGURE_SECONDARY_PHASE2_UNKNOWN == (pFrameworkObjectManagerRejoinNodesToClusterMessage->getNewNodeStatus (ipAddress1, port1)))
            {
                pFrameworkObjectManagerRejoinNodesToClusterMessage->updateNewNodeStatus (ipAddress1, port1, FRAMEWORK_ERROR_CREATE_CLUSTER_CONFIGURE_SECONDARY_PHASE2_TIMED_OUT);

                disconnectFromLocation (newLocationId1);
                pRejoinNodesToClusterContext->addToFailedLocationIdVector (newLocationId1);
                numberOfFailures++;
            }
            else
            {
                if (WAVE_MESSAGE_SUCCESS != (pFrameworkObjectManagerRejoinNodesToClusterMessage->getNewNodeStatus (ipAddress1, port1)))
                {
                    numberOfFailures++;
                }
            }

            // Added the successfully added location in a vector. This is going to be used in Phase 3

            if (WAVE_MESSAGE_SUCCESS == pFrameworkObjectManagerRejoinNodesToClusterMessage->getNewNodeStatus (ipAddress1, port1))
            {
                pRejoinNodesToClusterContext->addToSuccessfullyAddedLocationIdVector (newLocationId1);
            }
        }

        if (numberOfFailures == numberOfNewIpAddresses)
        {
            vector<LocationId> failedLocationIdsVectorInPhase2           = pRejoinNodesToClusterContext->getFailedLocationIdVector ();
            UI32               numberOffailedLocationIdsVectorInPhase2   = failedLocationIdsVectorInPhase2.size ();

            if (0 < numberOffailedLocationIdsVectorInPhase2)
            {
                WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext = new WaveFrameworkFailoverWorkerContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveFrameworkObjectManager::failoverforNodesFailedInRejoinPhase2Callback), pRejoinNodesToClusterContext);

                for (UI32 j = 0; j < numberOffailedLocationIdsVectorInPhase2; j++)
                {
                    pWaveFrameworkFailoverWorkerContext->addFailedLocationId (failedLocationIdsVectorInPhase2[j]);
                }
      
                pWaveFrameworkFailoverWorkerContext->setThisLocationRole (LOCATION_PRIMARY);
                pWaveFrameworkFailoverWorkerContext->setFailoverReason  (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED);

                tracePrintf (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesPhase2StepCallback Invoking Uncontrolled failover for %u nodes", numberOffailedLocationIdsVectorInPhase2);

                m_pWaveFrameworkFailoverWorker->executeFailover (pWaveFrameworkFailoverWorkerContext);
            }
        }   
        else
        {
            pRejoinNodesToClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        }
    }

}

void WaveFrameworkObjectManager::failoverforNodesFailedInRejoinPhase2 (RejoinNodesToClusterContext *pRejoinNodesToClusterContext)
{
    vector<LocationId> failedLocationIdsVector            = pRejoinNodesToClusterContext->getFailedLocationIdVector ();
    UI32               numberOffailedLocationIdsVector    = failedLocationIdsVector.size ();

    if (0 < numberOffailedLocationIdsVector)
    {
        WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext = new WaveFrameworkFailoverWorkerContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveFrameworkObjectManager::failoverforNodesFailedInRejoinPhase2Callback), pRejoinNodesToClusterContext);

        for (UI32 k = 0; k < numberOffailedLocationIdsVector; k++)
        {
            pWaveFrameworkFailoverWorkerContext->addFailedLocationId (failedLocationIdsVector[k]);
        }

        pWaveFrameworkFailoverWorkerContext->setThisLocationRole (LOCATION_PRIMARY);
        pWaveFrameworkFailoverWorkerContext->setFailoverReason (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED);

        tracePrintf (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::failoverforNodesFailedInRejoinPhase2 Invoking failover for %u nodes", numberOffailedLocationIdsVector);

        m_pWaveFrameworkFailoverWorker->executeFailover (pWaveFrameworkFailoverWorkerContext);
    }
    else
    {
        pRejoinNodesToClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
}

void WaveFrameworkObjectManager::failoverforNodesFailedInRejoinPhase2Callback (WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::failoverforNodesFailedInRejoinPhase2Callback : Entering ...");

    waveAssert (NULL != pWaveFrameworkFailoverWorkerContext, __FILE__, __LINE__);

    RejoinNodesToClusterContext  *pRejoinNodesToClusterContext = reinterpret_cast<RejoinNodesToClusterContext *> (pWaveFrameworkFailoverWorkerContext->getPCallerContext ());

    delete pWaveFrameworkFailoverWorkerContext;

    waveAssert (NULL != pRejoinNodesToClusterContext, __FILE__, __LINE__);

    //clear the failed location vector setup in previous phases as failover is triggered for those locations.
    pRejoinNodesToClusterContext->clearFailedLocationIdVector ();

    vector<LocationId>      successfullyAddedLocationIdVector = pRejoinNodesToClusterContext->getSuccessfullyAddedLocationIdVector ();
                 UI32       numberOfSuccessfullyAddedNode     = successfullyAddedLocationIdVector.size ();

    if (0 == numberOfSuccessfullyAddedNode)
    {
        pRejoinNodesToClusterContext->executeNextStep (FRAMEWORK_ERROR_FAILED_TO_CONFIGURE_ALL_NEW_LOCATIONS);
    }
    else
    {
        pRejoinNodesToClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
}

void WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesPhase3Step (RejoinNodesToClusterContext *pRejoinNodesToClusterContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesPhase3Step : Starting ...");

    FrameworkObjectManagerRejoinNodesToClusterMessage *pFrameworkObjectManagerRejoinNodesToClusterMessage = dynamic_cast<FrameworkObjectManagerRejoinNodesToClusterMessage *> (pRejoinNodesToClusterContext->getPWaveMessage ());
    vector<LocationId>                                 successfullyAddedLocationIdVector                  = pRejoinNodesToClusterContext->getSuccessfullyAddedLocationIdVector ();
    UI32                                               numberOfSuccessfullyAddedNode                      = successfullyAddedLocationIdVector.size ();
    UI32                                               numberOfFailures                                   = 0;
    LocationId                                         locationId;

    ++(*pRejoinNodesToClusterContext);

    for (UI32 i = 0; i < numberOfSuccessfullyAddedNode; i++)
    {

        locationId = successfullyAddedLocationIdVector[i];

        WaveRejoinClusterSecondaryPhase3Message *pWaveRejoinClusterSecondaryPhase3Message = new WaveRejoinClusterSecondaryPhase3Message ();

        WaveMessageStatus status = send (pWaveRejoinClusterSecondaryPhase3Message, reinterpret_cast<WaveMessageResponseHandler> (&WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesPhase3StepCallback), pRejoinNodesToClusterContext, 0, locationId);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            disconnectFromLocation (locationId);
            pRejoinNodesToClusterContext->addToFailedLocationIdVector (locationId);

            trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesPhase3Step : Not able to Rejoin secondary location During Phase 3: ") + locationId + string (" Status : ") + FrameworkToolKit::localize (status));

            numberOfFailures++;

            if (NULL != pFrameworkObjectManagerRejoinNodesToClusterMessage)
            {
                pFrameworkObjectManagerRejoinNodesToClusterMessage->updateNewNodeStatus (FrameworkToolKit::getIpAddressForLocationId (locationId), FrameworkToolKit::getPortForLocationId (locationId), status);
            }

            delete pWaveRejoinClusterSecondaryPhase3Message;            
        }
        else
        {
            ++(*pRejoinNodesToClusterContext);
        }
    }
    
    --(*pRejoinNodesToClusterContext);

    if (numberOfFailures == numberOfSuccessfullyAddedNode)
    {
        // Trigger Uncontrolled failover
        vector<LocationId> failedLocationIdsVectorInPhase3           = pRejoinNodesToClusterContext->getFailedLocationIdVector ();
        UI32               numberOffailedLocationIdsVectorInPhase3   = failedLocationIdsVectorInPhase3.size ();

        WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext = new WaveFrameworkFailoverWorkerContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveFrameworkObjectManager::failoverforNodesFailedInRejoinPhase3Callback), pRejoinNodesToClusterContext); 

        for (UI32 j = 0; j < numberOffailedLocationIdsVectorInPhase3; j++)
        {
            pWaveFrameworkFailoverWorkerContext->addFailedLocationId (failedLocationIdsVectorInPhase3[j]);
        }

        pWaveFrameworkFailoverWorkerContext->setThisLocationRole (LOCATION_PRIMARY);
        pWaveFrameworkFailoverWorkerContext->setFailoverReason  (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED);

        tracePrintf (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesPhase3Step Invoking Uncontrolled failover for %u nodes", numberOffailedLocationIdsVectorInPhase3);

        m_pWaveFrameworkFailoverWorker->executeFailover (pWaveFrameworkFailoverWorkerContext);
    }
    else
    {
        pRejoinNodesToClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
}

void WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesPhase3StepCallback (FrameworkStatus frameworkStatus, WaveRejoinClusterSecondaryPhase3Message *pWaveRejoinClusterSecondaryPhase3Message, void *pContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesPhase3StepCallback: Starting ....");

    RejoinNodesToClusterContext                       *pRejoinNodesToClusterContext                       = reinterpret_cast<RejoinNodesToClusterContext *> (pContext);
    FrameworkObjectManagerRejoinNodesToClusterMessage *pFrameworkObjectManagerRejoinNodesToClusterMessage = dynamic_cast<FrameworkObjectManagerRejoinNodesToClusterMessage *> (pRejoinNodesToClusterContext->getPWaveMessage ());

    waveAssert (NULL != pWaveRejoinClusterSecondaryPhase3Message, __FILE__, __LINE__);

    LocationId                   locationId                   = pWaveRejoinClusterSecondaryPhase3Message->getReceiverLocationId ();

    --(*pRejoinNodesToClusterContext);

    if (FRAMEWORK_SUCCESS == frameworkStatus)
    {
        ResourceId completionStatus = pWaveRejoinClusterSecondaryPhase3Message->getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != completionStatus)
        {
            trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesPhase3StepCallback:Failed to Rejoin Location Id ") + locationId + " status : " + completionStatus);
            disconnectFromLocation (locationId);
            pRejoinNodesToClusterContext->addToFailedLocationIdVector (locationId);            
        }

        if (NULL != pFrameworkObjectManagerRejoinNodesToClusterMessage)
        {
            pFrameworkObjectManagerRejoinNodesToClusterMessage->updateNewNodeStatus (FrameworkToolKit::getIpAddressForLocationId (locationId), FrameworkToolKit::getPortForLocationId (locationId), completionStatus);
        }
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesPhase3StepCallback: Failed to Rejoin Location Id ") + locationId + " status : " + frameworkStatus);

        disconnectFromLocation (locationId);
        pRejoinNodesToClusterContext->addToFailedLocationIdVector (locationId);

        if (NULL != pFrameworkObjectManagerRejoinNodesToClusterMessage)
        {
            pFrameworkObjectManagerRejoinNodesToClusterMessage->updateNewNodeStatus (FrameworkToolKit::getIpAddressForLocationId (locationId), FrameworkToolKit::getPortForLocationId (locationId), frameworkStatus);
        }
    }
    

    if (0 == (pRejoinNodesToClusterContext->getNumberOfCallbacksBeforeAdvancingToNextStep ()))
    {
        vector<LocationId> failedLocationIdsVectorInPhase3           = pRejoinNodesToClusterContext->getFailedLocationIdVector ();
        UI32               numberOffailedLocationIdsVectorInPhase3   = failedLocationIdsVectorInPhase3.size ();

        if (0 < numberOffailedLocationIdsVectorInPhase3)
        {
            WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext = new WaveFrameworkFailoverWorkerContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveFrameworkObjectManager::failoverforNodesFailedInRejoinPhase3Callback), pRejoinNodesToClusterContext);

            for (UI32 j = 0; j < numberOffailedLocationIdsVectorInPhase3; j++)
            {
                pWaveFrameworkFailoverWorkerContext->addFailedLocationId (failedLocationIdsVectorInPhase3[j]);
            }
            
            pWaveFrameworkFailoverWorkerContext->setThisLocationRole (LOCATION_PRIMARY);
            pWaveFrameworkFailoverWorkerContext->setFailoverReason  (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED);

            tracePrintf (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinNodesToClusterRejoinClusterSecondariesPhase3StepCallback Invoking Uncontrolled failover for %u nodes", numberOffailedLocationIdsVectorInPhase3);

            m_pWaveFrameworkFailoverWorker->executeFailover (pWaveFrameworkFailoverWorkerContext);
        }
        else
        {
            pRejoinNodesToClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        }
    } 

    delete pWaveRejoinClusterSecondaryPhase3Message;
}

void WaveFrameworkObjectManager::failoverforNodesFailedInRejoinPhase3Callback (WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::failoverforNodesFailedInRejoinPhase3Callback : Entering ...");

    waveAssert (NULL != pWaveFrameworkFailoverWorkerContext, __FILE__, __LINE__);

    RejoinNodesToClusterContext  *pRejoinNodesToClusterContext = reinterpret_cast<RejoinNodesToClusterContext *> (pWaveFrameworkFailoverWorkerContext->getPCallerContext ());

    delete pWaveFrameworkFailoverWorkerContext;

    waveAssert (NULL != pRejoinNodesToClusterContext, __FILE__, __LINE__);

    pRejoinNodesToClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

/// Name
/// rejoinClusterSecondaryMessageHandler
/// Description
/// This handler processes the rejoin request received on the secondary node frameowrk
/// from the primary node framework.It establishes the steps required to process the message
/// and lodges them in the context
///  Input
/// FrameworkObjectManagerRejoinClusterSecondaryMessage:pointer to message
/// received from the primary
/// Output
/// none
/// Return
/// none
void WaveFrameworkObjectManager::rejoinClusterSecondaryMessageHandler (FrameworkObjectManagerRejoinClusterSecondaryMessage *pFrameworkObjectManagerRejoinClusterSecondaryMessage)
{
    SecondaryNodeClusterContext *pSecondaryNodeClusterContext = NULL;
    
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinClusterSecondaryMessageHandler: (ACTIVE)");

    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::removePreviousDatabaseBackupFile),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinSecondaryNodeValidateStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::stopHeartBeatToNode),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinSecondaryNodeValidateVersionStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinSecondaryNodeValidateServicesStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinSecondaryNodeShutdownServicesStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinSecondaryNodeConnectToPrimaryStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinSecondaryNodeConfigureThisLocationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinSecondaryNodeBootServicesPrePhaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinSecondaryNodeNotifyHaPeerStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeBackupCurrentDatabaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeCleanPreparedTransactionsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeEmptyDatabaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::startClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::checkHaPeerSyncStatusStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::secondaryNodeClusterFailureStep),
    };

    //Note that memory is freed in the framework in the success or the failure step
    pSecondaryNodeClusterContext = new SecondaryNodeClusterContext (pFrameworkObjectManagerRejoinClusterSecondaryMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pSecondaryNodeClusterContext->setClusterPrimaryIpAddress  (pFrameworkObjectManagerRejoinClusterSecondaryMessage->getClusterPrimaryIpAddress ());
    pSecondaryNodeClusterContext->setClusterPrimaryPort       (pFrameworkObjectManagerRejoinClusterSecondaryMessage->getClusterPrimaryPort ());
    pSecondaryNodeClusterContext->setClusterPrimaryLocationId (pFrameworkObjectManagerRejoinClusterSecondaryMessage->getClusterPrimaryLocationId ());

    pSecondaryNodeClusterContext->holdAll ();
    pSecondaryNodeClusterContext->start ();
}

void WaveFrameworkObjectManager::rejoinClusterSecondaryHaPeerMessageHandler (FrameworkObjectManagerRejoinClusterSecondaryHaPeerMessage *pFrameworkObjectManagerRejoinClusterSecondaryHaPeerMessage)
{
    SecondaryNodeClusterContext *pSecondaryNodeClusterContext = NULL;

    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinClusterSecondaryHaPeerMessageHandler: (STANDBY)");

    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::removePreviousDatabaseBackupFile),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinSecondaryNodeShutdownServicesStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeBootServicesPrePhaseForStandbyStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeBackupCurrentDatabaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinSecondaryNodeSetLocationRoleOnStandbyStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeCleanPreparedTransactionsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeEmptyDatabaseStep),
        //reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::startClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerFailedStep),
    };

    pSecondaryNodeClusterContext = new SecondaryNodeClusterContext (pFrameworkObjectManagerRejoinClusterSecondaryHaPeerMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pSecondaryNodeClusterContext->holdAll ();
    pSecondaryNodeClusterContext->start ();

}

void WaveFrameworkObjectManager::rejoinClusterSecondaryPhase1MessageHandler (WaveRejoinClusterSecondaryPhase1Message *pWaveRejoinClusterSecondaryPhase1Message)
{
    SecondaryNodeClusterContext *pSecondaryNodeClusterContext = NULL;

    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinClusterSecondaryPhase1MessageHandler: (ACTIVE)");

    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::stopClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::updateLocationRoleStepInRejoinPhase1),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinSecondaryHaPeerPrePhaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeLoadDatabaseFromPrimaryDatabaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeUpdateInstanceIdsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::startClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::checkHaPeerSyncStatusStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::secondaryNodeClusterFailureStep),
    };

    pSecondaryNodeClusterContext = new SecondaryNodeClusterContext (pWaveRejoinClusterSecondaryPhase1Message, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pSecondaryNodeClusterContext->holdAll ();
    pSecondaryNodeClusterContext->start ();
}

void WaveFrameworkObjectManager::rejoinClusterSecondaryHaPeerPhase1MessageHandler (WaveRejoinClusterSecondaryHaPeerPhase1Message *pWaveRejoinClusterSecondaryHaPeerPhase1Message)
{
    SecondaryNodeClusterContext *pSecondaryNodeClusterContext = NULL;

    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinClusterSecondaryPhase1MessageHandler: (STANDBY)");

    WaveLinearSequencerStep sequencerSteps[] =
    {
        //reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::stopClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeLoadDatabaseFromPrimaryDatabaseStep),
        //reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::startClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerFailedStep),
    };

    pSecondaryNodeClusterContext = new SecondaryNodeClusterContext (pWaveRejoinClusterSecondaryHaPeerPhase1Message, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pSecondaryNodeClusterContext->holdAll ();
    pSecondaryNodeClusterContext->start ();

}

void WaveFrameworkObjectManager::updateLocationRoleStepInRejoinPhase1 (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    LocationRole locationRole = m_pThisLocation->getLocationRole ();

    if (LOCATION_SECONDARY_REJOIN_PHASE_0 == locationRole)
    {
    m_pThisLocation->setLocationRole (LOCATION_SECONDARY_REJOIN_PHASE_1);
    pSecondaryNodeClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}
    else
    {
        trace (TRACE_LEVEL_WARN, "WaveFrameworkObjectManager::updateLocationRoleStepInRejoinPhase1 received Message in incorrect location role, return with error");
        pSecondaryNodeClusterContext->executeNextStep (WAVE_MESSAGE_ERROR);
    }
}

/// Name
/// rejoinSecondaryNodeValidateStep
/// Description
/// This function validates the rejoin request received on the secondary node frameowrk
/// from the primary node framework.It validates
/// 1. Location Role
/// 2. Loaction Id of the Node
/// 3. Location Id of the primary
/// 4. IP Address
///  Input
/// SecondaryNodeClusterContext:pointer to the context
/// Output
/// none
/// Return
/// none
void WaveFrameworkObjectManager::rejoinSecondaryNodeValidateStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::rejoinSecondaryNodeValidateStep : Entering ...");

    FrameworkObjectManagerRejoinClusterSecondaryMessage *pFrameworkObjectManagerRejoinClusterSecondaryMessage = reinterpret_cast<FrameworkObjectManagerRejoinClusterSecondaryMessage *> (pSecondaryNodeClusterContext->getPWaveMessage ());

    waveAssert(NULL != pFrameworkObjectManagerRejoinClusterSecondaryMessage,__FILE__,__LINE__);

    ResourceId    status               = WAVE_MESSAGE_SUCCESS;

    //Postboot needed to false and this will be reset only in case of replace rejoin or default configuration rejoin.
    setIsPostBootNeededDuringRejoin (false);

    LocationRole  currentLocationRole             = m_pThisLocation->getLocationRole ();

    if (true == FrameworkToolKit::isConfigurationCompatibilityCheckRequired ())
    {
        UI64      configurationTransactionId  = 0;  
        DateTime  configurationTime;
        DateTime  latestUpdateTime;
                      
        PersistenceToolKit::getConfigurationManagedObjectInformation (configurationTransactionId, configurationTime, latestUpdateTime); 

        vector<UI64> configurationNumber = pFrameworkObjectManagerRejoinClusterSecondaryMessage->getConfigurationNumber ();

        trace (TRACE_LEVEL_INFO, string (" size of configuration number from primary is ") + configurationNumber.size ());

        if ((configurationTransactionId != configurationNumber [0]) && (0 != configurationTransactionId))
        {
            trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::rejoinSecondaryNodeValidateStep configuration mismatch primary node transaction id is ") + configurationNumber [0] + string (" This node transaction id is ") + configurationTransactionId);

            status  = WAVE_MESSAGE_ERROR_CONFIGURATION_MISMATCH; 
        }
    }

    // Ensure node is in standalone role if rejoin is happening due to switch replacement.
    if (true == pFrameworkObjectManagerRejoinClusterSecondaryMessage->getIsReplaceRejoin ())
    {
        if (LOCATION_STAND_ALONE != currentLocationRole)
        {
            if (WAVE_MESSAGE_SUCCESS == status)
            {
                trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::rejoinSecondaryNodeValidateStep : This location does not have standalone role. Cannot replace rejoin.");

                status = FRAMEWORK_ERROR_CANNOT_JOIN_CLUSTER_LOCATION_UNKNOWN_ROLE;
            }
        }

        //Postboot needed during replace rejoin
        setIsPostBootNeededDuringRejoin (true);

        if (WAVE_MESSAGE_SUCCESS == status)
        {        
            pSecondaryNodeClusterContext->executeNextStep (status);
            return;
        }
    }

        /* We need to support rejoin node after failover from the cluster */
    if (LOCATION_SECONDARY_UNCONFIRMED != currentLocationRole && LOCATION_PRIMARY_UNCONFIRMED != currentLocationRole)
    {
        if (LOCATION_PRIMARY == currentLocationRole)
        {
            trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::rejoinSecondaryNodeValidateStep : This location is a primary location.");
        }
        else if (LOCATION_SECONDARY == currentLocationRole)
        {
            // This coindition can happen when link toggling cause HB failure but no FC principal change. In this case on HB failure Primary will trigger uncontrolled failover and sent rejoin               to this node. This node didn't get a chance to become principal as on link toggling this node become fc principal for very short duration. By the time heartbeat fails this node               was not fc principal any more.

            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinSecondaryNodeValidateStep : This location is already a confirmed secondary location, Proceeding For Rejoin ");
        }
        else if (LOCATION_SUB_LOCATION == currentLocationRole)
        {
            if (WAVE_MESSAGE_SUCCESS == status)
            {
                trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::rejoinSecondaryNodeValidateStep : This location is a sub location.");

                status = FRAMEWORK_ERROR_CANNOT_JOIN_CLUSTER_LOCATION_SUB_LOCATION;
            }
        }
        else if (LOCATION_STAND_ALONE == currentLocationRole)
        {
            //Postboot needed during default configuration rejoin.
            setIsPostBootNeededDuringRejoin (true);

            if (WAVE_MESSAGE_SUCCESS == status)
            {
                trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::rejoinSecondaryNodeValidateStep : Stand Alone, getting rejoin");

                pSecondaryNodeClusterContext->executeNextStep (status);
                return;
            }
        }
        else
        {
            if (WAVE_MESSAGE_SUCCESS == status)
            {
                trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::rejoinSecondaryNodeValidateStep : This location has unknown role.");

                status = FRAMEWORK_ERROR_CANNOT_JOIN_CLUSTER_LOCATION_UNKNOWN_ROLE;
            }
        }
    }

    //LocationId validation
    LocationId   currentLocationId = FrameworkToolKit::getThisLocationId ();
    LocationId   suggestedLocationId = pFrameworkObjectManagerRejoinClusterSecondaryMessage->getLocationId ();

    if (currentLocationId != suggestedLocationId)
    {
        if (WAVE_MESSAGE_SUCCESS == status)
        {
            trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::rejoinSecondaryNodeValidateStep : CurrentLocationId (") + currentLocationId + ") does not match with Suggected LocationId (" + suggestedLocationId + ").");

            status = FRAMEWORK_ERROR_CANNOT_JOIN_CLUSTER_LOCATIONID_MISMATCH;
        }
    }

    pSecondaryNodeClusterContext->executeNextStep (status);
    return;
}

/// Name
/// rejoinSecondaryNodeValidateVersionStep
/// Description
/// This function compares the version received on the primary 
/// with the version received on the secondary
/// Input
/// SecondaryNodeClusterContext:pointer to the context
/// Output
/// none
/// Return
/// none
void WaveFrameworkObjectManager::rejoinSecondaryNodeValidateVersionStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
   FrameworkObjectManagerRejoinClusterSecondaryMessage *pFrameworkObjectManagerRejoinClusterSecondaryMessage = dynamic_cast<FrameworkObjectManagerRejoinClusterSecondaryMessage *> (pSecondaryNodeClusterContext->getPWaveMessage ());

   waveAssert(NULL != pFrameworkObjectManagerRejoinClusterSecondaryMessage,__FILE__, __LINE__);
 
    string                                 primaryWaveVersionString              = pFrameworkObjectManagerRejoinClusterSecondaryMessage->getClusterPrimaryWaveVersion ();
    string                                 thisLocationWavePrimaryVersionString  = WaveVersion::getVersionString ();
    ResourceId                             status                                 = WAVE_MESSAGE_SUCCESS;

    if (getNumberOfLineCardPostBootCurrentlyRunning ())
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::rejoinSecondaryNodeValidateVersionStep :LC Postboot in progress. Returning error.");
        pSecondaryNodeClusterContext->executeNextStep (FRAMEWORK_LINECARD_POSTBOOT_IN_PROGRESS);
        return;
    }

    trace (TRACE_LEVEL_INFO, "This       Location Wave Version : " + thisLocationWavePrimaryVersionString);
    trace (TRACE_LEVEL_INFO, "Requesting Location Wave Version : " + primaryWaveVersionString);

    if (0 == thisLocationWavePrimaryVersionString.compare (primaryWaveVersionString))
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinSecondaryNodeValidateVersionStep : Version Check succeeded.\n");

        status = WAVE_MESSAGE_SUCCESS;
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::rejoinSecondaryNodeValidateVersionStep : Version Check failed.\n");

        status = FRAMEWORK_ERROR_CANNOT_BECOME_SECONDARY_WAVE_VERSION_MISMATCH;
    }

    vector<string>  managedObjectNamesForSchemaChange;
    vector<string>  fieldNamesStringsForSchemaChange;
    vector<string>  fieldNamesTypesForSchemaChange;
    vector<UI32>    classIds;
    vector<UI32>    parentTableIds;

    pFrameworkObjectManagerRejoinClusterSecondaryMessage->getSchemaChangeVectors (managedObjectNamesForSchemaChange,fieldNamesStringsForSchemaChange,fieldNamesTypesForSchemaChange, classIds, parentTableIds);

    if (!isSchemaReceivedFromPrimaryCompatible (managedObjectNamesForSchemaChange,fieldNamesStringsForSchemaChange,fieldNamesTypesForSchemaChange, classIds, parentTableIds))
    {
        status = WAVE_MESSAGE_ERROR_SCHEMA_MISMATCH;
    }

    pSecondaryNodeClusterContext->executeNextStep (status);
}


/// Name
/// rejoinSecondaryNodeValidateServicesStep
/// Description
/// This function loops through each of the services and
/// if the service is enabled it sends the validation data
/// to the service.The response received is appended to
/// the message to be sent back to the primary.
/// Input
/// SecondaryNodeClusterContext:pointer to the context
/// Output
/// none
/// Return
/// none

void WaveFrameworkObjectManager::rejoinSecondaryNodeValidateServicesStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::rejoinSecondaryNodeValidateServicesStep : Entering\n");
    vector<WaveServiceId> waveServiceIds;
    WaveThread::getListOfServiceIds (waveServiceIds);

    ResourceId status = WAVE_MESSAGE_SUCCESS;
    UI32  numberOfWaveServiceIds = waveServiceIds.size ();

    FrameworkObjectManagerRejoinClusterSecondaryMessage *pFrameworkObjectManagerRejoinClusterSecondaryMessage = dynamic_cast<FrameworkObjectManagerRejoinClusterSecondaryMessage *> (pSecondaryNodeClusterContext->getPWaveMessage ());
    waveAssert(NULL != pFrameworkObjectManagerRejoinClusterSecondaryMessage, __FILE__ , __LINE__);

    for (UI32 i = 0; i < numberOfWaveServiceIds; i++)
    {
        trace (TRACE_LEVEL_DEBUG, string ("WaveFrameworkObjectManager::rejoinSecondaryNodeValidateServicesStep : Validating Service : ") + FrameworkToolKit::getServiceNameById (waveServiceIds[i]));
 
        if (true == (isServiceToBeExcludedInClusterCommunications (waveServiceIds[i]))  || false == isServiceEnabled(waveServiceIds[i]))
        {
            continue;
        }

        UI32   size  = 0;
        void* pValidationData = pFrameworkObjectManagerRejoinClusterSecondaryMessage->transferBufferToUser (waveServiceIds[i], size);

        WaveObjectManagerValidateClusterCreationMessage message (waveServiceIds[i]);

        // If we have got some validation data then attach it and send it to the service.

        if ((NULL != pValidationData) && (0 != size))
        {
            trace (TRACE_LEVEL_DEBUG, string ("WaveFrameworkObjectManager::rejoinSecondaryNodeValidateServicesStep : Sending Validation details to Service : ") + FrameworkToolKit::getServiceNameById (waveServiceIds[i]));

            message.setValidationDetails (pValidationData, size, true);
        }

    LocationId thisLocationId = FrameworkToolKit::getThisLocationId ();

    status = sendSynchronously (&message, thisLocationId);
        if (WAVE_MESSAGE_SUCCESS != status)
        {
            status = FRAMEWORK_ERROR_SERVICE_VALIDATION_FAILED;
            trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::rejoinSecondaryNodeValidateServicesStep : Failed to Validate Service (") + FrameworkToolKit::getServiceNameById (waveServiceIds[i]) + "), Status : " + FrameworkToolKit::localize (status));
            break;
        }

        status = message.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            status = FRAMEWORK_ERROR_SERVICE_VALIDATION_FAILED;
            trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::rejoinSecondaryNodeValidateServicesStep : Failed to Validate Service (") + FrameworkToolKit::getServiceNameById (waveServiceIds[i]) + "), Completion Status : " + FrameworkToolKit::localize (status));
            break;
        }

        void *pValidationResults = NULL;

        message.getValidationResults (pValidationResults, size);

    //attach validation results to the message to be sent back to the principal
        if ((0 != size) && (NULL != pValidationResults))
        {
            trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::rejoinSecondaryNodeValidateServicesStep : Obtained Validation Results for Service : " + FrameworkToolKit::getServiceNameById (waveServiceIds[i]));

            pFrameworkObjectManagerRejoinClusterSecondaryMessage->addBuffer (waveServiceIds[i] + s_offSetForValidationResults, size, pValidationResults, true);
        }
        else
        {
            trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::rejoinSecondaryNodeValidateServicesStep : No Validation Results are obtained for Service : " + FrameworkToolKit::getServiceNameById (waveServiceIds[i]));
        }
    }

    pSecondaryNodeClusterContext->executeNextStep (status);
}

void WaveFrameworkObjectManager::rejoinSecondaryNodeNotifyHaPeerStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinSecondaryNodeNotifyHaPeerStep Entering");

    if ((true == FrameworkToolKit::isConfigurationCompatibilityCheckRequired ()) && (true == getIsPostBootNeededDuringRejoin ()))
    {
        // For LC mode Notify HA that secondary rejoining cluster with default config to start, so HA sync to be stopped.
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinSecondaryNodeNotifyHaPeerStep: Notify on ClusterUnReady event for secondary rejoin with default config");

        FrameworkToolKit::disableLiveSync ();
        setSyncState (OUT_OF_SYNC);
        setNeedNotifyClusterReadyState (true);
        bool readyState = false;
        notifyClusterReadyState (readyState);
        pSecondaryNodeClusterContext->setClusterHaSyncInProgress (false);
    }
    else if ( (WAVE_MESSAGE_SUCCESS == FrameworkToolKit::isConnectedToHaPeerLocation ()) && (true == FrameworkToolKit::getIsLiveSyncEnabled ()) )
    {
         trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinSecondaryNodeNotifyHaPeerStep: Ha Peer is connected and Live Sync enabled.");

         FrameworkObjectManagerRejoinClusterSecondaryMessage *pFrameworkObjectManagerRejoinClusterSecondaryMessage = dynamic_cast<FrameworkObjectManagerRejoinClusterSecondaryMessage *> (pSecondaryNodeClusterContext->getPWaveMessage ());
         waveAssert(NULL != pFrameworkObjectManagerRejoinClusterSecondaryMessage, __FILE__ , __LINE__);

         FrameworkObjectManagerRejoinClusterSecondaryHaPeerMessage *pFrameworkObjectManagerRejoinClusterSecondaryHaPeerMessage = new FrameworkObjectManagerRejoinClusterSecondaryHaPeerMessage;

         waveAssert (NULL != pFrameworkObjectManagerRejoinClusterSecondaryHaPeerMessage, __FILE__, __LINE__);

         pFrameworkObjectManagerRejoinClusterSecondaryHaPeerMessage->copyBuffersFrom (*pFrameworkObjectManagerRejoinClusterSecondaryMessage);  

         ResourceId haPeerSendStatus = send (pFrameworkObjectManagerRejoinClusterSecondaryHaPeerMessage, reinterpret_cast<WaveMessageResponseHandler> (&WaveFrameworkObjectManager::rejoinClusterSecondaryHaPeerMessageCallback), pSecondaryNodeClusterContext, 200000, FrameworkToolKit::getHaPeerLocationId ());
 
        if (WAVE_MESSAGE_SUCCESS != haPeerSendStatus)
        {
            trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::rejoinSecondaryNodeNotifyHaPeerStep: Send to Ha Peer failed.");
            delete pFrameworkObjectManagerRejoinClusterSecondaryHaPeerMessage;
            FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
        }
        else
        {
            if (false == pSecondaryNodeClusterContext->getClusterHaSyncInProgress ())
            {
                trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinSecondaryNodeNotifyHaPeerStep: Cluster Phase 0 to Ha Peer start.");
                pSecondaryNodeClusterContext->setClusterHaSyncInProgress (true);
            }
        }
    }
    else if ((FrameworkToolKit::getSyncState () == IN_SYNC) && (false == FrameworkToolKit::getIsLiveSyncEnabled ()))
    { 
        // DB previously in sync from sync dump. but live transaction sync not supported. So set out of sync and notify on sync update fail
        trace (TRACE_LEVEL_WARN, "WaveFrameworkObjectManager::rejoinSecondaryNodeNotifyHaPeerStep: Live sync disabled. Notify sync update failure on first update after sync dump.");
        FrameworkToolKit::notifySyncUpdateFailure(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_NOT_SUPPORTED);
    }
    else
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinSecondaryNodeNotifyHaPeerStep: Ha Peer is unavailable OR Live sync is disabled.");
    }

    pSecondaryNodeClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::rejoinClusterSecondaryHaPeerMessageCallback (FrameworkStatus frameworkStatus, FrameworkObjectManagerRejoinClusterSecondaryHaPeerMessage *pFrameworkObjectManagerRejoinClusterSecondaryHaPeerMessage, void *pContext)
{
    //trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinClusterSecondaryHaPeerMessageCallback: Begin.");
 
    if (FRAMEWORK_SUCCESS != frameworkStatus)
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::rejoinClusterSecondaryHaPeerMessageCallback: Failed to configure Peer, Framework Status: " + FrameworkToolKit::localize (frameworkStatus));
        FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
    }
    else
    {
        ResourceId status = pFrameworkObjectManagerRejoinClusterSecondaryHaPeerMessage->getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::rejoinClusterSecondaryHaPeerMessageCallback: Failed to configure Peer, Completion Status: " + FrameworkToolKit::localize (status));
            FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
        }
    }

    if (NULL != pFrameworkObjectManagerRejoinClusterSecondaryHaPeerMessage)
    {
        delete pFrameworkObjectManagerRejoinClusterSecondaryHaPeerMessage;
    }

    SecondaryNodeClusterContext *pSecondaryNodeClusterContext = reinterpret_cast<SecondaryNodeClusterContext *> (pContext); 

    if (true == pSecondaryNodeClusterContext->getClusterHaSyncInProgress ())
    {
        pSecondaryNodeClusterContext->setClusterHaSyncInProgress (false);

        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinClusterSecondaryHaPeerMessageCallback: Cluster Phase 0 to Ha Peer end.");

        if ( (pSecondaryNodeClusterContext->getNumberOfCallbacksBeforeAdvancingToNextStep ()) > 0)
        {
            --(*pSecondaryNodeClusterContext);
            pSecondaryNodeClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        }
    }
}

/// Name
/// rejoinSecondaryNodeShutdownServicesStep
/// Description
/// This will trigger the shutdown of services
/// (shutdown, disable, uninitialize).
/// Input
/// SecondaryNodeClusterContext:pointer to the context
/// Output
/// none
/// Return
/// none

void WaveFrameworkObjectManager::rejoinSecondaryNodeShutdownServicesStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::rejoinSecondaryNodeShutdownServicesStep : Entering ...");

    ResourceId status = WAVE_MESSAGE_SUCCESS;

    status = m_pWaveFinalizeWorker->shutdownWaveServices (WAVE_SHUTDOWN_SECONDARY_REJOIN);

    pSecondaryNodeClusterContext->executeNextStep (status);
}

/// Name
/// rejoinSecondaryNodeConnectToPrimaryStep
/// Description
/// This function connects back to the primary. Typically,
/// by this time the connection is already set up to the primary.
/// The connection to the primary is established when the first
/// message has been received from the Primary.
/// Input
/// SecondaryNodeClusterContext:pointer to the context
/// Output
/// none
/// Return
/// none

void WaveFrameworkObjectManager::rejoinSecondaryNodeConnectToPrimaryStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::rejoinSecondaryNodeConnectToPrimaryStep : Entering ...");

    static const UI32                                    maximumNumberOfRetriesToConnectToARemoteLocation     = 30;
    static const UI32                                    maximumNumberOfSecondsToWaitToConnect                = 30;
    FrameworkObjectManagerRejoinClusterSecondaryMessage *pFrameworkObjectManagerRejoinClusterSecondaryMessage = dynamic_cast<FrameworkObjectManagerRejoinClusterSecondaryMessage *> (pSecondaryNodeClusterContext->getPWaveMessage ());

    waveAssert (NULL != pFrameworkObjectManagerRejoinClusterSecondaryMessage,__FILE__, __LINE__);
         
    SI32       currentPrimaryPort       = pSecondaryNodeClusterContext->getClusterPrimaryPort();
    LocationId currentPrimaryLocationId = pSecondaryNodeClusterContext->getClusterPrimaryLocationId();
    string     primaryIpAddress         = pSecondaryNodeClusterContext->getClusterPrimaryIpAddress ();

    m_pThisLocation->setClusterPrimaryLocationId (currentPrimaryLocationId);
    m_pThisLocation->setClusterPrimaryPort       (currentPrimaryPort);

    //The rejoining  node should have the primary node as one of its known locations
    //If the node has rebooted and is then rejoining, it should get the list of 
    // all known locations from the persistent config.
    if (true != (isAKnownLocation (currentPrimaryLocationId)))
    {
        if (true == pFrameworkObjectManagerRejoinClusterSecondaryMessage->getIsReplaceRejoin ())
        { 
            // If this is a replace rejoin then add the cluster primary as a known location.

            m_pThisLocation->addKnownLocation (currentPrimaryLocationId, primaryIpAddress, currentPrimaryPort);
        }
        else if ((LOCATION_STAND_ALONE == m_pThisLocation->getLocationRole ()) || (LOCATION_PRIMARY_UNCONFIRMED == m_pThisLocation->getLocationRole ()) || (LOCATION_SECONDARY_UNCONFIRMED == m_pThisLocation->getLocationRole ()))
        {
            // If a primary/secondary node in cluster is rebooted and before it comes up(can be held at boot,failed to boot etc.,)
            // a new node has joined the cluster and has become new primary(the current primary is rebooted after add node).
            // The new node will send an invite to the node which went for a reboot and is UP now.
            // Since the other node is in primary/secondary unconfirmed role after it is up from a reboot 
            // and is not aware of the new primary yet it should consider adding the primary to its known locations.

            m_pThisLocation->addKnownLocation (currentPrimaryLocationId, primaryIpAddress, currentPrimaryPort);
        }
        else
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::rejoinSecondaryNodeConnectToPrimaryStep: Primary location is unknown. Our location " + FrameworkToolKit::localize (m_pThisLocation->getLocationRole ()));

            waveAssert (false, __FILE__, __LINE__);

            pSecondaryNodeClusterContext->executeNextStep (FRAMEWORK_ERROR_CANNOT_JOIN_CLUSTER_LOCATION_CONFIGURATION_INVALID);
            return;
        }
    }

    string       currentPrimaryIpAddress  = FrameworkToolKit::getIpAddressForLocationId (currentPrimaryLocationId);
    ResourceId   status                   = m_pThisLocation->connectToRemoteLocation (currentPrimaryLocationId, maximumNumberOfRetriesToConnectToARemoteLocation, maximumNumberOfSecondsToWaitToConnect);

    if (FRAMEWORK_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::rejoinSecondaryNodeConnectToPrimaryStep : Could not connect to Current Primary : " + currentPrimaryIpAddress + ", Status = " + status);
    }
    else
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinSecondaryNodeConnectToPrimaryStep : Now Connected to Current Primary : " + currentPrimaryIpAddress + ".");
        status = WAVE_MESSAGE_SUCCESS;
    }

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinSecondaryNodeConnectToPrimaryStep : Rolling back as the node is in phase 0/1");

        ResourceId rollbackStatus = m_pInitializeWorker->startWaveServices (WAVE_BOOT_PERSISTENT, WAVE_BOOT_ROLL_BACK_BOOT_PHASE_BEFORE_PHASE_0);

        if (WAVE_MESSAGE_SUCCESS != rollbackStatus)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::rejoinSecondaryNodeConnectToPrimaryStep : Roll Back should Never Fail");
            waveAssert (false, __FILE__, __LINE__);
        }
    }
    else
    {
        m_pThisLocation->setLocationRole(LOCATION_SECONDARY_REJOIN_PHASE_0);
    }

    pSecondaryNodeClusterContext->executeNextStep (status);
}

/// Name
/// rejoinSecondaryNodeConnectToPrimaryStep
/// Description
///TODO: AASHISH: This should setup fields in the 
/// Local Cluster Object Manager
/// Input
/// SecondaryNodeClusterContext:pointer to the context
/// Output
/// none
/// Return
/// none

void WaveFrameworkObjectManager::rejoinSecondaryNodeConfigureThisLocationStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::rejoinSecondaryNodeConfigureThisLocationStep : Entering ...");
    FrameworkObjectManagerRejoinClusterSecondaryMessage *pFrameworkObjectManagerRejoinClusterSecondaryMessage = dynamic_cast<FrameworkObjectManagerRejoinClusterSecondaryMessage *> (pSecondaryNodeClusterContext->getPWaveMessage ());

    waveAssert(NULL != pFrameworkObjectManagerRejoinClusterSecondaryMessage, __FILE__, __LINE__);

#if 0
    LocationId                                           currentPrimaryLocationId                             = m_pThisLocation->getClusterPrimaryLocationId ();
    SI32                                                 clusterPrimaryPort                                   = FrameworkToolKit::getPortForLocationId (currentPrimaryLocationId);
    string                                               currentPrimaryIpAddress                              = FrameworkToolKit::getIpAddressForLocationId (currentPrimaryLocationId);
#endif

    ResourceId                                           processingStatus                                     = WAVE_MESSAGE_SUCCESS;
    UI32                                                 sizeOfValidationDetails                              = 0;
    void                                                *pValidationDetailsBuffer                             = NULL;

    // If replace rejoin scenario then reset the current locationId and ipAddress
    if ((true == pFrameworkObjectManagerRejoinClusterSecondaryMessage->getIsReplaceRejoin ()) || (getThisLocationId () != pFrameworkObjectManagerRejoinClusterSecondaryMessage->getLocationId ()))
    {
        LocationId myNewLocationId          = pFrameworkObjectManagerRejoinClusterSecondaryMessage->getLocationId ();

        trace (TRACE_LEVEL_INFO, string ("WaveFrameworkObjectManager::rejoinSecondaryNodeConfigureThisLocationStep : replaceRejoin: reconfiguring this location with locationId ") + myNewLocationId);

        m_pThisLocation->setLocationId (myNewLocationId);
    }

    // Get the validation details, transfer those to the user from the message.
    // We will resuse those to send it to Local Cluster Conficuration service.

    pFrameworkObjectManagerRejoinClusterSecondaryMessage->getValidationDetails (sizeOfValidationDetails, pValidationDetailsBuffer, true);

    pSecondaryNodeClusterContext->executeNextStep (processingStatus);
}

/// Name
/// rejoinSecondaryNodeBootServicesPrePhaseStep
/// Description
/// This will trigger the bbot of some services 
/// in the first phase of rejoin processing.
/// Input
/// SecondaryNodeClusterContext:pointer to the context
/// Output
/// none
/// Return
/// none

void WaveFrameworkObjectManager::rejoinSecondaryNodeBootServicesPrePhaseStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::rejoinSecondaryNodeBootServicesPrePhaseStep : Entering ...");

    //The first parameter will result in the worker choosing a specific boot agent written especially for rejoin.
    //It will trigger the pre phase
    ResourceId status = m_pInitializeWorker->startWaveServices (WAVE_BOOT_SECONDARY_REJOIN, WAVE_BOOT_PHASE_PRE_PHASE);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::rejoinSecondaryNodeBootServicesPrePhaseStep : Booting Secondary during rejoin must NEVER fail.");
        waveAssert (false, __FILE__, __LINE__);
    }

    pSecondaryNodeClusterContext->executeNextStep (status);
}

/// Name
/// rejoinClusterSecondaryPhase2MessageHandler
/// Description
/// This handler establishes the steps to process te phase 2
/// rejoin message from the secondary and kick starts its processing.
/// Input
/// WaveRejoinClusterSecondaryPhase2Message: Pointer to phase 2 message
/// Output
/// none
/// Return
/// none

void WaveFrameworkObjectManager::rejoinClusterSecondaryPhase2MessageHandler (WaveRejoinClusterSecondaryPhase2Message *pWaveRejoinClusterSecondaryPhase2Message)
{
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::stopClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::updateLocationRoleStepInRejoinPhase2),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinSecondaryNodePhase2BootServicesPostPhaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodePhase2ReplaceNodeIfNeededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodePhase2ConfigureThisLocationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::startClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::secondaryNodeClusterFailureStep),
    };

    SecondaryNodeClusterPhase2Context *pSecondaryNodeClusterPhase2Context = new SecondaryNodeClusterPhase2Context (pWaveRejoinClusterSecondaryPhase2Message, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]), false);

    pSecondaryNodeClusterPhase2Context->holdAll ();
    pSecondaryNodeClusterPhase2Context->start ();
}

void WaveFrameworkObjectManager::updateLocationRoleStepInRejoinPhase2 (SecondaryNodeClusterPhase2Context *pSecondaryNodeClusterPhase2Context)
{
    LocationRole locationRole = m_pThisLocation->getLocationRole ();

    if (LOCATION_SECONDARY_REJOIN_PHASE_1 == locationRole)
    {
    m_pThisLocation->setLocationRole (LOCATION_SECONDARY_REJOIN_PHASE_2);
    pSecondaryNodeClusterPhase2Context->executeNextStep (WAVE_MESSAGE_SUCCESS);
}
    else
    {
        trace (TRACE_LEVEL_WARN, "WaveFrameworkObjectManager::updateLocationRoleStepInRejoinPhase2 received Message in incorrect location role, return with error");
        pSecondaryNodeClusterPhase2Context->executeNextStep (WAVE_MESSAGE_ERROR);
    }
}

/// Name
/// rejoinClusterSecondaryPhase2MessageHandler
/// Description
/// This function restarts all the services on the 
/// Input
/// SecondaryNodeClusterContext: pointer to ctxt 
/// Output
/// none
/// Return
/// none

void WaveFrameworkObjectManager::rejoinSecondaryNodePhase2BootServicesPostPhaseStep (SecondaryNodeClusterPhase2Context *pSecondaryNodeClusterPhase2Context)
{
    trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::rejoinSecondaryNodePhase2BootServicesPostPhaseStep : Entering ...");

    //The first argument results in selection of specific boot agent for rejoin node
    ResourceId status = m_pInitializeWorker->startWaveServices (WAVE_BOOT_SECONDARY_REJOIN, WAVE_BOOT_PHASE_POST_PHASE);

    // Instead of asserting, rollback to last known good state.

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_INFO, "rejoinSecondaryNodePhase2BootServicesPostPhaseStep: Rollback to last known state");

        disconnectFromAllConnectedNodes ();

        ResourceId rollbackStatus = m_pWaveFinalizeWorker->shutdownWaveServices (WAVE_SHUTDOWN_SECONDARY_ROLLBACK);

        if (WAVE_MESSAGE_SUCCESS != rollbackStatus)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::rejoinSecondaryNodePhase2BootServicesPostPhaseStep : shutdown should Never Fail");
            waveAssert (false, __FILE__, __LINE__);
        }

        rollbackStatus = m_pInitializeWorker->startWaveServices (WAVE_BOOT_PERSISTENT, WAVE_BOOT_ROLL_BACK_BOOT_PHASE_AFTER_PHASE_2);

        if (WAVE_MESSAGE_SUCCESS != rollbackStatus)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::rejoinSecondaryNodePhase2BootServicesPostPhaseStep : Roll Back should Never Fail");
            waveAssert (false, __FILE__, __LINE__);
        }
    }

#if 0
    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::rejoinSecondaryNodePhase2BootServicesPostPhaseStep : Booting Secondary immediately after configuring must NEVER fail.");
        waveAssert (false, __FILE__, __LINE__);
    }
#endif
    pSecondaryNodeClusterPhase2Context->executeNextStep (status);
}

void WaveFrameworkObjectManager::rejoinClusterSecondaryPhase3MessageHandler (WaveRejoinClusterSecondaryPhase3Message *pWaveRejoinClusterSecondaryPhase3Message)
{
    SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context = NULL;

    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinClusterSecondaryPhase3MessageHandler: (ACTIVE)");

    if (getIsPostBootNeededDuringRejoin ())
    {
        // Perform post boot in this case after backend sync up.
        // Backend sync up is done as part of rejoinSecondaryNodePhase3BootServicesAfterPostPhaseStep

        WaveLinearSequencerStep sequencerSteps[] =
        {
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::stopClusterPhaseTimer),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::updateLocationRoleStepInRejoinPhase3),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::broadcastClusterPhase3StartEvent),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinSecondaryHaPeerPostPhaseStep),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinSecondaryNodePhase3BootServicesAfterPostPhaseStep),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodePhase3ExecutePostBootStep),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::updateLocationRoleStepInRejoinPhase3Complete),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::broadcastClusterPhase3CompleteEvent),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodePhase3SendStartHearBeat),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::checkHaPeerSyncPostPhaseStep),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerFailedStep),
        };

        pSecondaryNodeClusterPhase3Context = new SecondaryNodeClusterPhase3Context (pWaveRejoinClusterSecondaryPhase3Message, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

        pSecondaryNodeClusterPhase3Context->holdAll ();
        pSecondaryNodeClusterPhase3Context->start ();

    }
    else
    {
        WaveLinearSequencerStep sequencerSteps[] =
        {
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::stopClusterPhaseTimer),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::updateLocationRoleStepInRejoinPhase3),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::broadcastClusterPhase3StartEvent),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinSecondaryHaPeerPostPhaseStep),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinSecondaryNodePhase3BootServicesAfterPostPhaseStep),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::updateLocationRoleStepInRejoinPhase3Complete),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::broadcastClusterPhase3CompleteEvent),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodePhase3SendStartHearBeat),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::checkHaPeerSyncPostPhaseStep),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
            reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerFailedStep),
        };

        pSecondaryNodeClusterPhase3Context = new SecondaryNodeClusterPhase3Context (pWaveRejoinClusterSecondaryPhase3Message, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

        pSecondaryNodeClusterPhase3Context->holdAll ();
        pSecondaryNodeClusterPhase3Context->start ();
    }
}

void WaveFrameworkObjectManager::rejoinClusterSecondaryHaPeerPhase3MessageHandler (WaveRejoinClusterSecondaryHaPeerPhase3Message *pWaveRejoinClusterSecondaryHaPeerPhase3Message)
{
    SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context = NULL;

    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinClusterSecondaryPhase3MessageHandler: (STANDBY)");

    WaveLinearSequencerStep sequencerSteps[] =
    {
        //reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::stopClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prepareStandbyAfterClusterPhaseSync),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerFailedStep),
    };

    pSecondaryNodeClusterPhase3Context = new SecondaryNodeClusterPhase3Context (pWaveRejoinClusterSecondaryHaPeerPhase3Message, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pSecondaryNodeClusterPhase3Context->holdAll ();
    pSecondaryNodeClusterPhase3Context->start ();
}

void WaveFrameworkObjectManager::rejoinSecondaryHaPeerPrePhaseStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    WaveRejoinClusterSecondaryPhase1Message *pWaveRejoinClusterSecondaryPhase1Message = reinterpret_cast<WaveRejoinClusterSecondaryPhase1Message *> (pSecondaryNodeClusterContext->getPWaveMessage ());
    waveAssert (NULL != pWaveRejoinClusterSecondaryPhase1Message, __FILE__, __LINE__);

    if ( (WAVE_MESSAGE_SUCCESS == FrameworkToolKit::isConnectedToHaPeerLocation ()) && (true == FrameworkToolKit::getIsLiveSyncEnabled ()) )
    {
        WaveRejoinClusterSecondaryHaPeerPhase1Message *pWaveRejoinClusterSecondaryHaPeerPhase1Message = new WaveRejoinClusterSecondaryHaPeerPhase1Message;
        waveAssert (NULL != pWaveRejoinClusterSecondaryHaPeerPhase1Message, __FILE__, __LINE__);

        pWaveRejoinClusterSecondaryHaPeerPhase1Message->copyBuffersFrom (*pWaveRejoinClusterSecondaryPhase1Message);

        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinSecondaryHaPeerPrePhaseStep: Ha Peer is connected and Live Sync enabled.");

        ResourceId haPeerSendStatus = send (pWaveRejoinClusterSecondaryHaPeerPhase1Message, reinterpret_cast<WaveMessageResponseHandler> (&WaveFrameworkObjectManager::rejoinSecondaryHaPeerPrePhaseCallback), pSecondaryNodeClusterContext, 200000, FrameworkToolKit::getHaPeerLocationId ());

        if (WAVE_MESSAGE_SUCCESS != haPeerSendStatus)
        {
            trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::rejoinSecondaryHaPeerPrePhaseStep: Send to Ha Peer failed.");
            delete pWaveRejoinClusterSecondaryHaPeerPhase1Message;
            FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
        }
        else
        {
            if (false == pSecondaryNodeClusterContext->getClusterHaSyncInProgress ())
            {
                trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinSecondaryHaPeerPrePhaseStep: Cluster Pre-Phase to Ha Peer start.");
                pSecondaryNodeClusterContext->setClusterHaSyncInProgress (true);
            }
        }
    }
    else
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinSecondaryHaPeerPrePhaseStep: Ha Peer is unavailable OR Live sync is disabled.");
    }

    pSecondaryNodeClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::rejoinSecondaryHaPeerPrePhaseCallback (FrameworkStatus frameworkStatus, WaveRejoinClusterSecondaryHaPeerPhase1Message *pWaveRejoinClusterSecondaryHaPeerPhase1Message, void *pContext)
{
    //trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinSecondaryHaPeerPrePhaseCallback: Begin.");
    
    if (FRAMEWORK_SUCCESS != frameworkStatus)
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::rejoinSecondaryHaPeerPrePhaseCallback: Failed to configure Peer, Framework Status: " + FrameworkToolKit::localize (frameworkStatus));
        FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
    }
    else
    {
        ResourceId status = pWaveRejoinClusterSecondaryHaPeerPhase1Message->getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::rejoinSecondaryHaPeerPrePhaseCallback: Failed to configure Peer, Completion Status: " + FrameworkToolKit::localize (status));
            FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
        }
    }

    if (NULL != pWaveRejoinClusterSecondaryHaPeerPhase1Message)
    {
        delete pWaveRejoinClusterSecondaryHaPeerPhase1Message;
    }

    SecondaryNodeClusterContext *pSecondaryNodeClusterContext = reinterpret_cast<SecondaryNodeClusterContext *> (pContext); 

    if (true == pSecondaryNodeClusterContext->getClusterHaSyncInProgress ())
    {
        pSecondaryNodeClusterContext->setClusterHaSyncInProgress (false);

        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinSecondaryHaPeerPrePhaseCallback: Cluster Pre-Phase to Ha Peer end.");

        if ( (pSecondaryNodeClusterContext->getNumberOfCallbacksBeforeAdvancingToNextStep ()) > 0)
        {
            --(*pSecondaryNodeClusterContext);
            pSecondaryNodeClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        }
    }
}

void WaveFrameworkObjectManager::rejoinSecondaryHaPeerPostPhaseStep (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context)
{
    WaveRejoinClusterSecondaryPhase3Message *pWaveRejoinClusterSecondaryPhase3Message = reinterpret_cast<WaveRejoinClusterSecondaryPhase3Message *> (pSecondaryNodeClusterPhase3Context->getPWaveMessage ());
    waveAssert (NULL != pWaveRejoinClusterSecondaryPhase3Message, __FILE__, __LINE__);

    if ( (WAVE_MESSAGE_SUCCESS == FrameworkToolKit::isConnectedToHaPeerLocation ()) && (true == FrameworkToolKit::getIsLiveSyncEnabled ()) )
    {
        WaveRejoinClusterSecondaryHaPeerPhase3Message *pWaveRejoinClusterSecondaryHaPeerPhase3Message = new WaveRejoinClusterSecondaryHaPeerPhase3Message;
        waveAssert (NULL != pWaveRejoinClusterSecondaryHaPeerPhase3Message, __FILE__, __LINE__);

        pWaveRejoinClusterSecondaryHaPeerPhase3Message->copyBuffersFrom (*pWaveRejoinClusterSecondaryPhase3Message);

        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinSecondaryHaPeerPostPhaseStep: Ha Peer is connected and Live Sync enabled.");

        ResourceId haPeerSendStatus = send (pWaveRejoinClusterSecondaryHaPeerPhase3Message, reinterpret_cast<WaveMessageResponseHandler> (&WaveFrameworkObjectManager::rejoinSecondaryHaPeerPostPhaseCallback), pSecondaryNodeClusterPhase3Context, s_clusterPhase3TimeoutInMilliseconds, FrameworkToolKit::getHaPeerLocationId ());

        if (WAVE_MESSAGE_SUCCESS != haPeerSendStatus)
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinSecondaryHaPeerPostPhaseStep: Send to Ha Peer failed.");
            delete pWaveRejoinClusterSecondaryHaPeerPhase3Message;
            FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
        }
        else
        {
            if (false == pSecondaryNodeClusterPhase3Context->getClusterHaSyncInProgress ())
            {
                trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinSecondaryHaPeerPostPhaseStep: Cluster Post-Phase to Ha Peer start.");
                pSecondaryNodeClusterPhase3Context->setClusterHaSyncInProgress (true);
            }
        }
    }
    else
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinSecondaryHaPeerPostPhaseStep: Ha Peer is unavailable OR Live sync is disabled.");
    }

    pSecondaryNodeClusterPhase3Context->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::rejoinSecondaryHaPeerPostPhaseCallback (FrameworkStatus frameworkStatus, WaveRejoinClusterSecondaryHaPeerPhase3Message *pWaveRejoinClusterSecondaryHaPeerPhase3Message, void *pContext)
{
    //trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinSecondaryHaPeerPostPhaseCallback: Begin.");
 
    if (FRAMEWORK_SUCCESS != frameworkStatus)
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::rejoinSecondaryHaPeerPostPhaseCallback: Failed to configure Peer, Framework Status: " + FrameworkToolKit::localize (frameworkStatus));
        FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
    }
    else
    {
        ResourceId status = pWaveRejoinClusterSecondaryHaPeerPhase3Message->getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::rejoinSecondaryHaPeerPostPhaseCallback: Failed to configure Peer, Completion Status: " + FrameworkToolKit::localize (status));
            FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
        }
    }

    if (NULL != pWaveRejoinClusterSecondaryHaPeerPhase3Message)
    {
        delete pWaveRejoinClusterSecondaryHaPeerPhase3Message;
    }

    SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context = reinterpret_cast<SecondaryNodeClusterPhase3Context *> (pContext); 

    if (true == pSecondaryNodeClusterPhase3Context->getClusterHaSyncInProgress ())
    {
        pSecondaryNodeClusterPhase3Context->setClusterHaSyncInProgress (false);

        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinSecondaryHaPeerPostPhaseCallback: Cluster Post-phase to Ha Peer end.");

        if ( (pSecondaryNodeClusterPhase3Context->getNumberOfCallbacksBeforeAdvancingToNextStep ()) > 0)
        {
            --(*pSecondaryNodeClusterPhase3Context);
            pSecondaryNodeClusterPhase3Context->executeNextStep (WAVE_MESSAGE_SUCCESS);
        }
    }

}

void WaveFrameworkObjectManager::updateLocationRoleStepInRejoinPhase3 (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context)
{
    LocationRole locationRole = m_pThisLocation->getLocationRole ();

    if (LOCATION_SECONDARY_REJOIN_PHASE_2 == locationRole)
    {
    m_pThisLocation->setLocationRole (LOCATION_SECONDARY_REJOIN_PHASE_3);
    pSecondaryNodeClusterPhase3Context->executeNextStep (WAVE_MESSAGE_SUCCESS);
}
    else
    {
        trace (TRACE_LEVEL_WARN, "WaveFrameworkObjectManager::updateLocationRoleStepInRejoinPhase3 received Message in incorrect location role, return with error");
        pSecondaryNodeClusterPhase3Context->executeNextStep (WAVE_MESSAGE_ERROR);
    }
}

void WaveFrameworkObjectManager::updateLocationRoleStepInRejoinPhase3Complete (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context)
{
    m_pThisLocation->setLocationRole (LOCATION_SECONDARY);
    pSecondaryNodeClusterPhase3Context->executeNextStep (WAVE_MESSAGE_SUCCESS);
}
void WaveFrameworkObjectManager::rejoinSecondaryNodePhase3BootServicesAfterPostPhaseStep (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rejoinSecondaryNodePhase3BootServicesAfterPostPhaseStep : Entering ...");

    //The first argument results in selection of specific boot agent for rejoin node
    ResourceId status = m_pInitializeWorker->startWaveServices (WAVE_BOOT_SECONDARY_REJOIN, WAVE_BOOT_PHASE_AFTER_POST_PHASE);

    // Instead of asserting, rollback to last known good state.

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_INFO, "rejoinSecondaryNodePhase3BootServicesAfterPostPhaseStep: Rollback to last known state");

        disconnectFromAllConnectedNodes ();

        ResourceId rollbackStatus = m_pWaveFinalizeWorker->shutdownWaveServices (WAVE_SHUTDOWN_SECONDARY_ROLLBACK);

        if (WAVE_MESSAGE_SUCCESS != rollbackStatus)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::rejoinSecondaryNodePhase3BootServicesAfterPostPhaseStep : shutdown should Never Fail");
            waveAssert (false, __FILE__, __LINE__);
        }

        rollbackStatus = m_pInitializeWorker->startWaveServices (WAVE_BOOT_PERSISTENT, WAVE_BOOT_ROLL_BACK_BOOT_PHASE_AFTER_PHASE_2);

        if (WAVE_MESSAGE_SUCCESS != rollbackStatus)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::rejoinSecondaryNodePhase3BootServicesAfterPostPhaseStep : Roll Back should Never Fail");
            waveAssert (false, __FILE__, __LINE__);
        }
    }

#if 0
    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::rejoinSecondaryNodePhase3BootServicesAfterPostPhaseStep : Booting Secondary immediately after configuring must NEVER fail.");
        waveAssert (false, __FILE__, __LINE__);
    }
#endif
    pSecondaryNodeClusterPhase3Context->executeNextStep (status);

}



void WaveFrameworkObjectManager::detachFromClusterMessageHandler (FrameworkObjectManagerDetachFromClusterMessage *pFrameworkObjectManagerDetachFromClusterMessage)
{
    DetachFromClusterAsynchronousContext *pDetachFromClusterAsynchronousContext = new DetachFromClusterAsynchronousContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveFrameworkObjectManager::detachFromClusterMessageHandlerCallback), pFrameworkObjectManagerDetachFromClusterMessage);

    pDetachFromClusterAsynchronousContext->setReasonForDetachingFromCluster (pFrameworkObjectManagerDetachFromClusterMessage->getReasonForDetachingFromCluster ());

    detachFromClusterAsynchronousHandler (pDetachFromClusterAsynchronousContext);
}

void WaveFrameworkObjectManager::detachFromClusterMessageHandlerCallback (DetachFromClusterAsynchronousContext *pDetachFromClusterAsynchronousContext)
{
    waveAssert (NULL != pDetachFromClusterAsynchronousContext, __FILE__, __LINE__);

    FrameworkObjectManagerDetachFromClusterMessage *pFrameworkObjectManagerDetachFromClusterMessage = reinterpret_cast<FrameworkObjectManagerDetachFromClusterMessage *> (pDetachFromClusterAsynchronousContext->getPCallerContext ());

    waveAssert (NULL != pFrameworkObjectManagerDetachFromClusterMessage, __FILE__, __LINE__);

    pFrameworkObjectManagerDetachFromClusterMessage->setCompletionStatus (pDetachFromClusterAsynchronousContext->getCompletionStatus ());

    delete pDetachFromClusterAsynchronousContext;

    reply (pFrameworkObjectManagerDetachFromClusterMessage);
}

void WaveFrameworkObjectManager::detachFromClusterAsynchronousHandler (DetachFromClusterAsynchronousContext *pDetachFromClusterAsynchronousContext)
{
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::detachFromClusterValidateStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::unconfigureClusterSecondaryNodeBootServicesStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::detachFromClusterTerminateClientConnectionsForKnownLocationsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::detachFromClusterDisconnectFromKnownLocationsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::detachFromClusterUnconfigureThisLocationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::detachFromClusterRunFailoverStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerFailedStep),
    };

    DetachFromClusterContext *pDetachFromClusterContext = new DetachFromClusterContext (pDetachFromClusterAsynchronousContext, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pDetachFromClusterContext->setReasonForDetachingFromCluster (pDetachFromClusterAsynchronousContext->getReasonForDetachingFromCluster ());

    pDetachFromClusterContext->holdAll ();
    pDetachFromClusterContext->start ();
}

void WaveFrameworkObjectManager::detachFromClusterValidateStep (DetachFromClusterContext *pDetachFromClusterContext)
{
    LocationRole thisLocationRole = m_pThisLocation->getLocationRole ();

    pDetachFromClusterContext->setThisLocationRoleBeforeDetach (thisLocationRole);

    if (LOCATION_SECONDARY == thisLocationRole)
    {
        pDetachFromClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;
    }
    else
    {
        pDetachFromClusterContext->executeNextStep (FRAMEWORK_ERROR_ONLY_SECONDARY_CAN_DETACH_ITSELF_FROM_CLUSTER);
        return;
    }
}

void WaveFrameworkObjectManager::detachFromClusterTerminateClientConnectionsForKnownLocationsStep (DetachFromClusterContext *pDetachFromClusterContext)
{
    LocationId clusterPrimaryLocationId = m_pThisLocation->getClusterPrimaryLocationId ();
    string     clusterPrimaryIpAddress  = FrameworkToolKit::getIpAddressForLocationId (clusterPrimaryLocationId);
    SI32       clusterPrimaryPort       = FrameworkToolKit::getPortForLocationId (clusterPrimaryLocationId);

    InterLocationMessageReceiverObjectManager::terminateAndRemoveInterLocationMessageReceiverThreadFromCache (clusterPrimaryIpAddress, clusterPrimaryPort);

    pDetachFromClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::detachFromClusterDisconnectFromKnownLocationsStep (DetachFromClusterContext *pDetachFromClusterContext)
{
    LocationId clusterPrimaryLocationId = m_pThisLocation->getClusterPrimaryLocationId ();

    trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::detachFromClusterDisconnectFromKnownLocationsStep: Disconnect from location");
    disconnectFromLocation (clusterPrimaryLocationId);
    removeKnownLocation (clusterPrimaryLocationId);

    pDetachFromClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::detachFromClusterUnconfigureThisLocationStep (DetachFromClusterContext *pDetachFromClusterContext)
{
    LocationId thisLocationId = FrameworkToolKit::getThisLocationId ();

    m_pThisLocation->resetLocationToStandAlone (thisLocationId);
    m_lastUsedLocationId = thisLocationId;

    pDetachFromClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::detachFromClusterRunFailoverStep (DetachFromClusterContext *pDetachFromClusterContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::detachFromClusterRunFailoverStep : Entering ...");

    WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext = new WaveFrameworkFailoverWorkerContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveFrameworkObjectManager::detachFromClusterRunFailoverCallback), pDetachFromClusterContext);

    waveAssert (NULL != pWaveFrameworkFailoverWorkerContext, __FILE__, __LINE__);
    waveAssert (NULL != m_pWaveFrameworkFailoverWorker, __FILE__, __LINE__);

    pWaveFrameworkFailoverWorkerContext->setThisLocationRole (pDetachFromClusterContext->getThisLocationRoleBeforeDetach ());
    pWaveFrameworkFailoverWorkerContext->setFailoverReason (pDetachFromClusterContext->getReasonForDetachingFromCluster ());

    m_pWaveFrameworkFailoverWorker->executeFailover (pWaveFrameworkFailoverWorkerContext);
}

void WaveFrameworkObjectManager::detachFromClusterRunFailoverCallback (WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::detachFromClusterRunFailoverCallback : Entering ...");

    waveAssert (NULL != pWaveFrameworkFailoverWorkerContext, __FILE__, __LINE__);

    DetachFromClusterContext *pDetachFromClusterContext = reinterpret_cast<DetachFromClusterContext *> (pWaveFrameworkFailoverWorkerContext->getPCallerContext ());
    ResourceId                status                    = pWaveFrameworkFailoverWorkerContext->getCompletionStatus ();

    delete pWaveFrameworkFailoverWorkerContext;

    waveAssert (NULL != pDetachFromClusterContext, __FILE__, __LINE__);

    pDetachFromClusterContext->executeNextStep (status);
}

void WaveFrameworkObjectManager::lostHeartBeatMessageHandler (FrameworkObjectManagerLostHeartBeatMessage *pFrameworkObjectManagerLostHeartBeatMessage)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::lostHeartBeatMessageHandler : Entering ...");

    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::lostHeartBeatStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerFailedStep),
    };

    HeartBeatLostContext *pHeartBeatLostContext      = new HeartBeatLostContext (pFrameworkObjectManagerLostHeartBeatMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));
    UI32                  numberOfHeartBeatLostNodes = pFrameworkObjectManagerLostHeartBeatMessage->getNumberOfNodes ();
    UI32                  i                          = 0;

    // Transfer the details about failed nodes into the context.

    for (i = 0; i < numberOfHeartBeatLostNodes; i++)
    {
        pHeartBeatLostContext->addNodeIpAddressAndPort (pFrameworkObjectManagerLostHeartBeatMessage->getNodeAt (i), pFrameworkObjectManagerLostHeartBeatMessage->getNodePortAt(i));
    }

    pHeartBeatLostContext->holdAll ();
    pHeartBeatLostContext->start ();
}

void WaveFrameworkObjectManager::lostHeartBeatStep (HeartBeatLostContext *pHeartBeatLostContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::lostHeartBeatCleanupClusterStep : Entering ...");

    UI32       numberOfFailedLocations = pHeartBeatLostContext->getNumberOfNodes ();
    UI32       i                       = 0;
    LocationId failedLocationId;
    string     failedIpAddress;
    UI32       failedPort;

    if (LOCATION_PRIMARY == (m_pThisLocation->getLocationRole ()))
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::lostHeartBeatCleanupClusterStep : Initiating Primary Un-Controlled Failover.");

        WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext = new WaveFrameworkFailoverWorkerContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveFrameworkObjectManager::lostHeartBeatPrimaryUncontrolledFailoverCallback), pHeartBeatLostContext);

        waveAssert (NULL != pWaveFrameworkFailoverWorkerContext, __FILE__, __LINE__);
        waveAssert (NULL != m_pWaveFrameworkFailoverWorker, __FILE__, __LINE__);

        pWaveFrameworkFailoverWorkerContext->setThisLocationRole (LOCATION_PRIMARY);
        pWaveFrameworkFailoverWorkerContext->setFailoverReason (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED);

        for (i = 0; i < numberOfFailedLocations; i++)
        {
            failedIpAddress = pHeartBeatLostContext->getNodeIpAddressAtIndex (i);
            failedPort      = pHeartBeatLostContext->getNodePortAtIndex (i);

            failedLocationId = FrameworkToolKit::getLocationIdForIpAddressAndPort (failedIpAddress, failedPort);

            pWaveFrameworkFailoverWorkerContext->addFailedLocationId (failedLocationId);
        }

        m_pWaveFrameworkFailoverWorker->executeFailover (pWaveFrameworkFailoverWorkerContext);
    }
    else if (LOCATION_SECONDARY == (m_pThisLocation->getLocationRole ()))
    {
        // On a secondary location there can be only one failed heart beat.  That heart beat will belong to the current primary node.  It is so because the secondaries heart beat with primary only.

        waveAssert (1 == numberOfFailedLocations, __FILE__, __LINE__);

        failedIpAddress = pHeartBeatLostContext->getNodeIpAddressAtIndex (i);
        failedPort      = pHeartBeatLostContext->getNodePortAtIndex (i);

        failedLocationId = FrameworkToolKit::getLocationIdForIpAddressAndPort (failedIpAddress, failedPort);

        waveAssert (failedLocationId == (m_pThisLocation->getClusterPrimaryLocationId ()), __FILE__, __LINE__);

        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::lostHeartBeatCleanupClusterStep : Initiating Role Arbitration Sequence.");

        vector<LocationId> connectedLocationsVector;
        UI32               numberOfConnectedLocations;
        LocationId         nextPrimaryCandidateLocationId = 0;
        string             nextPrimaryCandidateIpAddress;
        UI32               nextPrimaryCandidatePort;
        LocationId         thisLocationId                 = FrameworkToolKit::getThisLocationId ();

        // Add this location also into the list since it also can be a possible candidate.

        connectedLocationsVector.push_back (thisLocationId);
        FrameworkToolKit::getConnectedLocations (connectedLocationsVector);
        numberOfConnectedLocations = connectedLocationsVector.size ();

        nextPrimaryCandidateLocationId = connectedLocationsVector[0];

        for (i = 1; i < numberOfConnectedLocations; i++)
        {
            if (nextPrimaryCandidateLocationId > connectedLocationsVector[i])
            {
                nextPrimaryCandidateLocationId = connectedLocationsVector[i];
            }
        }

        nextPrimaryCandidateIpAddress = FrameworkToolKit::getIpAddressForLocationId (nextPrimaryCandidateLocationId);
        nextPrimaryCandidatePort      = FrameworkToolKit::getPortForLocationId      (nextPrimaryCandidateLocationId);

        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::lostHeartBeatStep : The Next Primary will be the following location : " + nextPrimaryCandidateIpAddress + string (":") + nextPrimaryCandidatePort + string (", ") + nextPrimaryCandidateLocationId);

        if (nextPrimaryCandidateLocationId == thisLocationId)
        {
            // Activate the Secondary Uncontrolled Failover Agent.

            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::lostHeartBeatCleanupClusterStep : Initiating Secondary Un-Controlled Failover.");

            WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext = new WaveFrameworkFailoverWorkerContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveFrameworkObjectManager::lostHeartBeatSecondaryUncontrolledFailoverCallback), pHeartBeatLostContext);

            waveAssert (NULL != pWaveFrameworkFailoverWorkerContext, __FILE__, __LINE__);
            waveAssert (NULL != m_pWaveFrameworkFailoverWorker, __FILE__, __LINE__);

            pWaveFrameworkFailoverWorkerContext->setThisLocationRole (LOCATION_SECONDARY);
            pWaveFrameworkFailoverWorkerContext->setFailoverReason (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED);

            for (i = 0; i < numberOfFailedLocations; i++)
            {
                failedIpAddress = pHeartBeatLostContext->getNodeIpAddressAtIndex (i);
                failedPort      = pHeartBeatLostContext->getNodePortAtIndex (i);

                failedLocationId = FrameworkToolKit::getLocationIdForIpAddressAndPort (failedIpAddress, failedPort);

                pWaveFrameworkFailoverWorkerContext->addFailedLocationId (failedLocationId);
            }

            m_pWaveFrameworkFailoverWorker->executeFailover (pWaveFrameworkFailoverWorkerContext);
        }
        else
        {
            // Otherwise simply proceed and finish.  The next Primary candidate will take over.
            // FIXME : sagar : however, we need to arm a timer here and check if some one has really taken over or not.
            //                 There can be a case where the next primary candidate can fail in the middle of taking over.

            pHeartBeatLostContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        }
    }
    else
    {
        trace (TRACE_LEVEL_WARN, "WaveFrameworkObjectManager::lostHeartBeatCleanupClusterStep : We got a Heartbeat Lost Message when there is no cluster created.  Simply ignoring the message.");
        pHeartBeatLostContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
}

void WaveFrameworkObjectManager::lostHeartBeatPrimaryUncontrolledFailoverCallback (WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::lostHeartBeatPrimaryUncontrolledFailoverCallback : Entering ...");

    waveAssert (NULL != pWaveFrameworkFailoverWorkerContext, __FILE__, __LINE__);

    HeartBeatLostContext *pHeartBeatLostContext = reinterpret_cast<HeartBeatLostContext *> (pWaveFrameworkFailoverWorkerContext->getPCallerContext ());
    ResourceId            status                = pWaveFrameworkFailoverWorkerContext->getCompletionStatus ();

    delete pWaveFrameworkFailoverWorkerContext;

    waveAssert (NULL != pHeartBeatLostContext, __FILE__, __LINE__);

    pHeartBeatLostContext->executeNextStep (status);
}

void WaveFrameworkObjectManager::lostHeartBeatSecondaryUncontrolledFailoverCallback (WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::lostHeartBeatSecondaryUncontrolledFailoverCallback : Entering ...");

    waveAssert (NULL != pWaveFrameworkFailoverWorkerContext, __FILE__, __LINE__);

    HeartBeatLostContext    *pHeartBeatLostContext = reinterpret_cast<HeartBeatLostContext *> (pWaveFrameworkFailoverWorkerContext->getPCallerContext ());
    ResourceId               status                = pWaveFrameworkFailoverWorkerContext->getCompletionStatus ();

    delete pWaveFrameworkFailoverWorkerContext;

    waveAssert (NULL != pHeartBeatLostContext, __FILE__, __LINE__);

    pHeartBeatLostContext->executeNextStep (status);
}

void WaveFrameworkObjectManager::lostHeartBeatSecondaryControlledFailoverCallback (WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::lostHeartBeatSecondaryControlledFailoverCallback : Entering ...");

    waveAssert (NULL != pWaveFrameworkFailoverWorkerContext, __FILE__, __LINE__); 
    HeartBeatLostContext *pHeartBeatLostContext = reinterpret_cast<HeartBeatLostContext *> (pWaveFrameworkFailoverWorkerContext->getPCallerContext ());
    ResourceId            status                = pWaveFrameworkFailoverWorkerContext->getCompletionStatus ();

    vector<LocationId> failedLocationIds;
    UI32               numberOfFailedLocations;

    pWaveFrameworkFailoverWorkerContext->getFailedLocationIds (failedLocationIds); 
    numberOfFailedLocations = failedLocationIds.size ();

    for (UI32 i = 0; i < numberOfFailedLocations; i++)
    {
        removeKnownLocation (failedLocationIds [i]);
    }
    
    delete pWaveFrameworkFailoverWorkerContext;

    waveAssert (NULL != pHeartBeatLostContext, __FILE__, __LINE__);

    pHeartBeatLostContext->executeNextStep (status);
}

void WaveFrameworkObjectManager::lostHeartBeatCleanupClusterDestroyClusterCallback (DestroyClusterAsynchronousContext *pDestroyClusterAsynchronousContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::lostHeartBeatCleanupClusterDestroyClusterCallback : Entering ...");

    waveAssert (NULL != pDestroyClusterAsynchronousContext, __FILE__, __LINE__);

    HeartBeatLostContext *pHeartBeatLostContext = reinterpret_cast<HeartBeatLostContext *> (pDestroyClusterAsynchronousContext->getPCallerContext ());

    waveAssert (NULL != pHeartBeatLostContext, __FILE__, __LINE__);

    ResourceId status = pDestroyClusterAsynchronousContext->getCompletionStatus ();

    delete pDestroyClusterAsynchronousContext;

    pHeartBeatLostContext->executeNextStep (status);
}

void WaveFrameworkObjectManager::lostHeartBeatCleanupClusterDetachFromClusterCallback (DetachFromClusterAsynchronousContext *pDetachFromClusterAsynchronousContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::lostHeartBeatCleanupClusterDetachFromClusterCallback : Entering ...");

    waveAssert (NULL != pDetachFromClusterAsynchronousContext, __FILE__, __LINE__);

    HeartBeatLostContext *pHeartBeatLostContext = reinterpret_cast<HeartBeatLostContext *> (pDetachFromClusterAsynchronousContext->getPCallerContext ());

    waveAssert (NULL != pHeartBeatLostContext, __FILE__, __LINE__);

    ResourceId status = pDetachFromClusterAsynchronousContext->getCompletionStatus ();

    delete pDetachFromClusterAsynchronousContext;

    pHeartBeatLostContext->executeNextStep (status);
}

void WaveFrameworkObjectManager::startExternalStateSynchronizationHandler(FrameworkObjectManagerStartExternalStateSynchronizationMessage *pFrameworkObjectManagerStartExternalStateSynchronizationMessage)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::startExternalStateSynchronizationHandler : Start the External State Synchronization .... ");

    int stageNumber = pFrameworkObjectManagerStartExternalStateSynchronizationMessage->getFssStageNumber();
    
    ResourceId serviceType = pFrameworkObjectManagerStartExternalStateSynchronizationMessage->getServiceType();

    string perfTraceStr = string("ESS Bootup; stage: ") + stageNumber + string("; service-type: ") + FrameworkToolKit::localize(serviceType);
    trace (TRACE_LEVEL_PERF_START, perfTraceStr);

    WaveExternalStateSynchronizationAgent *pWaveExternalStateSynchronization = new WaveExternalStateSynchronizationAgent (m_pWaveObjectManager, stageNumber, serviceType);

    pWaveExternalStateSynchronization->execute ();

    delete pWaveExternalStateSynchronization;

    pFrameworkObjectManagerStartExternalStateSynchronizationMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    reply (pFrameworkObjectManagerStartExternalStateSynchronizationMessage);

    trace (TRACE_LEVEL_PERF_END, perfTraceStr);
}

void WaveFrameworkObjectManager::startSlotFailoverHandler (FrameworkObjectManagerStartSlotFailoverMessage *pFrameworkObjectManagerStartSlotFailoverMessage)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::startSlotFailoverHandler : Start the SlotFailover Agent.... ");

    int slotNumber = pFrameworkObjectManagerStartSlotFailoverMessage->getSlotNumber ();
    
    SlotFailoverAgent *pSlotFailoverAgent = new SlotFailoverAgent (m_pWaveObjectManager, slotNumber);

    pSlotFailoverAgent->execute ();

    delete pSlotFailoverAgent;
    
    pFrameworkObjectManagerStartSlotFailoverMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);

    reply (pFrameworkObjectManagerStartSlotFailoverMessage);

}

void WaveFrameworkObjectManager::primaryChangedMessageHandler (FrameworkObjectManagerPrimaryChangedMessage *pFrameworkObjectManagerPrimaryChangedMessage)
{
    SecondaryNodeClusterContext *pSecondaryNodeClusterContext = NULL;
    
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::primaryChangedMessageHandler: Received Primary changed notification(ACTIVE).");

    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::primaryChangedValidateStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::removePreviousDatabaseBackupFile),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::primaryChangedStopHeartBeatToOldPrimayStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinSecondaryNodeShutdownServicesStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::primaryChangedUpdatePrimaryDetailsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinSecondaryNodeBootServicesPrePhaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::primaryChangedNotifyHaPeerStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeBackupCurrentDatabaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeCleanPreparedTransactionsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::primaryChangedEmptyDatabaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::startClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::checkHaPeerSyncStatusStep),

        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::secondaryNodeClusterFailureStep),
    };

    pSecondaryNodeClusterContext = new SecondaryNodeClusterContext (pFrameworkObjectManagerPrimaryChangedMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pSecondaryNodeClusterContext->setClusterPrimaryIpAddress  (pFrameworkObjectManagerPrimaryChangedMessage->getNewPrimaryIpAddress ());
    pSecondaryNodeClusterContext->setClusterPrimaryPort       (pFrameworkObjectManagerPrimaryChangedMessage->getNewPrimaryPort ());
    pSecondaryNodeClusterContext->setClusterPrimaryLocationId (pFrameworkObjectManagerPrimaryChangedMessage->getNewPrimaryLocationId ());

    pSecondaryNodeClusterContext->holdAll ();
    pSecondaryNodeClusterContext->start ();
}

void WaveFrameworkObjectManager::primaryChangedHaPeerMessageHandler (FrameworkObjectManagerPrimaryChangedHaPeerMessage *pFrameworkObjectManagerPrimaryChangedHaPeerMessage)
{
    SecondaryNodeClusterContext *pSecondaryNodeClusterContext = NULL;

    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::primaryChangedHaPeerMessageHandler: (STANDBY)");

    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::removePreviousDatabaseBackupFile),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinSecondaryNodeShutdownServicesStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeBootServicesPrePhaseForStandbyStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeBackupCurrentDatabaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinSecondaryNodeSetLocationRoleOnStandbyStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeCleanPreparedTransactionsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::primaryChangedEmptyDatabaseStep),
        //reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::startClusterPhaseTimer),

        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerFailedStep),
    };

    pSecondaryNodeClusterContext = new SecondaryNodeClusterContext (pFrameworkObjectManagerPrimaryChangedHaPeerMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pSecondaryNodeClusterContext->setDBEmptyRequired (pFrameworkObjectManagerPrimaryChangedHaPeerMessage->getIsDBEmptyRequired ());

    pSecondaryNodeClusterContext->holdAll ();
    pSecondaryNodeClusterContext->start ();
}

void WaveFrameworkObjectManager::primaryChangedPhase1MessageHandler (FrameworkObjectManagerPrimaryChangedPhase1Message *pFrameworkObjectManagerPrimaryChangedPhase1Message)
{
    SecondaryNodeClusterContext *pSecondaryNodeClusterContext = NULL;

    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::primaryChangedPhase1MessageHandler: Received Primary changed notification: (ACTIVE)");

    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::stopClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::updateLocationRoleStepInRejoinPhase1),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::primaryChangedHaPeerPrePhaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::primaryChangedLoadDatabaseFromPrimaryDatabaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodeUpdateInstanceIdsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::startClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::checkHaPeerSyncStatusStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::secondaryNodeClusterFailureStep),
    };

    pSecondaryNodeClusterContext = new SecondaryNodeClusterContext (pFrameworkObjectManagerPrimaryChangedPhase1Message, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    UI64 trackingNumber                 = PersistenceLocalObjectManager::getAnyConfigurationChangeTrackingNumber ();
    UI64 primaryPrincipalTrackingNumber = pFrameworkObjectManagerPrimaryChangedPhase1Message->getAnyConfigurationChangeTrackingNumber ();

    if (trackingNumber == primaryPrincipalTrackingNumber)
    {
        pSecondaryNodeClusterContext->setDBEmptyRequired (false);
    }

    pSecondaryNodeClusterContext->holdAll ();
    pSecondaryNodeClusterContext->start ();
}

void WaveFrameworkObjectManager::primaryChangedHaPeerPhase1MessageHandler (FrameworkObjectManagerPrimaryChangedHaPeerPhase1Message *pFrameworkObjectManagerPrimaryChangedHaPeerPhase1Message)
{
    SecondaryNodeClusterContext *pSecondaryNodeClusterContext = NULL;

    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::primaryChangedPhase1MessageHandler: Received Primary changed notification: (STANDBY)");

    WaveLinearSequencerStep sequencerSteps[] =
    {
        //reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::stopClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::primaryChangedLoadDatabaseFromPrimaryDatabaseStep),
        //reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::startClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerFailedStep),
    };

    pSecondaryNodeClusterContext = new SecondaryNodeClusterContext (pFrameworkObjectManagerPrimaryChangedHaPeerPhase1Message, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pSecondaryNodeClusterContext->setDBEmptyRequired (pFrameworkObjectManagerPrimaryChangedHaPeerPhase1Message->getIsDBRestoreRequired ());

    pSecondaryNodeClusterContext->holdAll ();
    pSecondaryNodeClusterContext->start ();

}

void WaveFrameworkObjectManager::primaryChangedValidateStep ( WaveLinearSequencerContext *pWaveLinearSequencerContext )
{

    if (getNumberOfLineCardPostBootCurrentlyRunning ())
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::primaryChangedValidateStep :LC Postboot in progress. Returning error.");
        pWaveLinearSequencerContext->executeNextStep (FRAMEWORK_LINECARD_POSTBOOT_IN_PROGRESS);
        return;
    }    

    LocationRole locationRole = m_pThisLocation->getLocationRole ();

    if ( LOCATION_SECONDARY == locationRole)
    {
        pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
    else
    {
        trace (TRACE_LEVEL_WARN, string("WaveFrameworkObjectManager::primaryChangedValidateStep : received Message in incorrect location role : ") + FrameworkToolKit::localize(locationRole) + (", return with error"));
        pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_ERROR);
    }
}

void WaveFrameworkObjectManager::primaryChangedNotifyHaPeerStep ( SecondaryNodeClusterContext *pSecondaryNodeClusterContext )
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::primaryChangedNotifyHaPeerStep: Entering \n");

    if ( (WAVE_MESSAGE_SUCCESS == FrameworkToolKit::isConnectedToHaPeerLocation ()) && (true == FrameworkToolKit::getIsLiveSyncEnabled ()) )
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::primaryChangedNotifyHaPeerStep: Ha Peer is connected and Live Sync enabled.");

        FrameworkObjectManagerPrimaryChangedMessage *pFrameworkObjectManagerPrimaryChangedMessage = dynamic_cast<FrameworkObjectManagerPrimaryChangedMessage *> (pSecondaryNodeClusterContext->getPWaveMessage ());
        waveAssert(NULL != pFrameworkObjectManagerPrimaryChangedMessage, __FILE__ , __LINE__);

        FrameworkObjectManagerPrimaryChangedHaPeerMessage *pFrameworkObjectManagerPrimaryChangedHaPeerMessage = new FrameworkObjectManagerPrimaryChangedHaPeerMessage;

        pFrameworkObjectManagerPrimaryChangedHaPeerMessage->setDBEmptyRequired (pSecondaryNodeClusterContext->getIsDBEmptyRequired ());

        waveAssert (NULL != pFrameworkObjectManagerPrimaryChangedHaPeerMessage, __FILE__, __LINE__);

        pFrameworkObjectManagerPrimaryChangedHaPeerMessage->copyBuffersFrom (*pFrameworkObjectManagerPrimaryChangedMessage);

        ResourceId haPeerSendStatus = send (pFrameworkObjectManagerPrimaryChangedHaPeerMessage, reinterpret_cast<WaveMessageResponseHandler> (&WaveFrameworkObjectManager::primaryChangedNotifyHaPeerMessageCallback), pSecondaryNodeClusterContext, 200000, FrameworkToolKit::getHaPeerLocationId ());

        if (WAVE_MESSAGE_SUCCESS != haPeerSendStatus)
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::primaryChangedNotifyHaPeerStep: Send to Ha Peer failed.");
            delete pFrameworkObjectManagerPrimaryChangedHaPeerMessage;
            FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
        }
        else
        {
            if (false == pSecondaryNodeClusterContext->getClusterHaSyncInProgress ())
            {
                trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::primaryChangedNotifyHaPeerStep: Cluster Phase 0 to Ha Peer start.");
                pSecondaryNodeClusterContext->setClusterHaSyncInProgress (true);
            }
        }
    }
    else if ((FrameworkToolKit::getSyncState () == IN_SYNC) && (false == FrameworkToolKit::getIsLiveSyncEnabled ()))
    {
        // DB previously in sync from sync dump. but live transaction sync not supported. So set out of sync and notify on sync update fail
        trace (TRACE_LEVEL_WARN, "WaveFrameworkObjectManager::primaryChangedNotifyHaPeerStep: Live sync disabled. Notify sync update failure on first update after sync dump.");
        FrameworkToolKit::notifySyncUpdateFailure(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_NOT_SUPPORTED);
    }
    else
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::primaryChangedNotifyHaPeerStep: Ha Peer is unavailable OR live sync disabled.");
    }

    pSecondaryNodeClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::primaryChangedNotifyHaPeerMessageCallback (FrameworkStatus frameworkStatus, FrameworkObjectManagerPrimaryChangedHaPeerMessage *pFrameworkObjectManagerPrimaryChangedHaPeerMessage, void *pContext)
{
    //trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::primaryChangedNotifyHaPeerMessageCallback: Begin.");
 
    if (FRAMEWORK_SUCCESS != frameworkStatus)
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::primaryChangedNotifyHaPeerMessageCallback: Failed to configure Peer, Framework Status: " + FrameworkToolKit::localize (frameworkStatus));
        FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
    }
    else
    {
        ResourceId status = pFrameworkObjectManagerPrimaryChangedHaPeerMessage->getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::primaryChangedNotifyHaPeerMessageCallback: Failed to configure Peer, Completion Status: " + FrameworkToolKit::localize (status));
            FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
        }
    }

    if (NULL != pFrameworkObjectManagerPrimaryChangedHaPeerMessage)
    {
        delete pFrameworkObjectManagerPrimaryChangedHaPeerMessage;
    }

    SecondaryNodeClusterContext *pSecondaryNodeClusterContext = reinterpret_cast<SecondaryNodeClusterContext *> (pContext); 

    if (true == pSecondaryNodeClusterContext->getClusterHaSyncInProgress ())
    {
        pSecondaryNodeClusterContext->setClusterHaSyncInProgress (false);

        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::primaryChangedNotifyHaPeerMessageCallback: Cluster Phase 0 to Ha Peer end.");

        if ( (pSecondaryNodeClusterContext->getNumberOfCallbacksBeforeAdvancingToNextStep ()) > 0)
        {
            --(*pSecondaryNodeClusterContext);
            pSecondaryNodeClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        }
    }
}

void WaveFrameworkObjectManager::primaryChangedHaPeerPrePhaseStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    FrameworkObjectManagerPrimaryChangedPhase1Message *pFrameworkObjectManagerPrimaryChangedPhase1Message = reinterpret_cast<FrameworkObjectManagerPrimaryChangedPhase1Message *> (pSecondaryNodeClusterContext->getPWaveMessage ());
    waveAssert (NULL != pFrameworkObjectManagerPrimaryChangedPhase1Message, __FILE__, __LINE__);

    if ( (WAVE_MESSAGE_SUCCESS == FrameworkToolKit::isConnectedToHaPeerLocation ()) && (true == FrameworkToolKit::getIsLiveSyncEnabled ()) )
    {
        FrameworkObjectManagerPrimaryChangedHaPeerPhase1Message *pFrameworkObjectManagerPrimaryChangedHaPeerPhase1Message = new FrameworkObjectManagerPrimaryChangedHaPeerPhase1Message;
        waveAssert (NULL != pFrameworkObjectManagerPrimaryChangedHaPeerPhase1Message, __FILE__, __LINE__);

        pFrameworkObjectManagerPrimaryChangedHaPeerPhase1Message->setDBRestoreRequired (pSecondaryNodeClusterContext->getIsDBEmptyRequired ());
        pFrameworkObjectManagerPrimaryChangedHaPeerPhase1Message->copyBuffersFrom (*pFrameworkObjectManagerPrimaryChangedPhase1Message);

        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::primaryChangedHaPeerPrePhaseStep: Ha Peer is connected and Live Sync enabled.");

        ResourceId haPeerSendStatus = send (pFrameworkObjectManagerPrimaryChangedHaPeerPhase1Message, reinterpret_cast<WaveMessageResponseHandler> (&WaveFrameworkObjectManager::primaryChangedHaPeerPrePhaseCallback), pSecondaryNodeClusterContext, 200000, FrameworkToolKit::getHaPeerLocationId ());

        if (WAVE_MESSAGE_SUCCESS != haPeerSendStatus)
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::primaryChangedHaPeerPrePhaseStep: Send to Ha Peer failed.");
            delete pFrameworkObjectManagerPrimaryChangedHaPeerPhase1Message;
            FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
        }
        else
        {
            if (false == pSecondaryNodeClusterContext->getClusterHaSyncInProgress ())
            {
                trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::primaryChangedHaPeerPrePhaseStep: Cluster Pre-phase to Ha Peer start.");
                pSecondaryNodeClusterContext->setClusterHaSyncInProgress (true);
            }
        }
    }
    else
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::primaryChangedHaPeerPrePhaseStep: Ha Peer is unavailable OR Live sync is disabled.");
    }

    pSecondaryNodeClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::primaryChangedHaPeerPrePhaseCallback (FrameworkStatus frameworkStatus, FrameworkObjectManagerPrimaryChangedHaPeerPhase1Message *pFrameworkObjectManagerPrimaryChangedHaPeerPhase1Message, void *pContext)
{
    //trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::primaryChangedHaPeerPrePhaseCallback: Starting.");
    
    if (FRAMEWORK_SUCCESS != frameworkStatus)
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::primaryChangedHaPeerPrePhaseCallback: Failed to configure Peer, Framework Status: " + FrameworkToolKit::localize (frameworkStatus));
        FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
    }
    else
    {
        ResourceId status = pFrameworkObjectManagerPrimaryChangedHaPeerPhase1Message->getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::primaryChangedHaPeerPrePhaseCallback: Failed to configure Peer, Completion Status: " + FrameworkToolKit::localize (status));
            FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
        }
    }

    if (NULL != pFrameworkObjectManagerPrimaryChangedHaPeerPhase1Message)
    {
        delete pFrameworkObjectManagerPrimaryChangedHaPeerPhase1Message;
    }

    SecondaryNodeClusterContext *pSecondaryNodeClusterContext = reinterpret_cast<SecondaryNodeClusterContext *> (pContext); 

    if (true == pSecondaryNodeClusterContext->getClusterHaSyncInProgress ())
    {
        pSecondaryNodeClusterContext->setClusterHaSyncInProgress (false);

        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::primaryChangedHaPeerPrePhaseCallback: Cluster Pre-Phase to Ha Peer end.");

        if ( (pSecondaryNodeClusterContext->getNumberOfCallbacksBeforeAdvancingToNextStep ()) > 0)
        {
            --(*pSecondaryNodeClusterContext);
            pSecondaryNodeClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        }
    }
}

void WaveFrameworkObjectManager::primaryChangedHaPeerPostPhaseStep (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context)
{
    FrameworkObjectManagerPrimaryChangedPhase3Message *pFrameworkObjectManagerPrimaryChangedPhase3Message = reinterpret_cast<FrameworkObjectManagerPrimaryChangedPhase3Message *> (pSecondaryNodeClusterPhase3Context->getPWaveMessage ());
    waveAssert (NULL != pFrameworkObjectManagerPrimaryChangedPhase3Message, __FILE__, __LINE__);

    if ( (WAVE_MESSAGE_SUCCESS == FrameworkToolKit::isConnectedToHaPeerLocation ()) && (true == FrameworkToolKit::getIsLiveSyncEnabled ()) )
    {
        FrameworkObjectManagerPrimaryChangedHaPeerPhase3Message *pFrameworkObjectManagerPrimaryChangedHaPeerPhase3Message = new FrameworkObjectManagerPrimaryChangedHaPeerPhase3Message;
        waveAssert (NULL != pFrameworkObjectManagerPrimaryChangedHaPeerPhase3Message, __FILE__, __LINE__);

        pFrameworkObjectManagerPrimaryChangedHaPeerPhase3Message->copyBuffersFrom (*pFrameworkObjectManagerPrimaryChangedPhase3Message);

        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::primaryChangedHaPeerPostPhaseStep: Ha Peer is connected and Live Sync enabled.");

        ResourceId haPeerSendStatus = send (pFrameworkObjectManagerPrimaryChangedHaPeerPhase3Message, reinterpret_cast<WaveMessageResponseHandler> (&WaveFrameworkObjectManager::primaryChangedHaPeerPostPhaseCallback), pSecondaryNodeClusterPhase3Context, s_clusterPhase3TimeoutInMilliseconds, FrameworkToolKit::getHaPeerLocationId ());

        if (WAVE_MESSAGE_SUCCESS != haPeerSendStatus)
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::primaryChangedHaPeerPostPhaseStep: Send to Ha Peer failed.");
            delete pFrameworkObjectManagerPrimaryChangedHaPeerPhase3Message;
            FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
        }
        else
        {
            if (false == pSecondaryNodeClusterPhase3Context->getClusterHaSyncInProgress ())
            {
                trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::primaryChangedHaPeerPostPhaseStep: Cluster Post-phase to Ha Peer start.");
                pSecondaryNodeClusterPhase3Context->setClusterHaSyncInProgress (true);
            }
        }
    }
    else
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::primaryChangedHaPeerPostPhaseStep: Ha Peer is unavailable OR Live sync is disabled.");
    }

    pSecondaryNodeClusterPhase3Context->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::primaryChangedHaPeerPostPhaseCallback (FrameworkStatus frameworkStatus, FrameworkObjectManagerPrimaryChangedHaPeerPhase3Message *pFrameworkObjectManagerPrimaryChangedHaPeerPhase3Message, void *pContext)
{
    //trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::primaryChangedHaPeerPostPhaseCallback: Starting.");
    
    if (FRAMEWORK_SUCCESS != frameworkStatus)
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::primaryChangedHaPeerPostPhaseCallback: Failed to configure Peer, Framework Status: " + FrameworkToolKit::localize (frameworkStatus));
        FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
    }
    else
    {
        ResourceId status = pFrameworkObjectManagerPrimaryChangedHaPeerPhase3Message->getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::primaryChangedHaPeerPostPhaseCallback: Failed to configure Peer, Completion Status: " + FrameworkToolKit::localize (status));
            FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
        }
    }

    if (NULL != pFrameworkObjectManagerPrimaryChangedHaPeerPhase3Message)
    {
        delete pFrameworkObjectManagerPrimaryChangedHaPeerPhase3Message;
    }

    SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context = reinterpret_cast<SecondaryNodeClusterPhase3Context *> (pContext);

    if (true == pSecondaryNodeClusterPhase3Context->getClusterHaSyncInProgress ())
    {
        pSecondaryNodeClusterPhase3Context->setClusterHaSyncInProgress (false);

        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::primaryChangedHaPeerPostPhaseCallback: Cluster Post-phase to Ha Peer end.");

        if ( (pSecondaryNodeClusterPhase3Context->getNumberOfCallbacksBeforeAdvancingToNextStep ()) > 0)
        {
            --(*pSecondaryNodeClusterPhase3Context);
            pSecondaryNodeClusterPhase3Context->executeNextStep (WAVE_MESSAGE_SUCCESS);
        }
    }
}

void WaveFrameworkObjectManager::rollbackStandbyOnActiveRollbackHandler (FrameworkObjectManagerRollbackStandbyOnActiveRollbackMessage *pFrameworkObjectManagerRollbackStandbyOnActiveRollbackMessage)
{
    ResourceId status = WAVE_MESSAGE_SUCCESS;

    // Shutdown All Services First

    status = m_pWaveFinalizeWorker->shutdownWaveServices (WAVE_SHUTDOWN_SECONDARY_CONFIGURE);

    // Bringup PrePhase service
    status = m_pInitializeWorker->startWaveServices (WAVE_BOOT_HASTANDBY, WAVE_BOOT_PHASE_PRE_PHASE);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::rollbackStandbyOnActiveRollbackHandler : Booting Secondary immediately after configuring must NEVER fail.");
        waveAssert (false, __FILE__, __LINE__);
    }

    DatabaseObjectManagerCleanPreparedTransactionsMessage cleanPreparedTransactionsMessage;

    status = sendSynchronously (&cleanPreparedTransactionsMessage);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::rollbackStandbyOnActiveRollbackHandler: Unable to clean prepared transactions. Status : " + FrameworkToolKit::localize (status));
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        status = cleanPreparedTransactionsMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS == status)
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rollbackStandbyOnActiveRollbackHandler: Succeeded in cleaning the previously prepared transactions.");
        }
        else
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::rollbackStandbyOnActiveRollbackHandler: Failed to clean previously prepared transactions. Status : " + FrameworkToolKit::localize (status));
            waveAssert (false, __FILE__, __LINE__);
        }
    }

    const string    prismConfigurationfileName   = (WaveFrameworkObjectManager::getInstance ())->getConfigurationFileName (); 
    vector<string>  output;
    SI32            cmdStatus                    = 0;

    trace (TRACE_LEVEL_WARN, string ("WaveFrameworkObjectManager::rollbackStandbyOnActiveRollbackHandler: deleting file ") + prismConfigurationfileName);

    cmdStatus = FrameworkToolKit::systemCommandOutput ((string ("/bin/rm -rf ") + prismConfigurationfileName).c_str(), output);

    if ( cmdStatus != 0 ) 
    {            
        trace (TRACE_LEVEL_ERROR, string("WaveFrameworkObjectManager::rollbackStandbyOnActiveRollbackHandler: Cmd to delete file ")+ prismConfigurationfileName + string(" failed with error message : ") + output[0]);
    }

    DatabaseObjectManagerEmptyMessage databaseEmptyMessage;
    status  = sendSynchronously (&databaseEmptyMessage);

    if (WAVE_MESSAGE_SUCCESS != status)
    {         
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::rollbackStandbyOnActiveRollbackHandler: Could not send message to empty database. Status : " + FrameworkToolKit::localize (status));
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        status = databaseEmptyMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::rollbackStandbyOnActiveRollbackHandler: Message to empty database failed. Completion Status : " + FrameworkToolKit::localize (status));
            waveAssert (false, __FILE__, __LINE__);
        }
    }

    string backupFileName = string (FrameworkToolKit::getProcessInitialWorkingDirectory () + "/" + FrameworkToolKit::getDatabaseBackupFileName2 ());

    DatabaseObjectManagerRestoreMessage databaseRestoreMessage (backupFileName);
    databaseRestoreMessage.setDataOnlyRestore (true);
    databaseRestoreMessage.setSaveConfiguration (false);

    status  = sendSynchronously (&databaseRestoreMessage);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::rollbackStandbyOnActiveRollbackHandler: Could not send message to restore database. Status : " + FrameworkToolKit::localize (status));
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        status = databaseRestoreMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_ERROR_DB_RESTORE_FAILED == status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::rollbackStandbyOnActiveRollbackHandler: Not Able to Restore DB from Backed Up File. Completion Status : " + FrameworkToolKit::localize (status));
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::rollbackStandbyOnActiveRollbackHandler: Going For Extreme Recovery By going to default/startup configuration");

            status = FrameworkToolKit::changeWaveConfigurationValidity ( false );
            if ( status != WAVE_MESSAGE_SUCCESS  )
            {
                trace (TRACE_LEVEL_FATAL, ("WaveFrameworkObjectManager::rollbackStandbyOnActiveRollbackHandler: Removing CFG file failed in extreme Recoverycase "));
            }
            system ("/sbin/reboot -f");

            sleep (300);
    
            trace (TRACE_LEVEL_FATAL, ("System is not rebooting, Manual recovery is required"));
        
            waveAssert (false, __FILE__, __LINE__);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::rollbackStandbyOnActiveRollbackHandler: SUCCESSFULLY rollback to the last known valid previous DB configuration.");
        }
    }

    // restore CFG file too

    rollbackCfgFile ();

    // Save Configuration File After DB restore.

    FrameworkToolKit::saveWaveConfiguration ();

    // Bring up postphase service
    status = m_pInitializeWorker->startWaveServices (WAVE_BOOT_HASTANDBY, WAVE_BOOT_PHASE_POST_PHASE);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::prepareStandbyAfterClusterPhaseSync: Post phase failed.");
        waveAssert (false, __FILE__, __LINE__);
    }

    WaveFrameworkObjectManager::setSecondaryNodeClusterCreationFlag (false);

    pFrameworkObjectManagerRollbackStandbyOnActiveRollbackMessage->setCompletionStatus (status);
    reply (pFrameworkObjectManagerRollbackStandbyOnActiveRollbackMessage);
}

void WaveFrameworkObjectManager::primaryChangedStopHeartBeatToOldPrimayStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::primaryChangedStopHeartBeatToOldPrimayStep : Starting ...");

    FrameworkObjectManagerPrimaryChangedMessage *pFrameworkObjectManagerPrimaryChangedMessage = reinterpret_cast<FrameworkObjectManagerPrimaryChangedMessage *> (pWaveLinearSequencerContext->getPWaveMessage ());

    waveAssert (NULL != pFrameworkObjectManagerPrimaryChangedMessage, __FILE__, __LINE__);
    waveAssert (NULL != m_pThisLocation, __FILE__, __LINE__);

    vector<string>  managedObjectNamesForSchemaChange;
    vector<string>  fieldNamesStringsForSchemaChange;
    vector<string>  fieldNamesTypesForSchemaChange;
    vector<UI32>    classIds;
    vector<UI32>    parentTableIds;

    pFrameworkObjectManagerPrimaryChangedMessage->getSchemaChangeVectors (managedObjectNamesForSchemaChange,fieldNamesStringsForSchemaChange,fieldNamesTypesForSchemaChange,classIds,parentTableIds); 

    if (!isSchemaReceivedFromPrimaryCompatible (managedObjectNamesForSchemaChange,fieldNamesStringsForSchemaChange,fieldNamesTypesForSchemaChange,classIds,parentTableIds))
    {
        pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_ERROR_SCHEMA_MISMATCH);
        return;
    }

    LocationId oldPrimaryLocationId     = m_pThisLocation->getClusterPrimaryLocationId ();
    string     oldPrimaryNodeIpAddress  = m_pThisLocation->getIpAddressForLocationId(oldPrimaryLocationId);
    UI32       oldPrimaryNodePort       = m_pThisLocation->getClusterPrimaryPort ();


    StopHeartBeatMessage *pStopHeartBeatMessage = new StopHeartBeatMessage();
    pStopHeartBeatMessage->setDstIpAddress(oldPrimaryNodeIpAddress);
    pStopHeartBeatMessage->setDstPortNumber(oldPrimaryNodePort);
   
    WaveMessageStatus status = sendSynchronously(pStopHeartBeatMessage);
    ResourceId        processingStatus = WAVE_MESSAGE_SUCCESS;

    if(WAVE_MESSAGE_SUCCESS != status) 
    {
        processingStatus = status;
    }
    else 
    {
        ResourceId    completionStatus = pStopHeartBeatMessage->getCompletionStatus();
        if(completionStatus != WAVE_MESSAGE_SUCCESS) 
        {
            processingStatus = completionStatus;
        }
    }

    if(WAVE_MESSAGE_SUCCESS !=  processingStatus) 
    {
        trace(TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::primaryChangedStopHeartBeatToOldPrimayStep:Failure sending StopHeartBeatMessage: status: " + FrameworkToolKit::localize(processingStatus));
    }
    delete pStopHeartBeatMessage;

    trace (TRACE_LEVEL_INFO, string("primaryChangedStopHeartBeatToOldPrimayStep : Loc: ") + oldPrimaryLocationId + string(" Port:") + oldPrimaryNodePort);

    //Also Disconnect From Old Primary
    disconnectFromLocation (oldPrimaryLocationId);

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);

}

void WaveFrameworkObjectManager::primaryChangedRemoveOldPrimaryLocationStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager:: primaryChangedRemoveOldPrimaryLocationStep : Starting ...");


    FrameworkObjectManagerPrimaryChangedMessage *pFrameworkObjectManagerPrimaryChangedMessage = reinterpret_cast<FrameworkObjectManagerPrimaryChangedMessage *> (pWaveLinearSequencerContext->getPWaveMessage ());

    waveAssert (NULL != pFrameworkObjectManagerPrimaryChangedMessage, __FILE__, __LINE__);
    waveAssert (NULL != m_pThisLocation, __FILE__, __LINE__);

    if(pFrameworkObjectManagerPrimaryChangedMessage->isPrimaryChangeDueToControlledFailover()) 
    {
        LocationId oldPrimaryLocationId     = m_pThisLocation->getClusterPrimaryLocationId ();    
        removeKnownLocation(oldPrimaryLocationId);
        tracePrintf (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager:: primaryChangedRemoveOldPrimaryLocationStep :Removing the old primary location id %u due to controlled failover", oldPrimaryLocationId);
    }
    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::primaryChangedUpdatePrimaryDetailsStep (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::primaryChangedUpdatePrimaryDetailsStep : Starting ...");

    FrameworkObjectManagerPrimaryChangedMessage *pFrameworkObjectManagerPrimaryChangedMessage = reinterpret_cast<FrameworkObjectManagerPrimaryChangedMessage *> (pSecondaryNodeClusterContext->getPWaveMessage ());

    waveAssert (NULL != pFrameworkObjectManagerPrimaryChangedMessage, __FILE__, __LINE__);
    waveAssert (NULL != m_pThisLocation, __FILE__, __LINE__);

    LocationId newPrimaryLocationId = pSecondaryNodeClusterContext->getClusterPrimaryLocationId ();
    UI32       newPrimaryPort       = pSecondaryNodeClusterContext->getClusterPrimaryPort ();

    m_pThisLocation->setClusterPrimaryLocationId (newPrimaryLocationId);
    m_pThisLocation->setClusterPrimaryPort       (newPrimaryPort);
    m_pThisLocation->setLocationRole             (LOCATION_SECONDARY_REJOIN_PHASE_0);

    trace (TRACE_LEVEL_INFO, string("primaryChangedUpdatePrimaryDetailsStep : Loc: ") + newPrimaryLocationId + string(" Port:") + newPrimaryPort);

    UI64 trackingNumber                 = PersistenceLocalObjectManager::getAnyConfigurationChangeTrackingNumber ();
    UI64 primaryPrincipalTrackingNumber = pFrameworkObjectManagerPrimaryChangedMessage->getAnyConfigurationChangeTrackingNumber ();

    if (trackingNumber == primaryPrincipalTrackingNumber)
    {
        pSecondaryNodeClusterContext->setDBEmptyRequired (false);
    }

    pSecondaryNodeClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::primaryChangedEmptyDatabaseStep  (SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManager::primaryChangedEmptyDatabaseStep : Entering ...");

    if (false == pSecondaryNodeClusterContext->getIsDBEmptyRequired ())
    {
        pSecondaryNodeClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;
    }

    DatabaseObjectManagerEmptyMessage message;
    ResourceId                        status  = sendSynchronously (&message);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::primaryChangedEmptyDatabaseStep : Could not send message to empty database.  Status : " + FrameworkToolKit::localize (status));
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        status = message.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::primaryChangedEmptyDatabaseStep : Message to empty database failed.  Completion Status : " + FrameworkToolKit::localize (status));
            waveAssert (false, __FILE__, __LINE__);
        }
    }

    pSecondaryNodeClusterContext->executeNextStep (status);
}

void WaveFrameworkObjectManager::primaryChangedLoadDatabaseFromPrimaryDatabaseStep ( SecondaryNodeClusterContext *pSecondaryNodeClusterContext)
{
    if (false  == pSecondaryNodeClusterContext->getIsDBEmptyRequired ())
    {
        pSecondaryNodeClusterContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;
    }

    FrameworkObjectManagerPrimaryChangedPhase1Message *pFrameworkObjectManagerPrimaryChangedPhase1Message = reinterpret_cast<FrameworkObjectManagerPrimaryChangedPhase1Message *> (pSecondaryNodeClusterContext->getPWaveMessage ());
    UI32                                              sizeOfTheDatabaseBackupFromPrimary                  = 0;
    char                                             *pBuffer                                             = reinterpret_cast<char *> (pFrameworkObjectManagerPrimaryChangedPhase1Message->findBuffer (pFrameworkObjectManagerPrimaryChangedPhase1Message->getDatabaseBackupBufferTag (), sizeOfTheDatabaseBackupFromPrimary));

    string backupFileName = string (FrameworkToolKit::getProcessInitialWorkingDirectory () + "/" + FrameworkToolKit::getDatabaseBackupFileName3 ());

    if (NULL != pBuffer)
    {
        ofstream                               databaseBackupFile;

        databaseBackupFile.open (backupFileName.c_str (), ios::binary);
        databaseBackupFile.write (pBuffer, sizeOfTheDatabaseBackupFromPrimary);
        databaseBackupFile.close ();
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::primaryChangedLoadDatabaseFromPrimaryDatabaseStep : No Database backup has been received ???");
    }

    // Request the Database service to restore itself from the backup file that we created based on the buffer we obtained from the primary.

    DatabaseObjectManagerRestoreMessage message (backupFileName);
    message.setDataOnlyRestore (true);

    ResourceId status  = sendSynchronously (&message);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::primaryChangedLoadDatabaseFromPrimaryDatabaseStep : Could not send message to restore database.  Status : " + FrameworkToolKit::localize (status));
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        status = message.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::primaryChangedLoadDatabaseFromPrimaryDatabaseStep : Message to restore database failed.  Completion Status : " + FrameworkToolKit::localize (status));
            waveAssert (false, __FILE__, __LINE__);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::primaryChangedLoadDatabaseFromPrimaryDatabaseStep : SUCCESSFULLY Synced up local database with that of Primary.");
        }
    }

    pSecondaryNodeClusterContext->executeNextStep (status);
}

void WaveFrameworkObjectManager::primaryChangedPhase2MessageHandler (FrameworkObjectManagerPrimaryChangedPhase2Message *pFrameworkObjectManagerPrimaryChangedPhase2Message)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::primaryChangedPhase2MessageHandler : Received Primary changed notification ...");

    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::stopClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::updateLocationRoleStepInRejoinPhase2),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinSecondaryNodePhase2BootServicesPostPhaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodePhase2ConfigureThisLocationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::startClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::secondaryNodeClusterFailureStep),
    };

    SecondaryNodeClusterPhase2Context *pSecondaryNodeClusterPhase2Context = new SecondaryNodeClusterPhase2Context (pFrameworkObjectManagerPrimaryChangedPhase2Message, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]),false);

    pSecondaryNodeClusterPhase2Context->holdAll ();
    pSecondaryNodeClusterPhase2Context->start ();
}

void WaveFrameworkObjectManager::primaryChangedPhase3MessageHandler (FrameworkObjectManagerPrimaryChangedPhase3Message *pFrameworkObjectManagerPrimaryChangedPhase3Message)
{
    SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context = NULL;

    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::primaryChangedPhase3MessageHandler: Received Primary changed notification(ACTIVE) ");

    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::stopClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::updateLocationRoleStepInRejoinPhase3),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::broadcastClusterPhase3StartEvent),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::primaryChangedHaPeerPostPhaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::rejoinSecondaryNodePhase3BootServicesAfterPostPhaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::updateLocationRoleStepInRejoinPhase3Complete),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::broadcastClusterPhase3CompleteEvent),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::broadcastPrimaryChangedEventForPlugins),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureSecondaryNodePhase3SendStartHearBeat),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::saveWaveConfigurationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::checkHaPeerSyncPostPhaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerFailedStep),
    };

    pSecondaryNodeClusterPhase3Context = new SecondaryNodeClusterPhase3Context (pFrameworkObjectManagerPrimaryChangedPhase3Message, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pSecondaryNodeClusterPhase3Context->holdAll ();
    pSecondaryNodeClusterPhase3Context->start ();
}

void WaveFrameworkObjectManager::primaryChangedHaPeerPhase3MessageHandler (FrameworkObjectManagerPrimaryChangedHaPeerPhase3Message *pFrameworkObjectManagerPrimaryChangedHaPeerPhase3Message)
{
    SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context = NULL;

    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::primaryChangedPhase3MessageHandler: Received Primary changed notification(STANDBY) ");

    WaveLinearSequencerStep sequencerSteps[] =
    {
        //reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::stopClusterPhaseTimer),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prepareStandbyAfterClusterPhaseSync),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerFailedStep),
    };

    pSecondaryNodeClusterPhase3Context = new SecondaryNodeClusterPhase3Context (pFrameworkObjectManagerPrimaryChangedHaPeerPhase3Message, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pSecondaryNodeClusterPhase3Context->holdAll ();
    pSecondaryNodeClusterPhase3Context->start ();
}

void WaveFrameworkObjectManager::broadcastClusterPhase3StartEvent (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::broadcastClusterPhase3StartEvent: Entering....");

    ClusterPhase3StartEvent *pClusterPhase3StartEvent = new ClusterPhase3StartEvent ();

    ResourceId status = broadcast (pClusterPhase3StartEvent);

    if(status != WAVE_MESSAGE_SUCCESS)
    {  
       trace(TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::broadcastClusterPhase3StartEvent: Failure during broadcast..");
       pSecondaryNodeClusterPhase3Context->executeNextStep (status);
       return;
    }

    pSecondaryNodeClusterPhase3Context->executeNextStep (WAVE_MESSAGE_SUCCESS);
    return;
}

void WaveFrameworkObjectManager::broadcastClusterPhase3CompleteEvent (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::broadcastClusterPhase3CompleteEvent Entering....");

    //Reset the secondary cluster formation flag so that the SCN handling is not postponed in case of secondary node.
    WaveFrameworkObjectManager::setSecondaryNodeClusterCreationFlag (false);

/*
    if (true == getTableIdsChangedForSchemaCompatibilityFlag ())
    {
        setTableIdsChangedForSchemaCompatibilityFlag (false);
    }
*/

    ClusterPhase3CompleteEvent *pClusterPhase3CompleteEvent = new ClusterPhase3CompleteEvent ();

    ResourceId status = broadcast (pClusterPhase3CompleteEvent);

    if(status != WAVE_MESSAGE_SUCCESS)
    {
       trace(TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::broadcastClusterPhase3CompleteEvent: Failure during broadcast..");
       pSecondaryNodeClusterPhase3Context->executeNextStep (status);
       return;
    }

    pSecondaryNodeClusterPhase3Context->executeNextStep (WAVE_MESSAGE_SUCCESS);
    return;
}

void WaveFrameworkObjectManager::broadcastNodesAdditionToClusterCompletedEvent (CreateClusterWithNodesContext *pCreateClusterWithNodesContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::broadcastNodesAdditionToClusterCompletedEvent Entering....");

    vector<LocationId>      successfullyAddedLocationIdVector = pCreateClusterWithNodesContext->getSuccessfullyAddedLocationIdVector ();

    WaveNodesAdditionToClusterCompletedEvent* pWaveNodesAdditionToClusterCompletedEvent = new WaveNodesAdditionToClusterCompletedEvent();
    for(UI32 i = 0; i<successfullyAddedLocationIdVector.size(); ++i)
    {
       string ipAddress     = FrameworkToolKit::getIpAddressForLocationId(successfullyAddedLocationIdVector[i]);
       UI32    port         = FrameworkToolKit::getPortForLocationId(successfullyAddedLocationIdVector[i]);
       pWaveNodesAdditionToClusterCompletedEvent->addNewNodeDetails(successfullyAddedLocationIdVector[i], ipAddress, port);
    }

    ResourceId status = broadcast(pWaveNodesAdditionToClusterCompletedEvent);
    if(status != WAVE_MESSAGE_SUCCESS)
    {
       trace(TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::broadcastNodesAdditionToClusterCompletedEvent: Failure during broadcast..");
       pCreateClusterWithNodesContext->executeNextStep (status);
       return;
    }

    pCreateClusterWithNodesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    trace(TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::broadcastNodesAdditionToClusterCompletedEvent: Exiting..");
    return;

}

void WaveFrameworkObjectManager::broadcastPrimaryChangedEventForPlugins (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::broadcastPrimaryChangedEventForPlugins Entering....");

    PrimaryChangedEvent *pPrimaryChangedEvent = new PrimaryChangedEvent ();
    LocationId           newPrimaryLocationId = FrameworkToolKit::getClusterPrimaryLocationId ();

    pPrimaryChangedEvent->setNewPrimaryLocationId (newPrimaryLocationId);

    broadcast (pPrimaryChangedEvent);

    trace (TRACE_LEVEL_INFO, string("WaveFrameworkObjectManager::broadcastPrimaryChangedEventForPlugins : Broadcasted an event PrimaryChangedEvent with New Primary LocationId is ") + newPrimaryLocationId);
    pSecondaryNodeClusterPhase3Context->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void  WaveFrameworkObjectManager::saveWaveConfigurationStep(WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace(TRACE_LEVEL_DEVEL,"WaveFrameworkObjectManager::saveWaveConfigurationStep: Entering");
    FrameworkToolKit::saveWaveConfiguration(true);
    pWaveLinearSequencerContext->executeNextStep(WAVE_MESSAGE_SUCCESS);

}

void WaveFrameworkObjectManager::sendReplyBackToClusterGlobalService  (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    //WaveMessage *pMessage = pWaveLinearSequencerContext->getPWaveMessage ();

//    pMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);

//    reply (pMessage);

//    pWaveLinearSequencerContext->setPWaveMessage (NULL);

    pWaveLinearSequencerContext->unholdAll ();

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

FrameworkSequenceGenerator &WaveFrameworkObjectManager::getCurrentFrameworkSequenceGenerator ()
{
    FrameworkSequenceGenerator *pFrameworkSequenceGenerator = FrameworkSequenceGeneratorFactory::obtainFrameworkSequenceGenerator (s_frameworkSequenceType);

    return (*pFrameworkSequenceGenerator);
}

ResourceId WaveFrameworkObjectManager::saveConfiguration (const bool &syncToStandby)
{
    return (m_pConfigurationWorker->saveWaveConfiguration (s_frameworkConfigurationFile, syncToStandby));
}

ResourceId WaveFrameworkObjectManager::changeWaveConfigurationValidity( const bool &validity)
{
    return (m_pConfigurationWorker->changeWaveConfigurationValidity( validity ));
}

string WaveFrameworkObjectManager::getConfigurationFileName ()
{
    return (s_frameworkConfigurationFile);
}

string WaveFrameworkObjectManager::getConfigurationBackupFileName ()
{
    return (s_frameworkConfigurationBackupFile);
}

string WaveFrameworkObjectManager::getLockFileForConfigurationFile ()
{
    return (s_lockFileForConfigurationFile);
}

SI32 WaveFrameworkObjectManager::getLocationPort ()
{
    return (s_locationPort);
}

WaveFrameworkConfigurationWorker *WaveFrameworkObjectManager::getPConfigurationWorker ()
{
    return (m_pConfigurationWorker);
}

WaveFinalizeWorker *WaveFrameworkObjectManager::getPFinalizeWorker ()
{
    return (m_pWaveFinalizeWorker);
}

WaveFrameworkObjectManagerInitializeWorker *WaveFrameworkObjectManager::getPInitializeWorker ()
{
    return (m_pInitializeWorker);
}

bool WaveFrameworkObjectManager::isServiceToBeExcludedInClusterCommunications (const WaveServiceId &waveServiceId)
{
    if (((WaveFrameworkObjectManager::getWaveServiceId               ()) == waveServiceId)           ||
        ((CentralClusterConfigObjectManager::getWaveServiceId         ()) == waveServiceId)           ||
        ((ClusterTestObjectManager::getWaveServiceId                  ()) == waveServiceId)           ||
        ((RegressionTestObjectManager::getWaveServiceId               ()) == waveServiceId)           ||
        (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))) ||
        (true == (isServiceDynamicallyExcludedFromClusterCommunications (waveServiceId))))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

void WaveFrameworkObjectManager::configureAsLocation (SI32 port)
{
    s_locationRole = LOCATION_STAND_ALONE;
    s_locationPort = port;
}

void WaveFrameworkObjectManager::configureAsSubLocation (LocationId parentLocationId, string &parentIpAddress, SI32 parentPort, LocationId locationId, string &ipAddress, SI32 port)
{
    s_locationRole             = LOCATION_SUB_LOCATION;
    s_locationParentLocationId = parentLocationId;
    s_locationParentIpAddress  = parentIpAddress;
    s_locationParentPort       = parentPort;
    s_locationLocationId       = locationId;
    s_locationIpAddress        = ipAddress;
    s_locationPort             = port;
}

void WaveFrameworkObjectManager::resetLocationToPrimary ()
{
    waveAssert (NULL != m_pThisLocation, __FILE__, __LINE__);

    m_pThisLocation->resetLocationToPrimary ();
}

void WaveFrameworkObjectManager::acquireBootSynchronizationMutex ()
{
    s_bootSynchronizationMutex.lock ();
}

void WaveFrameworkObjectManager::releaseBootSynchronizationMutex ()
{
    s_bootSynchronizationMutex.unlock ();
}

void WaveFrameworkObjectManager::dynamicallyExcludeServiceFromClusterCommunications (const WaveServiceId &waveServiceId)
{
    m_servicesToBeExcludedForClusterCommunicationsLock.lock ();

    map<WaveServiceId, WaveServiceId>::iterator element    = m_servicesToBeExcludedForClusterCommunications.find (waveServiceId);
    map<WaveServiceId, WaveServiceId>::iterator endElement = m_servicesToBeExcludedForClusterCommunications.end  ();

    if (endElement == element)
    {
        m_servicesToBeExcludedForClusterCommunications[waveServiceId] = waveServiceId;
    }

    m_servicesToBeExcludedForClusterCommunicationsLock.unlock ();
}

bool WaveFrameworkObjectManager::isServiceDynamicallyExcludedFromClusterCommunications (const WaveServiceId &waveServiceId)
{
    bool isFound = false;

    m_servicesToBeExcludedForClusterCommunicationsLock.lock ();

    map<WaveServiceId, WaveServiceId>::iterator element    = m_servicesToBeExcludedForClusterCommunications.find (waveServiceId);
    map<WaveServiceId, WaveServiceId>::iterator endElement = m_servicesToBeExcludedForClusterCommunications.end  ();

    if (endElement != element)
    {
        isFound = true;
    }

    m_servicesToBeExcludedForClusterCommunicationsLock.unlock ();

    return (isFound);
}

void WaveFrameworkObjectManager::excludeServiceForClusterValidationPhase (const WaveServiceId &waveServiceId)
{
    (WaveFrameworkObjectManager::getInstance ())->dynamicallyExcludeServiceFromClusterCommunications (waveServiceId);
}

void WaveFrameworkObjectManager::setIpAddressForThisLocation (const string &ipAddressForThisLocation)
{
    m_ipAddressForThisLocationMutex.lock ();

    m_ipAddressForThisLocation = ipAddressForThisLocation;

    m_ipAddressForThisLocationMutex.unlock ();
}

string WaveFrameworkObjectManager::getIpAddressForThisLocation ()
{
    string ipAddressForThisLocation;

    m_ipAddressForThisLocationMutex.lock ();

    ipAddressForThisLocation = m_ipAddressForThisLocation;

    m_ipAddressForThisLocationMutex.unlock ();

    return (ipAddressForThisLocation);
}

void WaveFrameworkObjectManager::setEthernetInterfaceForThisLocation (const string &ethernetInterfaceForThisLocation)
{
    m_ethernetInterfaceForThisLocation = ethernetInterfaceForThisLocation;
}

string WaveFrameworkObjectManager::getEthernetInterfaceForThisLocation ()
{
    return (m_ethernetInterfaceForThisLocation);
}

void WaveFrameworkObjectManager::updateIpAddressForThisLocation (const string &ipAddressForThisLocation)
{
    setIpAddressForThisLocation (ipAddressForThisLocation);

    (WaveFrameworkObjectManager::getInstance ())->m_pThisLocation->resetIpAddress (ipAddressForThisLocation);
}

void WaveFrameworkObjectManager::setIsDBRestoreIncomplete (bool dbRestoreIncomplete)
{
    s_dbRestoreMutex.lock ();
    m_isDBRestoreIncomplete = dbRestoreIncomplete;
    s_dbRestoreMutex.unlock ();
}

bool WaveFrameworkObjectManager::getIsDBRestoreIncomplete ()
{
    bool isRestoreIncomplete;

    s_dbRestoreMutex.lock ();
    isRestoreIncomplete = m_isDBRestoreIncomplete;
    s_dbRestoreMutex.unlock ();

    return (isRestoreIncomplete);
}

void WaveFrameworkObjectManager::setDbConversionStatus (ResourceId dbConversionStatus)
{
    s_dbConversionStatusMutex.lock ();
    m_dbConversionStatus = dbConversionStatus;
    s_dbConversionStatusMutex.unlock ();
}

ResourceId WaveFrameworkObjectManager::getDbConversionStatus () const
{
    ResourceId dbConversionStatus;

    s_dbConversionStatusMutex.lock ();
    dbConversionStatus = m_dbConversionStatus;
    s_dbConversionStatusMutex.unlock ();

    return (dbConversionStatus);
}

/*
void WaveFrameworkObjectManager::setTableIdsChangedForSchemaCompatibilityFlag (bool tableIdsChanged)
{
    m_tableIdsChangedForSchemaCompatibility = tableIdsChanged; 
    tracePrintf (TRACE_LEVEL_INFO, true, false, "WaveFrameworkObjectManager::setTableIdsChangedForSchemaCompatibilityFlag: flag set to %u", tableIdsChanged);
}

bool WaveFrameworkObjectManager::getTableIdsChangedForSchemaCompatibilityFlag () 
{
    return (m_tableIdsChangedForSchemaCompatibility);
}
*/
void WaveFrameworkObjectManager::setAuxilliaryTableDetailsForSchemaConversion (vector<string> oldAuxilliaryTables, vector<string> newAuxilliaryTables, vector<string> parentTables, vector<string> relatedToTables)
{
    m_oldAuxilliaryTableNamesBeforeConversion = oldAuxilliaryTables;
    m_newAuxilliaryTableNamesAfterConversion  = newAuxilliaryTables;
    m_parentTableNamesForAuxilliaryTables     = parentTables;
    m_relatedToTableNamesForAuxilliaryTables  = relatedToTables;   
}

void WaveFrameworkObjectManager::getAuxilliaryTableDetailsForSchemaConversion (vector<string>& oldAuxilliaryTables, vector<string>& newAuxilliaryTables, vector<string>& parentTables, vector<string>& relatedToTables)
{
    oldAuxilliaryTables = m_oldAuxilliaryTableNamesBeforeConversion;
    newAuxilliaryTables = m_newAuxilliaryTableNamesAfterConversion;
    parentTables        = m_parentTableNamesForAuxilliaryTables;
    relatedToTables     = m_relatedToTableNamesForAuxilliaryTables;
}

void WaveFrameworkObjectManager::setIsStartupValid (const bool &isValid)
{
    s_startupValidMutex.lock ();
    m_isStartupValid = isValid;
    s_startupValidMutex.unlock ();
}

bool WaveFrameworkObjectManager::getIsStartupValid ()
{
    bool isStartupValid;

    s_startupValidMutex.lock ();
    isStartupValid = m_isStartupValid;
    s_startupValidMutex.unlock ();

    return (isStartupValid);
}

string WaveFrameworkObjectManager::getStartupFileName () const
{
    string startupFileName;

    s_startupFileMutex.lock ();
    startupFileName = FrameworkToolKit::getProcessInitialWorkingDirectory () + "/" + s_startupFileName;
    s_startupFileMutex.unlock ();

    return (startupFileName);
}

void WaveFrameworkObjectManager::setStartupFileName (const string &fileName)
{
    if (getStartupFileName () != fileName)
    {
        string createFileLink = string("ln -sf " + fileName + " " + FrameworkToolKit::getProcessInitialWorkingDirectory () + "/" + s_startupFileName);
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager:: setStartupFileName: setting startupFile to " + fileName);
        s_startupFileMutex.lock ();
        system (createFileLink.c_str ());
        s_startupFileMutex.unlock ();
    }
}

ResourceId WaveFrameworkObjectManager::getStartupFileType () const
{
    ResourceId startupFileType;

    s_startupFileTypeMutex.lock ();
    startupFileType = m_startupFileType;
    s_startupFileTypeMutex.unlock ();

    return (startupFileType);
}

void WaveFrameworkObjectManager::setStartupFileType (const ResourceId &fileType)
{
    s_startupFileTypeMutex.lock ();
    m_startupFileType = fileType;
    s_startupFileTypeMutex.unlock ();
}

bool WaveFrameworkObjectManager::getSecondaryNodeClusterCreationFlag ()
{
    bool secondaryNodeClusterCreationFlag;

    m_secondaryNodeClusterCreationFlagMutex.lock ();
    secondaryNodeClusterCreationFlag = m_secondaryNodeClusterCreationFlag;
    m_secondaryNodeClusterCreationFlagMutex.unlock ();

    return (secondaryNodeClusterCreationFlag);
}

void WaveFrameworkObjectManager::setSecondaryNodeClusterCreationFlag (bool secondaryNodeClusterCreationFlag)
{
    m_secondaryNodeClusterCreationFlagMutex.lock ();
    m_secondaryNodeClusterCreationFlag = secondaryNodeClusterCreationFlag;
    m_secondaryNodeClusterCreationFlagMutex.unlock ();
}

bool WaveFrameworkObjectManager::getPrimaryNodeClusterOperationFlag ()
{
    bool primaryNodeClusterOperationFlag;

    m_primaryNodeClusterOperationFlagMutex.lock ();
    primaryNodeClusterOperationFlag = m_primaryNodeClusterOperationFlag;
    m_primaryNodeClusterOperationFlagMutex.unlock ();

    return (primaryNodeClusterOperationFlag);
}

void WaveFrameworkObjectManager::setPrimaryNodeClusterOperationFlag (bool primaryNodeClusterOperationFlag)
{
    m_primaryNodeClusterOperationFlagMutex.lock ();
    m_primaryNodeClusterOperationFlag = primaryNodeClusterOperationFlag;
    m_primaryNodeClusterOperationFlagMutex.unlock ();
}

// Processing Secondary Node failure.
void WaveFrameworkObjectManager::secondaryNodeFailureNotificationMessageHandler(FrameworkObjectManagerSecondaryNodeFailureNotificationMessage *pFrameworkObjectManagerSecondaryNodeFailureNotificationMessage)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager:: secondaryNodeFailureNotificationMessageHandler: Entering ...");

    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::processSecondeyNodeFailureMessage),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerFailedStep),
    };

    WaveLinearSequencerContext *pWaveLinearSequencerContext = new WaveLinearSequencerContext (pFrameworkObjectManagerSecondaryNodeFailureNotificationMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pWaveLinearSequencerContext->holdAll ();
    pWaveLinearSequencerContext->start ();
    
}
void WaveFrameworkObjectManager::processSecondeyNodeFailureMessage(WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    FrameworkObjectManagerSecondaryNodeFailureNotificationMessage *pFrameworkObjectManagerSecondaryNodeFailureNotificationMessage = dynamic_cast<FrameworkObjectManagerSecondaryNodeFailureNotificationMessage *>(pWaveLinearSequencerContext->getPWaveMessage());

    vector<string>     failedIpAddresses  = pFrameworkObjectManagerSecondaryNodeFailureNotificationMessage->getFailedIpAddresses();
    vector<LocationId> failedLocationIds  = pFrameworkObjectManagerSecondaryNodeFailureNotificationMessage->getFailedLocationIds ();

    LocationId  thisLocationId = FrameworkToolKit::getThisLocationId ();


    WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext = NULL;

   // Activate the Primary Uncontrolled Failover Agent.

    if (true == pFrameworkObjectManagerSecondaryNodeFailureNotificationMessage->getIsControlledFailoverInSpecialCase ())
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::secondaryNodeFailureNotificationMessageHandler::Initiating Primary Controlled Failover.");

        pWaveFrameworkFailoverWorkerContext = new WaveFrameworkFailoverWorkerContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveFrameworkObjectManager::lostHeartBeatSecondaryControlledFailoverCallback), pWaveLinearSequencerContext);

        waveAssert (NULL != pWaveFrameworkFailoverWorkerContext, __FILE__, __LINE__);
        waveAssert (NULL != m_pWaveFrameworkFailoverWorker, __FILE__, __LINE__);

        pWaveFrameworkFailoverWorkerContext->setThisLocationRole (LOCATION_PRIMARY);

        pWaveFrameworkFailoverWorkerContext->setFailoverReason (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_CONTROLLED);
    }
    else
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::secondaryNodeFailureNotificationMessageHandler::Initiating Primary Un-Controlled Failover.");

        pWaveFrameworkFailoverWorkerContext = new WaveFrameworkFailoverWorkerContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveFrameworkObjectManager::lostHeartBeatSecondaryUncontrolledFailoverCallback), pWaveLinearSequencerContext);

        waveAssert (NULL != pWaveFrameworkFailoverWorkerContext, __FILE__, __LINE__);
        waveAssert (NULL != m_pWaveFrameworkFailoverWorker, __FILE__, __LINE__);

        pWaveFrameworkFailoverWorkerContext->setThisLocationRole (LOCATION_PRIMARY);

        pWaveFrameworkFailoverWorkerContext->setFailoverReason (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED);
    }

    UI32 numFailedLocationIds = failedLocationIds.size ();

    for (UI32 i = 0; i < numFailedLocationIds; ++i) 
    {
        pWaveFrameworkFailoverWorkerContext->addFailedLocationId (failedLocationIds[i]);
        disconnectFromLocation (failedLocationIds[i]);
        waveAssert (failedLocationIds[i] != thisLocationId, __FILE__, __LINE__);
    }
    
    m_pWaveFrameworkFailoverWorker->executeFailover (pWaveFrameworkFailoverWorkerContext);

}


//New Principal Selection handling

void WaveFrameworkObjectManager::newPrincipalSelectedAfterFaioverMessageHandler(FrameworkObjectManagerNewPrincipalEstablishedMessage *pFrameworkObjectManagerNewPrincipalEstablishedMessage)
{
    //Steps
    //1. validate
    //2. reboot global services
    //3. Send messages to all secondaries informing them that this node 
    //   is the new principal
    //4. Update local WaveNode object to inform it of the new primary Selection
    //5. Update the WaveNode of the old Principal to mark it as secondary_disconnected
    // 

    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager:: newPrincipalSelectedAfterFaioverMessageHandler: Entering ...");

    WaveLinearSequencerStep sequencerSteps[] =
    {
    reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::validateNewPrincipalSelection),
    reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::processNewPrincipalEstablishedMessage),
#if 0
    reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::updateWaveNodeManagedObjctsStep),
    reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::startHeartBeatToAllSecondariesStep),
#endif
    reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::primaryNodeClusterSuccessStep),
    reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::primaryNodeClusterFailureStep),
    };
    
    setPrimaryNodeClusterOperationFlag (true);

    WaveLinearSequencerContext *pWaveLinearSequencerContext = new WaveLinearSequencerContext (pFrameworkObjectManagerNewPrincipalEstablishedMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pWaveLinearSequencerContext->holdAll ();
    pWaveLinearSequencerContext->start ();
    
}

void WaveFrameworkObjectManager::validateNewPrincipalSelection (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
  trace(TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::validateNewPrincipalSelection..Entering");

  LocationRole locationRole = m_pThisLocation->getLocationRole ();
 
  // When a node goes to UNCONFIRMED role following a rollback from rejoin cluster phases 0/1 and
  // If there is a message pending in the queue to have this node become principal before 
  // the services were shutdown we should return an error upon picking the message since it is UNCONFIRMED role.
  // Framework should act upon new principal message only if the node's current role is SECONDARY

  if ((true == WaveFrameworkObjectManager::getSecondaryNodeClusterCreationFlag ()) || (LOCATION_PRIMARY_UNCONFIRMED == locationRole) || (LOCATION_SECONDARY_UNCONFIRMED == locationRole))
  {
      pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_ERROR_CLUSTER_OPERATION_IN_PROGRESS);
      return;
  }

  waveAssert(m_pThisLocation->getLocationRole () == LOCATION_SECONDARY, __FILE__, __LINE__);

  FrameworkObjectManagerNewPrincipalEstablishedMessage *pFrameworkObjectManagerNewPrincipalEstablishedMessage = dynamic_cast<FrameworkObjectManagerNewPrincipalEstablishedMessage *>(pWaveLinearSequencerContext->getPWaveMessage());

  waveAssert(NULL != pFrameworkObjectManagerNewPrincipalEstablishedMessage, __FILE__, __LINE__);

  pWaveLinearSequencerContext->executeNextStep(WAVE_MESSAGE_SUCCESS);


}

void WaveFrameworkObjectManager::processNewPrincipalEstablishedMessage (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{

   FrameworkObjectManagerNewPrincipalEstablishedMessage *pFrameworkObjectManagerNewPrincipalEstablishedMessage = dynamic_cast<FrameworkObjectManagerNewPrincipalEstablishedMessage *>(pWaveLinearSequencerContext->getPWaveMessage());

   waveAssert (NULL != pFrameworkObjectManagerNewPrincipalEstablishedMessage, __FILE__, __LINE__);

   string     failedIpAddress  = pFrameworkObjectManagerNewPrincipalEstablishedMessage->getFailedPrincipalIpAddress();
   //UI32       failedPort       = pFrameworkObjectManagerNewPrincipalEstablishedMessage->getFailedPrincipalPort();
   LocationId failedLocationId = pFrameworkObjectManagerNewPrincipalEstablishedMessage->getFailedPrincipalLocationId ();

   LocationId  thisLocationId = FrameworkToolKit::getThisLocationId ();

   waveAssert (failedLocationId != thisLocationId, __FILE__, __LINE__);

   // Activate the Secondary Uncontrolled Failover Agent.
  

    WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext = new WaveFrameworkFailoverWorkerContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveFrameworkObjectManager::lostHeartBeatSecondaryUncontrolledFailoverCallback), pWaveLinearSequencerContext);

    waveAssert (NULL != pWaveFrameworkFailoverWorkerContext, __FILE__, __LINE__);
    waveAssert (NULL != m_pWaveFrameworkFailoverWorker, __FILE__, __LINE__);

    pWaveFrameworkFailoverWorkerContext->setThisLocationRole (LOCATION_SECONDARY);
    if(pFrameworkObjectManagerNewPrincipalEstablishedMessage->getTriggerControlledFailover()) 
    {
      trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::processNewPrincipalEstablishedMessage::Initiating Secondary Controlled Failover.");
      pWaveFrameworkFailoverWorkerContext->setFailoverReason (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_CONTROLLED);
      pWaveFrameworkFailoverWorkerContext->setSecondaryControlledFailoverDueToPrimaryRemoval();

    }
    else 
    {
      trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::processNewPrincipalEstablishedMessage::Initiating Secondary Un-Controlled Failover.");
      pWaveFrameworkFailoverWorkerContext->setFailoverReason (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED);
    }
    pWaveFrameworkFailoverWorkerContext->addFailedLocationId (failedLocationId);
    m_pWaveFrameworkFailoverWorker->executeFailover (pWaveFrameworkFailoverWorkerContext);
 
}

void WaveFrameworkObjectManager::disconnectFromAllNodesHandler (FrameworkObjectManagerDisconnectFromAllNodesMessage *pFrameworkObjectManagerDisconnectFromAllNodesMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::disconnectAllKnownLocationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerFailedStep),
    };

    WaveLinearSequencerContext *pWaveLinearSequencerContext = new WaveLinearSequencerContext (pFrameworkObjectManagerDisconnectFromAllNodesMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pWaveLinearSequencerContext->holdAll ();
    pWaveLinearSequencerContext->start ();
}

void WaveFrameworkObjectManager::establishPrincipalAfterClusterRebootHandler (FrameworkObjectManagerEstablishPrincipalAfterClusterRebootMessage* pFrameworkObjectManagerEstablishPrincipalAfterClusterRebootMessage)
{
    WaveLinearSequencerStep sequencerSteps [] = 
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::establishPrincipalAfterClusterRebootStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerFailedStep)
    };
    WaveLinearSequencerContext *pWaveLinearSequencerContext = new WaveLinearSequencerContext (pFrameworkObjectManagerEstablishPrincipalAfterClusterRebootMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pWaveLinearSequencerContext->holdAll ();
    pWaveLinearSequencerContext->start ();


}

void WaveFrameworkObjectManager::establishPrincipalAfterClusterRebootStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManager::establishPrincipalAfterClusterRebootStep");

    resetLocationToPrimary ();
    
    FrameworkToolKit::saveWaveConfiguration (true);

    pWaveLinearSequencerContext->executeNextStep(WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::disconnectAllKnownLocationStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    vector<LocationId> connectedLocationsVector;
    LocationId         nodeLocationId;
    UI32               nodeCount;
    UI32               totalNodes               = 0;

    FrameworkToolKit::getKnownLocations (connectedLocationsVector);
    totalNodes = connectedLocationsVector.size ();

    for (nodeCount = 0; nodeCount < totalNodes; nodeCount++)
    {
        nodeLocationId = connectedLocationsVector[nodeCount];
        disconnectFromLocation (nodeLocationId);
        //removeKnownLocation    (nodeLocationId);

        trace (TRACE_LEVEL_INFO, string ("WaveFrameworkObjectManager::disconnectAllKnownLocationStep ")+nodeLocationId);
    }

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::invalidateClientStreamingSocketForRemoteLocation (LocationId locationId)
{
    m_pThisLocation->invalidateClientStreamingSocketForRemoteLocation(locationId);

}
void WaveFrameworkObjectManager::resetNodeForClusterMergeHandler (FrameworkObjectManagerResetNodeToUnconfirmRole *pFrameworkObjectManagerResetNodeToUnconfirmRole)
{
    if (LOCATION_STAND_ALONE == m_pThisLocation->getLocationRole ())
    {
        pFrameworkObjectManagerResetNodeToUnconfirmRole->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
        reply (pFrameworkObjectManagerResetNodeToUnconfirmRole);

        return;
    }

    if (true == WaveFrameworkObjectManager::getSecondaryNodeClusterCreationFlag ())
    {
        pFrameworkObjectManagerResetNodeToUnconfirmRole->setCompletionStatus (WAVE_MESSAGE_ERROR_CLUSTER_OPERATION_IN_PROGRESS);
        reply (pFrameworkObjectManagerResetNodeToUnconfirmRole);
        
        return;
    }    

    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::stopHeartBeatToNode),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::disconnectFromAllNodes),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::configureNodeForResetAndStartServices),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::triggerUncontrolledFailoverForRemainingNodes),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerFailedStep),
    };

    WaveLinearSequencerContext *pWaveLinearSequencerContext = new WaveLinearSequencerContext (pFrameworkObjectManagerResetNodeToUnconfirmRole, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pWaveLinearSequencerContext->holdAll ();
    pWaveLinearSequencerContext->start ();

}

void WaveFrameworkObjectManager::triggerUncontrolledFailoverForRemainingNodes (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    vector<LocationId> failedLocationIds;
    LocationId         thisLocationId = FrameworkToolKit::getThisLocationId ();

    FrameworkToolKit::getKnownLocations (failedLocationIds);

    WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext = NULL;


    pWaveFrameworkFailoverWorkerContext = new WaveFrameworkFailoverWorkerContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveFrameworkObjectManager::triggerUncontrolledFailoverForRemainingNodesCallback), pWaveLinearSequencerContext);

    waveAssert (NULL != pWaveFrameworkFailoverWorkerContext, __FILE__, __LINE__);
    waveAssert (NULL != m_pWaveFrameworkFailoverWorker, __FILE__, __LINE__);

    pWaveFrameworkFailoverWorkerContext->setThisLocationRole (LOCATION_PRIMARY);

    pWaveFrameworkFailoverWorkerContext->setFailoverReason (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED);

    UI32 numFailedLocationIds = failedLocationIds.size ();

    for (UI32 i = 0; i < numFailedLocationIds; ++i) 
    {    
      pWaveFrameworkFailoverWorkerContext->addFailedLocationId (failedLocationIds[i]);
      waveAssert (failedLocationIds[i] != thisLocationId, __FILE__, __LINE__);
    }    
    
    m_pWaveFrameworkFailoverWorker->executeFailover (pWaveFrameworkFailoverWorkerContext);
}

void WaveFrameworkObjectManager::triggerUncontrolledFailoverForRemainingNodesCallback (WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext)
{
    waveAssert (NULL != pWaveFrameworkFailoverWorkerContext, __FILE__, __LINE__);

    WaveLinearSequencerContext *pWaveLinearSequencerContext = reinterpret_cast<WaveLinearSequencerContext *> (pWaveFrameworkFailoverWorkerContext->getPCallerContext ());
    ResourceId                   status                       = pWaveFrameworkFailoverWorkerContext->getCompletionStatus ();

    delete pWaveFrameworkFailoverWorkerContext;

    waveAssert (NULL != pWaveLinearSequencerContext, __FILE__, __LINE__);

    pWaveLinearSequencerContext->executeNextStep (status);
}


void WaveFrameworkObjectManager::configureNodeForResetAndStartServices (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    ResourceId status = WAVE_MESSAGE_SUCCESS;

    trace (TRACE_LEVEL_INFO, string ("WaveFrameworkObjectManager::configureNodeForResetAndStartServices Location Role is ") + FrameworkToolKit::localize (m_pThisLocation->getLocationRole ()));

    if (LOCATION_PRIMARY == m_pThisLocation->getLocationRole ())
    {
        m_pThisLocation->setLocationRole (LOCATION_PRIMARY_UNCONFIRMED);
    }
    else if (LOCATION_SECONDARY == m_pThisLocation->getLocationRole ())
    {
        status = m_pInitializeWorker->startWaveServices (WAVE_BOOT_PERSISTENT, WAVE_BOOT_RESET_NODE_TO_UNCONFIRM_ROLE);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::configureNodeForResetAndStartServices : Start of Service should Never Fail");
            waveAssert (false, __FILE__, __LINE__);
        }
    }
    else if (LOCATION_STAND_ALONE == m_pThisLocation->getLocationRole ())
    {
        waveAssert (false, __FILE__, __LINE__);
    }
    
    pWaveLinearSequencerContext->executeNextStep(WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::disconnectFromAllNodes (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::disconnectFromAllNodes Entering....");

    disconnectFromAllConnectedNodes ();

    pWaveLinearSequencerContext->executeNextStep(WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::disconnectFromAllConnectedNodes ()
{
    vector<LocationId> connectedLocationsVector;

    FrameworkToolKit::getConnectedLocations (connectedLocationsVector);

    UI32         numberOfConnectedLocations  = connectedLocationsVector.size ();
    LocationId   locationId                  = 0;

    for (UI32 i = 0; i < numberOfConnectedLocations; i++)
    {
        locationId = connectedLocationsVector [i];
        disconnectFromLocation (locationId);
    }
}

void WaveFrameworkObjectManager::stopHeartBeatToNode (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    LocationRole locationRole = m_pThisLocation->getLocationRole ();
    LocationId   locationId   = 0;
    string       ipAddress    = "";
    SI32         port         = 0;
    ResourceId  status        = WAVE_MESSAGE_SUCCESS;
    vector<LocationId> currentlyKnownLocations;
    UI32               numberOfCurrentlyKnownLocations = 0;

    if (LOCATION_PRIMARY == locationRole)
    {
        // stop heartbeat to all the connected nodes
        vector<LocationId> connectedLocationsVector;
        FrameworkToolKit::getKnownLocations (currentlyKnownLocations);
        numberOfCurrentlyKnownLocations = currentlyKnownLocations.size ();

        for (UI32 i = 0; i < numberOfCurrentlyKnownLocations; i++)
        {
            locationId = currentlyKnownLocations [i];
            ipAddress  = FrameworkToolKit::getIpAddressForLocationId (locationId);
            port       = FrameworkToolKit::getPortForLocationId      (locationId);

            StopHeartBeatMessage stopHeartBeatMessage;
            IpV4Address          ip (ipAddress);

            stopHeartBeatMessage.setDstIpAddress       (ip);
            stopHeartBeatMessage.setDstPortNumber      (port);

            status = sendSynchronously (&stopHeartBeatMessage);

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::stopHeartBeatToNode : " + ipAddress + ":" + port + ", Error = " + FrameworkToolKit::localize (status));
            }

            status = stopHeartBeatMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::stopHeartBeatToNode : Could not stop Heart Beat to " + ipAddress + ":" + port + ", Error = " + FrameworkToolKit::localize (status));         
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::stopHeartBeatToNode :  For Node Reset : stopped Heart Beat to " + ipAddress + ":" + port);
            }
        }
    }
    else if (LOCATION_SECONDARY == locationRole)
    {
        // stop hearbeat to primary
        locationId = m_pThisLocation->getClusterPrimaryLocationId ();
        ipAddress  = FrameworkToolKit::getIpAddressForLocationId (locationId);
        port       = FrameworkToolKit::getPortForLocationId      (locationId);

        StopHeartBeatMessage stopHeartBeatMessage;
        IpV4Address          ip (ipAddress);

        stopHeartBeatMessage.setDstIpAddress       (ip);
        stopHeartBeatMessage.setDstPortNumber      (port);

        status = sendSynchronously (&stopHeartBeatMessage);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManager::stopHeartBeatToNode : " + ipAddress + ":" + port + ", Error = " + FrameworkToolKit::localize (status));
        }

        status = stopHeartBeatMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::stopHeartBeatToNode : Could not stop Heart Beat to Primary " + ipAddress + ":" + port + ", Error = " + FrameworkToolKit::localize (status));
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::stopHeartBeatToNode :  For Node Reset : stopped Heart Beat to Primary " + ipAddress + ":" + port);
        }
    }

    pWaveLinearSequencerContext->executeNextStep(WAVE_MESSAGE_SUCCESS);
}

bool WaveFrameworkObjectManager::getIsPostBootNeededDuringRejoin ()
{
    return (m_isPostBootNeededDuringRejoin);
}

void WaveFrameworkObjectManager::setIsPostBootNeededDuringRejoin (bool isPostBootNeededDuringRejoin)
{
    m_isPostBootNeededDuringRejoin = isPostBootNeededDuringRejoin;
}

bool WaveFrameworkObjectManager::getNeedNotifyClusterReadyState ()
{
    return (m_needNotifyClusterReadyState);
}

void WaveFrameworkObjectManager::setNeedNotifyClusterReadyState (bool needNotifyClusterReadyState)
{
    m_needNotifyClusterReadyState = needNotifyClusterReadyState;
}

void WaveFrameworkObjectManager::removeFailedLocationsFromKnownLocationsHandler (FrameworkObjectManagerRemoveKnownLocationsMessage *pFrameworkObjectManagerRemoveKnownLocationsMessage)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::removeFailedLocationsFromKnownLocationsHandler : entering");

    vector<LocationId> failedLocations      = pFrameworkObjectManagerRemoveKnownLocationsMessage->getFailedLocationIds ();
    UI32               numOfFailedLocations = failedLocations.size ();

    waveAssert (0 != numOfFailedLocations, __FILE__, __LINE__);

    trace (TRACE_LEVEL_INFO, string("WaveFrameworkObjectManager::removeFailedLocationsFromKnownLocationsHandler : numOfFailedLocations = ") + numOfFailedLocations);

    for (UI32 i = 0; i < numOfFailedLocations; i++)
    {
        LocationId failedLocation = failedLocations[i];
        trace (TRACE_LEVEL_INFO, string("WaveFrameworkObjectManager::removeFailedLocationsFromKnownLocationsHandler : failedLocation = ") + failedLocation);
        removeKnownLocation (failedLocation);
    } 

    pFrameworkObjectManagerRemoveKnownLocationsMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);

    FrameworkToolKit::saveWaveConfiguration(true);

    reply (pFrameworkObjectManagerRemoveKnownLocationsMessage);
}

void WaveFrameworkObjectManager::removePreviousDatabaseBackupFile (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    string commandToRemoveDatabaseBackupFile = string ("rm -rf " + FrameworkToolKit::getProcessInitialWorkingDirectory () + "/" + FrameworkToolKit::getDatabaseBackupFileName2 ());

    system (commandToRemoveDatabaseBackupFile.c_str ());

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::setGetInstancesFunction (GetInstancesFunction getInstancesFunction)
{
    m_getInstancesFunction  = getInstancesFunction;
}


void WaveFrameworkObjectManager::getInstances (vector<SI32> &connectedInstanceVector)
{
    trace (TRACE_LEVEL_DEBUG, ("WaveFrameworkObjectManager:: getInstances"));
    
    waveAssert (NULL != m_getInstancesFunction, __FILE__, __LINE__);

    if (NULL != m_getInstancesFunction)
    {
         (*m_getInstancesFunction) (connectedInstanceVector);
    }
}

void WaveFrameworkObjectManager::setGetInstancesAndSubInstancesFunction (GetInstancesAndSubInstancesFunction getInstancesAndSubInstancesFunction)
{
    m_getInstancesAndSubInstancesFunction = getInstancesAndSubInstancesFunction;
}

void WaveFrameworkObjectManager::getInstancesAndSubInstances (vector<SI32> &connectedInstanceVector, vector<SI32> &connectedSubInstanceVector)
{
    trace (TRACE_LEVEL_DEBUG, ("WaveFrameworkObjectManager:: getInstancesAndSubInstances"));

    waveAssert (NULL != m_getInstancesAndSubInstancesFunction, __FILE__, __LINE__);

    if (NULL != m_getInstancesAndSubInstancesFunction)
    {
         (*m_getInstancesAndSubInstancesFunction) (connectedInstanceVector, connectedSubInstanceVector);
    }
}

void WaveFrameworkObjectManager::setGetThisSlotInstanceFunction (GetThisSlotInstanceFunction getThisSlotInstanceFunction)
{
    m_getThisSlotInstanceFunction  = getThisSlotInstanceFunction;
}

SI32 WaveFrameworkObjectManager::getThisSlotInstance ()
{
    SI32 instnace = 0;
    trace (TRACE_LEVEL_INFO, ("WaveFrameworkObjectManager:: getSlotInstance"));
    
    waveAssert (NULL != m_getThisSlotInstanceFunction, __FILE__, __LINE__);

    if (NULL != m_getThisSlotInstanceFunction)
    {
         instnace = (*m_getThisSlotInstanceFunction) ();
    }
    return (instnace);
}

void WaveFrameworkObjectManager::setCreateDummySlotFunction (CreateDummySlotFunction createDummySlotFunction)
{
    m_createDummySlotFunction = createDummySlotFunction;
}

void WaveFrameworkObjectManager::createDummySlot (const UI32 slotNumber)
{
    trace (TRACE_LEVEL_INFO, ("WaveFrameworkObjectManager:: createDummySlot"));

    waveAssert (NULL != m_createDummySlotFunction, __FILE__, __LINE__);

    //Create a dummy slot
    (*m_createDummySlotFunction) (slotNumber);
}

void WaveFrameworkObjectManager::disconnectFromAllInstanceClientsHandler (FrameworkObjectManagerDisconnectFromAllInstanceClientsMessage *pFrameworkObjectManagerDisconnectFromAllInstanceClientsMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::disconnectAllInstanceClientsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerFailedStep),
    };

    WaveLinearSequencerContext *pWaveLinearSequencerContext = new WaveLinearSequencerContext (pFrameworkObjectManagerDisconnectFromAllInstanceClientsMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pWaveLinearSequencerContext->holdAll ();
    pWaveLinearSequencerContext->start ();
}

void WaveFrameworkObjectManager::disconnectAllInstanceClientsStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
   FrameworkObjectManagerDisconnectFromAllInstanceClientsMessage *pFrameworkObjectManagerDisconnectFromAllInstanceClientsMessage = dynamic_cast<FrameworkObjectManagerDisconnectFromAllInstanceClientsMessage *>(pWaveLinearSequencerContext->getPWaveMessage());

    string     clientIpAddress = pFrameworkObjectManagerDisconnectFromAllInstanceClientsMessage->getClientIpAddress();

    FrameworkToolKit::disconnectFromAllInstanceClients (clientIpAddress);

    trace (TRACE_LEVEL_INFO, string ("WaveFrameworkObjectManager::disconnectAllInstanceClientsStep: ")+clientIpAddress);

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

// ZEROIZE_FOR_FIPS
void WaveFrameworkObjectManager::zeroizeForFIPSMessageHandler(ZeroizeForFIPSMessage *pMessage)
{

    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::zeroizeForFIPSMessageHandler: processing FIPSMEssage");
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::validateStandaloneStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::notifyAllClientSessionsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::triggerFIPSZeroizeStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::zeroizeSuccessStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkObjectManager::prismLinearSequencerFailedStep),
    };
    
    ZeroizeForFIPSLinearSequencerContext *pContext = new ZeroizeForFIPSLinearSequencerContext (pMessage, (WaveElement*)this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));
    
    pContext->holdAll ();
    pContext->start (); 
    return; 
}


void WaveFrameworkObjectManager::validateStandaloneStep(ZeroizeForFIPSLinearSequencerContext *pContext)
{
    ResourceId status = WAVE_MESSAGE_SUCCESS;

    LocationRole  thisLocationRole = FrameworkToolKit::getThisLocationRole ();

    if ((LOCATION_STAND_ALONE != thisLocationRole) &&
        (LOCATION_PRIMARY != thisLocationRole) &&
        (LOCATION_SECONDARY != thisLocationRole) &&
        (LOCATION_PRIMARY_UNCONFIRMED != thisLocationRole) &&
        (LOCATION_SECONDARY_UNCONFIRMED != thisLocationRole))
    {
        status = FIPS_OPERATION_ZEROIZE_FAILED_LOCATION_NOT_READY;

        trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::validateStandaloneStep : thisLocationRole is [") + FrameworkToolKit::localizeToSourceCodeEnum (thisLocationRole) + string ("]. So, failing Zeroize operation. Returning [") + FrameworkToolKit::localizeToSourceCodeEnum (status) + string ("]."));
    }
    else
    {
        trace (TRACE_LEVEL_INFO, string ("WaveFrameworkObjectManager::validateStandaloneStep : thisLocationRole is [") + FrameworkToolKit::localizeToSourceCodeEnum (thisLocationRole) + string ("]"));
    }

    if(true == isNodeZeroized() )
    {
        status = FIPS_OPERATION_ZEROIZE_FAILED_ALREADY_ZEROIZED;
        Wave::logOperationStatus (FIPS_OPERATION_ZEROIZE_FAILED_ALREADY_ZEROIZED);

        trace (TRACE_LEVEL_ERROR, string ("WaveFrameworkObjectManager::validateStandaloneStep : FIPS_OPERATION_ZEROIZE_FAILED_ALREADY_ZEROIZED"));
    }
    else
    {
        setNodeZeroized(true);

        // Zeroize is to be supported in FC mode.
        // i.e. It is to be allowed when cluster exists / does not exist.
        // So, commenting follwong "Wave::isWaveClusteringEnabled ()" check.
        // May need to update this in case of logical chassis.
        // Should a RASLOG be added in place of "FIPS_OPERATION_CONFIRMED_NODE_AS_STANDALONE" ?

#if 0
        if (Wave::isWaveClusteringEnabled())
        {
            status = FIPS_OPERATION_FAILED_FOR_NODE_NOT_STANDALONE;
            Wave::logOperationStatus (FIPS_OPERATION_FAILED_FOR_NODE_NOT_STANDALONE);
            setNodeZeroized(false);
        }
        else
        {
            Wave::logOperationStatus (FIPS_OPERATION_CONFIRMED_NODE_AS_STANDALONE);
        }
#endif
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::validateStandaloneStep : validation successful.");
    }
    pContext->executeNextStep(status);
}

void WaveFrameworkObjectManager::notifyAllClientSessionsStep (ZeroizeForFIPSLinearSequencerContext *pContext)
{
    
    vector<string> commandOutput;
    string          cmd = "/bin/touch " + WaveFrameworkObjectManager::getFIPSZeroizeFile();
    FrameworkToolKit::systemCommandOutput (cmd, commandOutput);
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::notifyAllClientSessionsStep : Beginning System Call SYNC");
    sync ();
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::notifyAllClientSessionsStep : Ending System Call SYNC");

    /* Rotate trc file so that only zeroize logs are present.
     */
    TraceObjectManager::rotateTraceFile (true);
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::notifyAllClientSessionsStep : rotateTraceFile");
    
    /* Prompt all user session about zeroization */

    bool clusterEnabled = Wave::clusterEnabledCheck ();

    if (false == clusterEnabled)
    {
        // In FC mode, print warning only from Dcmd.

        WaveClientSessionContext tempWaveClientSessionContext;
        tempWaveClientSessionContext.setWaveClientOriginatingLocationId(FrameworkToolKit::getThisLocationId());
        printfToAllWaveClientSessions(tempWaveClientSessionContext,"%s%s%s%s",
        "\n",
        "**********************************************************************\n",
        "System is Zeroizing.. Logout immediately.\n",
        "**********************************************************************\n");

        Wave::logOperationStatus (FIPS_OPERATION_NOTIFY_SESSIONS_ABT_ZEROIZE);
    }

    pContext->executeNextStep(WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::triggerFIPSZeroizeStep (ZeroizeForFIPSLinearSequencerContext *pContext)
{

    ResourceId status = WAVE_MESSAGE_SUCCESS;
    trace(TRACE_LEVEL_INFO,"WaveFrameworkObjectManager::triggerFIPSZeroizeStep: Entered\n");
    Wave::logOperationStatus (FIPS_OPERATION_TRIGGER_CLEANUP_FOR_ZEROIZE);

    FrameworkSequenceGenerator &frameworkSequenceGenerator = WaveFrameworkObjectManager::getCurrentFrameworkSequenceGenerator ();
    WaveZeroizeAgent *pZAgent = new WaveZeroizeAgent(this, frameworkSequenceGenerator);

    status = pZAgent->execute();
    if(status != WAVE_MESSAGE_SUCCESS)
    {
        trace(TRACE_LEVEL_FATAL,"WaveFrameworkObjectManager::triggerFIPSZeroizeStep: one or more services failed to zeroize\n");
    }
    else
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::triggerFIPSZeroizeStep : successfully executed WaveZeroizeAgent.");

        Wave::logOperationStatus (FIPS_OPERATION_ZEROIZE_SUCCESS);
    }
    pContext->executeNextStep(WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::zeroizeSuccessStep (ZeroizeForFIPSLinearSequencerContext *pZeroizeForFIPSLinearSequencerContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::zeroizeSuccessStep.");

    WaveFrameworkObjectManager::prismLinearSequencerSucceededStep (pZeroizeForFIPSLinearSequencerContext);

    UI32 numberOfIterations = 0;

    while (1)
    {
        if (0 == numberOfIterations % 10)
        {
            trace (TRACE_LEVEL_INFO, string ("WaveFrameworkObjectManager::zeroizeSuccessStep : waiting for the switch to reboot. [") + numberOfIterations + string ("]"));
        }

        if (numberOfIterations < 900)
        {
            ++numberOfIterations;
            prismSleep (1);
        }
        else
        {
            // In Dcmd, need to wait until Ccmd zeroize is over.
            // Is this assert required ? Or, should the system be kept running ?
            WaveNs::trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::zeroizeSuccessStep : after zeroize was successful, 15 minutes are over. System has not rebooted. So Dcmd/Ccmd is forcefully asserting thus causing the system to reboot");
            WaveNs::waveAssert (false, __FILE__, __LINE__);
        }
    }
}

string WaveFrameworkObjectManager::getFIPSZeroizeFile()
{
    return (FrameworkToolKit::getProcessInitialWorkingDirectory () + "/" + ".FIPSZeroizing");
}

void WaveFrameworkObjectManager::disconnectFromAllKnownLocations ()
{

    (WaveFrameworkObjectManager::getInstance())->disconnectFromAllConnectedNodes ();
    
    return;
}

void WaveFrameworkObjectManager::getFullyConnectedLocations (vector<LocationId> &connectedLocationsVector)
{
    if (NULL != m_pThisLocation)
    {
        m_pThisLocation->getFullyConnectedLocations (connectedLocationsVector);
    }
}

void WaveFrameworkObjectManager::rollbackCfgFile ()
{
    LocationBase *pThisLocation         = (WaveFrameworkObjectManager::getInstance ())->getThisLocation ();

    string        thisLocationIpAddress = FrameworkToolKit::getThisLocationIpAddress ();
    UI32          thisNodePort          = (UI32) FrameworkToolKit::getThisLocationPort ();

    WaveManagedObjectSynchronousQueryContext synchronousQueryContext(WaveNode::getClassName ());
    synchronousQueryContext.addAndAttribute (new AttributeString (thisLocationIpAddress, "ipAddress"));
    synchronousQueryContext.addAndAttribute (new AttributeUI32 (thisNodePort, "port"));

    vector<WaveManagedObject *> *pResults = querySynchronously (&synchronousQueryContext);

    waveAssert (NULL != pResults, __FILE__, __LINE__);

//    waveAssert (1 == pResults->size (), __FILE__, __LINE__);

    if (1 == pResults->size ())
    {
        WaveNode *pThisNode = dynamic_cast<WaveNode *> ((*pResults)[0]);

        waveAssert (NULL != pThisNode, __FILE__, __LINE__);

        LocationId locationId = pThisNode->getLocationId ();

        pThisLocation->setLocationId   (locationId);
        pThisLocation->setClusterPrimaryLocationId (locationId);
        pThisLocation->setClusterPrimaryPort (thisNodePort);
        FrameworkToolKit::setLastUsedLocationId (locationId);

        delete pThisNode;

        pResults->clear ();

        delete pResults;

        pResults = NULL;

        pResults = querySynchronously (WaveCluster::getClassName ());

        waveAssert (NULL != pResults, __FILE__, __LINE__);

        if (0 == pResults->size ())
        {
            pThisLocation->setLocationRole (LOCATION_STAND_ALONE);
        }
    }
    else if (0 == pResults->size ())
    {
        trace (TRACE_LEVEL_WARN, "Database is in inconsistent state, Query For WaveNode returns 0 WaveNode");
        trace (TRACE_LEVEL_WARN, "Going For Extreme Recovery");

        ResourceId status = FrameworkToolKit::changeWaveConfigurationValidity ( false );
        if ( status != WAVE_MESSAGE_SUCCESS  )
        {
            trace (TRACE_LEVEL_FATAL, ("WaveFrameworkObjectManager::rollbackCfgFile : Removing CFG file failed in extreme Recoverycase "));        
        }

        system ("/sbin/reboot -f");

        sleep (300);

        trace (TRACE_LEVEL_FATAL, ("System is not rebooting, Manual recovery is required"));

        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, "Very Inconsistent State, Asserting");
        waveAssert (false, __FILE__, __LINE__);
    }

    WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector(pResults);

    if (LOCATION_STAND_ALONE == (pThisLocation->getLocationRole ()))
    {
        // clear known location if any
        vector<LocationId>  knownRemoteLocations;
        UI32                numberOfKnownRemoteLocations = 0;

        pThisLocation->getKnownRemoteLocations (knownRemoteLocations);

        numberOfKnownRemoteLocations = knownRemoteLocations.size ();

        for (UI32 i = 0; i < numberOfKnownRemoteLocations; i++)
        {
            pThisLocation->removeKnownLocation (knownRemoteLocations[i]);
        }
    }
}

void WaveFrameworkObjectManager::setRaslogAssertFunction (RaslogAssertFunction raslogAssertFunction)
{
    m_raslogAssertFunction  = raslogAssertFunction;
}

void WaveFrameworkObjectManager::raslogAssert (const string &file, const string &function, const UI32 line, const string &assertString)
{
    if (NULL != m_raslogAssertFunction)
        (*m_raslogAssertFunction) (file, function, line, assertString);
}

void WaveFrameworkObjectManager::prepareNodeForHASupportHandler ()
{
    ResourceId status = m_pWaveFinalizeWorker->shutdownWaveServices ();

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::prepareNodeForHASupportHandler : shutdown should Never Fail");
        waveAssert (false, __FILE__, __LINE__);
    }

    status = m_pInitializeWorker->startWaveServices (WAVE_BOOT_PREPARE_FOR_HA_BOOT);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::prepareNodeForHASupportHandler Boot of Services should Never Fail In this case");
        waveAssert (false, __FILE__, __LINE__);
    }
}

void WaveFrameworkObjectManager::setGetFirmwareVersionFunction (GetFirmwareVersionFunction getFirmwareVersionFunction)
{
    m_getFirmwareVersionFunction = getFirmwareVersionFunction;
}

string WaveFrameworkObjectManager::getFirmwareVersion ()
{
    if (NULL != m_getFirmwareVersionFunction)
    {
        return ((*m_getFirmwareVersionFunction) ());
    }
    return ("");
}

void WaveFrameworkObjectManager::setHandleDcmFssConfigUpdateFunction (HandleDcmFssConfigUpdateFunction handleDcmFssConfigUpdateFunction)
{
    m_handleDcmFssConfigUpdateFunction = handleDcmFssConfigUpdateFunction;
}

int WaveFrameworkObjectManager::handleDcmFssConfigUpdate (void *dcmConfigData)
{
    if (NULL != m_handleDcmFssConfigUpdateFunction)
    {
        return ((*m_handleDcmFssConfigUpdateFunction) (dcmConfigData));
    }
    return (0);
}

void WaveFrameworkObjectManager::setSetVcsClusterConfigHandlerFunction (SetVcsClusterConfigHandlerFunction setVcsClusterConfigHandlerFunction)
{
    m_setVcsClusterConfigHandlerFunction = setVcsClusterConfigHandlerFunction;
}

ResourceId WaveFrameworkObjectManager::setVcsClusterConfigData (VcsClusterConfiguration *pDcmVcsClusterConfigData, const UI32 &context)
{
    if (NULL != m_setVcsClusterConfigHandlerFunction)
    {
        return ((*m_setVcsClusterConfigHandlerFunction) (pDcmVcsClusterConfigData, context));
    }
    return (WAVE_MESSAGE_ERROR);
}

void WaveFrameworkObjectManager::setGetVcsClusterConfigHandlerFunction (GetVcsClusterConfigHandlerFunction getVcsClusterConfigHandlerFunction)
{
    m_getVcsClusterConfigHandlerFunction = getVcsClusterConfigHandlerFunction;
}

void WaveFrameworkObjectManager::getVcsClusterConfigData (VcsClusterConfiguration *pDcmVcsClusterConfigData, const UI32 &context)
{
    if (NULL != m_getVcsClusterConfigHandlerFunction)
    {
        return ((*m_getVcsClusterConfigHandlerFunction) (pDcmVcsClusterConfigData, context));
    }
}

void WaveFrameworkObjectManager::setNotifySyncUpdateFailureFunction (NotifySyncUpdateFailureFunction notifySyncUpdateFailureFunction)
{
    m_notifySyncUpdateFailureFunction = notifySyncUpdateFailureFunction;
}

bool WaveFrameworkObjectManager::notifySyncUpdateFailure (const ResourceId &reason)
{
    if (NULL != m_notifySyncUpdateFailureFunction)
    {
        return ((*m_notifySyncUpdateFailureFunction) (reason));
    }
    return (false);
}

void WaveFrameworkObjectManager::setNotifyClusterReadyStateFunction (NotifyClusterReadyStateFunction notifyClusterReadyStateFunction)
{
    m_notifyClusterReadyStateFunction = notifyClusterReadyStateFunction;
}

void WaveFrameworkObjectManager::notifyClusterReadyState (bool &readyState)
{
    if (NULL != m_notifyClusterReadyStateFunction)
    {
        return ((*m_notifyClusterReadyStateFunction) (readyState));
    }
    return ;
}

bool WaveFrameworkObjectManager::isExternalStateSynchronizationRequired (WaveServiceId waveServiceId)
{
    m_externalStateSynchronizationRequiredListLock.lock();

    for (UI32 i = 0; i < m_externalStateSynchronizationRequiredList.size(); ++i)
    {
        if (waveServiceId == m_externalStateSynchronizationRequiredList[i])
        {
            m_externalStateSynchronizationRequiredListLock.unlock ();
            return true;
        }
    }
    
    m_externalStateSynchronizationRequiredListLock.unlock ();
    return false;
}

void  WaveFrameworkObjectManager::addToExternalStateSynchronizationRequiredList (WaveServiceId waveServiceId)
{
    if (isExternalStateSynchronizationRequired (waveServiceId))
    {
        WaveNs::trace (TRACE_LEVEL_INFO, string("WaveFrameworkObjectManager::addToExternalStateSynchronizationRequiredList waveServiceId ")+waveServiceId+ "already in state synchronization required list, request ignored");
    }
    else
    {
        m_externalStateSynchronizationRequiredListLock.lock();
        m_externalStateSynchronizationRequiredList.push_back (waveServiceId);
        m_externalStateSynchronizationRequiredListLock.unlock ();
        WaveNs::trace (TRACE_LEVEL_DEVEL, string ("WaveFrameworkObjectManager::addToExternalStateSynchronizationRequiredList:  ")+ FrameworkToolKit::getServiceNameById (waveServiceId)+ " SID: "+ waveServiceId+" added to external synchronization required list");
    }
}


bool WaveFrameworkObjectManager::getIsSyncDumpCompleted ( )
{
    return (m_pWaveFrameworkObjectManagerHaSyncWorker->getSyncDumpComplete ());
}

UI32 WaveFrameworkObjectManager::getSyncState ()
{
    return (m_pWaveFrameworkObjectManagerHaSyncWorker->getSyncState ());
}

void WaveFrameworkObjectManager::setSyncState (const UI32 &syncState)
{
    return (m_pWaveFrameworkObjectManagerHaSyncWorker->setSyncState (syncState));
}

UI32 WaveFrameworkObjectManager::getStandbySyncState ()
{
    return (m_pWaveFrameworkObjectManagerHaSyncWorker->getStandbySyncState ());
}

ResourceId WaveFrameworkObjectManager::upgradeDatabase ()
{
    WaveFrameworkConfiguration waveFrameworkConfiguration;
    bool ignoreConfigFile = true;
    ResourceId status = getPInitializeWorker ()->performSchemaConversion(waveFrameworkConfiguration, ignoreConfigFile);;
    if (FRAMEWORK_SUCCESS == status)
    {
        getPInitializeWorker ()->populateSchemaUpgradeTableInDb ();
    }
    return status;
}

void WaveFrameworkObjectManager::prepareNodeForWarmRecoveryWithDefaultConfiguration (FrameworkObjectManagerPrepareForWarmRecoveryWithDefaultConfiguration *pFrameworkObjectManagerPrepareForWarmRecoveryWithDefaultConfiguration)
{
    prepareNodeForHASupportHandler ();

    pFrameworkObjectManagerPrepareForWarmRecoveryWithDefaultConfiguration->setCompletionStatus (WAVE_MESSAGE_SUCCESS);

    reply (pFrameworkObjectManagerPrepareForWarmRecoveryWithDefaultConfiguration);
}

void WaveFrameworkObjectManager::storeConfigurationIntentMessageHandler (FrameworkObjectManagerStoreConfigurationIntentMessage *pFrameworkObjectManagerStoreConfigurationIntentMessage)
{
    //trace (TRACE_LEVEL_DEVEL, string ("WaveFrameworkObjectManager::storeConfigurationIntentMessageHandler : Entering ..."));

    UI32    configurationIntentMessageId            = pFrameworkObjectManagerStoreConfigurationIntentMessage->getConfigurationIntentMessageId ();
    UI32    configurationIntentBufferSize           = 0;
    char   *configurationIntentBuffer               = reinterpret_cast<char *> (pFrameworkObjectManagerStoreConfigurationIntentMessage->findBuffer (SERIALIZED_CONFIGURATION_INTENT_BUFFER, configurationIntentBufferSize));
    string  configurationIntentSerializedMessage    (configurationIntentBuffer, configurationIntentBufferSize);

    //trace (TRACE_LEVEL_DEBUG, string ("WaveFrameworkObjectManager::storeConfigurationIntentMessageHandler : Configuration intent message id : ") + configurationIntentMessageId + string (", Configuration intent serialized message : ") + configurationIntentSerializedMessage + string (", serialized buffer size : ") + configurationIntentBufferSize + ", serialized message size : " + configurationIntentSerializedMessage.size ());

    WaveConfigurationIntentRepository::addConfigurationIntent (configurationIntentMessageId, configurationIntentSerializedMessage);

    pFrameworkObjectManagerStoreConfigurationIntentMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    reply (pFrameworkObjectManagerStoreConfigurationIntentMessage);
}

void WaveFrameworkObjectManager::removeConfigurationIntentMessageHandler (FrameworkObjectManagerRemoveConfigurationIntentMessage *pFrameworkObjectManagerRemoveConfigurationIntentMessage)
{
    //trace (TRACE_LEVEL_DEVEL, string ("WaveFrameworkObjectManager::removeConfigurationIntentMessageHandler : Entering ..."));

    UI32    configurationIntentMessageId    = pFrameworkObjectManagerRemoveConfigurationIntentMessage->getConfigurationIntentMessageId ();

    //trace (TRACE_LEVEL_DEBUG, string ("WaveFrameworkObjectManager::removeConfigurationIntentMessageHandler : Configuration intent message id : ") + configurationIntentMessageId);

    WaveConfigurationIntentRepository::removeConfigurationIntent (configurationIntentMessageId);

    pFrameworkObjectManagerRemoveConfigurationIntentMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    reply (pFrameworkObjectManagerRemoveConfigurationIntentMessage);
}

void WaveFrameworkObjectManager::storeConfigurationIntentStaticMessageHandler (FrameworkObjectManagerStoreConfigurationIntentMessage *pFrameworkObjectManagerStoreConfigurationIntentMessage)
{
    //WaveNs::trace (TRACE_LEVEL_DEVEL, string ("WaveFrameworkObjectManager::storeConfigurationIntentStaticMessageHandler : Entering ..."));

    UI32    configurationIntentMessageId            = pFrameworkObjectManagerStoreConfigurationIntentMessage->getConfigurationIntentMessageId ();
    UI32    configurationIntentBufferSize           = 0;
    char   *configurationIntentBuffer               = reinterpret_cast<char *> (pFrameworkObjectManagerStoreConfigurationIntentMessage->findBuffer (SERIALIZED_CONFIGURATION_INTENT_BUFFER, configurationIntentBufferSize));
    string  configurationIntentSerializedMessage    (configurationIntentBuffer, configurationIntentBufferSize);

    //WaveNs::trace (TRACE_LEVEL_DEBUG, string ("WaveFrameworkObjectManager::storeConfigurationIntentStaticMessageHandler : Configuration intent message id : ") + configurationIntentMessageId + string (", Configuration intent serialized message : ") + configurationIntentSerializedMessage + string (", serialized buffer size : ") + configurationIntentBufferSize + ", serialized message size : " + configurationIntentSerializedMessage.size ());

    WaveConfigurationIntentRepository::addConfigurationIntent (configurationIntentMessageId, configurationIntentSerializedMessage);   

    pFrameworkObjectManagerStoreConfigurationIntentMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::removeConfigurationIntentStaticMessageHandler (FrameworkObjectManagerRemoveConfigurationIntentMessage *pFrameworkObjectManagerRemoveConfigurationIntentMessage)
{
    //WaveNs::trace (TRACE_LEVEL_DEVEL, string ("WaveFrameworkObjectManager::removeConfigurationIntentStaticMessageHandler : Entering ..."));

    //UI32    configurationIntentMessageId    = pFrameworkObjectManagerRemoveConfigurationIntentMessage->getConfigurationIntentMessageId ();

    //WaveNs::trace (TRACE_LEVEL_DEBUG, string ("WaveFrameworkObjectManager::removeConfigurationIntentStaticMessageHandler : Configuration intent message id : ") + configurationIntentMessageId);

    //WaveConfigurationIntentRepository::removeConfigurationIntent (configurationIntentMessageId);

    // For now we will always clear the entire intent repository since we currently only allowing a single intent to be replayed (the last stored intent).  Change this when we support batched configurations.

    WaveConfigurationIntentRepository::clearConfigurationIntentRepository ();

    pFrameworkObjectManagerRemoveConfigurationIntentMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::prepareStandbyAfterClusterPhaseSync (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManager::prepareStandbyAfterClusterPhaseSync (STANDBY)");

    ResourceId status = WAVE_MESSAGE_SUCCESS;

    status = m_pInitializeWorker->startWaveServices (WAVE_BOOT_HASTANDBY, WAVE_BOOT_PHASE_POST_PHASE);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::prepareStandbyAfterClusterPhaseSync: Post phase failed.");
        waveAssert (false, __FILE__, __LINE__);
    }

    pSecondaryNodeClusterPhase3Context->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkObjectManager::prepareFrameworkForHaRecoveryMessageHandler (FrameworkObjectManagerPrepareForHaFailoverWithPersistentConfiguration *pFrameworkObjectManagerPrepareForHaFailoverWithPersistentConfiguration)
{
    FrameworkToolKit::setSyncFailureNotified (false);

    LocationRole locationRole = m_pThisLocation->getLocationRole ();

    trace (TRACE_LEVEL_INFO, string ("WaveFrameworkObjectManager::prepareFrameworkForHaRecoveryMessageHandler with location role") + FrameworkToolKit::localize (locationRole));

    // If standby MM has the DB synced from active MM, always use running DB for failover.
    // In case DB is not in sync with active MM, HASM/FSS should trigger chassis reboot instead of failover
    // This covers the warm recovery and cold recovery with running config synced from active MM.
    // If DB was nevered synced to standby MM, and in case of active MM removal, standby MM reboot with
    // startup config file synced from active MM in case FC mode, and default config in MC mode with cold recovery

    if (getStandbySyncState () == IN_SYNC)
    {
        bool isWarmRecoveryInvolved = pFrameworkObjectManagerPrepareForHaFailoverWithPersistentConfiguration->isWarmHaRecoveryPreparationInProgress ();

        setWarmHaRecoveryPreparationInProgress (isWarmRecoveryInvolved);

        ResourceId status = m_pWaveFinalizeWorker->shutdownWaveServices (WAVE_SHUTDOWN_SECONDARY_REJOIN);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::prepareNodeForHASupportHandler : shutdown should Never Fail");
            waveAssert (false, __FILE__, __LINE__);
        }

        status = m_pInitializeWorker->startWaveServices (WAVE_BOOT_PERSISTENT, WAVE_BOOT_PREPARE_FOR_HA_FAILOVER_PHASE);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManager::prepareNodeForHASupportHandler Boot of Services should Never Fail In this case");
            waveAssert (false, __FILE__, __LINE__);
        } 

        setWarmHaRecoveryPreparationInProgress (false);
    }
    else
    {
        prepareNodeForHASupportHandler ();
    }

    WaveFrameworkObjectManager::setSecondaryNodeClusterCreationFlag (false);
    pFrameworkObjectManagerPrepareForHaFailoverWithPersistentConfiguration->setCompletionStatus (WAVE_MESSAGE_SUCCESS);

    reply (pFrameworkObjectManagerPrepareForHaFailoverWithPersistentConfiguration);
}

void WaveFrameworkObjectManager::resumePostponedMessages ()
{
    trace (TRACE_LEVEL_INFO, string ("WaveFrameworkObjectManager::resumePostponedMessages: Resuming all the pending messages"));
    resumeAllPostponedMessages ();
}

ClientStreamingSocket* WaveFrameworkObjectManager::getClientStreamingSocketForRemoteLocation (LocationId locationId)
{
    if (NULL != m_pThisLocation)
    {
        return (m_pThisLocation->getClientStreamingSocketForRemoteLocation (locationId));
    }

    return (NULL);
}

void WaveFrameworkObjectManager::replayConfigFileMessageHandler (WaveFrameworkReplayConfigMessage *pWaveFrameworkReplayConfigMessage)
{
    string      configFilePath          = ConfigFileManagementToolKit::getConfigFileManagementScriptsDirectory ();
    string      globalConfigFilename    = configFilePath + "/" + ConfigFileManagementToolKit::getConfigFileManagementGlobalOnlyFilename ();
    string      localConfigFilename     = configFilePath + "/" + ConfigFileManagementToolKit::getConfigFileManagementLocalOnlyFilename ();
    string      preConfigReplayCommands = "";
    ResourceId  status                  = WAVE_MESSAGE_SUCCESS;

    //replay global config file
    if (true == ConfigFileManagementToolKit::isFileExisting (globalConfigFilename))
    {
        trace (TRACE_LEVEL_INFO, string ("WaveFrameworkObjectManager::replayConfigFileIfRequired : Replay \"") + globalConfigFilename+ "\" config file on principal node...");
 
        status = ConfigFileManagementToolKit::replayConfigurationFile (configFilePath, ConfigFileManagementToolKit::getConfigFileManagementGlobalOnlyFilename (), preConfigReplayCommands);
 
        trace (TRACE_LEVEL_INFO, string ("WaveFrameworkObjectManager::replayConfigFileIfRequired : Replay of \"") + globalConfigFilename + "\" config file on principal node completed with status: " + FrameworkToolKit::localize (status));
 
        if (WAVE_MESSAGE_SUCCESS == status)
        {
            string newConfigFilename = globalConfigFilename + "." + FrameworkToolKit::getThisLocationIpAddress () + ".backup";
 
            ConfigFileManagementToolKit::renameConfigurationFile (globalConfigFilename, newConfigFilename);
        }
    }
    else
    {
        trace (TRACE_LEVEL_INFO, string ("WaveFrameworkObjectManager::replayConfigFileIfRequired : Skipping this step. ") + globalConfigFilename + " does not exist.");
    }

    //replay local Config file
    if (true == ConfigFileManagementToolKit::isFileExisting (localConfigFilename))
    {
        trace (TRACE_LEVEL_INFO, string ("WaveFrameworkObjectManager::replayConfigFileIfRequired : Replay \"") + localConfigFilename + "\" config file on principal node...");
 
        status = ConfigFileManagementToolKit::replayConfigurationFile (configFilePath, ConfigFileManagementToolKit::getConfigFileManagementLocalOnlyFilename (), preConfigReplayCommands);
            trace (TRACE_LEVEL_INFO, string ("WaveFrameworkObjectManager::replayConfigFileIfRequired : Replay of \"") + localConfigFilename + "\" config file on principal node completed with status: " + FrameworkToolKit::localize (status));    
        if (WAVE_MESSAGE_SUCCESS == status)
        {
            string newConfigFilename = localConfigFilename + "." + FrameworkToolKit::getThisLocationIpAddress () + ".backup";
            
            ConfigFileManagementToolKit::renameConfigurationFile (localConfigFilename, newConfigFilename);
        }   
    }
    else
    {
        trace (TRACE_LEVEL_INFO, string ("WaveFrameworkObjectManager::replayConfigFileIfRequired : Skipping this step. ") + localConfigFilename + " does not exist.");
    }


    pWaveFrameworkReplayConfigMessage->setCompletionStatus (status);
    reply (pWaveFrameworkReplayConfigMessage);
}

void WaveFrameworkObjectManager::resetFrameworkConfigurationToDefault ()
{
    if (NULL == m_pThisLocation)
    {   
        trace (TRACE_LEVEL_ERROR, "RecoverWaveBootAgent::updateFrameworkConfigurationToDefaultStep: Location config cannot be null");
        waveAssert (false, __FILE__, __LINE__);
    }

    LocationId locationId = (UI32) (1 << 8);

    m_pThisLocation->resetLocationToStandAlone   (locationId);
    m_pThisLocation->removeAllKnownLocations     ();
    m_pThisLocation->removeAllSubLocations       ();
    initializeLastUsedLocationId                 ();// resets last used location Id to 256
    setIsStartupValid                            (false);// This will be used to replay the startup file

}

string WaveFrameworkObjectManager::getGlobalConfigurationFileName ()
{
  return (s_frameworkGlobalConfigurationFile) ;
}

string WaveFrameworkObjectManager::getGlobalConfigurationTempFileName ()
{
  return (s_frameworkGlobalConfigurationTempFile);
}

}

