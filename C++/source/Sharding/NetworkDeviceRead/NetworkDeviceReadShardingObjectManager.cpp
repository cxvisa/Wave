/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Sharding/NetworkDeviceRead/NetworkDeviceReadShardingObjectManager.h"
#include "Sharding/NetworkDeviceRead/NetworkDeviceReadShardWorker.h"
#include "Sharding/NetworkDeviceRead/RequestForShardOwnerWorker.h"

namespace WaveNs
{

NetworkDeviceReadShardingObjectManager::NetworkDeviceReadShardingObjectManager ()
    : WaveObjectManager (getServiceName ())
{
    m_pNetworkDeviceReadShardWorker = new NetworkDeviceReadShardWorker (this);

    waveAssert (NULL != m_pNetworkDeviceReadShardWorker, __FILE__, __LINE__);

    m_pRequestForShardOwnerWorker = new RequestForShardOwnerWorker (this);

    waveAssert (NULL != m_pRequestForShardOwnerWorker, __FILE__, __LINE__);
}

NetworkDeviceReadShardingObjectManager::~NetworkDeviceReadShardingObjectManager ()
{
    if (NULL != m_pNetworkDeviceReadShardWorker)
    {
        delete m_pNetworkDeviceReadShardWorker;
    }

    if (NULL != m_pRequestForShardOwnerWorker)
    {
        delete m_pRequestForShardOwnerWorker;
    }
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
