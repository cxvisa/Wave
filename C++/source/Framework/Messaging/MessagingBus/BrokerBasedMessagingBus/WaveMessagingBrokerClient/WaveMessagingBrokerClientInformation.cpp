/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveMessagingBrokerClient/WaveMessagingBrokerClientInformation.h"
#include "Framework/ObjectModel/SerializableObject.h"

namespace WaveNs
{

WaveMessagingBrokerClientInformation::WaveMessagingBrokerClientInformation ()
    : SerializableObject (),
      m_port             (0)
{
}

WaveMessagingBrokerClientInformation::WaveMessagingBrokerClientInformation (const string &name, const string &ipAddress, const SI32 &port)
    : SerializableObject (),
      m_name             (name),
      m_ipAddress        (ipAddress),
      m_port             (port)
{
}

WaveMessagingBrokerClientInformation::~WaveMessagingBrokerClientInformation ()
{
}

string WaveMessagingBrokerClientInformation::getName () const
{
    return (m_name);
}

void WaveMessagingBrokerClientInformation::setName (const string &name)
{
    m_name = name;
}

string WaveMessagingBrokerClientInformation::getIpAddress () const
{
    return (m_ipAddress);
}

void WaveMessagingBrokerClientInformation::setIpAddress (const string &ipAddress)
{
    m_ipAddress = ipAddress;
}

SI32 WaveMessagingBrokerClientInformation::getPort () const
{
    return (m_port);
}

void WaveMessagingBrokerClientInformation::setPort (const SI32 &port)
{
    m_port = port;
}

void WaveMessagingBrokerClientInformation::setupAttributesForSerialization ()
{
    SerializableObject::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeString (&m_name,      "name"));
    addSerializableAttribute (new AttributeString (&m_ipAddress, "ipAddress"));
    addSerializableAttribute (new AttributeSI32   (&m_port,      "port"));

}

}
