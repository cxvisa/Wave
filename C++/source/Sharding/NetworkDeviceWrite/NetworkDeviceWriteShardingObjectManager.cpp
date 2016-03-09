/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Sharding/NetworkDeviceWrite/NetworkDeviceWriteShardingObjectManager.h"
#include "Sharding/NetworkDeviceWrite/NetworkDeviceWriteShardWorker.h"
#include "Sharding/NetworkDeviceWrite/NetworkDeviceWriteShardingCategoryManagedObject.h"
#include "Sharding/NetworkDeviceWrite/NetworkDeviceWriteShardDataManagedObject.h"

namespace WaveNs
{

NetworkDeviceWriteShardingObjectManager::NetworkDeviceWriteShardingObjectManager ()
    : WaveObjectManager (getServiceName ())
{
    m_pNetworkDeviceWriteShardWorker = new NetworkDeviceWriteShardWorker (this);

    waveAssert (NULL != m_pNetworkDeviceWriteShardWorker, __FILE__, __LINE__);
}

NetworkDeviceWriteShardingObjectManager::~NetworkDeviceWriteShardingObjectManager ()
{
    if (NULL != m_pNetworkDeviceWriteShardWorker)
    {
        delete m_pNetworkDeviceWriteShardWorker;
    }
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
