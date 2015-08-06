/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : MITHUN BS                                                    *
 ***************************************************************************/

#include "Framework/Core/Test/WaveTestManagedObject12.h"

namespace WaveNs
{

WaveTestManagedObject12::WaveTestManagedObject12 (WaveObjectManager *pWaveObjectManager)
        : WaveElement (pWaveObjectManager),
        PrismPersistableObject (WaveTestManagedObject12::getClassName (), WaveManagedObject::getClassName ()),
        WaveManagedObject (pWaveObjectManager),
        m_integer12        (0)
{
    setEmptyNeededOnPersistentBoot (true);
}

WaveTestManagedObject12::~WaveTestManagedObject12 ()
{
}

string WaveTestManagedObject12::getClassName ()
{
    return ("WaveTestManagedObject12");
}

void WaveTestManagedObject12::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeUI32 (&m_integer12,"integer12"));
    addPersistableAttribute (new AttributeString (&m_message12,"message12"));
}

void WaveTestManagedObject12::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeUI32 (&m_integer12,"integer12"));
    addPersistableAttributeForCreate (new AttributeString (&m_message12,"message12"));

    vector<string > keyName;
    keyName.push_back ("integer12");
    setUserDefinedKeyCombination (keyName);
}

void WaveTestManagedObject12::setInteger12 (const UI32 &integer12)
{
    m_integer12 = integer12;
}

void WaveTestManagedObject12::setMessage12 (const string &message12)
{
    m_message12 = message12;
}


UI32 WaveTestManagedObject12::getInteger12 () const
{
    return (m_integer12);
}

string WaveTestManagedObject12::getMessage12 () const
{
    return (m_message12);
}

}
