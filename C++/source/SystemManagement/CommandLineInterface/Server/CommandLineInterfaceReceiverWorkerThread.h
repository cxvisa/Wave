/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef COMMANDLINEINTERFACERECEIVERWORKERTHREAD_H
#define COMMANDLINEINTERFACERECEIVERWORKERTHREAD_H

#include "Framework/MultiThreading/WavePosixThread.h"
#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Utils/WaveMutex.h"
#include "Framework/Utils/WaveCondition.h"

#include <deque>

namespace WaveNs
{

class CommandLineInterfaceReceiverWorkerThread;

typedef void (CommandLineInterfaceReceiverWorkerThread::* WaveMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread) (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, void *pContext);

class ServerStreamingSocket;
class CommandLineInterfaceReceiverObjectManager;
class CommandLineInterfaceWorkerMessage;
class CommandLineInterfaceMessage;
class WaveSystemManagementGetYangUserInterfaceMessage;
class WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage;
class YangElement;

class CommandLineInterfaceReceiverWorkerThread : public WavePosixThread, WaveWorker
{
    private :

                CommandLineInterfaceWorkerMessage *getNextCommandLineInterfaceWorkerMessage                     ();
                void                               processMessages                                              ();
                void                               processSendCallbacks                                         (CommandLineInterfaceMessage *pCommandLineInterfaceMessage);
        virtual WaveMessageStatus                  send                                                         (WaveMessage *pWaveMessage, WaveMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread prismMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread, void *pWaveMessageContext, UI32 timeOutInMilliSeconds = 0, LocationId locationId = 0);

        virtual WaveThreadStatus                   start                                                        ();
                void                               processCommandLineInterfaceMessage                           (CommandLineInterfaceMessage *pCommandLineInterfaceMessage);
                void                               processCommandLineInterfaceMessageToGetYangUserInterface     (CommandLineInterfaceMessage *pCommandLineInterfaceMessage);
                void                               getYangUserInterfaceCallback                                 (FrameworkStatus frameworkStatus, WaveSystemManagementGetYangUserInterfaceMessage *pWaveSystemManagementGetYangUserInterfaceMessage, void *pContext);
                void                               processCommandLineInterfaceMessageToShowRunningConfiguration (CommandLineInterfaceMessage *pCommandLineInterfaceMessage);
                void                               showRunningConfigurationCallback                             (FrameworkStatus frameworkStatus, WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage *pWaveSystemManagementDisplayConfigurationByTargetNodeNameMessage, void *pContext);
                void                               processCommandLineInterfaceMessageToHandleWriteRequest (CommandLineInterfaceMessage *pCommandLineInterfaceMessage);
                WaveCommandLineInterfaceOperationStatus processWriteRequests (vector<string> inputString, string &erroString, bool isWyserEaCompatibilityMode);
                YangElement *                      parseInputArguments (const string &targetNodeName, map<string, string> &listItemsInTargetNodeNameMap);

    protected :
    public :
                                                   CommandLineInterfaceReceiverWorkerThread (CommandLineInterfaceReceiverObjectManager *pCommandLineInterfaceReceiverObjectManager, ServerStreamingSocket *pServerStreamingSocket);
        virtual                                   ~CommandLineInterfaceReceiverWorkerThread ();

                void                               submitCommandLineInterfaceWorkerMessage  (CommandLineInterfaceWorkerMessage *pCommandLineInterfaceWorkerMessage);

    // Now the data members

    private :
        CommandLineInterfaceReceiverObjectManager  *m_pCommandLineInterfaceReceiverObjectManager;
        ServerStreamingSocket                      *m_pServerStreamingSocket;
        WaveMutex                                 *m_pWaveMutex;
        WaveCondition                             *m_pWaveCondition;

        deque<CommandLineInterfaceWorkerMessage *>  m_commandLineInterfaceWorkerMessages;

    protected :
    public :
};

}

#endif // COMMANDLINEINTERFACERECEIVERWORKERTHREAD_H
