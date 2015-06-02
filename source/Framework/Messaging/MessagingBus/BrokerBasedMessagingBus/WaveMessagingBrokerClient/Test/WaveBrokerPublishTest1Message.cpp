/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveMessagingBrokerClient/Test/WaveBrokerPublishTest1Message.h"

namespace WaveNs
{

WaveBrokerPublishTest1Message::WaveBrokerPublishTest1Message ()
    : WaveBrokerPublishMessage ("WaveBrokerPublishTest1Message"),
      m_sequenceNumber         (0)
{
}

WaveBrokerPublishTest1Message::~WaveBrokerPublishTest1Message ()
{
}

void WaveBrokerPublishTest1Message::setupAttributesForSerialization ()
{
    WaveBrokerPublishMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeString (&m_messageToBePublished, "messageToBePublished"));
    addSerializableAttribute (new AttributeUI32   (&m_sequenceNumber,       "sequenceNumber"));
}

WaveBrokerPublishMessage *WaveBrokerPublishTest1Message::createMessageInstance ()
{
    return (new WaveBrokerPublishTest1Message ());
}

string WaveBrokerPublishTest1Message::getMessageToBePublished () const
{
    return (m_messageToBePublished);
}

void WaveBrokerPublishTest1Message::setMessageToBePublished (const string &messageToBePublished)
{
    m_messageToBePublished = messageToBePublished;
}

UI32 WaveBrokerPublishTest1Message::getSequenceNumber () const
{
    return (m_sequenceNumber);
}

void WaveBrokerPublishTest1Message::setSequenceNumber (const UI32 &sequenceNumber)
{
    m_sequenceNumber = sequenceNumber;
}

}
