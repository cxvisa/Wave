/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Amit Agrawal                                                 *
 ***************************************************************************/

#include "Framework/Postboot/WavePostbootAgentContext.h"

namespace WaveNs
{

WavePostbootAgentContext::WavePostbootAgentContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveSynchronousLinearSequencerContext (pWaveAsynchronousContext, pWaveElement, pSteps, numberOfSteps)
{
}

WavePostbootAgentContext::~WavePostbootAgentContext ()
{
}

vector<WaveServiceId> &WavePostbootAgentContext::getEnabledServices ()
{
    return (m_enabledServices);
}

}
