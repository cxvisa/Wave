/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "ServiceManagement/Global/AddExternalNonNativeServiceWorker.h"
#include "ServiceManagement/Global/ExternalNonNativeServiceManagedObject.h"
#include "ServiceManagement/Global/AddExternalNonNativeServiceContext.h"
#include "ServiceManagement/Global/AddExternalNonNativeServiceMessage.h"
#include "ServiceManagement/Global/ServiceManagementTypes.h"

namespace WaveNs
{

AddExternalNonNativeServiceWorker::AddExternalNonNativeServiceWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
    ExternalNonNativeServiceManagedObject externalNonNativeServiceManagedObject (pWaveObjectManager);

    externalNonNativeServiceManagedObject.setupOrm ();

    addManagedClass (ExternalNonNativeServiceManagedObject::getClassName (), this);

    addOperationMap (SERVCIE_MANAGEMENT_ADD_EXTERNAL_NON_NATIVE_SERVICE, reinterpret_cast<WaveMessageHandler> (&AddExternalNonNativeServiceWorker::addExternalNonNativeServiceRequestHandler));
}

AddExternalNonNativeServiceWorker::~AddExternalNonNativeServiceWorker ()
{
}

WaveMessage *AddExternalNonNativeServiceWorker::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case SERVCIE_MANAGEMENT_ADD_EXTERNAL_NON_NATIVE_SERVICE :
            pWaveMessage = new AddExternalNonNativeServiceMessage;
            break;

        default :
            pWaveMessage = NULL;
    }

    return (pWaveMessage);
}

WaveManagedObject *AddExternalNonNativeServiceWorker::createManagedObjectInstance (const string &managedClassName)
{
    WaveManagedObject *pWaveManagedObject = NULL;

    if ((ExternalNonNativeServiceManagedObject::getClassName ()) == managedClassName)
    {
        pWaveManagedObject = new ExternalNonNativeServiceManagedObject (getPWaveObjectManager ());
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, "AddExternalNonNativeServiceWorker::createManagedObjectInstance : Unknown Managed Class Name : " + managedClassName);
        waveAssert (false, __FILE__, __LINE__);
    }

    return (pWaveManagedObject);
}

void AddExternalNonNativeServiceWorker::addExternalNonNativeServiceRequestHandler (AddExternalNonNativeServiceMessage *pAddExternalNonNativeServiceMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
            {
                    reinterpret_cast<WaveLinearSequencerStep> (&AddExternalNonNativeServiceWorker::validateStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&AddExternalNonNativeServiceWorker::waveLinearSequencerStartTransactionStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&AddExternalNonNativeServiceWorker::createStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&AddExternalNonNativeServiceWorker::waveLinearSequencerCommitTransactionStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&AddExternalNonNativeServiceWorker::waveLinearSequencerSucceededStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&AddExternalNonNativeServiceWorker::waveLinearSequencerFailedStep),
            };

    AddExternalNonNativeServiceContext *pAddExternalNonNativeServiceContext = new AddExternalNonNativeServiceContext (pAddExternalNonNativeServiceMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pAddExternalNonNativeServiceContext->setApplicationNames (pAddExternalNonNativeServiceMessage->getApplicationNames ());

    pAddExternalNonNativeServiceContext->holdAll ();
    pAddExternalNonNativeServiceContext->start   ();
}

void AddExternalNonNativeServiceWorker::validateStep (AddExternalNonNativeServiceContext *pAddExternalNonNativeServiceContext)
{
    trace (TRACE_LEVEL_INFO, "AddExternalNonNativeServiceWorker::validateStep : Entering ...");

    const vector<string> &applicationNames = pAddExternalNonNativeServiceContext->getApplicationNames ();

    vector<string>::const_iterator element    = applicationNames.begin ();
    vector<string>::const_iterator endElement = applicationNames.end   ();

    bool validationSuccessful = true;

    while (element != endElement)
    {
        const string applicationName = *element;

        tracePrintf (TRACE_LEVEL_INFO, "AddExternalNonNativeServiceWorker::validateStep : Validating application : %s.", applicationName.c_str ());


        UI32 numberOfapplicationsWithGiveName = 0;

        querySynchronouslyForCountForManagedObjectByName (ExternalNonNativeServiceManagedObject::getClassName (), applicationName, numberOfapplicationsWithGiveName);

        if (0 != numberOfapplicationsWithGiveName)
        {
            tracePrintf (TRACE_LEVEL_ERROR, "AddExternalNonNativeServiceWorker::validateStep : Validating application failed : %s already exists.", applicationName.c_str ());

            validationSuccessful = false;
        }

        element++;
    }

    if (validationSuccessful)
    {
        pAddExternalNonNativeServiceContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
    else
    {
        pAddExternalNonNativeServiceContext->executeNextStep (WAVE_MESSAGE_ERROR);
    }
}

void AddExternalNonNativeServiceWorker::createStep (AddExternalNonNativeServiceContext *pAddExternalNonNativeServiceContext)
{
    trace (TRACE_LEVEL_INFO, "AddExternalNonNativeServiceWorker::createStep : Entering ...");

    const vector<string> &applicationNames = pAddExternalNonNativeServiceContext->getApplicationNames ();

    vector<string>::const_iterator element    = applicationNames.begin ();
    vector<string>::const_iterator endElement = applicationNames.end   ();

    while (element != endElement)
    {
        const string applicationName = *element;

        ExternalNonNativeServiceManagedObject *pExternalNonNativeServiceManagedObject = new ExternalNonNativeServiceManagedObject (getPWaveObjectManager (), applicationName);

        pAddExternalNonNativeServiceContext->addManagedObjectForGarbageCollection(pExternalNonNativeServiceManagedObject);

        element++;
    }

    pAddExternalNonNativeServiceContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

}
