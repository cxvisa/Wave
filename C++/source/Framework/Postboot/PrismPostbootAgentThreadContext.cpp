/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jitendra Singh                                                 *
 ***************************************************************************/

#include "Framework/Postboot/PrismPostbootAgentThreadContext.h"
#include "Framework/Utils/PrismCondition.h"
#include "Framework/Utils/PrismMutex.h"

namespace WaveNs
{

PrismPostbootAgentThreadContext::PrismPostbootAgentThreadContext ()
{
    m_pPrismPostPersistenceBootMessage = NULL;
    m_pPostbootMutex = NULL;
    m_pPostbootSynchronizingCondition = NULL;
}

PrismPostbootAgentThreadContext::~PrismPostbootAgentThreadContext ()
{
}

void   PrismPostbootAgentThreadContext::setPostbootMessagePointer (PrismPostPersistenceBootMessage *pPrismPostPersistenceBootMessage)
{
    m_pPrismPostPersistenceBootMessage = pPrismPostPersistenceBootMessage;

}

PrismPostPersistenceBootMessage *PrismPostbootAgentThreadContext::getPostbootMessagePointer ()
{
    return m_pPrismPostPersistenceBootMessage;
}

void PrismPostbootAgentThreadContext::setPostbootMutex (PrismMutex *pPostbootMutex)
{
    m_pPostbootMutex = pPostbootMutex;
}

PrismMutex *PrismPostbootAgentThreadContext::getPostbootMutex () const
{   
    return (m_pPostbootMutex);
}   
    
void PrismPostbootAgentThreadContext::setPostbootSynchronizingCondition (PrismCondition *pPostbootSynchronizingCondition)
{   
    m_pPostbootSynchronizingCondition = pPostbootSynchronizingCondition;
}

PrismCondition *PrismPostbootAgentThreadContext::getPostbootSynchronizingCondition () const
{   
    return (m_pPostbootSynchronizingCondition);
}

}
