/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#include "Framework/DistributedLog/DistributedLogAddLogEntryMessage.h"
#include "Framework/DistributedLog/DistributedLogTypes.h"
#include "Framework/DistributedLog/DistributedLogObjectManager.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Attributes/AttributeResourceId.h"

namespace WaveNs
{

DistributedLogAddLogEntryMessage::DistributedLogAddLogEntryMessage ()
    : ManagementInterfaceMessage (DistributedLogObjectManager::getServiceName (), DISTRIBUTED_LOG_ADD_LOG_ENTRY),
    m_logType               (),
    m_logDescriptionType    (),
    m_description           (""),
    m_username              (""),
    m_waveServiceId        (),
    m_dateTimeStamp         (),
    m_waveNodeObjectId      (FrameworkToolKit::getThisWaveNodeObjectId ()),
    m_managedObjectId       ()
{
}

DistributedLogAddLogEntryMessage::DistributedLogAddLogEntryMessage (const ResourceId &logType, const ResourceId &logDescriptionType, const string &description)
    : ManagementInterfaceMessage (DistributedLogObjectManager::getServiceName (), DISTRIBUTED_LOG_ADD_LOG_ENTRY),
    m_logType               (logType),
    m_logDescriptionType    (logDescriptionType),
    m_description           (description),
    m_username              (""),
    m_waveServiceId        (),
    m_dateTimeStamp         (),
    m_waveNodeObjectId      (FrameworkToolKit::getThisWaveNodeObjectId ()),
    m_managedObjectId       ()
{
}

DistributedLogAddLogEntryMessage::DistributedLogAddLogEntryMessage (const ResourceId &logType, const ResourceId &logDescriptionType, const string &description, const string &username)
    : ManagementInterfaceMessage (DistributedLogObjectManager::getServiceName (), DISTRIBUTED_LOG_ADD_LOG_ENTRY),
    m_logType               (logType),
    m_logDescriptionType    (logDescriptionType),
    m_description           (description),
    m_username              (username),
    m_waveServiceId        (),
    m_dateTimeStamp         (),
    m_waveNodeObjectId      (FrameworkToolKit::getThisWaveNodeObjectId ()),
    m_managedObjectId       ()
{
}

DistributedLogAddLogEntryMessage::DistributedLogAddLogEntryMessage (const ResourceId &logType, const ResourceId &logDescriptionType, const string &description, const string &username, const WaveServiceId &waveServiceId, const ObjectId &waveNodeObjectId)
    : ManagementInterfaceMessage (DistributedLogObjectManager::getServiceName (), DISTRIBUTED_LOG_ADD_LOG_ENTRY),
    m_logType               (logType),
    m_logDescriptionType    (logDescriptionType),
    m_description           (description),
    m_username              (username),
    m_waveServiceId        (waveServiceId),
    m_dateTimeStamp         (),
    m_waveNodeObjectId      (waveNodeObjectId),
    m_managedObjectId       ()
{
}

DistributedLogAddLogEntryMessage::DistributedLogAddLogEntryMessage (const ResourceId &logType, const ResourceId &logDescriptionType, const string &description, const WaveServiceId &waveServiceId, const ObjectId &waveNodeObjectId)
    : ManagementInterfaceMessage (DistributedLogObjectManager::getServiceName (), DISTRIBUTED_LOG_ADD_LOG_ENTRY),
    m_logType               (logType),
    m_logDescriptionType    (logDescriptionType),
    m_description           (description),
    m_username              (""),
    m_waveServiceId        (waveServiceId),
    m_dateTimeStamp         (),
    m_waveNodeObjectId      (waveNodeObjectId),
    m_managedObjectId       ()
{
}

DistributedLogAddLogEntryMessage::DistributedLogAddLogEntryMessage (const ResourceId &logType, const ResourceId &logDescriptionType, const string &description, const WaveServiceId &waveServiceId, const ObjectId &waveNodeObjectId, const ObjectId &managedObjectId)
    : ManagementInterfaceMessage (DistributedLogObjectManager::getServiceName (), DISTRIBUTED_LOG_ADD_LOG_ENTRY),
    m_logType               (logType),
    m_logDescriptionType    (logDescriptionType),
    m_description           (description),
    m_username              (""),
    m_waveServiceId        (waveServiceId),
    m_dateTimeStamp         (),
    m_waveNodeObjectId      (waveNodeObjectId),
    m_managedObjectId       (managedObjectId)
{
}

DistributedLogAddLogEntryMessage::~DistributedLogAddLogEntryMessage ()
{
}

void DistributedLogAddLogEntryMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();
    
     addSerializableAttribute (new AttributeResourceId      (&m_logType,            "logType"));
     addSerializableAttribute (new AttributeResourceId      (&m_logDescriptionType, "logDescriptionType"));
     addSerializableAttribute (new AttributeString          (&m_description,        "description"));
     addSerializableAttribute (new AttributeString          (&m_username,           "username"));
     addSerializableAttribute (new AttributeWaveServiceId  (&m_waveServiceId,     "waveServiceId"));
     addSerializableAttribute (new AttributeDateTime        (&m_dateTimeStamp,      "dateTimeStamp"));
     addSerializableAttribute (new AttributeObjectId        (&m_waveNodeObjectId,   "waveNodeObjectId"));
     addSerializableAttribute (new AttributeObjectId        (&m_managedObjectId,    "managedObjectId"));
}

ResourceId DistributedLogAddLogEntryMessage::getLogType () const
{
    return (m_logType);
}

void DistributedLogAddLogEntryMessage::setLogType (const ResourceId &logType)
{
    m_logType = logType;
}

ResourceId DistributedLogAddLogEntryMessage::getLogDescriptionType () const
{
    return (m_logDescriptionType);
}

void DistributedLogAddLogEntryMessage::setLogDescriptionType (const ResourceId &logDescriptionType)
{
    m_logDescriptionType = logDescriptionType;
}

string DistributedLogAddLogEntryMessage::getDescription () const
{
    return (m_description);
}

void DistributedLogAddLogEntryMessage::setDescription (const string &description)
{
    m_description = description;
}

string DistributedLogAddLogEntryMessage::getUsername () const
{
    return (m_username);
}

void DistributedLogAddLogEntryMessage::setUsername (const string &username)
{
    m_username = username;
}

WaveServiceId DistributedLogAddLogEntryMessage::getWaveServiceId () const
{
    return (m_waveServiceId);
}

void DistributedLogAddLogEntryMessage::setWaveServiceId (WaveServiceId waveServiceId)
{
    m_waveServiceId = waveServiceId;
}

DateTime DistributedLogAddLogEntryMessage::getDateTimeStamp () const
{
    return (m_dateTimeStamp);
}

void DistributedLogAddLogEntryMessage::setDateTimeStamp (const DateTime &dateTimeStamp)
{
    m_dateTimeStamp = dateTimeStamp;
}

ObjectId DistributedLogAddLogEntryMessage::getWaveNodeObjectId () const
{
    return (m_waveNodeObjectId);
}

void DistributedLogAddLogEntryMessage::setWaveNodeObjectId (const ObjectId &waveNodeObjectId)
{
    m_waveNodeObjectId = waveNodeObjectId;
}

ObjectId DistributedLogAddLogEntryMessage::getManagedObjectId () const
{
    return (m_managedObjectId);
}

void DistributedLogAddLogEntryMessage::setManagedObjectId (const ObjectId &managedObjectId)
{
    m_managedObjectId = managedObjectId;
}

}

