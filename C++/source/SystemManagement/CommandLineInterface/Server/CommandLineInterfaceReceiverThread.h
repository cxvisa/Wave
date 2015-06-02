/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef COMMANDLINEINTERFACERECEIVERTHREAD_H
#define COMMANDLINEINTERFACERECEIVERTHREAD_H

#include "Framework/MultiThreading/PrismPosixThread.h"

namespace WaveNs
{

class ServerStreamingSocket;
class CommandLineInterfaceReceiverObjectManager;

class CommandLineInterfaceReceiverThread : public PrismPosixThread
{
    private :
        virtual WaveThreadStatus start ();

    protected :
    public :
                 CommandLineInterfaceReceiverThread (CommandLineInterfaceReceiverObjectManager *pCommandLineInterfaceReceiverObjectManager, ServerStreamingSocket *pServerStreamingSocket);
        virtual ~CommandLineInterfaceReceiverThread ();

    // Now the data members

    private :
        CommandLineInterfaceReceiverObjectManager *m_pCommandLineInterfaceReceiverObjectManager;
        ServerStreamingSocket                     *m_pServerSocketForCommandLineInterfaceClients;

    protected :
    public :
};

}

#endif // COMMANDLINEINTERFACERECEIVERTHREAD_H
