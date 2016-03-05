/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Sharding/NetworkDeviceRead/NetworkDeviceReadShardingObjectManager.h"
#include "Sharding/NetworkDeviceRead/NetworkDeviceReadShardingCategoryManagedObject.h"
#include "Sharding/NetworkDeviceRead/NetworkDeviceReadShardDataManagedObject.h"

namespace WaveNs
{

NetworkDeviceReadShardingObjectManager::NetworkDeviceReadShardingObjectManager ()
    : WaveObjectManager (getServiceName ())
{
    NetworkDeviceReadShardingCategoryManagedObject networkDeviceReadShardingCategoryManagedObject (this);
    NetworkDeviceReadShardDataManagedObject networkDeviceReadShardDataManagedObject (this);

    networkDeviceReadShardingCategoryManagedObject.setupOrm ();
    networkDeviceReadShardDataManagedObject.setupOrm ();

    addManagedClass (NetworkDeviceReadShardingCategoryManagedObject::getClassName());
    addManagedClass (NetworkDeviceReadShardDataManagedObject::getClassName());
}

NetworkDeviceReadShardingObjectManager::~NetworkDeviceReadShardingObjectManager ()
{
}

NetworkDeviceReadShardingObjectManager *NetworkDeviceReadShardingObjectManager:: getInstance ()
{
    static NetworkDeviceReadShardingObjectManager *pNetworkDeviceReadShardingObjectManagerObjectManager = new NetworkDeviceReadShardingObjectManager ();

    WaveNs::waveAssert (NULL != pNetworkDeviceReadShardingObjectManagerObjectManager, __FILE__, __LINE__);

    return (pNetworkDeviceReadShardingObjectManagerObjectManager);
}

WaveServiceId NetworkDeviceReadShardingObjectManager:: getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

string NetworkDeviceReadShardingObjectManager::getServiceName ()
{
    return ("Network Device Read Sharding");
}

}
