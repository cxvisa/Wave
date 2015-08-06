/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "ManagementInterface/ManagementInterfaceMessage.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Messaging/MessageFactory/WaveMessageFactory.h"

namespace WaveNs
{

ManagementInterfaceMessage::ManagementInterfaceMessage (const string &serviceName, const UI32 &operationId)
    : WaveMessage  (FrameworkToolKit::getServiceIdByName (serviceName), operationId),
      m_serviceName (serviceName),
      m_clientPort  (0),
      m_clientId    (0),
      m_serverId    (0),
      m_slotInstance(0)
{
    // This should be initialized to false and will be set in respective send API
    m_allWaveClients = false;
}

ManagementInterfaceMessage::~ManagementInterfaceMessage ()
{
}

void ManagementInterfaceMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeString (&m_serviceName,                 "serviceName"));
     addSerializableAttribute (new AttributeString (&m_clientIpAddress,             "clientIpAddress"));
     addSerializableAttribute (new AttributeUI32   (&m_clientPort,                  "clientPort"));
     addSerializableAttribute (new AttributeUI32   (&m_clientId,                    "clientId"));
     addSerializableAttribute (new AttributeString (&m_clientName,                  "clientName"));
     addSerializableAttribute (new AttributeString (&m_clientNameWithoutExtension,  "clientNameWithoutExtension"));
     addSerializableAttribute (new AttributeUI32   (&m_serverId,                    "serverId"));
     addSerializableAttribute (new AttributeSI32   (&m_slotInstance,                "slotInstance"));
     addSerializableAttribute (new AttributeBool   (&m_allWaveClients,              "allWaveClients"));
     addSerializableAttribute (new AttributeString (&m_ttyName,                     "ttyName"));
}

string ManagementInterfaceMessage::getServiceName () const
{
    return (m_serviceName);
}

string ManagementInterfaceMessage::getClientIpAddress () const
{
    return (m_clientIpAddress);
}

void ManagementInterfaceMessage::setClientIpAddress (const string &clientIpAddress)
{
    m_clientIpAddress = clientIpAddress;
}

UI32 ManagementInterfaceMessage::getClientPort () const
{
    return (m_clientPort);
}

void ManagementInterfaceMessage::setClientPort (const UI32 &clientPort)
{
    m_clientPort = clientPort;
}

UI32 ManagementInterfaceMessage::getClientId () const
{
    return (m_clientId);
}

void ManagementInterfaceMessage::setClientId (const UI32 &clientId)
{
    m_clientId = clientId;
}

string ManagementInterfaceMessage::getClientName () const
{
    return (m_clientName);
}

void ManagementInterfaceMessage::setClientName (const string &clientName)
{
    m_clientName = clientName;
}

string ManagementInterfaceMessage::getClientNameWithoutExtension () const
{
    return (m_clientNameWithoutExtension);
}

void ManagementInterfaceMessage::setClientNameWithoutExtension (const string &clientNameWithoutExtension)
{
    m_clientNameWithoutExtension = clientNameWithoutExtension;
}

UI32 ManagementInterfaceMessage::getServerId () const
{
    return (m_serverId);
}

void ManagementInterfaceMessage::setServerId (const UI32 &serverId)
{
    m_serverId = serverId;
}

SI32 ManagementInterfaceMessage::getSlotInstance () const
{
    return (m_slotInstance);
}

void ManagementInterfaceMessage::setSlotInstance (const SI32 &instance)
{
    m_slotInstance = instance;
}

bool ManagementInterfaceMessage::getAllWaveClients () const
{
    return (m_allWaveClients);
}

void ManagementInterfaceMessage::setAllWaveClients (const bool &allWaveClients)
{
    m_allWaveClients = allWaveClients;
}

string ManagementInterfaceMessage::getTtyName () const
{
    return (m_ttyName);
}

void ManagementInterfaceMessage::setTtyName (const string &ttyName)
{
    m_ttyName = ttyName;
}

WaveMessage *ManagementInterfaceMessage::clone ()
{
    WaveMessage *pClonedWaveMessage            = WaveMessageFactory::getManagementInterfaceMessageInstance (m_clientNameWithoutExtension, m_serviceCode, m_operationCode);
    string        serializedData;
    UI32          messageIdAtOriginatingLocation = 0;
    UI32          originalMessageId              = 0;
    UI32          waveClientMessageId            = 0;

    prismAssert (NULL != pClonedWaveMessage, __FILE__, __LINE__);

    if (NULL == pClonedWaveMessage)
    {
        return (NULL);
    }

    ManagementInterfaceMessage *pManagementInterfaceMesage = dynamic_cast<ManagementInterfaceMessage *> (pClonedWaveMessage);

    prismAssert (NULL != pManagementInterfaceMesage, __FILE__, __LINE__);

    // Prepare for serialization on this message.

    prepareForSerialization ();

    // Prepare for serialization and load the attributes from this message into the cloned message.

    messageIdAtOriginatingLocation = pManagementInterfaceMesage->getMessageIdAtOriginatingLocation ();
    originalMessageId              = pManagementInterfaceMesage->getOriginalMessageId ();
    waveClientMessageId            = pManagementInterfaceMesage->getWaveClientMessageId ();

    pManagementInterfaceMesage->prepareForSerialization ();
    pManagementInterfaceMesage->loadFromSerializableObject (this);

    pManagementInterfaceMesage->setMessageIdAtOriginatingLocation (messageIdAtOriginatingLocation);
    pManagementInterfaceMesage->setOriginalMessageId              (originalMessageId);
    pManagementInterfaceMesage->setWaveClientMessageId            (waveClientMessageId);
    pManagementInterfaceMesage->m_isACopy                         = true;

    pManagementInterfaceMesage->copyBuffersFrom (*this);

    return (pManagementInterfaceMesage);
}


}
