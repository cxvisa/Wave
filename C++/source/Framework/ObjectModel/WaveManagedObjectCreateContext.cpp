/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveManagedObjectCreateContext.h"
#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

WaveManagedObjectCreateContext::WaveManagedObjectCreateContext (WaveMessage* pWaveMessage, WaveElement* pWaveElement, PrismLinearSequencerStep* pSteps, UI32 numberOfSteps)
    : WaveManagedObjectUpdateContext   (pWaveMessage, pWaveElement, pSteps, numberOfSteps)
{
      m_pInputWaveManagedObject     = NULL;
      m_pOperateOnWaveManagedObject = NULL;

      m_needToCreateManagedObject = false;
}

WaveManagedObjectCreateContext::WaveManagedObjectCreateContext (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement* pWaveElement, PrismLinearSequencerStep* pSteps, UI32 numberOfSteps)
    : WaveManagedObjectUpdateContext   (pPrismAsynchronousContext, pWaveElement, pSteps, numberOfSteps)
{
      m_pInputWaveManagedObject     = NULL;
      m_pOperateOnWaveManagedObject = NULL;

      m_needToCreateManagedObject = false;
}

WaveManagedObjectCreateContext::~WaveManagedObjectCreateContext ()
{

}

string WaveManagedObjectCreateContext::getManagedObjectClassNameNeedToBeCreated () const
{
   return (m_managedObjectClassName);
}

void WaveManagedObjectCreateContext::setManagedObjectClassNameNeedToBeCreated (const string &managedObjectClassName)
{
    m_managedObjectClassName = managedObjectClassName;
}

bool WaveManagedObjectCreateContext::isNeedToCreateManagedObject () const
{
    return (m_needToCreateManagedObject);
}

void WaveManagedObjectCreateContext::setNeedToCreateManagedObject (const bool &needToCreateManagedObject)
{
    m_needToCreateManagedObject = needToCreateManagedObject;
}

vector<Attribute *> WaveManagedObjectCreateContext::getChildAttributeVector () const
{
    return (m_childAttributes);
}

void WaveManagedObjectCreateContext::addToChildAttributeVector (Attribute *pAttribute)
{
    prismAssert (NULL != pAttribute, __FILE__, __LINE__);

    m_childAttributes.push_back (pAttribute);
}

}

