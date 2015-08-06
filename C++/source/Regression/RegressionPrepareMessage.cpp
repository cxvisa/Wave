/***************************************************************************
 *   Copyright (C) 2006 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Regression/RegressionPrepareMessage.h"

namespace WaveNs
{

RegressionPrepareMessage::RegressionPrepareMessage (WaveServiceId id)
    : PrismMessage (id, WAVE_OBJECT_MANAGER_PREPARE_FOR_REGRESSION)
{
}

RegressionPrepareMessage::RegressionPrepareMessage ()
    : PrismMessage (0, WAVE_OBJECT_MANAGER_PREPARE_FOR_REGRESSION)
{
}

RegressionPrepareMessage::~RegressionPrepareMessage ()
{
}

void RegressionPrepareMessage::setupAttributesForSerialization ()
{
    PrismMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeStringVector (&m_inputStrings, "inputStrings"));
}

void RegressionPrepareMessage::addInputString (const string &inputString)
{
    m_inputStrings.push_back (inputString);
}

vector<string> &RegressionPrepareMessage::getInputStrings ()
{
    return (m_inputStrings);
}

}
