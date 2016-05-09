/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/LightHouse/LightPulseRegistrationMessage.h"
#include "Framework/Messaging/LightHouse/LightPulseDispatchObjectManager.h"
#include "LightPulseDispatchTypes.h"

namespace WaveNs
{

LightPulseRegistrationMessage::LightPulseRegistrationMessage ()
    : WaveMessage (LightPulseDispatchObjectManager::getWaveServiceId (), LIGHT_PULSE_DISPATCH_REGISTER_FOR_LIGHT_PULSE)
{
}

LightPulseRegistrationMessage::~LightPulseRegistrationMessage ()
{
}

string LightPulseRegistrationMessage::getLightPulseName () const
{
    return (m_lightPulseName);
}

void LightPulseRegistrationMessage::setLightPulseName (const string &lightPulseName)
{
    m_lightPulseName = lightPulseName;
}

void LightPulseRegistrationMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeString (&m_lightPulseName, "lightPulseName"));
}

}
