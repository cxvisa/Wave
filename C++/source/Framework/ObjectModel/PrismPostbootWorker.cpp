/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Amit Agrawal                                                 *
 ***************************************************************************/

#include "Framework/ObjectModel/PrismPostbootWorker.h"
#include "Framework/Postboot/PrismPostbootAgent.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForPostbootPhase.h"
#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"

namespace WaveNs
{

PrismPostbootWorker::PrismPostbootWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
    addOperationMap (WAVE_OBJECT_MANAGER_POSTBOOT, reinterpret_cast<WaveMessageHandler> (&PrismPostbootWorker::postbootHandler));
}

PrismPostbootWorker::~PrismPostbootWorker ()
{
}

void PrismPostbootWorker::postbootHandler (PrismPostbootObjectManagerMessage *pPrismPostbootObjectManagerMessage)
{
    PrismLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<PrismLinearSequencerStep> (&PrismPostbootWorker::postbootBootWorkersStep),
        reinterpret_cast<PrismLinearSequencerStep> (&PrismPostbootWorker::postbootBootSelfStep),
        reinterpret_cast<PrismLinearSequencerStep> (&PrismPostbootWorker::prismLinearSequencerSucceededStep),
        reinterpret_cast<PrismLinearSequencerStep> (&PrismPostbootWorker::prismLinearSequencerFailedStep)
    };

    PrismLinearSequencerContext *pPrismLinearSequencerContext = new PrismLinearSequencerContext (pPrismPostbootObjectManagerMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pPrismLinearSequencerContext->start ();
}

void PrismPostbootWorker::postbootBootWorkersStep (PrismLinearSequencerContext *pPrismLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "PrismPostbootWorker::postbootBootWorkersStep : Entering ...");

    WaveObjectManager                   *postbootWaveObjectManager = getPWaveObjectManager();
    vector<WaveWorker *>                waveWorkers = postbootWaveObjectManager->getWorkers();
    UI32                                numberOfWorkers = waveWorkers.size ();
    UI32                                i = 0;
    PrismPostbootObjectManagerMessage   *pPrismPostbootObjectManagerMessage;

    ++(*pPrismLinearSequencerContext);

    for (i = 0; i < numberOfWorkers; i++)
    {
        WaveAsynchronousContextForPostbootPhase *pWaveAsynchronousContextForPostbootPhase = new WaveAsynchronousContextForPostbootPhase (this, reinterpret_cast<PrismAsynchronousCallback> (&PrismPostbootWorker::postbootBootWorkersStepCallback), pPrismLinearSequencerContext);
        pPrismPostbootObjectManagerMessage = reinterpret_cast<PrismPostbootObjectManagerMessage*> (pPrismLinearSequencerContext->getPWaveMessage());
        pWaveAsynchronousContextForPostbootPhase->setPassNum (pPrismPostbootObjectManagerMessage->getPassNum());
        pWaveAsynchronousContextForPostbootPhase->setPassName (pPrismPostbootObjectManagerMessage->getPassName());
        pWaveAsynchronousContextForPostbootPhase->setSlotNum (pPrismPostbootObjectManagerMessage->getSlotNum());
        pWaveAsynchronousContextForPostbootPhase->setRecoveryType (pPrismPostbootObjectManagerMessage->getRecoveryType());

        ++(*pPrismLinearSequencerContext);
        waveWorkers[i]->postboot (pWaveAsynchronousContextForPostbootPhase);
    }

    --(*pPrismLinearSequencerContext);
    pPrismLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void PrismPostbootWorker::postbootBootWorkersStepCallback (WaveAsynchronousContextForPostbootPhase *pWaveAsynchronousContextForPostbootPhase)
{
    trace (TRACE_LEVEL_DEVEL, "PrismPostbootWorker::postbootBootWorkersStepCallback : Entering ...");

    PrismLinearSequencerContext *pPrismLinearSequencerContext = reinterpret_cast<PrismLinearSequencerContext *> (pWaveAsynchronousContextForPostbootPhase->getPCallerContext ());
    ResourceId                 status                     = pWaveAsynchronousContextForPostbootPhase->getCompletionStatus ();

    --(*pPrismLinearSequencerContext);

    delete pWaveAsynchronousContextForPostbootPhase;

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, "PrismPostbootWorker::postbootBootWorkersStepCallback : Postbooting one worker failed.");
        prismAssert (false, __FILE__, __LINE__);
    }

    pPrismLinearSequencerContext->executeNextStep (status);
}

void PrismPostbootWorker::postbootBootSelfStep (PrismLinearSequencerContext *pPrismLinearSequencerContext)
{
    PrismPostbootObjectManagerMessage   *pPrismPostbootObjectManagerMessage;

    trace (TRACE_LEVEL_DEVEL, "PrismPostbootWorker::postbootBootSelfStep : Entering ...");

    WaveAsynchronousContextForPostbootPhase *pWaveAsynchronousContextForPostbootPhase = new WaveAsynchronousContextForPostbootPhase (this, reinterpret_cast<PrismAsynchronousCallback> (&PrismPostbootWorker::postbootBootSelfStepCallback), pPrismLinearSequencerContext);
    pPrismPostbootObjectManagerMessage = reinterpret_cast<PrismPostbootObjectManagerMessage*> (pPrismLinearSequencerContext->getPWaveMessage());
    pWaveAsynchronousContextForPostbootPhase->setPassNum (pPrismPostbootObjectManagerMessage->getPassNum());
    pWaveAsynchronousContextForPostbootPhase->setPassName (pPrismPostbootObjectManagerMessage->getPassName());
    pWaveAsynchronousContextForPostbootPhase->setSlotNum (pPrismPostbootObjectManagerMessage->getSlotNum());
    pWaveAsynchronousContextForPostbootPhase->setRecoveryType (pPrismPostbootObjectManagerMessage->getRecoveryType());

    WaveObjectManager   *postbootWaveObjectManager = getPWaveObjectManager();
    postbootWaveObjectManager->postboot (pWaveAsynchronousContextForPostbootPhase);
}

void PrismPostbootWorker::postbootBootSelfStepCallback (WaveAsynchronousContextForPostbootPhase *pWaveAsynchronousContextForPostbootPhase)
{
    trace (TRACE_LEVEL_DEVEL, "PrismPostbootWorker::postbootBootSelfStepCallback : Entering ...");

    PrismLinearSequencerContext *pPrismLinearSequencerContext = reinterpret_cast<PrismLinearSequencerContext *> (pWaveAsynchronousContextForPostbootPhase->getPCallerContext ());
    ResourceId                 status                     = pWaveAsynchronousContextForPostbootPhase->getCompletionStatus ();

    delete pWaveAsynchronousContextForPostbootPhase;
    pPrismLinearSequencerContext->executeNextStep (status);
}

}
