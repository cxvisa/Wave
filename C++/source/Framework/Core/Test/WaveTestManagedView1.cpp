/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : MITHUN BS                                                    *
 ***************************************************************************/

#include "Framework/Core/Test/WaveTestManagedView1.h"

namespace WaveNs
{

WaveTestManagedView1::WaveTestManagedView1 (WaveObjectManager *pWaveObjectManager)
    : WaveElement           (pWaveObjectManager),
      WavePersistableObject (WaveTestManagedView1::getClassName ()),
      WaveManagedObject      (pWaveObjectManager),
      WaveManagedView        (pWaveObjectManager)
{   
}

WaveTestManagedView1::~WaveTestManagedView1 ()
{
}

string WaveTestManagedView1::getClassName ()
{
    return ("WaveTestManagedView1");
}

void WaveTestManagedView1::setupAttributesForPersistence ()
{
    addPersistableAttribute (new AttributeUI32     (&m_integer1,  "integer1"));
    addPersistableAttribute (new AttributeString   (&m_message1,  "message1"));
}

void WaveTestManagedView1::setupAttributesForCreate ()
{
    addPersistableAttributeForCreate (new AttributeUI32     (&m_integer1,  "integer1"));
    addPersistableAttributeForCreate (new AttributeString   (&m_message1,  "message1"));
}

string WaveTestManagedView1::getSqlForCreateView ()
{
    string sqlForCreateView = "CREATE OR REPLACE VIEW WaveCurrent.WaveTestManagedView1 AS SELECT integer1, message1 from  wavecurrent.WaveTestManagedObject1 UNION SELECT integer2, message2 from wavecurrent.WaveTestManagedObject2;";
    return sqlForCreateView;
}

void WaveTestManagedView1::setInteger1 (const UI32 &integer1)
{
    m_integer1 = integer1;
}

void WaveTestManagedView1::setMessage1 (const string &message1)
{
    m_message1 = message1;
}

UI32 WaveTestManagedView1::getInteger1 () const
{   
    return (m_integer1);
}

string WaveTestManagedView1::getMessage1 () const
{   
    return (m_message1);
}

}
