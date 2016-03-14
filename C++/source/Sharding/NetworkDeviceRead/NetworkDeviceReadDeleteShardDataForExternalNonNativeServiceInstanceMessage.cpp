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
    : ManagementInterfaceMessage (NetworkDeviceReadShardingObjectManager::getServiceName (), NETWORK_DEVICE_READ_SHARDING_DELETE_SHARD_DATA_FOR_SHARD_OWNER),
      m_serviceInstanceObjectId (serviceInstanceObjectId)
{
}

NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage::~NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage ()
{
}

void NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

    // This class Specific Attributes below

    addSerializableAttribute (new AttributeObjectId (&m_serviceInstanceObjectId, "serviceInstanceObjectId"));
}

ObjectId NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage::getServiceInstanceObjectId () const
{
    return (m_serviceInstanceObjectId);
}

void NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage::setServiceInstanceObjectId (const ObjectId &serviceInstanceObjectId)
{
    m_serviceInstanceObjectId = serviceInstanceObjectId;
}

}
