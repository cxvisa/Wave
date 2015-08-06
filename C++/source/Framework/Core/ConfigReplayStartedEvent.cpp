/**
 *  @file: ConfigReplayStartedEvent.cpp
 *  Copyright (C) 2010 Vidyasagara Guntaka                 
 *  All rights reserved.
 *  Description:Implementation of ConfigReplayStartedEvent
 *  Author : Aashish Akhouri
 *  Date: 10/20/2010
 */

#include "Framework/Core/ConfigReplayStartedEvent.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"

namespace WaveNs
{

ConfigReplayStartedEvent::ConfigReplayStartedEvent ()
    : WaveEvent (PrismFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_CONFIG_REPLAY_STARTED_EVENT),
    m_configFileReplayFlag (false)
{
}

ConfigReplayStartedEvent::ConfigReplayStartedEvent (const bool &flag)
    : WaveEvent (PrismFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_CONFIG_REPLAY_STARTED_EVENT),
    m_configFileReplayFlag (flag)
{
}

ConfigReplayStartedEvent::~ConfigReplayStartedEvent ()
{
}

void ConfigReplayStartedEvent::setupAttributesForSerialization ()
{
    WaveEvent::setupAttributesForSerialization ();
}

bool ConfigReplayStartedEvent::getConfigFileReplayFlag () const
{
    return m_configFileReplayFlag;
}

void ConfigReplayStartedEvent::setConfigFileReplayFlag (const bool &flag)
{
    m_configFileReplayFlag = flag;
}

}
