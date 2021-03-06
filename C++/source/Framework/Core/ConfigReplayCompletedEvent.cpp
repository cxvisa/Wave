/**
 *  @file: ConfigReplayCompletedEvent.cpp
 *  Copyright (C) 2010 Vidyasagara Guntaka                 
 *  All rights reserved.
 *  Description: Implementation of
 *               ConfigReplayCompletedEvent
 *  Author : Aashish Akhouri
 *  Date: 10/20/2010
 */

#include "Framework/Core/ConfigReplayCompletedEvent.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Attributes/AttributeResourceId.h"

namespace WaveNs
{

ConfigReplayCompletedEvent::ConfigReplayCompletedEvent ()
    : WaveEvent (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_CONFIG_REPLAY_COMPLETED_EVENT)
{
}

ConfigReplayCompletedEvent::ConfigReplayCompletedEvent (const ResourceId &recoveryType)
    : WaveEvent (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_CONFIG_REPLAY_COMPLETED_EVENT),
     m_recoveryType (recoveryType)
{
}

ConfigReplayCompletedEvent::~ConfigReplayCompletedEvent ()
{

}

void ConfigReplayCompletedEvent::setupAttributesForSerialization ()
{
    WaveEvent::setupAttributesForSerialization ();
     addSerializableAttribute (new AttributeResourceId (&m_recoveryType, "recoveryType"));
}

ResourceId  ConfigReplayCompletedEvent::getRecoveryType () const
{
    return (m_recoveryType);
}

void  ConfigReplayCompletedEvent::setRecoveryType (const ResourceId &recoveryType)
{
    m_recoveryType = recoveryType;
}

}
