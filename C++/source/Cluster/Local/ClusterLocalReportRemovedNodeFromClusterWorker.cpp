/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Aashish Akhouri                                              *
 ***************************************************************************/

#include "Cluster/Local/ClusterLocalReportRemovedNodeFromClusterMessage.h"
#include "Cluster/Local/ClusterLocalReportRemovedNodeFromClusterWorker.h"
#include "Cluster/Local/ClusterLocalObjectManager.h"
#include "Cluster/Local/ClusterLocalTypes.h"
#include  "Framework/Types/Types.h"
#include "Framework/Utils/PrismLinearSequencerContext.h"
#include "Framework/ObjectModel/WaveManagedObjectToolKit.h"
#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"
#include "Cluster/Local/WaveNode.h"
#include "Cluster/PrismCluster.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContext.h"
#include "Cluster/Local/HeartBeat/HeartBeatMessages.h"

namespace WaveNs
{

/// Name
/// ClusterLocalReportRemovedNodeFromClusterWorker
/// Description
/// Constructor:Registers the handler to handle the node removal message
/// from the Framework
/// Input
/// ClusterLocalObjectManager *: Registered with the WaveElement
/// Output
/// None
/// Return
/// None

ClusterLocalReportRemovedNodeFromClusterWorker::ClusterLocalReportRemovedNodeFromClusterWorker (ClusterLocalObjectManager *pClusterLocalObjectManager)
    : WaveWorker (pClusterLocalObjectManager)
{
    addOperationMap (CLUSTER_LOCAL_REPORT_NODE_REMOVED_FROM_CLUSTER, reinterpret_cast<WaveMessageHandler> (&ClusterLocalReportRemovedNodeFromClusterWorker::nodeRemovedMessageHandler));
}

/// Name
/// ClusterLocalReportRemovedNodeFromClusterWorker
/// Description
/// Destructor
/// Input
/// None
/// Output
/// None
/// Return
/// None

ClusterLocalReportRemovedNodeFromClusterWorker::~ClusterLocalReportRemovedNodeFromClusterWorker ()
{
}

/// Name
/// nodeRemovedMessageHandler
/// Description
/// On receiving the message from the framework it constructs the steps of processing
/// and lodges them in a context.Then it kick starts the processing of the remove
/// Input
/// ClusterLocalReportRemovedNodeFromClusterMessage *: pointer to message to received from f/w
/// Output
/// None
/// Return
/// None

void ClusterLocalReportRemovedNodeFromClusterWorker::nodeRemovedMessageHandler(ClusterLocalReportRemovedNodeFromClusterMessage *pClusterLocalReportRemovedNodeFromClusterMessage)
{
    PrismLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<PrismLinearSequencerStep> (&ClusterLocalReportRemovedNodeFromClusterWorker::updateWaveNodeManagedObjectStep),     
        reinterpret_cast<PrismLinearSequencerStep> (&ClusterLocalReportRemovedNodeFromClusterWorker::prismLinearSequencerSucceededStep),
        reinterpret_cast<PrismLinearSequencerStep> (&ClusterLocalReportRemovedNodeFromClusterWorker::prismLinearSequencerFailedStep)
    };
    PrismLinearSequencerContext *pPrismLinearSequencerContext = new PrismLinearSequencerContext (pClusterLocalReportRemovedNodeFromClusterMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0])); 
   
    pPrismLinearSequencerContext->holdAll ();
    pPrismLinearSequencerContext->start ();
}


/// Name
/// updateWaveNodeManagedObjectStep
/// Description
/// In this step the local WaveNode MO's node status is updated 
/// to STAND-ALONE the wavenode is committed back to the DB
/// Input
/// PrismLinearSequencerContext *
/// Output
/// None
/// Return
/// None

void ClusterLocalReportRemovedNodeFromClusterWorker::updateWaveNodeManagedObjectStep(PrismLinearSequencerContext *pPrismLinearSequencerContext)
{

    trace (TRACE_LEVEL_DEVEL, "ClusterLocalRemoveNodeWorker::updateWaveNodeManagedObjectStep: Entering ...");

    ClusterLocalReportRemovedNodeFromClusterMessage* pClusterLocalReportRemovedNodeFromClusterMessage = dynamic_cast<ClusterLocalReportRemovedNodeFromClusterMessage* >(pPrismLinearSequencerContext->getPWaveMessage());

    prismAssert(NULL != pClusterLocalReportRemovedNodeFromClusterMessage, __FILE__, __LINE__);

    //Obtain the wavenode and update the status and then commit
    startTransaction();
    WaveManagedObjectSynchronousQueryContext queryContext (WaveNode::getClassName ());

    LocationId  locationId = pClusterLocalReportRemovedNodeFromClusterMessage->getThisNodeLocationId ();

    queryContext.addAndAttribute (new AttributeUI32 (locationId, "locationId"));
            
    vector<WaveManagedObject *>              *pWaveNodeMOs = querySynchronously (&queryContext);
    prismAssert(NULL != pWaveNodeMOs, __FILE__, __LINE__);

    UI32 numberOfResults = pWaveNodeMOs->size ();
    prismAssert (1 == numberOfResults, __FILE__, __LINE__);
            
    WaveNode *pWaveNode = dynamic_cast<WaveNode *> ((*pWaveNodeMOs)[0]);
    prismAssert(NULL != pWaveNode, __FILE__, __LINE__); 

    //Set LocationId and NodeStatus 
    LocationId thisNodeLocationid  =    pClusterLocalReportRemovedNodeFromClusterMessage->getThisNodeLocationId();
    pWaveNode->setLocationId(thisNodeLocationid);
    pWaveNode->setGenericStatus(WAVE_MANAGED_OBJECT_GENERIC_STATUS_GOOD);
    pWaveNode->setSpecificStatus(WAVE_MANAGED_OBJECT_SPECIFIC_STATUS_STAND_ALONE);
    updateWaveManagedObject(pWaveNode);
    ResourceId status = commitTransaction();

    if (FRAMEWORK_SUCCESS != status)
    {
        trace (TRACE_LEVEL_WARN, "ClusterLocalReportRemovedNodeFromClusterWorker::updateWaveNodeManagedObjectStep : failed for commitTransaction for WaveNode");
    }

    WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector(pWaveNodeMOs);

    pPrismLinearSequencerContext->executeNextStep(WAVE_MESSAGE_SUCCESS); 

    return;
}



}
