/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/LightHouse/Test/LightHouseTestObjectManager1.h"
#include "Regression/RegressionTestMessage.h"
#include "Framework/Messaging/LightHouse/Test/LightHouseTestContext.h"
#include "Framework/Messaging/LightHouse/Test/LightHouseTestLightPulse1.h"
#include "Framework/Utils/StringUtils.h"
#include "Shell/ShellDebug.h"
#include "Shell/ShellBase.h"
#include "Framework/Utils/ClientDatagramSocket.h"
#include "Framework/Utils/ServerDatagramSocket.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Messaging/LightHouse/Test/DatagramSocketReaderThread.h"

namespace WaveNs
{

LightHouseTestObjectManager1::LightHouseTestObjectManager1 ()
    : WaveTestObjectManager (getServiceName ())
{

    addDebugFunction ((ShellCmdFunction) (&LightHouseTestObjectManager1::clientDatagramTest),               "clientDatagramTest");
    addDebugFunction ((ShellCmdFunction) (&LightHouseTestObjectManager1::serverDatagramTest),               "serverDatagramTest");

    addDebugFunction ((ShellCmdFunction) (&LightHouseTestObjectManager1::secureClientDatagramTest),         "secureClientDatagramTest");
    addDebugFunction ((ShellCmdFunction) (&LightHouseTestObjectManager1::secureServerDatagramTest),         "secureServerDatagramTest");
}

LightHouseTestObjectManager1::~LightHouseTestObjectManager1 ()
{
}

string LightHouseTestObjectManager1::getServiceName ()
{
    return ("Light House Test 1");
}

LightHouseTestObjectManager1 *LightHouseTestObjectManager1::getInstance ()
{
    static LightHouseTestObjectManager1 *pLightHouseTestObjectManager1 = new LightHouseTestObjectManager1 ();

    WaveNs::waveAssert (NULL != pLightHouseTestObjectManager1, __FILE__, __LINE__);

    return (pLightHouseTestObjectManager1);
}

WaveServiceId LightHouseTestObjectManager1::getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

void LightHouseTestObjectManager1::testRequestHandler (RegressionTestMessage *pRegressionTestMessage)
{
    trace (TRACE_LEVEL_DEVEL, "LightHouseTestObjectManager1::testRequestHandler : Entering ...");

    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&LightHouseTestObjectManager1::broadcastTestLightPulse1TestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&LightHouseTestObjectManager1::waveLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&LightHouseTestObjectManager1::waveLinearSequencerFailedStep),
    };

    LightHouseTestContext *pLightHouseTestContext = new LightHouseTestContext (pRegressionTestMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pLightHouseTestContext->start ();
}

