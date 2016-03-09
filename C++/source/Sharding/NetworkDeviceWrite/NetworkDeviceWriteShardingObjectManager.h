/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef NETWORKDEVICEWRITESHARDINGOBJECTMANAGER_H
#define NETWORKDEVICEWRITESHARDINGOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveObjectManager.h"

namespace WaveNs
{

class NetworkDeviceWriteShardWorker;

class NetworkDeviceWriteShardingObjectManager : public WaveObjectManager
{
    private:
        NetworkDeviceWriteShardingObjectManager ();

    protected:
    public:
        virtual ~NetworkDeviceWriteShardingObjectManager ();

        static NetworkDeviceWriteShardingObjectManager *getInstance      ();
        static WaveServiceId                            getWaveServiceId ();
        static string                                   getServiceName   ();

        // Now the Data Members

    private:
        NetworkDeviceWriteShardWorker *m_pNetworkDeviceWriteShardWorker;

    protected:
    public:
};

}

#endif // NETWORKDEVICEWRITESHARDINGOBJECTMANAGER_H
