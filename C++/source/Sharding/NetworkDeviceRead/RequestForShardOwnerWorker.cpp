/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Sharding/NetworkDeviceRead/RequestForShardOwnerWorker.h"

#include "Framework/Utils/FrameworkToolKit.h"
#include "Sharding/NetworkDeviceRead/NetworkDeviceReadShardDataManagedObject.h"
#include "Sharding/NetworkDeviceRead/NetworkDeviceReadShardingTypes.h"
#include "Sharding/NetworkDeviceRead/RequestForShardOwnerContext.h"
#include "Sharding/NetworkDeviceRead/RequestForShardOwnerMessage.h"
#include "Sharding/ShardingCapabilitiesToolKit.h"

namespace WaveNs
{

RequestForShardOwnerWorker::RequestForShardOwnerWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
    addOperationMap (NETWORK_DEVICE_READ_SHARDING_REQUEST_FOR_SHARD_OWNER, reinterpret_cast<WaveMessageHandler> (&RequestForShardOwnerWorker::requestForShardOwnerRequestHandler));
}

RequestForShardOwnerWorker::~RequestForShardOwnerWorker ()
{
}

WaveMessage *RequestForShardOwnerWorker::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case NETWORK_DEVICE_READ_SHARDING_REQUEST_FOR_SHARD_OWNER :
            pWaveMessage = new RequestForShardOwnerMessage;
            break;

        default :
            pWaveMessage = NULL;
    }

    return (pWaveMessage);
}

