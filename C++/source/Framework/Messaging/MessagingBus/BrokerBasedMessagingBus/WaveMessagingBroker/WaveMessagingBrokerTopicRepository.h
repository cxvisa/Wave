/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMESSAGINGBROKERTOPICREPOSITORY_H
#define WAVEMESSAGINGBROKERTOPICREPOSITORY_H

#include "Framework/Types/Types.h"
#include "Framework/Utils/WaveMutex.h"

#include <map>
#include <string>

using namespace std;

namespace WaveNs
{

class WaveMessagingBrokerTopic;

class WaveMessagingBrokerTopicRepository
{
    private :
        WaveMessagingBrokerTopicRepository ();

    protected :
    public :
                                                   ~WaveMessagingBrokerTopicRepository    ();

                bool                                isAKnownWaveMessagingBrokerTopic      (const string &waveMessagingBrokerTopicName);
                void                                addWaveMessagingBrokerTopic           (const string &waveMessagingBrokerTopicName, const string &clientUniqueString);
                void                                addWaveMessagingBrokerTopicIfNotKnown (const string &waveMessagingBrokerTopicName, const string &clientUniqueString);
                void                                removeWaveMessagingBrokerTopic        (const string &waveMessagingBrokerTopicName, const string &clientUniqueString);
                void                                removeWaveMessagingBrokerTopicIfKnown (const string &waveMessagingBrokerTopicName, const string &clientUniqueString);
                void                                getCurrentlySubscribedClientsForTopic (const string &waveMessagingBrokerTopicName, vector<string> &currentlySubscribedClients);

        static  WaveMessagingBrokerTopicRepository *getInstance                           ();

    // Now the data members

    private :
        map<string, WaveMessagingBrokerTopic *> m_waveMesasgingBrokerTopics;
        WaveMutex                              m_waveMesasgingBrokerTopicsMutex;

    protected :
    public :
};
}

#endif // WAVEMESSAGINGBROKERTOPICREPOSITORY_H
