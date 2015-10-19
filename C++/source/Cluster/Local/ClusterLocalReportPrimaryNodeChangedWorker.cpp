/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Aashish Akhouri                                              *
 ***************************************************************************/

#include "Cluster/Local/ClusterLocalReportPrimaryNodeChangedMessage.h"
#include "Cluster/Local/ClusterLocalReportPrimaryNodeChangedWorker.h"
#include "Cluster/Local/ClusterLocalObjectManager.h"
#include "Cluster/Local/ClusterLocalTypes.h"
#include "Framework/Types/Types.h"
#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/ObjectModel/WaveManagedObjectToolKit.h"
#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Cluster/Local/WaveNode.h"
#include "Cluster/WaveCluster.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContext.h"
#include "Cluster/Local/HeartBeat/HeartBeatMessages.h"
#include "Framework/Utils/FrameworkToolKit.h"

namespace WaveNs
{

/// Name
/// ClusterLocalReportPrimaryNodeChangedWorker
/// Description
/// Constructor: Registers the handler to handle the primaryNodeChange
/// notification from the framework.
/// Constructor
/// Input
/// ClusterLocalObjectManager *: Registered with the WaveElement
/// Output
/// None
/// Return
/// None

ClusterLocalReportPrimaryNodeChangedWorker::ClusterLocalReportPrimaryNodeChangedWorker (ClusterLocalObjectManager *pClusterLocalObjectManager)
    : WaveWorker (pClusterLocalObjectManager)
{
    addOperationMap (CLUSTER_LOCAL_REPORT_PRIMARY_NODE_CHANGED, reinterpret_cast<WaveMessageHandler> (&ClusterLocalReportPrimaryNodeChangedWorker::primaryNodeChangedMessageHandler));
}
/// Name
/// ClusterLocalReportPrimaryNodeChangedWorker
/// Description
/// Destructor
/// Input
/// None
/// Output
/// None
/// Return
/// None

ClusterLocalReportPrimaryNodeChangedWorker::~ClusterLocalReportPrimaryNodeChangedWorker ()
{
}

/// Name
/// primaryNodeChangedMessageHandler
/// Description
/// On receiving the message from the framework it constructs the steps of processing
/// and lodges them in a context.Then it kick starts the processing
/// Input
/// ClusterLocalReportPrimaryNodeChangedMessage *: pointer to message to received from f/w
/// Output
/// None
/// Return
/// None

void ClusterLocalReportPrimaryNodeChangedWorker::primaryNodeChangedMessageHandler (ClusterLocalReportPrimaryNodeChangedMessage *pClusterLocalReportPrimaryNodeChangedMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&ClusterLocalReportPrimaryNodeChangedWorker::updateWaveNodeManagedObjectStep),

        reinterpret_cast<WaveLinearSequencerStep> (&ClusterLocalReportPrimaryNodeChangedWorker::waveLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&ClusterLocalReportPrimaryNodeChangedWorker::waveLinearSequencerFailedStep)
    };

    //Note: Memory is freed inside the framework in the Succeeeded or Failure step
    WaveLinearSequencerContext *pWaveLinearSequencerContext = new WaveLinearSequencerContext (pClusterLocalReportPrimaryNodeChangedMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0])); 
    tracePrintf(TRACE_LEVEL_INFO, "Number of Steps = %d",sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pWaveLinearSequencerContext->holdAll ();
    pWaveLinearSequencerContext->start ();
}

/// Name
/// updateWaveNodeManagedObjectStep
/// Description
/// In this step the local WaveNode MO's node status is updated 
/// and committed back to the DB
/// Input
/// WaveLinearSequencerContext *
/// Output
/// None
/// Return
/// None
void ClusterLocalReportPrimaryNodeChangedWorker::updateWaveNodeManagedObjectStep(WaveLinearSequencerContext *pWaveLinearSequencerContext)
{

    trace (TRACE_LEVEL_DEVEL, "ClusterLocalReportPrimaryNodeChangedWorker::updateWaveNodeManagedObjectStep: Entering ...");

    //Message from the context
    ClusterLocalReportPrimaryNodeChangedMessage* pClusterLocalReportPrimaryNodeChangedMessage = dynamic_cast<ClusterLocalReportPrimaryNodeChangedMessage* >(pWaveLinearSequencerContext->getPWaveMessage());

    waveAssert(NULL != pClusterLocalReportPrimaryNodeChangedMessage, __FILE__, __LINE__);

    //Obtain the wavenode and update the status and then committ
    startTransaction();
    WaveManagedObjectSynchronousQueryContext queryContext (WaveNode::getClassName ());

    string     thisNodeIpAddress   =    pClusterLocalReportPrimaryNodeChangedMessage->getThisNodeIpAddress();
    UI32       thisNodePort        =    pClusterLocalReportPrimaryNodeChangedMessage->getThisNodePort();
    queryContext.addAndAttribute (new AttributeString (thisNodeIpAddress,"ipAddress"));
    queryContext.addAndAttribute (new AttributeUI32 (thisNodePort,"port"));
            
    vector<WaveManagedObject *>              *pWaveNodeMOs = querySynchronously (&queryContext);
    waveAssert(NULL != pWaveNodeMOs, __FILE__, __LINE__);

    UI32 numberOfResults = pWaveNodeMOs->size ();
    waveAssert (1 == numberOfResults, __FILE__, __LINE__);
            
    WaveNode *pWaveNode = dynamic_cast<WaveNode *> ((*pWaveNodeMOs)[0]);
    waveAssert(NULL != pWaveNode, __FILE__, __LINE__);
    //Set LocationId and NodeStatus 
    LocationId thisNodeLocationid  =    pClusterLocalReportPrimaryNodeChangedMessage->getThisNodeLocationId();
    pWaveNode->setLocationId(thisNodeLocationid);
    //Generic Status is Good and since this happens at the end of add or rejoin
    // we can say that Secondary is connected to cluster
    pWaveNode->setGenericStatus(WAVE_MANAGED_OBJECT_GENERIC_STATUS_GOOD);
    if (FrameworkToolKit::getThisLocationRole () == LOCATION_SECONDARY_CLUSTER_PHASE_2 )
    {
        pWaveNode->setSpecificStatus(WAVE_MANAGED_OBJECT_SPECIFIC_STATUS_SECONDARY_ADD_PHASE2_STARTED);
        trace (TRACE_LEVEL_INFO, "ClusterLocalReportPrimaryNodeChangedWorker::updateWaveNodeManagedObjectStep: WaveNode Specificstatus set to Secondary Add Phase2 Started");
    }
    else if(FrameworkToolKit::getThisLocationRole () == LOCATION_SECONDARY_REJOIN_PHASE_2)
    {   
        pWaveNode->setSpecificStatus(WAVE_MANAGED_OBJECT_SPECIFIC_STATUS_SECONDARY_REJOIN_PHASE2_STARTED);
        trace (TRACE_LEVEL_INFO, "ClusterLocalReportPrimaryNodeChangedWorker::updateWaveNodeManagedObjectStep: WaveNode Specificstatus set to Secondary Rejoin Phase2 Started");
    }
    updateWaveManagedObject(pWaveNode);
    ResourceId status = commitTransaction();

    if (FRAMEWORK_SUCCESS != status)
    {
        trace (TRACE_LEVEL_WARN, "ClusterLocalReportPrimaryNodeChangedWorker::updateWaveNodeManagedObjectStep : failed for commitTransaction for WaveNode");
    }

    WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector(pWaveNodeMOs);

    pWaveLinearSequencerContext->executeNextStep(WAVE_MESSAGE_SUCCESS); 

    return;
}

}
