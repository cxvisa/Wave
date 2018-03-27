/**************************************************************************
 *   Copyright (C) 2005-2018 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Security/Local/SecurityUtils.h"
#include "Framework/Utils/ClientDatagramSocket.h"
#include "Framework/Utils/TraceUtils.h"

namespace WaveNs
{

ClientDatagramSocket::ClientDatagramSocket (const string &ipAddress, const SI32 &port)
    : DatagramSocket ()
{
    m_fromSocketLength = sizeof (m_fromSocketAddres);

    memset ((char *) &m_fromSocketAddres, 0, m_fromSocketLength);

    m_fromSocketAddres.sin_family = AF_INET;
    m_fromSocketAddres.sin_port = htons(port);

    SI32 status = inet_pton (AF_INET, ipAddress.c_str (), &(m_fromSocketAddres.sin_addr));

    if (0 >= status)
    {
        tracePrintf (TRACE_LEVEL_ERROR, "ClientDatagramSocket::ClientDatagramSocket : Errno : %d\n", errno);
        //cout << "*** errno = " << errno << " ***\n";

        waveAssert (false, __FILE__, __LINE__);
    }
}

ClientDatagramSocket::~ClientDatagramSocket ()
{
}

void ClientDatagramSocket::enableSecurity ()
{
    if (true == (isValid ()))
    {
        m_pSsl = SSL_new (SecurityUtils::getPDtlsClientSslContext ());

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

bool ClientDatagramSocket::connect ()
{
    SI32 status = ::connect (m_socket, (const sockaddr *) &m_fromSocketAddres, m_fromSocketLength);

    if (0 == status)
    {
        if (false == (DatagramSocket::connect ()))
        {
            return (false);
        }
    }
    else
    {
        //cout << "*** errno = " << errno << " ***\r\n";
        return (false);
    }

    return (true);
}

}
