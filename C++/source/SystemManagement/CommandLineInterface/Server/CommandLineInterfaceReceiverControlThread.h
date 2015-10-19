/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef COMMANDLINEINTERFACERECEIVERCONTROLTHREAD_H
#define COMMANDLINEINTERFACERECEIVERCONTROLTHREAD_H

#include "Framework/MultiThreading/WavePosixThread.h"
#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class ServerStreamingSocket;
class CommandLineInterfaceReceiverObjectManager;
class CommandLineInterfaceReceiverWorkerThread;

class CommandLineInterfaceReceiverControlThread : public WavePosixThread, WaveWorker
{
    private :
        virtual WaveThreadStatus start     ();

                bool             authorize ();

    protected :
    public :
                 CommandLineInterfaceReceiverControlThread (CommandLineInterfaceReceiverObjectManager *pCommandLineInterfaceReceiverObjectManager, ServerStreamingSocket *pServerStreamingSocket);
        virtual ~CommandLineInterfaceReceiverControlThread ();

    // Now the data members

    private :
        ServerStreamingSocket                     *m_pServerStreamingSocket;
        bool                                       m_transferredSocketcontrol;

        CommandLineInterfaceReceiverObjectManager *m_pCommandLineInterfaceReceiverObjectManager;
        CommandLineInterfaceReceiverWorkerThread  *m_pCommandLineInterfaceReceiverWorkerThread;

    protected :
    public :
};

}

#endif // COMMANDLINEINTERFACERECEIVERCONTROLTHREAD_H
