/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Cluster/Local/HeartBeat/HeartBeatFailureAgentContext.h"

namespace WaveNs
{

HeartBeatFailureAgentContext::HeartBeatFailureAgentContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveSynchronousLinearSequencerContext (pWaveAsynchronousContext, pWaveElement, pSteps, numberOfSteps)
{
}

HeartBeatFailureAgentContext::~HeartBeatFailureAgentContext ()
{
}

vector<WaveServiceId> &HeartBeatFailureAgentContext::getEnabledServices ()
{
    return (m_enabledServices);
}

}
