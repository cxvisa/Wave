/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "ServiceManagement/Global/ExternalNonNativeServiceManagedObject.h"
#include "ServiceManagement/Local/ExternalNonNativeServiceInstanceManagedObject.h"

namespace WaveNs
{

ExternalNonNativeServiceManagedObject::ExternalNonNativeServiceManagedObject (WaveObjectManager *pWaveObjectManager)
    : WaveElement                (pWaveObjectManager),
      WavePersistableObject      (ExternalNonNativeServiceManagedObject::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject          (pWaveObjectManager)
{
}

ExternalNonNativeServiceManagedObject::ExternalNonNativeServiceManagedObject (WaveObjectManager *pWaveObjectManager, const string &name)
    : WaveElement                (pWaveObjectManager),
      WavePersistableObject      (ExternalNonNativeServiceManagedObject::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject          (pWaveObjectManager)
{
    setName (name);
}

ExternalNonNativeServiceManagedObject::~ExternalNonNativeServiceManagedObject ()
{
}

string ExternalNonNativeServiceManagedObject::getClassName ()
{
    return ("ExternalNonNativeServiceManagedObject");
}

void ExternalNonNativeServiceManagedObject::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();

    // This class Specific Attributes below

    addPersistableAttribute (new AttributeObjectIdVectorAssociation (&m_serviceInstances, "serviceInstances", getClassName (), getObjectId (), ExternalNonNativeServiceInstanceManagedObject::getClassName ()));
}

void ExternalNonNativeServiceManagedObject::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    // This class Specific Attributes below

    addPersistableAttributeForCreate (new AttributeObjectIdVectorAssociation (&m_serviceInstances, "serviceInstances", getClassName (), getObjectId (), ExternalNonNativeServiceInstanceManagedObject::getClassName ()));
}

void ExternalNonNativeServiceManagedObject::setupKeys ()
{
    vector<string> userDefinedKeyCombination;

    userDefinedKeyCombination.push_back ("name");

    setUserDefinedKeyCombination (userDefinedKeyCombination);
}

}
