/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author Anil C                                                         *
 ***************************************************************************/

#include "Framework/Postboot/WavePostPersistentBootWorkerClusterContext.h"
#include "Framework/Utils/WaveCondition.h"
#include "Framework/Utils/WaveMutex.h"

namespace WaveNs
{

WavePostPersistentBootWorkerClusterContext::WavePostPersistentBootWorkerClusterContext()
 :  m_eventId           (0),
    m_parameter         (0),
    m_recoveryType      (0),
    m_pPostbootMutex    (NULL),
    m_pPostbootSynchronizingCondition (NULL),
    m_pWavePostPersistenceBootMessage (NULL)
{
}

WavePostPersistentBootWorkerClusterContext::WavePostPersistentBootWorkerClusterContext( const UI32 &eventId, const UI32 &parameter, const ResourceId &recoveryType, WavePostPersistenceBootMessage *pWavePostPersistenceBootMessage, WaveMutex *pPostbootMutex, WaveCondition *pPostbootSynchronizingCondition )
 : m_eventId (eventId),
   m_parameter (parameter), 
   m_recoveryType (recoveryType), 
   m_pPostbootMutex (pPostbootMutex),
   m_pPostbootSynchronizingCondition (pPostbootSynchronizingCondition),
   m_pWavePostPersistenceBootMessage (pWavePostPersistenceBootMessage)   
{
}

WavePostPersistentBootWorkerClusterContext::~WavePostPersistentBootWorkerClusterContext()
{
}

void WavePostPersistentBootWorkerClusterContext::initializeContext ( const UI32 &eventId, const UI32 &parameter, const ResourceId &recoveryType, WavePostPersistenceBootMessage *pWavePostPersistenceBootMessage, WaveMutex *pPostbootMutex, WaveCondition *pPostbootSynchronizingCondition )
{
    m_eventId = eventId ;
    m_parameter = parameter;
    m_recoveryType = recoveryType;
    m_pPostbootMutex = pPostbootMutex;
    m_pPostbootSynchronizingCondition = pPostbootSynchronizingCondition;
    m_pWavePostPersistenceBootMessage = pWavePostPersistenceBootMessage;
}

void WavePostPersistentBootWorkerClusterContext::setEventId(const UI32 &eventId)
{
    m_eventId  =  eventId;
}

UI32 WavePostPersistentBootWorkerClusterContext::getEventId() const
{
    return (m_eventId);
}

void WavePostPersistentBootWorkerClusterContext::setParameter(const UI32 &parameter)
{
    m_parameter  =  parameter;
}

UI32 WavePostPersistentBootWorkerClusterContext::getParameter() const
{
    return (m_parameter);
}

void WavePostPersistentBootWorkerClusterContext::setRecoveryType(const ResourceId &recoveryType)
{
    m_recoveryType  =  recoveryType;
}

ResourceId  WavePostPersistentBootWorkerClusterContext::getRecoveryType() const
{
    return (m_recoveryType);
}

void WavePostPersistentBootWorkerClusterContext::setPostbootMutex (WaveMutex *pPostbootMutex)
{
    m_pPostbootMutex = pPostbootMutex;
}

WaveMutex *WavePostPersistentBootWorkerClusterContext::getPostbootMutex () const
{
    return (m_pPostbootMutex);
}

void WavePostPersistentBootWorkerClusterContext::setPostbootSynchronizingCondition (WaveCondition *pPostbootSynchronizingCondition)
{
    m_pPostbootSynchronizingCondition = pPostbootSynchronizingCondition;
}

WaveCondition *WavePostPersistentBootWorkerClusterContext::getPostbootSynchronizingCondition () const
{
    return (m_pPostbootSynchronizingCondition);
}

void WavePostPersistentBootWorkerClusterContext::setPostbootMessagePointer (WavePostPersistenceBootMessage *pWavePostPersistenceBootMessage)
{
    m_pWavePostPersistenceBootMessage = pWavePostPersistenceBootMessage;
}

WavePostPersistenceBootMessage *WavePostPersistentBootWorkerClusterContext::getPostbootMessagePointer () const
{
    return ( m_pWavePostPersistenceBootMessage );
}

}
