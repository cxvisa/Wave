/**
 *@file ClusterLocalSetHardwareSynchronizationMessage.cpp
 * Copyright (C) 2011 BrocadeCommunications Systems,Inc.
 * All rights reserved. 
 *
 * Description: This file has the implementation of the message class
 *              handled by ClusterLocalOM which is used for updating
 *              the hardware synchronization state attribute in the
 *              WaveNode Managed Object. 
 *
 * Author :     Brian Adaniya
 * Date :       05/05/2011
 */

#include "Cluster/Local/ClusterLocalSetHardwareSynchronizationStateMessage.h"
#include "Framework/Messaging/Local/PrismMessage.h"
#include "Cluster/Local/ClusterLocalTypes.h"
#include "Cluster/Local/ClusterLocalObjectManager.h"
#include "Framework/Attributes/AttributeResourceId.h"

namespace WaveNs
{

ClusterLocalSetHardwareSynchronizationStateMessage::ClusterLocalSetHardwareSynchronizationStateMessage ()
    : PrismMessage (ClusterLocalObjectManager::getPrismServiceId (), CLUSTER_LOCAL_SET_HARDWARE_SYNCHRONIZATION_STATE),
    m_hardwareSynchronizationState  (WAVE_NODE_HARDWARE_SYNCHRONIZATION_STATE_UNINITIALIZED)
{
}

ClusterLocalSetHardwareSynchronizationStateMessage::ClusterLocalSetHardwareSynchronizationStateMessage (ResourceId hardwareSynchronizationState)
    : PrismMessage (ClusterLocalObjectManager::getPrismServiceId (), CLUSTER_LOCAL_SET_HARDWARE_SYNCHRONIZATION_STATE),
    m_hardwareSynchronizationState  (hardwareSynchronizationState)
{
}

ClusterLocalSetHardwareSynchronizationStateMessage::~ClusterLocalSetHardwareSynchronizationStateMessage ()
{
}

void ClusterLocalSetHardwareSynchronizationStateMessage::setupAttributesForSerialization ()
{
    PrismMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeResourceId       (&m_hardwareSynchronizationState, "hardwareSynchronizationState"));
}

ResourceId ClusterLocalSetHardwareSynchronizationStateMessage::getHardwareSynchronizationState () const
{
    return (m_hardwareSynchronizationState);
}

void ClusterLocalSetHardwareSynchronizationStateMessage::setHardwareSynchronizationState (ResourceId hardwareSynchronizationState)
{
    m_hardwareSynchronizationState = hardwareSynchronizationState;
}

}
