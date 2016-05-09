/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/LightHouse/LightPulseUnregistrationMessage.h"
#include "Framework/Messaging/LightHouse/LightPulseDispatchObjectManager.h"
#include "LightPulseDispatchTypes.h"

namespace WaveNs
{

LightPulseUnregistrationMessage::LightPulseUnregistrationMessage ()
    : WaveMessage (LightPulseDispatchObjectManager::getWaveServiceId (), LIGHT_PULSE_DISPATCH_UNREGISTER_FOR_LIGHT_PULSE)
{
}

LightPulseUnregistrationMessage::LightPulseUnregistrationMessage (const string &lightPulseName)
    : WaveMessage      (LightPulseDispatchObjectManager::getWaveServiceId (), LIGHT_PULSE_DISPATCH_UNREGISTER_FOR_LIGHT_PULSE),
      m_lightPulseName (lightPulseName)
{
}

LightPulseUnregistrationMessage::~LightPulseUnregistrationMessage ()
{
}

string LightPulseUnregistrationMessage::getLightPulseName () const
{
    return (m_lightPulseName);
}

void LightPulseUnregistrationMessage::setLightPulseName (const string &lightPulseName)
{
    m_lightPulseName = lightPulseName;
}

void LightPulseUnregistrationMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeString (&m_lightPulseName, "lightPulseName"));
}

}
