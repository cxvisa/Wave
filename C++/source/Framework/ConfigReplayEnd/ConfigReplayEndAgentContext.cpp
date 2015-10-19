/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/ConfigReplayEnd/ConfigReplayEndAgentContext.h"

namespace WaveNs
{

ConfigReplayEndAgentContext::ConfigReplayEndAgentContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveSynchronousLinearSequencerContext (pWaveAsynchronousContext, pWaveElement, pSteps, numberOfSteps)
{
}

ConfigReplayEndAgentContext::~ConfigReplayEndAgentContext ()
{
}

vector<WaveServiceId> &ConfigReplayEndAgentContext::getEnabledServices ()
{
    return (m_enabledServices);
}

}
