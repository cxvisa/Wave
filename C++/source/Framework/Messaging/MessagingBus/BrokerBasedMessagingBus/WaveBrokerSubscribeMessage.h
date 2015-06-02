/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEBROKERSUBSCRIBEMESSAGE_H
#define WAVEBROKERSUBSCRIBEMESSAGE_H

#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveBrokerBasedMessage.h"

#include <vector>

using namespace std;

namespace WaveNs
{

class WaveBrokerSubscribeMessage : public WaveBrokerBasedMessage
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
    public :
                                        WaveBrokerSubscribeMessage ();
                                        WaveBrokerSubscribeMessage (const vector<string> &topicNames);
                                        WaveBrokerSubscribeMessage (const string &topicName);
        virtual                        ~WaveBrokerSubscribeMessage ();

                vector<string>          getTopicNames              () const;
                void                    setTopicNames              (const vector<string> &topicNames);
                void                    addTopicNames              (const vector<string> &topicNames);

        static  WaveBrokerBasedMessage *createMessageInstance      ();

    // now the data members

    private :
        vector<string> m_topicNames;

    protected :
    public :
};

}

#endif // WAVEBROKERSUBSCRIBEMESSAGE_H
