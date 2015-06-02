/***************************************************************************
 *   Copyright (C) 2013 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Pritee Ghosh                                                 *
 ***************************************************************************/

#include "Framework/Core/Test/PrismTestManagedView2.h"
#include "Framework/Core/Test/PrismTestManagedObject1.h"
#include "Framework/Core/Test/PrismTestManagedObject2.h"

namespace WaveNs
{

PrismTestManagedView2::PrismTestManagedView2 (WaveObjectManager *pWaveObjectManager)
    : PrismElement (pWaveObjectManager),
      PrismPersistableObject (PrismTestManagedView2::getClassName ()), 
      WaveManagedObject (pWaveObjectManager),
      WaveManagedView   (pWaveObjectManager),
      m_integer1        (0),
      m_message1        ("")
{
}

PrismTestManagedView2::~PrismTestManagedView2 ()
{
}

string PrismTestManagedView2::getClassName ()
{
    return ("PrismTestManagedView2");
}

void PrismTestManagedView2::setupAttributesForPersistence ()
{
    WaveManagedView::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeUI32     (&m_integer1,  "integer1"));
    addPersistableAttribute (new AttributeString   (&m_message1,  "message1"));
}

void PrismTestManagedView2::setupAttributesForCreate ()
{
    WaveManagedView::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeUI32     (&m_integer1,  "integer1"));
    addPersistableAttributeForCreate (new AttributeString   (&m_message1,  "message1"));
}

void PrismTestManagedView2::getSetContextForCreateView (WaveManagedObjectSynchronousQueryContextForSetOperation &viewContext)
{
    trace (TRACE_LEVEL_INFO, "PrismTestManagedView2::getSetContextForCreateView: entering..");

    vector<string> selectFields;
    selectFields.push_back ("integer1");
    selectFields.push_back ("message1");

    WaveManagedObjectSynchronousInnerQueryContext* pInnerSynchronousQuery1 = viewContext.addInnerQueryContext (PrismTestManagedObject1::getClassName (), selectFields);

    prismAssert (NULL != pInnerSynchronousQuery1, __FILE__, __LINE__);

    selectFields.clear();
    selectFields.push_back ("integer2");
    selectFields.push_back ("message2");

    WaveManagedObjectSynchronousInnerQueryContext* pInnerSynchronousQuery2 = viewContext.addInnerQueryContext (PrismTestManagedObject2::getClassName (), selectFields, OPERATOR_UNION);
    
    prismAssert (NULL != pInnerSynchronousQuery2, __FILE__, __LINE__);
}

string PrismTestManagedView2::getMessage2 ()
{
    return (m_message1);
}

UI32 PrismTestManagedView2::getInteger2 ()
{
    return (m_integer1);
}

}
