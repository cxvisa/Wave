/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jitendra Singh                                                *
 ***************************************************************************/

#include "Framework/Postboot/PrismPostbootAgent.h"
#include "Framework/Postboot/PrismPostbootAgentThread.h"
#include "Framework/Postboot/PrismPostbootAgentThreadContext.h"
#include "Framework/Postboot/PrismPostPersistentBootMessages.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/Utils/WaveMutex.h"

namespace WaveNs
{

    UI32        PrismPostbootAgentThread::m_parallelPostBootAgentThreads;
    WaveMutex  PrismPostbootAgentThread::m_parallelPostBootAgentThreadsMutex;

PrismPostbootAgentThread::PrismPostbootAgentThread   (WaveObjectManager *pWaveObjectManager, const UI32 &event, const UI32 &parameter, 
                                                      const ResourceId &recoveryType, PrismPostbootAgentThreadContext *pPrismPostbootAgentThreadContext)
    : WaveWorker (pWaveObjectManager, false),
    PrismPosixThread (),
    m_eventId    (event),
    m_parameter  (parameter),
    m_recoveryType (recoveryType),
    m_pPrismPostbootAgentThreadContext (pPrismPostbootAgentThreadContext)
    
{
    FrameworkToolKit::incrementLineCardPostBootCount ();

    m_parallelPostBootAgentThreadsMutex.lock();
    m_parallelPostBootAgentThreads++;
    m_parallelPostBootAgentThreadsMutex.unlock();
}

PrismPostbootAgentThread::~PrismPostbootAgentThread ()
{
    m_parallelPostBootAgentThreadsMutex.lock();
    m_parallelPostBootAgentThreads--;

    if ( ( 0 == m_parallelPostBootAgentThreads ) && ( NULL != m_pPrismPostbootAgentThreadContext ) )
    {
        if ( ( NULL == m_pPrismPostbootAgentThreadContext->getPostbootMessagePointer() ) && ( NULL != m_pPrismPostbootAgentThreadContext->getPostbootMutex()) )
        {
            (m_pPrismPostbootAgentThreadContext->getPostbootMutex())->lock();
            (m_pPrismPostbootAgentThreadContext->getPostbootSynchronizingCondition())->resume();
            (m_pPrismPostbootAgentThreadContext->getPostbootMutex())->unlock();
        }
    }

    delete (m_pPrismPostbootAgentThreadContext);

    m_parallelPostBootAgentThreadsMutex.unlock();

    FrameworkToolKit::decrementLineCardPostBootCount ();
}

WaveThreadStatus PrismPostbootAgentThread::start ()
{
    trace (TRACE_LEVEL_PERF_START, "LC Postboot.");
    PrismPostPersistenceBootMessage *pPrismPostPersistenceBootMessage = m_pPrismPostbootAgentThreadContext->getPostbootMessagePointer ();

    PrismPostbootAgent *pPrismPostbootAgent = new PrismPostbootAgent(m_pWaveObjectManager, m_eventId, m_parameter, m_recoveryType);
    prismAssert (NULL != pPrismPostbootAgent, __FILE__, __LINE__);
    ResourceId status = pPrismPostbootAgent->execute ();
    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, string ("PrismPostbootAgentThread::start: PrismPostbootAgent execute returned error: ")+FrameworkToolKit::localize (status));
    }
    else
    {
        trace (TRACE_LEVEL_SUCCESS, string ("PrismPostbootAgentThread::start: PrismPostbootAgent execute succeeded"));
    }
   
    if ( NULL != pPrismPostPersistenceBootMessage )
    {    
        pPrismPostPersistenceBootMessage->setCompletionStatus (status);
        reply (pPrismPostPersistenceBootMessage);
    }

    trace (TRACE_LEVEL_PERF_END, "LC Postboot.");

    delete (pPrismPostbootAgent);
    delete (this);
    return (WAVE_THREAD_SUCCESS);
}
}

