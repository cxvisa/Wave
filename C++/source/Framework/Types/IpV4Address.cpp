/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Types/IpV4Address.h"
#include "Framework/Utils/TraceUtils.h"
#include <sys/socket.h>

namespace WaveNs
{

IpV4Address::IpV4Address ()
    : IpAddress ("127.0.0.1")
{
}

IpV4Address::IpV4Address (const string &ipV4Address)
    : IpAddress (ipV4Address)
{
}

IpV4Address::IpV4Address (const IpV4Address &ipV4Address)
    : IpAddress (ipV4Address)
{
}

IpV4Address::~IpV4Address ()
{
}

UI32 IpV4Address::getAddressFamily ()
{
    return (AF_INET);
}

ResourceId IpV4Address::loadFromPlainString (const string &valueString)
{
    ResourceId status = WAVE_MESSAGE_ERROR;
    unsigned char buf[sizeof(struct in6_addr)];

    if (inet_pton(AF_INET, valueString.c_str(), &buf) == 1)
    {
        IpAddress::loadFromPlainString (valueString);
        status = WAVE_MESSAGE_SUCCESS;
    }

    if( WAVE_MESSAGE_ERROR == status)
    {
        trace (TRACE_LEVEL_ERROR, string("IpV4Address::loadFromPlainString : Improper format of IpV4Address in input string"));
    }

    return status;
}

}
