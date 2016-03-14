/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "ServiceManagement/Local/RemoveExternalNonNativeServiceInstanceMessage.h"
#include "ServiceManagement/Local/ServiceManagementLocalTypes.h"
#include "ServiceManagement/Local/ServiceManagementLocalObjectManager.h"

namespace WaveNs
{

RemoveExternalNonNativeServiceInstanceMessage::RemoveExternalNonNativeServiceInstanceMessage ()
    : ManagementInterfaceMessage (ServiceManagementLocalObjectManager::getServiceName (), SERVCIE_MANAGEMENT_LOCAL_REMOVE_EXTERNAL_NON_NATIVE_SERVICE_INSTANCE)
{
}

RemoveExternalNonNativeServiceInstanceMessage::RemoveExternalNonNativeServiceInstanceMessage (const string &applicationName, const string &applicationInstanceName)
    : ManagementInterfaceMessage (ServiceManagementLocalObjectManager::getServiceName (), SERVCIE_MANAGEMENT_LOCAL_REMOVE_EXTERNAL_NON_NATIVE_SERVICE_INSTANCE)
{
    m_applicationName = applicationName;
    m_applicationInstanceNames.push_back (applicationInstanceName);
}

RemoveExternalNonNativeServiceInstanceMessage::RemoveExternalNonNativeServiceInstanceMessage (const string &applicationName, const vector<string> &applicationInstanceNames)
    : ManagementInterfaceMessage (ServiceManagementLocalObjectManager::getServiceName (), SERVCIE_MANAGEMENT_LOCAL_REMOVE_EXTERNAL_NON_NATIVE_SERVICE_INSTANCE)
{
    m_applicationName          = applicationName;
    m_applicationInstanceNames = applicationInstanceNames;
}

RemoveExternalNonNativeServiceInstanceMessage::~RemoveExternalNonNativeServiceInstanceMessage ()
{
}

void RemoveExternalNonNativeServiceInstanceMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

    // This class Specific Attributes below

    addSerializableAttribute (new AttributeString       (&m_applicationName,          "applicationName"));
    addSerializableAttribute (new AttributeStringVector (&m_applicationInstanceNames, "applicationInstanceNames"));
}

const string &RemoveExternalNonNativeServiceInstanceMessage::getApplicationName () const
{
    return (m_applicationName);
}

void RemoveExternalNonNativeServiceInstanceMessage::setApplicationName (const string &applicationName)
{
    m_applicationName = applicationName;
}

const vector<string> &RemoveExternalNonNativeServiceInstanceMessage::getApplicationInstanceNames () const
{
    return (m_applicationInstanceNames);
}

void RemoveExternalNonNativeServiceInstanceMessage::setApplicationInstanceNames (const vector<string> &applicationInstanceNames)
{
    m_applicationInstanceNames = applicationInstanceNames;
}

}
