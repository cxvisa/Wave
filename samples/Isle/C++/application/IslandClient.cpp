/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/Wave.h"
#include "IsleClientInterface/IsleClientSynchronousConnection.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "Shell/WaveCliShell.h"
#include "IsleShell/IsleCliDebugShell.h"
#include "ManagementInterface/ClientInterface/WaveUserInterfaceObjectManager.h"
#include "ManagementInterface/ClientInterface/Test/ManagementInterfaceClientTestMessages.h"
#include "ManagementInterface/ClientInterface/Test/ManagementInterfaceClientTestTypes.h"
#include "ManagementInterface/ClientInterface/WaveClientReceiverObjectManager.h"
#include "Framework/../../application/WaveCliReplyThread.h"

#include <iostream>
#include <strings.h>

using namespace std;
using namespace WaveNs;
using namespace IsleNs;

extern "C" int isleClientMain (const char * const pProgramName, const int clientPort);

void displayUsage (const char *pProgramName)
{
    cout << "USAGE:" << endl;
    cout << pProgramName << " [-serverip <Server IP Address>] [-serverport <Server TCP/IP Port Number>]" << endl;
    cout << endl;
    cout << endl;
    cout << "Command Line Options:" << endl;
    cout << endl;
    cout << "    -serverip   : Server IP Address         - The IP Address where Island is running" << endl;
    cout << endl;
    cout << "    -serverport : Server TCP/IP Port Number - Management port number of Island instance to connect to" << endl;
    cout << endl;
}

ManagementInterfaceMessage *clientManagementInterfaceMessageInstantiator (const UI32 &operationCode)
{
    ManagementInterfaceMessage *pManagementInterfaceMessage = NULL;

    // trace (TRACE_LEVEL_DEBUG, string ("clientManagementInterfaceMessageInstantiator : op=") + operationCode);

    switch (operationCode)
    {
        case 0:
            pManagementInterfaceMessage = new ManagementInterfaceClientTestMessage1 ();
            break;

        case 1:
            pManagementInterfaceMessage = new ManagementInterfaceClientTestMessage2 ();
            break;

        case 2:
            pManagementInterfaceMessage = new ManagementInterfaceClientTestMessage3 ();
            break;

        case 3:
            pManagementInterfaceMessage = new ManagementInterfaceClientTestMessage4 ();
            break;
        default:
            trace (TRACE_LEVEL_ERROR, string ("clientManagementInterfaceMessageInstantiator : Unknown Operation Code : ") + operationCode);
            pManagementInterfaceMessage = NULL;
    }

    return (pManagementInterfaceMessage);
}

ResourceId clientManagementInterfaceMessageHandler (ManagementInterfaceMessage *pManagementInterfaceMessage)
{
    static UI32 managementInterfaceMessageCounter = 0;
           UI32 operationCode;

    managementInterfaceMessageCounter++;

    if (0 == managementInterfaceMessageCounter % 1000)
    {
        trace (TRACE_LEVEL_INFO, string ("Number of Management Interface Messages Received so far from the server : ") + managementInterfaceMessageCounter);
    }

    operationCode = pManagementInterfaceMessage->getOperationCode ();

    if (2 == operationCode)
    {
        WaveCliReplyThread *pWaveCliReplyThread = new WaveCliReplyThread (pManagementInterfaceMessage);

        WaveThreadStatus status = pWaveCliReplyThread->run ();

        if (WAVE_THREAD_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "clientManagementInterfaceMessageHandler : A new thread COULD NOT BE CREATED to start the action");
            delete pWaveCliReplyThread;
            return (WAVE_MESSAGE_ERROR);
        }

        return (WAVE_MGMT_CLIENT_INTF_CLIENT_ASYNC_REPSONSE);

    } else if (3 == operationCode)
    {
	    ResourceId                             status;
        ManagementInterfaceClientTestMessage4 *pMessage = reinterpret_cast<ManagementInterfaceClientTestMessage4 *> (pManagementInterfaceMessage);

        if (true == (pMessage->validateInputBuffer1 ()))
        {
            status = WAVE_MESSAGE_SUCCESS;
        }
        else
        {
            status = WAVE_MESSAGE_ERROR;
        }

        if (true == (pMessage->validateInputLargeBuffer1 ()))
        {
            status = pMessage->getRequestedCompletionStatus ();
        }
        else
        {
            status = WAVE_MESSAGE_ERROR;
        }

        if (status == WAVE_MESSAGE_ERROR)
        {
            trace (TRACE_LEVEL_INFO, "clientManagementInterfaceMessageHandler : sendToClients test status = WAVE_MESSAGE_ERROR");

            return (status);
        }

        pMessage->setupOutputBuffer1 ();

        trace (TRACE_LEVEL_INFO, "clientManagementInterfaceMessageHandler : sendToClients test status = WAVE_MESSAGE_SUCCESS");

        return (WAVE_MESSAGE_SUCCESS);
    }
    else
    {
        return (WAVE_MESSAGE_SUCCESS);
    }
}

