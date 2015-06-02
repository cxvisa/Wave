/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "SystemManagement/CommandLineInterface/Server/CommandLineInterfaceReceiverWorkerThread.h"
#include "SystemManagement/WaveSystemManagementGatewayMessage.h"

namespace WaveNs
{

WaveCommandLineInterfaceOperationStatus CommandLineInterfaceReceiverWorkerThread::processWriteRequests (vector<string> inputString, string &errorString, bool isWyserEaCompatibilityMode)
{
    WaveCommandLineInterfaceOperationStatus retStatus = WAVE_CLI_OPERATION_SUCCESS;

    // Only one line of input comes in as a write request, so we check for the size of the vector and get the first element 
    // as the input
    UI32    inputStringSize = inputString.size ();
    string  targetNodeName = "";
    string  subMode = "";

    if (inputStringSize == 2)
    {
        subMode = inputString[0];
        targetNodeName = inputString[1];
    }
        
    if (targetNodeName == "" && subMode == "")
    {
        retStatus = WAVE_CLI_OPERATION_ERROR;
        return (retStatus);
    }
        
    /* Send a message to Wyser GW for processing the request
     */ 
    
    WaveSystemManagementGatewayMessage *pWaveSystemManagementGatewayMessage = new WaveSystemManagementGatewayMessage ();

    pWaveSystemManagementGatewayMessage->setWriteInputArguments (targetNodeName);
    pWaveSystemManagementGatewayMessage->setWriteSubMode (subMode);
    pWaveSystemManagementGatewayMessage->setIsWyserEaCompatibilityMode(isWyserEaCompatibilityMode);

    ResourceId status = sendSynchronously (pWaveSystemManagementGatewayMessage);

    if (WAVE_MESSAGE_SUCCESS == status)
    {   
        status = pWaveSystemManagementGatewayMessage->getCompletionStatus (); 

        if (WAVE_MESSAGE_SUCCESS == status)
        {   
            trace (TRACE_LEVEL_DEBUG, "CommandLineInterfaceReceiverWorkerThread::processWriteRequests : Message Processing Success");
            retStatus = WAVE_CLI_OPERATION_SUCCESS;
        }   
        else
        {
        	errorString = pWaveSystemManagementGatewayMessage->getCommandErrorString();
            trace (TRACE_LEVEL_ERROR, "CommandLineInterfaceReceiverWorkerThread::processWriteRequests : Message Processing FAILURE");
            retStatus = WAVE_CLI_OPERATION_ERROR;
        }
    }   
    else
    {   
        trace (TRACE_LEVEL_ERROR, "CommandLineInterfaceReceiverWorkerThread::processWriteRequests : Message Failure");
        retStatus = WAVE_CLI_OPERATION_ERROR;
    }   

    delete pWaveSystemManagementGatewayMessage;

    return (retStatus);
}


}
