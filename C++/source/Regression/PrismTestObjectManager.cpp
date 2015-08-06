/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Regression/PrismTestObjectManager.h"
#include "Regression/RegressionTestObjectManager.h"

namespace WaveNs
{

PrismTestObjectManager::PrismTestObjectManager (const string &prismTestObjectManagerName, const UI32 &stackSize, const vector<UI32> *pCpuAffinityVector)
    : WaveLocalObjectManager (prismTestObjectManagerName, stackSize, pCpuAffinityVector)
{
    addOperationMap (WAVE_OBJECT_MANAGER_TEST,                   reinterpret_cast<WaveMessageHandler> (&PrismTestObjectManager::testRequestHandler));
    addOperationMap (WAVE_OBJECT_MANAGER_PREPARE_FOR_REGRESSION, reinterpret_cast<WaveMessageHandler> (&PrismTestObjectManager::prepareForRegressionRequestHandler));
    addOperationMap (WAVE_OBJECT_MANAGER_PREPARE_FOR_REGRESSION2, reinterpret_cast<WaveMessageHandler> (&PrismTestObjectManager::prepareForRegressionRequestHandler2));

    RegressionTestObjectManager::addToRegressionShell (getServiceId (), true);
}

void PrismTestObjectManager::prepareForRegressionRequestHandler (RegressionPrepareMessage *pMessage)
{
    trace (TRACE_LEVEL_INFO, "PrismTestObjectManager::prepareForRegressionRequestHandler : Entering ...");

    m_regressionInput = pMessage->getInputStrings ();
    pMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    reply (pMessage);
}

void PrismTestObjectManager::prepareForRegressionRequestHandler2 (RegressionPrepareMessage2 *pMessage)
{
    trace (TRACE_LEVEL_INFO, "PrismTestObjectManager::prepareForRegressionRequestHandler2 : Entering ...");

    UI32             argIndex;
    vector<string>   inputParameters;

    inputParameters = pMessage->getInputStrings();
    for (argIndex = 0; argIndex < (UI32) inputParameters.size() ; )
    {
        if ('-' == inputParameters[argIndex].at(0))
        {
            inputParameters[argIndex].erase( inputParameters[argIndex].begin() );
            m_testParameters[ inputParameters[argIndex] ] = inputParameters[argIndex + 1];
            argIndex += 2;
        }
        else
        {
            trace (TRACE_LEVEL_DEVEL, "PrismTestObjectManager::prepareForRegressionRequestHandler2 : Skipping input '" + inputParameters[argIndex] + "'.  Expecting Key prefixed with '-'.");
            argIndex++;
        }
    }

    pMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    reply (pMessage);
}

WaveMessage *PrismTestObjectManager::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case WAVE_OBJECT_MANAGER_TEST :
            pWaveMessage = new RegressionTestMessage;
            break;

        case WAVE_OBJECT_MANAGER_PREPARE_FOR_REGRESSION :
            pWaveMessage = new RegressionPrepareMessage;
            break;

        case WAVE_OBJECT_MANAGER_PREPARE_FOR_REGRESSION2 :
            pWaveMessage = new RegressionPrepareMessage2;
            break;

        default :
            pWaveMessage = NULL;
    }

    return (pWaveMessage);
}

string PrismTestObjectManager::getTestParameterValue (const string &inputStringKey)
{
    map<string,string>::iterator iter;
    iter = m_testParameters.find(inputStringKey);
    string returnString;

    if (m_testParameters.end() != iter)
    {
        returnString = iter->second;
    }
    else
    {   
        returnString = "";
    }
    
    return (returnString);
}

}