void *isleGetOutputForCStructure (ManagementInterfaceMessage *pManagementInterfaceMessage)
{
    return (NULL);
}


int main (int argc, char *argv[])
{
    string  serverIpAddress              = FrameworkToolKit::getAPublicIpAddressForThisMachine ();
    UI32    serverPort                   = 9110;
    UI32    i                            = 0;
    char    serverIpCharArray[64];
    string  clientIpAddress;
    char    clientIpCharArray[64];
    UI32    numberOfCommandLineArguments = (UI32) argc;
    SI32    clientPort                   = 9810;
    SI32    maxNumberOfRetries           = 15;
    string  command;
    string  ipAddress;
    SI32    instance                     = 0;
    string   clientName                  =  "WaveClient";

    for (i = 1; i < numberOfCommandLineArguments; i++)
    {
        if (0 == strcasecmp ("-serverip", argv[i]))
        {
            strcpy (serverIpCharArray, argv[i + 1]);
            serverIpAddress = serverIpCharArray;

            i++;
        }
        else if (0 == strcasecmp ("-serverport", argv[i]))
        {
            serverPort = atoi (argv[i + 1]);

            i++;
        }
        else if (0 == strcasecmp ("-clientip", argv[i]))
        {
            strcpy (clientIpCharArray, argv[i + 1]);
            clientIpAddress = clientIpCharArray;

            i++;
        }
        else if (0 == strcasecmp ("-clientport", argv[i]))
        {
            clientPort = atoi (argv[i + 1]);

            i++;
        }
        else if (0 == strcasecmp ("-connectionretries", argv[i]))
        {
            maxNumberOfRetries = atoi (argv[i + 1]);

            i++;
        }
        else if (0 == strcasecmp ("-instance", argv[i]))
        {
	    instance = atoi (argv[i + 1]);
            i++;
        }
        else if (0 == strcasecmp ("-clientname", argv[i]))
        {
            clientName = argv[i + 1];

            i++;
        }
        else
        {
            command += argv[i];
            command += " ";
        }
    }

    //WaveNs::trace (TRACE_LEVEL_DEVEL, string ("Instance for this Island Client : ") + instance);
    if (0 == instance)
    {
    } 

    WaveClientReceiverObjectManager::setAutoScanForAvailablePort (true);
    WaveUserInterfaceObjectManager::setManagementInterfaceMessageInstantiatorForClient (clientManagementInterfaceMessageInstantiator);
    WaveUserInterfaceObjectManager::setManagementInterfaceMessageHandlerForClient (clientManagementInterfaceMessageHandler);
    WaveUserInterfaceObjectManager::setClientHandlerToLoadOutputForCStructure     (isleGetOutputForCStructure);

    string isleclientName = clientName;

    isleClientMain (clientName.c_str (), clientPort);

    if (0 == clientIpAddress.size())
    {
        ipAddress = FrameworkToolKit::getAPublicIpAddressForThisMachine ();
    }
    else
    {
        ipAddress = clientIpAddress;
    }

    IsleClientSynchronousConnection connection                              (isleclientName, serverIpAddress, serverPort);
    WaveConnectionStatus           connectionstatus                      = WAVE_MGMT_CLIENT_INTF_CONNECTION_ESTABLISHED_TO_SERVER;
    UI32                           managementInterfaceClientReceiverPort = FrameworkToolKit::getManagementInterfaceClientReceiverPort ();
    string                         clientNameExtension                   = ipAddress + managementInterfaceClientReceiverPort;
    //ResourceId                     status;

    connectionstatus = connection.connect (clientNameExtension, maxNumberOfRetries);

    if (WAVE_MGMT_CLIENT_INTF_CONNECTION_ESTABLISHED_TO_SERVER == connectionstatus)
    {
        vector<string> tokens;

        WaveCliShell      *pWaveCliShell      = WaveCliShell::getInstance (connection);
        IsleCliDebugShell *pIsleCliDebugShell = new IsleCliDebugShell (connection);

        waveAssert (NULL != pWaveCliShell,      __FILE__, __LINE__);
        waveAssert (NULL != pIsleCliDebugShell, __FILE__, __LINE__);

        pWaveCliShell->addSubShell (pIsleCliDebugShell);

        // Subshells under IsleCliDebugShell have been moved to its constructor.
        // So, we don't need to edit this file when adding more subshells

        tokenize (command, tokens);

        pWaveCliShell->execute (tokens);

        delete pWaveCliShell;

        connection.close ();
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, "Could not establish connection to DCM Server.");

        return (1);
    }

    return (0);
}
