/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jitendra Singh                                                 *
 ***************************************************************************/

#include "Framework/Postboot/WavePostbootAgentThreadContext.h"
#include "Framework/Utils/WaveCondition.h"
#include "Framework/Utils/WaveMutex.h"

namespace WaveNs
{

WavePostbootAgentThreadContext::WavePostbootAgentThreadContext ()
{
    m_pWavePostPersistenceBootMessage = NULL;
    m_pPostbootMutex = NULL;
    m_pPostbootSynchronizingCondition = NULL;
}

WavePostbootAgentThreadContext::~WavePostbootAgentThreadContext ()
{
}

void   WavePostbootAgentThreadContext::setPostbootMessagePointer (WavePostPersistenceBootMessage *pWavePostPersistenceBootMessage)
{
    m_pWavePostPersistenceBootMessage = pWavePostPersistenceBootMessage;

}

WavePostPersistenceBootMessage *WavePostbootAgentThreadContext::getPostbootMessagePointer ()
{
    return m_pWavePostPersistenceBootMessage;
}

void WavePostbootAgentThreadContext::setPostbootMutex (WaveMutex *pPostbootMutex)
{
    m_pPostbootMutex = pPostbootMutex;
}

WaveMutex *WavePostbootAgentThreadContext::getPostbootMutex () const
{   
    return (m_pPostbootMutex);
}   
    
void WavePostbootAgentThreadContext::setPostbootSynchronizingCondition (WaveCondition *pPostbootSynchronizingCondition)
{   
    m_pPostbootSynchronizingCondition = pPostbootSynchronizingCondition;
}

WaveCondition *WavePostbootAgentThreadContext::getPostbootSynchronizingCondition () const
{   
    return (m_pPostbootSynchronizingCondition);
}

}
