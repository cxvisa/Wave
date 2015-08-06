/**
 *@file CentralClusterConfigUpdateHardwareSynchronizationStateWorker.cpp 
 * Copyright (C) 2011 BrocadeCommunications Systems,Inc.
 * All rights reserved.
 * 
 * Description: This file has the implementation of the
 *              Worker class which is responsible for updating 
 *              local WaveNodeManagedObject's hardware sync state. 
 * Author :     Brian Adaniya
 */

#include "Cluster/CentralClusterConfigUpdateHardwareSynchronizationStateWorker.h"
#include "Cluster/CentralClusterConfigObjectManager.h"
#include "Cluster/ClusterMessages.h"
#include "Cluster/ClusterTypes.h"
#include "Cluster/Local/ClusterLocalSetHardwareSynchronizationStateMessage.h"
#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/ObjectModel/WaveSendToClusterContext.h"
#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/Utils/FrameworkToolKit.h"

namespace WaveNs
{

/** 
 *Name:         CentralClusterConfigUpdateHardwareSynchronizationStateWorker 
 *Description:  Constructor 
 * 
 * @param       CentralClusterConfigObjectManager* : Object Manager that owns this worker 
 */
CentralClusterConfigUpdateHardwareSynchronizationStateWorker::CentralClusterConfigUpdateHardwareSynchronizationStateWorker (CentralClusterConfigObjectManager *pCentralClusterConfigObjectManager)
    : WaveWorker (pCentralClusterConfigObjectManager)
{
    addOperationMap (CENTRAL_CLUSTER_CONFIG_UPDATE_HARDWARE_SYNCHRONIZATION_STATE, reinterpret_cast<WaveMessageHandler> (&CentralClusterConfigUpdateHardwareSynchronizationStateWorker::updateHardwareSynchronizationStateMessageHandler));
}

/** 
 *Name:         ~CentralClusterConfigUpdateHardwareSynchronizationStateWorker 
 *Description:  Destructor 
 */
CentralClusterConfigUpdateHardwareSynchronizationStateWorker::~CentralClusterConfigUpdateHardwareSynchronizationStateWorker ()
{
}

WaveMessage *CentralClusterConfigUpdateHardwareSynchronizationStateWorker::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case CENTRAL_CLUSTER_CONFIG_UPDATE_HARDWARE_SYNCHRONIZATION_STATE :
            pWaveMessage = new CentralClusterConfigUpdateHardwareSynchronizationStateMessage ();
            break;

        default :
            pWaveMessage = NULL;
    }

    return (pWaveMessage);
}

/** 
 *Name:         updateHardwareSynchronizationStateMessageHandler
 *Description:  Message handler to set the hardware synchronization state
 *              for the WaveNode Managed Object
 * 
 * @param       CentralClusterConfigUpdateHardwareSynchronizationStateMessage* : Message to be handled
 */
void CentralClusterConfigUpdateHardwareSynchronizationStateWorker::updateHardwareSynchronizationStateMessageHandler (CentralClusterConfigUpdateHardwareSynchronizationStateMessage *pCentralClusterConfigUpdateHardwareSynchronizationStateMessage)
{
     PrismLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<PrismLinearSequencerStep> (&CentralClusterConfigUpdateHardwareSynchronizationStateWorker::sendUpdateWaveNodesToClusterLocalStep),
        reinterpret_cast<PrismLinearSequencerStep> (&CentralClusterConfigUpdateHardwareSynchronizationStateWorker::prismLinearSequencerSucceededStep),
        reinterpret_cast<PrismLinearSequencerStep> (&CentralClusterConfigUpdateHardwareSynchronizationStateWorker::prismLinearSequencerFailedStep)
    };

    WaveLinearSequencerContext *pWaveLinearSequencerContext = new WaveLinearSequencerContext (pCentralClusterConfigUpdateHardwareSynchronizationStateMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    // serialize the handling of this message
    pWaveLinearSequencerContext->holdAll ();

    pWaveLinearSequencerContext->start ();
}

/** 
 *Name:         sendUpdateWaveNodesToClusterLocalStep
 *Description:  Asynchronous linear sequencer step to update the WaveNodeMO's
 *              hardware syncrhonization state attribute.  A single filtered
 *              query is used to get all desired WaveNode MO's by their location
 *              id.  From these results, the WaveNodeMO's hardware sync state
 *              will be updated.  This is a batched update.
 * 
 * @param       WaveLinearSequencerContext* : Asynchronous linear sequencer context
 */ 
