/***************************************************************************
 *   Copyright (C) 2005-2018 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Security/Local/SecurityUtils.h"
#include "Framework/Utils/ServerDatagramSocket.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"

#include <sys/types.h>
#include <openssl/bio.h>

namespace WaveNs
{

ServerDatagramSocket::ServerDatagramSocket ()
    : DatagramSocket ()
{
    sockaddr_in localSocket;

    memset((char *) &localSocket, 0, sizeof(localSocket));
}

ServerDatagramSocket::ServerDatagramSocket (const SI32 &port)
    : DatagramSocket ()
{
    sockaddr_in localSocket;

    memset((char *) &localSocket, 0, sizeof(localSocket));

    localSocket.sin_family = AF_INET;
    localSocket.sin_port = htons(port);
    localSocket.sin_addr.s_addr = INADDR_ANY;

    SI32 status = bind (m_socket, (struct sockaddr *) &localSocket, sizeof( localSocket));

    if (0 != status)
    {
        tracePrintf (TRACE_LEVEL_ERROR, "ServerDatagramSocket::ServerDatagramSocket : Failed to bind to port : Errno : %d\n", errno);
        //cout << "*** errno = " << errno << " ***\n";

        waveAssert (false, __FILE__, __LINE__);
    }
}

ServerDatagramSocket::~ServerDatagramSocket ()
{
}

bool ServerDatagramSocket::connectUnderlyingSocket ()
{
    char *pBuffer = new char[100];

    SI32 status = recvfrom (m_socket, pBuffer, 100, MSG_PEEK, (sockaddr *) &m_fromSocketAddres, &m_fromSocketLength);

    delete[] pBuffer;

    if (0 > status)
    {
        //cout << "1 *** errno = " << errno << " ***\n";
        return (false);
    }

    if (0 < status)
    {
        status = ::connect (m_socket, (const sockaddr *) &m_fromSocketAddres, m_fromSocketLength);

        if (0 == status)
        {
            return (true);
        }
        else
        {
            //cout << "3 *** errno = " << errno << " ***\n";
            return (false);
        }
    }
    else
    {
        //cout << "4 *** errno = " << errno << " ***\n";

        return (false);
    }

    return (true);
}

}