void RequestForShardOwnerWorker::requestForShardOwnerRequestHandler (RequestForShardOwnerMessage *pRequestForShardOwnerMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
            {
                    reinterpret_cast<WaveLinearSequencerStep> (&RequestForShardOwnerWorker::validateStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&RequestForShardOwnerWorker::waveLinearSequencerStartTransactionStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&RequestForShardOwnerWorker::createStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&RequestForShardOwnerWorker::waveLinearSequencerCommitTransactionStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&RequestForShardOwnerWorker::waveLinearSequencerSucceededStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&RequestForShardOwnerWorker::waveLinearSequencerFailedStep),
            };

    RequestForShardOwnerContext *pRequestForShardOwnerContext = new RequestForShardOwnerContext (pRequestForShardOwnerMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pRequestForShardOwnerContext->setResourceName     (pRequestForShardOwnerMessage->getResourceName     ());
    pRequestForShardOwnerContext->setShardingCategory (pRequestForShardOwnerMessage->getShardingCategory ());

    pRequestForShardOwnerContext->holdAll ();
    pRequestForShardOwnerContext->start   ();
}

void RequestForShardOwnerWorker::validateStep (RequestForShardOwnerContext *pRequestForShardOwnerContext)
{
    trace (TRACE_LEVEL_INFO, "RequestForShardOwnerWorker::validateStep : Entering ...");

    const string     resourceName             = pRequestForShardOwnerContext->getResourceName     ();
    const ResourceId shardingCategory         = pRequestForShardOwnerContext->getShardingCategory ();

    if (0 == shardingCategory)
    {
        pRequestForShardOwnerContext->executeNextStep (WAVE_MESSAGE_ERROR);
        return;
    }

    const string     shardingCategoryToken    = FrameworkToolKit::localize (shardingCategory);
    const ObjectId   shardingCategoryObjectId = ShardingCapabilitiesToolKit::getShardableResourceCategoryObjectIdByToken (shardingCategoryToken);

    pRequestForShardOwnerContext->setShardingCategoryObjectId (shardingCategoryObjectId);

    tracePrintf (TRACE_LEVEL_INFO, true, false, "RequestForShardOwnerWorker::validateStep : %s : %s : %s", resourceName.c_str (), shardingCategoryToken.c_str (), (shardingCategoryObjectId.toString ()).c_str ());

    if (ObjectId::NullObjectId == shardingCategoryObjectId)
    {
        trace (TRACE_LEVEL_INFO, "RequestForShardOwnerWorker::validateStep : Could not find sharding category.");

        pRequestForShardOwnerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;
    }

    const ObjectId applicationInstanceObjectId = ShardingCapabilitiesToolKit::getServiceInstanceObjectIdByshardableResourceCategoryAndReosurce (shardingCategoryObjectId, resourceName);

    if (ObjectId::NullObjectId != applicationInstanceObjectId)
    {
        tracePrintf (TRACE_LEVEL_INFO, "RequestForShardOwnerWorker::validateStep : Sharding owner already exists : %s", (applicationInstanceObjectId.toString ()).c_str ());

        WaveManagedObject *pWaveManagedObject = queryManagedObject (applicationInstanceObjectId);

        waveAssert (NULL != pWaveManagedObject, __FILE__, __LINE__);

        tracePrintf (TRACE_LEVEL_INFO, "RequestForShardOwnerWorker::validateStep : Sharding owner already existing application instance name : %s", (pWaveManagedObject->getName ()).c_str ());

        pRequestForShardOwnerContext->setApplicationInstanceName     (pWaveManagedObject->getName ());
        pRequestForShardOwnerContext->setApplicationInstanceObjectId (pWaveManagedObject->getObjectId ());

        pRequestForShardOwnerContext->addManagedObjectForGarbageCollection (pWaveManagedObject);

        RequestForShardOwnerMessage *pRequestForShardOwnerMessage = dynamic_cast<RequestForShardOwnerMessage *> (pRequestForShardOwnerContext->getPWaveMessage ());

        pRequestForShardOwnerMessage->setApplicationInstanceName (pRequestForShardOwnerContext->getApplicationInstanceName ());

        pRequestForShardOwnerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;
    }
    else
    {
        const ObjectId newApplicationInstanceObjectId = ShardingCapabilitiesToolKit::getServiceInstanceObjectIdWithMinimalShardCategoryOwnership (shardingCategoryObjectId);

        pRequestForShardOwnerContext->setNewApplicationInstanceObjectId (newApplicationInstanceObjectId);
    }

    pRequestForShardOwnerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    return;
}

void RequestForShardOwnerWorker::createStep (RequestForShardOwnerContext *pRequestForShardOwnerContext)
{
    trace (TRACE_LEVEL_INFO, "RequestForShardOwnerWorker::createStep : Entering ...");

    const ObjectId applicationInstanceObjectId = pRequestForShardOwnerContext->getApplicationInstanceObjectId ();

    if (ObjectId::NullObjectId != applicationInstanceObjectId)
    {
        pRequestForShardOwnerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;
    }

    const string     resourceName             = pRequestForShardOwnerContext->getResourceName             ();
    const ObjectId   shardingCategoryObjectId = pRequestForShardOwnerContext->getShardingCategoryObjectId ();

    const ObjectId   newApplicationInstanceObjectId = pRequestForShardOwnerContext->getNewApplicationInstanceObjectId ();

    NetworkDeviceReadShardDataManagedObject *pNetworkDeviceReadShardDataManagedObject = new NetworkDeviceReadShardDataManagedObject (getPWaveObjectManager ());

    pNetworkDeviceReadShardDataManagedObject->setNetworkDeviceReadShardingCategory (shardingCategoryObjectId);
    pNetworkDeviceReadShardDataManagedObject->setServiceInstance                   (newApplicationInstanceObjectId);

    pNetworkDeviceReadShardDataManagedObject->setName (resourceName);

    WaveManagedObject *pWaveManagedObject = queryManagedObject (newApplicationInstanceObjectId);

    waveAssert (NULL != pWaveManagedObject, __FILE__, __LINE__);

    tracePrintf (TRACE_LEVEL_INFO, "RequestForShardOwnerWorker::createStep : New Sharding owner application instance name : %s", (pWaveManagedObject->getName ()).c_str ());

    pRequestForShardOwnerContext->setApplicationInstanceName     (pWaveManagedObject->getName ());
    pRequestForShardOwnerContext->setApplicationInstanceObjectId (pWaveManagedObject->getObjectId ());

    pRequestForShardOwnerContext->addManagedObjectForGarbageCollection (pWaveManagedObject);

    RequestForShardOwnerMessage *pRequestForShardOwnerMessage = dynamic_cast<RequestForShardOwnerMessage *> (pRequestForShardOwnerContext->getPWaveMessage ());

    pRequestForShardOwnerMessage->setApplicationInstanceName (pRequestForShardOwnerContext->getApplicationInstanceName ());

    pRequestForShardOwnerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    return;
}

}
