/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEBROKERUNSUBSCRIBEMESSAGE_H
#define WAVEBROKERUNSUBSCRIBEMESSAGE_H

#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveBrokerBasedMessage.h"

namespace WaveNs
{

class WaveBrokerUnsubscribeMessage : public WaveBrokerBasedMessage
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
    public :
                                        WaveBrokerUnsubscribeMessage ();
                                        WaveBrokerUnsubscribeMessage (const string &topicName);
        virtual                        ~WaveBrokerUnsubscribeMessage ();

                string                  getTopicName                 () const;

        static  WaveBrokerBasedMessage *createMessageInstance        ();

    // now the data members

    private :
        string m_topicName;

    protected :
    public :
};

}

#endif // WAVEBROKERUNSUBSCRIBEMESSAGE_H
