/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMESSAGINGBROKERRECEIVEROBJECTMANAGER_H
#define WAVEMESSAGINGBROKERRECEIVEROBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"

namespace WaveNs
{

class WaveAsynchronousContextForBootPhases;
class ServerStreamingSocket;
class BootCompleteForThisLocationEvent;

class WaveMessagingBrokerReceiverObjectManager : public WaveLocalObjectManagerForUserSpecificTasks
{
    private :
        virtual void boot                                        (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        virtual void initialize                                  (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

        virtual void listenForEvents                             (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                void bootCompleteForThisLocationEventHandler     (const BootCompleteForThisLocationEvent *&pBootCompleteForThisLocationEvent);

                void registerWaveBrokerBasedMessageInstantiators ();

        static  void debugPrintBrokerClientRepository             (UI32 argc, vector<string> argv);
        static  void registerDebugShellEntries                    ();


    protected :
    public :
                                                          WaveMessagingBrokerReceiverObjectManager ();
        virtual                                          ~WaveMessagingBrokerReceiverObjectManager ();

        static  WaveMessagingBrokerReceiverObjectManager *getInstance                              ();
        static  PrismServiceId                            getPrismServiceId                        ();
        static  string                                    getServiceName                           ();

    // Now the data members

    private :
        ServerStreamingSocket *m_pServerSocketForWaveMessagingBrokerClients;

    protected :
    public :
};

}

#endif // WAVEMESSAGINGBROKERRECEIVEROBJECTMANAGER_H
