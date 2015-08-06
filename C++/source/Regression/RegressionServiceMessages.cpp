/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Regression/RegressionServiceMessages.h"
#include "Regression/RegressionTestTypes.h"
#include "Regression/RegressionTestObjectManager.h"
#include "Framework/Utils/AssertUtils.h"

namespace WaveNs
{

RegressionTestObjectManagerGetTestServiceEntriesMessage::RegressionTestObjectManagerGetTestServiceEntriesMessage ()
    : ManagementInterfaceMessage (RegressionTestObjectManager::getServiceName (), REGRESSION_GET_TEST_SERVICE_ENTRIES),
      m_numberOfTestServiceEntries (0)
{
}

RegressionTestObjectManagerGetTestServiceEntriesMessage::~RegressionTestObjectManagerGetTestServiceEntriesMessage ()
{
}

void RegressionTestObjectManagerGetTestServiceEntriesMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeUI32 (&m_numberOfTestServiceEntries,    "numberOfTestServiceEntries"));
     addSerializableAttribute (new AttributeUI32Vector (&m_testServiceIds,          "testServiceIds"));
     addSerializableAttribute (new AttributeBoolVector (&m_testServiceStates,       "testServiceStates"));
}

void RegressionTestObjectManagerGetTestServiceEntriesMessage::setNumberOfTestServiceEntries (UI32 numberOfTestServiceEntries)
{
    m_numberOfTestServiceEntries = numberOfTestServiceEntries;
}

void RegressionTestObjectManagerGetTestServiceEntriesMessage::addTestServiceEntry (const WaveServiceId &prismServiceId, const bool &isServiceEnabled)
{
    m_testServiceIds.push_back (prismServiceId);
    m_testServiceStates.push_back (isServiceEnabled);
}

UI32 RegressionTestObjectManagerGetTestServiceEntriesMessage::getNumberOfTestServiceEntries ()
{
    return (m_numberOfTestServiceEntries);
}

RegressionTestEntry RegressionTestObjectManagerGetTestServiceEntriesMessage::getTestServiceEntryAt (UI32 index)
{
    if (index < m_numberOfTestServiceEntries)
    {
        prismAssert ((m_testServiceIds.size ()) > index, __FILE__, __LINE__);
        prismAssert ((m_testServiceStates.size ()) > index, __FILE__, __LINE__);

        RegressionTestEntry tempEntry (m_testServiceIds[index], m_testServiceStates[index]);
        return (tempEntry);
    }
    else
    {
        prismAssert (false, __FILE__, __LINE__);
        RegressionTestEntry tempEntry (0, false);
        return (tempEntry);
    }
}

RegressionTestObjectManagerSetTestServiceStateMessage::RegressionTestObjectManagerSetTestServiceStateMessage ()
    : WaveMessage    (RegressionTestObjectManager::getWaveServiceId (), REGRESSION_SET_TEST_SERVICE_STATE),
      m_testServiceId (0),
      m_isTestEnabled (false)
{
}

RegressionTestObjectManagerSetTestServiceStateMessage::RegressionTestObjectManagerSetTestServiceStateMessage (WaveServiceId testServiceId, bool isTestEnabled)
    : WaveMessage (RegressionTestObjectManager::getWaveServiceId (), REGRESSION_SET_TEST_SERVICE_STATE),
      m_testServiceId (testServiceId),
      m_isTestEnabled (isTestEnabled)
{
}

RegressionTestObjectManagerSetTestServiceStateMessage::~RegressionTestObjectManagerSetTestServiceStateMessage ()
{
}

void RegressionTestObjectManagerSetTestServiceStateMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeWaveServiceId (&m_testServiceId, "testServiceId"));
     addSerializableAttribute (new AttributeBool (&m_isTestEnabled,           "isTestEnabled"));
}

WaveServiceId RegressionTestObjectManagerSetTestServiceStateMessage::getTestServiceId ()
{
    return (m_testServiceId);
}

bool RegressionTestObjectManagerSetTestServiceStateMessage::getIsTestEnabled ()
{
    return (m_isTestEnabled);
}

RegressionTestObjectManagerStartRegressionMessage::RegressionTestObjectManagerStartRegressionMessage ()
    : WaveMessage (RegressionTestObjectManager::getWaveServiceId (), REGRESSION_START_REGRESSION),
      m_numberOfTimesToRunRegression (1)
{
}

RegressionTestObjectManagerStartRegressionMessage::RegressionTestObjectManagerStartRegressionMessage (UI32 numberOfTimesToRunRegression)
    : WaveMessage (RegressionTestObjectManager::getWaveServiceId (), REGRESSION_START_REGRESSION),
      m_numberOfTimesToRunRegression (numberOfTimesToRunRegression)
{
}

