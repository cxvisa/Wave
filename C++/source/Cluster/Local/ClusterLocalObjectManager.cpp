/***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Cluster/Local/ClusterLocalObjectManager.h"
#include "Cluster/Local/WaveNode.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContext.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForShutdownPhases.h"
#include "Framework/Utils/WaveSynchronousLinearSequencerContext.h"
#include "Cluster/Local/ClusterLocalSetThisNodeIpAddressWorker.h"
#include "Cluster/Local/ClusterLocalReportPrimaryNodeChangedWorker.h"
#include "Cluster/Local/ClusterLocalReportRemovedNodeFromClusterWorker.h"
#include "Cluster/Local/ClusterLocalReportReplaceWorker.h"
#include "Cluster/Local/ClusterLocalSetHardwareSynchronizationStateWorker.h"
#include "Cluster/Local/ClusterLocalSetHaRoleWorker.h"
#include "Cluster/Local/ClusterLocalGetObjectIdWorker.h"
#include "Cluster/CentralClusterConfigObjectManager.h"
#include "Cluster/Local/WaveHaNode.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Cluster/Local/ClusterLocalWaveSlotManagementWorker.h"
#include "Cluster/Local/WaveSlotLocalManagedObject.h"
#include "Framework/ObjectModel/WaveManagedObjectToolKit.h"
#include "Framework/CliBlockManagement/CliBlockDetail.h"
#include "Framework/CliBlockManagement/CliBlockManagementToolKit.h"
#include "Framework/CliBlockManagement/CliBlockServiceIndependentMessage.h"
#include "Framework/CliBlockManagement/CliBlockType.h"
#include "Cluster/Local/ClusterLocalSetControllerDetailsMessage.h"
#include "Cluster/Local/ClusterLocalReportToControllerAsClientMessage.h"
#include "ManagementInterface/ClientInterface/WaveClientSynchronousConnection.h"
#include "Framework/Types/Types.h"

namespace WaveNs
{

bool                ClusterLocalObjectManager::m_isInstantiated                                 = false;
UI32                ClusterLocalObjectManager::m_thisNodeClientIndentificationNumber            = 0;
vector<IpVxAddress> ClusterLocalObjectManager::m_pendingIpaddressesToBeAddedToController;
vector<SI32>        ClusterLocalObjectManager::m_pendingPortsToBeAddedToController;
TimerHandle         ClusterLocalObjectManager::m_controllerClusterFormationDampeningTimerHandle = 0;

ClusterLocalObjectManager::ClusterLocalObjectManager ()
    : WaveLocalObjectManager (getWaveServiceName ())
{
    associateWithVirtualWaveObjectManager (CentralClusterConfigObjectManager::getInstance ());

    WaveNode waveNode (this);
    waveNode.setupOrm ();
    addManagedClass (WaveNode::getClassName ());

    WaveSlotLocalManagedObject waveSlot (this);
    waveSlot.setupOrm ();
    addManagedClass (WaveSlotLocalManagedObject::getClassName ());

    WaveHaNode waveHaNode (this);

    waveHaNode.setupOrm ();
    addManagedClass (WaveHaNode::getClassName ());

    m_pClusterLocalSetThisNodeIpAddressWorker = new ClusterLocalSetThisNodeIpAddressWorker (this);

    waveAssert (NULL != m_pClusterLocalSetThisNodeIpAddressWorker, __FILE__, __LINE__);

    m_pClusterLocalPrimaryNodeChangedWorker = new ClusterLocalReportPrimaryNodeChangedWorker(this);

    waveAssert( NULL != m_pClusterLocalPrimaryNodeChangedWorker, __FILE__, __LINE__);

    m_pClusterLocalReportRemovedNodeFromClusterWorker = new ClusterLocalReportRemovedNodeFromClusterWorker(this);

    waveAssert( NULL!= m_pClusterLocalReportRemovedNodeFromClusterWorker, __FILE__, __LINE__);

    m_pClusterLocalReportReplaceWorker = new ClusterLocalReportReplaceWorker(this);

    waveAssert( NULL != m_pClusterLocalPrimaryNodeChangedWorker, __FILE__, __LINE__);

    m_pClusterLocalSetHardwareSynchronizationStateWorker = new ClusterLocalSetHardwareSynchronizationStateWorker (this);

    waveAssert (NULL != m_pClusterLocalSetHardwareSynchronizationStateWorker, __FILE__, __LINE__);


	m_pClusterLocalSetHaRoleWorker = new ClusterLocalSetHaRoleWorker(this);
	waveAssert( NULL!= m_pClusterLocalSetHaRoleWorker, __FILE__, __LINE__);

    m_pClusterLocalWaveSlotManagementWorker = new ClusterLocalWaveSlotManagementWorker (this);
    waveAssert (NULL != m_pClusterLocalWaveSlotManagementWorker, __FILE__, __LINE__);

    m_pClusterLocalGetObjectIdWorker = new ClusterLocalGetObjectIdWorker (this);
    waveAssert (NULL != m_pClusterLocalGetObjectIdWorker, __FILE__, __LINE__);

    m_isInstantiated = true;

    m_thisHardwareSyncState = WAVE_NODE_HARDWARE_SYNCHRONIZATION_STATE_UNINITIALIZED;

    addOperationMap (CLI_BLOCK_SERVICE_INDEPENDENT,                  reinterpret_cast<WaveMessageHandler> (&ClusterLocalObjectManager::cliBlockMessageHandler));
    addServiceIndependentOperationMap (CLI_BLOCK_SERVICE_INDEPENDENT,reinterpret_cast<WaveServiceIndependentMessageHandler> (&ClusterLocalObjectManager::cliBlockMessageStaticHandler));

    addOperationMap (CLUSTER_LOCAL_SET_CONTROLLER_DETAILS_MESSAGE,   reinterpret_cast<WaveMessageHandler> (&ClusterLocalObjectManager::setControllerDetailsMessageHandler));
    addOperationMap (CLUSTER_LOCAL_REPORT_AS_CLIENT_MESSAGE,         reinterpret_cast<WaveMessageHandler> (&ClusterLocalObjectManager::clientReportingToControllerMessageHandler));
}

void  ClusterLocalObjectManager::cliBlockMessageStaticHandler (CliBlockServiceIndependentMessage *pCliBlockServiceIndependentMessage)
{

    bool            operation      = pCliBlockServiceIndependentMessage->getOperation ();
    ResourceId      status         = WAVE_MESSAGE_ERROR;

    // construct block detail

    CliBlockDetail  detail (*pCliBlockServiceIndependentMessage);

    if (true == operation)
    {
        status = CliBlockManagementToolKit::blockCli (detail);
    }
    else
    {
        status = CliBlockManagementToolKit::unblockCli (detail);
    }

    pCliBlockServiceIndependentMessage->setCompletionStatus (status);

}

void ClusterLocalObjectManager::cliBlockMessageHandler (CliBlockServiceIndependentMessage *pCliBlockServiceIndependentMessage)
{

    bool            operation        = pCliBlockServiceIndependentMessage->getOperation ();
    ResourceId      status           = WAVE_MESSAGE_ERROR;

    // construct block detail

    CliBlockDetail  detail (*pCliBlockServiceIndependentMessage);

    if (true == operation)
    {
        status = CliBlockManagementToolKit::blockCli (detail);
    }
    else
    {
        status = CliBlockManagementToolKit::unblockCli (detail);
    }

    pCliBlockServiceIndependentMessage->setCompletionStatus (status);

    reply (pCliBlockServiceIndependentMessage);
}

ClusterLocalObjectManager::~ClusterLocalObjectManager ()
{
    if (NULL != m_pClusterLocalSetThisNodeIpAddressWorker)
    {
        delete m_pClusterLocalSetThisNodeIpAddressWorker;
    }

    if(NULL != m_pClusterLocalPrimaryNodeChangedWorker)
    {
	delete m_pClusterLocalPrimaryNodeChangedWorker;
    }

    if( NULL != m_pClusterLocalReportRemovedNodeFromClusterWorker)
    {
	delete m_pClusterLocalReportRemovedNodeFromClusterWorker;
    }

    if( NULL != m_pClusterLocalReportReplaceWorker)
    {
	delete m_pClusterLocalReportReplaceWorker;
    }

    if (NULL != m_pClusterLocalSetHardwareSynchronizationStateWorker)
    {
        delete m_pClusterLocalSetHardwareSynchronizationStateWorker;
    }

	if( NULL != m_pClusterLocalSetHaRoleWorker)
    {
        delete m_pClusterLocalSetHaRoleWorker;
    }
    if (NULL != m_pClusterLocalWaveSlotManagementWorker)
    {
        delete m_pClusterLocalWaveSlotManagementWorker;
    }
    if (NULL != m_pClusterLocalGetObjectIdWorker)
    {
        delete m_pClusterLocalGetObjectIdWorker;
    }
}

ClusterLocalObjectManager *ClusterLocalObjectManager:: getInstance ()
{
    static ClusterLocalObjectManager *pClusterLocalObjectManager = new ClusterLocalObjectManager ();

    WaveNs::waveAssert (NULL != pClusterLocalObjectManager, __FILE__, __LINE__);

    return (pClusterLocalObjectManager);
}

WaveServiceId ClusterLocalObjectManager:: getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

string ClusterLocalObjectManager::getWaveServiceName ()
{
    return ("Cluster Local");
}

bool ClusterLocalObjectManager::getIsInstantiated ()
{
    return (m_isInstantiated);
}


WaveManagedObject *ClusterLocalObjectManager::createManagedObjectInstance (const string &managedClassName)
{
    WaveManagedObject *pWaveManagedObject = NULL;

    if ((WaveNode::getClassName ()) == managedClassName)
    {
        pWaveManagedObject = new WaveNode (this);
    }
	else if ((WaveHaNode::getClassName ()) == managedClassName)
    {
        pWaveManagedObject = new WaveHaNode (this);
    }
    else if ((WaveSlotLocalManagedObject::getClassName ()) == managedClassName)
    {
        pWaveManagedObject = new WaveSlotLocalManagedObject (this);
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, "ClusterLocalObjectManager::createManagedObjectInstance : Unknown Managed Class Name : " + managedClassName);
        waveAssert (false, __FILE__, __LINE__);
    }

    return (pWaveManagedObject);
}

WaveMessage *ClusterLocalObjectManager::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case CLI_BLOCK_SERVICE_INDEPENDENT :
            pWaveMessage = new CliBlockServiceIndependentMessage ();
            break;

        case CLUSTER_LOCAL_SET_CONTROLLER_DETAILS_MESSAGE:
            pWaveMessage = new ClusterLocalSetControllerDetailsMessage ();
            break;

        case CLUSTER_LOCAL_REPORT_AS_CLIENT_MESSAGE:
            pWaveMessage = new ClusterLocalReportToControllerAsClientMessage ();
            break;

        default :
            pWaveMessage = NULL;
    }

    return (pWaveMessage);
}

void ClusterLocalObjectManager::listenForEvents (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    listenForEvent (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_BROADCAST_ADDITION_OF_NEW_NODES_EVENT, reinterpret_cast<WaveEventHandler> (&ClusterLocalObjectManager::nodeAddedEventHandler));
    listenForEvent (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_BROADCAST_PHASE3_START_EVENT, reinterpret_cast<WaveEventHandler> (&ClusterLocalObjectManager::phase3StartEventHandler));
    listenForEvent (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_BROADCAST_PHASE3_COMPLETE_EVENT, reinterpret_cast<WaveEventHandler> (&ClusterLocalObjectManager::phase3CompleteEventHandler));

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void ClusterLocalObjectManager::install (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    // During installation persist WaveNode corresponding to this node.
    WaveBootReason bootReason = pWaveAsynchronousContextForBootPhases->getBootReason ();
    ResourceId status = WAVE_MESSAGE_ERROR;

    if (WAVE_BOOT_PERSISTENT_WITH_DEFAULT_BOOT != bootReason)
    {
        startTransaction ();

        WaveNode *pWaveNode = new WaveNode (this, FrameworkToolKit::getThisLocationId (), FrameworkToolKit::getThisLocationIpAddress (), FrameworkToolKit::getThisLocationPort ());

        waveAssert (NULL != pWaveNode, __FILE__, __LINE__);

        setThisWaveNodeObjectId (pWaveNode->getObjectId ());

        pWaveNode->setThisNodeStartMode (FrameworkToolKit::getStartMode ());
//        WaveHaNode *pWaveHaNode = new WaveHaNode (this, WAVE_HA_NODE_STANDBY_UNCONFIRMED);
//        pWaveNode->addWaveHaNode (pWaveHaNode->getObjectId ());

        status = commitTransaction ();

        if (FRAMEWORK_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "ClusterLocalObjectManager::initialize : Could not install ClusterLocalObjectManager.");
//            waveAssert (false, __FILE__, __LINE__);
        }
        else
        {
            status = WAVE_MESSAGE_SUCCESS;
        }

        delete pWaveNode;
//        delete pWaveHaNode;
    }
    else if (WAVE_BOOT_PERSISTENT_WITH_DEFAULT_BOOT == bootReason)
    {
        // During this install phase and persistent default boot reason the Local MO's will need this WaveNode ObjectId when they are installed.
        // So this query and set of in memory WaveNode ObjectId is necessary during this time.  Boot phase of this Object Manager also does the
        // does the same, but is not early enough for Local MO's that get installed during install phase.  Boot phase code will be left as is
        // for now.

        LocationId                                  thisLocationId          = FrameworkToolKit::getThisLocationId ();
        WaveNode                                   *pThisWaveNode           = NULL;
        WaveManagedObjectSynchronousQueryContext    synchronousQueryContext (WaveNode::getClassName ());

        // Query for the WaveNode row corresponding to this location
        synchronousQueryContext.addAndAttribute (new AttributeLocationId (thisLocationId, "locationId"));

        vector<WaveManagedObject *> *pWaveManagedObjects = querySynchronously (&synchronousQueryContext);

        // Ensure we have exactly one WaveNode result
        waveAssert (NULL != pWaveManagedObjects, __FILE__, __LINE__);
        waveAssert (1 == (pWaveManagedObjects->size ()), __FILE__, __LINE__);

        pThisWaveNode = dynamic_cast<WaveNode *> ((*pWaveManagedObjects)[0]);

        // Clean up query results
        pWaveManagedObjects->clear ();
        delete pWaveManagedObjects;

        // Ensure our cast succeeded
        waveAssert (NULL != pThisWaveNode, __FILE__, __LINE__);

        trace (TRACE_LEVEL_DEBUG, string ("ClusterLocalObjectManager::install : Wave Local Node Details :"));
        trace (TRACE_LEVEL_DEBUG, string ("ClusterLocalObjectManager::install :     Object ID   : ") + (pThisWaveNode->getObjectId ()).toString ());

        // Update the in memory WaveNode ObjectId
        setThisWaveNodeObjectId (pThisWaveNode->getObjectId ());

        // Clean up the WaveNode
        delete pThisWaveNode;

        status = WAVE_MESSAGE_SUCCESS;
    }

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (status);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void ClusterLocalObjectManager::boot (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    trace (TRACE_LEVEL_DEBUG, "ClusterLocalObjectManager::boot : Entering ...");

    //WaveBootReason                            bootReason             = pWaveAsynchronousContextForBootPhases->getBootReason ();
    LocationId                                thisLocationId         = FrameworkToolKit::getThisLocationId ();
    WaveNode                                 *pThisWaveNode          = NULL;
    WaveManagedObjectSynchronousQueryContext synchronousQueryContext   (WaveNode::getClassName ());

    synchronousQueryContext.addAndAttribute (new AttributeLocationId (thisLocationId, "locationId"));

    vector<WaveManagedObject *> *pWaveManagedObjects = querySynchronously (&synchronousQueryContext);

    waveAssert (NULL != pWaveManagedObjects, __FILE__, __LINE__);

    waveAssert (1 == (pWaveManagedObjects->size ()), __FILE__, __LINE__);

    pThisWaveNode = dynamic_cast<WaveNode *> ((*pWaveManagedObjects)[0]);

    pWaveManagedObjects->clear ();

    delete pWaveManagedObjects;

    waveAssert (NULL != pThisWaveNode, __FILE__, __LINE__);

    trace (TRACE_LEVEL_INFO, string ("ClusterLocalObjectManager::boot : Wave Local Node Details :"));
    trace (TRACE_LEVEL_INFO, string ("ClusterLocalObjectManager::boot :     Location Id : ") + pThisWaveNode->getLocationId ());
    trace (TRACE_LEVEL_INFO, string ("ClusterLocalObjectManager::boot :     IP Address  : ") + pThisWaveNode->getIpAddress ());
    trace (TRACE_LEVEL_INFO, string ("ClusterLocalObjectManager::boot :     Port        : ") + pThisWaveNode->getPort ());
    trace (TRACE_LEVEL_INFO, string ("ClusterLocalObjectManager::boot :     Object ID   : ") + (pThisWaveNode->getObjectId ()).toString ());

    setThisWaveNodeObjectId (pThisWaveNode->getObjectId ());

    // The hardware sync state tracks if the hardware programming (postboot)
    // is in sync with the configuration in the database.

    pThisWaveNode->setHardwareSynchronizationState (WAVE_NODE_HARDWARE_SYNCHRONIZATION_STATE_UNINITIALIZED);

    delete pThisWaveNode;

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void ClusterLocalObjectManager::shutdown (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases)
{
    WaveNode *pThisWaveNode = getThisWaveNodeManagedObject();

    if (NULL == pThisWaveNode)
    {
        pWaveAsynchronousContextForShutDownPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
        pWaveAsynchronousContextForShutDownPhases->callback ();
        return;
    }

    ResourceId currentLocalHwSyncState = pThisWaveNode->getHardwareSynchronizationState ();

    trace (TRACE_LEVEL_INFO, string("ClusterLocalObjectManager::shutdown : WaveNode hardware synchronization state: ") + FrameworkToolKit::localize (currentLocalHwSyncState));

    m_thisHardwareSyncState = pThisWaveNode->getHardwareSynchronizationState ();

    delete pThisWaveNode;

    pWaveAsynchronousContextForShutDownPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForShutDownPhases->callback ();
}

void ClusterLocalObjectManager::backendSyncUp (WaveAsynchronousContext *pWaveAsynchronousContext)
{
    trace (TRACE_LEVEL_DEVEL, string("ClusterLocalObjectManager::backendSyncUp : Entering..."));

    ResourceId  backendSyncUpStatus = WAVE_MESSAGE_ERROR;
    WaveNode *pThisWaveNode = getThisWaveNodeManagedObject();

    if (NULL == pThisWaveNode)
    {
        waveAssert (false, __FILE__, __LINE__);
    }

    ResourceId currentLocalHwSyncState = pThisWaveNode->getHardwareSynchronizationState ();

    trace (TRACE_LEVEL_INFO, string("ClusterLocalObjectManager::backendSyncUp : Queried WaveNode hardware synchronization state: ") + FrameworkToolKit::localize (currentLocalHwSyncState));

    startTransaction ();

    updateWaveManagedObject(pThisWaveNode);
    pThisWaveNode->setHardwareSynchronizationState (m_thisHardwareSyncState);

    trace (TRACE_LEVEL_INFO, string("ClusterLocalObjectManager::backendSyncUp : Restoring locally cached WaveNode hardware synchronization state: ") + FrameworkToolKit::localize (m_thisHardwareSyncState));

    ResourceId commitStatus = commitTransaction ();

    if (FRAMEWORK_SUCCESS == commitStatus)
    {
        backendSyncUpStatus = WAVE_MESSAGE_SUCCESS;
    }
    else
    {
        backendSyncUpStatus = WAVE_MESSAGE_ERROR;
    }

    delete pThisWaveNode;

    pWaveAsynchronousContext->setCompletionStatus (backendSyncUpStatus);
    pWaveAsynchronousContext->callback ();
}

void ClusterLocalObjectManager::setThisWaveNodeObjectId (const ObjectId &thisWaveNodeObjectId)
{
    m_thisWaveNodeObjectIdMutex.lock ();

    m_thisWaveNodeObjectId = thisWaveNodeObjectId;

    m_thisWaveNodeObjectIdMutex.unlock ();
}

ObjectId ClusterLocalObjectManager::getThisWaveNodeObjectId ()
{
    ObjectId tempObjectId;

    m_thisWaveNodeObjectIdMutex.lock ();

    tempObjectId = m_thisWaveNodeObjectId;

    m_thisWaveNodeObjectIdMutex.unlock ();

    return (tempObjectId);
}

WaveNode *ClusterLocalObjectManager::getThisWaveNodeManagedObject()
{
    LocationId                                thisLocationId         = FrameworkToolKit::getThisLocationId ();
    WaveNode                                 *pThisWaveNode          = NULL;
    WaveManagedObjectSynchronousQueryContext synchronousQueryContext   (WaveNode::getClassName ());

    synchronousQueryContext.addAndAttribute (new AttributeLocationId (thisLocationId, "locationId"));

    vector<WaveManagedObject *> *pWaveManagedObjects = querySynchronously (&synchronousQueryContext);

    waveAssert (NULL != pWaveManagedObjects, __FILE__, __LINE__);

    if (1 != pWaveManagedObjects->size ())
    {
        trace (TRACE_LEVEL_ERROR, string ("This node location Id is ") + thisLocationId + string (" and number of wave node of for this location is not valid. number of wavenode found in DB for this location is ") + pWaveManagedObjects->size ());
        return NULL;
    }

    pThisWaveNode = dynamic_cast<WaveNode *> ((*pWaveManagedObjects)[0]);

    pWaveManagedObjects->clear ();

    delete pWaveManagedObjects;

    waveAssert (NULL != pThisWaveNode, __FILE__, __LINE__);

    return pThisWaveNode;
}

void ClusterLocalObjectManager::nodeAddedEventHandler (const WaveNewNodesAddedEvent* &pEvent)
{
    trace (TRACE_LEVEL_DEBUG, "ClusterLocalObjectManager::nodeAddedEventHandler : Entering ...");

    WaveNode    *pThisWaveNode = getThisWaveNodeManagedObject();

    if (NULL == pThisWaveNode)
    {
        waveAssert (false, __FILE__, __LINE__);
    }


    ResourceId specificStatus = pThisWaveNode->getSpecificStatus();

    if( WAVE_MANAGED_OBJECT_SPECIFIC_STATUS_SECONDARY_ADD_PHASE2_STARTED == specificStatus || WAVE_MANAGED_OBJECT_SPECIFIC_STATUS_SECONDARY_REJOIN_PHASE2_STARTED == specificStatus)
    {
        ResourceId status = WAVE_MESSAGE_SUCCESS;

        startTransaction();
        updateWaveManagedObject(pThisWaveNode);
        if ( WAVE_MANAGED_OBJECT_SPECIFIC_STATUS_SECONDARY_ADD_PHASE2_STARTED == specificStatus )
        {
            //This node is being added to the cluster and phase2 is complete
            pThisWaveNode->setSpecificStatus( WAVE_MANAGED_OBJECT_SPECIFIC_STATUS_SECONDARY_ADD_PHASE2_COMPLETED );
            trace (TRACE_LEVEL_INFO, "ClusterLocalObjectManager::nodeAddedEventHandler: WaveNode specific status of this node has been set to --> Secondary Add Phase2 Completed ");
        }
        else
        {
            //  VCS_FABRIC_LOCAL_SPECIFIC_STATUS_SECONDARY_REJOIN_PHASE2_STARTED == specificStatus
           //   This node is being rejoined to the cluster and phase2 is complete
            pThisWaveNode->setSpecificStatus( WAVE_MANAGED_OBJECT_SPECIFIC_STATUS_SECONDARY_REJOIN_PHASE2_COMPLETED );
            trace (TRACE_LEVEL_INFO, "ClusterLocalObjectManager::nodeAddedEventHandler: WaveNode specific status of this node has been set to --> Secondary Rejoin Phase2 Completed ");
        }
        status = commitTransaction ();

        if (FRAMEWORK_SUCCESS == status)
        {
            trace (TRACE_LEVEL_DEBUG, "ClusterLocalObjectManager::nodeAddedEventHandler: WaveNode specific status has been committed to DB");
            status = WAVE_MESSAGE_SUCCESS;
        }
        else
        {
            trace (TRACE_LEVEL_FATAL, "ClusterLocalObjectManager::nodeAddedEventHandler: WaveNode specific status commit to DB Failed");
//            waveAssert (false, __FILE__, __LINE__);
        }
    }
    delete pThisWaveNode;
    reply (reinterpret_cast<const WaveEvent *&>(pEvent));
}

void ClusterLocalObjectManager::phase3StartEventHandler( const ClusterPhase3StartEvent* &pEvent )
{
    trace (TRACE_LEVEL_DEBUG, "ClusterLocalObjectManager::phase3StartEventHandler : Entering ...");

    WaveNode    *pThisWaveNode = getThisWaveNodeManagedObject();

    if (NULL == pThisWaveNode)
    {
        waveAssert (false, __FILE__, __LINE__);
    }

    ResourceId specificStatus = pThisWaveNode->getSpecificStatus();

    if( WAVE_MANAGED_OBJECT_SPECIFIC_STATUS_SECONDARY_ADD_PHASE2_COMPLETED == specificStatus || WAVE_MANAGED_OBJECT_SPECIFIC_STATUS_SECONDARY_REJOIN_PHASE2_STARTED == specificStatus || WAVE_MANAGED_OBJECT_SPECIFIC_STATUS_SECONDARY_REJOIN_PHASE2_COMPLETED == specificStatus)
    {
        ResourceId status = WAVE_MESSAGE_SUCCESS;

        startTransaction();
        updateWaveManagedObject(pThisWaveNode);
        if ( WAVE_MANAGED_OBJECT_SPECIFIC_STATUS_SECONDARY_ADD_PHASE2_COMPLETED == specificStatus )
        {
            //This node is being added to the cluster and phase3 has started
            pThisWaveNode->setSpecificStatus( WAVE_MANAGED_OBJECT_SPECIFIC_STATUS_SECONDARY_ADD_PHASE3_STARTED );
            trace (TRACE_LEVEL_INFO, "ClusterLocalObjectManager::phase3StartEventHandler: WaveNode specific status of this node has been set to --> Secondary Add Phase3 Started ");
        }
        else
        {
             // VCS_FABRIC_LOCAL_SPECIFIC_STATUS_SECONDARY_REJOIN_PHASE2_COMPLETED == specificStatus
            //  VCS_FABRIC_LOCAL_SPECIFIC_STATUS_SECONDARY_REJOIN_PHASE2_STARTED == specificStatus
           //   This node is being rejoined to the cluster and phase3 has started

            pThisWaveNode->setSpecificStatus( WAVE_MANAGED_OBJECT_SPECIFIC_STATUS_SECONDARY_REJOIN_PHASE3_STARTED );
            trace (TRACE_LEVEL_INFO, "ClusterLocalObjectManager::phase3StartEventHandler: WaveNode specific status of this node has been set to --> Secondary Rejoin Phase3 Started");
        }
        status = commitTransaction ();

        if (FRAMEWORK_SUCCESS == status)
        {
            trace (TRACE_LEVEL_DEBUG, "ClusterLocalObjectManager::phase3StartEventHandler: WaveNode specific status has been committed to DB");
            status = WAVE_MESSAGE_SUCCESS;
        }
        else
        {
            trace (TRACE_LEVEL_FATAL, "ClusterLocalObjectManager::phase3StartEventHandler: WaveNode specific status commit to DB Failed");
//            waveAssert (false, __FILE__, __LINE__);
        }
    }
    delete pThisWaveNode;
    reply (reinterpret_cast<const WaveEvent *&> (pEvent));
}

void ClusterLocalObjectManager::phase3CompleteEventHandler( const ClusterPhase3CompleteEvent* &pEvent )
{
    trace (TRACE_LEVEL_DEBUG, "ClusterLocalObjectManager::phase3CompleteEventHandler : Entering ...");
    WaveNode    *pThisWaveNode = getThisWaveNodeManagedObject();

    if (NULL == pThisWaveNode)
    {
        waveAssert (false, __FILE__, __LINE__);
    }

    ResourceId specificStatus = pThisWaveNode->getSpecificStatus();

    if( WAVE_MANAGED_OBJECT_SPECIFIC_STATUS_SECONDARY_ADD_PHASE3_STARTED == specificStatus || WAVE_MANAGED_OBJECT_SPECIFIC_STATUS_SECONDARY_REJOIN_PHASE3_STARTED == specificStatus)
    {
        ResourceId status = WAVE_MESSAGE_SUCCESS;

        startTransaction();
        updateWaveManagedObject(pThisWaveNode);
        //This node is being added to the cluster and phase3 is complete
        pThisWaveNode->setSpecificStatus( WAVE_MANAGED_OBJECT_SPECIFIC_STATUS_SECONDARY_CONNECTED_TO_CLUSTER );

        trace (TRACE_LEVEL_INFO, "ClusterLocalObjectManager::phase3CompleteEventHandler: WaveNode specific status of this node has been set to --> Secondary Connected To Cluster ");
        status = commitTransaction ();

        if (FRAMEWORK_SUCCESS == status)
        {
            trace (TRACE_LEVEL_DEBUG, "ClusterLocalObjectManager::phase3CompleteEventHandler: WaveNode specific status has been committed to DB");
            status = WAVE_MESSAGE_SUCCESS;
        }
        else
        {
			/* defect: 347440
		 	 * No Assert required, secondaryFailover will complete the transaction
			 */
            tracePrintf (TRACE_LEVEL_DEBUG, "ClusterLocalObjectManager::phase3CompleteEventHandler: WaveNode specific status commit to DB Failed: %s",FrameworkToolKit::localize(status).c_str());
        }
    }
    delete pThisWaveNode;
    reply (reinterpret_cast<const WaveEvent *&> (pEvent));
}

