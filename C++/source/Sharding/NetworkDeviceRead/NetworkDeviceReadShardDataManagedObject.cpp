/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Sharding/NetworkDeviceRead/NetworkDeviceReadShardDataManagedObject.h"
#include "Sharding/NetworkDeviceRead/NetworkDeviceReadShardingCategoryManagedObject.h"
#include "ServiceManagement/Local/ExternalNonNativeServiceInstanceManagedObject.h"
#include "ServiceManagement/Global/ExternalNonNativeServiceManagedObject.h"

namespace WaveNs
{

NetworkDeviceReadShardDataManagedObject::NetworkDeviceReadShardDataManagedObject (WaveObjectManager *pWaveObjectManager)
    : WaveElement               (pWaveObjectManager),
      WavePersistableObject     (NetworkDeviceReadShardDataManagedObject::getClassName (), ShardData::getClassName ()),
      WaveManagedObject         (pWaveObjectManager),
      ShardData (pWaveObjectManager)
{
}

NetworkDeviceReadShardDataManagedObject::~NetworkDeviceReadShardDataManagedObject ()
{
}

string NetworkDeviceReadShardDataManagedObject::getClassName ()
{
    return ("NetworkDeviceReadShardDataManagedObject");
}

void NetworkDeviceReadShardDataManagedObject::setupAttributesForPersistence ()
{
    ShardData::setupAttributesForPersistence ();

    // This class Specific Attributes below

    addPersistableAttribute (new AttributeObjectIdAssociation (&m_networkDeviceReadShardingCategory, "networkDeviceReadShardingCategory", NetworkDeviceReadShardingCategoryManagedObject::getClassName ()));
    //addPersistableAttribute (new AttributeObjectIdAssociation (&m_service,                           "service",                           ExternalNonNativeServiceManagedObject::getClassName ()));
    addPersistableAttribute (new AttributeObjectIdAssociation (&m_serviceInstance,                   "serviceInstance",                   ExternalNonNativeServiceInstanceManagedObject::getClassName ()));
}

void NetworkDeviceReadShardDataManagedObject::setupAttributesForCreate ()
{
    // This class Specific Attributes below

    addPersistableAttributeForCreate (new AttributeObjectIdAssociation (&m_networkDeviceReadShardingCategory, "networkDeviceReadShardingCategory", NetworkDeviceReadShardingCategoryManagedObject::getClassName ()));
    //addPersistableAttributeForCreate (new AttributeObjectIdAssociation (&m_service,                           "service",                           ExternalNonNativeServiceManagedObject::getClassName ()));
    addPersistableAttributeForCreate (new AttributeObjectIdAssociation (&m_serviceInstance,                   "serviceInstance",                   ExternalNonNativeServiceInstanceManagedObject::getClassName ()));
}

void NetworkDeviceReadShardDataManagedObject::setupKeys ()
{
    vector<string> userDefinedKeyCombination;

    userDefinedKeyCombination.push_back ("name");
    userDefinedKeyCombination.push_back ("networkDeviceReadShardingCategory");

    setUserDefinedKeyCombination (userDefinedKeyCombination);
}

ObjectId NetworkDeviceReadShardDataManagedObject::getNetworkDeviceReadShardingCategory () const
{
    return (m_networkDeviceReadShardingCategory);
}

void NetworkDeviceReadShardDataManagedObject::setNetworkDeviceReadShardingCategory (const ObjectId &networkDeviceReadShardingCategory)
{
    m_networkDeviceReadShardingCategory = networkDeviceReadShardingCategory;
}

ObjectId NetworkDeviceReadShardDataManagedObject::getServiceInstance () const
{
    return (m_serviceInstance);
}

void NetworkDeviceReadShardDataManagedObject::setServiceInstance (const ObjectId &serviceInstance)
{
    m_serviceInstance = serviceInstance;
}

}
