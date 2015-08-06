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

    WaveLinearSequencerContext *pWaveLinearSequencerContext = new WaveLinearSequencerContext (pPrismPostbootObjectManagerMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pWaveLinearSequencerContext->start ();
}

void PrismPostbootWorker::postbootBootWorkersStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "PrismPostbootWorker::postbootBootWorkersStep : Entering ...");

    WaveObjectManager                   *postbootWaveObjectManager = getPWaveObjectManager();
    vector<WaveWorker *>                waveWorkers = postbootWaveObjectManager->getWorkers();
    UI32                                numberOfWorkers = waveWorkers.size ();
    UI32                                i = 0;
    PrismPostbootObjectManagerMessage   *pPrismPostbootObjectManagerMessage;

    ++(*pWaveLinearSequencerContext);

    for (i = 0; i < numberOfWorkers; i++)
    {
        WaveAsynchronousContextForPostbootPhase *pWaveAsynchronousContextForPostbootPhase = new WaveAsynchronousContextForPostbootPhase (this, reinterpret_cast<PrismAsynchronousCallback> (&PrismPostbootWorker::postbootBootWorkersStepCallback), pWaveLinearSequencerContext);
        pPrismPostbootObjectManagerMessage = reinterpret_cast<PrismPostbootObjectManagerMessage*> (pWaveLinearSequencerContext->getPWaveMessage());
        pWaveAsynchronousContextForPostbootPhase->setPassNum (pPrismPostbootObjectManagerMessage->getPassNum());
        pWaveAsynchronousContextForPostbootPhase->setPassName (pPrismPostbootObjectManagerMessage->getPassName());
        pWaveAsynchronousContextForPostbootPhase->setSlotNum (pPrismPostbootObjectManagerMessage->getSlotNum());
        pWaveAsynchronousContextForPostbootPhase->setRecoveryType (pPrismPostbootObjectManagerMessage->getRecoveryType());

        ++(*pWaveLinearSequencerContext);
        waveWorkers[i]->postboot (pWaveAsynchronousContextForPostbootPhase);
    }

    --(*pWaveLinearSequencerContext);
    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void PrismPostbootWorker::postbootBootWorkersStepCallback (WaveAsynchronousContextForPostbootPhase *pWaveAsynchronousContextForPostbootPhase)
{
    trace (TRACE_LEVEL_DEVEL, "PrismPostbootWorker::postbootBootWorkersStepCallback : Entering ...");

    WaveLinearSequencerContext *pWaveLinearSequencerContext = reinterpret_cast<WaveLinearSequencerContext *> (pWaveAsynchronousContextForPostbootPhase->getPCallerContext ());
    ResourceId                 status                     = pWaveAsynchronousContextForPostbootPhase->getCompletionStatus ();

    --(*pWaveLinearSequencerContext);

    delete pWaveAsynchronousContextForPostbootPhase;

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, "PrismPostbootWorker::postbootBootWorkersStepCallback : Postbooting one worker failed.");
        waveAssert (false, __FILE__, __LINE__);
    }

    pWaveLinearSequencerContext->executeNextStep (status);
}

void PrismPostbootWorker::postbootBootSelfStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    PrismPostbootObjectManagerMessage   *pPrismPostbootObjectManagerMessage;

    trace (TRACE_LEVEL_DEVEL, "PrismPostbootWorker::postbootBootSelfStep : Entering ...");

    WaveAsynchronousContextForPostbootPhase *pWaveAsynchronousContextForPostbootPhase = new WaveAsynchronousContextForPostbootPhase (this, reinterpret_cast<PrismAsynchronousCallback> (&PrismPostbootWorker::postbootBootSelfStepCallback), pWaveLinearSequencerContext);
    pPrismPostbootObjectManagerMessage = reinterpret_cast<PrismPostbootObjectManagerMessage*> (pWaveLinearSequencerContext->getPWaveMessage());
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

    WaveLinearSequencerContext *pWaveLinearSequencerContext = reinterpret_cast<WaveLinearSequencerContext *> (pWaveAsynchronousContextForPostbootPhase->getPCallerContext ());
    ResourceId                 status                     = pWaveAsynchronousContextForPostbootPhase->getCompletionStatus ();

    delete pWaveAsynchronousContextForPostbootPhase;
    pWaveLinearSequencerContext->executeNextStep (status);
}

}
