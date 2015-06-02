/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef COMMANDLINEINTERFACEWORKERSENDCONTEXT_H
#define COMMANDLINEINTERFACEWORKERSENDCONTEXT_H

#include "Framework/Messaging/Local/PrismMessage.h"
#include "Framework/ObjectModel/PrismElement.h"
#include "SystemManagement/CommandLineInterface/Server/CommandLineInterfaceReceiverWorkerThread.h"

namespace WaveNs
{

class CommandLineInterfaceWorkerSendContext
{
    private :
    protected :
    public :
                                                                                CommandLineInterfaceWorkerSendContext (FrameworkStatus frameworkStatus, PrismMessage *pPrismMessage, PrismMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread prismMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread, void *pPrismMessageContext);
                                                                               ~CommandLineInterfaceWorkerSendContext ();

        FrameworkStatus                                                         getFrameworkStatus                    ();
        PrismMessage                                                           *getPPrismMessage                      ();
        PrismMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread  getPrismMessageResponseHandler        ();
        void                                                                   *getPPrismMessageContext               ();

    // Now the Data Members

    private :
        FrameworkStatus                                                         m_frameworkStatus;
        PrismMessage                                                           *m_pPrismMessage;
        PrismMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread  m_prismMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread;
        void                                                                   *m_pPrismMessageContext;

    protected :
    public :
};

}

#endif // COMMANDLINEINTERFACEWORKERSENDCONTEXT_H
