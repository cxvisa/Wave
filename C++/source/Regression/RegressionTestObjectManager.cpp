/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Regression/RegressionTestObjectManager.h"
#include "Regression/RegressionTestMessage.h"
#include "Regression/RegressionServiceMessages.h"
#include "Regression/RegressionPrepareMessage2.h"
#include "Regression/RegressionTestTypes.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Core/Test/FrameworkCoreTestObjectManager.h"
#include "Framework/Messaging/Local/Test/FrameworkLocalMessagingTestObjectManager.h"
#include "Framework/Messaging/Local/Test/FrameworkLocalMessagingTestObjectManager2.h"
#include "Framework/Messaging/Remote/Test/FrameworkRemoteMessagingTestObjectManager.h"
#include "Framework/Messaging/Remote/Test/FrameworkRemoteMessagingTestObjectManager2.h"
#include "Framework/Trace/Test/TraceTestObjectManager.h"
#include "Cluster/Test/ClusterTestObjectManager.h"
#include "Framework/Timer/Test/TimerTestObjectManager.h"

namespace WaveNs
{

UI32 messageCount = 0;

RegressionTestObjectManager::RegressionTestObjectManager ()
    : WaveLocalObjectManager (getServiceName ())
{
    addOperationMap (REGRESSION_GET_TEST_SERVICE_ENTRIES,   reinterpret_cast<WaveMessageHandler> (&RegressionTestObjectManager::getTestServiceEntriesMessageHandler));
    addOperationMap (REGRESSION_SET_TEST_SERVICE_STATE,     reinterpret_cast<WaveMessageHandler> (&RegressionTestObjectManager::setTestServiceStateMessageHandler));
    addOperationMap (REGRESSION_START_REGRESSION,           reinterpret_cast<WaveMessageHandler> (&RegressionTestObjectManager::startRegressionMessageHandler));
    addOperationMap (REGRESSION_PREPARE_TEST_FOR_A_SERVICE, reinterpret_cast<WaveMessageHandler> (&RegressionTestObjectManager::prepareAServiceTestMessageHandler));
    addOperationMap (REGRESSION_RUN_TEST_FOR_A_SERVICE,     reinterpret_cast<WaveMessageHandler> (&RegressionTestObjectManager::runAServiceTestMessageHandler));
}

RegressionTestObjectManager *RegressionTestObjectManager::getInstance ()
{
    static RegressionTestObjectManager *pRegressionTestObjectManager = new RegressionTestObjectManager ();

    WaveNs::waveAssert (NULL != pRegressionTestObjectManager, __FILE__, __LINE__);

    return (pRegressionTestObjectManager);
}

WaveServiceId RegressionTestObjectManager::getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

string RegressionTestObjectManager::getServiceName ()
{
    return ("Regression");
}

WaveMessage *RegressionTestObjectManager::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case REGRESSION_GET_TEST_SERVICE_ENTRIES :
            pWaveMessage = new RegressionTestObjectManagerGetTestServiceEntriesMessage;
            break;

        case REGRESSION_SET_TEST_SERVICE_STATE :
            pWaveMessage = new RegressionTestObjectManagerSetTestServiceStateMessage;
            break;

        case REGRESSION_START_REGRESSION :
            pWaveMessage = new RegressionTestObjectManagerStartRegressionMessage;
            break;

        case REGRESSION_PREPARE_TEST_FOR_A_SERVICE :
            pWaveMessage = new RegressionTestObjectManagerPrepareTestForAServiceMessage;
            break;

        case REGRESSION_RUN_TEST_FOR_A_SERVICE :
            pWaveMessage = new RegressionTestObjectManagerRunTestForAServiceMessage;
            break;

        default :
            pWaveMessage = NULL;
    }

    return (pWaveMessage);
}

void RegressionTestObjectManager::getTestServiceEntriesMessageHandler (RegressionTestObjectManagerGetTestServiceEntriesMessage *pMessage)
{
    UI32 numberOfTestServices  = m_testServiceEntries.size ();
    UI32 i;

    for (i = 0; i < numberOfTestServices; i++)
    {
        pMessage->addTestServiceEntry (m_testServiceEntries[i].getTestServiceId (), m_testServiceEntries[i].getIsTestEnabled ());
    }

    pMessage->setNumberOfTestServiceEntries (numberOfTestServices);

    pMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);

    reply (pMessage);
}

