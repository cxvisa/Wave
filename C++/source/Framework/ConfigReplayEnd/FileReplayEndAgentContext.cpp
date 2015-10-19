/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/ConfigReplayEnd/FileReplayEndAgentContext.h"

namespace WaveNs
{

FileReplayEndAgentContext::FileReplayEndAgentContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveSynchronousLinearSequencerContext (pWaveAsynchronousContext, pWaveElement, pSteps, numberOfSteps)
{
}

FileReplayEndAgentContext::~FileReplayEndAgentContext ()
{
}

vector<WaveServiceId> &FileReplayEndAgentContext::getEnabledServices ()
{
    return (m_enabledServices);
}

}
