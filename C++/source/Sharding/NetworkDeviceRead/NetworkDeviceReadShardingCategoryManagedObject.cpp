/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Sharding/NetworkDeviceRead/NetworkDeviceReadShardingCategoryManagedObject.h"
#include "Sharding/NetworkDeviceRead/NetworkDeviceReadShardDataManagedObject.h"

namespace WaveNs
{

NetworkDeviceReadShardingCategoryManagedObject::NetworkDeviceReadShardingCategoryManagedObject (WaveObjectManager *pWaveObjectManager)
    : WaveElement               (pWaveObjectManager),
      WavePersistableObject     (NetworkDeviceReadShardingCategoryManagedObject::getClassName (), ShardableResourceCategory::getClassName ()),
      WaveManagedObject         (pWaveObjectManager),
      ShardableResourceCategory (pWaveObjectManager)
{
}

NetworkDeviceReadShardingCategoryManagedObject::~NetworkDeviceReadShardingCategoryManagedObject ()
{
}

string NetworkDeviceReadShardingCategoryManagedObject::getClassName ()
{
    return ("NetworkDeviceReadShardingCategoryManagedObject");
}

void NetworkDeviceReadShardingCategoryManagedObject::setupAttributesForPersistence ()
{
    ShardableResourceCategory::setupAttributesForPersistence ();

    // This class Specific Attributes below

    addPersistableAttribute (new AttributeObjectIdVectorAggregation (&m_shardData, "shardData", getClassName (), getObjectId (), NetworkDeviceReadShardDataManagedObject::getClassName()));
}

void NetworkDeviceReadShardingCategoryManagedObject::setupAttributesForCreate ()
{
    // This class Specific Attributes below

    addPersistableAttributeForCreate (new AttributeObjectIdVectorAggregation (&m_shardData, "shardData", getClassName (), getObjectId (), NetworkDeviceReadShardDataManagedObject::getClassName()));
}

}
