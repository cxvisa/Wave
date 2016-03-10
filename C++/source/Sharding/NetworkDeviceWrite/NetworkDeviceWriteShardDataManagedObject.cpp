/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Sharding/NetworkDeviceWrite/NetworkDeviceWriteShardDataManagedObject.h"
#include "Sharding/NetworkDeviceWrite/NetworkDeviceWriteShardingCategoryManagedObject.h"
#include "ServiceManagement/Local/ExternalNonNativeServiceInstanceManagedObject.h"

namespace WaveNs
{

NetworkDeviceWriteShardDataManagedObject::NetworkDeviceWriteShardDataManagedObject (WaveObjectManager *pWaveObjectManager)
    : WaveElement               (pWaveObjectManager),
      WavePersistableObject     (NetworkDeviceWriteShardDataManagedObject::getClassName (), ShardData::getClassName ()),
      WaveManagedObject         (pWaveObjectManager),
      ShardData (pWaveObjectManager)
{
}

NetworkDeviceWriteShardDataManagedObject::~NetworkDeviceWriteShardDataManagedObject ()
{
}

string NetworkDeviceWriteShardDataManagedObject::getClassName ()
{
    return ("NetworkDeviceWriteShardDataManagedObject");
}

void NetworkDeviceWriteShardDataManagedObject::setupAttributesForPersistence ()
{
    ShardData::setupAttributesForPersistence ();

    // This class Specific Attributes below

    addPersistableAttribute (new AttributeObjectIdAssociation (&m_networkDeviceWriteShardingCategory, "networkDeviceWriteShardingCategory", NetworkDeviceWriteShardingCategoryManagedObject::getClassName ()));
    addPersistableAttribute (new AttributeObjectIdAssociation (&m_serviceInstance,                    "serviceInstance",                    ExternalNonNativeServiceInstanceManagedObject::getClassName ()));
}

void NetworkDeviceWriteShardDataManagedObject::setupAttributesForCreate ()
{
    // This class Specific Attributes below

    addPersistableAttributeForCreate (new AttributeObjectIdAssociation (&m_networkDeviceWriteShardingCategory, "networkDeviceWriteShardingCategory", NetworkDeviceWriteShardingCategoryManagedObject::getClassName ()));
    addPersistableAttributeForCreate (new AttributeObjectIdAssociation (&m_serviceInstance,                    "serviceInstance",                    ExternalNonNativeServiceInstanceManagedObject::getClassName ()));
}

void NetworkDeviceWriteShardDataManagedObject::setupKeys ()
{
    vector<string> userDefinedKeyCombination;

    userDefinedKeyCombination.push_back ("name");
    userDefinedKeyCombination.push_back ("networkDeviceWriteShardingCategory");

    setUserDefinedKeyCombination (userDefinedKeyCombination);
}

}
