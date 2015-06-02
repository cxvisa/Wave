/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SERVERSTREAMINGSOCKET_H
#define SERVERSTREAMINGSOCKET_H

#include "Framework/Utils/StreamingSocket.h"
#include "Framework/Utils/FixedSizeBuffer.h"

namespace WaveNs
{

typedef enum
{
    SERVER_STREAMING_SOCKET_SUCCESS = 0,
    SERVER_STREAMING_SOCKET_ERROR_COULD_NOT_BIND,
    SERVER_STREAMING_SOCKET_ERROR_COULD_NOT_LISTEN
} ServerStreamingSocketStatus;

class ServerStreamingSocket : protected StreamingSocket
{
    private :
    protected :
    public :
                                                   ServerStreamingSocket (SI32 port, SI32 maximumNumberOfConnections);
                                                   ServerStreamingSocket ();
        virtual                                   ~ServerStreamingSocket ();
                const ServerStreamingSocket       &operator <<           (const string &dataString);
                      bool                         operator <<           (SerializableObject *pSerializableObject);
                      bool                         operator >>           (string &dataString);
                      bool                         operator >>           (FixedSizeBuffer &fizedSizeBuffer);
                      bool                         operator >>           (UI32 &value);
                      bool                         accept                (ServerStreamingSocket &newSocket);
        virtual       string                       getSourceIpAddress    ();
        virtual       string                       getPeerIpAddress      ();
        virtual       SI32                         getPeerPort           ();
                const ServerStreamingSocketStatus  getStatus             ();

                      // Keep Alive settings -
                      bool                         setCustomKeepAliveTimeouts (UI32 keepAliveIdleTimeoutInMilliSeconds, UI32 keepAliveProbeIntervalInMilliSeconds, UI32 keepAliveProbeCount);
                      // sets custom timeouts to WaveNs::ServerStreamingSocket::* values.
                      bool                         setCustomKeepAliveTimeouts ();

                      void                         close                 (void);

    // Now the data members

    private :
        ServerStreamingSocketStatus m_status;
        static const  UI32          m_customDefaultKeepAliveIdleTimeoutInMilliSeconds;
        static const  UI32          m_customDefaultKeepAliveProbeIntervalInMilliSeconds;
        static const  UI32          m_customDefaultKeepAliveProbeCount;
    protected :
    public :
};

}

#endif // SERVERSTREAMINGSOCKET_H
