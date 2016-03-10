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
                    reinterpret_cast<WaveLinearSequencerStep> (&RequestForShardOwnerWorker::setOutputStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&RequestForShardOwnerWorker::waveLinearSequencerSucceededStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&RequestForShardOwnerWorker::waveLinearSequencerFailedStep),
            };

    RequestForShardOwnerContext *pRequestForShardOwnerContext = new RequestForShardOwnerContext (pRequestForShardOwnerMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pRequestForShardOwnerContext->setResourceNames    (pRequestForShardOwnerMessage->getResourceNames     ());
    pRequestForShardOwnerContext->setShardingCategory (pRequestForShardOwnerMessage->getShardingCategory ());

    pRequestForShardOwnerContext->holdAll ();
    pRequestForShardOwnerContext->start   ();
}

void RequestForShardOwnerWorker::validateStep (RequestForShardOwnerContext *pRequestForShardOwnerContext)
{
    trace (TRACE_LEVEL_INFO, "RequestForShardOwnerWorker::validateStep : Entering ...");

    const vector<string> resourceNames    = pRequestForShardOwnerContext->getResourceNames    ();
    const ResourceId     shardingCategory = pRequestForShardOwnerContext->getShardingCategory ();

    if (0 == shardingCategory)
    {
        pRequestForShardOwnerContext->executeNextStep (WAVE_MESSAGE_ERROR);
        return;
    }

    const string     shardingCategoryToken    = FrameworkToolKit::localize (shardingCategory);
    const ObjectId   shardingCategoryObjectId = ShardingCapabilitiesToolKit::getShardableResourceCategoryObjectIdByToken (shardingCategoryToken);

    pRequestForShardOwnerContext->setShardingCategoryObjectId (shardingCategoryObjectId);

    if (ObjectId::NullObjectId == shardingCategoryObjectId)
    {
        trace (TRACE_LEVEL_INFO, "RequestForShardOwnerWorker::validateStep : Could not find sharding category.");

        pRequestForShardOwnerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;
    }

    map<string, ObjectId> &applicationInstanceObjectIdByResourceNameMap = pRequestForShardOwnerContext->getApplicationInstanceObjectIdByResourceNameMap ();

    ShardingCapabilitiesToolKit::getServiceInstanceObjectIdsByshardableResourceCategoryAndReosurces (shardingCategoryObjectId, resourceNames, applicationInstanceObjectIdByResourceNameMap);

    if ((resourceNames.size ()) == (applicationInstanceObjectIdByResourceNameMap.size ()))
    {
        tracePrintf (TRACE_LEVEL_INFO, "RequestForShardOwnerWorker::validateStep : Sharding owners already exists for all resources");
    }
    else
    {
        map<ObjectId, UI32> &shardOwnerCountsByapplicationInstanceObjectIdMap = pRequestForShardOwnerContext->getShardOwnerCountsByapplicationInstanceObjectIdMap ();

        ShardingCapabilitiesToolKit::getServiceInstanceObjectIdToShardCategoryOwnershipCountMap (shardingCategoryObjectId, shardOwnerCountsByapplicationInstanceObjectIdMap);
    }

    pRequestForShardOwnerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    return;
}

void RequestForShardOwnerWorker::createStep (RequestForShardOwnerContext *pRequestForShardOwnerContext)
{
    trace (TRACE_LEVEL_INFO, "RequestForShardOwnerWorker::createStep : Entering ...");

    const vector<string>         resourceNames                                = pRequestForShardOwnerContext->getResourceNames            ();
    const ObjectId               shardingCategoryObjectId                     = pRequestForShardOwnerContext->getShardingCategoryObjectId ();

          map<string, ObjectId> &applicationInstanceObjectIdByResourceNameMap = pRequestForShardOwnerContext->getApplicationInstanceObjectIdByResourceNameMap ();

    vector<string>::const_iterator element    = resourceNames.begin ();
    vector<string>::const_iterator endElement = resourceNames.end   ();

    while (endElement != element)
    {
        const string   resourceName                   = *element;
        const ObjectId applicationInstanceObjectId    = applicationInstanceObjectIdByResourceNameMap[resourceName];

        if (ObjectId::NullObjectId == applicationInstanceObjectId)
        {
            const ObjectId newApplicationInstanceObjectId = pRequestForShardOwnerContext->getApplicationInstanceObjectIdWithMinimalShardOwnerCount ();

            NetworkDeviceReadShardDataManagedObject *pNetworkDeviceReadShardDataManagedObject = new NetworkDeviceReadShardDataManagedObject (getPWaveObjectManager ());

            pNetworkDeviceReadShardDataManagedObject->setNetworkDeviceReadShardingCategory (shardingCategoryObjectId);
            pNetworkDeviceReadShardDataManagedObject->setServiceInstance                   (newApplicationInstanceObjectId);

            pNetworkDeviceReadShardDataManagedObject->setName (resourceName);

            applicationInstanceObjectIdByResourceNameMap[resourceName] = newApplicationInstanceObjectId;

            pRequestForShardOwnerContext->incrementShardOwnerCountForApplicationInstanceObjectId (newApplicationInstanceObjectId);

            pRequestForShardOwnerContext->addManagedObjectForGarbageCollection (pNetworkDeviceReadShardDataManagedObject);
        }

        element++;
    }

    pRequestForShardOwnerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    return;
}

void RequestForShardOwnerWorker::setOutputStep (RequestForShardOwnerContext *pRequestForShardOwnerContext)
{
    trace (TRACE_LEVEL_INFO, "RequestForShardOwnerWorker::setOutputStep : Entering ...");

    pRequestForShardOwnerContext->populateApplicationInstanceNameByObjectIdMap ();

    const vector<string>                  resourceNames                                = pRequestForShardOwnerContext->getResourceNames            ();

          map<string, ObjectId>          &applicationInstanceObjectIdByResourceNameMap = pRequestForShardOwnerContext->getApplicationInstanceObjectIdByResourceNameMap ();
          map<ObjectId, string>          &applicationInstanceNameByObjectIdMap         = pRequestForShardOwnerContext->getApplicationInstanceNameByObjectIdMap         ();

          vector<string>::const_iterator  element                                      = resourceNames.begin ();
          vector<string>::const_iterator  endElement                                   = resourceNames.end   ();

          vector<string>                  applicationInstanceNames;

    while (endElement != element)
    {
        const string   resourceName                   = *element;
        const ObjectId applicationInstanceObjectId    = applicationInstanceObjectIdByResourceNameMap[resourceName];
        const string   applicationInstanceName        = applicationInstanceNameByObjectIdMap[applicationInstanceObjectId];

        applicationInstanceNames.push_back (applicationInstanceName);

        element++;
    }

    RequestForShardOwnerMessage *pRequestForShardOwnerMessage = dynamic_cast<RequestForShardOwnerMessage *> (pRequestForShardOwnerContext->getPWaveMessage ());

    waveAssert (NULL != pRequestForShardOwnerMessage, __FILE__, __LINE__);

    pRequestForShardOwnerMessage->setApplicationInstanceNames (applicationInstanceNames);

    pRequestForShardOwnerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    return;
}


}
