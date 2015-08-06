/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMESSAGINGBROKERCLIENT_H
#define WAVEMESSAGINGBROKERCLIENT_H

#include "Framework/Types/Types.h"
#include "Framework/Utils/WaveMutex.h"

#include <map>
#include <string>

using namespace std;

namespace WaveNs
{

class ClientStreamingSocket;
class WaveBrokerPublishMessage;
class WaveBrokerBasedMessagePayload;

class WaveMessagingBrokerClient
{
    private :
    protected :
    public :
                    WaveMessagingBrokerClient       (const string &name, const string &ipAddress, const SI32 &port);
                   ~WaveMessagingBrokerClient       ();

        string      getName                         () const;
        void        setName                         (const string &name);

        string      getIpAddress                    () const;
        void        setIpAddress                    (const string &ipAddress);

        SI32        getPort                         () const;
        void        setPort                         (const SI32 &port);

        bool        isAKnownSubscriptionTopic       (const string &subscriptionTopic) const;
        void        addSubscriptionTopic            (const string &subscriptionTopic);
        void        removeSubscriptionTopic         (const string &subscriptionTopic);
        void        removeAllSubscriptionTopics     ();

        string      getUniqueString                 () const;

        ResourceId  connect                         (const UI32 &numberOfRetries = 0, const UI32 &maximumNumberOfSecondsToTryFor = 0);
        void        indicateClosing                 ();

        void        checkout                        ();
        void        checkin                         ();

        UI32        getNumberOfOutstandingCheckouts ();

        bool        operator <<                     (WaveBrokerPublishMessage      *pWaveBrokerPublishMessage);
        bool        operator <<                     (WaveBrokerBasedMessagePayload *pWaveBrokerBasedMessagePayload);

        void        getAllSubscribedTopics          (vector<string> &allSubscribedTopics);


        // Now the data members

    private :
        string                 m_name;
        string                 m_ipAddress;
        SI32                   m_port;
        map<string, string>    m_subscriptionTopics;
        ClientStreamingSocket *m_pClientStreamingSocket;
        WaveMutex             m_mutex;
        UI32                   m_numberOfOutstandingCheckouts;


    protected :
    public :
};

}

#endif // WAVEMESSAGINGBROKERCLIENT_H
