/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Sharding/NetworkDeviceRead/NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage.h"
#include "Sharding/NetworkDeviceRead/NetworkDeviceReadShardingObjectManager.h"
#include "Sharding/NetworkDeviceRead/NetworkDeviceReadShardingTypes.h"

namespace WaveNs
{

NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage::NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage ()
    : ManagementInterfaceMessage (NetworkDeviceReadShardingObjectManager::getServiceName (), NETWORK_DEVICE_READ_SHARDING_DELETE_SHARD_DATA_FOR_SHARD_OWNER)
{
}

NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage::NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage (const ObjectId &serviceInstanceObjectId)
    : ManagementInterfaceMessage (NetworkDeviceReadShardingObjectManager::getServiceName (), NETWORK_DEVICE_READ_SHARDING_DELETE_SHARD_DATA_FOR_SHARD_OWNER)
{
    m_serviceInstanceObjectIds.push_back (serviceInstanceObjectId);
}

NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage::NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage (const vector<ObjectId> &serviceInstanceObjectIds)
    : ManagementInterfaceMessage (NetworkDeviceReadShardingObjectManager::getServiceName (), NETWORK_DEVICE_READ_SHARDING_DELETE_SHARD_DATA_FOR_SHARD_OWNER),
      m_serviceInstanceObjectIds (serviceInstanceObjectIds)
{
}

NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage::~NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage ()
{
}

void NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

    // This class Specific Attributes below

    addSerializableAttribute (new AttributeObjectIdVector (&m_serviceInstanceObjectIds, "serviceInstanceObjectIds"));
}

vector<ObjectId> NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage::getServiceInstanceObjectIds () const
{
    return (m_serviceInstanceObjectIds);
}

void NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage::setServiceInstanceObjectIds (const vector<ObjectId> &serviceInstanceObjectIds)
{
    m_serviceInstanceObjectIds = serviceInstanceObjectIds;
}

}
