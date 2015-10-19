/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "SystemManagement/CommandLineInterface/Server/CommandLineInterfaceReceiverThread.h"
#include "Framework/Utils/ServerStreamingSocket.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "SystemManagement/CommandLineInterface/Server/CommandLineInterfaceReceiverObjectManager.h"
#include "SystemManagement/CommandLineInterface/Server/CommandLineInterfaceReceiverControlThread.h"
#include "SystemManagement/CommandLineInterface/Server/CommandLineInterfaceReceiverWorkerThread.h"

namespace WaveNs
{

CommandLineInterfaceReceiverThread::CommandLineInterfaceReceiverThread (CommandLineInterfaceReceiverObjectManager *pCommandLineInterfaceReceiverObjectManager, ServerStreamingSocket *pServerStreamingSocket)
    : WavePosixThread                              (),
      m_pCommandLineInterfaceReceiverObjectManager  (pCommandLineInterfaceReceiverObjectManager),
      m_pServerSocketForCommandLineInterfaceClients (pServerStreamingSocket)
{
    waveAssert (NULL != m_pCommandLineInterfaceReceiverObjectManager,  __FILE__, __LINE__);
    waveAssert (NULL != m_pServerSocketForCommandLineInterfaceClients, __FILE__, __LINE__);
}

CommandLineInterfaceReceiverThread::~CommandLineInterfaceReceiverThread ()
{
}

WaveThreadStatus CommandLineInterfaceReceiverThread::start ()
{
    trace (TRACE_LEVEL_INFO, "CommandLineInterfaceReceiverThread::start : Now accepting connections from Wave Clients.");

    for (;;)
    {
        ServerStreamingSocket *pNewServerStreamingSocket         = new ServerStreamingSocket;
        bool                   successfullyAcceptedNewConnection = false;

        waveAssert (NULL != pNewServerStreamingSocket, __FILE__, __LINE__);

        trace (TRACE_LEVEL_DEBUG, "CommandLineInterfaceReceiverThread::start : Awaiting NEW Command Line Client Connections...");

        successfullyAcceptedNewConnection = m_pServerSocketForCommandLineInterfaceClients->accept (*pNewServerStreamingSocket);

        if (true != successfullyAcceptedNewConnection)
        {
            trace (TRACE_LEVEL_INFO, "CommandLineInterfaceReceiverThread::start : Could not accept connection from a new Command Line Interface Client.  This could be because of an unwanted Client arbitrarily trying to connect to us.");

            delete pNewServerStreamingSocket;
            continue;
        }

        trace (TRACE_LEVEL_DEBUG, "CommandLineInterfaceReceiverThread::start : Accepted A NEW connection From : " + pNewServerStreamingSocket->getPeerIpAddress ());

        CommandLineInterfaceReceiverControlThread *pCommandLineInterfaceReceiverControlThread = new CommandLineInterfaceReceiverControlThread (m_pCommandLineInterfaceReceiverObjectManager, pNewServerStreamingSocket);

        WaveThreadStatus status = pCommandLineInterfaceReceiverControlThread->run ();

        if (WAVE_THREAD_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "CommandLineInterfaceReceiverObjectManager::boot : A new thread COULD NOT BE CREATED to monitor messages from this newly connected Client.  Status : " + FrameworkToolKit::localize (status));

            delete pCommandLineInterfaceReceiverControlThread;
        }
        else
        {
            trace (TRACE_LEVEL_DEBUG, "CommandLineInterfaceReceiverThread::start : Now a new thread will monitor messages from this newly connected Client.");
        }
    }

    return (WAVE_THREAD_SUCCESS);
}

}
