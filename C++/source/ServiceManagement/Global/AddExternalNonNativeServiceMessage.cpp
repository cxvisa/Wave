/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "ServiceManagement/Global/AddExternalNonNativeServiceMessage.h"
#include "ServiceManagement/Global/ServiceManagementTypes.h"
#include "ServiceManagement/Global/ServiceManagementObjectManager.h"

namespace WaveNs
{

AddExternalNonNativeServiceMessage::AddExternalNonNativeServiceMessage ()
    : ManagementInterfaceMessage (ServiceManagementObjectManager::getServiceName (), SERVCIE_MANAGEMENT_ADD_EXTERNAL_NON_NATIVE_SERVICE)
{
}

AddExternalNonNativeServiceMessage::AddExternalNonNativeServiceMessage (const string &applicationName)
    : ManagementInterfaceMessage (ServiceManagementObjectManager::getServiceName (), SERVCIE_MANAGEMENT_ADD_EXTERNAL_NON_NATIVE_SERVICE)
{
        m_applicationNames.push_back (applicationName);
}

AddExternalNonNativeServiceMessage::AddExternalNonNativeServiceMessage (const vector<string> &applicationNames)
    : ManagementInterfaceMessage (ServiceManagementObjectManager::getServiceName (), SERVCIE_MANAGEMENT_ADD_EXTERNAL_NON_NATIVE_SERVICE)
{
        m_applicationNames = applicationNames;
}

AddExternalNonNativeServiceMessage::~AddExternalNonNativeServiceMessage ()
{
}

void AddExternalNonNativeServiceMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

    // This class Specific Attributes below

    addSerializableAttribute (new AttributeStringVector (&m_applicationNames, "applicationNames"));
}

const vector<string> &AddExternalNonNativeServiceMessage::getApplicationNames () const
{
    return (m_applicationNames);
}

void AddExternalNonNativeServiceMessage::setApplicationNames (const vector<string> &applicationNames)
{
    m_applicationNames = applicationNames;
}

}
