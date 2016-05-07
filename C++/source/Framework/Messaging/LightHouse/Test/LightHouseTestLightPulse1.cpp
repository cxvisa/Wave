/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/LightHouse/Test/LightHouseTestLightPulse1.h"

namespace WaveNs
{

LightHouseTestLightPulse1::LightHouseTestLightPulse1 ()
    : LightPulse (getLightPulseName ())
{
}

LightHouseTestLightPulse1::~LightHouseTestLightPulse1 ()
{
}

string LightHouseTestLightPulse1::getLightPulseName ()
{
    return ("LightHouseTestLightPulse1");
}

string LightHouseTestLightPulse1::getLightMessage () const
{
    return (m_lightMessage);
}

void LightHouseTestLightPulse1::setLightMessage (const string &lightMessage)
{
    m_lightMessage = lightMessage;
}

void LightHouseTestLightPulse1::setupAttributesForSerialization ()
{
    LightPulse::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeString (&m_lightMessage, "lightMessage"));
}

}
