/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/


#include "Policy/NBAR2/Nbar2ProtocolPorts.h"
#include "Framework/Attributes/Attributes.h"

namespace WaveNs
{

Nbar2ProtocolPorts::Nbar2ProtocolPorts ()
    : Nbar2Element (),
      m_ip         (0)
{
    addTextAttribute ("ip",  new AttributeUI64   (&m_ip));
    addTextAttribute ("udp", new AttributeString (&m_udp));
    addTextAttribute ("tcp", new AttributeString (&m_tcp));
}

Nbar2ProtocolPorts::~Nbar2ProtocolPorts ()
{
}

UI64 Nbar2ProtocolPorts::getIp () const
{
    return (m_ip);
}

string Nbar2ProtocolPorts::getTcp () const
{
    return (m_tcp);
}

string Nbar2ProtocolPorts::getUdp () const
{
    return (m_udp);
}

}

