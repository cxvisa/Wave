/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/FrameworkSequenceGeneratorType1.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"
#include "Framework/Core/Test/FrameworkCoreTestObjectManager.h"
#include "Framework/Core/Test/FrameworkTestability1ObjectManager.h"
#include "Framework/Core/Test/FrameworkTestability2ObjectManager.h"
#include "Framework/Core/Test/FrameworkTestability3ObjectManager.h"
#include "Framework/Core/Test/FrameworkTestability4ObjectManager.h"
#include "Framework/Core/Test/FrameworkTestability5ObjectManager.h"
#include "Framework/Core/Test/FrameworkTestability6ObjectManager.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Persistence/PersistenceObjectManager.h"
#include "Framework/Messaging/Local/Test/FrameworkLocalMessagingTestObjectManager.h"
#include "Framework/Messaging/Local/Test/FrameworkLocalMessagingTestObjectManager2.h"
#include "Framework/Messaging/Remote/Test/FrameworkRemoteMessagingTestObjectManager.h"
#include "Shell/ShellObjectManager.h"
#include "License/LicenseObjectManager.h"
#include "License/Test/LicenseTestObjectManager.h"
#include "Framework/Trace/TraceObjectManager.h"
#include "Framework/Trace/Test/TraceTestObjectManager.h"
#include "Regression/RegressionTestObjectManager.h"
#include "App/ClusterInterfaceObjectManager.h"
#include "Cluster/CentralClusterConfigObjectManager.h"
#include "Cluster/LocalClusterConfigObjectManager.h"
#include "Cluster/Local/HeartBeat/HeartBeatObjectManager.h"
#include "Cluster/Test/ClusterTestObjectManager.h"
#include "Framework/Timer/TimerObjectManager.h"
#include "Framework/Timer/TimerSignalObjectManager.h"
#include "Framework/Timer/Test/TimerTestObjectManager.h"
#include "SoftwareManagement/SoftwareManagementObjectManager.h"
#include "ManagementInterface/ManagementInterfaceObjectManager.h"
#include "Framework/Messaging/Remote/InterLocationMessageTransportObjectManager.h"
#include "Framework/Messaging/Remote/InterLocationMessageReceiverObjectManager.h"
#include "ManagementInterface/ManagementInterfaceReceiverObjectManager.h"
#include "Framework/Persistence/Test/PersistenceTestObjectManager.h"
#include "LockManagement/LockManagementObjectManager.h"

