/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Amr Sabaa                                                    *
 ***************************************************************************/

#include "Framework/Timer/TimerSignalObjectManager.h"
#include "Framework/Timer/TimerWorker.h"
#include "Framework/Utils/AssertUtils.h"
#include <signal.h>
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"

namespace WaveNs
{

TimerSignalObjectManager::TimerSignalObjectManager ()
    : WaveLocalObjectManagerForUserSpecificTasks ("Framework Timer Signal")
{
}

TimerSignalObjectManager *TimerSignalObjectManager::getInstance ()
{
    static TimerSignalObjectManager *pTimerSignalObjectManager = NULL;

    if (NULL == pTimerSignalObjectManager)
    {
        pTimerSignalObjectManager = new TimerSignalObjectManager ();
        WaveNs::prismAssert (NULL != pTimerSignalObjectManager, __FILE__, __LINE__);
    }

    return (pTimerSignalObjectManager);
}

TimerSignalObjectManager::~TimerSignalObjectManager ()
{

}

PrismServiceId TimerSignalObjectManager::getPrismServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

void TimerSignalObjectManager::catchTimerAlarm ()
{
    TimerWorker::processTimeOut ();
}

void TimerSignalObjectManager::boot (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    trace (TRACE_LEVEL_DEVEL, "TimerSignalObjectManager::boot : Entering ...");

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();

	prismCreateWaitableTimer ();

    while (1)
    {
        prismWaitForAlarmSignal ();
        catchTimerAlarm ();
    }
}

}
