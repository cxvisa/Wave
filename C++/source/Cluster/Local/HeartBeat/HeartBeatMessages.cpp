/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Amr Sabaa                                                    *
 ***************************************************************************/

#include "Cluster/Local/HeartBeat/HeartBeatMessages.h"
#include "Cluster/ClusterTypes.h"
#include "Cluster/Local/HeartBeat/HeartBeatObjectManager.h"
#include "Framework/Utils/FrameworkToolKit.h"

namespace WaveNs
{

StartHeartBeatMessage::StartHeartBeatMessage (WaveServiceId serviceCode, UI32 operationCode)
    : WaveMessage (serviceCode, operationCode),
      m_dstPortNumber(0),
      m_heartBeatInterval         (0),
      m_heartBeatFailureThreshold (0)
{
}
    
StartHeartBeatMessage::StartHeartBeatMessage (IpV4Address dstIpAddress, UI16 dstPortNumber)
    : WaveMessage (HeartBeatObjectManager::getWaveServiceId (), HEARTBEAT_START), 
      m_dstIpAddress              (dstIpAddress), 
      m_dstPortNumber             (dstPortNumber),
      m_heartBeatInterval         (0),
      m_heartBeatFailureThreshold (0)
{
}

StartHeartBeatMessage::StartHeartBeatMessage (IpV4Address dstIpAddress, UI16 dstPortNumber, UI32 heartBeatInterval)
    : WaveMessage (HeartBeatObjectManager::getWaveServiceId (), HEARTBEAT_START), 
      m_dstIpAddress              (dstIpAddress), 
      m_dstPortNumber             (dstPortNumber),
      m_heartBeatInterval         (heartBeatInterval),
      m_heartBeatFailureThreshold (0)
{

}

StartHeartBeatMessage::StartHeartBeatMessage (IpV4Address dstIpAddress, UI16 dstPortNumber, UI32 heartBeatInterval, UI32 heartBeatFailureThreshold)
    : WaveMessage (HeartBeatObjectManager::getWaveServiceId (), HEARTBEAT_START), 
      m_dstIpAddress              (dstIpAddress), 
      m_dstPortNumber             (dstPortNumber),
      m_heartBeatInterval         (heartBeatInterval),
      m_heartBeatFailureThreshold (heartBeatFailureThreshold)
{

}

StartHeartBeatMessage::StartHeartBeatMessage ()
    : WaveMessage (HeartBeatObjectManager::getWaveServiceId (), HEARTBEAT_START), 
      m_dstPortNumber             (0),
      m_heartBeatInterval         (0),
      m_heartBeatFailureThreshold (0)
{
}

StartHeartBeatMessage::~StartHeartBeatMessage ()
{
}

void StartHeartBeatMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeIpV4Address (&m_dstIpAddress,               "dstIpAddress"));
     addSerializableAttribute (new AttributeUI16        (&m_dstPortNumber,              "dstPortNumber"));
     addSerializableAttribute (new AttributeUI32        (&m_heartBeatInterval,          "heartBeatInterval"));
     addSerializableAttribute (new AttributeUI32        (&m_heartBeatFailureThreshold,  "heartBeatFailureThreshold"));
}

IpV4Address StartHeartBeatMessage::getDstIpAddress ()
{
    return (m_dstIpAddress);
}

void StartHeartBeatMessage::setDstIpAddress (IpV4Address dstIpAddress)
{
    m_dstIpAddress = dstIpAddress;
}


UI16 StartHeartBeatMessage::getDstPortNumber()
{
    return (m_dstPortNumber);
}

void StartHeartBeatMessage::setDstPortNumber (UI16 dstPortNumber)
{
    m_dstPortNumber= dstPortNumber;
}

UI32 StartHeartBeatMessage::getHeartBeatInterval ()
{
    return (m_heartBeatInterval);
}

void StartHeartBeatMessage::setHeartBeatInterval (UI32 heartBeatInterval)
{
    m_heartBeatInterval = heartBeatInterval;
}

UI32 StartHeartBeatMessage::getHeartBeatFailureThreshold ()
{
    return (m_heartBeatFailureThreshold);
}

void StartHeartBeatMessage::setHeartBeatFailureThreshold (UI32 heartBeatFailureThreshold)
{
    m_heartBeatFailureThreshold = heartBeatFailureThreshold;
}

// StopHeartBeat

StopHeartBeatMessage::StopHeartBeatMessage ()
    : StartHeartBeatMessage (HeartBeatObjectManager::getWaveServiceId (), HEARTBEAT_STOP)
{
}

StopHeartBeatMessage::~StopHeartBeatMessage ()
{
}

PauseHeartBeatMessage::PauseHeartBeatMessage ()
    : StartHeartBeatMessage (HeartBeatObjectManager::getWaveServiceId (), HEARTBEAT_PAUSE)
{
}

PauseHeartBeatMessage::~PauseHeartBeatMessage ()
{
}

ResumeHeartBeatMessage::ResumeHeartBeatMessage ()
    : StartHeartBeatMessage (HeartBeatObjectManager::getWaveServiceId (), HEARTBEAT_RESUME)
{
}

ResumeHeartBeatMessage::~ResumeHeartBeatMessage ()
{
}

ConfigHeartBeatMessage::ConfigHeartBeatMessage ()
    : StartHeartBeatMessage (HeartBeatObjectManager::getWaveServiceId (), HEARTBEAT_CONFIG)
{
}

ConfigHeartBeatMessage::~ConfigHeartBeatMessage ()
{
}

