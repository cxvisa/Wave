/***************************************************************************
 *   Copyright (C) 2013      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Kuai Yu                                                      *
 ***************************************************************************/

#include "Framework/CliBlockManagement/CliBlockWorker.h"
#include "Framework/CliBlockManagement/CliBlockMessage.h"
#include "Framework/CliBlockManagement/CliBlockServiceIndependentMessage.h"
#include "Framework/CliBlockManagement/CliBlockManagementToolKit.h"
#include "Framework/Utils/PrismLinearSequencerContext.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Cluster/CentralClusterConfigObjectManager.h"
#include "Framework/CliBlockManagement/CliBlockType.h"

namespace WaveNs
{

CliBlockWorker::CliBlockWorker (CentralClusterConfigObjectManager *pCentralClusterConfigObjectManager)
    : WaveWorker (pCentralClusterConfigObjectManager)
{
    addOperationMap (CLI_BLOCK, reinterpret_cast<WaveMessageHandler> (&CliBlockWorker::cliBlockMessageHandler));
}

CliBlockWorker::~CliBlockWorker ()
{
}

WaveMessage *CliBlockWorker::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case CLI_BLOCK :
            pWaveMessage = new CliBlockMessage;
            break;

        default :
            pWaveMessage = NULL;
    }

    return (pWaveMessage);
}

void CliBlockWorker::cliBlockMessageHandler (CliBlockMessage *pCliBlockMessage)
{

    PrismLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<PrismLinearSequencerStep> (&CliBlockWorker::processCliBlockMessageForConnectedLocationStep),
        reinterpret_cast<PrismLinearSequencerStep> (&CliBlockWorker::prismLinearSequencerSucceededStep),
        reinterpret_cast<PrismLinearSequencerStep> (&CliBlockWorker::prismLinearSequencerFailedStep),
    };

    PrismLinearSequencerContext *pPrismLinearSequencerContext = new PrismLinearSequencerContext (pCliBlockMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pPrismLinearSequencerContext->start ();
}

void CliBlockWorker::processCliBlockMessageForConnectedLocationStepCallback (WaveSendToClusterContext *pWaveSendToClusterContext)
{

    PrismLinearSequencerContext *pPrismLinearSequencerContext = reinterpret_cast<PrismLinearSequencerContext *> (pWaveSendToClusterContext->getPCallerContext ());

    prismAssert (NULL != pPrismLinearSequencerContext, __FILE__, __LINE__);

    ResourceId  sendToClusterCompletionStatus   = pWaveSendToClusterContext->getCompletionStatus ();

    delete (pWaveSendToClusterContext->getPWaveMessageForPhase1 ());
    delete (pWaveSendToClusterContext);

    trace (TRACE_LEVEL_DEBUG, "CliBlockWorker::processCliBlockMessageForConnectedLocationStep : Finish.");

    pPrismLinearSequencerContext->executeNextStep (sendToClusterCompletionStatus);

}

void CliBlockWorker::processCliBlockMessageForConnectedLocationStep (PrismLinearSequencerContext *pPrismLinearSequencerContext)
{

    trace (TRACE_LEVEL_INFO, "CliBlockWorker::processCliBlockMessageForConnectedLocationStep : Entering ...");

    CliBlockMessage *pCliBlockMessage = reinterpret_cast<CliBlockMessage *> (pPrismLinearSequencerContext->getPWaveMessage ());

    CliBlockServiceIndependentMessage *pCliBlockServiceIndependentMessage1 = new CliBlockServiceIndependentMessage (*pCliBlockMessage);
 
    WaveSendToClusterContext *pWaveSendToClusterContext = new WaveSendToClusterContext (this, reinterpret_cast<PrismAsynchronousCallback> (&CliBlockWorker::processCliBlockMessageForConnectedLocationStepCallback), pPrismLinearSequencerContext);

    prismAssert (NULL != pWaveSendToClusterContext, __FILE__, __LINE__);


    pWaveSendToClusterContext->setPWaveMessageForPhase1 (pCliBlockServiceIndependentMessage1);
    pWaveSendToClusterContext->setTreatFailureOnFailingOverAsSuccessFlag (true);

    sendToWaveCluster (pWaveSendToClusterContext);

}

}
