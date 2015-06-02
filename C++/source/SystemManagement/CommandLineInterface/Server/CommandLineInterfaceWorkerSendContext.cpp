/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "SystemManagement/CommandLineInterface/Server/CommandLineInterfaceWorkerSendContext.h"

namespace WaveNs
{

CommandLineInterfaceWorkerSendContext::CommandLineInterfaceWorkerSendContext (FrameworkStatus frameworkStatus, PrismMessage *pPrismMessage, PrismMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread prismMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread, void *pPrismMessageContext)
    : m_frameworkStatus                                                        (frameworkStatus),
      m_pPrismMessage                                                          (pPrismMessage),
      m_prismMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread (prismMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread),
      m_pPrismMessageContext                                                   (pPrismMessageContext)
{
}

CommandLineInterfaceWorkerSendContext::~CommandLineInterfaceWorkerSendContext ()
{
}

FrameworkStatus CommandLineInterfaceWorkerSendContext::getFrameworkStatus ()
{
    return (m_frameworkStatus);
}

PrismMessage *CommandLineInterfaceWorkerSendContext::getPPrismMessage ()
{
    return (m_pPrismMessage);
}

PrismMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread CommandLineInterfaceWorkerSendContext::getPrismMessageResponseHandler ()
{
    return (m_prismMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread);
}

void *CommandLineInterfaceWorkerSendContext::getPPrismMessageContext ()
{
    return (m_pPrismMessageContext);
}

}
