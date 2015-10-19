/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Leifang Hu                                                   *
 ***************************************************************************/
#include "Cluster/Local/ClusterLocalSetHaRoleMessage.h"
#include "Cluster/Local/ClusterLocalSetHaRoleWorker.h"
#include "Cluster/Local/ClusterLocalObjectManager.h"
#include "Cluster/Local/ClusterLocalTypes.h"
#include  "Framework/Types/Types.h"
#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/ObjectModel/WaveManagedObjectToolKit.h"
#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Cluster/Local/WaveNode.h"
#include "Cluster/Local/WaveHaNode.h"
#include "Cluster/WaveCluster.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContext.h"
#include "Framework/Attributes/AttributeEnum.h"

namespace WaveNs
{

/// Name
/// ClusterLocalSetHaRoleWorker
/// Description
/// Constructor: Registers the handler to handle the HA role notofication message 
/// notification from the framework.
/// Constructor
/// Input
/// ClusterLocalObjectManager *: Registered with the WaveElement
/// Output
/// None
/// Return
/// None

ClusterLocalSetHaRoleWorker::ClusterLocalSetHaRoleWorker (ClusterLocalObjectManager *pClusterLocalObjectManager)
    : WaveWorker (pClusterLocalObjectManager)
{
    addOperationMap (CLUSTER_LOCAL_SET_HA_ROLE, reinterpret_cast<WaveMessageHandler> (&ClusterLocalSetHaRoleWorker::setHaRoleMessageHandler));
}
/// Name
/// ClusterLocalSetHaRoleWorker
/// Description
/// Destructor
/// Input
/// None
/// Output
/// None
/// Return
/// None

ClusterLocalSetHaRoleWorker::~ClusterLocalSetHaRoleWorker ()
{
}

/// Name
/// ClusterLocalSetHaRoleWorker
/// Description
/// On receiving the message from the framework it constructs the steps of processing
/// and lodges them in a context.Then it kick starts the processing
/// Input
/// ClusterLocalSetHaRoleMessage *: pointer to message to received from f/w
/// Output
/// None
/// Return
/// None

void ClusterLocalSetHaRoleWorker::setHaRoleMessageHandler (ClusterLocalSetHaRoleMessage *pClusterLocalSetHaRoleMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&ClusterLocalSetHaRoleWorker::updateWaveHaNodeManagedObjectStep),

        reinterpret_cast<WaveLinearSequencerStep> (&ClusterLocalSetHaRoleWorker::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&ClusterLocalSetHaRoleWorker::prismLinearSequencerFailedStep)
    };

    //Note: Memory is freed inside the framework in the Succeeeded or Failure step
    WaveLinearSequencerContext *pWaveLinearSequencerContext = new WaveLinearSequencerContext (pClusterLocalSetHaRoleMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0])); 
    tracePrintf(TRACE_LEVEL_INFO, "Number of Steps = %d",sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pWaveLinearSequencerContext->holdAll ();
    pWaveLinearSequencerContext->start ();
}

/// Name
/// updateWaveHaNodeManagedObjectStep
/// Description
/// In this step the local WaveNode MO's node status is updated 
/// and committed back to the DB
/// Input
/// WaveLinearSequencerContext *
/// Output
/// None
/// Return
/// None
void ClusterLocalSetHaRoleWorker::updateWaveHaNodeManagedObjectStep(WaveLinearSequencerContext *pWaveLinearSequencerContext)
{

    trace (TRACE_LEVEL_INFO, "ClusterLocalSetHaRoleWorker::updateWaveHaNodeManagedObjectStep: Entering ...");

#if 0
    //Message from the context
    ClusterLocalSetHaRoleMessage* pClusterLocalSetHaRoleMessage = dynamic_cast<ClusterLocalSetHaRoleMessage* >(pWaveLinearSequencerContext->getPWaveMessage());

    waveAssert(NULL != pClusterLocalSetHaRoleMessage, __FILE__, __LINE__);

    //Obtain the wavenode and update the status and then committ
    WaveManagedObjectSynchronousQueryContext queryContext (WaveHaNode::getClassName ());

	WaveHaNodeRole  haRole    =    (WaveHaNodeRole)(pClusterLocalSetHaRoleMessage->getHaRole());

    vector<WaveManagedObject *>              *pWaveHaNodeMOs = querySynchronously (&queryContext);
    waveAssert(NULL != pWaveHaNodeMOs, __FILE__, __LINE__);

    UI32 numberOfResults = pWaveHaNodeMOs->size ();
    waveAssert (1 == numberOfResults, __FILE__, __LINE__);

	startTransaction();
    WaveHaNode *pWaveHaNode = dynamic_cast<WaveHaNode *> ((*pWaveHaNodeMOs)[0]);
    //Set HaRole 
    pWaveHaNode->setHaRole(haRole);
    updateWaveManagedObject(pWaveHaNode);
    commitTransaction();

	trace (TRACE_LEVEL_INFO, string("ClusterLocalSetHaRoleWorker:set haNode to ") + haRole);
    WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector(pWaveHaNodeMOs);
#endif

    pWaveLinearSequencerContext->executeNextStep(WAVE_MESSAGE_SUCCESS); 

    return;
}

}
