/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/LightHouse/LightPulseDispatchMessage.h"
#include "Framework/Messaging/LightHouse/LightPulseDispatchObjectManager.h"
#include "LightPulseDispatchTypes.h"

namespace WaveNs
{

LightPulseDispatchMessage::LightPulseDispatchMessage ()
    : WaveMessage (LightPulseDispatchObjectManager::getWaveServiceId (), LIGHT_PULSE_DISPATCH_RECEIVED_LIGHT_PULSE)
{
}

LightPulseDispatchMessage::~LightPulseDispatchMessage ()
{
}

string LightPulseDispatchMessage::getLightPulseSerializedString () const
{
    return (m_lightPulseSerializedString);
}

void LightPulseDispatchMessage::setLightPulseSerializedString (const string &lightPulseSerializedString)
{
    m_lightPulseSerializedString = lightPulseSerializedString;
}

void LightPulseDispatchMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeString (&m_lightPulseSerializedString, "lightPulseSerializedString"));
}

}
