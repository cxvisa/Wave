/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/LocationManagement/WaveNodeConnectionInformation.h"

namespace WaveNs
{

WaveNodeConnectionInformation::WaveNodeConnectionInformation ()
    : SerializableObject (),
      m_thisLocationServerIpAddress (""),
      m_thisLocationServerPort (0),
      m_expectedLocationId (256),
      m_messageVersion ("")
{
}

WaveNodeConnectionInformation::WaveNodeConnectionInformation (const string &thisLocationServerIpAddress, const UI32 &thisLocationServerPort, const LocationId &expectedLocationId, const string &messageVersion)
    : SerializableObject (),
      m_thisLocationServerIpAddress (thisLocationServerIpAddress),
      m_thisLocationServerPort (thisLocationServerPort),
      m_expectedLocationId (expectedLocationId),
      m_messageVersion     (messageVersion)
{
}

WaveNodeConnectionInformation::~WaveNodeConnectionInformation ()
{
}

void WaveNodeConnectionInformation::setupAttributesForSerialization ()
{
    SerializableObject::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeString (&m_thisLocationServerIpAddress,  "thisLocationServerIpAddress"));
    addSerializableAttribute (new AttributeUI32   (&m_thisLocationServerPort,       "thisLocationServerPort"));
    addSerializableAttribute (new AttributeLocationId   (&m_expectedLocationId,     "expectedLocationId"));
    addSerializableAttribute (new AttributeString       (&m_messageVersion,         "messageVersion"));
}
 
string WaveNodeConnectionInformation::getThisLocationServerIpAddress () const
{
    return (m_thisLocationServerIpAddress);
}

void WaveNodeConnectionInformation::setThisLocationServerIpAddress (const string &thisLocationServerIpAddress)
{
    m_thisLocationServerIpAddress = thisLocationServerIpAddress;
}

UI32 WaveNodeConnectionInformation::getThisLocationServerPort () const
{
    return (m_thisLocationServerPort);
}

void WaveNodeConnectionInformation::setThisLocationServerPort (const UI32 &thisLocationServerPort)
{
    m_thisLocationServerPort = thisLocationServerPort;
}

LocationId WaveNodeConnectionInformation::getExpectedLocationId () const
{
    return (m_expectedLocationId);
}

void WaveNodeConnectionInformation::setExpectedLocationId (const LocationId &expectedLocationId)
{
    m_expectedLocationId = expectedLocationId;
}

string WaveNodeConnectionInformation::getMessageVersion () const
{
    return (m_messageVersion); 
}

void WaveNodeConnectionInformation::setMessageVersion (const string &messageVersion) 
{
    m_messageVersion = messageVersion;
}

WaveHaNodeConnectionInformation::WaveHaNodeConnectionInformation ()
    : SerializableObject (),
      m_thisLocationServerIpAddress (""),
      m_thisLocationServerPort (0),
      m_expectedLocationId (256),
      m_messageVersion ("")
{
}

WaveHaNodeConnectionInformation::WaveHaNodeConnectionInformation (const string &thisLocationServerIpAddress, const UI32 &thisLocationServerPort, const LocationId &expectedLocationId, const string &messageVersion)
    : SerializableObject (),
      m_thisLocationServerIpAddress (thisLocationServerIpAddress),
      m_thisLocationServerPort (thisLocationServerPort),
      m_expectedLocationId (expectedLocationId),
      m_messageVersion (messageVersion)
{
}

WaveHaNodeConnectionInformation::~WaveHaNodeConnectionInformation ()
{
}

void WaveHaNodeConnectionInformation::setupAttributesForSerialization ()
{
    SerializableObject::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeString (&m_thisLocationServerIpAddress,  "thisLocationServerIpAddress"));
    addSerializableAttribute (new AttributeUI32   (&m_thisLocationServerPort,       "thisLocationServerPort"));
    addSerializableAttribute (new AttributeLocationId   (&m_expectedLocationId,     "expectedLocationId"));
    addSerializableAttribute (new AttributeString (&m_messageVersion,               "messageVersion"));
}

void WaveHaNodeConnectionInformation::setupAttributesForSerializationInAttributeOrderFormat ()
{
    SerializableObject::setupAttributesForSerializationInAttributeOrderFormat ();
    
    addAttributeNameForOrderToNameMapping ("thisLocationServerIpAddress");
    addAttributeNameForOrderToNameMapping ("thisLocationServerPort");
    addAttributeNameForOrderToNameMapping ("expectedLocationId");
    addAttributeNameForOrderToNameMapping ("messageVersion");
}

string WaveHaNodeConnectionInformation::getThisLocationServerIpAddress () const
{
    return (m_thisLocationServerIpAddress);
}

void WaveHaNodeConnectionInformation::setThisLocationServerIpAddress (const string &thisLocationServerIpAddress)
{
    m_thisLocationServerIpAddress = thisLocationServerIpAddress;
}

UI32 WaveHaNodeConnectionInformation::getThisLocationServerPort () const
{
    return (m_thisLocationServerPort);
}

void WaveHaNodeConnectionInformation::setThisLocationServerPort (const UI32 &thisLocationServerPort)
{
    m_thisLocationServerPort = thisLocationServerPort;
}

LocationId WaveHaNodeConnectionInformation::getExpectedLocationId () const
{
    return (m_expectedLocationId);
}

void WaveHaNodeConnectionInformation::setExpectedLocationId (const LocationId &expectedLocationId)
{
    m_expectedLocationId = expectedLocationId;
}

string WaveHaNodeConnectionInformation::getMessageVersion () const
{
    return (m_messageVersion);
}

void WaveHaNodeConnectionInformation::setMessageVersion (const string &messageVersion)
{
    m_messageVersion = messageVersion;
}

}
