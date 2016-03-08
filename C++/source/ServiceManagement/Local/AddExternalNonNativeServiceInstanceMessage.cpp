/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "ServiceManagement/Local/AddExternalNonNativeServiceInstanceMessage.h"
#include "ServiceManagement/Local/ServiceManagementLocalTypes.h"
#include "ServiceManagement/Local/ServiceManagementLocalObjectManager.h"

namespace WaveNs
{

AddExternalNonNativeServiceInstanceMessage::AddExternalNonNativeServiceInstanceMessage ()
    : ManagementInterfaceMessage (ServiceManagementLocalObjectManager::getServiceName (), SERVCIE_MANAGEMENT_ADD_EXTERNAL_NON_NATIVE_SERVICE_INSTANCE)
{
}

AddExternalNonNativeServiceInstanceMessage::AddExternalNonNativeServiceInstanceMessage (const string &applicationName, const string &applicationInstanceName)
    : ManagementInterfaceMessage (ServiceManagementLocalObjectManager::getServiceName (), SERVCIE_MANAGEMENT_ADD_EXTERNAL_NON_NATIVE_SERVICE_INSTANCE)
{
    m_applicationName = applicationName;
    m_applicationInstanceNames.push_back (applicationInstanceName);
}

AddExternalNonNativeServiceInstanceMessage::AddExternalNonNativeServiceInstanceMessage (const string &applicationName, const vector<string> &applicationInstanceNames)
    : ManagementInterfaceMessage (ServiceManagementLocalObjectManager::getServiceName (), SERVCIE_MANAGEMENT_ADD_EXTERNAL_NON_NATIVE_SERVICE_INSTANCE)
{
    m_applicationName          = applicationName;
    m_applicationInstanceNames = applicationInstanceNames;
}

AddExternalNonNativeServiceInstanceMessage::~AddExternalNonNativeServiceInstanceMessage ()
{
}

void AddExternalNonNativeServiceInstanceMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

    // This class Specific Attributes below

    addSerializableAttribute (new AttributeString       (&m_applicationName,          "applicationName"));
    addSerializableAttribute (new AttributeStringVector (&m_applicationInstanceNames, "applicationInstanceNames"));
}

const string &AddExternalNonNativeServiceInstanceMessage::getApplicationName () const
{
    return (m_applicationName);
}

void AddExternalNonNativeServiceInstanceMessage::setApplicationName (const string &applicationName)
{
    m_applicationName = applicationName;
}

const vector<string> &AddExternalNonNativeServiceInstanceMessage::getApplicationInstanceNames () const
{
    return (m_applicationInstanceNames);
}

void AddExternalNonNativeServiceInstanceMessage::setApplicationInstanceNames (const vector<string> &applicationInstanceNames)
{
    m_applicationInstanceNames = applicationInstanceNames;
}

}