RegressionTestObjectManagerStartRegressionMessage::~RegressionTestObjectManagerStartRegressionMessage ()
{
}

void RegressionTestObjectManagerStartRegressionMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeUI32 (&m_numberOfTimesToRunRegression, "numberOfTimesToRunRegression"));
}

UI32 RegressionTestObjectManagerStartRegressionMessage::getNumberOfTimesToRunRegression ()
{
    return (m_numberOfTimesToRunRegression);
}

RegressionTestObjectManagerRunTestForAServiceMessage::RegressionTestObjectManagerRunTestForAServiceMessage ()
    : ManagementInterfaceMessage (RegressionTestObjectManager::getServiceName (), REGRESSION_RUN_TEST_FOR_A_SERVICE),
      m_serviceCode (0),
      m_numberOfTimesToRunServiceTest (1)
{
}

RegressionTestObjectManagerRunTestForAServiceMessage::RegressionTestObjectManagerRunTestForAServiceMessage (WaveServiceId serviceCode)
    : ManagementInterfaceMessage (RegressionTestObjectManager::getServiceName (), REGRESSION_RUN_TEST_FOR_A_SERVICE),
      m_serviceCode (serviceCode),
      m_numberOfTimesToRunServiceTest (1)
{
}

RegressionTestObjectManagerRunTestForAServiceMessage::RegressionTestObjectManagerRunTestForAServiceMessage (WaveServiceId serviceCode, UI32 numberOfTimesToRunServiceTest)
    : ManagementInterfaceMessage (RegressionTestObjectManager::getServiceName (), REGRESSION_RUN_TEST_FOR_A_SERVICE),
      m_serviceCode (serviceCode),
      m_numberOfTimesToRunServiceTest (numberOfTimesToRunServiceTest)
{
}

RegressionTestObjectManagerRunTestForAServiceMessage::~RegressionTestObjectManagerRunTestForAServiceMessage ()
{
}

void RegressionTestObjectManagerRunTestForAServiceMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeWaveServiceId (&m_serviceCode,         "serviceCode"));
     addSerializableAttribute (new AttributeUI32 (&m_numberOfTimesToRunServiceTest, "numberOfTimesToRunServiceTest"));
}

WaveServiceId RegressionTestObjectManagerRunTestForAServiceMessage::getServiceCode ()
{
    return (m_serviceCode);
}

UI32 RegressionTestObjectManagerRunTestForAServiceMessage::getNumberOfTimesToRunServiceTest ()
{
    return (m_numberOfTimesToRunServiceTest);
}


RegressionTestObjectManagerPrepareTestForAServiceMessage::RegressionTestObjectManagerPrepareTestForAServiceMessage ()
    : ManagementInterfaceMessage (RegressionTestObjectManager::getServiceName (), REGRESSION_PREPARE_TEST_FOR_A_SERVICE),
      m_serviceCode (0)
{
}

RegressionTestObjectManagerPrepareTestForAServiceMessage::RegressionTestObjectManagerPrepareTestForAServiceMessage (WaveServiceId serviceCode)
    : ManagementInterfaceMessage (RegressionTestObjectManager::getServiceName (), REGRESSION_PREPARE_TEST_FOR_A_SERVICE),
      m_serviceCode (serviceCode)
{
}

RegressionTestObjectManagerPrepareTestForAServiceMessage::RegressionTestObjectManagerPrepareTestForAServiceMessage (WaveServiceId serviceCode, vector<string> inputStrings)
    : ManagementInterfaceMessage (RegressionTestObjectManager::getServiceName (), REGRESSION_PREPARE_TEST_FOR_A_SERVICE),
      m_serviceCode (serviceCode),
      m_inputStrings (inputStrings)
{
}

RegressionTestObjectManagerPrepareTestForAServiceMessage::~RegressionTestObjectManagerPrepareTestForAServiceMessage ()
{
}

void RegressionTestObjectManagerPrepareTestForAServiceMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeWaveServiceId (&m_serviceCode, "serviceCode"));
     addSerializableAttribute (new AttributeStringVector (&m_inputStrings,  "inputStrings"));
}

WaveServiceId RegressionTestObjectManagerPrepareTestForAServiceMessage::getServiceCode ()
{
    return (m_serviceCode);
}

vector<string> &RegressionTestObjectManagerPrepareTestForAServiceMessage::getInputStrings ()
{
    return (m_inputStrings);
}

}
