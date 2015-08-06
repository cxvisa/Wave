/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/Test/PrismTestManagedObject3.h"
#include "Framework/Core/Test/PrismTestManagedObject2.h"

namespace WaveNs
{

PrismTestManagedObject3::PrismTestManagedObject3 (WaveObjectManager *pWaveObjectManager)
    : WaveElement (pWaveObjectManager),
      PrismPersistableObject (PrismTestManagedObject3::getClassName (), PrismTestManagedObject1::getClassName ()),
      PrismTestManagedObject1 (pWaveObjectManager),
      m_integer3              (0)
{
}

PrismTestManagedObject3::~PrismTestManagedObject3 ()
{
}

string PrismTestManagedObject3::getClassName ()
{
    return ("PrismTestManagedObject3");
}

void PrismTestManagedObject3::setupAttributesForPersistence ()
{
    PrismTestManagedObject1::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeUI32                (&m_integer3,     "integer3"));
    addPersistableAttribute (new AttributeString              (&m_message3,     "message3"));
    addPersistableAttribute (new AttributeObjectId            (&m_objectId3,    "objectId3"));
    addPersistableAttribute (new AttributeObjectIdAssociation (&m_association3, "association3", PrismTestManagedObject1::getClassName ()));
}

void PrismTestManagedObject3::setupAttributesForCreate ()
{
    addPersistableAttributeForCreate (new AttributeUI32                (&m_integer3,     "integer3"));
    addPersistableAttributeForCreate (new AttributeString              (&m_message3,     "message3"));
    addPersistableAttributeForCreate (new AttributeObjectId            (&m_objectId3,    "objectId3"));
    addPersistableAttributeForCreate (new AttributeObjectIdAssociation (&m_association3, "association3", PrismTestManagedObject1::getClassName ()));
}

void PrismTestManagedObject3::setInteger3 (const UI32 &integer3)
{
    m_integer3 = integer3;
}

void PrismTestManagedObject3::setMessage3 (const string &message3)
{
    m_message3 = message3;
}

void PrismTestManagedObject3::setObjectId3 (const ObjectId &objectId3)
{
    m_objectId3 = objectId3;
}

void PrismTestManagedObject3::setAssociation3 (const ObjectId &association3)
{
    m_association3 = association3;
}

UI32 PrismTestManagedObject3::getInteger3 () const
{
    return (m_integer3);
}

string PrismTestManagedObject3::getMessage3 () const
{
    return (m_message3);
}

ObjectId PrismTestManagedObject3::getObjectId3 () const
{
    return (m_objectId3);
}

ObjectId PrismTestManagedObject3::getAssociation3 () const
{
    return (m_association3);
}

bool PrismTestManagedObject3::operator == (const PrismTestManagedObject3 &rhs) const
{
    bool isEqual = PrismTestManagedObject1::operator == (rhs);

    if (false == isEqual)
    {
        return (false);
    }

    if (rhs.m_integer3 != m_integer3)
    {
        return (false);
    }

    if (rhs.m_message3 != m_message3)
    {
        return (false);
    }

    if (rhs.m_objectId3 != m_objectId3)
    {
        return (false);
    }

    if (rhs.m_association3 != m_association3)
    {
        return (false);
    }

    return (true);
}

bool PrismTestManagedObject3::operator != (const PrismTestManagedObject3 &rhs) const
{
    return (!(operator == (rhs)));
}

}
