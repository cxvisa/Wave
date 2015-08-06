/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMESSAGINGBROKERCLIENTRECEIVEROBJECTMANAGER_H
#define WAVEMESSAGINGBROKERCLIENTRECEIVEROBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"

namespace WaveNs
{

class WaveAsynchronousContextForBootPhases;
class ServerStreamingSocket;
class BootCompleteForThisLocationEvent;

class WaveMessagingBrokerClientReceiverObjectManager : public WaveLocalObjectManagerForUserSpecificTasks
{
    private :
        virtual void boot                                         (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        virtual void initialize                                   (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

        virtual void listenForEvents                              (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                void bootCompleteForThisLocationEventHandler      (const BootCompleteForThisLocationEvent *&pBootCompleteForThisLocationEvent);

                void  registerWaveBrokerBasedMessageInstantiators ();

        static  void debugConnectToWaveMessageBroker              (UI32 argc, vector<string> argv);
        static  void debugSubscribeToWaveMessageBroker            (UI32 argc, vector<string> argv);
        static  void registerDebugShellEntries                    ();


    protected :
    public :
                                                                WaveMessagingBrokerClientReceiverObjectManager ();
        virtual                                                ~WaveMessagingBrokerClientReceiverObjectManager ();

        static  WaveMessagingBrokerClientReceiverObjectManager *getInstance                                    ();
        static  WaveServiceId                                  getWaveServiceId                              ();
        static  string                                          getServiceName                                 ();

    // Now the data members

    private :
        ServerStreamingSocket *m_pServerSocketForWaveMessagingBrokerClients;

    protected :
    public :
};

}

#endif // WAVEMESSAGINGBROKERCLIENTRECEIVEROBJECTMANAGER_H
