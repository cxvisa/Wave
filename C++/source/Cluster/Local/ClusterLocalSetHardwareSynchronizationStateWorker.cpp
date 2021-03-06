/**
 *@file ClusterLocalSetHardwareSynchronizationStateWorker.cpp 
 * Copyright (C) 2011 BrocadeCommunications Systems,Inc.
 * All rights reserved.
 * 
 * Description: This file has the implementation of the
 *              Worker class which is responsible for updating 
 *              local WaveNodeManagedObject's hardware sync state. 
 * Author :     Brian Adaniya
 */

#include "Cluster/Local/ClusterLocalSetHardwareSynchronizationStateWorker.h"
#include "Cluster/Local/ClusterLocalObjectManager.h"
#include "Cluster/Local/ClusterLocalSetHardwareSynchronizationStateMessage.h"
#include "Cluster/Local/ClusterLocalTypes.h"
#include "Cluster/Local/WaveNode.h"
#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContext.h"
#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/Utils/FrameworkToolKit.h"

namespace WaveNs
{

/** 
 *Name:         ClusterLocalSetHardwareSynchronizationStateWorker 
 *Description:  Constructor 
 * 
 * @param       ClusterLocalObjectManager* : Object Manager that owns this worker 
 */
ClusterLocalSetHardwareSynchronizationStateWorker::ClusterLocalSetHardwareSynchronizationStateWorker (ClusterLocalObjectManager *pClusterLocalObjectManager)
    : WaveWorker (pClusterLocalObjectManager)
{
    addOperationMap (CLUSTER_LOCAL_SET_HARDWARE_SYNCHRONIZATION_STATE, reinterpret_cast<WaveMessageHandler> (&ClusterLocalSetHardwareSynchronizationStateWorker::setHardwareSynchronizationStateMessageHandler));
}

/** 
 *Name:         ~ClusterLocalSetHardwareSynchronizationStateWorker 
 *Description:  Destructor 
 */
ClusterLocalSetHardwareSynchronizationStateWorker::~ClusterLocalSetHardwareSynchronizationStateWorker ()
{
}

WaveMessage *ClusterLocalSetHardwareSynchronizationStateWorker::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case CLUSTER_LOCAL_SET_HARDWARE_SYNCHRONIZATION_STATE :
            pWaveMessage = new ClusterLocalSetHardwareSynchronizationStateMessage ();
            break;

        default :
            pWaveMessage = NULL;
    }

    return (pWaveMessage);
}

/** 
 *Name:         setHardwareSynchronizationStateMessageHandler
 *Description:  Message handler to set the hardware synchronization state
 *              for the WaveNode Managed Object
 * 
 * @param       ClusterLocalSetHardwareSynchronizationStateMessage* : Message to be handled
 */
void ClusterLocalSetHardwareSynchronizationStateWorker::setHardwareSynchronizationStateMessageHandler (ClusterLocalSetHardwareSynchronizationStateMessage *pClusterLocalSetHardwareSynchronizationStateMessage)
{
     WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&ClusterLocalSetHardwareSynchronizationStateWorker::waveLinearSequencerStartTransactionStep),
        reinterpret_cast<WaveLinearSequencerStep> (&ClusterLocalSetHardwareSynchronizationStateWorker::updateWaveNodeManagedObjectStep),
        reinterpret_cast<WaveLinearSequencerStep> (&ClusterLocalSetHardwareSynchronizationStateWorker::waveLinearSequencerCommitTransactionStep),
        reinterpret_cast<WaveLinearSequencerStep> (&ClusterLocalSetHardwareSynchronizationStateWorker::waveLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&ClusterLocalSetHardwareSynchronizationStateWorker::waveLinearSequencerFailedStep)
    };

    WaveLinearSequencerContext *pWaveLinearSequencerContext = new WaveLinearSequencerContext (pClusterLocalSetHardwareSynchronizationStateMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    // serialize the handling of this message
    pWaveLinearSequencerContext->holdAll ();

    pWaveLinearSequencerContext->start ();
}

/** 
 *Name:         updateWaveNodeManagedObjectStep
 *Description:  Asynchronous linear sequencer step to update the WaveNodeMO
 * 
 * @param       WaveLinearSequencerContext* : Asynchronous linear sequencer context
 */ 
void ClusterLocalSetHardwareSynchronizationStateWorker::updateWaveNodeManagedObjectStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "ClusterLocalSetHardwareSynchronizationStateWorker::updateWaveNodeManagedObjectStep : Entering ...");

    ClusterLocalSetHardwareSynchronizationStateMessage* pClusterLocalSetHardwareSynchronizationStateMessage = dynamic_cast<ClusterLocalSetHardwareSynchronizationStateMessage* >(pWaveLinearSequencerContext->getPWaveMessage());

    if (NULL == pClusterLocalSetHardwareSynchronizationStateMessage)
    {
        trace (TRACE_LEVEL_FATAL, "ClusterLocalSetHardwareSynchronizationStateWorker::updateWaveNodeManagedObjectStep : Dynamic cast to ClusterLocalSetHardwareSynchronizationStateMessage failed.");
        waveAssert (false, __FILE__, __LINE__);
    }

    ResourceId hardwareSynchronizationState = pClusterLocalSetHardwareSynchronizationStateMessage->getHardwareSynchronizationState ();

    // Query for the WaveNode MO that we need to update

    WaveNode *pWaveNode = ClusterLocalObjectManager::getInstance ()->getThisWaveNodeManagedObject ();
    waveAssert (NULL != pWaveNode, __FILE__, __LINE__);

    updateWaveManagedObject(pWaveNode);

    pWaveNode->setHardwareSynchronizationState (hardwareSynchronizationState);

    // Clean up of queried Managed Objects are marked now and properly deleted later during sequencer's destructor

    pWaveLinearSequencerContext->addManagedObjectForGarbageCollection (pWaveNode);

    pWaveLinearSequencerContext->executeNextStep(WAVE_MESSAGE_SUCCESS); 
}

}
