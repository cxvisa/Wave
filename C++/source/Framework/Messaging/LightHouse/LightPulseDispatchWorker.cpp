/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/LightHouse/LightPulseDispatchWorker.h"
#include "Framework/Messaging/LightHouse/LightPulseDispatchMessage.h"
#include "Framework/Messaging/LightHouse/LightPulseDispatchObjectManager.h"
#include "Framework/Messaging/LightHouse/LightPulseDispatchTypes.h"

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

    trace (TRACE_LEVEL_INFO, "LightPulseDispatchWorker::dispatchReceivedLightPulseMessageHandler : Dispatching a Light Pulse ...\n" + pLightPulseDispatchMessage->getLightPulseSerializedString ());

    pLightPulseDispatchMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    reply (pLightPulseDispatchMessage);
}

}
