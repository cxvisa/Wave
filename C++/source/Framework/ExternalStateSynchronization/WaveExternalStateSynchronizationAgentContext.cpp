/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/ExternalStateSynchronization/WaveExternalStateSynchronizationAgentContext.h"

namespace WaveNs
{

WaveExternalStateSynchronizationAgentContext::WaveExternalStateSynchronizationAgentContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveSynchronousLinearSequencerContext (pWaveAsynchronousContext, pWaveElement, pSteps, numberOfSteps)
{
}

WaveExternalStateSynchronizationAgentContext::~WaveExternalStateSynchronizationAgentContext ()
{
}

vector<WaveServiceId> &WaveExternalStateSynchronizationAgentContext::getEnabledServices ()
{
    return (m_enabledServices);
}

}
