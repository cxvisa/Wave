/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/LightHouse/LightHouseTransportBroadcastLightPulseMessage.h"
#include "Framework/Messaging/LightHouse/LightHouseTransportObjectManager.h"
#include "Framework/Messaging/LightHouse/LightHouseTransportTypes.h"
#include "Framework/Messaging/LightHouse/LightPulse.h"

namespace WaveNs
{

LightHouseTransportBroadcastLightPulseMessage::LightHouseTransportBroadcastLightPulseMessage (LightPulse *pLightPulse)
    : WaveMessage (LightHouseTransportObjectManager::getWaveServiceId (), LIGHT_HOUSE_TRANSPORT_BROADCAST_LIGHT_PULSE),
      m_pLightPulse (pLightPulse)
{
}

LightHouseTransportBroadcastLightPulseMessage::~LightHouseTransportBroadcastLightPulseMessage ()
{
    if (NULL != m_pLightPulse)
    {
        delete m_pLightPulse;
    }
}

LightPulse *LightHouseTransportBroadcastLightPulseMessage::getPLightPulse ()
{
    return (m_pLightPulse);
}

void LightHouseTransportBroadcastLightPulseMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();
}

}
