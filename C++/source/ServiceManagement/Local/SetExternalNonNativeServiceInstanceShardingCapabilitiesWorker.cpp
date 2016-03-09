/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "ServiceManagement/Local/SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker.h"
#include "ServiceManagement/Local/SetExternalNonNativeServiceInstanceShardingCapabilitiesMessage.h"
#include "ServiceManagement/Local/SetExternalNonNativeServiceInstanceShardingCapabilitiesContext.h"

namespace WaveNs
{

SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker::SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
}

SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker::~SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker ()
{
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

    pSetExternalNonNativeServiceInstanceShardingCapabilitiesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker::setStep (SetExternalNonNativeServiceInstanceShardingCapabilitiesContext *pSetExternalNonNativeServiceInstanceShardingCapabilitiesContext)
{
    trace (TRACE_LEVEL_INFO, "SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker::setStep : Entering ...");

    pSetExternalNonNativeServiceInstanceShardingCapabilitiesContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

}
