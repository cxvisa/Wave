/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "ServiceManagement/Local/ExternalNonNativeServiceInstanceManagedObject.h"
#include "ServiceManagement/Global/ExternalNonNativeServiceManagedObject.h"

namespace WaveNs
{

ExternalNonNativeServiceInstanceManagedObject::ExternalNonNativeServiceInstanceManagedObject (WaveObjectManager *pWaveObjectManager)
    : WaveElement                (pWaveObjectManager),
      WavePersistableObject      (ExternalNonNativeServiceInstanceManagedObject::getClassName (), WaveLocalManagedObject::getClassName ()),
      WaveManagedObject          (pWaveObjectManager),
      WaveLocalManagedObjectBase (this),
      WaveLocalManagedObject     (pWaveObjectManager)
{
}

ExternalNonNativeServiceInstanceManagedObject::ExternalNonNativeServiceInstanceManagedObject (WaveObjectManager *pWaveObjectManager, const string &applicationInstanceName)
    : WaveElement                (pWaveObjectManager),
      WavePersistableObject      (ExternalNonNativeServiceInstanceManagedObject::getClassName (), WaveLocalManagedObject::getClassName ()),
      WaveManagedObject          (pWaveObjectManager),
      WaveLocalManagedObjectBase (this),
      WaveLocalManagedObject     (pWaveObjectManager)
{
    setName (applicationInstanceName);
}

ExternalNonNativeServiceInstanceManagedObject::~ExternalNonNativeServiceInstanceManagedObject ()
{
}

string ExternalNonNativeServiceInstanceManagedObject::getClassName ()
{
    return ("ExternalNonNativeServiceInstanceManagedObject");
}

void ExternalNonNativeServiceInstanceManagedObject::setupAttributesForPersistence ()
{
    WaveLocalManagedObject::setupAttributesForPersistence ();

    // This class Specific Attributes below

    addPersistableAttribute (new AttributeObjectIdAggregation (&m_service, "service", ExternalNonNativeServiceManagedObject::getClassName()));
}

void ExternalNonNativeServiceInstanceManagedObject::setupAttributesForCreate ()
{
    WaveLocalManagedObject::setupAttributesForCreate ();

    // This class Specific Attributes below

    addPersistableAttributeForCreate (new AttributeObjectIdAggregation (&m_service, "service", ExternalNonNativeServiceManagedObject::getClassName()));
}

void ExternalNonNativeServiceInstanceManagedObject::setupKeys ()
{
    vector<string> userDefinedKeyCombination;

    userDefinedKeyCombination.push_back ("name");

    setUserDefinedKeyCombination (userDefinedKeyCombination);
}

ObjectId ExternalNonNativeServiceInstanceManagedObject::getService () const
{
    return (m_service);
}

void ExternalNonNativeServiceInstanceManagedObject::setService (const ObjectId &service)
{
    m_service = service;
}

}
