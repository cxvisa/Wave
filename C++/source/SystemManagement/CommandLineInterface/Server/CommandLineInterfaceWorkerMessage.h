/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef COMMANDLINEINTERFACEWORKERMESSAGE_H
#define COMMANDLINEINTERFACEWORKERMESSAGE_H

#include "Framework/Types/Types.h"

namespace WaveNs
{

class CommandLineInterfaceMessage;
class CommandLineInterfaceWorkerSendContext;

class CommandLineInterfaceWorkerMessage
{
    private :
    protected :
    public :
                                                 CommandLineInterfaceWorkerMessage           (CommandLineInterfaceMessage           *pCommandLineInterfaceMessage);
                                                 CommandLineInterfaceWorkerMessage           (CommandLineInterfaceWorkerSendContext *pCommandLineInterfaceWorkerSendContext);
                                                ~CommandLineInterfaceWorkerMessage           ();

        WaveCommandLineInterfaceWorkerOperation  getWaveCommandLineInterfaceWorkerOperation  ();
        CommandLineInterfaceMessage             *getPCommandLineInterfaceMessage             ();
        void                                     setPCommandLineInterfaceMessage             (CommandLineInterfaceMessage *pCommandLineInterfaceMessage);
        CommandLineInterfaceWorkerSendContext   *getPCommandLineInterfaceWorkerSenderContext ();
        void                                     setPCommandLineInterfaceWorkerSenderContext (CommandLineInterfaceWorkerSendContext *pCommandLineInterfaceWorkerSendContext);

        // Now the data members

    private :
        WaveCommandLineInterfaceWorkerOperation  m_commandLineInterfaceWorkerOperation;
        CommandLineInterfaceMessage             *m_pcommandLineInterfaceMessage;
        CommandLineInterfaceWorkerSendContext   *m_pCommandLineInterfaceWorkerSendContext;

    protected :
    public :
};

}

#endif // COMMANDLINEINTERFACEWORKERMESSAGE_H
