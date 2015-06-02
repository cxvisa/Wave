/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#include "Framework/DistributedLog/DistributedLogConfigurationManagedObject.h"
#include "Framework/DistributedLog/DistributedLogObjectManager.h"

namespace WaveNs
{

DistributedLogConfigurationManagedObject::DistributedLogConfigurationManagedObject (DistributedLogObjectManager *pDistributedLogObjectManager)
    : PrismElement           (pDistributedLogObjectManager),
      PrismPersistableObject (DistributedLogConfigurationManagedObject::getClassName (), WaveManagedObject::getClassName()),
      WaveManagedObject      (pDistributedLogObjectManager),
      m_maxLogEntries        (10000),
      m_firstLogId           (0),
      m_nextLogId            (0)
{
}

DistributedLogConfigurationManagedObject::DistributedLogConfigurationManagedObject (DistributedLogObjectManager *pDistributedLogObjectManager, const string &name)
    : PrismElement           (pDistributedLogObjectManager),
      PrismPersistableObject (DistributedLogConfigurationManagedObject::getClassName (), WaveManagedObject::getClassName()),
      WaveManagedObject      (pDistributedLogObjectManager),
      m_maxLogEntries        (10000),
      m_firstLogId           (0),
      m_nextLogId            (0)
{
    setName (name);
}

DistributedLogConfigurationManagedObject::~DistributedLogConfigurationManagedObject ()
{
}

string DistributedLogConfigurationManagedObject::getClassName ()
{
    return ("DistributedLogConfigurationManagedObject");
}

void DistributedLogConfigurationManagedObject::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();
    
    addPersistableAttribute (new AttributeUI64 (&m_maxLogEntries, "maxLogEntries"));
    addPersistableAttribute (new AttributeUI64 (&m_firstLogId, "firstLogId"));
    addPersistableAttribute (new AttributeUI64 (&m_nextLogId, "nextLogId"));
}

void DistributedLogConfigurationManagedObject::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeUI64 (&m_maxLogEntries, "maxLogEntries"));
    addPersistableAttributeForCreate (new AttributeUI64 (&m_firstLogId, "firstLogId"));
    addPersistableAttributeForCreate (new AttributeUI64 (&m_nextLogId, "nextLogId"));
}

UI64 DistributedLogConfigurationManagedObject::getMaxLogEntries () const
{
    return (m_maxLogEntries);
}

void DistributedLogConfigurationManagedObject::setMaxLogEntries (const UI64 &maxLogEntries)
{
    m_maxLogEntries = maxLogEntries;
}

UI64 DistributedLogConfigurationManagedObject::getFirstLogId () const
{
    return (m_firstLogId);
}

void DistributedLogConfigurationManagedObject::setFirstLogId (const UI64 &firstLogId)
{
    m_firstLogId = firstLogId;
}

UI64 DistributedLogConfigurationManagedObject::getNextLogId () const
{
    return (m_nextLogId);
}

void DistributedLogConfigurationManagedObject::setNextLogId (const UI64 &nextLogId)
{
    m_nextLogId = nextLogId;
}

}

