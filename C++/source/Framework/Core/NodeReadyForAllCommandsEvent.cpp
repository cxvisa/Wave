/**
 *  @file: NodeReadyForAllCommandsEvent.cpp
 *  Copyright (C) 2010 Vidyasagara Guntaka                 
 *  All rights reserved.
 *  Description:Implmentation of NodeReadyForAllCommandsEvent
 *              Class. 
 *  
 *  Author : Aashish Akhouri
 *  Date: 10/20/2010
 */

#include "Framework/Core/NodeReadyForAllCommandsEvent.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"
#include "Framework/Attributes/AttributeResourceId.h"

namespace WaveNs
{

NodeReadyForAllCommandsEvent::NodeReadyForAllCommandsEvent ()
    : WaveEvent (PrismFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_NODE_READY_FOR_ALL_COMMANDS_EVENT),
     m_recoveryType (0)
{
}

NodeReadyForAllCommandsEvent::NodeReadyForAllCommandsEvent (const ResourceId &recoveryType)
    : WaveEvent (PrismFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_NODE_READY_FOR_ALL_COMMANDS_EVENT),
     m_recoveryType (recoveryType)
{
}

NodeReadyForAllCommandsEvent::~NodeReadyForAllCommandsEvent ()
{
}

void NodeReadyForAllCommandsEvent::setupAttributesForSerialization ()
{
    WaveEvent::setupAttributesForSerialization ();
     addSerializableAttribute (new AttributeResourceId (&m_recoveryType, "recoveryType"));
}

ResourceId  NodeReadyForAllCommandsEvent::getRecoveryType () const
{
    return (m_recoveryType);
}

void  NodeReadyForAllCommandsEvent::setRecoveryType (const ResourceId &recoveryType)
{
    m_recoveryType = recoveryType;
}

}
