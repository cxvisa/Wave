/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMESSAGINGBROKERCLIENTREPOSITORY_H
#define WAVEMESSAGINGBROKERCLIENTREPOSITORY_H

#include "Framework/Types/Types.h"
#include "Framework/Utils/WaveMutex.h"

#include <map>
#include <string>

using namespace std;

namespace WaveNs
{

class WaveMessagingBrokerClient;

class WaveMessagingBrokerClientRepository
{
    private :
        WaveMessagingBrokerClientRepository ();

    protected :
    public :
                                                   ~WaveMessagingBrokerClientRepository         ();

        static string                               getWaveMessagingBrokerClientUniqueString    (const string &ipAddress, const SI32 &port);
               bool                                 isAKnownWaveMessagingBrokerClient           (const string &ipAddress, const SI32 &port);
               void                                 addWaveMessagingBrokerClient                (const string &name, const string &ipAddress, const SI32 &port);
               bool                                 addWaveMessagingBrokerClientIfNotKnown      (const string &name, const string &ipAddress, const SI32 &port);
               void                                 removeWaveMessagingBrokerClient             (const string &ipAddress, const SI32 &port);
               void                                 addWaveMessagingBrokerClientSubscription    (const string &ipAddress, const SI32 &port, const string &subscriptionTopic);
               void                                 removeWaveMessagingBrokerClientSubscription (const string &ipAddress, const SI32 &port, const string &subscriptionTopic);

               WaveMessagingBrokerClient           *checkoutWaveMessagingBrokerClient           (const string &ipAddress, const SI32 &port);
               WaveMessagingBrokerClient           *checkoutWaveMessagingBrokerClient           (const string &waveMessagingBrokerClientUniqueString);
               void                                 checkinWaveMessagingBrokerClient            (WaveMessagingBrokerClient *pWaveMessagingBrokerClient);

        static WaveMessagingBrokerClientRepository *getInstance                                 ();

               void                                 print                                       ();

    // Now the data members

    private :
        map<string, WaveMessagingBrokerClient *> m_waveMessagingBrokerClientsMap;

        WaveMutex                               m_waveMessagingBrokerClientsMutex;

    protected :
    public :
};

}

#endif // WAVEMESSAGINGBROKERCLIENTREPOSITORY_H
