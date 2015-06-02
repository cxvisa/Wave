/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEBROKERPUBLISHMESSAGE_H
#define WAVEBROKERPUBLISHMESSAGE_H

#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveBrokerBasedMessage.h"
#include "Framework/Utils/PrismMutex.h"

namespace WaveNs
{

class WaveBrokerPublishMessage : public WaveBrokerBasedMessage
{
    private :
    protected :
        virtual void        setupAttributesForSerialization ();

    public :
                                        WaveBrokerPublishMessage  ();
                                        WaveBrokerPublishMessage  (const string &topicName);
        virtual                        ~WaveBrokerPublishMessage  ();

                string                  getTopicName              () const;

        static  WaveBrokerBasedMessage *createMessageInstance     ();

                string                   getBrokerName            () const;
                void                     setBrokerName            (const string &brokerName);

                void                     incrementReferenceCount  ();
                void                     setReferenceCount        (const UI32 &referenceCount);
                void                     decrementReferenceCount  ();
                void                     garbageCollect           () const;

                const char              *getPMessageBuffer        ();
                void                     setPMessageBuffer        (const char *pMessageBuffer);

                void                     loadFromSerializedData2 ();

    // now the data members

    private :
        string m_topicName;

        // Non serialized members

        string     m_brokerName;

        PrismMutex m_mutex;
        UI32       m_referenceCount;

        const char *m_pMessageBuffer;

    protected :
    public :
};

}

#endif // WAVEBROKERPUBLISHMESSAGE_H
