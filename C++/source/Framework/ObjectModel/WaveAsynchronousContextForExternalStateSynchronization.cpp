/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveAsynchronousContextForExternalStateSynchronization.h"

namespace WaveNs
{

WaveAsynchronousContextForExternalStateSynchronization::WaveAsynchronousContextForExternalStateSynchronization (WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext)
    : WaveAsynchronousContext (pCaller, pCallback, pCallerContext),
      m_fssStageNumber (0),
      m_serviceType (0)
{
}

WaveAsynchronousContextForExternalStateSynchronization::~WaveAsynchronousContextForExternalStateSynchronization ()
{
}

UI32 WaveAsynchronousContextForExternalStateSynchronization::getFssStageNumber () const
{
    return (m_fssStageNumber);
}

void WaveAsynchronousContextForExternalStateSynchronization::setFssStageNumber (const UI32 fssStageNumber)
{
    m_fssStageNumber = fssStageNumber;
}

ResourceId WaveAsynchronousContextForExternalStateSynchronization::getServiceType () const
{
    return (m_serviceType);
}

void WaveAsynchronousContextForExternalStateSynchronization::setServiceType (const ResourceId serviceType)
{
    m_serviceType = serviceType;
}

}
