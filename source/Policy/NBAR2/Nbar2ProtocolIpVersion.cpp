/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *       
 *   All rights reserved.                                                  *       
 *   Author : Vidyasagara Reddy Guntaka                                    *       
 ***************************************************************************/

#include "Policy/NBAR2/Nbar2ProtocolIpVersion.h"
#include "Framework/Attributes/Attributes.h"

namespace WaveNs
{

Nbar2ProtocolIpVersion::Nbar2ProtocolIpVersion ()
    : Nbar2Element ()
{
    addTextAttribute ("ipv4", new AttributeBool (&m_ipv4));
    addTextAttribute ("ipv6", new AttributeBool (&m_ipv6));
}

Nbar2ProtocolIpVersion::~Nbar2ProtocolIpVersion ()
{
}

}

