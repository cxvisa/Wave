/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/Test/WaveTestManagedObject2.h"
#include "Framework/Core/Test/WaveTestManagedObject1.h"

namespace WaveNs
{

WaveTestManagedObject2::WaveTestManagedObject2 (WaveObjectManager *pWaveObjectManager)
    : WaveElement (pWaveObjectManager),
      WavePersistableObject (WaveTestManagedObject2::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject (pWaveObjectManager),
      m_integer2        (0)
{
}

WaveTestManagedObject2::~WaveTestManagedObject2 ()
{
}

string WaveTestManagedObject2::getClassName ()
{
    return ("WaveTestManagedObject2");
}

void WaveTestManagedObject2::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeUI32                (&m_integer2,     "integer2"));
    addPersistableAttribute (new AttributeString              (&m_message2,     "message2"));
    addPersistableAttribute (new AttributeObjectId            (&m_objectId2,    "objectId2"));
    addPersistableAttribute (new AttributeObjectIdAssociation (&m_association2, "association2", WaveTestManagedObject1::getClassName (), true));
}

void WaveTestManagedObject2::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeUI32                (&m_integer2,     "integer2"));
    addPersistableAttributeForCreate (new AttributeString              (&m_message2,     "message2"));
    addPersistableAttributeForCreate (new AttributeObjectId            (&m_objectId2,    "objectId2"));
    addPersistableAttributeForCreate (new AttributeObjectIdAssociation (&m_association2, "association2", WaveTestManagedObject1::getClassName (), true));
}

void WaveTestManagedObject2::setInteger2 (const UI32 &integer2)
{
    m_integer2 = integer2;
}

void WaveTestManagedObject2::setMessage2 (const string &message2)
{
    m_message2 = message2;
}

void WaveTestManagedObject2::setObjectId2 (const ObjectId &objectId2)
{
    m_objectId2 = objectId2;
}

void WaveTestManagedObject2::setAssociation2 (const ObjectId &association2)
{
    m_association2 = association2;
}

UI32 WaveTestManagedObject2::getInteger2 () const
{
    return (m_integer2);
}

string WaveTestManagedObject2::getMessage2 () const
{
    return (m_message2);
}

ObjectId WaveTestManagedObject2::getObjectId2 () const
{
    return (m_objectId2);
}

ObjectId WaveTestManagedObject2::getAssociation2 () const
{
    return (m_association2);
}

bool WaveTestManagedObject2::operator == (const WaveTestManagedObject2 &rhs) const
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

bool WaveTestManagedObject2::operator != (const WaveTestManagedObject2 &rhs) const
{
    return (!(operator == (rhs)));
}

}
