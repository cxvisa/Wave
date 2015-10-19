/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#include "Cluster/Local/ClusterLocalReportReplaceMessage.h"
#include "Cluster/Local/ClusterLocalReportReplaceWorker.h"
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
/// ClusterLocalReportReplaceWorker
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

ClusterLocalReportReplaceWorker::ClusterLocalReportReplaceWorker (ClusterLocalObjectManager *pClusterLocalObjectManager)
    : WaveWorker (pClusterLocalObjectManager)
{
    addOperationMap (CLUSTER_LOCAL_REPORT_REPLACE, reinterpret_cast<WaveMessageHandler> (&ClusterLocalReportReplaceWorker::replaceMessageHandler));
}
/// Name
/// ClusterLocalReportReplaceWorker
/// Description
/// Destructor
/// Input
/// None
/// Output
/// None
/// Return
/// None

ClusterLocalReportReplaceWorker::~ClusterLocalReportReplaceWorker ()
{
}

/// Name
/// replaceMessageHandler
/// Description
/// On receiving the message from the framework it constructs the steps of processing
/// and lodges them in a context.Then it kick starts the processing
/// Input
/// ClusterLocalReportReplaceMessage *: pointer to message to received from f/w
/// Output
/// None
/// Return
/// None

void ClusterLocalReportReplaceWorker::replaceMessageHandler (ClusterLocalReportReplaceMessage *pClusterLocalReportReplaceMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&ClusterLocalReportReplaceWorker::updateWaveNodeManagedObjectStep),

        reinterpret_cast<WaveLinearSequencerStep> (&ClusterLocalReportReplaceWorker::waveLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&ClusterLocalReportReplaceWorker::waveLinearSequencerFailedStep)
    };

    //Note: Memory is freed inside the framework in the Succeeeded or Failure step
    WaveLinearSequencerContext *pWaveLinearSequencerContext = new WaveLinearSequencerContext (pClusterLocalReportReplaceMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0])); 

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
void ClusterLocalReportReplaceWorker::updateWaveNodeManagedObjectStep(WaveLinearSequencerContext *pWaveLinearSequencerContext)
{

    trace (TRACE_LEVEL_DEVEL, "ClusterLocalReportReplaceWorker::updateWaveNodeManagedObjectStep: Entering ...");

    //Message from the context
    ClusterLocalReportReplaceMessage* pClusterLocalReportReplaceMessage = dynamic_cast<ClusterLocalReportReplaceMessage* >(pWaveLinearSequencerContext->getPWaveMessage());

    waveAssert(NULL != pClusterLocalReportReplaceMessage, __FILE__, __LINE__);

    //Obtain the wavenode and set the ip address and port 
    startTransaction();
    WaveManagedObjectSynchronousQueryContext queryContext (WaveNode::getClassName ());

    LocationId thisNodeLocationId = pClusterLocalReportReplaceMessage->getThisNodeLocationId();
    queryContext.addAndAttribute (new AttributeLocationId (thisNodeLocationId,"locationid"));

    vector<WaveManagedObject *>              *pWaveNodeMOs = querySynchronously (&queryContext);
    waveAssert(NULL != pWaveNodeMOs, __FILE__, __LINE__);

    UI32 numberOfResults = pWaveNodeMOs->size ();
    waveAssert (1 == numberOfResults, __FILE__, __LINE__);
            
    WaveNode *pWaveNode = dynamic_cast<WaveNode *> ((*pWaveNodeMOs)[0]);
    waveAssert (NULL != pWaveNode, __FILE__, __LINE__);

    //Set new IP address and port 
    pWaveNode->setIpAddress (pClusterLocalReportReplaceMessage->getThisNodeIpAddress ());
    pWaveNode->setPort (pClusterLocalReportReplaceMessage->getThisNodePort ());

    updateWaveManagedObject(pWaveNode);
    ResourceId status = commitTransaction();

    if (FRAMEWORK_SUCCESS != status)
    {
        trace (TRACE_LEVEL_WARN, "ClusterLocalReportReplaceWorker::updateWaveNodeManagedObjectStep : failed for commitTransaction for WaveNode"); 
    }

    WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector(pWaveNodeMOs);

    pWaveLinearSequencerContext->executeNextStep(WAVE_MESSAGE_SUCCESS); 

    return;
}

}
