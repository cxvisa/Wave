/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/Multicast/WaveMulticastMessage.h"

namespace WaveNs
{

WaveMulticastMessage::WaveMulticastMessage (const string &topic)
    : SerializableObject (),
      m_topic            (topic)
{
}

WaveMulticastMessage::~WaveMulticastMessage ()
{
}

string WaveMulticastMessage::getTopic () const
{
    return (m_topic);
}

void WaveMulticastMessage::setTopic (const string &topic)
{
    m_topic = topic;
}

void WaveMulticastMessage::setupAttributesForSerialization ()
{
    SerializableObject::setupAttributesForSerialization ();
}

}
