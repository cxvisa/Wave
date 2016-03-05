/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Sharding/NetworkDeviceWrite/NetworkDeviceWriteShardingCategoryManagedObject.h"
#include "Sharding/NetworkDeviceWrite/NetworkDeviceWriteShardDataManagedObject.h"

namespace WaveNs
{

NetworkDeviceWriteShardingCategoryManagedObject::NetworkDeviceWriteShardingCategoryManagedObject (WaveObjectManager *pWaveObjectManager)
    : WaveElement               (pWaveObjectManager),
      WavePersistableObject     (NetworkDeviceWriteShardingCategoryManagedObject::getClassName (), ShardableResourceCategory::getClassName ()),
      WaveManagedObject         (pWaveObjectManager),
      ShardableResourceCategory (pWaveObjectManager)
{
}

NetworkDeviceWriteShardingCategoryManagedObject::~NetworkDeviceWriteShardingCategoryManagedObject ()
{
}

string NetworkDeviceWriteShardingCategoryManagedObject::getClassName ()
{
    return ("NetworkDeviceWriteShardingCategoryManagedObject");
}

void NetworkDeviceWriteShardingCategoryManagedObject::setupAttributesForPersistence ()
{
    ShardableResourceCategory::setupAttributesForPersistence ();

    // This class Specific Attributes below

    addPersistableAttribute (new AttributeObjectIdVectorAggregation (&m_shardData, "shardData", getClassName (), getObjectId (), NetworkDeviceWriteShardDataManagedObject::getClassName()));
}

void NetworkDeviceWriteShardingCategoryManagedObject::setupAttributesForCreate ()
{
    // This class Specific Attributes below

    addPersistableAttributeForCreate (new AttributeObjectIdVectorAggregation (&m_shardData, "shardData", getClassName (), getObjectId (), NetworkDeviceWriteShardDataManagedObject::getClassName()));
}

}
