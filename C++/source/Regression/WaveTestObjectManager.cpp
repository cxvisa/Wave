/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Regression/WaveTestObjectManager.h"
#include "Regression/RegressionTestObjectManager.h"
#include "Modeling/JSON/ObjectModel/JsonFactory/JsonFactory.h"
#include "Framework/Messaging/MessageFactory/WaveMessageFactory.h"
#include "Modeling/JSON/ObjectModel/JsonValue.h"
#include "Modeling/JSON/ObjectModel/JsonNumber.h"
#include "Modeling/JSON/ObjectModel/JsonString.h"
#include "Modeling/JSON/ObjectModel/JsonObject.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Modeling/JSON/ObjectModel/JsonPair.h"

namespace WaveNs
{

WaveTestObjectManager::WaveTestObjectManager (const string &waveTestObjectManagerName, const UI32 &stackSize, const vector<UI32> *pCpuAffinityVector)
    : WaveLocalObjectManager (waveTestObjectManagerName, stackSize, pCpuAffinityVector)
{
    addOperationMap (WAVE_OBJECT_MANAGER_TEST,                    reinterpret_cast<WaveMessageHandler> (&WaveTestObjectManager::testRequestHandler));
    addOperationMap (WAVE_OBJECT_MANAGER_TEST_PATTERNS,           reinterpret_cast<WaveMessageHandler> (&WaveTestObjectManager::runTestPatternsHandler));
    addOperationMap (WAVE_OBJECT_MANAGER_PREPARE_FOR_REGRESSION,  reinterpret_cast<WaveMessageHandler> (&WaveTestObjectManager::prepareForRegressionRequestHandler));
    addOperationMap (WAVE_OBJECT_MANAGER_PREPARE_FOR_REGRESSION2, reinterpret_cast<WaveMessageHandler> (&WaveTestObjectManager::prepareForRegressionRequestHandler2));

    RegressionTestObjectManager::addToRegressionShell (getServiceId (), true);
}

void WaveTestObjectManager::prepareForRegressionRequestHandler (RegressionPrepareMessage *pMessage)
{
    trace (TRACE_LEVEL_INFO, "WaveTestObjectManager::prepareForRegressionRequestHandler : Entering ...");

    m_regressionInput = pMessage->getInputStrings ();
    pMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    reply (pMessage);
}

void WaveTestObjectManager::prepareForRegressionRequestHandler2 (RegressionPrepareMessage2 *pMessage)
{
    trace (TRACE_LEVEL_INFO, "WaveTestObjectManager::prepareForRegressionRequestHandler2 : Entering ...");

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
            trace (TRACE_LEVEL_DEVEL, "WaveTestObjectManager::prepareForRegressionRequestHandler2 : Skipping input '" + inputParameters[argIndex] + "'.  Expecting Key prefixed with '-'.");
            argIndex++;
        }
    }

    pMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    reply (pMessage);
}

WaveMessage *WaveTestObjectManager::createMessageInstance (const UI32 &operationCode)
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

string WaveTestObjectManager::getTestParameterValue (const string &inputStringKey)
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