GetHeartBeatStatMessage::GetHeartBeatStatMessage ()
    : ManagementInterfaceMessage ("Heart Beat Service", HEARTBEAT_GET_STAT),
      m_dstPortNumber (0), 
      m_heartBeatSent (0),
      m_heartBeatReplySent (0),
      m_heartBeatReceived  (0),
      m_heartBeatReplyReceived (0),
      m_lastHeartBeatReceived (0),
      m_lastHeartBeatReplyReceived (0),
      m_heartBeatLost (0),
      m_heartBeatLostInRow (0),
      m_heartBeatDelayed (0),
      m_heartBeatDuplicate (0)
{
}

GetHeartBeatStatMessage::~GetHeartBeatStatMessage ()
{
}

void GetHeartBeatStatMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeIpV4Address (&m_dstIpAddress,               "dstIpAddress"));
     addSerializableAttribute (new AttributeUI16        (&m_dstPortNumber,              "dstPortNumber"));
     addSerializableAttribute (new AttributeUI32        (&m_heartBeatSent,              "heartBeatSent"));
     addSerializableAttribute (new AttributeUI32        (&m_heartBeatReplySent,         "heartBeatReplySent"));
     addSerializableAttribute (new AttributeUI32        (&m_heartBeatReceived,          "heartBeatReceived"));
     addSerializableAttribute (new AttributeUI32        (&m_heartBeatReplyReceived,     "heartBeatReplyReceived"));
     addSerializableAttribute (new AttributeUI32        (&m_lastHeartBeatReceived,      "lastHeartBeatReceived"));
     addSerializableAttribute (new AttributeUI32        (&m_lastHeartBeatReplyReceived, "lastHeartBeatReplyReceived"));
     addSerializableAttribute (new AttributeUI32        (&m_heartBeatLost,              "heartBeatLost"));
     addSerializableAttribute (new AttributeUI32        (&m_heartBeatLostInRow,         "heartBeatLostInRow"));
     addSerializableAttribute (new AttributeUI32        (&m_heartBeatDelayed,           "heartBeatDelayed"));
     addSerializableAttribute (new AttributeUI32        (&m_heartBeatDuplicate,         "heartBeatDuplicate"));
}

IpV4Address GetHeartBeatStatMessage::getDstIpAddress ()
{
    return (m_dstIpAddress);
}

void GetHeartBeatStatMessage::setDstIpAddress (IpV4Address dstIpAddress)
{
    m_dstIpAddress = dstIpAddress;
}


UI16 GetHeartBeatStatMessage::getDstPortNumber()
{
    return (m_dstPortNumber);
}

void GetHeartBeatStatMessage::setDstPortNumber (UI16 dstPortNumber)
{
    m_dstPortNumber= dstPortNumber;
}

ShowHeartBeatStatMessage::ShowHeartBeatStatMessage ()
    : StartHeartBeatMessage (HeartBeatObjectManager::getWaveServiceId (), HEARTBEAT_SHOW_STAT)
{
    m_dstPortNumber      = FrameworkToolKit::getThisLocationPort ();
}

ShowHeartBeatStatMessage::~ShowHeartBeatStatMessage ()
{
}

ReportHeartBeatMessage::ReportHeartBeatMessage ()
    : StartHeartBeatMessage (HeartBeatObjectManager::getWaveServiceId (), HEARTBEAT_REPORT),
      m_senderPort (0),
      m_heartBeatNum (0)
{
}

ReportHeartBeatMessage::~ReportHeartBeatMessage ()
{
}

UI32 ReportHeartBeatMessage::getHeartBeatNum ()
{
    return (m_heartBeatNum);
}

void ReportHeartBeatMessage::setHeartBeatNum (UI32 heartBeatNum)
{
    m_heartBeatNum  =   heartBeatNum;
}

IpV4Address ReportHeartBeatMessage::getSenderIpAddress ()
{
    return (m_senderIpAddress);
}

void ReportHeartBeatMessage::setSenderIpAddress (IpV4Address senderIpAddress)
{
    m_senderIpAddress   = senderIpAddress;
}

UI32 ReportHeartBeatMessage::getSenderPort ()
{
    return (m_senderPort);
}

void ReportHeartBeatMessage::setSenderPort (UI32 senderPort)
{
    m_senderPort   = senderPort;
}

void ReportHeartBeatMessage::setupAttributesForSerialization ()
{
    StartHeartBeatMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeIpV4Address (&m_senderIpAddress,    "senderIpAddress"));
     addSerializableAttribute (new AttributeUI32 (&m_senderPort,                "senderPort"));
     addSerializableAttribute (new AttributeUI32 (&m_heartBeatNum,              "heartBeatNum"));
}

DisconnectFromNodeMessage::DisconnectFromNodeMessage(LocationId locationId)
      :WaveMessage (HeartBeatObjectManager::getWaveServiceId(),HEARTBEAT_DISCONNECT_FROM_NODE),
       mLocationId  (locationId),
       m_serverPort (0)
{
}


DisconnectFromNodeMessage::~DisconnectFromNodeMessage()
{
}

void DisconnectFromNodeMessage::setLocationId(LocationId locationId)
{
    mLocationId = locationId;
}

LocationId  DisconnectFromNodeMessage::getLocationId() const
{
    return mLocationId;
}

void DisconnectFromNodeMessage::setServerIpAddress (const string &serverIpAddress)
{
    m_serverIpAddress = serverIpAddress;
}

void DisconnectFromNodeMessage::setServerPort (const UI32 &serverPort)
{
    m_serverPort = serverPort;
}

string DisconnectFromNodeMessage::getServerIpAddress () const
{
    return (m_serverIpAddress);
}

UI32 DisconnectFromNodeMessage::getServerPort  () const
{
    return (m_serverPort);
}

}
