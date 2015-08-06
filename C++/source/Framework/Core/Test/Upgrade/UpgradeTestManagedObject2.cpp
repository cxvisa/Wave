/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/Test/Upgrade/UpgradeTestManagedObject2.h"
#include "Framework/Core/Test/Upgrade/UpgradeTestManagedObject1.h"

namespace WaveNs
{

UpgradeTestManagedObject2::UpgradeTestManagedObject2 (WaveObjectManager *pWaveObjectManager)
        : WaveElement (pWaveObjectManager),
        PrismPersistableObject (UpgradeTestManagedObject2::getClassName (), WaveManagedObject::getClassName ()),
        WaveManagedObject (pWaveObjectManager),
        m_integer2        (0)
{
}

UpgradeTestManagedObject2::~UpgradeTestManagedObject2 ()
{
}

string UpgradeTestManagedObject2::getClassName ()
{
    return ("UpgradeTestManagedObject2");
}

void UpgradeTestManagedObject2::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeUI32                (&m_integer2,     "integer2"));
    addPersistableAttribute (new AttributeString              (&m_message2,     "message2"));
    addPersistableAttribute (new AttributeObjectId            (&m_objectId2,    "objectId2"));
    addPersistableAttribute (new AttributeObjectIdAssociation (&m_association2, "association2", UpgradeTestManagedObject1::getClassName ()));
}

void UpgradeTestManagedObject2::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeUI32                (&m_integer2,     "integer2"));
    addPersistableAttributeForCreate (new AttributeString              (&m_message2,     "message2"));
    addPersistableAttributeForCreate (new AttributeObjectId            (&m_objectId2,    "objectId2"));
    addPersistableAttributeForCreate (new AttributeObjectIdAssociation (&m_association2, "association2", UpgradeTestManagedObject1::getClassName ()));
}

void UpgradeTestManagedObject2::setInteger2 (const UI32 &integer2)
{
    m_integer2 = integer2;
}

void UpgradeTestManagedObject2::setMessage2 (const string &message2)
{
    m_message2 = message2;
}

void UpgradeTestManagedObject2::setObjectId2 (const ObjectId &objectId2)
{
    m_objectId2 = objectId2;
}

void UpgradeTestManagedObject2::setAssociation2 (const ObjectId &association2)
{
    m_association2 = association2;
}

UI32 UpgradeTestManagedObject2::getInteger2 () const
{
    return (m_integer2);
}

string UpgradeTestManagedObject2::getMessage2 () const
{
    return (m_message2);
}

ObjectId UpgradeTestManagedObject2::getObjectId2 () const
{
    return (m_objectId2);
}

ObjectId UpgradeTestManagedObject2::getAssociation2 () const
{
    return (m_association2);
}

bool UpgradeTestManagedObject2::operator == (const UpgradeTestManagedObject2 &rhs) const
{
    if ((rhs.getObjectId ()) != ((getObjectId ())))
    {
        return (false);
    }

    if (rhs.m_integer2 != m_integer2)
    {
        return (false);
    }

    if (rhs.m_message2 != m_message2)
    {
        return (false);
    }

    if (rhs.m_objectId2 != m_objectId2)
    {
        return (false);
    }

    if (rhs.m_association2 != m_association2)
    {
        return (false);
    }

    return (true);
}

bool UpgradeTestManagedObject2::operator != (const UpgradeTestManagedObject2 &rhs) const
{
    return (!(operator == (rhs)));
}

}
