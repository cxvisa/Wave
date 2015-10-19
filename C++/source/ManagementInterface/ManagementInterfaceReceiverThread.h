/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef MANAGEMENTINTERFACERECEIVERTHREAD_H
#define MANAGEMENTINTERFACERECEIVERTHREAD_H

#include "Framework/MultiThreading/WavePosixThread.h"
#include "Framework/Types/Types.h"
#include "Framework/Utils/WaveMutex.h"
#include <string>

namespace WaveNs
{

class ServerStreamingSocket;

class ManagementInterfaceReceiverThread : public WavePosixThread
{
    private :
        bool authorizeClient ();

    protected :
    public :
                                   ManagementInterfaceReceiverThread (ServerStreamingSocket *pServerStreamingSocket);
        virtual                   ~ManagementInterfaceReceiverThread ();

        virtual WaveThreadStatus   start                             ();
                void               setPeerServerDetails              (const string &peerServerIpAddress, const SI32 &peerServerPort, const string& messageVersion = "");
                void               closePeerServerStreamingSocket    (void);

                void               setPeerClientId                   (const UI32 &peerClientId);
                void               setPeerClientName                 (const string &peerClientName);
                string             getPeerClientName                 () const;
                string             getPeerServerMessageVersion       () const;
                UI8                getPeerServerSerializationType    () const;

    // Now the data members

    private :
        ServerStreamingSocket *m_pServerStreamingSocket;
        string                 m_peerServerIpAddress;
        SI32                   m_peerServerPort;
        string                 m_peerServerMessageVersion;
        UI8                    m_peerServerSerializationType;
        WaveMutex             m_peerServerMutex;

        UI32                   m_peerClientId;
        string                 m_peerClientName;
    protected :
    public :
};

}

#endif // MANAGEMENTINTERFACERECEIVERTHREAD_H
