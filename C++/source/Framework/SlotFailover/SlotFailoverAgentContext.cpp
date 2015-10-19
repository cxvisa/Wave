/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/SlotFailover/SlotFailoverAgentContext.h"

namespace WaveNs
{

SlotFailoverAgentContext::SlotFailoverAgentContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveSynchronousLinearSequencerContext (pWaveAsynchronousContext, pWaveElement, pSteps, numberOfSteps)
{
}

SlotFailoverAgentContext::~SlotFailoverAgentContext ()
{
}

vector<WaveServiceId> &SlotFailoverAgentContext::getEnabledServices ()
{
    return (m_enabledServices);
}

}
