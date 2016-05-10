/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/LightHouse/Test/LightHouseTestObjectManager1.h"
#include "Regression/RegressionTestMessage.h"
#include "Framework/Messaging/LightHouse/Test/LightHouseTestContext.h"
#include "Framework/Messaging/LightHouse/Test/LightHouseTestLightPulse1.h"
#include "Framework/Utils/StringUtils.h"

namespace WaveNs
{

LightHouseTestObjectManager1::LightHouseTestObjectManager1 ()
    : WaveTestObjectManager (getServiceName ())
{
}

LightHouseTestObjectManager1::~LightHouseTestObjectManager1 ()
{
}

string LightHouseTestObjectManager1::getServiceName ()
{
    return ("Light House Test 1");
}

LightHouseTestObjectManager1 *LightHouseTestObjectManager1::getInstance ()
{
    static LightHouseTestObjectManager1 *pLightHouseTestObjectManager1 = new LightHouseTestObjectManager1 ();

    WaveNs::waveAssert (NULL != pLightHouseTestObjectManager1, __FILE__, __LINE__);

    return (pLightHouseTestObjectManager1);
}

WaveServiceId LightHouseTestObjectManager1::getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

void LightHouseTestObjectManager1::testRequestHandler (RegressionTestMessage *pRegressionTestMessage)
{
    trace (TRACE_LEVEL_DEVEL, "LightHouseTestObjectManager1::testRequestHandler : Entering ...");

    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&LightHouseTestObjectManager1::broadcastTestLightPulse1TestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&LightHouseTestObjectManager1::waveLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&LightHouseTestObjectManager1::waveLinearSequencerFailedStep),
    };

    LightHouseTestContext *pLightHouseTestContext = new LightHouseTestContext (pRegressionTestMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pLightHouseTestContext->start ();
}

void LightHouseTestObjectManager1::broadcastTestLightPulse1TestStep (LightHouseTestContext *pLightHouseTestContext)
{
    trace (TRACE_LEVEL_DEVEL, "LightHouseTestObjectManager1::broadcastTestLightPulse1TestStep : Entering ...");

    static const UI32 numberOfLightPulsesToBeBroadcast = 1000;
    static       UI32 currentCounter                   = 0;
          UI32 i                                = 0;

    for (i = 0; i < numberOfLightPulsesToBeBroadcast; i++)
    {
        LightHouseTestLightPulse1 *pLightHouseTestLightPulse1 = new LightHouseTestLightPulse1 ();

        waveAssert (NULL != pLightHouseTestLightPulse1, __FILE__, __LINE__);

        pLightHouseTestLightPulse1->setLightMessage (string ("Light Message : ") + currentCounter++);

        broadcastLightPulse (pLightHouseTestLightPulse1);
    }

    pLightHouseTestContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

}
