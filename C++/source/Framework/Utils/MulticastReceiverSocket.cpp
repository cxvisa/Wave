/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/MulticastReceiverSocket.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/FixedSizeBuffer.h"

#include <errno.h>

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

bool MulticastReceiverSocket::receive (string &dataString, string &fromIpAddress, SI32 &fromPort)
{
    if (true != (isValid ()))
    {
        return (false);
    }

    char *pBuffer = new char[s_maximumDataLengthToReceive + 1];

    m_fromSocketLength = sizeof (m_fromSocketAddres);

    SI32  status  = ::recvfrom (m_socket, pBuffer, s_maximumDataLengthToReceive, 0, (sockaddr *) &m_fromSocketAddres, &m_fromSocketLength);

    dataString = "";

    if (-1 == status)
    {
        tracePrintf (TRACE_LEVEL_ERROR, "MulticastReceiverSocket::receive (string &dataString) : Status = %d, errno : %d", status, errno);

        delete[] pBuffer;
        return (false);
    }
    else if (0 == status)
    {
        tracePrintf (TRACE_LEVEL_WARN, "MulticastReceiverSocket::receive (string &dataString) : Status = %d, errno : %d", status, errno);

        fromIpAddress = inet_ntoa (m_fromSocketAddres.sin_addr);
        fromPort      = m_fromSocketAddres.sin_port;

        delete[] pBuffer;
        return (true);
    }
    else
    {
        //tracePrintf (TRACE_LEVEL_WARN, "MulticastReceiverSocket::receive (string &dataString) : Status = %d, errno : %d", status, errno);

        //pBuffer[status] = '\0';
        dataString.assign (pBuffer, status);

        fromIpAddress = inet_ntoa (m_fromSocketAddres.sin_addr);
        fromPort      = m_fromSocketAddres.sin_port;

        delete[] pBuffer;
        return (true);
    }
}

SI32 MulticastReceiverSocket::receive (UI8 *pBuffer, const UI32 maximumBufferLength, string &fromIpAddress, SI32 &fromPort)
{
    if (true != (isValid ()))
    {
        return (false);
    }

    m_fromSocketLength = sizeof (m_fromSocketAddres);

    SI32 status = ::recvfrom (m_socket, (char *) pBuffer, maximumBufferLength, 0, (sockaddr *) &m_fromSocketAddres, &m_fromSocketLength);

    if (-1 == status)
    {
        tracePrintf (TRACE_LEVEL_ERROR, "MulticastReceiverSocket::receive (UI8 *pBuffer, const UI32 maximumBufferLength) : Status = %d, errno : %d", status, errno);
    }
    else if (0 == status)
    {
        tracePrintf (TRACE_LEVEL_WARN, "MulticastReceiverSocket::receive (UI8 *pBuffer, const UI32 maximumBufferLength) : Status = %d, errno : %d", status, errno);
    }
    else
    {
        //tracePrintf (TRACE_LEVEL_WARN, "MulticastReceiverSocket::receive ((UI8 *pBuffer, const UI32 maximumBufferLength) : Status = %d, errno : %d", status, errno);
    }

    fromIpAddress = inet_ntoa (m_fromSocketAddres.sin_addr);
    fromPort      = m_fromSocketAddres.sin_port;

    return (status);
}

SI32 MulticastReceiverSocket::receive (FixedSizeBuffer * const pFixedSizeBuffer, string &fromIpAddress, SI32 &fromPort)
{
    if (NULL == pFixedSizeBuffer)
    {
        tracePrintf (TRACE_LEVEL_ERROR, "MulticastReceiverSocket::receive (UI8 *pBuffer, const UI32 maximumBufferLength) : NULL input buffer cannot be used for input.");

        return (-1);
    }

    if (true != (isValid ()))
    {
        return (false);
    }

    UI8 *pBuffer = pFixedSizeBuffer->getPCurrentRawBuffer ();

    m_fromSocketLength = sizeof (m_fromSocketAddres);

    SI32 status = ::recvfrom (m_socket, (char *) pBuffer, pFixedSizeBuffer->getMaximumSize (), 0, (sockaddr *) &m_fromSocketAddres, &m_fromSocketLength);

    if (-1 == status)
    {
        tracePrintf (TRACE_LEVEL_ERROR, "MulticastReceiverSocket::receive (UI8 *pBuffer, const UI32 maximumBufferLength) : Status = %d, errno : %d", status, errno);
    }
    else if (0 == status)
    {
        tracePrintf (TRACE_LEVEL_WARN, "MulticastReceiverSocket::receive (UI8 *pBuffer, const UI32 maximumBufferLength) : Status = %d, errno : %d", status, errno);
    }
    else
    {
        //tracePrintf (TRACE_LEVEL_WARN, "MulticastReceiverSocket::receive ((UI8 *pBuffer, const UI32 maximumBufferLength) : Status = %d, errno : %d", status, errno);

        pFixedSizeBuffer->incrementCurrentSize (status);
    }

    fromIpAddress = inet_ntoa (m_fromSocketAddres.sin_addr);
    fromPort      = m_fromSocketAddres.sin_port;

    return (status);
}

SI32 MulticastReceiverSocket::receiveAll (UI8 *pBuffer, const UI32 maximumBufferLength, string &fromIpAddress, SI32 &fromPort)
{
    if (true != (isValid ()))
    {
        return (0);
    }

    m_fromSocketLength = sizeof (m_fromSocketAddres);

    SI32 status = ::recvfrom (m_socket, (char *) pBuffer, maximumBufferLength, 0, (sockaddr *) &m_fromSocketAddres, &m_fromSocketLength); //MSG_WAITALL);

    if (-1 == status)
    {
        tracePrintf (TRACE_LEVEL_ERROR, "MulticastReceiverSocket::receiveAll (UI8 *pBuffer, const UI32 maximumBufferLength) : Status = %d, errno : %d", status, errno);
    }
    else if (0 == status)
    {
        tracePrintf (TRACE_LEVEL_DEBUG, "MulticastReceiverSocket::receiveAll (UI8 *pBuffer, const UI32 maximumBufferLength) : Status = %d, errno : %d", status, errno);
    }
    else
    {
        //tracePrintf (TRACE_LEVEL_WARN, "MulticastReceiverSocket::receiveAll (UI8 *pBuffer, const UI32 maximumBufferLength) : Status = %d, errno : %d", status, errno);
    }

    fromIpAddress = inet_ntoa (m_fromSocketAddres.sin_addr);
    fromPort      = m_fromSocketAddres.sin_port;

    return (status);
}

}
