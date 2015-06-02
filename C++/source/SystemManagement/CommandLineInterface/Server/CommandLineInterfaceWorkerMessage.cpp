/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "SystemManagement/CommandLineInterface/Server/CommandLineInterfaceWorkerMessage.h"
#include "SystemManagement/CommandLineInterface/Server/CommandLineInterfaceMessage.h"
#include "SystemManagement/CommandLineInterface/Server/CommandLineInterfaceWorkerSendContext.h"

namespace WaveNs
{

CommandLineInterfaceWorkerMessage::CommandLineInterfaceWorkerMessage (CommandLineInterfaceMessage *pCommandLineInterfaceMessage)
    : m_commandLineInterfaceWorkerOperation    (WAVE_CLI_WORKER_OPERATION_USER_REQUEST),
      m_pcommandLineInterfaceMessage           (pCommandLineInterfaceMessage),
      m_pCommandLineInterfaceWorkerSendContext (NULL)
{
}

CommandLineInterfaceWorkerMessage::CommandLineInterfaceWorkerMessage (CommandLineInterfaceWorkerSendContext *pCommandLineInterfaceWorkerSendContext)
    : m_commandLineInterfaceWorkerOperation    (WAVE_CLI_WORKER_OPERATION_SEND_CALLBACK),
      m_pcommandLineInterfaceMessage           (NULL),
      m_pCommandLineInterfaceWorkerSendContext (pCommandLineInterfaceWorkerSendContext)
{
}

CommandLineInterfaceWorkerMessage::~CommandLineInterfaceWorkerMessage ()
{
    if (NULL != m_pcommandLineInterfaceMessage)
    {
        delete m_pcommandLineInterfaceMessage;
    }

    if (NULL != m_pCommandLineInterfaceWorkerSendContext)
    {
        delete m_pCommandLineInterfaceWorkerSendContext;
    }
}

WaveCommandLineInterfaceWorkerOperation CommandLineInterfaceWorkerMessage::getWaveCommandLineInterfaceWorkerOperation ()
{
    return (m_commandLineInterfaceWorkerOperation);
}

CommandLineInterfaceMessage *CommandLineInterfaceWorkerMessage::getPCommandLineInterfaceMessage ()
{
    return (m_pcommandLineInterfaceMessage);
}

void CommandLineInterfaceWorkerMessage::setPCommandLineInterfaceMessage (CommandLineInterfaceMessage *pCommandLineInterfaceMessage)
{
    m_pcommandLineInterfaceMessage = pCommandLineInterfaceMessage;
}

CommandLineInterfaceWorkerSendContext *CommandLineInterfaceWorkerMessage::getPCommandLineInterfaceWorkerSenderContext ()
{
    return (m_pCommandLineInterfaceWorkerSendContext);
}

void CommandLineInterfaceWorkerMessage::setPCommandLineInterfaceWorkerSenderContext (CommandLineInterfaceWorkerSendContext *pCommandLineInterfaceWorkerSendContext)
{
    m_pCommandLineInterfaceWorkerSendContext = pCommandLineInterfaceWorkerSendContext;
}

}
