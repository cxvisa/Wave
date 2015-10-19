/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Shutdown/WaveShutdownAgentContext.h"

namespace WaveNs
{

WaveShutdownAgentContext::WaveShutdownAgentContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveSynchronousLinearSequencerContext (pWaveAsynchronousContext, pWaveElement, pSteps, numberOfSteps)
{
}

WaveShutdownAgentContext::~WaveShutdownAgentContext ()
{
}

vector<WaveServiceId> &WaveShutdownAgentContext::getEnabledServices ()
{
    return (m_enabledServices);
}

}
