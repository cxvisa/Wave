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

ExternalNonNativeServiceInstanceManagedObject::~ExternalNonNativeServiceInstanceManagedObject ()
{
}

string ExternalNonNativeServiceInstanceManagedObject::getClassName ()
{
    return ("ExternalNonNativeServiceInstanceManagedObject");
}

void ExternalNonNativeServiceInstanceManagedObject::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();

    // This class Specific Attributes below

    addPersistableAttribute (new AttributeObjectIdAggregation (&m_service, "service", ExternalNonNativeServiceInstanceManagedObject::getClassName()));
}

void ExternalNonNativeServiceInstanceManagedObject::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    // This class Specific Attributes below
}

}
