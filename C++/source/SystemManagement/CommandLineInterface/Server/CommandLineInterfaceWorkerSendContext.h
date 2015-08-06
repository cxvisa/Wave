/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef COMMANDLINEINTERFACEWORKERSENDCONTEXT_H
#define COMMANDLINEINTERFACEWORKERSENDCONTEXT_H

#include "Framework/Messaging/Local/WaveMessage.h"
#include "Framework/ObjectModel/PrismElement.h"
#include "SystemManagement/CommandLineInterface/Server/CommandLineInterfaceReceiverWorkerThread.h"

namespace WaveNs
{

class CommandLineInterfaceWorkerSendContext
{
    private :
    protected :
    public :
                                                                                CommandLineInterfaceWorkerSendContext (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, WaveMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread prismMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread, void *pWaveMessageContext);
                                                                               ~CommandLineInterfaceWorkerSendContext ();

        FrameworkStatus                                                         getFrameworkStatus                    ();
        WaveMessage                                                           *getPWaveMessage                      ();
        WaveMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread  getWaveMessageResponseHandler        ();
        void                                                                   *getPWaveMessageContext               ();

    // Now the Data Members

    private :
        FrameworkStatus                                                         m_frameworkStatus;
        WaveMessage                                                           *m_pWaveMessage;
        WaveMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread  m_prismMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread;
        void                                                                   *m_pWaveMessageContext;

    protected :
    public :
};

}

#endif // COMMANDLINEINTERFACEWORKERSENDCONTEXT_H
