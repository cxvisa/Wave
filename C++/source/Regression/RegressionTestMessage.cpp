/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Regression/RegressionTestMessage.h"

namespace WaveNs
{

RegressionTestMessage::RegressionTestMessage ()
    : WaveMessage (0, WAVE_OBJECT_MANAGER_TEST)
{
}

RegressionTestMessage::RegressionTestMessage (WaveServiceId serviceCode)
    : WaveMessage (serviceCode, WAVE_OBJECT_MANAGER_TEST)
{
}

RegressionTestMessage::~RegressionTestMessage ()
{
}

void RegressionTestMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();
}

}
