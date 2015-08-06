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
#include "Framework/Utils/PrismLinearSequencerContext.h"
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

    PrismLinearSequencerContext *pPrismLinearSequencerContext = new PrismLinearSequencerContext (pCentralClusterConfigUpdateHardwareSynchronizationStateMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    // serialize the handling of this message
    pPrismLinearSequencerContext->holdAll ();

    pPrismLinearSequencerContext->start ();
}

/** 
 *Name:         sendUpdateWaveNodesToClusterLocalStep
 *Description:  Asynchronous linear sequencer step to update the WaveNodeMO's
 *              hardware syncrhonization state attribute.  A single filtered
 *              query is used to get all desired WaveNode MO's by their location
 *              id.  From these results, the WaveNodeMO's hardware sync state
 *              will be updated.  This is a batched update.
 * 
 * @param       PrismLinearSequencerContext* : Asynchronous linear sequencer context
 */ 
void CentralClusterConfigUpdateHardwareSynchronizationStateWorker::sendUpdateWaveNodesToClusterLocalStep (PrismLinearSequencerContext *pPrismLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "CentralClusterConfigUpdateHardwareSynchronizationStateWorker::sendUpdateWaveNodesToClusterLocalStep : Entering ...");

    CentralClusterConfigUpdateHardwareSynchronizationStateMessage* pCentralClusterConfigUpdateHardwareSynchronizationStateMessage = dynamic_cast<CentralClusterConfigUpdateHardwareSynchronizationStateMessage* >(pPrismLinearSequencerContext->getPWaveMessage());

    if (NULL == pCentralClusterConfigUpdateHardwareSynchronizationStateMessage)
    {
        trace (TRACE_LEVEL_FATAL, "CentralClusterConfigUpdateHardwareSynchronizationStateWorker::sendUpdateWaveNodesToClusterLocalStep : Failed to dynamic cast CentralClusterConfigUpdateHardwareSynchronizationStateMessage.");
        prismAssert (false, __FILE__, __LINE__);
    }

    ResourceId                                              hardwareSyncState                                       = pCentralClusterConfigUpdateHardwareSynchronizationStateMessage->getHardwareSynchronizationState (); 
    vector<LocationId>                                      locationsForWaveNodeUpdate                              = pCentralClusterConfigUpdateHardwareSynchronizationStateMessage->getLocationIds ();

    ClusterLocalSetHardwareSynchronizationStateMessage  *pClusterLocalSetHardwareSynchronizationStateMessage  = new ClusterLocalSetHardwareSynchronizationStateMessage (hardwareSyncState);

    if (NULL == pClusterLocalSetHardwareSynchronizationStateMessage)
    {
        trace (TRACE_LEVEL_FATAL, "CentralClusterConfigUpdateHardwareSynchronizationStateWorker::sendUpdateWaveNodesToClusterLocalStep : Failed to allocate ClusterLocalUpdateHardwareSynchronizationStateMessage.");
        prismAssert (false, __FILE__, __LINE__);
    }
 
    // Use sendToWaveCluster to allow ClusterLocal to update the WaveNode hardware sync state attribute.

    WaveSendToClusterContext *pWaveSendToClusterContext = new WaveSendToClusterContext (this, reinterpret_cast<PrismAsynchronousCallback> (&CentralClusterConfigUpdateHardwareSynchronizationStateWorker::sendUpdateWaveNodesToClusterLocalStepCallback), pPrismLinearSequencerContext);

    pWaveSendToClusterContext->setPWaveMessageForPhase1 (pClusterLocalSetHardwareSynchronizationStateMessage);
    pWaveSendToClusterContext->setLocationsToSendToForPhase1 (locationsForWaveNodeUpdate);
    pWaveSendToClusterContext->setPartialSuccessFlag (true);    

    sendToWaveCluster (pWaveSendToClusterContext);   
}

void CentralClusterConfigUpdateHardwareSynchronizationStateWorker::sendUpdateWaveNodesToClusterLocalStepCallback (WaveSendToClusterContext *pWaveSendToClusterContext)
{
    PrismLinearSequencerContext    *pPrismLinearSequencerContext    = reinterpret_cast<PrismLinearSequencerContext *> (pWaveSendToClusterContext->getPCallerContext ());
    ResourceId                      sendToClusterCompletionStatus   = pWaveSendToClusterContext->getCompletionStatus ();

    if (NULL == pPrismLinearSequencerContext)
    {
        trace (TRACE_LEVEL_FATAL, "CentralClusterConfigUpdateHardwareSynchronizationStateWorker::sendUpdateWaveNodesToClusterLocalStepCallback : Failed to cast PrismLinearSequencerContext.");
        prismAssert (NULL != pPrismLinearSequencerContext, __FILE__, __LINE__);
    }

    delete (pWaveSendToClusterContext->getPWaveMessageForPhase1 ());
    delete (pWaveSendToClusterContext);

    pPrismLinearSequencerContext->executeNextStep(sendToClusterCompletionStatus); 
} 

}
