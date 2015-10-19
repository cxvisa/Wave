/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/Test/WaveTestManagedObject1.h"

namespace WaveNs
{

WaveTestManagedObject1::WaveTestManagedObject1 (WaveObjectManager *pWaveObjectManager)
    : WaveElement (pWaveObjectManager),
      WavePersistableObject (WaveTestManagedObject1::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject (pWaveObjectManager),
      m_integer1        (0)
{
}

WaveTestManagedObject1::~WaveTestManagedObject1 ()
{
}

string WaveTestManagedObject1::getClassName ()
{
    return ("WaveTestManagedObject1");
}

void WaveTestManagedObject1::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeUI32     (&m_integer1,  "integer1"));
    addPersistableAttribute (new AttributeString   (&m_message1,  "message1"));
    addPersistableAttribute (new AttributeObjectId (&m_objectId1, "objectId1"));
}

void WaveTestManagedObject1::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeUI32     (&m_integer1,  "integer1"));
    addPersistableAttributeForCreate (new AttributeString   (&m_message1,  "message1"));
    addPersistableAttributeForCreate (new AttributeObjectId (&m_objectId1, "objectId1"));
}

void WaveTestManagedObject1::setInteger1 (const UI32 &integer1)
{
    m_integer1 = integer1;
}

void WaveTestManagedObject1::setMessage1 (const string &message1)
{
    m_message1 = message1;
}

void WaveTestManagedObject1::setObjectId1 (const ObjectId &objectId1)
{
    m_objectId1 = objectId1;
}

UI32 WaveTestManagedObject1::getInteger1 () const
{
    return (m_integer1);
}

string WaveTestManagedObject1::getMessage1 () const
{
    return (m_message1);
}

ObjectId WaveTestManagedObject1::getObjectId1 () const
{
    return (m_objectId1);
}

bool WaveTestManagedObject1::operator == (const WaveTestManagedObject1 &rhs) const
{
    if ((rhs.getObjectId ()) != ((getObjectId ())))
    {
        return (false);
    }

    if (rhs.m_integer1 != m_integer1)
    {
        return (false);
    }

    if (rhs.m_message1 != m_message1)
    {
        return (false);
    }

    if (rhs.m_objectId1 != m_objectId1)
    {
        return (false);
    }

    return (true);
}

bool WaveTestManagedObject1::operator != (const WaveTestManagedObject1 &rhs) const
{
    return (!(operator == (rhs)));
}

}
