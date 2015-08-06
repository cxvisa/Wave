/**
 *  @file: PostBootStartedEvent.h
 *  Copyright (C) 2010 Vidyasagara Guntaka                 
 *  All rights reserved.
 *  Description:Implementation of PostBootStartedEvent
 *  
 *  Author : Aashish Akhouri
 *  Date: 10/20/2010
 */

#include "Framework/Core/PostBootStartedEvent.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"

namespace WaveNs
{

PostBootStartedEvent::PostBootStartedEvent ()
    : PrismEvent (PrismFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_POST_BOOT_STARTED_EVENT),
      m_eventId (0),
      m_parameter (0)
	  
{
}

PostBootStartedEvent::PostBootStartedEvent (const UI32 &eventId, const UI32 &parameter)
    : PrismEvent (PrismFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_POST_BOOT_STARTED_EVENT),
     m_eventId (eventId),
     m_parameter (parameter)
{
}

PostBootStartedEvent::~PostBootStartedEvent ()
{
}

void PostBootStartedEvent::setupAttributesForSerialization ()
{
  PrismEvent::setupAttributesForSerialization ();
}

UI32 PostBootStartedEvent::getPostBootStartedEventId () const
{
    return m_eventId;
}

void PostBootStartedEvent::setPostBootStartedEventId (const UI32 &eventId)
{
    m_eventId = eventId;
}

UI32 PostBootStartedEvent::getPostBootStartedEventParameter () const
{
    return m_parameter;
}

void PostBootStartedEvent::setPostBootStartedEventParameter (const UI32 &parameter)
{
    m_parameter = parameter;
}

}