void ClusterLocalObjectManager::setThisWaveHaNodeRole (const WaveHaNodeRole &thisWaveHaNodeRole)
{
    m_thisWaveHaNodeRoleMutex.lock ();

    m_thisWaveHaNodeRole = thisWaveHaNodeRole;

    m_thisWaveHaNodeRoleMutex.unlock ();
}

WaveHaNodeRole ClusterLocalObjectManager::getThisWaveHaNodeRole ()
{
    WaveHaNodeRole tempHaRole;

    m_thisWaveHaNodeRoleMutex.lock ();

    tempHaRole = m_thisWaveHaNodeRole;

    m_thisWaveHaNodeRoleMutex.unlock ();

    return (tempHaRole);
}

void ClusterLocalObjectManager::dbInconsistencyCheck (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    trace (TRACE_LEVEL_INFO, "ClusterLocalObjectManager::dbInconsistencyCheck : Entering ...");

    ResourceId  status = WAVE_MESSAGE_SUCCESS;
    WaveBootReason bootReason = pWaveAsynchronousContextForBootPhases->getBootReason ();
    trace (TRACE_LEVEL_INFO, string ("ClusterLocalObjectManager::dbInconsistencyCheck : BootReason : ") + FrameworkToolKit::localize (bootReason));

    UI32                                      i                      = 0;
    LocationId                                thisLocationId         = FrameworkToolKit::getThisLocationId ();
    WaveManagedObjectSynchronousQueryContext  synchronousQueryContext   (WaveNode::getClassName ());

    synchronousQueryContext.addAndAttribute (new AttributeLocationId (thisLocationId, "locationId"));

    vector<WaveManagedObject *> *pResults = querySynchronously (&synchronousQueryContext);

    waveAssert (NULL != pResults, __FILE__, __LINE__);

    if (0 == pResults->size ())
    {
        trace (TRACE_LEVEL_ERROR, string ("ClusterLocalObjectManager::dbInconsistencyCheck : Zero entries found in WaveNode for this location."));
        status = WAVE_MESSAGE_ERROR;
    }
    else if (1 == pResults->size ())
    {
        WaveNode *pThisWaveNode = NULL;
        pThisWaveNode = dynamic_cast<WaveNode *> ((*pResults)[0]);

        waveAssert (NULL != pThisWaveNode, __FILE__, __LINE__);

        setThisWaveNodeObjectId (pThisWaveNode->getObjectId ());

        status = WAVE_MESSAGE_SUCCESS;
    }
    else if (2 == pResults->size ())
    {
        ObjectId object1 = ((*pResults)[0])->getObjectId ();
        ObjectId object2 = ((*pResults)[1])->getObjectId ();
        if (object1 == object2)
        {
            trace (TRACE_LEVEL_ERROR, string ("ClusterLocalObjectManager::dbInconsistencyCheck : Duplicate entries found in WaveNode. The ObjectIds are " + object1.toString () + " and " + object2.toString ()));
            status = WAVE_MESSAGE_ERROR;
        }
        else
        {
            trace (TRACE_LEVEL_ERROR, string ("ClusterLocalObjectManager::dbInconsistencyCheck : Two entries found in WaveNode."));
            waveAssert (false, __FILE__, __LINE__);
        }

    }
    else if (2 < pResults->size ())
    {
        trace (TRACE_LEVEL_ERROR, string ("ClusterLocalObjectManager::dbInconsistencyCheck : Multiple entries found in WaveNode"));
        waveAssert (false, __FILE__, __LINE__);
    }
    for (i = 0; i < pResults->size (); i++)
    {
        delete (*pResults)[i];
    }

    pResults->clear ();
    delete pResults;

/*
    else if (1 < pWaveManagedObjects->size ())
    {
        WaveNode *pWaveNode1 = NULL;
        WaveNode *pWaveNode2 = NULL;

        pWaveNode1 = dynamic_cast<WaveNode *> ((*pWaveManagedObjects)[0]);
        pWaveNode2 = dynamic_cast<WaveNode *> ((*pWaveManagedObjects)[1]);

        waveAssert (NULL != pWaveNode1, __FILE__, __LINE__);
        waveAssert (NULL != pWaveNode2, __FILE__, __LINE__);

        ObjectId object1 = pWaveNode1->getObjectId ();
        ObjectId object2 = pWaveNode2->getObjectId ();

        trace (TRACE_LEVEL_ERROR, string ("ClusterLocalObjectManager::dbInconsistencyCheck : Duplicate entries found in WaveNode for this location. The ObjectIds are ") + object1.toString () + " and " + object2.toString ());
        status = WAVE_MESSAGE_ERROR;

        delete pWaveNode1;
        delete pWaveNode2;
    }

    pWaveManagedObjects->clear ();
    delete pWaveManagedObjects;
*/

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (status);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void ClusterLocalObjectManager::haboot (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    trace (TRACE_LEVEL_DEVEL, "ClusterLocalObjectManager::haboot : Entering ...");

    LocationId                                thisLocationId         = FrameworkToolKit::getThisLocationId ();
    WaveNode                                 *pThisWaveNode          = NULL;
    WaveManagedObjectSynchronousQueryContext  synchronousQueryContext   (WaveNode::getClassName ());

    synchronousQueryContext.addAndAttribute (new AttributeLocationId (thisLocationId, "locationId"));

    vector<WaveManagedObject *> *pWaveManagedObjects = querySynchronously (&synchronousQueryContext);

    waveAssert (NULL != pWaveManagedObjects, __FILE__, __LINE__);

    waveAssert (1 == (pWaveManagedObjects->size ()), __FILE__, __LINE__);

    pThisWaveNode = dynamic_cast<WaveNode *> ((*pWaveManagedObjects)[0]);

    pWaveManagedObjects->clear ();

    delete pWaveManagedObjects;

    waveAssert (NULL != pThisWaveNode, __FILE__, __LINE__);

    trace (TRACE_LEVEL_INFO, string ("ClusterLocalObjectManager::haboot : Wave Local Node Details :"));
    trace (TRACE_LEVEL_INFO, string ("ClusterLocalObjectManager::haboot :     Location Id : ") + pThisWaveNode->getLocationId ());
    trace (TRACE_LEVEL_INFO, string ("ClusterLocalObjectManager::haboot :     IP Address  : ") + pThisWaveNode->getIpAddress ());
    trace (TRACE_LEVEL_INFO, string ("ClusterLocalObjectManager::haboot :     Port        : ") + pThisWaveNode->getPort ());
    trace (TRACE_LEVEL_INFO, string ("ClusterLocalObjectManager::haboot :     Object ID   : ") + (pThisWaveNode->getObjectId ()).toString ());

    setThisWaveNodeObjectId (pThisWaveNode->getObjectId ());

    // The hardware sync state tracks if the hardware programming (postboot)
    // is in sync with the configuration in the database.

    pThisWaveNode->setHardwareSynchronizationState (WAVE_NODE_HARDWARE_SYNCHRONIZATION_STATE_UNINITIALIZED);

    delete pThisWaveNode;

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

ResourceId ClusterLocalObjectManager::blockCli (const ResourceId &reason, const bool &clusterWide)
{
    trace (TRACE_LEVEL_FATAL, string ("ClusterLocalObjectManager::blockCli : this service cannot block cli "));
    waveAssert (false, __FILE__, __LINE__);
    return WAVE_MESSAGE_ERROR;
}

ResourceId ClusterLocalObjectManager::unblockCli (const ResourceId &reason, const bool &clusterWide)
{
    trace (TRACE_LEVEL_FATAL, string ("ClusterLocalObjectManager::blockCli : this service cannot block cli "));
    waveAssert (false, __FILE__, __LINE__);
    return WAVE_MESSAGE_ERROR;
}

void ClusterLocalObjectManager::setControllerDetailsMessageHandler (ClusterLocalSetControllerDetailsMessage *pClusterLocalSetControllerDetailsMessage)
{
    m_thisWaveNodeControllerIpAddress = pClusterLocalSetControllerDetailsMessage->getControllerIpAddress ();
    m_thisWaveNodeControllerPort      = pClusterLocalSetControllerDetailsMessage->getControllerPort ();

    trace (TRACE_LEVEL_INFO, string ("ClusterLocalObjectManager::setControllerDetailsMessageHandler Controller IpAddress is :") + m_thisWaveNodeControllerIpAddress.toString () + string (" Controller Port ") + m_thisWaveNodeControllerPort);

    pClusterLocalSetControllerDetailsMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);

    reply (pClusterLocalSetControllerDetailsMessage);

    string thisNodeIpAddress = FrameworkToolKit::getThisLocationIpAddress ();
    SI32   thisNodePort      = FrameworkToolKit::getThisLocationPort ();
    string clientName        = thisNodeIpAddress + ":" + thisNodePort + "." + m_thisNodeClientIndentificationNumber++;

    // After receiving the controller sent the information to controller to report this client.

    WaveClientSynchronousConnection *pWaveClientSynchronousConnection = new WaveClientSynchronousConnection (clientName, m_thisWaveNodeControllerIpAddress.toString (), m_thisWaveNodeControllerPort);

    ResourceId connectionStatus = pWaveClientSynchronousConnection->connect ();

    if (WAVE_MGMT_CLIENT_INTF_CONNECTION_ESTABLISHED_TO_SERVER != connectionStatus)
    {
        delete pWaveClientSynchronousConnection;
    }
    else
    {
        ClusterLocalReportToControllerAsClientMessage *pClusterLocalReportToControllerAsClientMessage = new ClusterLocalReportToControllerAsClientMessage ();

        IpVxAddress clientIpAddress (thisNodeIpAddress);

        pClusterLocalReportToControllerAsClientMessage->setControllerIpAddress (m_thisWaveNodeControllerIpAddress);
        pClusterLocalReportToControllerAsClientMessage->setControllerPort      (m_thisWaveNodeControllerPort);

        pClusterLocalReportToControllerAsClientMessage->setControllerClientIpAddress     (clientIpAddress);
        pClusterLocalReportToControllerAsClientMessage->setControllerClientPort          (thisNodePort);


        ResourceId status = pWaveClientSynchronousConnection->sendToWaveServer (pClusterLocalReportToControllerAsClientMessage, reinterpret_cast<WaveMessageResponseHandler> (&ClusterLocalObjectManager::clusterLocalReportToControllerAsClientCallback), this, pWaveClientSynchronousConnection);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            delete pClusterLocalReportToControllerAsClientMessage;
        }

    }
}

