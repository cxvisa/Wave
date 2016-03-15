/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Sharding/NetworkDeviceRead/NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceWorker.h"
#include "Sharding/NetworkDeviceRead/NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceContext.h"
#include "Sharding/NetworkDeviceRead/NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage.h"
#include "Sharding/NetworkDeviceRead/NetworkDeviceReadShardingTypes.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContextForDeletion.h"
#include "ServiceManagement/Local/ExternalNonNativeServiceInstanceManagedObject.h"
#include "Sharding/NetworkDeviceRead/NetworkDeviceReadShardDataManagedObject.h"

namespace WaveNs
{

NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceWorker::NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
    addOperationMap (NETWORK_DEVICE_READ_SHARDING_DELETE_SHARD_DATA_FOR_SHARD_OWNER, reinterpret_cast<WaveMessageHandler> (&NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceWorker::deleteShardDataForExternalNonNativeServiceInstanceRequestHandler));
}

NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceWorker::~NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceWorker ()
{
}

WaveMessage *NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceWorker::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case NETWORK_DEVICE_READ_SHARDING_DELETE_SHARD_DATA_FOR_SHARD_OWNER :
            pWaveMessage = new NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage;
            break;

        default :
            pWaveMessage = NULL;
    }

    return (pWaveMessage);
}

void NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceWorker::deleteShardDataForExternalNonNativeServiceInstanceRequestHandler (NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage *pNetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
            {
                    reinterpret_cast<WaveLinearSequencerStep> (&NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceWorker::waveLinearSequencerStartTransactionStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceWorker::deleteStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceWorker::waveLinearSequencerCommitTransactionStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceWorker::waveLinearSequencerSucceededStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceWorker::waveLinearSequencerFailedStep),
            };

    NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceContext *pNetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceContext = new NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceContext (pNetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pNetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceContext->setServiceInstanceObjectIds (pNetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage->getServiceInstanceObjectIds ());

    pNetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceContext->holdAll ();
    pNetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceContext->start   ();
}

void NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceWorker::deleteStep (NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceContext *pNetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceContext)
{
    tracePrintf (TRACE_LEVEL_INFO, "NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceWorker::deleteStep : Entering ...");

    WaveManagedObjectSynchronousQueryContextForDeletion *pWaveManagedObjectSynchronousQueryContextForDeletion = new WaveManagedObjectSynchronousQueryContextForDeletion (NetworkDeviceReadShardDataManagedObject::getClassName ());

    vector<ObjectId> serviceInstanceObjectIds = pNetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceContext->getServiceInstanceObjectIds ();

    vector<ObjectId>::const_iterator element    = serviceInstanceObjectIds.begin ();
    vector<ObjectId>::const_iterator endElement = serviceInstanceObjectIds.end   ();

    while (endElement != element)
    {
        const ObjectId serviceInstanceObjectId = *element;

        pWaveManagedObjectSynchronousQueryContextForDeletion->addOrAttribute (new AttributeObjectIdAssociation (serviceInstanceObjectId, "serviceInstance", ExternalNonNativeServiceInstanceManagedObject::getClassName ()));

        element++;
    }

    deleteMultipleWaveManagedObjects (pWaveManagedObjectSynchronousQueryContextForDeletion);

    pNetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    return;
}

}
