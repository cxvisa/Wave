/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : cgangwar                                                     *
 ***************************************************************************/


#include "Framework/ObjectModel/PrismLinearSequencerContextForShutdownPhase.h"
#include "ManagementInterface/ClientInterface/UnifiedClientBackendDetails.h"
#include "Framework/Utils/PrismLinearSequencerContext.h"

namespace WaveNs
{

PrismLinearSequencerContextForShutdownPhase::PrismLinearSequencerContextForShutdownPhase(PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismLinearSequencerContext (pPrismAsynchronousContext,pPrismElement,pSteps,numberOfSteps)
{
}

PrismLinearSequencerContextForShutdownPhase::~PrismLinearSequencerContextForShutdownPhase()
{
}

void  PrismLinearSequencerContextForShutdownPhase::setBackendMap(const map<string,UnifiedClientBackendDetails*>  &backendMap)
{
    m_backendMap = backendMap;
}
 
map<string,UnifiedClientBackendDetails*>  PrismLinearSequencerContextForShutdownPhase::getBackendMap() const
{
    return(m_backendMap);
}

}
