/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveBrokerBasedEvent.h"

namespace WaveNs
{

WaveBrokerBasedEvent::WaveBrokerBasedEvent (const string &topic)
    : SerializableObject (),
      m_topic            (topic)
{
}

WaveBrokerBasedEvent::~WaveBrokerBasedEvent ()
{
}

string WaveBrokerBasedEvent::getTopic () const
{
    return (m_topic);
}

void WaveBrokerBasedEvent::setTopic (const string &topic)
{
    m_topic = topic;
}

void WaveBrokerBasedEvent::setupAttributesForSerialization ()
{
    SerializableObject::setupAttributesForSerialization ();
}

}
