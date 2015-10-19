/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "SystemManagement/CommandLineInterface/Server/CommandLineInterfaceWorkerSendContext.h"

namespace WaveNs
{

CommandLineInterfaceWorkerSendContext::CommandLineInterfaceWorkerSendContext (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, WaveMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread waveMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread, void *pWaveMessageContext)
    : m_frameworkStatus                                                        (frameworkStatus),
      m_pWaveMessage                                                          (pWaveMessage),
      m_waveMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread (waveMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread),
      m_pWaveMessageContext                                                   (pWaveMessageContext)
{
}

CommandLineInterfaceWorkerSendContext::~CommandLineInterfaceWorkerSendContext ()
{
}

FrameworkStatus CommandLineInterfaceWorkerSendContext::getFrameworkStatus ()
{
    return (m_frameworkStatus);
}

WaveMessage *CommandLineInterfaceWorkerSendContext::getPWaveMessage ()
{
    return (m_pWaveMessage);
}

WaveMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread CommandLineInterfaceWorkerSendContext::getWaveMessageResponseHandler ()
{
    return (m_waveMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread);
}

void *CommandLineInterfaceWorkerSendContext::getPWaveMessageContext ()
{
    return (m_pWaveMessageContext);
}

}