void ClusterLocalObjectManager::clusterLocalReportToControllerAsClientCallback (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, void *pContext)
{
    ClusterLocalReportToControllerAsClientMessage *pClusterLocalReportToControllerAsClientMessage = dynamic_cast<ClusterLocalReportToControllerAsClientMessage *> (pWaveMessage);

    WaveClientSynchronousConnection *pWaveClientSynchronousConnection = reinterpret_cast<WaveClientSynchronousConnection *> (pContext);

    waveAssert (NULL != pClusterLocalReportToControllerAsClientMessage, __FILE__, __LINE__);
    waveAssert (NULL != pWaveClientSynchronousConnection, __FILE__, __LINE__);

    pWaveClientSynchronousConnection->close ();

    delete pClusterLocalReportToControllerAsClientMessage;
    delete pWaveClientSynchronousConnection;
}

void ClusterLocalObjectManager::clientReportingToControllerMessageHandler (ClusterLocalReportToControllerAsClientMessage *pClusterLocalReportToControllerAsClientMessage)
{
    trace (TRACE_LEVEL_INFO, "Received Message for client");

    IpVxAddress clientIpAddress = pClusterLocalReportToControllerAsClientMessage->getControllerClientIpAddress ();
    SI32        clientPort      = pClusterLocalReportToControllerAsClientMessage->getControllerClientPort ();

    ResourceId  status           = FRAMEWORK_SUCCESS;

    pClusterLocalReportToControllerAsClientMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    reply (pClusterLocalReportToControllerAsClientMessage);

    //A client has reported. Make sure you this node is in Controller Mode.
    //If this is in controller mode, send a message to cluster global to add this node appropriately

    if (WAVE_NODE_START_AS_CONTROLLER == FrameworkToolKit::getStartMode ())
    {
        m_pendingIpaddressesToBeAddedToController.push_back (clientIpAddress);
        m_pendingPortsToBeAddedToController.push_back       (clientPort);

        if (0 != m_controllerClusterFormationDampeningTimerHandle)
        {
            deleteTimer (m_controllerClusterFormationDampeningTimerHandle);
        }

        status = startTimer (m_controllerClusterFormationDampeningTimerHandle, 30000, reinterpret_cast<WaveTimerExpirationHandler> (&ClusterLocalObjectManager::controllerClusterFormationDampeningTimerCallback), NULL);

        if (FRAMEWORK_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "ClusterLocalObjectManager::clientReportingToControllerMessageHandler : Failed to start dampening timer on controller : " + FrameworkToolKit::localize (status));
        }
    }
    else
    {
        trace (TRACE_LEVEL_WARN, "ClusterLocalObjectManager::clientReportingToControllerMessageHandler : Ignoring Client Request as we are not in controller mode.");
    }
}

