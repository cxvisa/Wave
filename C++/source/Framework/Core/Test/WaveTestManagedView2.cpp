/***************************************************************************
 *   Copyright (C) 2013 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Pritee Ghosh                                                 *
 ***************************************************************************/

#include "Framework/Core/Test/WaveTestManagedView2.h"
#include "Framework/Core/Test/WaveTestManagedObject1.h"
#include "Framework/Core/Test/WaveTestManagedObject2.h"

namespace WaveNs
{

WaveTestManagedView2::WaveTestManagedView2 (WaveObjectManager *pWaveObjectManager)
    : WaveElement (pWaveObjectManager),
      WavePersistableObject (WaveTestManagedView2::getClassName ()), 
      WaveManagedObject (pWaveObjectManager),
      WaveManagedView   (pWaveObjectManager),
      m_integer1        (0),
      m_message1        ("")
{
}

WaveTestManagedView2::~WaveTestManagedView2 ()
{
}

string WaveTestManagedView2::getClassName ()
{
    return ("WaveTestManagedView2");
}

void WaveTestManagedView2::setupAttributesForPersistence ()
{
    WaveManagedView::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeUI32     (&m_integer1,  "integer1"));
    addPersistableAttribute (new AttributeString   (&m_message1,  "message1"));
}

void WaveTestManagedView2::setupAttributesForCreate ()
{
    WaveManagedView::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeUI32     (&m_integer1,  "integer1"));
    addPersistableAttributeForCreate (new AttributeString   (&m_message1,  "message1"));
}

void WaveTestManagedView2::getSetContextForCreateView (WaveManagedObjectSynchronousQueryContextForSetOperation &viewContext)
{
    trace (TRACE_LEVEL_INFO, "WaveTestManagedView2::getSetContextForCreateView: entering..");

    vector<string> selectFields;
    selectFields.push_back ("integer1");
    selectFields.push_back ("message1");

    WaveManagedObjectSynchronousInnerQueryContext* pInnerSynchronousQuery1 = viewContext.addInnerQueryContext (WaveTestManagedObject1::getClassName (), selectFields);

    waveAssert (NULL != pInnerSynchronousQuery1, __FILE__, __LINE__);

    selectFields.clear();
    selectFields.push_back ("integer2");
    selectFields.push_back ("message2");

    WaveManagedObjectSynchronousInnerQueryContext* pInnerSynchronousQuery2 = viewContext.addInnerQueryContext (WaveTestManagedObject2::getClassName (), selectFields, OPERATOR_UNION);
    
    waveAssert (NULL != pInnerSynchronousQuery2, __FILE__, __LINE__);
}

string WaveTestManagedView2::getMessage2 ()
{
    return (m_message1);
}

UI32 WaveTestManagedView2::getInteger2 ()
{
    return (m_integer1);
}

}
