/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Sharding/NetworkDeviceWrite/NetworkDeviceWriteShardingObjectManager.h"
#include "Sharding/NetworkDeviceWrite/NetworkDeviceWriteShardingCategoryManagedObject.h"
#include "Sharding/NetworkDeviceWrite/NetworkDeviceWriteShardDataManagedObject.h"

namespace WaveNs
{

NetworkDeviceWriteShardingObjectManager::NetworkDeviceWriteShardingObjectManager ()
    : WaveObjectManager (getServiceName ())
{
    NetworkDeviceWriteShardingCategoryManagedObject networkDeviceWriteShardingCategoryManagedObject (this);
    NetworkDeviceWriteShardDataManagedObject networkDeviceWriteShardDataManagedObject (this);

    networkDeviceWriteShardingCategoryManagedObject.setupOrm ();
    networkDeviceWriteShardDataManagedObject.setupOrm ();

    addManagedClass (NetworkDeviceWriteShardingCategoryManagedObject::getClassName());
    addManagedClass (NetworkDeviceWriteShardDataManagedObject::getClassName());
}

NetworkDeviceWriteShardingObjectManager::~NetworkDeviceWriteShardingObjectManager ()
{
}

NetworkDeviceWriteShardingObjectManager *NetworkDeviceWriteShardingObjectManager:: getInstance ()
{
    static NetworkDeviceWriteShardingObjectManager *pNetworkDeviceWriteShardingObjectManagerObjectManager = new NetworkDeviceWriteShardingObjectManager ();

    WaveNs::waveAssert (NULL != pNetworkDeviceWriteShardingObjectManagerObjectManager, __FILE__, __LINE__);

    return (pNetworkDeviceWriteShardingObjectManagerObjectManager);
}

WaveServiceId NetworkDeviceWriteShardingObjectManager:: getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

string NetworkDeviceWriteShardingObjectManager::getServiceName ()
{
    return ("Network Device Write Sharding");
}

}
