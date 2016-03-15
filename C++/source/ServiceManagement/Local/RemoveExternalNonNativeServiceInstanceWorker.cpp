/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "ServiceManagement/Local/RemoveExternalNonNativeServiceInstanceWorker.h"
#include "ServiceManagement/Global/ExternalNonNativeServiceManagedObject.h"
#include "ServiceManagement/Local/ExternalNonNativeServiceInstanceManagedObject.h"
#include "ServiceManagement/Local/RemoveExternalNonNativeServiceInstanceContext.h"
#include "ServiceManagement/Local/RemoveExternalNonNativeServiceInstanceMessage.h"
#include "ServiceManagement/Local/ServiceManagementLocalTypes.h"
#include "Framework/ObjectModel/WaveManagedObjectToolKit.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContext.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContextForDeletion.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Sharding/NetworkDeviceRead/NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage.h"

namespace WaveNs
{

RemoveExternalNonNativeServiceInstanceWorker::RemoveExternalNonNativeServiceInstanceWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
    addOperationMap (SERVCIE_MANAGEMENT_LOCAL_REMOVE_EXTERNAL_NON_NATIVE_SERVICE_INSTANCE, reinterpret_cast<WaveMessageHandler> (&RemoveExternalNonNativeServiceInstanceWorker::addExternalNonNativeServiceInstanceRequestHandler));
}

RemoveExternalNonNativeServiceInstanceWorker::~RemoveExternalNonNativeServiceInstanceWorker ()
{
}

WaveMessage *RemoveExternalNonNativeServiceInstanceWorker::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case SERVCIE_MANAGEMENT_LOCAL_REMOVE_EXTERNAL_NON_NATIVE_SERVICE_INSTANCE :
            pWaveMessage = new RemoveExternalNonNativeServiceInstanceMessage;
            break;

        default :
            pWaveMessage = NULL;
    }

    return (pWaveMessage);
}

