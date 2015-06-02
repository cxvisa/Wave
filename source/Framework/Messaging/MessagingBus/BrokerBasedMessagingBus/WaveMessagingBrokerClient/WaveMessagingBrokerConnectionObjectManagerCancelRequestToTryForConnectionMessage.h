/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMESSAGINGBROKERCONNECTIONOBJECTMANAGERCANCELREQUESTTOTRYFORCONNECTIONMESSAGE_H
#define WAVEMESSAGINGBROKERCONNECTIONOBJECTMANAGERCANCELREQUESTTOTRYFORCONNECTIONMESSAGE_H

#include "Framework/Messaging/Local/PrismMessage.h"

namespace WaveNs
{

class WaveMessagingBrokerConnectionObjectManagerCancelRequestToTryForConnectionMessage : public PrismMessage
{
    private :
    protected :
    public :
                                WaveMessagingBrokerConnectionObjectManagerCancelRequestToTryForConnectionMessage (const string &brokerName);
                                WaveMessagingBrokerConnectionObjectManagerCancelRequestToTryForConnectionMessage (const vector<string> &brokerNames);
        virtual                ~WaveMessagingBrokerConnectionObjectManagerCancelRequestToTryForConnectionMessage ();

                vector<string>  getBrokerNames                                                                   () const;
                void            setBrokerNames                                                                   (const vector<string> &brokerNames);
                void            addBrokerNames                                                                   (const vector<string> &brokerNames);
                void            addBrokerName                                                                    (const string &brokerName);

    // Now the data members

    private :
        vector<string> m_brokerNames;

    protected :
    public :
};
}

#endif //WAVEMESSAGINGBROKERCONNECTIONOBJECTMANAGERCANCELREQUESTTOTRYFORCONNECTIONMESSAGE_H
