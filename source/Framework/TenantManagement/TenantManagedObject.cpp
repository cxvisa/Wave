/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/TenantManagement/TenantManagedObject.h"

namespace WaveNs
{

TenantManagedObject::TenantManagedObject (WaveObjectManager *pWaveObjectManager)
    : PrismElement           (pWaveObjectManager),
      PrismPersistableObject (TenantManagedObject::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject      (pWaveObjectManager)
{
}

TenantManagedObject::~TenantManagedObject ()
{
}

string TenantManagedObject::getClassName ()
{
    return ("TenantManagedObject");
}

void TenantManagedObject::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeUI32 (&m_id, "id"));
}

void TenantManagedObject::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeUI32 (&m_id, "id"));
}

UI32 TenantManagedObject::getId () const
{
    return (m_id);
}

void TenantManagedObject::setId (const UI32 &id)
{
    m_id = id;
}

}