namespace WaveNs
{

FrameworkSequenceGeneratorType1::FrameworkSequenceGeneratorType1 ()
    : FrameworkSequenceGenerator ()
{
    // Initialize

    m_prismServiceIdsToInitializeDuringPrePhase.push_back (TraceObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInitializeDuringPrePhase.push_back (TimerSignalObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInitializeDuringPrePhase.push_back (TimerObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInitializeDuringPrePhase.push_back (DatabaseObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInitializeDuringPrePhase.push_back (PersistenceObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInitializeDuringPrePhase.push_back (InterLocationMessageReceiverObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInitializeDuringPrePhase.push_back (InterLocationMessageTransportObjectManager::getWaveServiceId ());

    m_prismServiceIdsToInitialize.push_back (SoftwareManagementObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInitialize.push_back (ManagementInterfaceObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInitialize.push_back (ManagementInterfaceReceiverObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInitialize.push_back (LocalClusterConfigObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInitialize.push_back (CentralClusterConfigObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInitialize.push_back (HeartBeatObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInitialize.push_back (ClusterInterfaceObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInitialize.push_back (LockManagementObjectManager::getWaveServiceId ());

    m_prismServiceIdsToInitialize.push_back (TraceTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInitialize.push_back (FrameworkCoreTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInitialize.push_back (FrameworkTestability1ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInitialize.push_back (FrameworkTestability2ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInitialize.push_back (FrameworkTestability3ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInitialize.push_back (FrameworkTestability4ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInitialize.push_back (FrameworkTestability5ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInitialize.push_back (FrameworkTestability6ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInitialize.push_back (FrameworkLocalMessagingTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInitialize.push_back (FrameworkLocalMessagingTestObjectManager2::getWaveServiceId ());
    m_prismServiceIdsToInitialize.push_back (FrameworkRemoteMessagingTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInitialize.push_back (TimerTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInitialize.push_back (ClusterTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInitialize.push_back (PersistenceTestObjectManager::getWaveServiceId ());

    m_prismServiceIdsToInitialize.push_back (RegressionTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInitialize.push_back (ShellObjectManager::getWaveServiceId ());

    // Enable

    m_prismServiceIdsToEnableDuringPrePhase.push_back (TraceObjectManager::getWaveServiceId ());
    m_prismServiceIdsToEnableDuringPrePhase.push_back (TimerSignalObjectManager::getWaveServiceId ());
    m_prismServiceIdsToEnableDuringPrePhase.push_back (TimerObjectManager::getWaveServiceId ());
    m_prismServiceIdsToEnableDuringPrePhase.push_back (DatabaseObjectManager::getWaveServiceId ());
    m_prismServiceIdsToEnableDuringPrePhase.push_back (PersistenceObjectManager::getWaveServiceId ());
    m_prismServiceIdsToEnableDuringPrePhase.push_back (InterLocationMessageReceiverObjectManager::getWaveServiceId ());
    m_prismServiceIdsToEnableDuringPrePhase.push_back (InterLocationMessageTransportObjectManager::getWaveServiceId ());

    m_prismServiceIdsToEnable.push_back (SoftwareManagementObjectManager::getWaveServiceId ());
    m_prismServiceIdsToEnable.push_back (ManagementInterfaceObjectManager::getWaveServiceId ());
    m_prismServiceIdsToEnable.push_back (ManagementInterfaceReceiverObjectManager::getWaveServiceId ());
    m_prismServiceIdsToEnable.push_back (LocalClusterConfigObjectManager::getWaveServiceId ());
    m_prismServiceIdsToEnable.push_back (CentralClusterConfigObjectManager::getWaveServiceId ());
    m_prismServiceIdsToEnable.push_back (HeartBeatObjectManager::getWaveServiceId ());
    m_prismServiceIdsToEnable.push_back (ClusterInterfaceObjectManager::getWaveServiceId ());
    m_prismServiceIdsToEnable.push_back (LockManagementObjectManager::getWaveServiceId ());

    m_prismServiceIdsToEnable.push_back (TraceTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToEnable.push_back (FrameworkCoreTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToEnable.push_back (FrameworkTestability1ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToEnable.push_back (FrameworkTestability2ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToEnable.push_back (FrameworkTestability3ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToEnable.push_back (FrameworkTestability4ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToEnable.push_back (FrameworkTestability5ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToEnable.push_back (FrameworkTestability6ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToEnable.push_back (FrameworkLocalMessagingTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToEnable.push_back (FrameworkLocalMessagingTestObjectManager2::getWaveServiceId ());
    m_prismServiceIdsToEnable.push_back (FrameworkRemoteMessagingTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToEnable.push_back (TimerTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToEnable.push_back (ClusterTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToEnable.push_back (PersistenceTestObjectManager::getWaveServiceId ());

    m_prismServiceIdsToEnable.push_back (RegressionTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToEnable.push_back (ShellObjectManager::getWaveServiceId ());

    // Install

    m_prismServiceIdsToInstallDuringPrePhase.push_back (TraceObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInstallDuringPrePhase.push_back (TimerSignalObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInstallDuringPrePhase.push_back (TimerObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInstallDuringPrePhase.push_back (DatabaseObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInstallDuringPrePhase.push_back (PersistenceObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInstallDuringPrePhase.push_back (InterLocationMessageReceiverObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInstallDuringPrePhase.push_back (InterLocationMessageTransportObjectManager::getWaveServiceId ());

    m_prismServiceIdsToInstall.push_back (SoftwareManagementObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInstall.push_back (ManagementInterfaceObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInstall.push_back (ManagementInterfaceReceiverObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInstall.push_back (LocalClusterConfigObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInstall.push_back (CentralClusterConfigObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInstall.push_back (HeartBeatObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInstall.push_back (ClusterInterfaceObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInstall.push_back (LockManagementObjectManager::getWaveServiceId ());

    m_prismServiceIdsToInstall.push_back (TraceTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInstall.push_back (FrameworkCoreTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInstall.push_back (FrameworkTestability1ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInstall.push_back (FrameworkTestability2ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInstall.push_back (FrameworkTestability3ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInstall.push_back (FrameworkTestability4ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInstall.push_back (FrameworkTestability5ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInstall.push_back (FrameworkTestability6ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInstall.push_back (FrameworkLocalMessagingTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInstall.push_back (FrameworkLocalMessagingTestObjectManager2::getWaveServiceId ());
    m_prismServiceIdsToInstall.push_back (FrameworkRemoteMessagingTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInstall.push_back (TimerTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInstall.push_back (ClusterTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInstall.push_back (PersistenceTestObjectManager::getWaveServiceId ());

    m_prismServiceIdsToInstall.push_back (RegressionTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToInstall.push_back (ShellObjectManager::getWaveServiceId ());

    // Boot

    m_prismServiceIdsToBootDuringPrePhase.push_back (TraceObjectManager::getWaveServiceId ());
    m_prismServiceIdsToBootDuringPrePhase.push_back (TimerSignalObjectManager::getWaveServiceId ());
    m_prismServiceIdsToBootDuringPrePhase.push_back (TimerObjectManager::getWaveServiceId ());
    m_prismServiceIdsToBootDuringPrePhase.push_back (DatabaseObjectManager::getWaveServiceId ());
    m_prismServiceIdsToBootDuringPrePhase.push_back (PersistenceObjectManager::getWaveServiceId ());
    m_prismServiceIdsToBootDuringPrePhase.push_back (InterLocationMessageReceiverObjectManager::getWaveServiceId ());
    m_prismServiceIdsToBootDuringPrePhase.push_back (InterLocationMessageTransportObjectManager::getWaveServiceId ());

    m_prismServiceIdsToBoot.push_back (SoftwareManagementObjectManager::getWaveServiceId ());
    m_prismServiceIdsToBoot.push_back (ManagementInterfaceObjectManager::getWaveServiceId ());
    m_prismServiceIdsToBoot.push_back (ManagementInterfaceReceiverObjectManager::getWaveServiceId ());
    m_prismServiceIdsToBoot.push_back (LocalClusterConfigObjectManager::getWaveServiceId ());
    m_prismServiceIdsToBoot.push_back (CentralClusterConfigObjectManager::getWaveServiceId ());
    m_prismServiceIdsToBoot.push_back (HeartBeatObjectManager::getWaveServiceId ());
    m_prismServiceIdsToBoot.push_back (ClusterInterfaceObjectManager::getWaveServiceId ());
    m_prismServiceIdsToBoot.push_back (LockManagementObjectManager::getWaveServiceId ());

    m_prismServiceIdsToBoot.push_back (TraceTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToBoot.push_back (FrameworkCoreTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToBoot.push_back (FrameworkTestability1ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToBoot.push_back (FrameworkTestability2ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToBoot.push_back (FrameworkTestability3ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToBoot.push_back (FrameworkTestability4ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToBoot.push_back (FrameworkTestability5ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToBoot.push_back (FrameworkTestability6ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToBoot.push_back (FrameworkLocalMessagingTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToBoot.push_back (FrameworkLocalMessagingTestObjectManager2::getWaveServiceId ());
    m_prismServiceIdsToBoot.push_back (FrameworkRemoteMessagingTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToBoot.push_back (TimerTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToBoot.push_back (ClusterTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToBoot.push_back (PersistenceTestObjectManager::getWaveServiceId ());

    m_prismServiceIdsToBoot.push_back (RegressionTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToBoot.push_back (ShellObjectManager::getWaveServiceId ());

    // Shutdown

    m_prismServiceIdsToShutdown.push_back (ShellObjectManager::getWaveServiceId ());
    m_prismServiceIdsToShutdown.push_back (RegressionTestObjectManager::getWaveServiceId ());

    m_prismServiceIdsToShutdown.push_back (LocalClusterConfigObjectManager::getWaveServiceId ());
    m_prismServiceIdsToShutdown.push_back (CentralClusterConfigObjectManager::getWaveServiceId ());
    m_prismServiceIdsToShutdown.push_back (HeartBeatObjectManager::getWaveServiceId ());
    m_prismServiceIdsToShutdown.push_back (ClusterInterfaceObjectManager::getWaveServiceId ());
    m_prismServiceIdsToShutdown.push_back (LockManagementObjectManager::getWaveServiceId ());

    m_prismServiceIdsToShutdown.push_back (TraceTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToShutdown.push_back (FrameworkCoreTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToShutdown.push_back (FrameworkTestability1ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToShutdown.push_back (FrameworkTestability2ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToShutdown.push_back (FrameworkTestability3ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToShutdown.push_back (FrameworkTestability4ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToShutdown.push_back (FrameworkTestability5ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToShutdown.push_back (FrameworkTestability6ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToShutdown.push_back (FrameworkLocalMessagingTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToShutdown.push_back (FrameworkLocalMessagingTestObjectManager2::getWaveServiceId ());
    m_prismServiceIdsToShutdown.push_back (FrameworkRemoteMessagingTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToShutdown.push_back (TimerTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToShutdown.push_back (ClusterTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToShutdown.push_back (PersistenceTestObjectManager::getWaveServiceId ());

    m_prismServiceIdsToShutdown.push_back (ManagementInterfaceObjectManager::getWaveServiceId ());
    m_prismServiceIdsToShutdown.push_back (InterLocationMessageTransportObjectManager::getWaveServiceId ());
    m_prismServiceIdsToShutdown.push_back (RegressionTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToShutdown.push_back (TimerObjectManager::getWaveServiceId ());
    m_prismServiceIdsToShutdown.push_back (TimerSignalObjectManager::getWaveServiceId ());
    m_prismServiceIdsToShutdown.push_back (SoftwareManagementObjectManager::getWaveServiceId ());
    m_prismServiceIdsToShutdown.push_back (PersistenceObjectManager::getWaveServiceId ());
    m_prismServiceIdsToShutdown.push_back (DatabaseObjectManager::getWaveServiceId ());
    m_prismServiceIdsToShutdown.push_back (TraceObjectManager::getWaveServiceId ());

    // Disable

    m_prismServiceIdsToDisable.push_back (ShellObjectManager::getWaveServiceId ());
    m_prismServiceIdsToDisable.push_back (RegressionTestObjectManager::getWaveServiceId ());

    m_prismServiceIdsToDisable.push_back (LocalClusterConfigObjectManager::getWaveServiceId ());
    m_prismServiceIdsToDisable.push_back (CentralClusterConfigObjectManager::getWaveServiceId ());
    m_prismServiceIdsToDisable.push_back (HeartBeatObjectManager::getWaveServiceId ());
    m_prismServiceIdsToDisable.push_back (ClusterInterfaceObjectManager::getWaveServiceId ());
    m_prismServiceIdsToDisable.push_back (LockManagementObjectManager::getWaveServiceId ());

    m_prismServiceIdsToDisable.push_back (TraceTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToDisable.push_back (FrameworkCoreTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToDisable.push_back (FrameworkTestability1ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToDisable.push_back (FrameworkTestability2ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToDisable.push_back (FrameworkTestability3ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToDisable.push_back (FrameworkTestability4ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToDisable.push_back (FrameworkTestability5ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToDisable.push_back (FrameworkTestability6ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToDisable.push_back (FrameworkLocalMessagingTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToDisable.push_back (FrameworkLocalMessagingTestObjectManager2::getWaveServiceId ());
    m_prismServiceIdsToDisable.push_back (FrameworkRemoteMessagingTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToDisable.push_back (TimerTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToDisable.push_back (ClusterTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToDisable.push_back (PersistenceTestObjectManager::getWaveServiceId ());

    //m_prismServiceIdsToDisable.push_back (PrismFrameworkObjectManager::getWaveServiceId ());
    m_prismServiceIdsToDisable.push_back (ManagementInterfaceObjectManager::getWaveServiceId ());
    m_prismServiceIdsToDisable.push_back (InterLocationMessageTransportObjectManager::getWaveServiceId ());
    m_prismServiceIdsToDisable.push_back (RegressionTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToDisable.push_back (TimerObjectManager::getWaveServiceId ());
    m_prismServiceIdsToDisable.push_back (TimerSignalObjectManager::getWaveServiceId ());
    m_prismServiceIdsToDisable.push_back (SoftwareManagementObjectManager::getWaveServiceId ());
    m_prismServiceIdsToDisable.push_back (PersistenceObjectManager::getWaveServiceId ());
    m_prismServiceIdsToDisable.push_back (DatabaseObjectManager::getWaveServiceId ());
    m_prismServiceIdsToDisable.push_back (TraceObjectManager::getWaveServiceId ());

    // Failover

    m_prismServiceIdsToFailover.push_back (TraceObjectManager::getWaveServiceId ());
    m_prismServiceIdsToFailover.push_back (TimerObjectManager::getWaveServiceId ());
    m_prismServiceIdsToFailover.push_back (DatabaseObjectManager::getWaveServiceId ());
    m_prismServiceIdsToFailover.push_back (PersistenceObjectManager::getWaveServiceId ());
    m_prismServiceIdsToFailover.push_back (InterLocationMessageTransportObjectManager::getWaveServiceId ());

    m_prismServiceIdsToFailover.push_back (LicenseObjectManager::getWaveServiceId ());
    m_prismServiceIdsToFailover.push_back (SoftwareManagementObjectManager::getWaveServiceId ());
    m_prismServiceIdsToFailover.push_back (ManagementInterfaceObjectManager::getWaveServiceId ());
    m_prismServiceIdsToFailover.push_back (LocalClusterConfigObjectManager::getWaveServiceId ());
    m_prismServiceIdsToFailover.push_back (CentralClusterConfigObjectManager::getWaveServiceId ());
    m_prismServiceIdsToFailover.push_back (HeartBeatObjectManager::getWaveServiceId ());
    m_prismServiceIdsToFailover.push_back (ClusterInterfaceObjectManager::getWaveServiceId ());
    m_prismServiceIdsToFailover.push_back (LockManagementObjectManager::getWaveServiceId ());

    m_prismServiceIdsToFailover.push_back (LicenseTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToFailover.push_back (TraceTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToFailover.push_back (FrameworkCoreTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToFailover.push_back (FrameworkTestability1ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToFailover.push_back (FrameworkTestability2ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToFailover.push_back (FrameworkTestability3ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToFailover.push_back (FrameworkTestability4ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToFailover.push_back (FrameworkTestability5ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToFailover.push_back (FrameworkTestability6ObjectManager::getWaveServiceId ());
    m_prismServiceIdsToFailover.push_back (FrameworkLocalMessagingTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToFailover.push_back (FrameworkLocalMessagingTestObjectManager2::getWaveServiceId ());
    m_prismServiceIdsToFailover.push_back (FrameworkRemoteMessagingTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToFailover.push_back (TimerTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToFailover.push_back (ClusterTestObjectManager::getWaveServiceId ());
    m_prismServiceIdsToFailover.push_back (PersistenceTestObjectManager::getWaveServiceId ());

    m_prismServiceIdsToFailover.push_back (RegressionTestObjectManager::getWaveServiceId ());
}

FrameworkSequenceGeneratorType1::~FrameworkSequenceGeneratorType1 ()
{
}

}
