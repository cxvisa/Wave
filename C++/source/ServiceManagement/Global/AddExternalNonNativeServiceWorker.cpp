/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "ServiceManagement/Global/AddExternalNonNativeServiceWorker.h"
#include "ServiceManagement/Global/AddExternalNonNativeServiceContext.h"
#include "ServiceManagement/Global/AddExternalNonNativeServiceMessage.h"
#include "ServiceManagement/Global/ServiceManagementTypes.h"

namespace WaveNs
{

AddExternalNonNativeServiceWorker::AddExternalNonNativeServiceWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
    addOperationMap (SERVCIE_MANAGEMENT_ADD_EXTERNAL_NON_NATIVE_SERVICE, reinterpret_cast<WaveMessageHandler> (&AddExternalNonNativeServiceWorker::addExternalNonNativeServiceRequestHandler));
}

AddExternalNonNativeServiceWorker::~AddExternalNonNativeServiceWorker ()
{
}

void AddExternalNonNativeServiceWorker::addExternalNonNativeServiceRequestHandler (AddExternalNonNativeServiceMessage *pAddExternalNonNativeServiceMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
            {
                    reinterpret_cast<WaveLinearSequencerStep> (&AddExternalNonNativeServiceWorker::validateStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&AddExternalNonNativeServiceWorker::waveLinearSequencerStartTransactionStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&AddExternalNonNativeServiceWorker::createStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&AddExternalNonNativeServiceWorker::waveLinearSequencerCommitTransactionStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&AddExternalNonNativeServiceWorker::waveSynchronousLinearSequencerSucceededStep),
                    reinterpret_cast<WaveLinearSequencerStep> (&AddExternalNonNativeServiceWorker::waveSynchronousLinearSequencerFailedStep),
            };

    AddExternalNonNativeServiceContext *pAddExternalNonNativeServiceContext = new AddExternalNonNativeServiceContext (pAddExternalNonNativeServiceMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pAddExternalNonNativeServiceContext->holdAll ();
    pAddExternalNonNativeServiceContext->start   ();
}

void AddExternalNonNativeServiceWorker::validateStep (AddExternalNonNativeServiceContext *pAddExternalNonNativeServiceContext)
{
    trace (TRACE_LEVEL_INFO, "AddExternalNonNativeServiceWorker::validateStep : Entering ...");

    pAddExternalNonNativeServiceContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void AddExternalNonNativeServiceWorker::createStep (AddExternalNonNativeServiceContext *pAddExternalNonNativeServiceContext)
{
    trace (TRACE_LEVEL_INFO, "AddExternalNonNativeServiceWorker::createStep : Entering ...");

    pAddExternalNonNativeServiceContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

}
