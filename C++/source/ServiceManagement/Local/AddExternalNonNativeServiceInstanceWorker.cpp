/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "ServiceManagement/Local/AddExternalNonNativeServiceInstanceWorker.h"
#include "ServiceManagement/Global/ExternalNonNativeServiceManagedObject.h"
#include "ServiceManagement/Local/ExternalNonNativeServiceInstanceManagedObject.h"
#include "ServiceManagement/Local/AddExternalNonNativeServiceInstanceContext.h"
#include "ServiceManagement/Local/AddExternalNonNativeServiceInstanceMessage.h"
#include "ServiceManagement/Local/ServiceManagementLocalTypes.h"
#include "Framework/ObjectModel/WaveManagedObjectToolKit.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContext.h"

namespace WaveNs
{

AddExternalNonNativeServiceInstanceWorker::AddExternalNonNativeServiceInstanceWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
    ExternalNonNativeServiceInstanceManagedObject externalNonNativeServiceInstanceManagedObject (pWaveObjectManager);

    externalNonNativeServiceInstanceManagedObject.setupOrm ();

    addManagedClass (ExternalNonNativeServiceInstanceManagedObject::getClassName (), this);

    addOperationMap (SERVCIE_MANAGEMENT_LOCAL_ADD_EXTERNAL_NON_NATIVE_SERVICE_INSTANCE, reinterpret_cast<WaveMessageHandler> (&AddExternalNonNativeServiceInstanceWorker::addExternalNonNativeServiceInstanceRequestHandler));
}

AddExternalNonNativeServiceInstanceWorker::~AddExternalNonNativeServiceInstanceWorker ()
{
}

WaveMessage *AddExternalNonNativeServiceInstanceWorker::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case SERVCIE_MANAGEMENT_LOCAL_ADD_EXTERNAL_NON_NATIVE_SERVICE_INSTANCE :
            pWaveMessage = new AddExternalNonNativeServiceInstanceMessage;
            break;

        default :
            pWaveMessage = NULL;
    }

    return (pWaveMessage);
}

WaveManagedObject *AddExternalNonNativeServiceInstanceWorker::createManagedObjectInstance (const string &managedClassName)
{
    WaveManagedObject *pWaveManagedObject = NULL;

    if ((ExternalNonNativeServiceInstanceManagedObject::getClassName ()) == managedClassName)
    {
        pWaveManagedObject = new ExternalNonNativeServiceInstanceManagedObject (getPWaveObjectManager ());
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, "AddExternalNonNativeServiceInstanceWorker::createManagedObjectInstance : Unknown Managed Class Name : " + managedClassName);
        waveAssert (false, __FILE__, __LINE__);
    }

    return (pWaveManagedObject);
}

