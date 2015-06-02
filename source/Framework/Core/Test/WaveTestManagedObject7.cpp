/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/Test/WaveTestManagedObject7.h"
#include "Framework/Attributes/AttributeManagedObjectVectorComposition.cpp"

namespace WaveNs
{

WaveTestManagedObject7::WaveTestManagedObject7 (WaveObjectManager *pWaveObjectManager)
    : PrismElement (pWaveObjectManager),
      PrismPersistableObject (WaveTestManagedObject7::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject (pWaveObjectManager),
      m_integer7        (0)
{
}

WaveTestManagedObject7::~WaveTestManagedObject7 ()
{
}

string WaveTestManagedObject7::getClassName ()
{
    return ("WaveTestManagedObject7");
}

void WaveTestManagedObject7::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeUI32                                                    (&m_integer7,     "integer7"));
    addPersistableAttribute (new AttributeString                                                  (&m_message7,     "message7"));
    addPersistableAttribute (new AttributeObjectId                                                (&m_objectId7,    "objectId7"));
    addPersistableAttribute (new AttributeManagedObjectVectorComposition<PrismTestManagedObject1> (&m_composition7, "composition7", getClassName (), getObjectId (), PrismTestManagedObject1::getClassName ()));
}

void WaveTestManagedObject7::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeUI32                                                    (&m_integer7,     "integer7"));
    addPersistableAttributeForCreate (new AttributeString                                                  (&m_message7,     "message7"));
    addPersistableAttributeForCreate (new AttributeObjectId                                                (&m_objectId7,    "objectId7"));
    addPersistableAttributeForCreate (new AttributeManagedObjectVectorComposition<PrismTestManagedObject1> (&m_composition7, "composition7", getClassName (), getObjectId (), PrismTestManagedObject1::getClassName ()));
}

void WaveTestManagedObject7::setInteger7 (const UI32 &integer7)
{
    m_integer7 = integer7;
}

void WaveTestManagedObject7::setMessage7 (const string &message7)
{
    m_message7 = message7;
}

void WaveTestManagedObject7::setObjectId7 (const ObjectId &objectId7)
{
    m_objectId7 = objectId7;
}

void WaveTestManagedObject7::setComposition7 (const vector<WaveManagedObjectPointer<PrismTestManagedObject1> > &composition7)
{
    m_composition7 = composition7;
}

UI32 WaveTestManagedObject7::getInteger7 () const
{
    return (m_integer7);
}

string WaveTestManagedObject7::getMessage7 () const
{
    return (m_message7);
}

ObjectId WaveTestManagedObject7::getObjectId7 () const
{
    return (m_objectId7);
}

vector<WaveManagedObjectPointer<PrismTestManagedObject1> > WaveTestManagedObject7::getComposition7 () const
{
    return (m_composition7);
}

bool WaveTestManagedObject7::operator == (const WaveTestManagedObject7 &rhs) const
{
    if ((rhs.getObjectId ()) != ((getObjectId ())))
    {
        return (false);
    }

    if (rhs.m_integer7 != m_integer7)
    {
        return (false);
    }

    if (rhs.m_message7 != m_message7)
    {
        return (false);
    }

    if (rhs.m_objectId7 != m_objectId7)
    {
        return (false);
    }

          map<ObjectId, WaveManagedObjectPointer<PrismTestManagedObject1> > mapForThis;
          map<ObjectId, WaveManagedObjectPointer<PrismTestManagedObject1> > mapForRhs;
    const UI32                                                              thisSize      = m_composition7.size ();
    const UI32                                                              rhsSize       = rhs.m_composition7.size ();
          UI32                                                              i             = 0;
          ObjectId                                                          tempObjectId;
          WaveManagedObjectPointer<PrismTestManagedObject1>                 temp;

    if (thisSize != rhsSize)
    {
        return (false);
    }

    for (i = 0; i < thisSize; i++)
    {
        temp         = m_composition7[i];
        tempObjectId = temp->getObjectId ();

        mapForThis[tempObjectId] = temp;
    }

    for (i = 0; i < rhsSize; i++)
    {
        temp         = rhs.m_composition7[i];
        tempObjectId = temp->getObjectId ();

        mapForRhs[tempObjectId] = temp;
    }

    if (mapForThis != mapForRhs)
    {
        return (false);
    }

    return (true);
}

bool WaveTestManagedObject7::operator != (const WaveTestManagedObject7 &rhs) const
{
    return (!(operator == (rhs)));
}

}
