/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMESSAGINGBROKERCLIENTRECEIVERTHREAD_H
#define WAVEMESSAGINGBROKERCLIENTRECEIVERTHREAD_H

#include "Framework/MultiThreading/WavePosixThread.h"
#include "Framework/Utils/WaveMutex.h"

namespace WaveNs
{

class ServerStreamingSocket;
class WaveBrokerBasedMessage;
class WaveBrokerPublishMessage;

class WaveMessagingBrokerClientReceiverThread : public WavePosixThread
{
    private :
                                 WaveMessagingBrokerClientReceiverThread (ServerStreamingSocket *pServerStreamingSocket);

        virtual WaveThreadStatus start                                   ();

                bool             authorizeClient                         ();

                void             setPeerServerDetails                    (const string &peerServerIpAddress, const SI32 &peerServerPort);

                void             setPeerClientName                       (const string &peerClientName);
                string           getPeerClientName                       () const;

                void             processWaveBrokerBasedMessage           (WaveBrokerBasedMessage   *pWaveBrokerBasedMessage, const char *pMessageBuffer);
                void             processWaveBrokerBasedMessage           (WaveBrokerPublishMessage *pWaveBrokerPublishMessage);

                void             reconnectToPeerServer                   ();

    protected :
    public :
        virtual ~WaveMessagingBrokerClientReceiverThread ();

    // Now the data members

    private :
        ServerStreamingSocket *m_pServerStreamingSocket;
        string                 m_peerServerIpAddress;
        SI32                   m_peerServerPort;
        WaveMutex             m_peerServerMutex;

        string                 m_peerClientName;

        string                 m_brokerNameFromClientPerspective;

    protected :
    public :

    friend class WaveMessagingBrokerClientReceiverObjectManager;
};

}

#endif // WAVEMESSAGINGBROKERCLIENTRECEIVERTHREAD_H
