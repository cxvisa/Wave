/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 ***************************************************************************/

#ifndef PRISMSERVICEMAP_H
#define PRISMSERVICEMAP_H

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

class PrismServiceMap
{
    private :
    protected :
    public :
                           PrismServiceMap                 ();
                          ~PrismServiceMap                 ();
        void               addServiceMap                   (PrismServiceId id, PrismThread *pPrismThread, const string &serviceName);
        void               removeServiceMap                (PrismServiceId id);
        void               getListOfServiceIds             (vector<PrismServiceId> &serviceIds);
        PrismThread       *getPrismThreadForServiceId      (PrismServiceId id);
        string             getPrismServiceNameForServiceId (const PrismServiceId &id);
        PrismServiceId     getPrismServiceIdForServiceName (const string &serviceName);
        WaveThreadStatus  joinAllThreads                   ();

    // Now the data members

    private :
        map<PrismServiceId, PrismThread *> m_servicesMap;
        map<PrismServiceId, string>        m_servicesNameMap;
        map<string, PrismServiceId>        m_servicesIdMap;
        PrismMutex                         m_mutex;

    protected :
    public:
};

}

#endif //PRISMSERVICEMAP_H
