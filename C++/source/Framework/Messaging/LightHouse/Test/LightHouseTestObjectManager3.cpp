/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/LightHouse/Test/LightHouseTestObjectManager3.h"
#include "Framework/Messaging/LightHouse/Test/LightHouseTestContext.h"
#include "Framework/Messaging/LightHouse/Test/LightHouseTestLightPulse1.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"

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

void LightHouseTestObjectManager3::listenForEvents (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    listenForLightPulse (LightHouseTestLightPulse1::getLightPulseName (), reinterpret_cast<WaveLightPulseHandler> (&LightHouseTestObjectManager3::lightHouseTestLightPulse1Handler));

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback            ();
}

void LightHouseTestObjectManager3::lightHouseTestLightPulse1Handler (const LightHouseTestLightPulse1 *&pLightHouseTestLightPulse1)
{
    waveAssert (NULL != pLightHouseTestLightPulse1, __FILE__, __LINE__);

    const string lightMessage                         = pLightHouseTestLightPulse1->getLightMessage                         ();
    const string senderIpAddressFromClientPerspective = pLightHouseTestLightPulse1->getSenderIpAddressFromClientPerspective ();

    trace (TRACE_LEVEL_INFO, "LightHouseTestObjectManager3::lightHouseTestLightPulse1Handler : Light Message Received : " + lightMessage + ", from ip address : " + senderIpAddressFromClientPerspective);
}

}