void RegressionTestObjectManager::setTestServiceStateMessageHandler (RegressionTestObjectManagerSetTestServiceStateMessage *pMessage)
{
    UI32         numberOfTestServices = m_testServiceEntries.size ();
    WaveServiceId testServiceId        = pMessage->getTestServiceId ();
    bool         isTestServiceEnabled = pMessage->getIsTestEnabled ();
    UI32         i;
    bool         foundTestService     = false;

    for (i = 0; i < numberOfTestServices; i++)
    {
        WaveServiceId tempTestServiceId = m_testServiceEntries[i].getTestServiceId ();

        if (testServiceId == tempTestServiceId)
        {
            m_testServiceEntries[i].setIsTestEnabled (isTestServiceEnabled);

            foundTestService = true;
            break;
        }
    }

    if (false == foundTestService)
    {
        pMessage->setCompletionStatus (REGRESSION_TEST_ERROR_INVALID_TEST_SERVICE_ID);
    }
    else
    {
        pMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    }

    reply (pMessage);
}

void RegressionTestObjectManager::startRegressionMessageHandler (RegressionTestObjectManagerStartRegressionMessage *pMessage)
{
    UI32 numberOfTestServices         = m_testServiceEntries.size ();
    UI32 numberOfTimesToRunRegression = pMessage->getNumberOfTimesToRunRegression ();
    UI32 i, j;

    for (j = 0; j < numberOfTimesToRunRegression; j++)
    {
        trace (TRACE_LEVEL_INFO, "");
        trace (TRACE_LEVEL_INFO, "");
        trace (TRACE_LEVEL_INFO, string ("Running Regression Iteration : ") + (j + 1));
        trace (TRACE_LEVEL_INFO, "");
        trace (TRACE_LEVEL_INFO, "");

        for (i = 0; i < numberOfTestServices; i++)
        {
            WaveServiceId testServiceId = m_testServiceEntries[i].getTestServiceId ();
            bool         isTestEnabled = m_testServiceEntries[i].getIsTestEnabled ();

            if (true == isTestEnabled)
            {
                RegressionTestMessage message (testServiceId);
                WaveMessageStatus      status;

                status = sendSynchronously (&message);

                if (WAVE_MESSAGE_SUCCESS != status)
                {
                    trace (TRACE_LEVEL_ERROR, "");
                    trace (TRACE_LEVEL_ERROR, string ("Test FAILED    for Service (") + FrameworkToolKit::getServiceNameById (testServiceId) + ").");
                    trace (TRACE_LEVEL_ERROR, "");
                }
                else
                {
                    ResourceId completionStatus = message.getCompletionStatus ();

                    if (WAVE_MESSAGE_SUCCESS != completionStatus)
                    {
                        trace (TRACE_LEVEL_ERROR, "");
                        trace (TRACE_LEVEL_ERROR, string ("Test FAILED    for Service (") + FrameworkToolKit::getServiceNameById (testServiceId) + ").");
                        trace (TRACE_LEVEL_ERROR, "");
                    }
                    else
                    {
                        trace (TRACE_LEVEL_SUCCESS, "");
                        trace (TRACE_LEVEL_SUCCESS, string ("Test SUCCEEDED for Service (") + FrameworkToolKit::getServiceNameById (testServiceId) + ").");
                        trace (TRACE_LEVEL_SUCCESS, "");
                    }
                }
            }
            else
            {
                trace (TRACE_LEVEL_WARN, "");
                trace (TRACE_LEVEL_WARN, string ("Test DISABLED for Service (") + FrameworkToolKit::getServiceNameById (testServiceId) + ").");
                trace (TRACE_LEVEL_WARN, "");
            }
        }
    }

    pMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    reply (pMessage);
}

