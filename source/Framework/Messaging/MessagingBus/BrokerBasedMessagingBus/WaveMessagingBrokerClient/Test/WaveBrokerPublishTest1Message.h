/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEBROKERPUBLISHTEST1MESSAGE_H
#define WAVEBROKERPUBLISHTEST1MESSAGE_H

#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveBrokerPublishMessage.h"

namespace WaveNs
{

class WaveBrokerPublishTest1Message : public WaveBrokerPublishMessage
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
    public :
                                          WaveBrokerPublishTest1Message ();
        virtual                          ~WaveBrokerPublishTest1Message ();

        static  WaveBrokerPublishMessage *createMessageInstance         ();

                string                    getMessageToBePublished       () const;
                void                      setMessageToBePublished       (const string &messagetoBePublished);

                UI32                      getSequenceNumber             () const;
                void                      setSequenceNumber             (const UI32 &sequenceNumber);

    // now the data members

    private :
        string m_messageToBePublished;
        UI32   m_sequenceNumber;

    protected :
    public :
};

}

#endif // WAVEBROKERPUBLISHTEST1MESSAGE_H
