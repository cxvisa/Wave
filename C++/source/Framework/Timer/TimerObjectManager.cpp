/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Amr Sabaa                                                    *
 ***************************************************************************/

#include "Framework/Timer/TimerObjectManager.h"
#include "Framework/Timer/TimerSignalObjectManager.h"
#include "Framework/Utils/AssertUtils.h"

namespace WaveNs
{

TimerObjectManager::TimerObjectManager ()
    : WaveLocalObjectManager ("Framework Timer")
{
    m_pTimerWorker = new TimerWorker (this);
}

TimerObjectManager *TimerObjectManager::getInstance ()
{
    static TimerObjectManager *pTimerObjectManager = NULL;

    if (NULL == pTimerObjectManager)
    {
        pTimerObjectManager = new TimerObjectManager ();
        WaveNs::waveAssert (NULL != pTimerObjectManager, __FILE__, __LINE__);
    }

    return (pTimerObjectManager);
}

TimerObjectManager::~TimerObjectManager ()
{
    if (NULL != m_pTimerWorker)
    {
        delete m_pTimerWorker;
    }
}

WaveServiceId TimerObjectManager::getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}


void TimerObjectManager::disable (PrismAsynchronousContext *pPrismAsynchronousContext)
{

    trace (TRACE_LEVEL_DEVEL, "TimerObjectManager::disable : Entering ...");

    pPrismAsynchronousContext->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pPrismAsynchronousContext->callback ();

    m_pTimerWorker->deleteAllTimers ();
}

}