void RegressionTestObjectManager::prepareAServiceTestMessageHandler (RegressionTestObjectManagerPrepareTestForAServiceMessage *pMessage)
{
    WaveServiceId serviceCode                 = pMessage->getServiceCode ();
    ResourceId     completionStatus            = WAVE_MESSAGE_SUCCESS;
    vector<string> inputStrings;
    UI32           argIndex;

    RegressionPrepareMessage2 message (serviceCode);
    WaveMessageStatus     status;

    inputStrings = pMessage->getInputStrings();    

    for (argIndex = 0; argIndex < (UI32) inputStrings.size(); argIndex++)
    {
        message.addInputString(inputStrings[argIndex]);
    }  

    status = sendSynchronously (&message);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, "");
        trace (TRACE_LEVEL_ERROR, string ("Prepare FAILED    for Service (") + FrameworkToolKit::getServiceNameById (serviceCode) + ").");
        trace (TRACE_LEVEL_ERROR, "");

        completionStatus = status;
    }
    else
    {
        completionStatus = message.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != completionStatus)
        {
            trace (TRACE_LEVEL_ERROR, "");
            trace (TRACE_LEVEL_ERROR, string ("Prepare FAILED    for Service (") + FrameworkToolKit::getServiceNameById (serviceCode) + ").");
            trace (TRACE_LEVEL_ERROR, "");
        }
        else
        {  
            trace (TRACE_LEVEL_SUCCESS, "");
            trace (TRACE_LEVEL_SUCCESS, string ("Prepare SUCCEEDED for Service (") + FrameworkToolKit::getServiceNameById (serviceCode) + ").");
            trace (TRACE_LEVEL_SUCCESS, "");
        }
    }

    pMessage->setCompletionStatus (completionStatus);
    reply (pMessage);
}

void RegressionTestObjectManager::runAServiceTestMessageHandler (RegressionTestObjectManagerRunTestForAServiceMessage *pMessage)
{
    WaveServiceId serviceCode                 = pMessage->getServiceCode ();
    UI32         numberOfTimesToRunServiceTest = pMessage->getNumberOfTimesToRunServiceTest ();
    UI32         i                             = 0;
    ResourceId   completionStatus              = WAVE_MESSAGE_SUCCESS;

    for (i = 0; i < numberOfTimesToRunServiceTest; i++)
    {
        trace (TRACE_LEVEL_INFO, "");
        trace (TRACE_LEVEL_INFO, "");
        trace (TRACE_LEVEL_INFO, string ("Running Service Test Iteration : ") + (i + 1));
        cout << "Running Service Test Iteration : " <<  (i + 1) << endl;
        trace (TRACE_LEVEL_INFO, "");
        trace (TRACE_LEVEL_INFO, "");

        RegressionTestMessage message (serviceCode);
        WaveMessageStatus     status;

        status = sendSynchronously (&message);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "");
            trace (TRACE_LEVEL_ERROR, string ("Test FAILED    for Service (") + FrameworkToolKit::getServiceNameById (serviceCode) + ").");
            trace (TRACE_LEVEL_ERROR, "");

            completionStatus = status;
        }
        else
        {
            completionStatus = message.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != completionStatus)
            {
                trace (TRACE_LEVEL_ERROR, "");
                trace (TRACE_LEVEL_ERROR, string ("Test FAILED    for Service (") + FrameworkToolKit::getServiceNameById (serviceCode) + ").");
                trace (TRACE_LEVEL_ERROR, "");
            }
            else
            {
                trace (TRACE_LEVEL_SUCCESS, "");
                trace (TRACE_LEVEL_SUCCESS, string ("Test SUCCEEDED for Service (") + FrameworkToolKit::getServiceNameById (serviceCode) + ").");
                trace (TRACE_LEVEL_SUCCESS, "");
            }
        }
    }

    pMessage->setCompletionStatus (completionStatus);
    reply (pMessage);
}

void RegressionTestObjectManager::addToRegressionShell (const WaveServiceId &waveServiceId, const bool &isEnabledByDefault)
{
    (getInstance ())->m_testServiceEntries.push_back (RegressionTestEntry (waveServiceId, isEnabledByDefault));
}

}