void LightHouseTestObjectManager1::broadcastTestLightPulse1TestStep (LightHouseTestContext *pLightHouseTestContext)
{
    trace (TRACE_LEVEL_DEVEL, "LightHouseTestObjectManager1::broadcastTestLightPulse1TestStep : Entering ...");

    static const UI32 numberOfLightPulsesToBeBroadcast = 1000;
    static       UI32 currentCounter                   = 0;
          UI32 i                                = 0;

    for (i = 0; i < numberOfLightPulsesToBeBroadcast; i++)
    {
        LightHouseTestLightPulse1 *pLightHouseTestLightPulse1 = new LightHouseTestLightPulse1 ();

        waveAssert (NULL != pLightHouseTestLightPulse1, __FILE__, __LINE__);

        pLightHouseTestLightPulse1->setLightMessage (string ("Light Message : ") + currentCounter++);

        broadcastLightPulse (pLightHouseTestLightPulse1);
    }

    pLightHouseTestContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

UI32 LightHouseTestObjectManager1::clientDatagramTest (UI32 argc, vector<string> argv)
{
    if (argc >= 6)
    {
        string remoteIpAddress           = argv[1];
        SI32   remotePort                = atoi (argv[2].c_str ());
        string messageToSend             = argv[3];
        SI32   numberOfClients           = atoi (argv[4].c_str ());
        SI32   numberOfMessagesPerClient = atoi (argv[5].c_str ());

        for (int i = 0; i < numberOfClients; i++)
        {
            ClientDatagramSocket clientDatagramSocket (remoteIpAddress, remotePort);

            bool isConnected = clientDatagramSocket.connect ();

            if (true != isConnected)
            {
                WaveNs::trace (TRACE_LEVEL_ERROR, "LightHouseTestObjectManager1::clientDatagramTest : Failed to connect.");
            }
            else
            {
                for (int j = 0; j < numberOfMessagesPerClient; j++)
                {
                    bool isSuccessful = clientDatagramSocket.send (messageToSend);

                    if (true == isSuccessful)
                    {
                        WaveNs::trace (TRACE_LEVEL_DEBUG, "LightHouseTestObjectManager1::clientDatagramTest : Successfully sent.");
                    }
                    else
                    {
                        WaveNs::trace (TRACE_LEVEL_ERROR, "LightHouseTestObjectManager1::clientDatagramTest : Failed to send.");
                    }
                }
            }
        }
    }

    return (0);
}

UI32 LightHouseTestObjectManager1::serverDatagramTest (UI32 argc, vector<string> argv)
{
    if (argc >= 2)
    {
        SI32 localPort = atoi (argv[1].c_str ());

        while (true)
        {
            ServerDatagramSocket *pServerDatagramSocket = new ServerDatagramSocket (localPort);

            bool isConnected = pServerDatagramSocket->connect ();

            if (true != isConnected)
            {
                WaveNs::trace (TRACE_LEVEL_ERROR, "LightHouseTestObjectManager1::serverDatagramTest : Failed to connect.");
            }
            else
            {
                DatagramSocketReaderThread *pDatagramSocketReaderThread = new DatagramSocketReaderThread (pServerDatagramSocket);

                pDatagramSocketReaderThread->run ();
            }
        }
    }

    return (0);
}

UI32 LightHouseTestObjectManager1::secureClientDatagramTest (UI32 argc, vector<string> argv)
{
    if (argc >= 6)
    {
        string remoteIpAddress           = argv[1];
        SI32   remotePort                = atoi (argv[2].c_str ());
        string messageToSend             = argv[3];
        SI32   numberOfClients           = atoi (argv[4].c_str ());
        SI32   numberOfMessagesPerClient = atoi (argv[5].c_str ());

        for (int i = 0; i < numberOfClients; i++)
        {
            ClientDatagramSocket clientDatagramSocket (remoteIpAddress, remotePort);

            clientDatagramSocket.enableSecurity ();

            bool isConnected = clientDatagramSocket.connect ();

            if (true != isConnected)
            {
                WaveNs::trace (TRACE_LEVEL_ERROR, "LightHouseTestObjectManager1::secureClientDatagramTest : Failed to connect.");
            }
            else
            {
                for (int j = 0; j < numberOfMessagesPerClient; j++)
                {
                    bool isSuccessful = clientDatagramSocket.send (messageToSend);

                    if (true == isSuccessful)
                    {
                        WaveNs::trace (TRACE_LEVEL_DEBUG, "LightHouseTestObjectManager1::secureClientDatagramTest : Successfully sent.");
                    }
                    else
                    {
                        WaveNs::trace (TRACE_LEVEL_ERROR, "LightHouseTestObjectManager1::secureClientDatagramTest : Failed to send.");
                    }
                }
            }
        }
    }

    return (0);
}

UI32 LightHouseTestObjectManager1::secureServerDatagramTest (UI32 argc, vector<string> argv)
{
    if (argc >= 2)
    {
        SI32 localPort = atoi (argv[1].c_str ());

        while (true)
        {
            ServerDatagramSocket *pServerDatagramSocket = new ServerDatagramSocket (localPort);

            pServerDatagramSocket->enableSecurity ();

            bool isConnected = pServerDatagramSocket->connect ();

            if (true != isConnected)
            {
                WaveNs::trace (TRACE_LEVEL_ERROR, "LightHouseTestObjectManager1::secureServerDatagramTest : Failed to connect.");

                delete pServerDatagramSocket;
            }
            else
            {
                DatagramSocketReaderThread *pDatagramSocketReaderThread = new DatagramSocketReaderThread (pServerDatagramSocket);

                pDatagramSocketReaderThread->run ();
            }
        }
    }

    return (0);
}

}
