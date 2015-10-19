/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jitendra Singh                                                *
 ***************************************************************************/

#include "Framework/Postboot/WavePostbootAgent.h"
#include "Framework/Postboot/WavePostbootAgentThread.h"
#include "Framework/Postboot/WavePostbootAgentThreadContext.h"
#include "Framework/Postboot/WavePostPersistentBootMessages.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/Utils/WaveMutex.h"

namespace WaveNs
{

    UI32        WavePostbootAgentThread::m_parallelPostBootAgentThreads;
    WaveMutex  WavePostbootAgentThread::m_parallelPostBootAgentThreadsMutex;

WavePostbootAgentThread::WavePostbootAgentThread   (WaveObjectManager *pWaveObjectManager, const UI32 &event, const UI32 &parameter, 
                                                      const ResourceId &recoveryType, WavePostbootAgentThreadContext *pWavePostbootAgentThreadContext)
    : WaveWorker (pWaveObjectManager, false),
    WavePosixThread (),
    m_eventId    (event),
    m_parameter  (parameter),
    m_recoveryType (recoveryType),
    m_pWavePostbootAgentThreadContext (pWavePostbootAgentThreadContext)
    
{
    FrameworkToolKit::incrementLineCardPostBootCount ();

    m_parallelPostBootAgentThreadsMutex.lock();
    m_parallelPostBootAgentThreads++;
    m_parallelPostBootAgentThreadsMutex.unlock();
}

WavePostbootAgentThread::~WavePostbootAgentThread ()
{
    m_parallelPostBootAgentThreadsMutex.lock();
    m_parallelPostBootAgentThreads--;

    if ( ( 0 == m_parallelPostBootAgentThreads ) && ( NULL != m_pWavePostbootAgentThreadContext ) )
    {
        if ( ( NULL == m_pWavePostbootAgentThreadContext->getPostbootMessagePointer() ) && ( NULL != m_pWavePostbootAgentThreadContext->getPostbootMutex()) )
        {
            (m_pWavePostbootAgentThreadContext->getPostbootMutex())->lock();
            (m_pWavePostbootAgentThreadContext->getPostbootSynchronizingCondition())->resume();
            (m_pWavePostbootAgentThreadContext->getPostbootMutex())->unlock();
        }
    }

    delete (m_pWavePostbootAgentThreadContext);

    m_parallelPostBootAgentThreadsMutex.unlock();

    FrameworkToolKit::decrementLineCardPostBootCount ();
}

WaveThreadStatus WavePostbootAgentThread::start ()
{
    trace (TRACE_LEVEL_PERF_START, "LC Postboot.");
    WavePostPersistenceBootMessage *pWavePostPersistenceBootMessage = m_pWavePostbootAgentThreadContext->getPostbootMessagePointer ();

    WavePostbootAgent *pWavePostbootAgent = new WavePostbootAgent(m_pWaveObjectManager, m_eventId, m_parameter, m_recoveryType);
    waveAssert (NULL != pWavePostbootAgent, __FILE__, __LINE__);
    ResourceId status = pWavePostbootAgent->execute ();
    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, string ("WavePostbootAgentThread::start: WavePostbootAgent execute returned error: ")+FrameworkToolKit::localize (status));
    }
    else
    {
        trace (TRACE_LEVEL_SUCCESS, string ("WavePostbootAgentThread::start: WavePostbootAgent execute succeeded"));
    }
   
    if ( NULL != pWavePostPersistenceBootMessage )
    {    
        pWavePostPersistenceBootMessage->setCompletionStatus (status);
        reply (pWavePostPersistenceBootMessage);
    }

    trace (TRACE_LEVEL_PERF_END, "LC Postboot.");

    delete (pWavePostbootAgent);
    delete (this);
    return (WAVE_THREAD_SUCCESS);
}
}

