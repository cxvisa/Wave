/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/DatagramSocket.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"

#include <errno.h>

namespace WaveNs
{

DatagramSocket::DatagramSocket ()
{
    m_socket = ::socket (PF_INET, SOCK_DGRAM, 0);

    if (true != isValid ())
    {
        tracePrintf (TRACE_LEVEL_FATAL, "DatagramSocket::DatagramSocket : %d\n", errno);
        waveAssert (false, __FILE__, __LINE__);
    }

    SI32 temp = 1;

    if (-1 == (setsockopt (m_socket, SOL_SOCKET, SO_REUSEADDR, (const char *) &temp, sizeof (temp))))
    {
        tracePrintf (TRACE_LEVEL_FATAL, "DatagramSocket::DatagramSocket : %d\n", errno);
        waveAssert (false, __FILE__, __LINE__);
    }
}

DatagramSocket::~DatagramSocket ()
{
}

bool DatagramSocket::isValid ()
{
    if (-1 != m_socket)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

}