void RemoveExternalNonNativeServiceInstanceWorker::addExternalNonNativeServiceInstanceRequestHandler (RemoveExternalNonNativeServiceInstanceMessage *pRemoveExternalNonNativeServiceInstanceMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
            {
                    reinterpret_cast<WaveLinearSequencerStep> (&RemoveExternalNonNativeServiceInstanceWorker::validateStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&RemoveExternalNonNativeServiceInstanceWorker::waveLinearSequencerStartTransactionStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&RemoveExternalNonNativeServiceInstanceWorker::deleteShardDataStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&RemoveExternalNonNativeServiceInstanceWorker::deleteStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&RemoveExternalNonNativeServiceInstanceWorker::waveLinearSequencerCommitTransactionStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&RemoveExternalNonNativeServiceInstanceWorker::waveLinearSequencerSucceededStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&RemoveExternalNonNativeServiceInstanceWorker::waveLinearSequencerFailedStep),
            };

    RemoveExternalNonNativeServiceInstanceContext *pRemoveExternalNonNativeServiceInstanceContext = new RemoveExternalNonNativeServiceInstanceContext (pRemoveExternalNonNativeServiceInstanceMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pRemoveExternalNonNativeServiceInstanceContext->setApplicationName          (pRemoveExternalNonNativeServiceInstanceMessage->getApplicationName          ());
    pRemoveExternalNonNativeServiceInstanceContext->setApplicationInstanceNames (pRemoveExternalNonNativeServiceInstanceMessage->getApplicationInstanceNames ());

    pRemoveExternalNonNativeServiceInstanceContext->holdAll ();
    pRemoveExternalNonNativeServiceInstanceContext->start   ();
}

void RemoveExternalNonNativeServiceInstanceWorker::validateStep (RemoveExternalNonNativeServiceInstanceContext *pRemoveExternalNonNativeServiceInstanceContext)
{
    trace (TRACE_LEVEL_INFO, "RemoveExternalNonNativeServiceInstanceWorker::validateStep : Entering ...");

    const string &applicationName = pRemoveExternalNonNativeServiceInstanceContext->getApplicationName ();

    tracePrintf (TRACE_LEVEL_INFO, "RemoveExternalNonNativeServiceInstanceWorker::validateStep : Validating application : %s.", applicationName.c_str ());

    vector<WaveManagedObject *> *pQueryResults = querySynchronouslyByName (ExternalNonNativeServiceManagedObject::getClassName (), applicationName);

    waveAssert (NULL != pQueryResults, __FILE__, __LINE__);

          WaveManagedObject *pWaveManagedObject = NULL;
    const UI32               numberOfResults    = pQueryResults->size ();

    if (numberOfResults == 0)
    {
        WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector (pQueryResults);

        tracePrintf (TRACE_LEVEL_ERROR, "RemoveExternalNonNativeServiceInstanceWorker::validateStep : %s service does not exist.", applicationName.c_str ());

        pRemoveExternalNonNativeServiceInstanceContext->executeNextStep (WAVE_MESSAGE_ERROR);
        return;
    }
    else if (1 < numberOfResults)
    {
        WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector (pQueryResults);

        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        pWaveManagedObject = (*pQueryResults)[0];
    }

    waveAssert (NULL != pWaveManagedObject, __FILE__, __LINE__);

    ExternalNonNativeServiceManagedObject *pExternalNonNativeServiceManagedObject = dynamic_cast<ExternalNonNativeServiceManagedObject *> (pWaveManagedObject);

    waveAssert (NULL != pExternalNonNativeServiceManagedObject, __FILE__, __LINE__);

    ObjectId applicationObjectId = pExternalNonNativeServiceManagedObject->getObjectId ();

    WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector (pQueryResults);

    pRemoveExternalNonNativeServiceInstanceContext->setApplicationObjectId (applicationObjectId);

    const vector<string> &applicationInstanceNames = pRemoveExternalNonNativeServiceInstanceContext->getApplicationInstanceNames ();

    vector<string>::const_iterator element    = applicationInstanceNames.begin ();
    vector<string>::const_iterator endElement = applicationInstanceNames.end   ();

    bool validationSuccessful = true;

    WaveManagedObjectSynchronousQueryContext waveManagedObjectSynchronousQueryContext (ExternalNonNativeServiceInstanceManagedObject::getClassName ());

    while (element != endElement)
    {
        const string applicationInstanceName = *element;

        tracePrintf (TRACE_LEVEL_INFO, "RemoveExternalNonNativeServiceInstanceWorker::validateStep : Validating application Instance: %s.", applicationInstanceName.c_str ());

        waveManagedObjectSynchronousQueryContext.addOrAttribute (new AttributeString (applicationInstanceName, "name"));

        element++;
    }

    UI32 numberOfapplicationInstancesWithGiveName = 0;

    querySynchronouslyForCount (&waveManagedObjectSynchronousQueryContext, numberOfapplicationInstancesWithGiveName);

    if (0 == numberOfapplicationInstancesWithGiveName)
    {
        tracePrintf (TRACE_LEVEL_ERROR, "RemoveExternalNonNativeServiceInstanceWorker::validateStep : Validating application Instance failed.  Not even a single instance name exists.");

        validationSuccessful = false;
    }

    if (validationSuccessful)
    {
        pRemoveExternalNonNativeServiceInstanceContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
    else
    {
        pRemoveExternalNonNativeServiceInstanceContext->executeNextStep (WAVE_MESSAGE_ERROR);
    }
}

void RemoveExternalNonNativeServiceInstanceWorker::deleteShardDataStep (RemoveExternalNonNativeServiceInstanceContext *pRemoveExternalNonNativeServiceInstanceContext)
{
    trace (TRACE_LEVEL_INFO, "RemoveExternalNonNativeServiceInstanceWorker::deleteShardDataStep : Entering ...");

    const vector<string> &applicationInstanceNames = pRemoveExternalNonNativeServiceInstanceContext->getApplicationInstanceNames ();

    vector<string>::const_iterator element    = applicationInstanceNames.begin ();
    vector<string>::const_iterator endElement = applicationInstanceNames.end   ();

    WaveManagedObjectSynchronousQueryContext *pWaveManagedObjectSynchronousQueryContext = new WaveManagedObjectSynchronousQueryContext (ExternalNonNativeServiceInstanceManagedObject::getClassName ());

    pWaveManagedObjectSynchronousQueryContext->addSelectField ("name");

    while (element != endElement)
    {
        const string applicationInstanceName = *element;

        pWaveManagedObjectSynchronousQueryContext->addOrAttribute (new AttributeString (applicationInstanceName, "name"));

        element++;
    }

    vector<WaveManagedObject *> *pQueryResults = querySynchronously (pWaveManagedObjectSynchronousQueryContext);

    waveAssert (NULL != pQueryResults, __FILE__, __LINE__);

    const UI32 numberOfQueryResults = pQueryResults->size ();
          UI32 i                    = 0;


          vector<ObjectId> serviceInstanceObjectIds;

    for (i = 0; i < numberOfQueryResults; i++)
    {
        WaveManagedObject *pWaveManagedObject = (*pQueryResults)[i];

        waveAssert (NULL != pWaveManagedObject, __FILE__, __LINE__);

        const ObjectId objectId = pWaveManagedObject->getObjectId ();

        serviceInstanceObjectIds.push_back (objectId);
    }

    WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector (pQueryResults);

    NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage *pNetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage = new NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage (serviceInstanceObjectIds);

    WaveMessageStatus sendStatus = sendSynchronously (pNetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage);

    if (WAVE_MESSAGE_SUCCESS == sendStatus)
    {
        ResourceId completionStatus = pNetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage->getCompletionStatus ();

        delete pNetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage;

        if (WAVE_MESSAGE_SUCCESS != completionStatus)
        {
            trace (TRACE_LEVEL_INFO, "RemoveExternalNonNativeServiceInstanceWorker::deleteShardDataStep : Successfully deleted shard data.");
        }
        else
        {
            tracePrintf (TRACE_LEVEL_INFO, "RemoveExternalNonNativeServiceInstanceWorker::deleteShardDataStep : Failed to delete shard data : %s", FrameworkToolKit::localize (completionStatus));

            pRemoveExternalNonNativeServiceInstanceContext->executeNextStep (completionStatus);
            return;
        }
    }
    else
    {
        tracePrintf (TRACE_LEVEL_INFO, "RemoveExternalNonNativeServiceInstanceWorker::deleteShardDataStep : Failed to send Message : %s", FrameworkToolKit::localize (sendStatus));

        delete pNetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage;

        pRemoveExternalNonNativeServiceInstanceContext->executeNextStep (sendStatus);
        return;
    }

    pRemoveExternalNonNativeServiceInstanceContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    return;
}

void RemoveExternalNonNativeServiceInstanceWorker::deleteStep (RemoveExternalNonNativeServiceInstanceContext *pRemoveExternalNonNativeServiceInstanceContext)
{
    trace (TRACE_LEVEL_INFO, "RemoveExternalNonNativeServiceInstanceWorker::deleteStep : Entering ...");

    const vector<string> &applicationInstanceNames = pRemoveExternalNonNativeServiceInstanceContext->getApplicationInstanceNames ();
    //const ObjectId        applicationObjectId      = pRemoveExternalNonNativeServiceInstanceContext->getApplicationObjectId ();

    vector<string>::const_iterator element    = applicationInstanceNames.begin ();
    vector<string>::const_iterator endElement = applicationInstanceNames.end   ();

    WaveManagedObjectSynchronousQueryContextForDeletion *pWaveManagedObjectSynchronousQueryContextForDeletion = new WaveManagedObjectSynchronousQueryContextForDeletion (ExternalNonNativeServiceInstanceManagedObject::getClassName ());

    while (element != endElement)
    {
        const string applicationInstanceName = *element;

        pWaveManagedObjectSynchronousQueryContextForDeletion->addOrAttribute (new AttributeString (applicationInstanceName, "name"));

        element++;
    }

    deleteMultipleWaveManagedObjects (pWaveManagedObjectSynchronousQueryContextForDeletion);

    pRemoveExternalNonNativeServiceInstanceContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

}