void AddExternalNonNativeServiceInstanceWorker::addExternalNonNativeServiceInstanceRequestHandler (AddExternalNonNativeServiceInstanceMessage *pAddExternalNonNativeServiceInstanceMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
            {
                    reinterpret_cast<WaveLinearSequencerStep> (&AddExternalNonNativeServiceInstanceWorker::validateStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&AddExternalNonNativeServiceInstanceWorker::waveLinearSequencerStartTransactionStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&AddExternalNonNativeServiceInstanceWorker::createStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&AddExternalNonNativeServiceInstanceWorker::waveLinearSequencerCommitTransactionStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&AddExternalNonNativeServiceInstanceWorker::waveLinearSequencerSucceededStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&AddExternalNonNativeServiceInstanceWorker::waveLinearSequencerFailedStep),
            };

    AddExternalNonNativeServiceInstanceContext *pAddExternalNonNativeServiceInstanceContext = new AddExternalNonNativeServiceInstanceContext (pAddExternalNonNativeServiceInstanceMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pAddExternalNonNativeServiceInstanceContext->setApplicationName          (pAddExternalNonNativeServiceInstanceMessage->getApplicationName          ());
    pAddExternalNonNativeServiceInstanceContext->setApplicationInstanceNames (pAddExternalNonNativeServiceInstanceMessage->getApplicationInstanceNames ());

    pAddExternalNonNativeServiceInstanceContext->holdAll ();
    pAddExternalNonNativeServiceInstanceContext->start   ();
}

void AddExternalNonNativeServiceInstanceWorker::validateStep (AddExternalNonNativeServiceInstanceContext *pAddExternalNonNativeServiceInstanceContext)
{
    trace (TRACE_LEVEL_INFO, "AddExternalNonNativeServiceInstanceWorker::validateStep : Entering ...");

    const string &applicationName = pAddExternalNonNativeServiceInstanceContext->getApplicationName ();

    tracePrintf (TRACE_LEVEL_INFO, "AddExternalNonNativeServiceInstanceWorker::validateStep : Validating application : %s.", applicationName.c_str ());

    vector<WaveManagedObject *> *pQueryResults = querySynchronouslyByName (ExternalNonNativeServiceManagedObject::getClassName (), applicationName);

    waveAssert (NULL != pQueryResults, __FILE__, __LINE__);

          WaveManagedObject *pWaveManagedObject = NULL;
    const UI32               numberOfResults    = pQueryResults->size ();

    if (numberOfResults == 0)
    {
        WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector (pQueryResults);

        tracePrintf (TRACE_LEVEL_ERROR, "AddExternalNonNativeServiceInstanceWorker::validateStep : %s service does not exist.", applicationName.c_str ());

        pAddExternalNonNativeServiceInstanceContext->executeNextStep (WAVE_MESSAGE_ERROR);
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

    pAddExternalNonNativeServiceInstanceContext->setApplicationObjectId (applicationObjectId);

    const vector<string> &applicationInstanceNames = pAddExternalNonNativeServiceInstanceContext->getApplicationInstanceNames ();

    vector<string>::const_iterator element    = applicationInstanceNames.begin ();
    vector<string>::const_iterator endElement = applicationInstanceNames.end   ();

    bool validationSuccessful = true;

    WaveManagedObjectSynchronousQueryContext waveManagedObjectSynchronousQueryContext (ExternalNonNativeServiceInstanceManagedObject::getClassName ());

    while (element != endElement)
    {
        const string applicationInstanceName = *element;

        tracePrintf (TRACE_LEVEL_INFO, "AddExternalNonNativeServiceInstanceWorker::validateStep : Validating application Instance: %s.", applicationInstanceName.c_str ());

        waveManagedObjectSynchronousQueryContext.addOrAttribute (new AttributeString (applicationInstanceName, "name"));

        element++;
    }

    UI32 numberOfapplicationInstancesWithGiveName = 0;

    querySynchronouslyForCount (&waveManagedObjectSynchronousQueryContext, numberOfapplicationInstancesWithGiveName);

    if (0 != numberOfapplicationInstancesWithGiveName)
    {
        tracePrintf (TRACE_LEVEL_ERROR, "AddExternalNonNativeServiceInstanceWorker::validateStep : Validating application Instance failed : %d of the given instance names already exists.", numberOfapplicationInstancesWithGiveName);

        validationSuccessful = false;
    }

    if (validationSuccessful)
    {
        pAddExternalNonNativeServiceInstanceContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
    else
    {
        pAddExternalNonNativeServiceInstanceContext->executeNextStep (WAVE_MESSAGE_ERROR);
    }
}

void AddExternalNonNativeServiceInstanceWorker::createStep (AddExternalNonNativeServiceInstanceContext *pAddExternalNonNativeServiceInstanceContext)
{
    trace (TRACE_LEVEL_INFO, "AddExternalNonNativeServiceInstanceWorker::createStep : Entering ...");

    const vector<string> &applicationInstanceNames = pAddExternalNonNativeServiceInstanceContext->getApplicationInstanceNames ();
    const ObjectId        applicationObjectId      = pAddExternalNonNativeServiceInstanceContext->getApplicationObjectId ();

    vector<string>::const_iterator element    = applicationInstanceNames.begin ();
    vector<string>::const_iterator endElement = applicationInstanceNames.end   ();

    while (element != endElement)
    {
        const string applicationInstanceName = *element;

        ExternalNonNativeServiceInstanceManagedObject *pExternalNonNativeServiceInstanceManagedObject = new ExternalNonNativeServiceInstanceManagedObject (getPWaveObjectManager (), applicationInstanceName);

        pExternalNonNativeServiceInstanceManagedObject->setService (applicationObjectId);

        pAddExternalNonNativeServiceInstanceContext->addManagedObjectForGarbageCollection(pExternalNonNativeServiceInstanceManagedObject);

        element++;
    }

    pAddExternalNonNativeServiceInstanceContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

}
