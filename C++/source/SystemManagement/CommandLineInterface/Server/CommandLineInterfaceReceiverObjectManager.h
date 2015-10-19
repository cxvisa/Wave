/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef COMMANDLINEINTERFACERECEIVEROBJECTMANAGER_H
#define COMMANDLINEINTERFACERECEIVEROBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"
#include "SystemManagement/CommandLineInterface/Server/CommandLineInterfaceReceiverWorkerThread.h"

namespace WaveNs
{

class ServerStreamingSocket;
class BootCompleteForThisLocationEvent;
class WaveAsynchronousContextForBootPhases;
class CommandLineInterfaceReceiverThread;

class CommandLineInterfaceReceiverObjectManager : public WaveLocalObjectManagerForUserSpecificTasks
{
    private :
                                  CommandLineInterfaceReceiverObjectManager           ();

        virtual void              initialize                                          (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        virtual void              boot                                                (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

        virtual void              listenForEvents                                     (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                void              bootCompleteForThisLocationEventHandler             (const BootCompleteForThisLocationEvent *&pBootCompleteForThisLocationEvent);

        virtual WaveMessageStatus send                                                (WaveMessage *pWaveMessage, WaveMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread waveMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread, void *pWaveMessageContext,  CommandLineInterfaceReceiverWorkerThread *pCommandLineInterfaceReceiverWorkerThread, UI32 timeOutInMilliSeconds = 0, LocationId locationId = 0);
                void              sendCallback                                        (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, void *pContext);

                bool              isAMessageSentByThisObjectManager                   (WaveMessage *pWaveMessage);
                void              addToCommandLineInterfaceReceiverMapsByMessage      (WaveMessage *pWaveMessage, CommandLineInterfaceReceiverWorkerThread *pCommandLineInterfaceReceiverWorkerThread, WaveMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread waveMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread, void *pWaveMessageContext);
                void              removeFromCommandLineInterfaceReceiverMapsByMessage (WaveMessage *pWaveMessage);
                void              getCommandLineInterfaceReceiverDetailsForMessage    (WaveMessage *pWaveMessage, CommandLineInterfaceReceiverWorkerThread *&pCommandLineInterfaceReceiverWorkerThread, WaveMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread &waveMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread, void *&pWaveMessageContext);

    protected :
    public :
        virtual                                          ~CommandLineInterfaceReceiverObjectManager ();

        static string                                     getServiceName                            ();
        static CommandLineInterfaceReceiverObjectManager *getInstance                               ();
        static WaveServiceId                             getWaveServiceId                         ();

    // Now the data members

    private :
        ServerStreamingSocket                                                             *m_pServerSocketForCommandLineInterfaceClients;
        CommandLineInterfaceReceiverThread                                                *m_pCommandLineInterfaceReceiverThread;
        map<UI32, CommandLineInterfaceReceiverWorkerThread *>                              m_commandLineInterfaceReceiverWorkerThreadMapByMessageId;
        map<UI32, WaveMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread>  m_commandLineInterfaceReceiverCallbackMapByMessageId;
        map<UI32, void *>                                                                  m_commandLineInterfaceReceiverContextMapByMessageId;

    protected :
    public:

    friend class CommandLineInterfaceReceiverWorkerThread;
};

}

#endif // COMMANDLINEINTERFACERECEIVEROBJECTMANAGER_H
