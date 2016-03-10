/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "ServiceManagement/Local/SetExternalNonNativeServiceInstanceShardingCapabilitiesMessage.h"
#include "Framework/Attributes/AttributeResourceId.h"
#include "ServiceManagement/Local/ServiceManagementLocalObjectManager.h"
#include "ServiceManagement/Local/ServiceManagementLocalTypes.h"

namespace WaveNs
{

SetExternalNonNativeServiceInstanceShardingCapabilitiesMessage::SetExternalNonNativeServiceInstanceShardingCapabilitiesMessage ()
    : ManagementInterfaceMessage (ServiceManagementLocalObjectManager::getServiceName (), SERVCIE_MANAGEMENT_LOCAL_SET_EXTERNAL_NON_NATIVE_SERVICE_INSTANCE_SHARDING_CAPABILITIES)
{
}

SetExternalNonNativeServiceInstanceShardingCapabilitiesMessage::SetExternalNonNativeServiceInstanceShardingCapabilitiesMessage (const string &applicationName, const string &applicationInstanceName, const vector<ResourceId> shardingCapabilities)

    : ManagementInterfaceMessage (ServiceManagementLocalObjectManager::getServiceName (), SERVCIE_MANAGEMENT_LOCAL_SET_EXTERNAL_NON_NATIVE_SERVICE_INSTANCE_SHARDING_CAPABILITIES),
      m_applicationName          (applicationName),
      m_applicationInstanceName  (applicationInstanceName),
      m_shardingCapabilities     (shardingCapabilities)
{
}

SetExternalNonNativeServiceInstanceShardingCapabilitiesMessage::~SetExternalNonNativeServiceInstanceShardingCapabilitiesMessage ()
{
}

void SetExternalNonNativeServiceInstanceShardingCapabilitiesMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeString           (&m_applicationName,         "applicationName"));
    addSerializableAttribute (new AttributeString           (&m_applicationInstanceName, "applicationInstanceName"));
    addSerializableAttribute (new AttributeResourceIdVector (&m_shardingCapabilities,    "shardingCapabilities"));
}

string SetExternalNonNativeServiceInstanceShardingCapabilitiesMessage::getApplicationName () const
{
    return (m_applicationName);
}

void SetExternalNonNativeServiceInstanceShardingCapabilitiesMessage::setApplicationName (const string &applicationName)
{
    m_applicationName = applicationName;
}

string SetExternalNonNativeServiceInstanceShardingCapabilitiesMessage::getApplicationInstanceName () const
{
    return (m_applicationInstanceName);
}

void SetExternalNonNativeServiceInstanceShardingCapabilitiesMessage::setApplicationInstanceName (const string &applicationInstanceName)
{
    m_applicationInstanceName = applicationInstanceName;
}

vector<ResourceId> SetExternalNonNativeServiceInstanceShardingCapabilitiesMessage::getShardingCapabilities () const
{
    return (m_shardingCapabilities);
}

void SetExternalNonNativeServiceInstanceShardingCapabilitiesMessage::setShardingCapabilities (const vector<ResourceId> shardingCapabilities)
{
    m_shardingCapabilities = shardingCapabilities;
}

}
