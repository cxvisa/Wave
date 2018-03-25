/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/DatagramSocket.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "Security/Local/SecurityUtils.h"

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
        SSL_free (m_pSsl);
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

}
