/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Sharding/NetworkDeviceRead/RequestForShardOwnerMessage.h"
#include "Framework/Attributes/AttributeResourceId.h"
#include "Sharding/NetworkDeviceRead/NetworkDeviceReadShardingObjectManager.h"
#include "Sharding/NetworkDeviceRead/NetworkDeviceReadShardingTypes.h"

namespace WaveNs
{

RequestForShardOwnerMessage::RequestForShardOwnerMessage ()
    : ManagementInterfaceMessage (NetworkDeviceReadShardingObjectManager::getServiceName (), NETWORK_DEVICE_READ_SHARDING_REQUEST_FOR_SHARD_OWNER)
{
}

RequestForShardOwnerMessage::RequestForShardOwnerMessage (const vector<string> &resourceNames, const ResourceId &shardingCategory)
    : ManagementInterfaceMessage (NetworkDeviceReadShardingObjectManager::getServiceName (), NETWORK_DEVICE_READ_SHARDING_REQUEST_FOR_SHARD_OWNER),
      m_resourceNames            (resourceNames),
      m_shardingCategory         (shardingCategory)
{
}

RequestForShardOwnerMessage::~RequestForShardOwnerMessage ()
{
}

void RequestForShardOwnerMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

    // This class Specific Attributes below

    addSerializableAttribute (new AttributeStringVector (&m_resourceNames,            "resourceNames"));
    addSerializableAttribute (new AttributeResourceId   (&m_shardingCategory,         "shardingCategory"));
    addSerializableAttribute (new AttributeStringVector (&m_applicationInstanceNames, "applicationInstanceNames"));
}

vector<string> RequestForShardOwnerMessage::getResourceNames () const
{
    return (m_resourceNames);
}

void RequestForShardOwnerMessage::setResourceNames (const vector<string> &resourceNames)
{
    m_resourceNames = resourceNames;
}

ResourceId RequestForShardOwnerMessage::getShardingCategory () const
{
    return (m_shardingCategory);
}

void RequestForShardOwnerMessage::setShardingCategory (const ResourceId &shardingCategory)
{
    m_shardingCategory = shardingCategory;
}

vector<string> RequestForShardOwnerMessage::getApplicationInstanceNames () const
{
    return (m_applicationInstanceNames);
}

void RequestForShardOwnerMessage::setApplicationInstanceNames (const vector<string> &applicationInstanceNames)
{
    m_applicationInstanceNames = applicationInstanceNames ;
}

}
