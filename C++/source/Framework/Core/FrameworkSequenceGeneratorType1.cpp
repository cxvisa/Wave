/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/FrameworkSequenceGeneratorType1.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
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

    m_waveServiceIdsToInitializeDuringPrePhase.push_back (TraceObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInitializeDuringPrePhase.push_back (TimerSignalObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInitializeDuringPrePhase.push_back (TimerObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInitializeDuringPrePhase.push_back (DatabaseObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInitializeDuringPrePhase.push_back (PersistenceObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInitializeDuringPrePhase.push_back (InterLocationMessageReceiverObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInitializeDuringPrePhase.push_back (InterLocationMessageTransportObjectManager::getWaveServiceId ());

    m_waveServiceIdsToInitialize.push_back (SoftwareManagementObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInitialize.push_back (ManagementInterfaceObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInitialize.push_back (ManagementInterfaceReceiverObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInitialize.push_back (LocalClusterConfigObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInitialize.push_back (CentralClusterConfigObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInitialize.push_back (HeartBeatObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInitialize.push_back (ClusterInterfaceObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInitialize.push_back (LockManagementObjectManager::getWaveServiceId ());

    m_waveServiceIdsToInitialize.push_back (TraceTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInitialize.push_back (FrameworkCoreTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInitialize.push_back (FrameworkTestability1ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInitialize.push_back (FrameworkTestability2ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInitialize.push_back (FrameworkTestability3ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInitialize.push_back (FrameworkTestability4ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInitialize.push_back (FrameworkTestability5ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInitialize.push_back (FrameworkTestability6ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInitialize.push_back (FrameworkLocalMessagingTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInitialize.push_back (FrameworkLocalMessagingTestObjectManager2::getWaveServiceId ());
    m_waveServiceIdsToInitialize.push_back (FrameworkRemoteMessagingTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInitialize.push_back (TimerTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInitialize.push_back (ClusterTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInitialize.push_back (PersistenceTestObjectManager::getWaveServiceId ());

    m_waveServiceIdsToInitialize.push_back (RegressionTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInitialize.push_back (ShellObjectManager::getWaveServiceId ());

    // Enable

    m_waveServiceIdsToEnableDuringPrePhase.push_back (TraceObjectManager::getWaveServiceId ());
    m_waveServiceIdsToEnableDuringPrePhase.push_back (TimerSignalObjectManager::getWaveServiceId ());
    m_waveServiceIdsToEnableDuringPrePhase.push_back (TimerObjectManager::getWaveServiceId ());
    m_waveServiceIdsToEnableDuringPrePhase.push_back (DatabaseObjectManager::getWaveServiceId ());
    m_waveServiceIdsToEnableDuringPrePhase.push_back (PersistenceObjectManager::getWaveServiceId ());
    m_waveServiceIdsToEnableDuringPrePhase.push_back (InterLocationMessageReceiverObjectManager::getWaveServiceId ());
    m_waveServiceIdsToEnableDuringPrePhase.push_back (InterLocationMessageTransportObjectManager::getWaveServiceId ());

    m_waveServiceIdsToEnable.push_back (SoftwareManagementObjectManager::getWaveServiceId ());
    m_waveServiceIdsToEnable.push_back (ManagementInterfaceObjectManager::getWaveServiceId ());
    m_waveServiceIdsToEnable.push_back (ManagementInterfaceReceiverObjectManager::getWaveServiceId ());
    m_waveServiceIdsToEnable.push_back (LocalClusterConfigObjectManager::getWaveServiceId ());
    m_waveServiceIdsToEnable.push_back (CentralClusterConfigObjectManager::getWaveServiceId ());
    m_waveServiceIdsToEnable.push_back (HeartBeatObjectManager::getWaveServiceId ());
    m_waveServiceIdsToEnable.push_back (ClusterInterfaceObjectManager::getWaveServiceId ());
    m_waveServiceIdsToEnable.push_back (LockManagementObjectManager::getWaveServiceId ());

    m_waveServiceIdsToEnable.push_back (TraceTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToEnable.push_back (FrameworkCoreTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToEnable.push_back (FrameworkTestability1ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToEnable.push_back (FrameworkTestability2ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToEnable.push_back (FrameworkTestability3ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToEnable.push_back (FrameworkTestability4ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToEnable.push_back (FrameworkTestability5ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToEnable.push_back (FrameworkTestability6ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToEnable.push_back (FrameworkLocalMessagingTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToEnable.push_back (FrameworkLocalMessagingTestObjectManager2::getWaveServiceId ());
    m_waveServiceIdsToEnable.push_back (FrameworkRemoteMessagingTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToEnable.push_back (TimerTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToEnable.push_back (ClusterTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToEnable.push_back (PersistenceTestObjectManager::getWaveServiceId ());

    m_waveServiceIdsToEnable.push_back (RegressionTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToEnable.push_back (ShellObjectManager::getWaveServiceId ());

    // Install

    m_waveServiceIdsToInstallDuringPrePhase.push_back (TraceObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInstallDuringPrePhase.push_back (TimerSignalObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInstallDuringPrePhase.push_back (TimerObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInstallDuringPrePhase.push_back (DatabaseObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInstallDuringPrePhase.push_back (PersistenceObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInstallDuringPrePhase.push_back (InterLocationMessageReceiverObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInstallDuringPrePhase.push_back (InterLocationMessageTransportObjectManager::getWaveServiceId ());

    m_waveServiceIdsToInstall.push_back (SoftwareManagementObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInstall.push_back (ManagementInterfaceObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInstall.push_back (ManagementInterfaceReceiverObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInstall.push_back (LocalClusterConfigObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInstall.push_back (CentralClusterConfigObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInstall.push_back (HeartBeatObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInstall.push_back (ClusterInterfaceObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInstall.push_back (LockManagementObjectManager::getWaveServiceId ());

    m_waveServiceIdsToInstall.push_back (TraceTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInstall.push_back (FrameworkCoreTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInstall.push_back (FrameworkTestability1ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInstall.push_back (FrameworkTestability2ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInstall.push_back (FrameworkTestability3ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInstall.push_back (FrameworkTestability4ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInstall.push_back (FrameworkTestability5ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInstall.push_back (FrameworkTestability6ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInstall.push_back (FrameworkLocalMessagingTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInstall.push_back (FrameworkLocalMessagingTestObjectManager2::getWaveServiceId ());
    m_waveServiceIdsToInstall.push_back (FrameworkRemoteMessagingTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInstall.push_back (TimerTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInstall.push_back (ClusterTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInstall.push_back (PersistenceTestObjectManager::getWaveServiceId ());

    m_waveServiceIdsToInstall.push_back (RegressionTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToInstall.push_back (ShellObjectManager::getWaveServiceId ());

    // Boot

    m_waveServiceIdsToBootDuringPrePhase.push_back (TraceObjectManager::getWaveServiceId ());
    m_waveServiceIdsToBootDuringPrePhase.push_back (TimerSignalObjectManager::getWaveServiceId ());
    m_waveServiceIdsToBootDuringPrePhase.push_back (TimerObjectManager::getWaveServiceId ());
    m_waveServiceIdsToBootDuringPrePhase.push_back (DatabaseObjectManager::getWaveServiceId ());
    m_waveServiceIdsToBootDuringPrePhase.push_back (PersistenceObjectManager::getWaveServiceId ());
    m_waveServiceIdsToBootDuringPrePhase.push_back (InterLocationMessageReceiverObjectManager::getWaveServiceId ());
    m_waveServiceIdsToBootDuringPrePhase.push_back (InterLocationMessageTransportObjectManager::getWaveServiceId ());

    m_waveServiceIdsToBoot.push_back (SoftwareManagementObjectManager::getWaveServiceId ());
    m_waveServiceIdsToBoot.push_back (ManagementInterfaceObjectManager::getWaveServiceId ());
    m_waveServiceIdsToBoot.push_back (ManagementInterfaceReceiverObjectManager::getWaveServiceId ());
    m_waveServiceIdsToBoot.push_back (LocalClusterConfigObjectManager::getWaveServiceId ());
    m_waveServiceIdsToBoot.push_back (CentralClusterConfigObjectManager::getWaveServiceId ());
    m_waveServiceIdsToBoot.push_back (HeartBeatObjectManager::getWaveServiceId ());
    m_waveServiceIdsToBoot.push_back (ClusterInterfaceObjectManager::getWaveServiceId ());
    m_waveServiceIdsToBoot.push_back (LockManagementObjectManager::getWaveServiceId ());

    m_waveServiceIdsToBoot.push_back (TraceTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToBoot.push_back (FrameworkCoreTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToBoot.push_back (FrameworkTestability1ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToBoot.push_back (FrameworkTestability2ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToBoot.push_back (FrameworkTestability3ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToBoot.push_back (FrameworkTestability4ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToBoot.push_back (FrameworkTestability5ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToBoot.push_back (FrameworkTestability6ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToBoot.push_back (FrameworkLocalMessagingTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToBoot.push_back (FrameworkLocalMessagingTestObjectManager2::getWaveServiceId ());
    m_waveServiceIdsToBoot.push_back (FrameworkRemoteMessagingTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToBoot.push_back (TimerTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToBoot.push_back (ClusterTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToBoot.push_back (PersistenceTestObjectManager::getWaveServiceId ());

    m_waveServiceIdsToBoot.push_back (RegressionTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToBoot.push_back (ShellObjectManager::getWaveServiceId ());

    // Shutdown

    m_waveServiceIdsToShutdown.push_back (ShellObjectManager::getWaveServiceId ());
    m_waveServiceIdsToShutdown.push_back (RegressionTestObjectManager::getWaveServiceId ());

    m_waveServiceIdsToShutdown.push_back (LocalClusterConfigObjectManager::getWaveServiceId ());
    m_waveServiceIdsToShutdown.push_back (CentralClusterConfigObjectManager::getWaveServiceId ());
    m_waveServiceIdsToShutdown.push_back (HeartBeatObjectManager::getWaveServiceId ());
    m_waveServiceIdsToShutdown.push_back (ClusterInterfaceObjectManager::getWaveServiceId ());
    m_waveServiceIdsToShutdown.push_back (LockManagementObjectManager::getWaveServiceId ());

    m_waveServiceIdsToShutdown.push_back (TraceTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToShutdown.push_back (FrameworkCoreTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToShutdown.push_back (FrameworkTestability1ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToShutdown.push_back (FrameworkTestability2ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToShutdown.push_back (FrameworkTestability3ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToShutdown.push_back (FrameworkTestability4ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToShutdown.push_back (FrameworkTestability5ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToShutdown.push_back (FrameworkTestability6ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToShutdown.push_back (FrameworkLocalMessagingTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToShutdown.push_back (FrameworkLocalMessagingTestObjectManager2::getWaveServiceId ());
    m_waveServiceIdsToShutdown.push_back (FrameworkRemoteMessagingTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToShutdown.push_back (TimerTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToShutdown.push_back (ClusterTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToShutdown.push_back (PersistenceTestObjectManager::getWaveServiceId ());

    m_waveServiceIdsToShutdown.push_back (ManagementInterfaceObjectManager::getWaveServiceId ());
    m_waveServiceIdsToShutdown.push_back (InterLocationMessageTransportObjectManager::getWaveServiceId ());
    m_waveServiceIdsToShutdown.push_back (RegressionTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToShutdown.push_back (TimerObjectManager::getWaveServiceId ());
    m_waveServiceIdsToShutdown.push_back (TimerSignalObjectManager::getWaveServiceId ());
    m_waveServiceIdsToShutdown.push_back (SoftwareManagementObjectManager::getWaveServiceId ());
    m_waveServiceIdsToShutdown.push_back (PersistenceObjectManager::getWaveServiceId ());
    m_waveServiceIdsToShutdown.push_back (DatabaseObjectManager::getWaveServiceId ());
    m_waveServiceIdsToShutdown.push_back (TraceObjectManager::getWaveServiceId ());

    // Disable

    m_waveServiceIdsToDisable.push_back (ShellObjectManager::getWaveServiceId ());
    m_waveServiceIdsToDisable.push_back (RegressionTestObjectManager::getWaveServiceId ());

    m_waveServiceIdsToDisable.push_back (LocalClusterConfigObjectManager::getWaveServiceId ());
    m_waveServiceIdsToDisable.push_back (CentralClusterConfigObjectManager::getWaveServiceId ());
    m_waveServiceIdsToDisable.push_back (HeartBeatObjectManager::getWaveServiceId ());
    m_waveServiceIdsToDisable.push_back (ClusterInterfaceObjectManager::getWaveServiceId ());
    m_waveServiceIdsToDisable.push_back (LockManagementObjectManager::getWaveServiceId ());

    m_waveServiceIdsToDisable.push_back (TraceTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToDisable.push_back (FrameworkCoreTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToDisable.push_back (FrameworkTestability1ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToDisable.push_back (FrameworkTestability2ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToDisable.push_back (FrameworkTestability3ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToDisable.push_back (FrameworkTestability4ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToDisable.push_back (FrameworkTestability5ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToDisable.push_back (FrameworkTestability6ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToDisable.push_back (FrameworkLocalMessagingTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToDisable.push_back (FrameworkLocalMessagingTestObjectManager2::getWaveServiceId ());
    m_waveServiceIdsToDisable.push_back (FrameworkRemoteMessagingTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToDisable.push_back (TimerTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToDisable.push_back (ClusterTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToDisable.push_back (PersistenceTestObjectManager::getWaveServiceId ());

    //m_waveServiceIdsToDisable.push_back (WaveFrameworkObjectManager::getWaveServiceId ());
    m_waveServiceIdsToDisable.push_back (ManagementInterfaceObjectManager::getWaveServiceId ());
    m_waveServiceIdsToDisable.push_back (InterLocationMessageTransportObjectManager::getWaveServiceId ());
    m_waveServiceIdsToDisable.push_back (RegressionTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToDisable.push_back (TimerObjectManager::getWaveServiceId ());
    m_waveServiceIdsToDisable.push_back (TimerSignalObjectManager::getWaveServiceId ());
    m_waveServiceIdsToDisable.push_back (SoftwareManagementObjectManager::getWaveServiceId ());
    m_waveServiceIdsToDisable.push_back (PersistenceObjectManager::getWaveServiceId ());
    m_waveServiceIdsToDisable.push_back (DatabaseObjectManager::getWaveServiceId ());
    m_waveServiceIdsToDisable.push_back (TraceObjectManager::getWaveServiceId ());

    // Failover

    m_waveServiceIdsToFailover.push_back (TraceObjectManager::getWaveServiceId ());
    m_waveServiceIdsToFailover.push_back (TimerObjectManager::getWaveServiceId ());
    m_waveServiceIdsToFailover.push_back (DatabaseObjectManager::getWaveServiceId ());
    m_waveServiceIdsToFailover.push_back (PersistenceObjectManager::getWaveServiceId ());
    m_waveServiceIdsToFailover.push_back (InterLocationMessageTransportObjectManager::getWaveServiceId ());

    m_waveServiceIdsToFailover.push_back (LicenseObjectManager::getWaveServiceId ());
    m_waveServiceIdsToFailover.push_back (SoftwareManagementObjectManager::getWaveServiceId ());
    m_waveServiceIdsToFailover.push_back (ManagementInterfaceObjectManager::getWaveServiceId ());
    m_waveServiceIdsToFailover.push_back (LocalClusterConfigObjectManager::getWaveServiceId ());
    m_waveServiceIdsToFailover.push_back (CentralClusterConfigObjectManager::getWaveServiceId ());
    m_waveServiceIdsToFailover.push_back (HeartBeatObjectManager::getWaveServiceId ());
    m_waveServiceIdsToFailover.push_back (ClusterInterfaceObjectManager::getWaveServiceId ());
    m_waveServiceIdsToFailover.push_back (LockManagementObjectManager::getWaveServiceId ());

    m_waveServiceIdsToFailover.push_back (LicenseTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToFailover.push_back (TraceTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToFailover.push_back (FrameworkCoreTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToFailover.push_back (FrameworkTestability1ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToFailover.push_back (FrameworkTestability2ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToFailover.push_back (FrameworkTestability3ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToFailover.push_back (FrameworkTestability4ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToFailover.push_back (FrameworkTestability5ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToFailover.push_back (FrameworkTestability6ObjectManager::getWaveServiceId ());
    m_waveServiceIdsToFailover.push_back (FrameworkLocalMessagingTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToFailover.push_back (FrameworkLocalMessagingTestObjectManager2::getWaveServiceId ());
    m_waveServiceIdsToFailover.push_back (FrameworkRemoteMessagingTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToFailover.push_back (TimerTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToFailover.push_back (ClusterTestObjectManager::getWaveServiceId ());
    m_waveServiceIdsToFailover.push_back (PersistenceTestObjectManager::getWaveServiceId ());

    m_waveServiceIdsToFailover.push_back (RegressionTestObjectManager::getWaveServiceId ());
}

FrameworkSequenceGeneratorType1::~FrameworkSequenceGeneratorType1 ()
{
}

}
