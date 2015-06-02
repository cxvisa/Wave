/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author Anil C                                                         *
 ***************************************************************************/

#include "Framework/Postboot/PrismPostPersistentBootWorkerClusterContext.h"
#include "Framework/Utils/PrismCondition.h"
#include "Framework/Utils/PrismMutex.h"

namespace WaveNs
{

PrismPostPersistentBootWorkerClusterContext::PrismPostPersistentBootWorkerClusterContext()
 :  m_eventId           (0),
    m_parameter         (0),
    m_recoveryType      (0),
    m_pPostbootMutex    (NULL),
    m_pPostbootSynchronizingCondition (NULL),
    m_pPrismPostPersistenceBootMessage (NULL)
{
}

PrismPostPersistentBootWorkerClusterContext::PrismPostPersistentBootWorkerClusterContext( const UI32 &eventId, const UI32 &parameter, const ResourceId &recoveryType, PrismPostPersistenceBootMessage *pPrismPostPersistenceBootMessage, PrismMutex *pPostbootMutex, PrismCondition *pPostbootSynchronizingCondition )
 : m_eventId (eventId),
   m_parameter (parameter), 
   m_recoveryType (recoveryType), 
   m_pPostbootMutex (pPostbootMutex),
   m_pPostbootSynchronizingCondition (pPostbootSynchronizingCondition),
   m_pPrismPostPersistenceBootMessage (pPrismPostPersistenceBootMessage)   
{
}

PrismPostPersistentBootWorkerClusterContext::~PrismPostPersistentBootWorkerClusterContext()
{
}

void PrismPostPersistentBootWorkerClusterContext::initializeContext ( const UI32 &eventId, const UI32 &parameter, const ResourceId &recoveryType, PrismPostPersistenceBootMessage *pPrismPostPersistenceBootMessage, PrismMutex *pPostbootMutex, PrismCondition *pPostbootSynchronizingCondition )
{
    m_eventId = eventId ;
    m_parameter = parameter;
    m_recoveryType = recoveryType;
    m_pPostbootMutex = pPostbootMutex;
    m_pPostbootSynchronizingCondition = pPostbootSynchronizingCondition;
    m_pPrismPostPersistenceBootMessage = pPrismPostPersistenceBootMessage;
}

void PrismPostPersistentBootWorkerClusterContext::setEventId(const UI32 &eventId)
{
    m_eventId  =  eventId;
}

UI32 PrismPostPersistentBootWorkerClusterContext::getEventId() const
{
    return (m_eventId);
}

void PrismPostPersistentBootWorkerClusterContext::setParameter(const UI32 &parameter)
{
    m_parameter  =  parameter;
}

UI32 PrismPostPersistentBootWorkerClusterContext::getParameter() const
{
    return (m_parameter);
}

void PrismPostPersistentBootWorkerClusterContext::setRecoveryType(const ResourceId &recoveryType)
{
    m_recoveryType  =  recoveryType;
}

ResourceId  PrismPostPersistentBootWorkerClusterContext::getRecoveryType() const
{
    return (m_recoveryType);
}

void PrismPostPersistentBootWorkerClusterContext::setPostbootMutex (PrismMutex *pPostbootMutex)
{
    m_pPostbootMutex = pPostbootMutex;
}

PrismMutex *PrismPostPersistentBootWorkerClusterContext::getPostbootMutex () const
{
    return (m_pPostbootMutex);
}

void PrismPostPersistentBootWorkerClusterContext::setPostbootSynchronizingCondition (PrismCondition *pPostbootSynchronizingCondition)
{
    m_pPostbootSynchronizingCondition = pPostbootSynchronizingCondition;
}

PrismCondition *PrismPostPersistentBootWorkerClusterContext::getPostbootSynchronizingCondition () const
{
    return (m_pPostbootSynchronizingCondition);
}

void PrismPostPersistentBootWorkerClusterContext::setPostbootMessagePointer (PrismPostPersistenceBootMessage *pPrismPostPersistenceBootMessage)
{
    m_pPrismPostPersistenceBootMessage = pPrismPostPersistenceBootMessage;
}

PrismPostPersistenceBootMessage *PrismPostPersistentBootWorkerClusterContext::getPostbootMessagePointer () const
{
    return ( m_pPrismPostPersistenceBootMessage );
}

}
