/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/LightHouse/LightPulse.h"
#include "Framework/Attributes/Attributes.h"
#include "Framework/Attributes/AttributeUUID.h"

namespace WaveNs
{

LightPulse::LightPulse (const string &name)
    : m_name (name),
      m_senderLightHousePort (0)
{
}

LightPulse::~LightPulse ()
{
}

string LightPulse::getName () const
{
    return m_name;
}

void LightPulse::setName (const string& name)
{
    m_name = name;
}

string LightPulse::getSenderIpAddressFromClientPerspective () const
{
    return m_senderIpAddressFromClientPerspective;
}

void LightPulse::setSenderIpAddressFromClientPerspective (const string &senderIpAddressFromClientPerspective)
{
    m_senderIpAddressFromClientPerspective = senderIpAddressFromClientPerspective;
}

Uuid LightPulse::getSenderLightHouseId () const
{
    return m_senderLightHouseId;
}

void LightPulse::setSenderLightHouseId (const Uuid &senderLightHouseId)
{
    m_senderLightHouseId = senderLightHouseId;
}

string LightPulse::getSenderLightHouseIpAddress () const
{
    return m_senderLightHouseIpAddress;
}

void LightPulse::setSenderLightHouseIpAddress (const string &senderLightHouseIpAddress)
{
    m_senderLightHouseIpAddress = senderLightHouseIpAddress;
}

SI32 LightPulse::getSenderLightHousePort () const
{
    return m_senderLightHousePort;
}

void LightPulse::setSenderLightHousePort (const SI32 &senderLightHousePort)
{
    m_senderLightHousePort = senderLightHousePort;
}

void LightPulse::setupAttributesForSerialization ()
{
    SerializableObject::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeString (&m_name,                                 "name"));
    addSerializableAttribute (new AttributeUUID   (&m_senderLightHouseId,                   "senderLightHouseId"));
    addSerializableAttribute (new AttributeString (&m_senderLightHouseIpAddress,            "senderLightHouseIpAddress"));
    addSerializableAttribute (new AttributeSI32   (&m_senderLightHousePort,                 "senderLightHousePort"));
    addSerializableAttribute (new AttributeString (&m_senderIpAddressFromClientPerspective, "senderIpAddressFromClientPerspective"));
}

string LightPulse::getLightPulseName (const char *pSerializedData)
{
    static const char *pAttributeStringAtBegining = "<Aname>";
    static const char *pAttributeStringAtEnding   = "</Aname>";
    static       char  sotString[256];

    const char *pBegin = strstr (pSerializedData, pAttributeStringAtBegining);
    const char *pValue = pBegin + strlen (pAttributeStringAtBegining);
    const char *pEnd   = strstr (pValue, pAttributeStringAtEnding);

    UI32 valueSize = pEnd - pValue;

    strncpy (sotString, pValue, valueSize);

    sotString[valueSize] = '\0';

    return (sotString);
}

}
