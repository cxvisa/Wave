/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/LightHouse/Test/LightHouseTestObjectManager2.h"
#include "Regression/RegressionTestMessage.h"
#include "Framework/Messaging/LightHouse/Test/LightHouseTestContext.h"
#include "Framework/Messaging/LightHouse/Test/LightHouseTestLightPulse1.h"
#include "Framework/Utils/StringUtils.h"

namespace WaveNs
{

LightHouseTestObjectManager2::LightHouseTestObjectManager2 ()
    : WaveLocalObjectManager (getServiceName ())
{
    addLightPulseType (LightHouseTestLightPulse1::getLightPulseName ());
}

LightHouseTestObjectManager2::~LightHouseTestObjectManager2 ()
{
}

LightPulse *LightHouseTestObjectManager2::createLightPulseInstance (const string &lightPulseName)
{
    LightPulse *pLightPulse = NULL;

    if (lightPulseName == (LightHouseTestLightPulse1::getLightPulseName ()))
    {
        pLightPulse = new LightHouseTestLightPulse1 ();
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, "LightHouseTestObjectManager2::createLightPulseInstance : Unknown Light Pulse Type : " + lightPulseName);
    }

    return (pLightPulse);
}

string LightHouseTestObjectManager2::getServiceName ()
{
    return ("Light House Test 2");
}

LightHouseTestObjectManager2 *LightHouseTestObjectManager2::getInstance ()
{
    static LightHouseTestObjectManager2 *pLightHouseTestObjectManager2 = new LightHouseTestObjectManager2 ();

    WaveNs::waveAssert (NULL != pLightHouseTestObjectManager2, __FILE__, __LINE__);

    return (pLightHouseTestObjectManager2);
}

WaveServiceId LightHouseTestObjectManager2::getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

}
