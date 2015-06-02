/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : MITHUN BS                                                    *
 ***************************************************************************/

#include "Framework/Core/Test/PrismTestManagedView1.h"

namespace WaveNs
{

PrismTestManagedView1::PrismTestManagedView1 (WaveObjectManager *pWaveObjectManager)
    : PrismElement           (pWaveObjectManager),
      PrismPersistableObject (PrismTestManagedView1::getClassName ()),
      WaveManagedObject      (pWaveObjectManager),
      WaveManagedView        (pWaveObjectManager)
{   
}

PrismTestManagedView1::~PrismTestManagedView1 ()
{
}

string PrismTestManagedView1::getClassName ()
{
    return ("PrismTestManagedView1");
}

void PrismTestManagedView1::setupAttributesForPersistence ()
{
    addPersistableAttribute (new AttributeUI32     (&m_integer1,  "integer1"));
    addPersistableAttribute (new AttributeString   (&m_message1,  "message1"));
}

void PrismTestManagedView1::setupAttributesForCreate ()
{
    addPersistableAttributeForCreate (new AttributeUI32     (&m_integer1,  "integer1"));
    addPersistableAttributeForCreate (new AttributeString   (&m_message1,  "message1"));
}

string PrismTestManagedView1::getSqlForCreateView ()
{
    string sqlForCreateView = "CREATE OR REPLACE VIEW WaveCurrent.PrismTestManagedView1 AS SELECT integer1, message1 from  wavecurrent.PrismTestManagedObject1 UNION SELECT integer2, message2 from wavecurrent.PrismTestManagedObject2;";
    return sqlForCreateView;
}

void PrismTestManagedView1::setInteger1 (const UI32 &integer1)
{
    m_integer1 = integer1;
}

void PrismTestManagedView1::setMessage1 (const string &message1)
{
    m_message1 = message1;
}

UI32 PrismTestManagedView1::getInteger1 () const
{   
    return (m_integer1);
}

string PrismTestManagedView1::getMessage1 () const
{   
    return (m_message1);
}

}
