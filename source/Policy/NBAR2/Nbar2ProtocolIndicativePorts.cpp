/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Policy/NBAR2/Nbar2ProtocolIndicativePorts.h"
#include "Framework/Attributes/Attributes.h"

namespace WaveNs
{

Nbar2ProtocolIndicativePorts::Nbar2ProtocolIndicativePorts ()
    : m_ip (0)
{
    addTextAttribute ("ip",  new AttributeUI64   (&m_ip));
    addTextAttribute ("udp", new AttributeString (&m_udp));
    addTextAttribute ("tcp", new AttributeString (&m_tcp));
}

Nbar2ProtocolIndicativePorts::~Nbar2ProtocolIndicativePorts ()
{
}

UI64 Nbar2ProtocolIndicativePorts::getIp () const
{
    return (m_ip);
}

string Nbar2ProtocolIndicativePorts::getTcp () const
{
    return (m_tcp);
}

string Nbar2ProtocolIndicativePorts::getUdp () const
{
    return (m_udp);
}

}

