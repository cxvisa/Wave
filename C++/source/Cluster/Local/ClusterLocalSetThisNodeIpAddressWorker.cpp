/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Cluster/Local/ClusterLocalSetThisNodeIpAddressWorker.h"
#include "Cluster/Local/ClusterLocalObjectManager.h"
#include "Cluster/Local/ClusterLocalTypes.h"
#include "Cluster/Local/ClusterLocalSetThisNodeIpAddressMessage.h"
#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Cluster/Local/WaveNode.h"

namespace WaveNs
{

ClusterLocalSetThisNodeIpAddressWorker::ClusterLocalSetThisNodeIpAddressWorker (ClusterLocalObjectManager *pClusterLocalObjectManager)
    : WaveWorker (pClusterLocalObjectManager)
{
    addOperationMap (CLUSTER_LOCAL_SET_THIS_NODE_IP_ADDRESS, reinterpret_cast<WaveMessageHandler> (&ClusterLocalSetThisNodeIpAddressWorker::setThisNodeIpAddressMessageHandler));
}

ClusterLocalSetThisNodeIpAddressWorker::~ClusterLocalSetThisNodeIpAddressWorker ()
{
}

void ClusterLocalSetThisNodeIpAddressWorker::setThisNodeIpAddressMessageHandler (ClusterLocalSetThisNodeIpAddressMessage *pClusterLocalSetThisNodeIpAddressMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&ClusterLocalSetThisNodeIpAddressWorker::setThisNodeIpAddressValidateStep),
        reinterpret_cast<WaveLinearSequencerStep> (&ClusterLocalSetThisNodeIpAddressWorker::setThisNodeIpAddressUpdateWaveFrameworkObjectManagerStep),
        reinterpret_cast<WaveLinearSequencerStep> (&ClusterLocalSetThisNodeIpAddressWorker::waveLinearSequencerStartTransactionStep),
        reinterpret_cast<WaveLinearSequencerStep> (&ClusterLocalSetThisNodeIpAddressWorker::setThisNodeIpAddressUpdateThisWaveNodeStep),
        reinterpret_cast<WaveLinearSequencerStep> (&ClusterLocalSetThisNodeIpAddressWorker::waveLinearSequencerCommitTransactionStep),
        reinterpret_cast<WaveLinearSequencerStep> (&ClusterLocalSetThisNodeIpAddressWorker::waveLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&ClusterLocalSetThisNodeIpAddressWorker::waveLinearSequencerFailedStep)
    };

    WaveLinearSequencerContext *pWaveLinearSequencerContext = new WaveLinearSequencerContext (pClusterLocalSetThisNodeIpAddressMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pWaveLinearSequencerContext->holdAll ();
    pWaveLinearSequencerContext->start ();
}

void ClusterLocalSetThisNodeIpAddressWorker::setThisNodeIpAddressValidateStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "ClusterLocalSetThisNodeIpAddressWorker::setThisNodeIpAddressValidateStep : Entering ...");

    ClusterLocalSetThisNodeIpAddressMessage *pClusterLocalSetThisNodeIpAddressMessage = reinterpret_cast<ClusterLocalSetThisNodeIpAddressMessage *> (pWaveLinearSequencerContext->getPWaveMessage ());
    string                                   ipAddress                                = pClusterLocalSetThisNodeIpAddressMessage->getIpAddress ();
    ResourceId                               status                                   = WAVE_MESSAGE_SUCCESS;

    if (true != (FrameworkToolKit::isIpAddressValid (ipAddress)))
    {
        status = CLUSTER_LOCAL_SET_THIS_NODE_IP_ADDRESS_STATUS_INVALID_IP_ADDRESS;
    }

    pWaveLinearSequencerContext->executeNextStep (status);
}

void ClusterLocalSetThisNodeIpAddressWorker::setThisNodeIpAddressUpdateWaveFrameworkObjectManagerStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "ClusterLocalSetThisNodeIpAddressWorker::setThisNodeIpAddressUpdateWaveFrameworkObjectManagerStep : Entering ...");

    ClusterLocalSetThisNodeIpAddressMessage *pClusterLocalSetThisNodeIpAddressMessage = reinterpret_cast<ClusterLocalSetThisNodeIpAddressMessage *> (pWaveLinearSequencerContext->getPWaveMessage ());
    string                                   ipAddress                                = pClusterLocalSetThisNodeIpAddressMessage->getIpAddress ();

    WaveFrameworkObjectManager::updateIpAddressForThisLocation (ipAddress);

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void ClusterLocalSetThisNodeIpAddressWorker::setThisNodeIpAddressUpdateThisWaveNodeStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "ClusterLocalSetThisNodeIpAddressWorker::setThisNodeIpAddressUpdateThisWaveNodeStep : Entering ...");

    ClusterLocalSetThisNodeIpAddressMessage *pClusterLocalSetThisNodeIpAddressMessage = reinterpret_cast<ClusterLocalSetThisNodeIpAddressMessage *> (pWaveLinearSequencerContext->getPWaveMessage ());
    string                                   ipAddress                                = pClusterLocalSetThisNodeIpAddressMessage->getIpAddress ();
    WaveManagedObject                       *pWaveManagedObject                       = NULL;
    ObjectId                                 thisWaveNodeObjectId                     = FrameworkToolKit::getThisWaveNodeObjectId ();
    WaveNode                                *pWaveNode                                = NULL;
    ResourceId                               status                                   = WAVE_MESSAGE_SUCCESS;

    pWaveManagedObject = queryManagedObject (thisWaveNodeObjectId);

    if (NULL == pWaveManagedObject)
    {
        trace (TRACE_LEVEL_FATAL, "ClusterLocalSetThisNodeIpAddressWorker::setThisNodeIpAddressUpdateThisWaveNodeStep : Cannot find the Local Wave Node.  Something went terribly wrong.");
        waveAssert (false, __FILE__, __LINE__);

        status = CLUSTER_LOCAL_SET_THIS_NODE_IP_ADDRESS_STATUS_CANNOT_FIND_LOCAL_NODE;
    }
    else
    {
        pWaveNode = dynamic_cast<WaveNode *> (pWaveManagedObject);

        if (NULL == pWaveNode)
        {
            trace (TRACE_LEVEL_FATAL, "ClusterLocalSetThisNodeIpAddressWorker::setThisNodeIpAddressUpdateThisWaveNodeStep : Cannot cast the Local Wave Node.  Something went terribly wrong.");
            waveAssert (false, __FILE__, __LINE__);

            status = CLUSTER_LOCAL_SET_THIS_NODE_IP_ADDRESS_STATUS_CANNOT_CAST_LOCAL_NODE;
        }
        else
        {
            updateWaveManagedObject (pWaveNode);

            pWaveNode->setIpAddress (ipAddress);
        }
        pWaveLinearSequencerContext->addManagedObjectForGarbageCollection (pWaveManagedObject);
    }

    pWaveLinearSequencerContext->executeNextStep (status);
}

}
