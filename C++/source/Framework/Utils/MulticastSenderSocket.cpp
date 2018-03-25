/***************************************************************************
 *   Copyright (C) 2005-2018 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/MulticastSenderSocket.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"

#include <errno.h>

namespace WaveNs
{

MulticastSenderSocket::MulticastSenderSocket (const string &groupIpAddress, const SI32 &port)
:   MulticastSocket ()
{
    memset ((char *) &m_groupSocketAddress, 0, sizeof(m_groupSocketAddress));

    m_groupSocketAddress.sin_family = AF_INET;
    m_groupSocketAddress.sin_port = htons(port);

    SI32 status = inet_pton (AF_INET, groupIpAddress.c_str (), &(m_groupSocketAddress.sin_addr));

    if (0 >= status)
    {
        tracePrintf (TRACE_LEVEL_ERROR, "MulticastSenderSocket::MulticastSenderSocket : Errno : %d\n", errno);
        //cout << "*** errno = " << errno << " ***\n";

        waveAssert (false, __FILE__, __LINE__);
    }
}

MulticastSenderSocket::~MulticastSenderSocket ()
{
}

bool MulticastSenderSocket::send (const string &data)
{
    return (MulticastSocket::send ((sockaddr *) &m_groupSocketAddress, data));
}

}
