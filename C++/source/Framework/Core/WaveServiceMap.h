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
#include "Framework/Utils/PrismMutex.h"
#include "Framework/MultiThreading/WaveThreadStatus.h"

using namespace std;

namespace WaveNs
{

class PrismThread;

class WaveServiceMap
{
    private :
    protected :
    public :
                           WaveServiceMap                 ();
                          ~WaveServiceMap                 ();
        void               addServiceMap                   (WaveServiceId id, PrismThread *pPrismThread, const string &serviceName);
        void               removeServiceMap                (WaveServiceId id);
        void               getListOfServiceIds             (vector<WaveServiceId> &serviceIds);
        PrismThread       *getPrismThreadForServiceId      (WaveServiceId id);
        string             getPrismServiceNameForServiceId (const WaveServiceId &id);
        WaveServiceId     getWaveServiceIdForServiceName (const string &serviceName);
        WaveThreadStatus  joinAllThreads                   ();

    // Now the data members

    private :
        map<WaveServiceId, PrismThread *> m_servicesMap;
        map<WaveServiceId, string>        m_servicesNameMap;
        map<string, WaveServiceId>        m_servicesIdMap;
        PrismMutex                         m_mutex;

    protected :
    public:
};

}

#endif //WAVESERVICEMAP_H
