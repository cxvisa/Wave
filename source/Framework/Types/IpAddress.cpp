/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Types/IpAddress.h"
#include "Framework/Utils/TraceUtils.h"
#include <arpa/inet.h>

namespace WaveNs
{

IpAddress::IpAddress ()
    : m_ipAddress ("127.0.0.1")
{
}

IpAddress::IpAddress (const string &ipAddress)
    : m_ipAddress (ipAddress)
{
}

IpAddress::IpAddress (const IpAddress &ipAddress)
    : m_ipAddress (ipAddress.m_ipAddress)
{
}

IpAddress::~IpAddress ()
{
}

string IpAddress::toString () const
{
    return (m_ipAddress);
}

void IpAddress::fromString (const string &ipAddress)
{
    m_ipAddress = ipAddress;
}

ResourceId IpAddress::loadFromPlainString (const string &ipAddress)
{
    ResourceId status = WAVE_MESSAGE_ERROR;

    unsigned char buf[sizeof(struct in6_addr)];

    if (inet_pton(AF_INET, ipAddress.c_str(), &buf) == 1)
    {
        m_ipAddress = ipAddress;
        status = WAVE_MESSAGE_SUCCESS;
    }
    else if (inet_pton(AF_INET6, ipAddress.c_str(), &buf) == 1)
    {
        m_ipAddress = ipAddress;
        status = WAVE_MESSAGE_SUCCESS;
    }

    return status;
}

bool IpAddress::operator == (const IpAddress &ipAddress) const
{
    string tempIpAddress = ipAddress.toString ();

    if (m_ipAddress == tempIpAddress)
    {
        return (true);
    }

    return (false);
}

bool IpAddress::operator != (const IpAddress &ipAddress) const
{
    return (! (operator == (ipAddress)));
}

IpAddress &IpAddress::operator = (const IpAddress &ipAddress)
{
    m_ipAddress = ipAddress.m_ipAddress;

    return (*this);
}

}
