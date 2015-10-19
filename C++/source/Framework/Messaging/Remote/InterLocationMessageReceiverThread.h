/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef INTERLOCATIONMESSAGERECEIVERTHREAD_H
#define INTERLOCATIONMESSAGERECEIVERTHREAD_H

#include "Framework/MultiThreading/WavePosixThread.h"
#include "Framework/Types/Types.h"
#include "Framework/Utils/WaveMutex.h"
#include <string>

namespace WaveNs
{

class ServerStreamingSocket;

class InterLocationMessageReceiverThread : public WavePosixThread
{
    private :
        bool authorizeClient ();

    protected :
    public :
                                   InterLocationMessageReceiverThread (ServerStreamingSocket *pServerStreamingSocket);
        virtual                   ~InterLocationMessageReceiverThread ();
        virtual WaveThreadStatus   start                              ();
                void               setPeerServerDetails               (const string &peerServerIpAddress, const SI32 &peerServerPort, const string& messageVersion = "");
                string             getPeerServerMessageVersion        ()const;
                UI8                getPeerServerSerializationType     () const;
                void               closePeerServerStreamingSocket     (void);

    // Now the data members

    private :
        ServerStreamingSocket *m_pServerStreamingSocket;
        string                 m_peerServerIpAddress;
        SI32                   m_peerServerPort;
        WaveMutex             m_peerServerMutex;
        string                 m_peerServerMessageVersion;
        UI8                    m_peerServerSerializationType;

    protected :
    public :
};

}

#endif // INTERLOCATIONMESSAGERECEIVERTHREAD_H
