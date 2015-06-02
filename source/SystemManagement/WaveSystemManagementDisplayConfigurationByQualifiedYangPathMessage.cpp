/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "SystemManagement/WaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage.h"
#include "SystemManagement/WaveSystemManagementObjectManager.h"
#include "SystemManagement/WaveSystemManagementTypes.h"

namespace WaveNs
{

WaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage::WaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage ()
    : ManagementInterfaceMessage (WaveSystemManagementObjectManager::getClassName (), WAVE_SYSTEM_MANAGEMENT_DISPLAY_CURRENT_CONFIGURATION_BY_QUALIFIED_YANG_PATH),
      m_schemaName               ("wavecurrent")
{
}

WaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage::WaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage (const string &qualifiedYangPath)
    : ManagementInterfaceMessage (WaveSystemManagementObjectManager::getClassName (), WAVE_SYSTEM_MANAGEMENT_DISPLAY_CURRENT_CONFIGURATION_BY_QUALIFIED_YANG_PATH),
      m_qualifiedYangPath        (qualifiedYangPath),
      m_schemaName               ("wavecurrent")
{
}

WaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage::WaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage (const string &qualifiedYangPath, const string &schemaName)
    : ManagementInterfaceMessage (WaveSystemManagementObjectManager::getClassName (), WAVE_SYSTEM_MANAGEMENT_DISPLAY_CURRENT_CONFIGURATION_BY_QUALIFIED_YANG_PATH),
      m_qualifiedYangPath        (qualifiedYangPath),
      m_schemaName               (schemaName)
{
}

WaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage::~WaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage ()
{
}

void WaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeString (&m_qualifiedYangPath,    "qualifiedYangPath"));
    addSerializableAttribute (new AttributeString (&m_schemaName,           "schemaName"));
}

string WaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage::getQualifiedYangPath () const
{
    return (m_qualifiedYangPath);
}

void WaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage::setQualifiedYangPath (const string &qualifiedYangPath)
{
    m_qualifiedYangPath = qualifiedYangPath;
}

string WaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage::getSchemaName () const
{
    return (m_schemaName);
}

void WaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage::setSchemaName (const string &schemaName)
{
    m_schemaName = schemaName;
}

}
