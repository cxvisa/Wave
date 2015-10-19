/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/Core/Test/Upgrade/UpgradeTestManagedObject8.h"

namespace WaveNs
{

UpgradeTestManagedObject8::UpgradeTestManagedObject8 (WaveObjectManager *pWaveObjectManager)
        : WaveElement (pWaveObjectManager),
        WavePersistableObject (UpgradeTestManagedObject8::getClassName (), WaveManagedObject::getClassName ()),
        WaveManagedObject (pWaveObjectManager),
        m_integer8        (0)
{
}

UpgradeTestManagedObject8::~UpgradeTestManagedObject8 ()
{
}

string UpgradeTestManagedObject8::getClassName ()
{
    return ("UpgradeTestManagedObject8");
}

void UpgradeTestManagedObject8::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeUI32 (&m_integer8,"integer8"));
    addPersistableAttribute (new AttributeString (&m_message8,"message8"));
}

void UpgradeTestManagedObject8::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeUI32 (&m_integer8,"integer8"));
    addPersistableAttributeForCreate (new AttributeString (&m_message8,"message8"));
}

void UpgradeTestManagedObject8::setInteger8 (const UI32 &integer8)
{
    m_integer8 = integer8;
}

void UpgradeTestManagedObject8::setMessage8 (const string &message8)
{
    m_message8 = message8;
}


UI32 UpgradeTestManagedObject8::getInteger8 () const
{
    return (m_integer8);
}

string UpgradeTestManagedObject8::getMessage8 () const
{
    return (m_message8);
}

}
