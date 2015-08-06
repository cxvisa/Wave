/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/Test/WaveTestManagedObject11.h"
#include "Framework/Attributes/AttributeManagedObjectVectorComposition.cpp"

namespace WaveNs
{

WaveTestManagedObject11::WaveTestManagedObject11 (WaveObjectManager *pWaveObjectManager)
    : WaveElement (pWaveObjectManager),
      PrismPersistableObject (WaveTestManagedObject11::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject (pWaveObjectManager),
      m_integer11        (0)
{
}

WaveTestManagedObject11::~WaveTestManagedObject11 ()
{
}

string WaveTestManagedObject11::getClassName ()
{
    return ("WaveTestManagedObject11");
}

void WaveTestManagedObject11::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeUI32                                                    (&m_integer11,     "integer11"));
    addPersistableAttribute (new AttributeString                                                  (&m_message11,     "message11"));
    addPersistableAttribute (new AttributeManagedObjectVectorComposition<WaveTestManagedObject7> (&m_composition11, "composition11", getClassName (), getObjectId (), WaveTestManagedObject7::getClassName ()));
}

void WaveTestManagedObject11::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeUI32                                                    (&m_integer11,     "integer11"));
    addPersistableAttributeForCreate (new AttributeString                                                  (&m_message11,     "message11"));
    addPersistableAttributeForCreate (new AttributeManagedObjectVectorComposition<WaveTestManagedObject7> (&m_composition11, "composition11", getClassName (), getObjectId (), WaveTestManagedObject7::getClassName ()));
}

void WaveTestManagedObject11::setInteger11 (const UI32 &integer11)
{
    m_integer11 = integer11;
}

void WaveTestManagedObject11::setMessage11 (const string &message11)
{
    m_message11 = message11;
}

void WaveTestManagedObject11::setComposition11 (const vector<WaveManagedObjectPointer<WaveTestManagedObject7> > &composition11)
{
    m_composition11 = composition11;
}

UI32 WaveTestManagedObject11::getInteger11 () const
{
    return (m_integer11);
}

string WaveTestManagedObject11::getMessage11 () const
{
    return (m_message11);
}

vector<WaveManagedObjectPointer<WaveTestManagedObject7> > WaveTestManagedObject11::getComposition11 () const
{
    return (m_composition11);
}

bool WaveTestManagedObject11::operator == (const WaveTestManagedObject11 &rhs) const
{
    if ((rhs.getObjectId ()) != ((getObjectId ())))
    {
        return (false);
    }

    if (rhs.m_integer11 != m_integer11)
    {
        return (false);
    }

    if (rhs.m_message11 != m_message11)
    {
        return (false);
    }

          map<ObjectId, WaveManagedObjectPointer<WaveTestManagedObject7> > mapForThis;
          map<ObjectId, WaveManagedObjectPointer<WaveTestManagedObject7> > mapForRhs;
    const UI32                                                              thisSize      = m_composition11.size ();
    const UI32                                                              rhsSize       = rhs.m_composition11.size ();
          UI32                                                              i             = 0;
          ObjectId                                                          tempObjectId;
          WaveManagedObjectPointer<WaveTestManagedObject7>                 temp;

    if (thisSize != rhsSize)
    {
        return (false);
    }

    for (i = 0; i < thisSize; i++)
    {
        temp         = m_composition11[i];
        tempObjectId = temp->getObjectId ();

        mapForThis[tempObjectId] = temp;
    }

    for (i = 0; i < rhsSize; i++)
    {
        temp         = rhs.m_composition11[i];
        tempObjectId = temp->getObjectId ();

        mapForRhs[tempObjectId] = temp;
    }

    if (mapForThis != mapForRhs)
    {
        return (false);
    }

    return (true);
}

bool WaveTestManagedObject11::operator != (const WaveTestManagedObject11 &rhs) const
{
    return (!(operator == (rhs)));
}

}
