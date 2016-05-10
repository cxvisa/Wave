/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/LightHouse/Test/LightHouseTestObjectManager3.h"
#include "Regression/RegressionTestMessage.h"
#include "Framework/Messaging/LightHouse/Test/LightHouseTestContext.h"
#include "Framework/Messaging/LightHouse/Test/LightHouseTestLightPulse1.h"
#include "Framework/Utils/StringUtils.h"

namespace WaveNs
{

LightHouseTestObjectManager3::LightHouseTestObjectManager3 ()
    : WaveLocalObjectManager (getServiceName ())
{
}

LightHouseTestObjectManager3::~LightHouseTestObjectManager3 ()
{
}

string LightHouseTestObjectManager3::getServiceName ()
{
    return ("Light House Test 3");
}

LightHouseTestObjectManager3 *LightHouseTestObjectManager3::getInstance ()
{
    static LightHouseTestObjectManager3 *pLightHouseTestObjectManager3 = new LightHouseTestObjectManager3 ();

    WaveNs::waveAssert (NULL != pLightHouseTestObjectManager3, __FILE__, __LINE__);

    return (pLightHouseTestObjectManager3);
}

WaveServiceId LightHouseTestObjectManager3::getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

}
