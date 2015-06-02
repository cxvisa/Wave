/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "SoftwareManagement/SoftwareManagementGetVersionMessage.h"
#include "SoftwareManagement/SoftwareManagementObjectManager.h"
#include "SoftwareManagement/SoftwareManagementTypes.h"

namespace WaveNs
{

SoftwareManagementGetVersionMessage::SoftwareManagementGetVersionMessage ()
    : ManagementInterfaceMessage (SoftwareManagementObjectManager::getClassName (), SOFTWAREMANAGEMENT_GET_VERSION)
{
}

SoftwareManagementGetVersionMessage::~SoftwareManagementGetVersionMessage ()
{
}

void SoftwareManagementGetVersionMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeString (&m_version, "version"));
}

string SoftwareManagementGetVersionMessage::getVersion () const
{
    return (m_version);
}

void SoftwareManagementGetVersionMessage::setVersion (const string &version)
{
    m_version = version;
}

}
