/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/LightHouse/LightPulseRegistrationWorker.h"
#include "Framework/Messaging/LightHouse/LightPulseRegistrationMessage.h"
#include "Framework/Messaging/LightHouse/LightPulseDispatchObjectManager.h"
#include "Framework/Messaging/LightHouse/LightPulseDispatchTypes.h"

using WaveNs::LightPulseDispatchObjectManager;

namespace WaveNs
{

LightPulseRegistrationWorker::LightPulseRegistrationWorker (LightPulseDispatchObjectManager *pLightPulseDispatchObjectManager)
    : WaveWorker (pLightPulseDispatchObjectManager)
{
    addOperationMap (LIGHT_PULSE_DISPATCH_REGISTER_FOR_LIGHT_PULSE, reinterpret_cast<WaveMessageHandler> (&LightPulseRegistrationWorker::registerForLightPulseMessageHandler));
}

LightPulseRegistrationWorker::~LightPulseRegistrationWorker ()
{
}

void LightPulseRegistrationWorker::registerForLightPulseMessageHandler (LightPulseRegistrationMessage *pLightPulseRegistrationMessage)
{
    trace (TRACE_LEVEL_DEVEL, "LightPulseRegistrationWorker::registerForLightPulseMessageHandler : Entering ...");

    waveAssert (NULL != pLightPulseRegistrationMessage, __FILE__, __LINE__);

    pLightPulseRegistrationMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    reply (pLightPulseRegistrationMessage);
}

}
