/***************************************************************************
 *   Copyright (C) 2012 Vidyasagara Guntaka                                
 *   All rights reserved.  
 *   Description: This file implements the wave framework service independent
 *                messages.  These service independent messages are directly
 *                handled in the HaPeerMessageReceiverThread or 
 *                InterLocationMessageReceiverThread.
 *   Author : Brian Adaniya 
 *   Date   : 10/22/2012                                           
 ***************************************************************************/

#include "Framework/Core/WaveFrameworkServiceIndependentMessages.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"

namespace WaveNs
{

FrameworkObjectManagerStoreConfigurationIntentMessage::FrameworkObjectManagerStoreConfigurationIntentMessage ()
    : WaveServiceIndependentMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_STORE_CONFIGURATION_INTENT),
    m_configurationIntentMessageId  (0)
{
}

FrameworkObjectManagerStoreConfigurationIntentMessage::FrameworkObjectManagerStoreConfigurationIntentMessage (const UI32 &configurationIntentMessageId)
    : WaveServiceIndependentMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_STORE_CONFIGURATION_INTENT),
    m_configurationIntentMessageId  (configurationIntentMessageId)
{
}

FrameworkObjectManagerStoreConfigurationIntentMessage::~FrameworkObjectManagerStoreConfigurationIntentMessage ()
{   
}

void FrameworkObjectManagerStoreConfigurationIntentMessage::setupAttributesForSerialization ()
{
    WaveServiceIndependentMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeUI32     (&m_configurationIntentMessageId, "configurationIntentMessageId"));
}

UI32 FrameworkObjectManagerStoreConfigurationIntentMessage::getConfigurationIntentMessageId () const
{
    return (m_configurationIntentMessageId);
}

void FrameworkObjectManagerStoreConfigurationIntentMessage::setConfigurationIntentMessageId (const UI32 &configurationIntentMessageId)
{
    m_configurationIntentMessageId = configurationIntentMessageId;
}


FrameworkObjectManagerRemoveConfigurationIntentMessage::FrameworkObjectManagerRemoveConfigurationIntentMessage ()
    : WaveServiceIndependentMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_REMOVE_CONFIGURATION_INTENT),
    m_configurationIntentMessageId  (0)
{
}

FrameworkObjectManagerRemoveConfigurationIntentMessage::FrameworkObjectManagerRemoveConfigurationIntentMessage (const UI32 &configurationIntentMessageId)
    : WaveServiceIndependentMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_REMOVE_CONFIGURATION_INTENT),
    m_configurationIntentMessageId  (configurationIntentMessageId)
{
}

FrameworkObjectManagerRemoveConfigurationIntentMessage::~FrameworkObjectManagerRemoveConfigurationIntentMessage ()
{
}

void FrameworkObjectManagerRemoveConfigurationIntentMessage::setupAttributesForSerialization ()
{
    WaveServiceIndependentMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeUI32 (&m_configurationIntentMessageId, "configurationIntentMessageId"));
}

UI32 FrameworkObjectManagerRemoveConfigurationIntentMessage::getConfigurationIntentMessageId () const
{
    return (m_configurationIntentMessageId);
}

void FrameworkObjectManagerRemoveConfigurationIntentMessage::setConfigurationIntentMessageId (const UI32 &configurationIntentMessageId)
{
    m_configurationIntentMessageId = configurationIntentMessageId; 
}

}
