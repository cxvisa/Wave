/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 ***************************************************************************/

#ifndef WAVESERVICEMAP_H
#define WAVESERVICEMAP_H

#include <map>
#include <string>
#include <vector>
#include "Framework/Types/Types.h"
#include "Framework/Utils/WaveMutex.h"
#include "Framework/MultiThreading/WaveThreadStatus.h"

using namespace std;

namespace WaveNs
{

class WaveThread;

class WaveServiceMap
{
    private :
    protected :
    public :
                           WaveServiceMap                 ();
                          ~WaveServiceMap                 ();
        void               addServiceMap                   (WaveServiceId id, WaveThread *pWaveThread, const string &serviceName);
        void               removeServiceMap                (WaveServiceId id);
        void               getListOfServiceIds             (vector<WaveServiceId> &serviceIds);
        WaveThread       *getWaveThreadForServiceId      (WaveServiceId id);
        string             getWaveServiceNameForServiceId (const WaveServiceId &id);
        WaveServiceId     getWaveServiceIdForServiceName (const string &serviceName);
        WaveThreadStatus  joinAllThreads                   ();

    // Now the data members

    private :
        map<WaveServiceId, WaveThread *> m_servicesMap;
        map<WaveServiceId, string>        m_servicesNameMap;
        map<string, WaveServiceId>        m_servicesIdMap;
        WaveMutex                         m_mutex;

    protected :
    public:
};

}

#endif //WAVESERVICEMAP_H
