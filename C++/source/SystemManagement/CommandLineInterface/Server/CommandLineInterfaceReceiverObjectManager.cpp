/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "SystemManagement/CommandLineInterface/Server/CommandLineInterfaceReceiverObjectManager.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Utils/ServerStreamingSocket.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Boot/BootCompleteForThisLocationEvent.h"
#include "Framework/Boot/BootTypes.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"
#include "SystemManagement/CommandLineInterface/Server/CommandLineInterfaceReceiverThread.h"
#include "SystemManagement/CommandLineInterface/Server/CommandLineInterfaceReceiverWorkerThread.h"
#include "SystemManagement/CommandLineInterface/Server/CommandLineInterfaceWorkerMessage.h"
#include "SystemManagement/CommandLineInterface/Server/CommandLineInterfaceWorkerSendContext.h"

namespace WaveNs
{

CommandLineInterfaceReceiverObjectManager::CommandLineInterfaceReceiverObjectManager ()
    : WaveLocalObjectManagerForUserSpecificTasks    (getServiceName ()),
      m_pServerSocketForCommandLineInterfaceClients (NULL),
      m_pCommandLineInterfaceReceiverThread         (NULL)
{
    setAllowAutomaticallyUnlistenForEvents (false);

    restrictMessageHistoryLogging (false, false, false);
}

CommandLineInterfaceReceiverObjectManager::~CommandLineInterfaceReceiverObjectManager ()
{
}

string CommandLineInterfaceReceiverObjectManager::getServiceName ()
{
    return ("Command Line Interface Receiver");
}

CommandLineInterfaceReceiverObjectManager *CommandLineInterfaceReceiverObjectManager::getInstance ()
{
    static CommandLineInterfaceReceiverObjectManager *pCommandLineInterfaceReceiverObjectManager = new CommandLineInterfaceReceiverObjectManager ();

    WaveNs::waveAssert (NULL != pCommandLineInterfaceReceiverObjectManager, __FILE__, __LINE__);

    return (pCommandLineInterfaceReceiverObjectManager);
}

WaveServiceId CommandLineInterfaceReceiverObjectManager::getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

void CommandLineInterfaceReceiverObjectManager::initialize (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    ResourceId status = WAVE_MESSAGE_SUCCESS;

    m_pServerSocketForCommandLineInterfaceClients = new ServerStreamingSocket (FrameworkToolKit::getCommandLineInterfaceReceiverPort (), 1);

    waveAssert (NULL != m_pServerSocketForCommandLineInterfaceClients, __FILE__, __LINE__);

    status = m_pServerSocketForCommandLineInterfaceClients->getStatus ();

    if (SERVER_STREAMING_SOCKET_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, "CommandLineInterfaceReceiverObjectManager::initialize : Could not bind to the Command Line Interface Receiver Port.  Please make sure that this port is not used by any other application.  Otherwise specify a different port for this purpose.");

        status = WAVE_MESSAGE_ERROR;
    }
    else
    {
        trace (TRACE_LEVEL_DEBUG, "CommandLineInterfaceReceiverObjectManager::initialize : Successfully bound to the Management Interface Receiver Port");

        status = WAVE_MESSAGE_SUCCESS;
    }

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (status);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void CommandLineInterfaceReceiverObjectManager::boot (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void CommandLineInterfaceReceiverObjectManager::listenForEvents (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    listenForEvent (WaveFrameworkObjectManager::getWaveServiceId (), BOOT_COMPLETE_FOR_THIS_LOCATION, reinterpret_cast<WaveEventHandler> (&CommandLineInterfaceReceiverObjectManager::bootCompleteForThisLocationEventHandler));

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void CommandLineInterfaceReceiverObjectManager::bootCompleteForThisLocationEventHandler (const BootCompleteForThisLocationEvent *&pBootCompleteForThisLocationEvent)
{
    // Since we told framework not to unlistenEvents, we must explicitly unlisten for events since we are going to go into an infinite while loop.

    unlistenEvents ();

    reply (reinterpret_cast<const WaveEvent *&> (pBootCompleteForThisLocationEvent));

    m_pCommandLineInterfaceReceiverThread = new CommandLineInterfaceReceiverThread (this, m_pServerSocketForCommandLineInterfaceClients);

    waveAssert (NULL != m_pCommandLineInterfaceReceiverThread, __FILE__, __LINE__);

    m_pCommandLineInterfaceReceiverThread->run ();
}

WaveMessageStatus CommandLineInterfaceReceiverObjectManager::send (WaveMessage *pWaveMessage, WaveMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread prismMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread, void *pWaveMessageContext, CommandLineInterfaceReceiverWorkerThread *pCommandLineInterfaceReceiverWorkerThread, UI32 timeOutInMilliSeconds, LocationId locationId)
{
    if (NULL != pCommandLineInterfaceReceiverWorkerThread)
    {
        addToCommandLineInterfaceReceiverMapsByMessage (pWaveMessage, pCommandLineInterfaceReceiverWorkerThread, prismMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread, pWaveMessageContext);

        return (WaveObjectManager::send (pWaveMessage, reinterpret_cast<WaveMessageResponseHandler> (&CommandLineInterfaceReceiverObjectManager::sendCallback), pWaveMessageContext, timeOutInMilliSeconds, locationId, this));
    }
    else
    {
        waveAssert (false, __FILE__, __LINE__);
    }

    return (WAVE_MESSAGE_ERROR);
}

void CommandLineInterfaceReceiverObjectManager::sendCallback (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, void *pContext)
{
    waveAssert (NULL != pWaveMessage, __FILE__, __LINE__);

    CommandLineInterfaceReceiverWorkerThread                               *pCommandLineInterfaceReceiverWorkerThread                              = NULL;
    WaveMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread  prismMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread = NULL;
    void                                                                   *pWaveMessageContext                                                   = NULL;

    getCommandLineInterfaceReceiverDetailsForMessage (pWaveMessage, pCommandLineInterfaceReceiverWorkerThread, prismMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread, pWaveMessageContext);

    waveAssert (NULL != pCommandLineInterfaceReceiverWorkerThread,                              __FILE__, __LINE__);
    waveAssert (NULL != prismMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread, __FILE__, __LINE__);
    waveAssert (NULL != pWaveMessageContext,                                                   __FILE__, __LINE__);

    removeFromCommandLineInterfaceReceiverMapsByMessage (pWaveMessage);

    CommandLineInterfaceWorkerSendContext *pCommandLineInterfaceWorkerSendContext = new CommandLineInterfaceWorkerSendContext (frameworkStatus, pWaveMessage, prismMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread, pWaveMessageContext);

    waveAssert (NULL != pCommandLineInterfaceWorkerSendContext, __FILE__, __LINE__);

    CommandLineInterfaceWorkerMessage *pCommandLineInterfaceWorkerMessage = new CommandLineInterfaceWorkerMessage (pCommandLineInterfaceWorkerSendContext);

    waveAssert (NULL != pCommandLineInterfaceWorkerMessage, __FILE__, __LINE__);

    pCommandLineInterfaceReceiverWorkerThread->submitCommandLineInterfaceWorkerMessage (pCommandLineInterfaceWorkerMessage);
}

bool CommandLineInterfaceReceiverObjectManager::isAMessageSentByThisObjectManager (WaveMessage *pWaveMessage)
{
    UI32                                                                  messageId  = pWaveMessage->getMessageId                                   ();
    map<UI32, CommandLineInterfaceReceiverWorkerThread *>::const_iterator element    = m_commandLineInterfaceReceiverWorkerThreadMapByMessageId.find (messageId);
    map<UI32, CommandLineInterfaceReceiverWorkerThread *>::const_iterator endElement = m_commandLineInterfaceReceiverWorkerThreadMapByMessageId.end  ();
    bool                                                                  isKnown    = false;

    if (endElement == element)
    {
        isKnown = false;
    }
    else
    {
        isKnown = true;
    }

    return (isKnown);
}

void CommandLineInterfaceReceiverObjectManager::addToCommandLineInterfaceReceiverMapsByMessage (WaveMessage *pWaveMessage, CommandLineInterfaceReceiverWorkerThread *pCommandLineInterfaceReceiverWorkerThread, WaveMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread prismMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread, void *pWaveMessageContext)
{
    waveAssert (NULL != pWaveMessage,                             __FILE__, __LINE__);
    waveAssert (NULL != pCommandLineInterfaceReceiverWorkerThread, __FILE__, __LINE__);

    bool isKnown = isAMessageSentByThisObjectManager (pWaveMessage);

    if (true == isKnown)
    {
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        UI32 messageId = pWaveMessage->getMessageId ();

        m_commandLineInterfaceReceiverWorkerThreadMapByMessageId[messageId] = pCommandLineInterfaceReceiverWorkerThread;
        m_commandLineInterfaceReceiverCallbackMapByMessageId[messageId]     = prismMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread;
        m_commandLineInterfaceReceiverContextMapByMessageId[messageId]      = pWaveMessageContext;
    }
}

void CommandLineInterfaceReceiverObjectManager::getCommandLineInterfaceReceiverDetailsForMessage    (WaveMessage *pWaveMessage, CommandLineInterfaceReceiverWorkerThread *&pCommandLineInterfaceReceiverWorkerThread, WaveMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread &prismMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread, void *&pWaveMessageContext)
{
    waveAssert (NULL != pWaveMessage, __FILE__, __LINE__);

    bool isKnown = isAMessageSentByThisObjectManager (pWaveMessage);

    pCommandLineInterfaceReceiverWorkerThread                              = NULL;
    prismMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread = NULL;
    pWaveMessageContext                                                   = NULL;

    if (false == isKnown)
    {
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        UI32 messageId = pWaveMessage->getMessageId ();

        pCommandLineInterfaceReceiverWorkerThread                              = m_commandLineInterfaceReceiverWorkerThreadMapByMessageId[messageId];
        prismMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread = m_commandLineInterfaceReceiverCallbackMapByMessageId[messageId];
        pWaveMessageContext                                                   = m_commandLineInterfaceReceiverContextMapByMessageId[messageId];

        waveAssert (NULL != pCommandLineInterfaceReceiverWorkerThread,                              __FILE__, __LINE__);
        waveAssert (NULL != prismMessageResponseHandlerForCommandLineInterfaceReceiverWorkerThread, __FILE__, __LINE__);
        waveAssert (NULL != pWaveMessageContext,                                                   __FILE__, __LINE__);
    }
}

void CommandLineInterfaceReceiverObjectManager::removeFromCommandLineInterfaceReceiverMapsByMessage (WaveMessage *pWaveMessage)
{
    waveAssert (NULL != pWaveMessage, __FILE__, __LINE__);

    bool isKnown = isAMessageSentByThisObjectManager (pWaveMessage);

    if (false == isKnown)
    {
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        bool isLastReply = pWaveMessage->getIsLastReply ();

        if (true == isLastReply)
        {
            m_commandLineInterfaceReceiverWorkerThreadMapByMessageId.erase (pWaveMessage->getMessageId ());

            UI32 messageId = pWaveMessage->getMessageId ();

            m_commandLineInterfaceReceiverWorkerThreadMapByMessageId.erase (messageId);
            m_commandLineInterfaceReceiverCallbackMapByMessageId.erase     (messageId);
            m_commandLineInterfaceReceiverContextMapByMessageId.erase      (messageId);
        }
    }
}

}
