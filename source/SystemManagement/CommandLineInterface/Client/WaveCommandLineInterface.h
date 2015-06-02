/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVECOMMANDLINEINTERFACE_H
#define WAVECOMMANDLINEINTERFACE_H

#include "Framework/Types/Types.h"
#include "SystemManagement/CommandLineInterface/Server/CommandLineInterfaceMessage.h"
#include "SystemManagement/CommandLineInterface/Client/CommandLineInterfaceEntry.h"

#include <signal.h>

namespace WaveNs
{

class ClientStreamingSocket;
class YangUserInterface;
class YangElement;

class WaveCommandLineInterface
{
    private :
    protected :
    public :
                                          WaveCommandLineInterface                                (const string &serverIpAddress, const SI32 &serverPort);
                                         ~WaveCommandLineInterface                                ();

               void                       connectToServer                                         ();
               void                       reconnectToServer                                       ();

               void                       sendHelloSecretToServer                                 ();

               void                       post                                                    (CommandLineInterfaceMessage &commandLineInterfaceMessage);
               bool                       receive                                                 (CommandLineInterfaceMessage &commandLineInterfaceMessage);
               ResourceId                 processCommand                                          (CommandLineInterfaceMessage &commandLineInterfaceMessage);

               void                       acceptCommands                                          ();

               void                       displayTopLevelPrompt                                   ();

               void                       initializeCommandLineEntries                            ();
               CommandLineInterfaceEntry *getCommandLineInterfaceEntryForShowRunningConfiguration (const string &commandLine);

        static void                       sigIntHandler                                           (int signal);
        static void                       sigSegvHandler                                          (int signal);
               void                       installSigIntHandlers                                   () const;

        static WaveCommandLineInterface   *getInstance                                            ();
        static vector<YangElement *>       getYangElementsByTargetNodeName                        (const string &targetNodeName);

               CommandLineInterfaceEntry  *getPCurrentModecommandLineInterfaceEntry               ();

               vector<string>             &getCommandHistory                                      ();
               UI32                       &getCommandHistoryCurrentIndex                          ();
               string                     &getCurrentlyTypingCommand                              ();

        static CommandLineInterfaceEntry  *getPCurrentModeCommandLineInterfaceEntry               ();

        // Now the data members

    private :
               string                                    m_serverIpAddress;
               SI32                                      m_serverPort;
               WaveCommandLineInterfaceConnectionStatus  m_connectionStatus;
               ClientStreamingSocket                    *m_pClientStreamingSocket;
               string                                    m_thisMachineIpAddress;
               string                                    m_thisMachineHostName;

               YangUserInterface                        *m_pYangUserInterface;

               CommandLineInterfaceEntry                 m_commandLineinterfaceEntries;
               CommandLineInterfaceEntry                *m_pCurrentModeCommandLineInterfacEntry;

        static WaveCommandLineInterface                 *m_pWaveCommandLineInterface;

    protected :
    public :
};

}

#endif // WAVECOMMANDLINEINTERFACE_H
