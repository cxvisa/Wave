/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveBrokerSubscribeMessage.h"
#include "Framework/Attributes/Attributes.h"

namespace WaveNs
{

WaveBrokerSubscribeMessage::WaveBrokerSubscribeMessage ()
    : WaveBrokerBasedMessage (WAVE_BROKER_BASED_MESSAGING_BUS_MESSAGE_TYPE_SUBSCRIBE)
{
}

WaveBrokerSubscribeMessage::WaveBrokerSubscribeMessage (const vector<string> &topicNames)
    : WaveBrokerBasedMessage (WAVE_BROKER_BASED_MESSAGING_BUS_MESSAGE_TYPE_SUBSCRIBE),
      m_topicNames           (topicNames)
{
}

WaveBrokerSubscribeMessage::WaveBrokerSubscribeMessage (const string &topicName)
    : WaveBrokerBasedMessage (WAVE_BROKER_BASED_MESSAGING_BUS_MESSAGE_TYPE_SUBSCRIBE)
{
    m_topicNames.push_back (topicName);
}

WaveBrokerSubscribeMessage::~WaveBrokerSubscribeMessage ()
{
}

void WaveBrokerSubscribeMessage::setupAttributesForSerialization ()
{
    WaveBrokerBasedMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeStringVector (&m_topicNames, "topicNames"));
}

vector<string> WaveBrokerSubscribeMessage::getTopicNames () const
{
    return (m_topicNames);
}

void WaveBrokerSubscribeMessage::setTopicNames (const vector<string> &topicNames)
{
    m_topicNames = topicNames;
}

void WaveBrokerSubscribeMessage::addTopicNames (const vector<string> &topicNames)
{
    m_topicNames.insert (m_topicNames.end (), topicNames.begin (), topicNames.end ());
}

WaveBrokerBasedMessage *WaveBrokerSubscribeMessage::createMessageInstance ()
{
    return (new WaveBrokerSubscribeMessage ());
}

}
