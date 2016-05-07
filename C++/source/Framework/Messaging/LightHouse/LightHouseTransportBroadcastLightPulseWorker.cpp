/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/LightHouse/LightHouseTransportBroadcastLightPulseWorker.h"
#include "Framework/Messaging/LightHouse/LightHouseToolKit.h"
#include "Framework/Messaging/LightHouse/LightHouseTransportBroadcastLightPulseMessage.h"
#include "Framework/Messaging/LightHouse/LightHouseTransportObjectManager.h"
#include "Framework/Messaging/LightHouse/LightHouseTransportTypes.h"
#include "Framework/Messaging/LightHouse/LightPulse.h"
#include "Framework/Utils/MulticastSenderSocket.h"

namespace WaveNs
{

LightHouseTransportBroadcastLightPulseWorker::LightHouseTransportBroadcastLightPulseWorker (LightHouseTransportObjectManager *pLightHouseTransportObjectManager)
    : WaveWorker (pLightHouseTransportObjectManager)
{
    addOperationMap (LIGHT_HOUSE_TRANSPORT_BROADCAST_LIGHT_PULSE, reinterpret_cast<WaveMessageHandler> (&LightHouseTransportBroadcastLightPulseWorker::broadcastLightPulseMessageHandler));

    m_pMulticastSenderSocket = new MulticastSenderSocket (LightHouseToolKit::getLightHouseMulticastIpAddress (), LightHouseToolKit::getLightHouseMulticastPort ());

    waveAssert (NULL != m_pMulticastSenderSocket, __FILE__, __LINE__);
    waveAssert (m_pMulticastSenderSocket->isValid (), __FILE__, __LINE__);
}

LightHouseTransportBroadcastLightPulseWorker::~LightHouseTransportBroadcastLightPulseWorker ()
{
}

void LightHouseTransportBroadcastLightPulseWorker::broadcastLightPulseMessageHandler (LightHouseTransportBroadcastLightPulseMessage *pLightHouseTransportBroadcastLightPulseMessage)
{
    trace (TRACE_LEVEL_DEVEL, "LightHouseTransportBroadcastLightPulseWorker::broadcastLightPulseMessageHandler : Entering ...");

    waveAssert (NULL != pLightHouseTransportBroadcastLightPulseMessage, __FILE__, __LINE__);

    LightPulse *pLightPulse = pLightHouseTransportBroadcastLightPulseMessage->getPLightPulse ();

    waveAssert (NULL != pLightPulse, __FILE__, __LINE__);

    string serializedLightPulseString;

    pLightPulse->serialize2 (serializedLightPulseString);

    m_pMulticastSenderSocket->send (serializedLightPulseString);

    pLightHouseTransportBroadcastLightPulseMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    reply (pLightHouseTransportBroadcastLightPulseMessage);
}

}
