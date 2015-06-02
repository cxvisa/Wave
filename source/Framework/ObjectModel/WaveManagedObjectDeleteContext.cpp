/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveManagedObjectDeleteContext.h"
#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

WaveManagedObjectDeleteContext::WaveManagedObjectDeleteContext (PrismMessage* pPrismMessage, PrismElement* pPrismElement, PrismLinearSequencerStep* pSteps, UI32 numberOfSteps)
    : WaveManagedObjectUpdateContext (pPrismMessage, pPrismElement, pSteps, numberOfSteps)
{
      m_pInputWaveManagedObject     = NULL;
      m_pOperateOnWaveManagedObject = NULL;
}

WaveManagedObjectDeleteContext::~WaveManagedObjectDeleteContext ()
{

}

bool WaveManagedObjectDeleteContext::isNeedToDeleteManagedObject () const
{
    return (m_needToDeleteManagedObject);
}

void WaveManagedObjectDeleteContext::setNeedToDeleteManagedObject (const bool &needToDeleteManagedObject)
{
    m_needToDeleteManagedObject = needToDeleteManagedObject;
}

}

