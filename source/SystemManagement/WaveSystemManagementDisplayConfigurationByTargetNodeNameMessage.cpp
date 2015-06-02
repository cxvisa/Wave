/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "SystemManagement/WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage.h"
#include "SystemManagement/WaveSystemManagementObjectManager.h"
#include "SystemManagement/WaveSystemManagementTypes.h"

namespace WaveNs
{

WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage::WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage ()
    : ManagementInterfaceMessage (WaveSystemManagementObjectManager::getClassName (), WAVE_SYSTEM_MANAGEMENT_DISPLAY_CURRENT_CONFIGURATION_BY_TARGET_NODE_NAME),
      m_schemaName               ("wavecurrent")
{
}

WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage::WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage (const string &targetNodeName)
    : ManagementInterfaceMessage (WaveSystemManagementObjectManager::getClassName (), WAVE_SYSTEM_MANAGEMENT_DISPLAY_CURRENT_CONFIGURATION_BY_TARGET_NODE_NAME),
      m_targetNodeName           (targetNodeName),
      m_schemaName               ("wavecurrent")
{
}

WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage::WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage (const string &targetNodeName, const string &schemaName)
    : ManagementInterfaceMessage (WaveSystemManagementObjectManager::getClassName (), WAVE_SYSTEM_MANAGEMENT_DISPLAY_CURRENT_CONFIGURATION_BY_TARGET_NODE_NAME),
      m_targetNodeName           (targetNodeName),
      m_schemaName               (schemaName)
{
}

WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage::~WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage ()
{
}

void WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeString (&m_targetNodeName,   "targetNodeName"));
    addSerializableAttribute (new AttributeString (&m_schemaName,       "schemaName"));
}

string WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage::getTargetNodeName () const
{
    return (m_targetNodeName);
}

void WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage::setTargetNodeName (const string &targetNodeName)
{
    m_targetNodeName = targetNodeName;
}

string WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage::getSchemaName () const
{
    return (m_schemaName);
}

void WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage::setSchemaName (const string &schemaName)
{
    m_schemaName = schemaName;
}

}
