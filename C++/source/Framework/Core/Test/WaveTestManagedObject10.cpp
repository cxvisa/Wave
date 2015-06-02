/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Mithun B S                                                   *
 ***************************************************************************/

#include "Framework/Core/Test/WaveTestManagedObject10.h"
#include "Framework/Core/Test/WaveTestManagedObject6.h"
#include "Framework/Attributes/AttributeManagedObjectComposition.cpp"

namespace WaveNs
{

WaveTestManagedObject10::WaveTestManagedObject10 (WaveObjectManager *pWaveObjectManager)
    : PrismElement (pWaveObjectManager),
      PrismPersistableObject (WaveTestManagedObject10::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject (pWaveObjectManager),
      m_integer10        (0)
{
}

WaveTestManagedObject10::~WaveTestManagedObject10 ()
{
}

string WaveTestManagedObject10::getClassName ()
{
    return ("WaveTestManagedObject10");
}

void WaveTestManagedObject10::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeUI32                                              (&m_integer10,     "integer10"));
    addPersistableAttribute (new AttributeString                                            (&m_message10,     "message10"));
    addPersistableAttribute (new AttributeManagedObjectComposition<WaveTestManagedObject6> (&m_composition10, "composition10", WaveTestManagedObject6::getClassName ()));
}

void WaveTestManagedObject10::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeUI32                                              (&m_integer10,     "integer10"));
    addPersistableAttributeForCreate (new AttributeString                                            (&m_message10,     "message10"));
    addPersistableAttributeForCreate (new AttributeManagedObjectComposition<WaveTestManagedObject6> (&m_composition10, "composition10", WaveTestManagedObject6::getClassName ()));
}

void WaveTestManagedObject10::setInteger10 (const UI32 &integer10)
{
    m_integer10 = integer10;
}

void WaveTestManagedObject10::setMessage10 (const string &message10)
{
    m_message10 = message10;
}

void WaveTestManagedObject10::setComposition10 (const WaveManagedObjectPointer<WaveTestManagedObject6> &composition10)
{
    m_composition10 = composition10;
}

UI32 WaveTestManagedObject10::getInteger10 () const
{
    return (m_integer10);
}

string WaveTestManagedObject10::getMessage10 () const
{
    return (m_message10);
}

WaveManagedObjectPointer<WaveTestManagedObject6> WaveTestManagedObject10::getComposition10 () const
{
    return (m_composition10);
}

bool WaveTestManagedObject10::operator == (const WaveTestManagedObject10 &rhs) const
{
    if ((rhs.getObjectId ()) != ((getObjectId ())))
    {
        return (false);
    }

    if (rhs.m_integer10 != m_integer10)
    {
        return (false);
    }

    if (rhs.m_message10 != m_message10)
    {
        return (false);
    }

    if (m_composition10 != rhs.m_composition10)
    {
        return (false);
    }

    return (true);
}

bool WaveTestManagedObject10::operator != (const WaveTestManagedObject10 &rhs) const
{
    return (!(operator == (rhs)));
}

}
