/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMESSAGINGBROKERRECEIVERTHREAD_H
#define WAVEMESSAGINGBROKERRECEIVERTHREAD_H

#include "Framework/MultiThreading/WavePosixThread.h"
#include "Framework/Utils/WaveMutex.h"

namespace WaveNs
{

class ServerStreamingSocket;
class WaveBrokerSubscribeMessage;
class WaveBrokerUnsubscribeMessage;
class WaveBrokerBasedMessagePayload;

class WaveMessagingBrokerReceiverThread : public WavePosixThread
{
    private :
                                 WaveMessagingBrokerReceiverThread (ServerStreamingSocket *pServerStreamingSocket);

        virtual WaveThreadStatus start                             ();

                bool             authorizeClient                   ();

                void             setPeerServerDetails              (const string &peerServerIpAddress, const SI32 &peerServerPort);

                void             setPeerClientName                 (const string &peerClientName);
                string           getPeerClientName                 () const;

                void             processWaveBrokerBasedMessage     (WaveBrokerBasedMessagePayload *pWaveBrokerBasedMessagePayload);
                void             processWaveBrokerBasedMessage     (WaveBrokerSubscribeMessage    *pWaveBrokerSubscribeMessage);
                void             processWaveBrokerBasedMessage     (WaveBrokerUnsubscribeMessage  *pWaveBrokerUnsubscribeMessage);
                void             processWaveBrokerPublishMessage   (WaveBrokerBasedMessagePayload *pWaveBrokerBasedMessagePayload);


    protected :
    public :
        virtual ~WaveMessagingBrokerReceiverThread ();

    // Now the data members

    private :
        ServerStreamingSocket *m_pServerStreamingSocket;
        string                 m_peerServerIpAddress;
        SI32                   m_peerServerPort;
        string                 m_peerServerUniqueString;
        WaveMutex             m_peerServerMutex;

        string                 m_peerClientName;

    protected :
    public :

    friend class WaveMessagingBrokerReceiverObjectManager;
};

}

#endif // WAVEMESSAGINGBROKERRECEIVERTHREAD_H
