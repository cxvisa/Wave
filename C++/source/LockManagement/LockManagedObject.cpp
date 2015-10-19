/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anand Kumar Subramanian                                      *
 ***************************************************************************/

#include "LockManagement/LockManagedObject.h"
#include "Framework/Attributes/Attribute.h"

namespace WaveNs
{

LockManagedObject::LockManagedObject (WaveObjectManager *pWaveObjectManager)
    : WaveElement (pWaveObjectManager),
      WavePersistableObject (LockManagedObject::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject (pWaveObjectManager),
      m_locationId (0),
      m_serviceId (0)
{
}

LockManagedObject::LockManagedObject (WaveObjectManager *pWaveObjectManager, const LocationId &locationId, const string &serviceString, const WaveServiceId &serviceId)
    : WaveElement (pWaveObjectManager),
      WavePersistableObject (LockManagedObject::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject (pWaveObjectManager),
      m_locationId (locationId),
      m_serviceString (serviceString),
      m_serviceId (serviceId)    
{
}

LockManagedObject::~LockManagedObject ()
{
}

string LockManagedObject::getClassName ()
{
    return ("LockManagedObject");
}

void LockManagedObject::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeUI32 (&m_locationId,   "locationId"));
    addPersistableAttribute (new AttributeString (&m_serviceString,   "serviceString"));
    addPersistableAttribute (new AttributeUI32 (&m_serviceId, "serviceId"));
}

void LockManagedObject::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeUI32 (&m_locationId,   "locationId"));
    addPersistableAttributeForCreate (new AttributeString (&m_serviceString,   "serviceString"));
    addPersistableAttributeForCreate (new AttributeUI32 (&m_serviceId, "serviceId"));
}

LocationId LockManagedObject::getLocationId () const
{
    return (m_locationId);
}

const string& LockManagedObject::getServiceString () const
{
    return (m_serviceString);
}

WaveServiceId LockManagedObject::getServiceId () const
{
    return (m_serviceId);
}

void LockManagedObject::setLocationId (const LocationId locationId)
{
    m_locationId = locationId;
}

void LockManagedObject::setServiceString (const string &serviceString)
{
    m_serviceString = serviceString;
}

void LockManagedObject::setServiceId (const WaveServiceId serviceId)
{
    m_serviceId = serviceId;
}

void LockManagedObject::resetLockManagedObject ()
{
    m_locationId = 0;
    m_serviceString.clear ();
    m_serviceId = 0;
}

LockManagedObject &LockManagedObject::operator= (const LockManagedObject &lockManagedObject)
{
    m_locationId = lockManagedObject.m_locationId;
    m_serviceString = lockManagedObject.m_serviceString;
    m_serviceId = lockManagedObject.m_serviceId;

    return (*this);
}

}
