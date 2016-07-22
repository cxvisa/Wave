/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anand Kumar Subramanian                                            *
 ***************************************************************************/

#include "Framework/Types/IpVxAddress.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include <sys/socket.h>

namespace WaveNs
{

IpVxAddress::IpVxAddress ()
    : IpAddress ()
{
    //Use the default type as IPV4, as the base class will set ip as "127.0.0.1"
    setIpType (WAVE_IP_V4);
}

IpVxAddress::IpVxAddress (const string &ipVxAddress)
    : IpAddress (ipVxAddress),
      m_addressType (WAVE_IP_INVALID)
{
    if ("" != ipVxAddress)
    {
        setIpType (determineIpType (ipVxAddress));
    }
}

IpVxAddress::IpVxAddress (const IpVxAddress &ipVxAddress)
    : IpAddress (),
      m_addressType (WAVE_IP_INVALID)
{
    IpAddress::operator = (ipVxAddress);
    string ipString = ipVxAddress.toString ();

    if ("" != ipString)
    {
        setIpType (determineIpType (ipString));
    }
}

IpVxAddress::~IpVxAddress ()
{
}

UI32 IpVxAddress::getAddressFamily ()
{
    if (WAVE_IP_V4 == m_addressType)
    {
        return (AF_INET);
    }
    else
    {
        return (AF_INET6);
    }
}

bool IpVxAddress::operator == (const IpVxAddress &ipVxAddress) const
{
    return ((m_addressType == ipVxAddress.m_addressType) && (this->toString () == ipVxAddress.toString ()));
}

bool IpVxAddress::operator != (const IpVxAddress &ipVxAddress) const
{
    return (!(operator == (ipVxAddress)));
}

IpVxAddress &IpVxAddress::operator = (const IpVxAddress &ipVxAddress)
{
    IpAddress::operator = (ipVxAddress);
    string ipString = ipVxAddress.toString ();

    if ("" != ipString)
    {
        setIpType (determineIpType (ipString));
    }

    return (*this);
}

bool IpVxAddress::isValidIpV4Address (const string &ipVxAddress)
{
    UI8 buffer[sizeof (struct in6_addr)];

    SI32 status = inet_pton (AF_INET, ipVxAddress.c_str(), buffer);

    if (1 == status)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

bool IpVxAddress::isValidIpV6Address (const string &ipVxAddress)
{
    UI8 buffer[sizeof (struct in6_addr)];

    SI32 status = inet_pton (AF_INET6, ipVxAddress.c_str(), buffer);

    if (1 == status)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

void IpVxAddress::setIpType (const WaveIpType ipType)
{
    if (WAVE_IP_INVALID == ipType)
    {
        trace (TRACE_LEVEL_DEBUG, string ("IpVxAddress::setIpType Invalid IpType, If IpAddress string is empty this is possible"));
//        waveAssert (false, __FILE__, __LINE__);
    }

    m_addressType = ipType;

}

WaveIpType IpVxAddress::getIpType () const
{
    return (m_addressType);
}

WaveIpType IpVxAddress::determineIpType (const string &ipVxAddress)
{
    if ("" != ipVxAddress)
    {
        if (isValidIpV4Address (ipVxAddress))
        {
            return (WAVE_IP_V4);
        }
        else if (isValidIpV6Address (ipVxAddress))
        {
            return (WAVE_IP_V6);
        }
        else
        {
            trace (TRACE_LEVEL_FATAL, string ("IpVxAddress::IpVxAddress: Invalid IpVxAddress : ") + ipVxAddress);
            waveAssert (false, __FILE__, __LINE__);
        }
    }

    return (WAVE_IP_INVALID);

}

void IpVxAddress::fromString (const string &ipVxAddress)
{
    IpAddress :: fromString (ipVxAddress);
    setIpType  (determineIpType (ipVxAddress));
}

ResourceId IpVxAddress::loadFromPlainString (const string &ipVxAddress)
{
    ResourceId status = WAVE_MESSAGE_ERROR;
    status = IpAddress::loadFromPlainString (ipVxAddress);

    if ( WAVE_MESSAGE_SUCCESS == status )
    {
        if (isValidIpV4Address (ipVxAddress))
        {
            setIpType (WAVE_IP_V4);
        }
        else if (isValidIpV6Address (ipVxAddress))
        {
            setIpType (WAVE_IP_V6);
        }
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, string("IpVxAddress::loadFromPlainString : Improper format of IpVxAddress in input string"));
        setIpType (WAVE_IP_INVALID);
    }

    return status;
}

}

