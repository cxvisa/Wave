/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef NETWORKDEVICEREADSHARDINGOBJECTMANAGER_H
#define NETWORKDEVICEREADSHARDINGOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveObjectManager.h"

namespace WaveNs
{

class NetworkDeviceReadShardWorker;
class RequestForShardOwnerWorker;

class NetworkDeviceReadShardingObjectManager : public WaveObjectManager
{
    private:
        NetworkDeviceReadShardingObjectManager ();

    protected:
    public:
        virtual ~NetworkDeviceReadShardingObjectManager ();

        static NetworkDeviceReadShardingObjectManager *getInstance      ();
        static WaveServiceId                           getWaveServiceId ();
        static string                                  getServiceName   ();

        // Now the Data Members

    private:
        NetworkDeviceReadShardWorker *m_pNetworkDeviceReadShardWorker;
        RequestForShardOwnerWorker   *m_pRequestForShardOwnerWorker;

    protected:
    public:
};

}

#endif // NETWORKDEVICEREADSHARDINGOBJECTMANAGER_H
