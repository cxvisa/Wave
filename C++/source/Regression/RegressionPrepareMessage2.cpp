/***************************************************************************
 *   Copyright (C) 2006 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#include "Regression/RegressionPrepareMessage2.h"

namespace WaveNs
{

RegressionPrepareMessage2::RegressionPrepareMessage2 (WaveServiceId id)
    : PrismMessage (id, WAVE_OBJECT_MANAGER_PREPARE_FOR_REGRESSION2)
{
}

RegressionPrepareMessage2::RegressionPrepareMessage2 ()
    : PrismMessage (0, WAVE_OBJECT_MANAGER_PREPARE_FOR_REGRESSION2)
{
}

RegressionPrepareMessage2::~RegressionPrepareMessage2 ()
{
}

void RegressionPrepareMessage2::setupAttributesForSerialization ()
{
    PrismMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeStringVector (&m_inputStrings, "inputStrings"));
}

void RegressionPrepareMessage2::addInputString (const string &inputString)
{
    m_inputStrings.push_back (inputString);
}

vector<string> &RegressionPrepareMessage2::getInputStrings ()
{
    return (m_inputStrings);
}

}
