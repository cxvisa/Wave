/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Amit Agrawal                                                 *
 ***************************************************************************/

#include "Framework/ObjectModel/WavePostbootWorker.h"
#include "Framework/Postboot/WavePostbootAgent.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForPostbootPhase.h"
#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"

namespace WaveNs
{

WavePostbootWorker::WavePostbootWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
    addOperationMap (WAVE_OBJECT_MANAGER_POSTBOOT, reinterpret_cast<WaveMessageHandler> (&WavePostbootWorker::postbootHandler));
}

WavePostbootWorker::~WavePostbootWorker ()
{
}

void WavePostbootWorker::postbootHandler (WavePostbootObjectManagerMessage *pWavePostbootObjectManagerMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WavePostbootWorker::postbootBootWorkersStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WavePostbootWorker::postbootBootSelfStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WavePostbootWorker::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WavePostbootWorker::prismLinearSequencerFailedStep)
    };

    WaveLinearSequencerContext *pWaveLinearSequencerContext = new WaveLinearSequencerContext (pWavePostbootObjectManagerMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pWaveLinearSequencerContext->start ();
}

void WavePostbootWorker::postbootBootWorkersStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WavePostbootWorker::postbootBootWorkersStep : Entering ...");

    WaveObjectManager                   *postbootWaveObjectManager = getPWaveObjectManager();
    vector<WaveWorker *>                waveWorkers = postbootWaveObjectManager->getWorkers();
    UI32                                numberOfWorkers = waveWorkers.size ();
    UI32                                i = 0;
    WavePostbootObjectManagerMessage   *pWavePostbootObjectManagerMessage;

    ++(*pWaveLinearSequencerContext);

    for (i = 0; i < numberOfWorkers; i++)
    {
        WaveAsynchronousContextForPostbootPhase *pWaveAsynchronousContextForPostbootPhase = new WaveAsynchronousContextForPostbootPhase (this, reinterpret_cast<WaveAsynchronousCallback> (&WavePostbootWorker::postbootBootWorkersStepCallback), pWaveLinearSequencerContext);
        pWavePostbootObjectManagerMessage = reinterpret_cast<WavePostbootObjectManagerMessage*> (pWaveLinearSequencerContext->getPWaveMessage());
        pWaveAsynchronousContextForPostbootPhase->setPassNum (pWavePostbootObjectManagerMessage->getPassNum());
        pWaveAsynchronousContextForPostbootPhase->setPassName (pWavePostbootObjectManagerMessage->getPassName());
        pWaveAsynchronousContextForPostbootPhase->setSlotNum (pWavePostbootObjectManagerMessage->getSlotNum());
        pWaveAsynchronousContextForPostbootPhase->setRecoveryType (pWavePostbootObjectManagerMessage->getRecoveryType());

        ++(*pWaveLinearSequencerContext);
        waveWorkers[i]->postboot (pWaveAsynchronousContextForPostbootPhase);
    }

    --(*pWaveLinearSequencerContext);
    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WavePostbootWorker::postbootBootWorkersStepCallback (WaveAsynchronousContextForPostbootPhase *pWaveAsynchronousContextForPostbootPhase)
{
    trace (TRACE_LEVEL_DEVEL, "WavePostbootWorker::postbootBootWorkersStepCallback : Entering ...");

    WaveLinearSequencerContext *pWaveLinearSequencerContext = reinterpret_cast<WaveLinearSequencerContext *> (pWaveAsynchronousContextForPostbootPhase->getPCallerContext ());
    ResourceId                 status                     = pWaveAsynchronousContextForPostbootPhase->getCompletionStatus ();

    --(*pWaveLinearSequencerContext);

    delete pWaveAsynchronousContextForPostbootPhase;

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, "WavePostbootWorker::postbootBootWorkersStepCallback : Postbooting one worker failed.");
        waveAssert (false, __FILE__, __LINE__);
    }

    pWaveLinearSequencerContext->executeNextStep (status);
}

void WavePostbootWorker::postbootBootSelfStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    WavePostbootObjectManagerMessage   *pWavePostbootObjectManagerMessage;

    trace (TRACE_LEVEL_DEVEL, "WavePostbootWorker::postbootBootSelfStep : Entering ...");

    WaveAsynchronousContextForPostbootPhase *pWaveAsynchronousContextForPostbootPhase = new WaveAsynchronousContextForPostbootPhase (this, reinterpret_cast<WaveAsynchronousCallback> (&WavePostbootWorker::postbootBootSelfStepCallback), pWaveLinearSequencerContext);
    pWavePostbootObjectManagerMessage = reinterpret_cast<WavePostbootObjectManagerMessage*> (pWaveLinearSequencerContext->getPWaveMessage());
    pWaveAsynchronousContextForPostbootPhase->setPassNum (pWavePostbootObjectManagerMessage->getPassNum());
    pWaveAsynchronousContextForPostbootPhase->setPassName (pWavePostbootObjectManagerMessage->getPassName());
    pWaveAsynchronousContextForPostbootPhase->setSlotNum (pWavePostbootObjectManagerMessage->getSlotNum());
    pWaveAsynchronousContextForPostbootPhase->setRecoveryType (pWavePostbootObjectManagerMessage->getRecoveryType());

    WaveObjectManager   *postbootWaveObjectManager = getPWaveObjectManager();
    postbootWaveObjectManager->postboot (pWaveAsynchronousContextForPostbootPhase);
}

void WavePostbootWorker::postbootBootSelfStepCallback (WaveAsynchronousContextForPostbootPhase *pWaveAsynchronousContextForPostbootPhase)
{
    trace (TRACE_LEVEL_DEVEL, "WavePostbootWorker::postbootBootSelfStepCallback : Entering ...");

    WaveLinearSequencerContext *pWaveLinearSequencerContext = reinterpret_cast<WaveLinearSequencerContext *> (pWaveAsynchronousContextForPostbootPhase->getPCallerContext ());
    ResourceId                 status                     = pWaveAsynchronousContextForPostbootPhase->getCompletionStatus ();

    delete pWaveAsynchronousContextForPostbootPhase;
    pWaveLinearSequencerContext->executeNextStep (status);
}

}
