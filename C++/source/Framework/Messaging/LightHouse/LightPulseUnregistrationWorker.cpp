/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/LightHouse/LightPulseUnregistrationWorker.h"
#include "Framework/Messaging/LightHouse/LightPulseRegistrationMessage.h"
#include "Framework/Messaging/LightHouse/LightPulseDispatchObjectManager.h"
#include "Framework/Messaging/LightHouse/LightPulseDispatchTypes.h"

using WaveNs::LightPulseDispatchObjectManager;

namespace WaveNs
{

LightPulseUnregistrationWorker::LightPulseUnregistrationWorker (LightPulseDispatchObjectManager *pLightPulseDispatchObjectManager)
    : WaveWorker (pLightPulseDispatchObjectManager)
{
    addOperationMap (LIGHT_PULSE_DISPATCH_UNREGISTER_FOR_LIGHT_PULSE, reinterpret_cast<WaveMessageHandler> (&LightPulseUnregistrationWorker::unregisterForLightPulseMessageHandler));
}

LightPulseUnregistrationWorker::~LightPulseUnregistrationWorker ()
{
}

void LightPulseUnregistrationWorker::unregisterForLightPulseMessageHandler (LightPulseRegistrationMessage *pLightPulseRegistrationMessage)
{
    trace (TRACE_LEVEL_DEVEL, "LightPulseUnregistrationWorker::unregisterForLightPulseMessageHandler : Entering ...");

    waveAssert (NULL != pLightPulseRegistrationMessage, __FILE__, __LINE__);

    pLightPulseRegistrationMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    reply (pLightPulseRegistrationMessage);
}

}
