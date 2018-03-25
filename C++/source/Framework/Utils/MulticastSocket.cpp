/***************************************************************************
 *   Copyright (C) 2005-2018 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/MulticastSocket.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"

#include <errno.h>

namespace WaveNs
{

MulticastSocket::MulticastSocket ()
    : DatagramSocket()
{
    bool succeeded = setMulticastLoopback ();

    if (true != succeeded)
    {
        tracePrintf (TRACE_LEVEL_ERROR, "MulticastSocket::MulticastSocket : Setting Multicast Loop did not work.  Errno : %d\n", errno);
        //cout << "*** errno = " << errno << " ***\n";

        waveAssert (false, __FILE__, __LINE__);
    }

    m_localInterface.s_addr = INADDR_ANY;

    SI32 status = setsockopt(m_socket, IPPROTO_IP, IP_MULTICAST_IF, &m_localInterface, sizeof (m_localInterface));

    if (0 > status)
    {
        tracePrintf (TRACE_LEVEL_ERROR, "MulticastSocket::MulticastSocket : Setting multicast interface failed : Errno : %d\n", errno);
        //cout << "*** errno = " << errno << " ***\n";

        waveAssert (false, __FILE__, __LINE__);
    }
}

MulticastSocket::~MulticastSocket ()
{
}

bool MulticastSocket::setMulticastLoopback ()
{
    SI32 flag = 1;

    if (-1 == (setsockopt (m_socket, IPPROTO_IP, IP_MULTICAST_LOOP, (char *) &flag, sizeof (flag))))
    {
        return (false);
    }
    else
    {
        return (true);
    }
}

bool MulticastSocket::clearMulticastLoopback ()
{
    SI32 flag = 0;

    if (-1 == (setsockopt (m_socket, IPPROTO_IP, IP_MULTICAST_LOOP, (char *) &flag, sizeof (flag))))
    {
        return (false);
    }
    else
    {
        return (true);
    }
}

}
