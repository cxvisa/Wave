/***************************************************************************
 *   Copyright (C) 2011 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                    *
 ***************************************************************************/

#ifndef HAPEERMESSAGERECEIVERTHREAD_H
#define HAPEERMESSAGERECEIVERTHREAD_H

#include "Framework/MultiThreading/WavePosixThread.h"
#include "Framework/Types/Types.h"
#include "Framework/Utils/WaveMutex.h"
#include <string>

namespace WaveNs
{

class ServerStreamingSocket;

class HaPeerMessageReceiverThread : public WavePosixThread
{
    private :
        bool authorizeClient ();

    protected :
    public :
                                   HaPeerMessageReceiverThread (ServerStreamingSocket *pServerStreamingSocket);
        virtual                   ~HaPeerMessageReceiverThread ();
        virtual WaveThreadStatus   start                              ();
                void               setPeerServerDetails               (const string &peerServerIpAddress, const SI32 &peerServerPort, const string& peerServerMessageVersion = "");
                void               closePeerServerStreamingSocket     (void);
                string             getPeerServerMessageVersion        () const;
                UI8                getPeerServerSerializationType     () const;

    // Now the data members

    private :
        ServerStreamingSocket *m_pServerStreamingSocket;
        string                 m_peerServerIpAddress;
        SI32                   m_peerServerPort;
        string                 m_peerServerMessageVersion;
        UI8                    m_peerServerSerializationType;
        WaveMutex             m_peerServerMutex;

    protected :
    public :
};

}

#endif // HAPEERMESSAGERECEIVERTHREAD_H
