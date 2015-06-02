/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Regression/RegressionTestMessage.h"

namespace WaveNs
{

RegressionTestMessage::RegressionTestMessage ()
    : PrismMessage (0, WAVE_OBJECT_MANAGER_TEST)
{
}

RegressionTestMessage::RegressionTestMessage (PrismServiceId serviceCode)
    : PrismMessage (serviceCode, WAVE_OBJECT_MANAGER_TEST)
{
}

RegressionTestMessage::~RegressionTestMessage ()
{
}

void RegressionTestMessage::setupAttributesForSerialization ()
{
    PrismMessage::setupAttributesForSerialization ();
}

}
