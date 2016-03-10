/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "ServiceManagement/Local/SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker.h"

#include "ServiceManagement/Local/ServiceManagementLocalTypes.h"
#include "ServiceManagement/Local/SetExternalNonNativeServiceInstanceShardingCapabilitiesMessage.h"
#include "ServiceManagement/Local/SetExternalNonNativeServiceInstanceShardingCapabilitiesContext.h"
#include "ServiceManagement/Local/SetExternalNonNativeServiceInstanceShardingCapabilitiesMessage.h"

#include "Framework/Utils/FrameworkToolKit.h"
#include "ServiceManagement/Local/ExternalNonNativeServiceInstanceManagedObject.h"
#include "ServiceManagement/Local/ServiceInstanceToolKit.h"
#include "Sharding/ShardingCapabilitiesToolKit.h"
namespace WaveNs
{

SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker::SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
    addOperationMap (SERVCIE_MANAGEMENT_LOCAL_SET_EXTERNAL_NON_NATIVE_SERVICE_INSTANCE_SHARDING_CAPABILITIES, reinterpret_cast<WaveMessageHandler> (&SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker::setExternalNonNativeServiceInstanceShardingCapabilitiesRequestHandler));
}

SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker::~SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker ()
{
}

WaveMessage *SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case SERVCIE_MANAGEMENT_LOCAL_SET_EXTERNAL_NON_NATIVE_SERVICE_INSTANCE_SHARDING_CAPABILITIES :
            pWaveMessage = new SetExternalNonNativeServiceInstanceShardingCapabilitiesMessage;
            break;

        default :
            pWaveMessage = NULL;
    }

    return (pWaveMessage);
}

void SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker::setExternalNonNativeServiceInstanceShardingCapabilitiesRequestHandler (SetExternalNonNativeServiceInstanceShardingCapabilitiesMessage *pSetExternalNonNativeServiceInstanceShardingCapabilitiesMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
            {
                    reinterpret_cast<WaveLinearSequencerStep> (&SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker::validateStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker::waveLinearSequencerStartTransactionStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker::setStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker::waveLinearSequencerCommitTransactionStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker::waveLinearSequencerSucceededStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker::waveLinearSequencerFailedStep),
            };

    SetExternalNonNativeServiceInstanceShardingCapabilitiesContext *pSetExternalNonNativeServiceInstanceShardingCapabilitiesContext = new SetExternalNonNativeServiceInstanceShardingCapabilitiesContext (pSetExternalNonNativeServiceInstanceShardingCapabilitiesMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pSetExternalNonNativeServiceInstanceShardingCapabilitiesContext->setApplicationName         (pSetExternalNonNativeServiceInstanceShardingCapabilitiesMessage->getApplicationName         ());
    pSetExternalNonNativeServiceInstanceShardingCapabilitiesContext->setApplicationInstanceName (pSetExternalNonNativeServiceInstanceShardingCapabilitiesMessage->getApplicationInstanceName ());
    pSetExternalNonNativeServiceInstanceShardingCapabilitiesContext->setShardingCapabilities    (pSetExternalNonNativeServiceInstanceShardingCapabilitiesMessage->getShardingCapabilities    ());

    pSetExternalNonNativeServiceInstanceShardingCapabilitiesContext->holdAll ();
    pSetExternalNonNativeServiceInstanceShardingCapabilitiesContext->start   ();
}

void SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker::validateStep (SetExternalNonNativeServiceInstanceShardingCapabilitiesContext *pSetExternalNonNativeServiceInstanceShardingCapabilitiesContext)
{
    trace (TRACE_LEVEL_INFO, "SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker::validateStep : Entering ...");

    const string applicationName                  = pSetExternalNonNativeServiceInstanceShardingCapabilitiesContext->getApplicationName         ();
    const string applicationInstanceName          = pSetExternalNonNativeServiceInstanceShardingCapabilitiesContext->getApplicationInstanceName ();
    const vector<ResourceId> shardingCapabilities = pSetExternalNonNativeServiceInstanceShardingCapabilitiesContext->getShardingCapabilities    ();

    tracePrintf (TRACE_LEVEL_INFO, true, false, "SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker::validateStep : Application : Application Instance - %s:%s", applicationName.c_str (), applicationInstanceName.c_str ());

          ExternalNonNativeServiceInstanceManagedObject *pExternalNonNativeServiceInstanceManagedObject = ServiceInstanceToolKit::getServiceInstanceByName (applicationInstanceName);

    if (NULL == pExternalNonNativeServiceInstanceManagedObject)
    {
        tracePrintf (TRACE_LEVEL_ERROR, "SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker::validateStep : Failed to obtain ExternalNonNativeServiceInstanceManagedObject for %s", applicationInstanceName.c_str ());

        pSetExternalNonNativeServiceInstanceShardingCapabilitiesContext->executeNextStep (WAVE_MESSAGE_ERROR);
        return;
    }
    else
    {
        pSetExternalNonNativeServiceInstanceShardingCapabilitiesContext->setPExternalNonNativeServiceInstanceManagedObject (pExternalNonNativeServiceInstanceManagedObject);

        pSetExternalNonNativeServiceInstanceShardingCapabilitiesContext->addManagedObjectForGarbageCollection (pExternalNonNativeServiceInstanceManagedObject);
    }

    vector<ResourceId>::const_iterator element                      = shardingCapabilities.begin();
    vector<ResourceId>::const_iterator endElement                   = shardingCapabilities.end  ();
    vector<ObjectId>                   shardingCapabilityObjectIds;

    while (endElement != element)
    {
        if (0 == *element)
        {
            pSetExternalNonNativeServiceInstanceShardingCapabilitiesContext->executeNextStep (WAVE_MESSAGE_ERROR);
            return;
        }

        const string   token                    = FrameworkToolKit::localize (*element);
              ObjectId shardingCategoryObjectId = ShardingCapabilitiesToolKit::getShardableResourceCategoryObjectIdByToken (token);

        tracePrintf (TRACE_LEVEL_INFO, "SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker::validateStep : Token : %s", token.c_str ());

        ShardingCapabilitiesToolKit::getServiceInstanceObjectIdsForShardableResourceCategory (shardingCategoryObjectId);

        if (ObjectId::NullObjectId == shardingCategoryObjectId)
        {
            tracePrintf (TRACE_LEVEL_ERROR, "SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker::validateStep : Failed to obtain object id for token : %s", token.c_str ());

            pSetExternalNonNativeServiceInstanceShardingCapabilitiesContext->executeNextStep (WAVE_MESSAGE_ERROR);
            return;
        }
        else
        {
            shardingCapabilityObjectIds.push_back (shardingCategoryObjectId);
        }

        element++;
    }

    pSetExternalNonNativeServiceInstanceShardingCapabilitiesContext->setShardingCapabilityObjectIds (shardingCapabilityObjectIds);

    pSetExternalNonNativeServiceInstanceShardingCapabilitiesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker::setStep (SetExternalNonNativeServiceInstanceShardingCapabilitiesContext *pSetExternalNonNativeServiceInstanceShardingCapabilitiesContext)
{
    trace (TRACE_LEVEL_INFO, "SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker::setStep : Entering ...");

    const vector<ObjectId>                               shardingCapabilityObjectIds                    = pSetExternalNonNativeServiceInstanceShardingCapabilitiesContext->getShardingCapabilityObjectIds ();
          ExternalNonNativeServiceInstanceManagedObject *pExternalNonNativeServiceInstanceManagedObject = pSetExternalNonNativeServiceInstanceShardingCapabilitiesContext->getPExternalNonNativeServiceInstanceManagedObject ();

    pExternalNonNativeServiceInstanceManagedObject->setShardingCapabilities (shardingCapabilityObjectIds);
    updateWaveManagedObject (pExternalNonNativeServiceInstanceManagedObject);

    pSetExternalNonNativeServiceInstanceShardingCapabilitiesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

}
