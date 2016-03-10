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

RequestForShardOwnerMessage::RequestForShardOwnerMessage (const string &resourceName, const ResourceId &shardingCategory)
    : ManagementInterfaceMessage (NetworkDeviceReadShardingObjectManager::getServiceName (), NETWORK_DEVICE_READ_SHARDING_REQUEST_FOR_SHARD_OWNER),
      m_resourceName             (resourceName),
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

    addSerializableAttribute (new AttributeString     (&m_resourceName,            "resourceName"));
    addSerializableAttribute (new AttributeResourceId (&m_shardingCategory,        "shardingCategory"));
    addSerializableAttribute (new AttributeString     (&m_applicationInstanceName, "applicationInstanceName"));
}

string RequestForShardOwnerMessage::getResourceName () const
{
    return (m_resourceName);
}

void RequestForShardOwnerMessage::setResourceName (const string &resourceName)
{
    m_resourceName = resourceName;
}

ResourceId RequestForShardOwnerMessage::getShardingCategory () const
{
    return (m_shardingCategory);
}

void RequestForShardOwnerMessage::setShardingCategory (const ResourceId &shardingCategory)
{
    m_shardingCategory = shardingCategory;
}

string RequestForShardOwnerMessage::getApplicationInstanceName () const
{
    return (m_applicationInstanceName);
}

void  RequestForShardOwnerMessage::setApplicationInstanceName (const string &applicationInstanceName)
{
    m_applicationInstanceName = applicationInstanceName;
}

}
