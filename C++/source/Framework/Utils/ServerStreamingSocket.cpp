/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/ServerStreamingSocket.h"
#include "errno.h"
#include "Framework/Utils/AssertUtils.h"

namespace WaveNs
{

const   UI32    ServerStreamingSocket::m_customDefaultKeepAliveIdleTimeoutInMilliSeconds    = 30000;
const   UI32    ServerStreamingSocket::m_customDefaultKeepAliveProbeIntervalInMilliSeconds  = 20000;
const   UI32    ServerStreamingSocket::m_customDefaultKeepAliveProbeCount                   = 3;

ServerStreamingSocket::ServerStreamingSocket (SI32 port, SI32 maximumNumberOfConnections)
    : StreamingSocket (maximumNumberOfConnections),
      m_status (SERVER_STREAMING_SOCKET_SUCCESS)
{
    if (true != (StreamingSocket::bind (port)))
    {
//        cout << "*** errno = " << errno << " ***\n";
        m_status = SERVER_STREAMING_SOCKET_ERROR_COULD_NOT_BIND;
//        waveAssert (false, __FILE__,__LINE__);
    }

    if (true != (StreamingSocket::listen ()))
    {
//        cout << "*** errno = " << errno << " ***\n";
        m_status = SERVER_STREAMING_SOCKET_ERROR_COULD_NOT_LISTEN;
//        waveAssert (false, __FILE__,__LINE__);
    }
}

ServerStreamingSocket::ServerStreamingSocket ()
    : StreamingSocket (),
      m_status (SERVER_STREAMING_SOCKET_SUCCESS)
{
}

ServerStreamingSocket::~ServerStreamingSocket ()
{
}

const ServerStreamingSocket &ServerStreamingSocket::operator << (const string &dataString)
{
    if (-1 == (StreamingSocketBase::send (dataString)))
    {
//        cout << "*** errno = " << errno << " ***\n";
        //waveAssert (false, __FILE__,__LINE__);
    }

    return (*this);
}

SI32 ServerStreamingSocket::send(UI8 *pBuffer, const UI32 maximumBufferLength)
{
    return (StreamingSocketBase::send (pBuffer, maximumBufferLength));
}

bool ServerStreamingSocket::operator << (const FixedSizeBuffer &fixedSizeBuffer)
{
    if (-1 == (StreamingSocketBase::send (fixedSizeBuffer)))
    {
        //cout << "*** errno = " << errno << " ***\n";
        return (false);
    }
    else
    {
        return (true);
    }
}

bool ServerStreamingSocket::operator << (SerializableObject *pSerializableObject)
{
    if (-1 == (StreamingSocketBase::send (pSerializableObject)))
    {
        //cout << "*** errno = " << errno << " ***\n";
        return (false);
    }
    else
    {
        return (true);
    }
}


bool ServerStreamingSocket::operator >> (string &dataString)
{
    if (true != (receive (dataString)))
    {
//        cout << "*** errno = " << errno << " ***\n";
        return (false);
    }

    return (true);
}

bool ServerStreamingSocket::operator >> (FixedSizeBuffer &fixedSizeBuffer)
{
    UI32 numberOfBytesRemainingToRead = fixedSizeBuffer.getMaximumSize ();

    while (numberOfBytesRemainingToRead > 0)
    {
        SI32 numberOfBytesRead = receiveAll (fixedSizeBuffer.getPCurrentRawBuffer (), fixedSizeBuffer.getRemainingSize ());

        if (numberOfBytesRead > 0)
        {
            fixedSizeBuffer.incrementCurrentSize (numberOfBytesRead);
            numberOfBytesRemainingToRead -= numberOfBytesRead;
        }
        else
        {
            return (false);
        }
    }

    return (true);
}

bool ServerStreamingSocket::operator >> (UI32 &value)
{
    return (receiveUI32 (value));
}

bool ServerStreamingSocket::accept (ServerStreamingSocket &newSocket, const bool &enableSecurity)
{
    bool successfullyAcceptedNewConnection = StreamingSocket::accept (newSocket, enableSecurity);

    if (true != successfullyAcceptedNewConnection)
    {
//        cout << "*** errno = " << errno << " ***\n";
    }

    return (successfullyAcceptedNewConnection);
}
string ServerStreamingSocket::getSourceIpAddress ()
{
    return (StreamingSocket::getSourceIpAddress ());
}

string ServerStreamingSocket::getPeerIpAddress ()
{
    return (StreamingSocket::getPeerIpAddress ());
}

const ServerStreamingSocketStatus ServerStreamingSocket::getStatus ()
{
    return (m_status);
}

SI32 ServerStreamingSocket::getPeerPort ()
{
    return (StreamingSocket::getPeerPort ());
}

void ServerStreamingSocket::close (void)
{
    StreamingSocket::close ();
}

bool ServerStreamingSocket::setCustomKeepAliveTimeouts (UI32 keepAliveIdleTimeoutInMilliSeconds, UI32 keepAliveProbeIntervalInMilliSeconds, UI32 keepAliveProbeCount)
{
    bool setSocketOptionStatus = false;

    setSocketOptionStatus = setTcpKeepAliveIdleTimeout (keepAliveIdleTimeoutInMilliSeconds);

    // if (false == setSocketOptionStatus)
    // {
    //     waveAssert (false, __FILE__, __LINE__);
    // }

    if (true == setSocketOptionStatus)
    {
        setSocketOptionStatus = setTcpKeepAliveProbeInterval (keepAliveProbeIntervalInMilliSeconds);

        // if (false == setSocketOptionStatus)
        // {
        //     waveAssert (false, __FILE__, __LINE__);
        // }
    }

    if (true == setSocketOptionStatus)
    {
        setSocketOptionStatus = setTcpKeepAliveProbeCount (keepAliveProbeCount);

        // if (false == setSocketOptionStatus)
        // {
        //     waveAssert (false, __FILE__, __LINE__);
        // }
    }

    return setSocketOptionStatus;
}

bool ServerStreamingSocket::setCustomKeepAliveTimeouts ()
{
    return (setCustomKeepAliveTimeouts (m_customDefaultKeepAliveIdleTimeoutInMilliSeconds, m_customDefaultKeepAliveProbeIntervalInMilliSeconds, m_customDefaultKeepAliveProbeCount));
}

}

