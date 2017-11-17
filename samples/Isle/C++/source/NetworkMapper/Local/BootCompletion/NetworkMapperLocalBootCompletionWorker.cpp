/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "NetworkMapper/Local/BootCompletion/NetworkMapperLocalBootCompletionWorker.h"
#include "NetworkMapper/Local/NetworkMapperLocalObjectManager.h"
#include "Framework/Boot/BootTypes.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveManagedObjectToolKit.h"

namespace IsleNs
{

NetworkMapperLocalBootCompletionWorker::NetworkMapperLocalBootCompletionWorker (NetworkMapperLocalObjectManager *pNetworkMapperLocalObjectManager)
    : WaveWorker (pNetworkMapperLocalObjectManager)
{
}

NetworkMapperLocalBootCompletionWorker::~NetworkMapperLocalBootCompletionWorker ()
{
}

void NetworkMapperLocalBootCompletionWorker::initialize (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    trace (TRACE_LEVEL_DEVEL, "NetworkMapperLocalBootCompletionWorker::initialize : Entering ...");

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void NetworkMapperLocalBootCompletionWorker::boot (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    trace (TRACE_LEVEL_DEVEL, "NetworkMapperLocalBootCompletionWorker::boot : Entering ...");

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void NetworkMapperLocalBootCompletionWorker::listenForEvents (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    listenForEvent (WaveFrameworkObjectManager::getWaveServiceId (), BOOT_COMPLETE_FOR_THIS_LOCATION, reinterpret_cast<WaveEventHandler> (&NetworkMapperLocalBootCompletionWorker::bootCompleteForThisLocationEventHandler));

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void NetworkMapperLocalBootCompletionWorker::bootCompleteForThisLocationEventHandler (const BootCompleteForThisLocationEvent *&pBootCompleteForThisLocationEvent)
{
    trace (TRACE_LEVEL_INFO, "NetworkMapperLocalBootCompletionWorker::bootCompleteForThisLocationEventHandler : Entering ...");

    reply (reinterpret_cast<const WaveEvent *&> (pBootCompleteForThisLocationEvent));
}

}
