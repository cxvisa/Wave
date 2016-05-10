/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/LightHouse/LightPulseDispatchWorker.h"
#include "Framework/Messaging/LightHouse/LightPulse.h"
#include "Framework/Messaging/LightHouse/LightPulseDispatchMessage.h"
#include "Framework/Messaging/LightHouse/LightPulseDispatchObjectManager.h"
#include "Framework/Messaging/LightHouse/LightPulseDispatchTypes.h"
#include "Framework/Messaging/MessageFactory/WaveMessageFactory.h"

using WaveNs::LightPulseDispatchObjectManager;

namespace WaveNs
{

LightPulseDispatchWorker::LightPulseDispatchWorker (LightPulseDispatchObjectManager *pLightPulseDispatchObjectManager)
    : WaveWorker (pLightPulseDispatchObjectManager)
{
    addOperationMap (LIGHT_PULSE_DISPATCH_RECEIVED_LIGHT_PULSE, reinterpret_cast<WaveMessageHandler> (&LightPulseDispatchWorker::dispatchReceivedLightPulseMessageHandler));
}

LightPulseDispatchWorker::~LightPulseDispatchWorker ()
{
}

void LightPulseDispatchWorker::dispatchReceivedLightPulseMessageHandler (LightPulseDispatchMessage *pLightPulseDispatchMessage)
{
    trace (TRACE_LEVEL_DEVEL, "LightPulseDispatchWorker::dispatchReceivedLightPulseMessageHandler : Entering ...");

    waveAssert (NULL != pLightPulseDispatchMessage, __FILE__, __LINE__);

    const string seralizedLightPulseString = pLightPulseDispatchMessage->getLightPulseSerializedString ();

    trace (TRACE_LEVEL_INFO, "LightPulseDispatchWorker::dispatchReceivedLightPulseMessageHandler : Dispatching a Light Pulse ...\r\n" + seralizedLightPulseString);

    const string lightPulseName = LightPulse::getLightPulseName (seralizedLightPulseString.c_str ());

    trace (TRACE_LEVEL_INFO, "LightPulseDispatchWorker::dispatchReceivedLightPulseMessageHandler : Light Pulse Name : " + lightPulseName);

    LightPulse *pLightPulse = WaveMessageFactory::getLightPulseInstance (lightPulseName);

    if (NULL == pLightPulse)
    {
        trace (TRACE_LEVEL_FATAL, "LightPulseDispatchWorker::dispatchReceivedLightPulseMessageHandler : Please have the corresponding Object Manager implement  createLightPulseInstance for : " + lightPulseName);
        waveAssert (false, __FILE__, __LINE__);
    }

    pLightPulseDispatchMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    reply (pLightPulseDispatchMessage);
}

}