void ClusterLocalObjectManager::controllerClusterFormationDampeningTimerCallback (TimerHandle &timerHandle, void *pContext)
{
    m_controllerClusterFormationDampeningTimerHandle = 0;

    //A client has reported. Make sure you this node is in Controller Mode.
    //If this is in controller mode, send a message to cluster global to add this node appropriately

    if (WAVE_NODE_START_AS_CONTROLLER == FrameworkToolKit::getStartMode ())
    {
        UI32 numberOfPendingIpAddresses = m_pendingIpaddressesToBeAddedToController.size ();
        UI32 i                          = 0;

        vector <string> ipAddresses;
        vector <SI32>   ports;

        for (i = 0; i < numberOfPendingIpAddresses; i++)
        {
            ipAddresses.push_back (m_pendingIpaddressesToBeAddedToController[i].toString ());
        }

        ports = m_pendingPortsToBeAddedToController;

        m_pendingIpaddressesToBeAddedToController.clear ();
        m_pendingPortsToBeAddedToController.clear ();

        if (0 != numberOfPendingIpAddresses)
        {
            // Query DB is cluster exists or not

            UI32 numberOfWaveCluster;

            ResourceId status = querySynchronouslyForCount ("WaveCluster", numberOfWaveCluster, "wavecurrent");

            waveAssert (WAVE_MESSAGE_SUCCESS == status, __FILE__, __LINE__);

            if (0 == numberOfWaveCluster)
            {
                ClusterObjectManagerCreateClusterMessage *pClusterObjectManagerCreateClusterMessage = new  ClusterObjectManagerCreateClusterMessage (ipAddresses, ports);

                status = sendOneWay (pClusterObjectManagerCreateClusterMessage);

                waveAssert (WAVE_MESSAGE_SUCCESS == status, __FILE__, __LINE__);
            }
            else if (1 == numberOfWaveCluster)
            {
                ClusterObjectManagerAddNodeMessage *pClusterObjectManagerAddNodeMessage = new ClusterObjectManagerAddNodeMessage (ipAddresses, ports);

                status = sendOneWay (pClusterObjectManagerAddNodeMessage);

                waveAssert (WAVE_MESSAGE_SUCCESS == status, __FILE__, __LINE__);
            }
            else
            {
                waveAssert (false, __FILE__, __LINE__);
            }
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "ClusterLocalObjectManager::clientReportingToControllerMessageHandler : Ignoring Dampening Timer as there are no pending entries");
        }
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, "ClusterLocalObjectManager::clientReportingToControllerMessageHandler : Dampening Timer received when we are not in controller mode.  How did we even get here?");

        waveAssert (false, __FILE__, __LINE__);
    }
}

}
