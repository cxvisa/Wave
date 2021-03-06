/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/Core/Test/WaveTestManagedObject9.h"

namespace WaveNs
{

WaveTestManagedObject9::WaveTestManagedObject9 (WaveObjectManager *pWaveObjectManager)
    : WaveElement (pWaveObjectManager),
      WavePersistableObject (WaveTestManagedObject9::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject (pWaveObjectManager),
      m_integer9        (0)
{
}

WaveTestManagedObject9::~WaveTestManagedObject9 ()
{
}

string WaveTestManagedObject9::getClassName ()
{
    return ("WaveTestManagedObject9");
}

void WaveTestManagedObject9::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeUI32 (&m_integer9,"integer9"));
    addPersistableAttribute (new AttributeUI32 (&m_integer9_1,"integer9_1")); // This is a dummy attribute not used in BIST.  This is used to force a schema change.
    addPersistableAttribute (new AttributeString (&m_message9,"message9"));
}

void WaveTestManagedObject9::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeUI32 (&m_integer9,"integer9"));
    addPersistableAttributeForCreate (new AttributeUI32 (&m_integer9_1,"integer9_1"));
    addPersistableAttributeForCreate (new AttributeString (&m_message9,"message9"));
}

void WaveTestManagedObject9::setInteger9 (const UI32 &integer9)
{
    m_integer9 = integer9;
}

void WaveTestManagedObject9::setMessage9 (const string &message9)
{
    m_message9 = message9;
}


UI32 WaveTestManagedObject9::getInteger9 () const
{
    return (m_integer9);
}

string WaveTestManagedObject9::getMessage9 () const
{
    return (m_message9);
}

}
