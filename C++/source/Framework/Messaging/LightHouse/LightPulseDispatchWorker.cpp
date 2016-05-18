/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/LightHouse/LightPulseDispatchWorker.h"

#include "Framework/Core/WaveFrameworkMessages.h"
#include "Framework/Messaging/LightHouse/LightPulse.h"
#include "Framework/Messaging/LightHouse/LightPulseDispatchMessage.h"
#include "Framework/Messaging/LightHouse/LightPulseDispatchObjectManager.h"
#include "Framework/Messaging/LightHouse/LightPulseDispatchTypes.h"
#include "Framework/Messaging/LightHouse/LightPulseRegistrationRepository.h"
#include "Framework/Messaging/LightHouse/Test/LightHouseTestLightPulse1.h"
#include "Framework/Messaging/MessageFactory/WaveMessageFactory.h"
#include "Framework/Utils/FrameworkToolKit.h"

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

    trace (TRACE_LEVEL_DEVEL, "LightPulseDispatchWorker::dispatchReceivedLightPulseMessageHandler : Dispatching a Light Pulse ...\r\n" + seralizedLightPulseString);

    const string lightPulseName = LightPulse::getLightPulseName (seralizedLightPulseString.c_str ());

    trace (TRACE_LEVEL_DEVEL, "LightPulseDispatchWorker::dispatchReceivedLightPulseMessageHandler : Light Pulse Name : " + lightPulseName);

    LightPulse *pLightPulse = WaveMessageFactory::getLightPulseInstance (lightPulseName);

    if (NULL == pLightPulse)
    {
        trace (TRACE_LEVEL_FATAL, "LightPulseDispatchWorker::dispatchReceivedLightPulseMessageHandler : Please have the corresponding Object Manager implement  createLightPulseInstance for : " + lightPulseName);
        waveAssert (false, __FILE__, __LINE__);
    }

    pLightPulse->loadFromSerializedData2 (seralizedLightPulseString);

    pLightPulse->setSenderIpAddressFromClientPerspective (pLightPulseDispatchMessage->getSenderIpAddress ());

    LightPulseRegistrationRepository *pLightPulseRegistrationRepository = LightPulseRegistrationRepository::getInstance ();

    waveAssert (NULL != pLightPulseRegistrationRepository, __FILE__, __LINE__);

    set<WaveServiceId> servicesRegisteredForLightPulse = pLightPulseRegistrationRepository->getLightPulseRecepientsForLightPulseName (lightPulseName);

    set<WaveServiceId>::iterator element    = servicesRegisteredForLightPulse.begin ();
    set<WaveServiceId>::iterator endElement = servicesRegisteredForLightPulse.end   ();

    while (endElement != element)
    {
        WaveServiceId waveServiceId = *element;

        WaveDeliverLightPulseMessage *pWaveDeliverLightPulseMessage = new WaveDeliverLightPulseMessage (waveServiceId);

        pWaveDeliverLightPulseMessage->setPLightPulse (pLightPulse);

        WaveMessageStatus sendStatus = sendOneWay (pWaveDeliverLightPulseMessage);

        if (WAVE_MESSAGE_SUCCESS != sendStatus)
        {
            tracePrintf (TRACE_LEVEL_ERROR, true, false, "LightPulseDispatchWorker::dispatchReceivedLightPulseMessageHandler Could not deliver Light Pulse of type %s to service : %s, status : %s", lightPulseName.c_str (), (FrameworkToolKit::getServiceNameById (waveServiceId)).c_str (), (FrameworkToolKit::localize (sendStatus)).c_str ());
        }
        else
        {
            tracePrintf (TRACE_LEVEL_DEVEL, true, false, "LightPulseDispatchWorker::dispatchReceivedLightPulseMessageHandler : Trying to deliver Light Pulse of type %s to service : %s", lightPulseName.c_str (), (FrameworkToolKit::getServiceNameById (waveServiceId)).c_str ());
        }

        element++;
    }

    pLightPulseDispatchMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    reply (pLightPulseDispatchMessage);
}

}
