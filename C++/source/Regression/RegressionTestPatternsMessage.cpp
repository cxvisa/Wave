/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Regression/RegressionTestPatternsMessage.h"

namespace WaveNs
{

RegressionTestPatternsMessage::RegressionTestPatternsMessage ()
    : WaveMessage (0, WAVE_OBJECT_MANAGER_TEST_PATTERNS)
{
}

RegressionTestPatternsMessage::RegressionTestPatternsMessage (WaveServiceId serviceCode)
    : WaveMessage (serviceCode, WAVE_OBJECT_MANAGER_TEST_PATTERNS)
{
}

RegressionTestPatternsMessage::~RegressionTestPatternsMessage ()
{
}

void RegressionTestPatternsMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeString (&m_testPatterns));
}

const string &RegressionTestPatternsMessage::getTestPatterns () const
{
    return (m_testPatterns);
}

void RegressionTestPatternsMessage::setTestPatterns (const string &testPatterns)
{
    m_testPatterns = testPatterns;
}

}
