/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/LightHouse/LightPulseUnregistrationWorker.h"
#include "Framework/Messaging/LightHouse/LightPulseRegistrationMessage.h"
#include "Framework/Messaging/LightHouse/LightPulseDispatchObjectManager.h"
#include "Framework/Messaging/LightHouse/LightPulseDispatchTypes.h"
#include "Framework/Messaging/LightHouse/LightPulseRegistrationRepository.h"

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

    LightPulseRegistrationRepository *pLightPulseRegistrationRepository = LightPulseRegistrationRepository::getInstance ();

    waveAssert (NULL != pLightPulseRegistrationRepository, __FILE__, __LINE__);

    const string        &lightPulseName = pLightPulseRegistrationMessage->getLightPulseName ();
    const WaveServiceId  waveServiceId  = pLightPulseRegistrationMessage->getSenderServiceCode ();

    pLightPulseRegistrationRepository->removeLightPulseRecepientForLightPulseName (lightPulseName, waveServiceId);

    pLightPulseRegistrationMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    reply (pLightPulseRegistrationMessage);
}

}