void CentralClusterConfigUpdateHardwareSynchronizationStateWorker::sendUpdateWaveNodesToClusterLocalStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "CentralClusterConfigUpdateHardwareSynchronizationStateWorker::sendUpdateWaveNodesToClusterLocalStep : Entering ...");

    CentralClusterConfigUpdateHardwareSynchronizationStateMessage* pCentralClusterConfigUpdateHardwareSynchronizationStateMessage = dynamic_cast<CentralClusterConfigUpdateHardwareSynchronizationStateMessage* >(pWaveLinearSequencerContext->getPWaveMessage());

    if (NULL == pCentralClusterConfigUpdateHardwareSynchronizationStateMessage)
    {
        trace (TRACE_LEVEL_FATAL, "CentralClusterConfigUpdateHardwareSynchronizationStateWorker::sendUpdateWaveNodesToClusterLocalStep : Failed to dynamic cast CentralClusterConfigUpdateHardwareSynchronizationStateMessage.");
        waveAssert (false, __FILE__, __LINE__);
    }

    ResourceId                                              hardwareSyncState                                       = pCentralClusterConfigUpdateHardwareSynchronizationStateMessage->getHardwareSynchronizationState (); 
    vector<LocationId>                                      locationsForWaveNodeUpdate                              = pCentralClusterConfigUpdateHardwareSynchronizationStateMessage->getLocationIds ();

    ClusterLocalSetHardwareSynchronizationStateMessage  *pClusterLocalSetHardwareSynchronizationStateMessage  = new ClusterLocalSetHardwareSynchronizationStateMessage (hardwareSyncState);

    if (NULL == pClusterLocalSetHardwareSynchronizationStateMessage)
    {
        trace (TRACE_LEVEL_FATAL, "CentralClusterConfigUpdateHardwareSynchronizationStateWorker::sendUpdateWaveNodesToClusterLocalStep : Failed to allocate ClusterLocalUpdateHardwareSynchronizationStateMessage.");
        waveAssert (false, __FILE__, __LINE__);
    }
 
    // Use sendToWaveCluster to allow ClusterLocal to update the WaveNode hardware sync state attribute.

    WaveSendToClusterContext *pWaveSendToClusterContext = new WaveSendToClusterContext (this, reinterpret_cast<PrismAsynchronousCallback> (&CentralClusterConfigUpdateHardwareSynchronizationStateWorker::sendUpdateWaveNodesToClusterLocalStepCallback), pWaveLinearSequencerContext);

    pWaveSendToClusterContext->setPWaveMessageForPhase1 (pClusterLocalSetHardwareSynchronizationStateMessage);
    pWaveSendToClusterContext->setLocationsToSendToForPhase1 (locationsForWaveNodeUpdate);
    pWaveSendToClusterContext->setPartialSuccessFlag (true);    

    sendToWaveCluster (pWaveSendToClusterContext);   
}

void CentralClusterConfigUpdateHardwareSynchronizationStateWorker::sendUpdateWaveNodesToClusterLocalStepCallback (WaveSendToClusterContext *pWaveSendToClusterContext)
{
    WaveLinearSequencerContext    *pWaveLinearSequencerContext    = reinterpret_cast<WaveLinearSequencerContext *> (pWaveSendToClusterContext->getPCallerContext ());
    ResourceId                      sendToClusterCompletionStatus   = pWaveSendToClusterContext->getCompletionStatus ();

    if (NULL == pWaveLinearSequencerContext)
    {
        trace (TRACE_LEVEL_FATAL, "CentralClusterConfigUpdateHardwareSynchronizationStateWorker::sendUpdateWaveNodesToClusterLocalStepCallback : Failed to cast WaveLinearSequencerContext.");
        waveAssert (NULL != pWaveLinearSequencerContext, __FILE__, __LINE__);
    }

    delete (pWaveSendToClusterContext->getPWaveMessageForPhase1 ());
    delete (pWaveSendToClusterContext);

    pWaveLinearSequencerContext->executeNextStep(sendToClusterCompletionStatus); 
} 

}
