/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/Core/Test/WaveTestManagedObject8.h"

namespace WaveNs
{

WaveTestManagedObject8::WaveTestManagedObject8 (WaveObjectManager *pWaveObjectManager)
    : PrismElement (pWaveObjectManager),
      PrismPersistableObject (WaveTestManagedObject8::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject (pWaveObjectManager),
      m_integer8        (0)
{
}

WaveTestManagedObject8::~WaveTestManagedObject8 ()
{
}

string WaveTestManagedObject8::getClassName ()
{
    return ("WaveTestManagedObject8");
}

void WaveTestManagedObject8::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeUI32 (&m_integer8,"integer8"));
    addPersistableAttribute (new AttributeString (&m_message8,"message8"));
}

void WaveTestManagedObject8::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeUI32 (&m_integer8,"integer8"));
    addPersistableAttributeForCreate (new AttributeString (&m_message8,"message8"));
}

void WaveTestManagedObject8::setInteger8 (const UI32 &integer8)
{
    m_integer8 = integer8;
}

void WaveTestManagedObject8::setMessage8 (const string &message8)
{
    m_message8 = message8;
}


UI32 WaveTestManagedObject8::getInteger8 () const
{
    return (m_integer8);
}

string WaveTestManagedObject8::getMessage8 () const
{
    return (m_message8);
}

}
