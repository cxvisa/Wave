/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMESSAGINGBROKERCONNECTIONOBJECTMANAGERREQUESTTOTRYFORCONNECTIONMESSAGE_H
#define WAVEMESSAGINGBROKERCONNECTIONOBJECTMANAGERREQUESTTOTRYFORCONNECTIONMESSAGE_H

#include "Framework/Messaging/Local/PrismMessage.h"

namespace WaveNs
{

class WaveMessagingBrokerConnectionObjectManagerRequestToTryForConnectionMessage : public PrismMessage
{
    private :
    protected :
    public :
                                WaveMessagingBrokerConnectionObjectManagerRequestToTryForConnectionMessage (const string &brokerName);
                                WaveMessagingBrokerConnectionObjectManagerRequestToTryForConnectionMessage (const vector<string> &brokerNames);
        virtual                ~WaveMessagingBrokerConnectionObjectManagerRequestToTryForConnectionMessage ();

                vector<string>  getBrokerNames                                                             () const;
                void            setBrokerNames                                                             (const vector<string> &brokerNames);
                void            addBrokerNames                                                             (const vector<string> &brokerNames);
                void            addBrokerName                                                              (const string &brokerName);

    // Now the data members

    private :
        vector<string> m_brokerNames;

    protected :
    public :
};
}

#endif //WAVEMESSAGINGBROKERCONNECTIONOBJECTMANAGERREQUESTTOTRYFORCONNECTIONMESSAGE_H
