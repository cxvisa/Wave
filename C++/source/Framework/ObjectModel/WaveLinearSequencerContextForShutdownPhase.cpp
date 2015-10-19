/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : cgangwar                                                     *
 ***************************************************************************/


#include "Framework/ObjectModel/WaveLinearSequencerContextForShutdownPhase.h"
#include "ManagementInterface/ClientInterface/UnifiedClientBackendDetails.h"
#include "Framework/Utils/WaveLinearSequencerContext.h"

namespace WaveNs
{

WaveLinearSequencerContextForShutdownPhase::WaveLinearSequencerContextForShutdownPhase(WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveAsynchronousContext,pWaveElement,pSteps,numberOfSteps)
{
}

WaveLinearSequencerContextForShutdownPhase::~WaveLinearSequencerContextForShutdownPhase()
{
}

void  WaveLinearSequencerContextForShutdownPhase::setBackendMap(const map<string,UnifiedClientBackendDetails*>  &backendMap)
{
    m_backendMap = backendMap;
}
 
map<string,UnifiedClientBackendDetails*>  WaveLinearSequencerContextForShutdownPhase::getBackendMap() const
{
    return(m_backendMap);
}

}
