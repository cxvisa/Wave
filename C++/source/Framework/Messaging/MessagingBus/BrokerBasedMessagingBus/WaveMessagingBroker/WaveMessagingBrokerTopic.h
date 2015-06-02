/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMESSAGINGBROKERTOPIC_H
#define WAVEMESSAGINGBROKERTOPIC_H

#include "Framework/Types/Types.h"
#include "Framework/Utils/PrismMutex.h"

#include <map>
#include <string>

using namespace std;

namespace WaveNs
{

class WaveMessagingBrokerClient;

class WaveMessagingBrokerTopic
{
    private :
    protected :
    public :
              WaveMessagingBrokerTopic     (const string &name);
             ~WaveMessagingBrokerTopic     ();

        bool  isAKnownSubscription         (const string &ipAddress, const SI32 &port) const;
        void  addSubscription              (const string &ipAddress, const SI32 &port);
        void  addSubscription              (const string &uniqueString);
        void  removeSubscription           (const string &ipAddress, const SI32 &port);
        void  removeSubscription           (const string &uniqueString);
        void  getSubscribedClients         (vector<string> &subscribedClients) const;
        UI32  getNumberOfSubscribedClients () const;

    // Now the data members

    private :
        string              m_name;
        map<string, string> m_subscribedClients;

    protected :
    public :
};

}

#endif // WAVEMESSAGINGBROKERTOPIC_H