void WaveTestObjectManager::runTestPatternsHandler (RegressionTestPatternsMessage *pMessage)
{
    trace (TRACE_LEVEL_DEVEL, "WaveTestObjectManager::runTestPatternsHandler : Entering ...");

    waveAssert (NULL != pMessage, __FILE__, __LINE__);

    string testPatterns = pMessage->getTestPatterns ();

    JsonValue *pJsonValue = JsonFactory::createJsonValueFromString (testPatterns);

    if (NULL == pJsonValue)
    {
        trace (TRACE_LEVEL_ERROR, "WaveTestObjectManager::runTestPatternsHandler : Could not parse input test patterns JSON.");

        pMessage->setCompletionStatus (WAVE_MESSAGE_ERROR);
        return;
    }

    JsonObject *pTestPatternsRoot = dynamic_cast<JsonObject *> (pJsonValue);

    if (NULL == pTestPatternsRoot)
    {
        trace (TRACE_LEVEL_ERROR, "WaveTestObjectManager::runTestPatternsHandler : Could not parse input test patterns JSON as Object");

        delete pJsonValue;

        pMessage->setCompletionStatus (WAVE_MESSAGE_ERROR);
        return;
    }

    vector<JsonPair *> testPatternJsons = pTestPatternsRoot->getJsonPairs ();

    const UI32       numberOfTestPatterns = testPatternJsons.size ();
          UI32       i                    = 0;

          ResourceId status               = WAVE_MESSAGE_SUCCESS;

    for (i = 0; i < numberOfTestPatterns; i++)
    {
        JsonPair *pTestPatternPair = testPatternJsons[i];

        waveAssert (NULL != pTestPatternPair, __FILE__, __LINE__);

        JsonValue *pJsonValueForTestPattern = pTestPatternPair->getPValue ();

        waveAssert (NULL != pJsonValueForTestPattern, __FILE__, __LINE__);

        JsonObject *pJsonObjectForTestPattern = dynamic_cast<JsonObject *> (pJsonValueForTestPattern);

        waveAssert (NULL != pJsonObjectForTestPattern, __FILE__, __LINE__);

        JsonValue *pJsonValueForServiceName = pJsonObjectForTestPattern->getValueForName ("service");

        waveAssert (NULL != pJsonValueForServiceName, __FILE__, __LINE__);

        JsonValue *pJsonValueForOperationCode = pJsonObjectForTestPattern->getValueForName ("operation");

        waveAssert (NULL != pJsonValueForOperationCode, __FILE__, __LINE__);

        JsonString *pJsonStringForServiceName = dynamic_cast<JsonString *> (pJsonValueForServiceName);

        waveAssert (NULL != pJsonStringForServiceName, __FILE__, __LINE__);

        JsonNumber *pJsonNumberForOperationcode = dynamic_cast<JsonNumber *> (pJsonValueForOperationCode);

        waveAssert (NULL != pJsonNumberForOperationcode, __FILE__, __LINE__);

        const string serviceName   = pJsonStringForServiceName->getString ();
        const UI32   serviceId     = FrameworkToolKit::getServiceIdByName (serviceName);
        const UI32   operationCode = (UI32) ((pJsonNumberForOperationcode->getNumber ()).getLd ());

        WaveMessage *pWaveMessage = WaveMessageFactory::getMessageInstance (serviceId, operationCode);

        waveAssert (NULL != pWaveMessage, __FILE__, __LINE__);

        JsonValue *pJsonValueForInputTestPattern = pJsonObjectForTestPattern->getValueForName ("testPattern");

        waveAssert (NULL != pJsonValueForInputTestPattern, __FILE__, __LINE__);

        JsonObject *pJsonObjectForInputTestPattern = dynamic_cast<JsonObject *> (pJsonValueForInputTestPattern);

        waveAssert (NULL != pJsonObjectForInputTestPattern, __FILE__, __LINE__);

        pWaveMessage->loadFromJsonObject (pJsonObjectForInputTestPattern);

        status = sendSynchronously (pWaveMessage);

        if (WAVE_MESSAGE_SUCCESS == status)
        {
            status = pWaveMessage->getCompletionStatus ();
        }

        delete pWaveMessage;

        JsonValue  *pJsonValueForExpectedStatus     = pJsonObjectForTestPattern->getValueForName ("expectedStatus");
        JsonString *pJsonStringForExpectedStatus    = NULL;
        string      expectedStatusResourceIdString;

        if (NULL != pJsonValueForExpectedStatus)
        {
            pJsonStringForExpectedStatus = dynamic_cast<JsonString *> (pJsonValueForExpectedStatus);

            waveAssert (NULL != pJsonStringForExpectedStatus, __FILE__, __LINE__);

            expectedStatusResourceIdString = pJsonStringForExpectedStatus->getString ();
        }
        else
        {
            expectedStatusResourceIdString = "WAVE_MESSAGE_SUCCESS";
        }

        ResourceId expectedStatus = FrameworkToolKit::localizeToSourceCodeResourceId (expectedStatusResourceIdString);

        if (expectedStatus != status)
        {
            const string actualStatusResourceIdString = FrameworkToolKit::localizeToSourceCodeEnum (status);

            tracePrintf (TRACE_LEVEL_ERROR, true, false, "WaveTestObjectManager::runTestPatternsHandler : Test Pattern processing failed.  Expected : %s.  Got : %s", expectedStatusResourceIdString.c_str (), actualStatusResourceIdString.c_str ());

            break;
        }
        else
        {
            status = WAVE_MESSAGE_SUCCESS;
        }
    }

    delete pJsonValue;

    pMessage->setCompletionStatus (status);

    reply (pMessage);

    return;
}

}
