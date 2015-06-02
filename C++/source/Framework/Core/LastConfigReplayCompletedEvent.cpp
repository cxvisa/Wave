/**
 *  @file: LastConfigReplayCompletedEvent.cpp
 *  Copyright (C) 2013 Vidyasagara Guntaka                 
 *  All rights reserved.
 *  Description:Implementation  for LastConfigReplayCompletedEvent
 *  
 *  Author : Brian Adaniya
 *  Date: 01/06/2013
 */ 
 
#include "Framework/Core/LastConfigReplayCompletedEvent.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"

namespace WaveNs
{

LastConfigReplayCompletedEvent::LastConfigReplayCompletedEvent ()
    : PrismEvent (PrismFrameworkObjectManager::getPrismServiceId (), FRAMEWORK_OBJECT_MANAGER_LAST_CONFIG_REPLAY_COMPLETED_EVENT),
      m_lastConfigReplayCompletedEventStatus (WAVE_MESSAGE_SUCCESS)
{
}

LastConfigReplayCompletedEvent::LastConfigReplayCompletedEvent (const ResourceId &completionStatus)
    : PrismEvent (PrismFrameworkObjectManager::getPrismServiceId (), FRAMEWORK_OBJECT_MANAGER_LAST_CONFIG_REPLAY_COMPLETED_EVENT),
      m_lastConfigReplayCompletedEventStatus (completionStatus)
{
}

LastConfigReplayCompletedEvent::~LastConfigReplayCompletedEvent ()
{
}

void LastConfigReplayCompletedEvent::setupAttributesForSerialization ()
{
    PrismEvent::setupAttributesForSerialization ();
}

ResourceId LastConfigReplayCompletedEvent::getLastConfigReplayCompletedEventStatus () const
{
    return (m_lastConfigReplayCompletedEventStatus);
}

void LastConfigReplayCompletedEvent::setLastConfigReplayCompletedEventStatus (const ResourceId &completionStatus)
{
    m_lastConfigReplayCompletedEventStatus = completionStatus;
}

}
