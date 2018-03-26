/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/ClientDatagramSocket.h"
#include "Framework/Utils/ServerDatagramSocket.h"
#include "Framework/Messaging/LightHouse/LightHouseReceiverObjectManager.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Boot/BootCompleteForThisLocationEvent.h"
#include "Framework/Boot/BootTypes.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Messaging/LightHouse/LightHouseToolKit.h"
#include "Framework/Messaging/LightHouse/LightPulseDispatchMessage.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/MulticastReceiverSocket.h"
#include "Framework/Utils/MulticastSenderSocket.h"
#include "Shell/ShellDebug.h"

namespace WaveNs
{

LightHouseReceiverObjectManager::LightHouseReceiverObjectManager ()
    : WaveLocalObjectManagerForUserSpecificTasks (getServiceName ()),
      m_pMulticastReceiverSocket                 (NULL)
{
    setAllowAutomaticallyUnlistenForEvents (false);

    addDebugFunction ((ShellCmdFunction) (&LightHouseReceiverObjectManager::sendMessageToMulticastGroup),      "sendMessageToMulticastGroup");
    addDebugFunction ((ShellCmdFunction) (&LightHouseReceiverObjectManager::receiveMessageFromMulticastGroup), "receiveMessageFromMulticastGroup");
    addDebugFunction ((ShellCmdFunction) (&LightHouseReceiverObjectManager::clientDatagramTest),               "clientDatagramTest");
    addDebugFunction ((ShellCmdFunction) (&LightHouseReceiverObjectManager::serverDatagramTest),               "serverDatagramTest");
}

LightHouseReceiverObjectManager::~LightHouseReceiverObjectManager ()
{
}

string LightHouseReceiverObjectManager::getServiceName ()
{
    return ("Light House Receiver");
}

LightHouseReceiverObjectManager *LightHouseReceiverObjectManager::getInstance ()
{
    static LightHouseReceiverObjectManager *pLightHouseReceiverObjectManager = new LightHouseReceiverObjectManager ();

    WaveNs::waveAssert (NULL != pLightHouseReceiverObjectManager, __FILE__, __LINE__);

    return (pLightHouseReceiverObjectManager);
}

WaveServiceId LightHouseReceiverObjectManager::getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

void LightHouseReceiverObjectManager::initialize (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    m_pMulticastReceiverSocket = new MulticastReceiverSocket (LightHouseToolKit::getLightHouseMulticastIpAddress (), LightHouseToolKit::getLightHouseMulticastPort ());

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void LightHouseReceiverObjectManager::boot (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void LightHouseReceiverObjectManager::listenForEvents (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    listenForEvent (WaveFrameworkObjectManager::getWaveServiceId (), BOOT_COMPLETE_FOR_THIS_LOCATION, reinterpret_cast<WaveEventHandler> (&LightHouseReceiverObjectManager::bootCompleteForThisLocationEventHandler));

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void LightHouseReceiverObjectManager::bootCompleteForThisLocationEventHandler (const BootCompleteForThisLocationEvent *&pBootCompleteForThisLocationEvent)
{
    // Since we told framework not to unlistenEvents, we must explicitly unlisten for events since we are going to go into an infinite while loop.

    unlistenEvents ();

    reply (reinterpret_cast<const WaveEvent *&> (pBootCompleteForThisLocationEvent));

    trace (TRACE_LEVEL_INFO, "LightHouseReceiverObjectManager::bootCompleteForThisLocationEventHandler : Now accepting connections from Wave Clients.");

    for (;;)
    {
        const UI32 maximumBufferSizeToRead = 4096;

        FixedSizeBuffer fixedSizeBuffer (maximumBufferSizeToRead + 1);
        string          from;
        SI32            port;

        bool status = m_pMulticastReceiverSocket->receive (&fixedSizeBuffer, from, port);
        string lightPulseString;

        fixedSizeBuffer.toString (lightPulseString);

        if (true == status)
        {
            // trace (TRACE_LEVEL_INFO, string ("LightHouseReceiverObjectManager::bootCompleteForThisLocationEventHandler : Received a Light Pulse : ") + lightPulseString + ", from : " + from + ", port : " + port);

            LightPulseDispatchMessage *pLightPulseDispatchMessage = new LightPulseDispatchMessage ();

            waveAssert (NULL != pLightPulseDispatchMessage, __FILE__, __LINE__);

            pLightPulseDispatchMessage->setLightPulseSerializedString (lightPulseString);
            pLightPulseDispatchMessage->setSenderIpAddress (from);
            pLightPulseDispatchMessage->setSenderPort (port);

            WaveMessageStatus sendStatus = sendOneWay (pLightPulseDispatchMessage);

            if (WAVE_MESSAGE_SUCCESS != sendStatus)
            {
                trace (TRACE_LEVEL_ERROR, "LightHouseReceiverObjectManager::bootCompleteForThisLocationEventHandler : Error in sending message to dispatch a light pulse.  Status : " + FrameworkToolKit::localize (sendStatus));
                trace (TRACE_LEVEL_ERROR, "LightHouseReceiverObjectManager::bootCompleteForThisLocationEventHandler : Errored Light Pulse : \n" + lightPulseString);
            }
        }
    }
}

UI32 LightHouseReceiverObjectManager::sendMessageToMulticastGroup (UI32 argc, vector<string> argv)
{
    if (argc >= 4)
    {
        string multicastGroupIpAddress = argv[1];
        SI32   multicastGroupPort      = atoi (argv[2].c_str ());
        string messageToSend           = argv[3];

        MulticastSenderSocket multicastSenderSocket (multicastGroupIpAddress, multicastGroupPort);

        bool status = multicastSenderSocket.send (messageToSend);

        if (true == status)
        {
            WaveNs::trace (TRACE_LEVEL_SUCCESS, "LightHouseReceiverObjectManager::sendMessageToMulticastGroup : Succeeded.");
        }
        else
        {
            WaveNs::trace (TRACE_LEVEL_ERROR, "LightHouseReceiverObjectManager::sendMessageToMulticastGroup : Failed.");
        }
    }

    return (0);
}

UI32 LightHouseReceiverObjectManager::receiveMessageFromMulticastGroup (UI32 argc, vector<string> argv)
{
    if (argc >= 3)
    {
        string multicastGroupIpAddress = argv[1];
        SI32   multicastGroupPort      = atoi (argv[2].c_str ());
        string messageReceived;
        string from;
        SI32   port;

        MulticastReceiverSocket multicastReceiverSocket (multicastGroupIpAddress, multicastGroupPort);

        bool status = multicastReceiverSocket.receive (messageReceived, from, port);

        if (true == status)
        {
            WaveNs::trace (TRACE_LEVEL_SUCCESS, "LightHouseReceiverObjectManager::receiveMessageFromMulticastGroup : Received Message : " + messageReceived + ", from : " + from + ", port : " + port);
        }
        else
        {
            WaveNs::trace (TRACE_LEVEL_ERROR, "LightHouseReceiverObjectManager::receiveMessageFromMulticastGroup : Failed.");
        }
    }

    return (0);
}

UI32 LightHouseReceiverObjectManager::clientDatagramTest (UI32 argc, vector<string> argv)
{
    if (argc >= 4)
    {
        string remoteIpAddress = argv[1];
        SI32   remotePort      = atoi (argv[2].c_str ());
        string messageToSend   = argv[3];

        ClientDatagramSocket clientDatagramSocket (remoteIpAddress, remotePort);

        bool isConnected = clientDatagramSocket.connect ();

        if (true != isConnected)
        {
            WaveNs::trace (TRACE_LEVEL_ERROR, "LightHouseReceiverObjectManager::clientDatagramTest : Failed to connect.");
        }
        else
        {
            bool isSuccessful = clientDatagramSocket.send (messageToSend);

            if (true == isSuccessful)
            {
                WaveNs::trace (TRACE_LEVEL_SUCCESS, "LightHouseReceiverObjectManager::clientDatagramTest : Successfully sent.");
            }
            else
            {
                WaveNs::trace (TRACE_LEVEL_ERROR, "LightHouseReceiverObjectManager::clientDatagramTest : Failed to send.");
            }
        }
    }

    return (0);
}

UI32 LightHouseReceiverObjectManager::serverDatagramTest (UI32 argc, vector<string> argv)
{
    if (argc >= 2)
    {
        SI32 localPort = atoi (argv[1].c_str ());

        ServerDatagramSocket serverDatagramSocket (localPort);

        bool isAccepted = serverDatagramSocket.accept ();

        if (true != isAccepted)
        {
            WaveNs::trace (TRACE_LEVEL_ERROR, "LightHouseReceiverObjectManager::serverDatagramTest : Failed to accept.");
        }
        else
        {
            while (true)
            {
                string messageReceived;

                bool isSuccessful = serverDatagramSocket.receive (messageReceived);

                if (true == isSuccessful)
                {
                    WaveNs::trace (TRACE_LEVEL_SUCCESS, "LightHouseReceiverObjectManager::serverDatagramTest : Successfully received : " + messageReceived);
                }
                else
                {
                    WaveNs::trace (TRACE_LEVEL_ERROR, "LightHouseReceiverObjectManager::serverDatagramTest : Failed to receive.");
                }
            }
        }
    }

    return (0);
}

}
