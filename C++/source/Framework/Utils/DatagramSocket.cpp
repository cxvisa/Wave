/***************************************************************************
 *   Copyright (C) 2005-2018 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/DatagramSocket.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "Security/Local/SecurityUtils.h"
#include "Framework/Utils/FixedSizeBuffer.h"

#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

namespace WaveNs
{

DatagramSocket::DatagramSocket ()
    : m_pSsl        (NULL),
      m_isAccepted  (false),
      m_isConnected (false)
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

    memset((char *) &m_fromSocketAddres, 0, sizeof(m_fromSocketAddres));
    m_fromSocketLength = sizeof (m_fromSocketAddres);
}

DatagramSocket::~DatagramSocket ()
{
    if (true == (isValid ()))
    {
        if (true == (isSecurityEnabled ()))
        {
            disableSecurity ();
        }

        waveCloseSocket (m_socket);
    }
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

void DatagramSocket::enableSecurity ()
{
    if (true == (isValid ()))
    {
        m_pSsl = SSL_new (SecurityUtils::getPDtlsSslContext ());

        if (NULL == m_pSsl)
        {
            SecurityUtils::traceSslErrors ();
            WaveNs::waveAssert (false, __FILE__, __LINE__);
        }

        if (0 >= (SSL_set_fd (m_pSsl, m_socket)))
        {
            SecurityUtils::traceSslErrors ();
            WaveNs::waveAssert (false, __FILE__, __LINE__);
        }
    }
}

void DatagramSocket::disableSecurity ()
{
    if (NULL != m_pSsl)
    {
        //SSL_set_fd   (m_pSsl, 0);
        SSL_shutdown (m_pSsl);
        SSL_free     (m_pSsl);

        m_pSsl = NULL;
    }
}

bool DatagramSocket::isSecurityEnabled ()
{
    return (NULL != m_pSsl);
}

SSL *DatagramSocket::getPSsl ()
{
    return (m_pSsl);
}

bool DatagramSocket::accept ()
{
    if (true == (isValid ()))
    {
        if (true == isSecurityEnabled ())
        {
            if (0 >= (SSL_accept (m_pSsl)))
            {
                SecurityUtils::traceSslErrors ();
                return (false);
            }
        }

        setIsAccepted (true);

        return (true);
    }
    else
    {
        return (false);
    }
}

bool DatagramSocket::connect ()
{
    if (true == (isValid ()))
    {
        if (true == isSecurityEnabled ())
        {
            if (0 >= (SSL_connect (m_pSsl)))
            {
                SecurityUtils::traceSslErrors ();
                return (false);
            }
        }

        setIsConnected (true);

        return (true);
    }
    else
    {
        return (false);
    }
}

bool DatagramSocket::send (sockaddr *pSockAddr, const string &data)
{
    if (! (isValid ()))
    {
        return false;
    }

    SI32 status = sendto (m_socket, data.c_str (), data.length (), 0, pSockAddr, sizeof (*pSockAddr));

    if (0 > status)
    {
        tracePrintf (TRACE_LEVEL_ERROR, "DatagramSocket::send : Sending string data failed : Errno : %d\n", errno);

        return (false);
    }
    else
    {
        return (true);
    }
}

bool DatagramSocket::receive (string &dataString, string &fromIpAddress, SI32 &fromPort)
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
        tracePrintf (TRACE_LEVEL_ERROR, "DatagramSocket::receive (string &dataString) : Status = %d, errno : %d", status, errno);

        delete[] pBuffer;
        return (false);
    }
    else if (0 == status)
    {
        tracePrintf (TRACE_LEVEL_WARN, "DatagramSocket::receive (string &dataString) : Status = %d, errno : %d", status, errno);

        fromIpAddress = inet_ntoa (m_fromSocketAddres.sin_addr);
        fromPort      = m_fromSocketAddres.sin_port;

        delete[] pBuffer;
        return (true);
    }
    else
    {
        //tracePrintf (TRACE_LEVEL_WARN, "DatagramSocket::receive (string &dataString) : Status = %d, errno : %d", status, errno);

        //pBuffer[status] = '\0';
        dataString.assign (pBuffer, status);

        fromIpAddress = inet_ntoa (m_fromSocketAddres.sin_addr);
        fromPort      = m_fromSocketAddres.sin_port;

        delete[] pBuffer;
        return (true);
    }
}

SI32 DatagramSocket::receive (UI8 *pBuffer, const UI32 maximumBufferLength, string &fromIpAddress, SI32 &fromPort)
{
    if (true != (isValid ()))
    {
        return (false);
    }

    m_fromSocketLength = sizeof (m_fromSocketAddres);

    SI32 status = ::recvfrom (m_socket, (char *) pBuffer, maximumBufferLength, 0, (sockaddr *) &m_fromSocketAddres, &m_fromSocketLength);

    if (-1 == status)
    {
        tracePrintf (TRACE_LEVEL_ERROR, "DatagramSocket::receive (UI8 *pBuffer, const UI32 maximumBufferLength) : Status = %d, errno : %d", status, errno);
    }
    else if (0 == status)
    {
        tracePrintf (TRACE_LEVEL_WARN, "DatagramSocket::receive (UI8 *pBuffer, const UI32 maximumBufferLength) : Status = %d, errno : %d", status, errno);
    }
    else
    {
        //tracePrintf (TRACE_LEVEL_WARN, "DatagramSocket::receive ((UI8 *pBuffer, const UI32 maximumBufferLength) : Status = %d, errno : %d", status, errno);
    }

    fromIpAddress = inet_ntoa (m_fromSocketAddres.sin_addr);
    fromPort      = m_fromSocketAddres.sin_port;

    return (status);
}

SI32 DatagramSocket::receive (FixedSizeBuffer * const pFixedSizeBuffer, string &fromIpAddress, SI32 &fromPort)
{
    if (NULL == pFixedSizeBuffer)
    {
        tracePrintf (TRACE_LEVEL_ERROR, "DatagramSocket::receive (UI8 *pBuffer, const UI32 maximumBufferLength) : NULL input buffer cannot be used for input.");

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
        tracePrintf (TRACE_LEVEL_ERROR, "DatagramSocket::receive (UI8 *pBuffer, const UI32 maximumBufferLength) : Status = %d, errno : %d", status, errno);
    }
    else if (0 == status)
    {
        tracePrintf (TRACE_LEVEL_WARN, "DatagramSocket::receive (UI8 *pBuffer, const UI32 maximumBufferLength) : Status = %d, errno : %d", status, errno);
    }
    else
    {
        //tracePrintf (TRACE_LEVEL_WARN, "DatagramSocket::receive ((UI8 *pBuffer, const UI32 maximumBufferLength) : Status = %d, errno : %d", status, errno);

        pFixedSizeBuffer->incrementCurrentSize (status);
    }

    fromIpAddress = inet_ntoa (m_fromSocketAddres.sin_addr);
    fromPort      = m_fromSocketAddres.sin_port;

    return (status);
}

SI32 DatagramSocket::receiveAll (UI8 *pBuffer, const UI32 maximumBufferLength, string &fromIpAddress, SI32 &fromPort)
{
    if (true != (isValid ()))
    {
        return (0);
    }

    m_fromSocketLength = sizeof (m_fromSocketAddres);

    SI32 status = ::recvfrom (m_socket, (char *) pBuffer, maximumBufferLength, 0, (sockaddr *) &m_fromSocketAddres, &m_fromSocketLength); //MSG_WAITALL);

    if (-1 == status)
    {
        tracePrintf (TRACE_LEVEL_ERROR, "DatagramSocket::receiveAll (UI8 *pBuffer, const UI32 maximumBufferLength) : Status = %d, errno : %d", status, errno);
    }
    else if (0 == status)
    {
        tracePrintf (TRACE_LEVEL_DEBUG, "DatagramSocket::receiveAll (UI8 *pBuffer, const UI32 maximumBufferLength) : Status = %d, errno : %d", status, errno);
    }
    else
    {
        //tracePrintf (TRACE_LEVEL_WARN, "DatagramSocket::receiveAll (UI8 *pBuffer, const UI32 maximumBufferLength) : Status = %d, errno : %d", status, errno);
    }

    fromIpAddress = inet_ntoa (m_fromSocketAddres.sin_addr);
    fromPort      = m_fromSocketAddres.sin_port;

    return (status);
}

bool DatagramSocket::receive (string &dataString)
{
    if (true != (isValid ()))
    {
        return (false);
    }

    char *pBuffer = new char[s_maximumDataLengthToReceive + 1];

    SI32 status = 0;

    if (true == isSecurityEnabled ())
    {
        status = SSL_read (getPSsl (), pBuffer, s_maximumDataLengthToReceive);
    }
    else
    {
        status = ::recv (m_socket, pBuffer, s_maximumDataLengthToReceive, 0);
    }

    dataString = "";

    if (-1 == status)
    {
        tracePrintf (TRACE_LEVEL_ERROR, "DatagramSocket::receive (string &dataString) : Status = %d, errno : %d", status, errno);

        delete[] pBuffer;
        return (false);
    }
    else if (0 == status)
    {
        tracePrintf (TRACE_LEVEL_DEBUG, "DatagramSocket::receive (string &dataString) : Status = %d, errno : %d", status, errno);

        delete[] pBuffer;
        return (true);
    }
    else
    {
        //pBuffer[status] = '\0';
        dataString.assign (pBuffer, status);

        delete[] pBuffer;
        return (true);
    }
}

SI32 DatagramSocket::receive (UI8 *pBuffer, const UI32 maximumBufferLength)
{
    if (true != (isValid ()))
    {
        return (false);
    }

    SI32 status = 0;

    if (true == isSecurityEnabled ())
    {
        status = SSL_read (getPSsl (), (char *) pBuffer, maximumBufferLength);
    }
    else
    {
        status = ::recv (m_socket, (char *) pBuffer, maximumBufferLength, 0);
    }

    if (-1 == status)
    {
        tracePrintf (TRACE_LEVEL_ERROR, "DatagramSocket::receive (UI8 *pBuffer, const UI32 maximumBufferLength) : Status = %d, errno : %d", status, errno);
    }
    else if (0 == status)
    {
        tracePrintf (TRACE_LEVEL_DEBUG, "DatagramSocket::receive (UI8 *pBuffer, const UI32 maximumBufferLength) : Status = %d, errno : %d", status, errno);
    }

    return (status);
}

SI32 DatagramSocket::send(UI8 *pBuffer, const UI32 maximumBufferLength)
{
    if (true != (isValid ()))
    {
        return (-1);
    }

    SI32  sendStatus = 0;
    UI32  sendLen      = 0;

    if (NULL != pBuffer)
    {
        while (sendLen < maximumBufferLength)
        {
            if (true == (isSecurityEnabled ()))
            {
                sendStatus = SSL_write (getPSsl (), (char *) (pBuffer +sendLen), (maximumBufferLength-sendLen));
            }
            else
            {
                sendStatus = ::send (m_socket, (char *) (pBuffer +sendLen), (maximumBufferLength-sendLen), 0); //MSG_NOSIGNAL
            }

            tracePrintf (TRACE_LEVEL_DEVEL, "DatagramSocket::send(UI8 *pBuffer, const UI32 maximumBufferLength)Sen(Status %d, Len %d, Total %d)",sendStatus, sendLen, maximumBufferLength);

            if (-1 == sendStatus)
            {
                return (sendStatus);
            }

            sendLen += sendStatus;

            if (sendLen < maximumBufferLength)
            {
                tracePrintf (TRACE_LEVEL_WARN, "DatagramSocket::send(UI8 *pBuffer, const UI32 maximumBufferLength) Fragmented Send");
            }
        }
    }

    return (sendLen);
}

bool DatagramSocket::send (const string &dataString)
{
    if (true != (isValid ()))
    {
        return (-1);
    }

    SI32 sendStatus = 0;

    sendStatus = send ((UI8*)(dataString.data ()), dataString.size ()); //MSG_NOSIGNAL

    if (-1 == sendStatus)
    {
        tracePrintf (TRACE_LEVEL_ERROR, "DatagramSocket::send (const string &dataString) : errno : %d", errno);
    }

    return (sendStatus != -1);
}

bool DatagramSocket::getIsAccepted () const
{
    return (m_isAccepted);
}

void DatagramSocket::setIsAccepted (const bool &isAccepted)
{
    m_isAccepted = isAccepted;
}

bool DatagramSocket::getIsConnected () const
{
    return (m_isConnected);
}

void DatagramSocket::setIsConnected (const bool &isConnected)
{
    m_isConnected = isConnected;
}

bool DatagramSocket::setNonBlocking ()
{
    if (! (isValid ()))
    {
        return (false);
    }

    int flags = fcntl (m_socket, F_GETFL, 0);

    if (flags < 0)
    {
        return (false);
    }

    flags = fcntl (m_socket, F_SETFL, flags | O_NONBLOCK);

    if (flags < 0)
    {
        return (false);
    }

    return (true);
}

bool DatagramSocket::clearNonBlocking ()
{
    if (! (isValid ()))
    {
        return (false);
    }

    int flags = fcntl (m_socket, F_GETFL, 0);

    if (flags < 0)
    {
        return (false);
    }

    flags = fcntl (m_socket, F_SETFL, flags & (~O_NONBLOCK));

    if (flags < 0)
    {
        return (false);
    }

    return (true);
}

ReadReadyStatus DatagramSocket::isDataAvailableToRead (const UI32 &milliSecondsToWaitFor)
{
    if (! (isValid ()))
    {
        return (READ_READY_INVALID_SOCKET);
    }

    struct timeval timeOut;
           fd_set  fdSet;

    timeOut.tv_sec = milliSecondsToWaitFor / 1000;
    timeOut.tv_usec = (milliSecondsToWaitFor % 1000) * 1000;

    while (true)
    {
        FD_ZERO (&fdSet);
        FD_SET  (m_socket, &fdSet);

        SI32 status = select (m_socket + 1, &fdSet, NULL, NULL, &timeOut);

        if (0 < status)
        {
            return (READ_READY_READY);
        }
        else if (0 == status)
        {
            return (READ_READY_TIMEOUT);
        }
        else
        {
            if (EINTR == errno)
            {
                continue;
            }
            else
            {
                return (READ_READY_FATAL_ERROR);
            }
        }
    }
}

bool DatagramSocket::connectUnderlyingSocket ()
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
