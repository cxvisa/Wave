/**
 *  @file: PostBootCompletedEvent.cpp
 *  Copyright (C) 2010 Vidyasagara Guntaka                 
 *  All rights reserved.
 *  Description:Implementation  for PostBootCompletedEvent
 *  
 *  Author : Aashish Akhouri
 *  Date: 10/20/2010
 */ 
 
#include "Framework/Core/PostBootCompletedEvent.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"

namespace WaveNs
{

PostBootCompletedEvent::PostBootCompletedEvent ()
    : WaveEvent (PrismFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_POST_BOOT_COMPLETED_EVENT),
      m_eventId (0),
      m_parameter (0)
{
}

PostBootCompletedEvent::PostBootCompletedEvent (const UI32 &eventId, const UI32 &parameter)
    : WaveEvent (PrismFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_POST_BOOT_COMPLETED_EVENT),
     m_eventId (eventId),
     m_parameter (parameter)
{
}

PostBootCompletedEvent::~PostBootCompletedEvent ()
{

}

void PostBootCompletedEvent::setupAttributesForSerialization ()
{
  WaveEvent::setupAttributesForSerialization ();
}

UI32 PostBootCompletedEvent::getPostBootCompletedEventId () const
{
    return m_eventId;
}

void PostBootCompletedEvent::setPostBootCompletedEventId (const UI32 &eventId)
{
    m_eventId = eventId;
}

UI32 PostBootCompletedEvent::getPostBootCompletedEventParameter () const
{
    return m_parameter;
}

void PostBootCompletedEvent::setPostBootCompletedEventParameter (const UI32 &parameter)
{
    m_parameter = parameter;
}


}
