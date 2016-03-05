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
    protected:
    public:
};

}

#endif // NETWORKDEVICEREADSHARDINGOBJECTMANAGER_H
