/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/SlotFailover/SlotFailoverAgentContext.h"

namespace WaveNs
{

SlotFailoverAgentContext::SlotFailoverAgentContext (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismSynchronousLinearSequencerContext (pPrismAsynchronousContext, pWaveElement, pSteps, numberOfSteps)
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
