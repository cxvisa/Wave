/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/Test/WaveTestManagedObject3.h"
#include "Framework/Core/Test/WaveTestManagedObject2.h"

namespace WaveNs
{

WaveTestManagedObject3::WaveTestManagedObject3 (WaveObjectManager *pWaveObjectManager)
    : WaveElement (pWaveObjectManager),
      WavePersistableObject (WaveTestManagedObject3::getClassName (), WaveTestManagedObject1::getClassName ()),
      WaveTestManagedObject1 (pWaveObjectManager),
      m_integer3              (0)
{
}

WaveTestManagedObject3::~WaveTestManagedObject3 ()
{
}

string WaveTestManagedObject3::getClassName ()
{
    return ("WaveTestManagedObject3");
}

void WaveTestManagedObject3::setupAttributesForPersistence ()
{
    WaveTestManagedObject1::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeUI32                (&m_integer3,     "integer3"));
    addPersistableAttribute (new AttributeString              (&m_message3,     "message3"));
    addPersistableAttribute (new AttributeObjectId            (&m_objectId3,    "objectId3"));
    addPersistableAttribute (new AttributeObjectIdAssociation (&m_association3, "association3", WaveTestManagedObject1::getClassName ()));
}

void WaveTestManagedObject3::setupAttributesForCreate ()
{
    addPersistableAttributeForCreate (new AttributeUI32                (&m_integer3,     "integer3"));
    addPersistableAttributeForCreate (new AttributeString              (&m_message3,     "message3"));
    addPersistableAttributeForCreate (new AttributeObjectId            (&m_objectId3,    "objectId3"));
    addPersistableAttributeForCreate (new AttributeObjectIdAssociation (&m_association3, "association3", WaveTestManagedObject1::getClassName ()));
}

void WaveTestManagedObject3::setInteger3 (const UI32 &integer3)
{
    m_integer3 = integer3;
}

void WaveTestManagedObject3::setMessage3 (const string &message3)
{
    m_message3 = message3;
}

void WaveTestManagedObject3::setObjectId3 (const ObjectId &objectId3)
{
    m_objectId3 = objectId3;
}

void WaveTestManagedObject3::setAssociation3 (const ObjectId &association3)
{
    m_association3 = association3;
}

UI32 WaveTestManagedObject3::getInteger3 () const
{
    return (m_integer3);
}

string WaveTestManagedObject3::getMessage3 () const
{
    return (m_message3);
}

ObjectId WaveTestManagedObject3::getObjectId3 () const
{
    return (m_objectId3);
}

ObjectId WaveTestManagedObject3::getAssociation3 () const
{
    return (m_association3);
}

bool WaveTestManagedObject3::operator == (const WaveTestManagedObject3 &rhs) const
{
    bool isEqual = WaveTestManagedObject1::operator == (rhs);

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

bool WaveTestManagedObject3::operator != (const WaveTestManagedObject3 &rhs) const
{
    return (!(operator == (rhs)));
}

}
