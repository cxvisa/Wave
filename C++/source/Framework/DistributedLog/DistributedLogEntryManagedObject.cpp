/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#include "Framework/DistributedLog/DistributedLogEntryManagedObject.h"
#include "Framework/DistributedLog/DistributedLogObjectManager.h"
#include "Framework/Attributes/AttributeResourceId.h"

namespace WaveNs
{

DistributedLogEntryManagedObject::DistributedLogEntryManagedObject (DistributedLogObjectManager *pDistributedLogObjectManager)
    : WaveElement              (pDistributedLogObjectManager),
      PrismPersistableObject    (DistributedLogEntryManagedObject::getClassName (), WaveManagedObject::getClassName()),
      WaveManagedObject         (pDistributedLogObjectManager),
      m_logId                   (0),
      m_logType                 (),
      m_logDescriptionType      (),
      m_dateTimeStamp           (),
      m_waveServiceId          (),
      m_username                (""),
      m_description             (""),
      m_waveNodeObjectId        (),
      m_managedObjectId         ()
{
}

DistributedLogEntryManagedObject::DistributedLogEntryManagedObject (DistributedLogObjectManager *pDistributedLogObjectManager, const string &name)
    : WaveElement              (pDistributedLogObjectManager),
      PrismPersistableObject    (DistributedLogEntryManagedObject::getClassName (), WaveManagedObject::getClassName()),
      WaveManagedObject         (pDistributedLogObjectManager),
      m_logId                   (0),
      m_logType                 (),
      m_logDescriptionType      (),
      m_dateTimeStamp           (),
      m_waveServiceId          (),
      m_username                (""),
      m_description             (""),
      m_waveNodeObjectId        (),
      m_managedObjectId         ()
{
    setName (name);
}

DistributedLogEntryManagedObject::~DistributedLogEntryManagedObject ()
{
}

string DistributedLogEntryManagedObject::getClassName ()
{
    return ("DistributedLogEntryManagedObject");
}

void DistributedLogEntryManagedObject::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();
    
    addPersistableAttribute (new AttributeUI64 (&m_logId, "logId"));
    addPersistableAttribute (new AttributeResourceId (&m_logType, "logType"));
    addPersistableAttribute (new AttributeResourceId (&m_logDescriptionType, "logDescriptionType"));
    addPersistableAttribute (new AttributeDateTime (&m_dateTimeStamp, "dateTimeStamp"));
    addPersistableAttribute (new AttributeWaveServiceId (&m_waveServiceId, "prismServiceId"));
    addPersistableAttribute (new AttributeString (&m_username, "username"));
    addPersistableAttribute (new AttributeString (&m_description, "description"));
    addPersistableAttribute (new AttributeObjectId (&m_waveNodeObjectId, "waveNodeObjectId"));
    addPersistableAttribute (new AttributeObjectId (&m_managedObjectId, "managedObjectId"));
}

void DistributedLogEntryManagedObject::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeUI64 (&m_logId, "logId"));
    addPersistableAttributeForCreate (new AttributeResourceId (&m_logType, "logType"));
    addPersistableAttributeForCreate (new AttributeResourceId (&m_logDescriptionType, "logDescriptionType"));
    addPersistableAttributeForCreate (new AttributeDateTime (&m_dateTimeStamp, "dateTimeStamp"));
    addPersistableAttributeForCreate (new AttributeWaveServiceId (&m_waveServiceId, "prismServiceId"));
    addPersistableAttributeForCreate (new AttributeString (&m_username, "username"));
    addPersistableAttributeForCreate (new AttributeString (&m_description, "description"));
    addPersistableAttributeForCreate (new AttributeObjectId (&m_waveNodeObjectId, "waveNodeObjectId"));
    addPersistableAttributeForCreate (new AttributeObjectId (&m_managedObjectId, "managedObjectId"));
}

void DistributedLogEntryManagedObject::setupKeys ()
{
    vector<string> userDefinedKeycombination;

    userDefinedKeycombination.push_back ("logId");

    setUserDefinedKeyCombination (userDefinedKeycombination);
}

UI64 DistributedLogEntryManagedObject::getLogId () const
{
    return (m_logId);
}

void DistributedLogEntryManagedObject::setLogId (const UI64 &logId)
{
    m_logId = logId;
}

ResourceId DistributedLogEntryManagedObject::getLogType () const
{
    return (m_logType);
}

void DistributedLogEntryManagedObject::setLogType (const ResourceId &logType)
{
    m_logType = logType;
}

ResourceId DistributedLogEntryManagedObject::getLogDescriptionType () const
{
    return (m_logDescriptionType);
}

void DistributedLogEntryManagedObject::setLogDescriptionType (const ResourceId &logDescriptionType)
{
    m_logDescriptionType = logDescriptionType;
}

DateTime DistributedLogEntryManagedObject::getDateTimeStamp () const
{
    return (m_dateTimeStamp);
}

void DistributedLogEntryManagedObject::setDateTimeStamp (const DateTime &dateTimeStamp)
{
    m_dateTimeStamp = dateTimeStamp;
}

WaveServiceId DistributedLogEntryManagedObject::getWaveServiceId () const
{
    return (m_waveServiceId);
}

void DistributedLogEntryManagedObject::setWaveServiceId (const WaveServiceId &prismServiceId)
{
    m_waveServiceId = prismServiceId;
}

string DistributedLogEntryManagedObject::getUsername () const
{
    return (m_username);
}

void DistributedLogEntryManagedObject::setUsername (const string &username)
{
    m_username = username;
}

string DistributedLogEntryManagedObject::getDescription () const
{
    return (m_description);
}

void DistributedLogEntryManagedObject::setDescription (const string &description)
{
    m_description = description;
}

ObjectId DistributedLogEntryManagedObject::getWaveNodeObjectId () const
{
    return (m_waveNodeObjectId);
}

void DistributedLogEntryManagedObject::setWaveNodeObjectId (const ObjectId &waveNodeObjectId)
{
    m_waveNodeObjectId = waveNodeObjectId;
}

ObjectId DistributedLogEntryManagedObject::getManagedObjectId () const
{
    return (m_managedObjectId);
}

void DistributedLogEntryManagedObject::setManagedObjectId (const ObjectId &managedObjectId)
{
    m_managedObjectId = managedObjectId;
}

}

