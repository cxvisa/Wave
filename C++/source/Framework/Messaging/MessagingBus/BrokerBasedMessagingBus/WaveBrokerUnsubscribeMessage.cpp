/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveBrokerUnsubscribeMessage.h"

namespace WaveNs
{

WaveBrokerUnsubscribeMessage::WaveBrokerUnsubscribeMessage ()
    : WaveBrokerBasedMessage (WAVE_BROKER_BASED_MESSAGING_BUS_MESSAGE_TYPE_UNSUBSCRIBE)
{
}

WaveBrokerUnsubscribeMessage::WaveBrokerUnsubscribeMessage (const string &topicName)
    : WaveBrokerBasedMessage (WAVE_BROKER_BASED_MESSAGING_BUS_MESSAGE_TYPE_UNSUBSCRIBE),
      m_topicName            (topicName)
{
}

WaveBrokerUnsubscribeMessage::~WaveBrokerUnsubscribeMessage ()
{
}

void WaveBrokerUnsubscribeMessage::setupAttributesForSerialization ()
{
    WaveBrokerBasedMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeString (&m_topicName, "topicName"));
}

string WaveBrokerUnsubscribeMessage::getTopicName () const
{
    return (m_topicName);
}

WaveBrokerBasedMessage *WaveBrokerUnsubscribeMessage::createMessageInstance ()
{
    return (new WaveBrokerUnsubscribeMessage ());
}

}
