/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/MulticastReceiverSocket.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"

namespace WaveNs
{

MulticastReceiverSocket::MulticastReceiverSocket (const string &groupIpAddress, const SI32 &port)
    : MulticastSocket ()
{
    sockaddr_in localSocket;

    memset((char *) &localSocket, 0, sizeof(localSocket));

    localSocket.sin_family = AF_INET;
    localSocket.sin_port = htons(port);
    localSocket.sin_addr.s_addr = INADDR_ANY;

    SI32 status = bind (m_socket, (struct sockaddr *) &localSocket, sizeof( localSocket));

    if (0 != status)
    {
        tracePrintf (TRACE_LEVEL_ERROR, "MulticastReceiverSocket::MulticastReceiverSocket : Failed to bind to port : Errno : %d\n", errno);
        //cout << "*** errno = " << errno << " ***\n";

        waveAssert (false, __FILE__, __LINE__);
    }

    bool isSuccessful = addGroupMembership (groupIpAddress);

    if (false == isSuccessful)
    {
        tracePrintf (TRACE_LEVEL_ERROR, "MulticastReceiverSocket::MulticastReceiverSocket : Failed to add group membership : Errno : %d\n", errno);
        //cout << "*** errno = " << errno << " ***\n";

        waveAssert (false, __FILE__, __LINE__);
    }
}

MulticastReceiverSocket::~MulticastReceiverSocket ()
{
}

bool MulticastReceiverSocket::addGroupMembership (const string &groupIpAddress)
{
    ip_mreq groupMulticastRequest;

    memset ((char *) &groupMulticastRequest, 0, sizeof(groupMulticastRequest));

    groupMulticastRequest.imr_multiaddr.s_addr = inet_addr(groupIpAddress.c_str ());
    groupMulticastRequest.imr_interface.s_addr = INADDR_ANY;;

    if (-1 == (setsockopt (m_socket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *) &groupMulticastRequest, sizeof (groupMulticastRequest))))
    {
        return (false);
    }
    else
    {
        return (true);
    }
}

}
