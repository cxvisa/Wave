/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/ExternalStateSynchronization/PrismExternalStateSynchronizationAgentContext.h"

namespace WaveNs
{

PrismExternalStateSynchronizationAgentContext::PrismExternalStateSynchronizationAgentContext (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismSynchronousLinearSequencerContext (pPrismAsynchronousContext, pWaveElement, pSteps, numberOfSteps)
{
}

PrismExternalStateSynchronizationAgentContext::~PrismExternalStateSynchronizationAgentContext ()
{
}

vector<WaveServiceId> &PrismExternalStateSynchronizationAgentContext::getEnabledServices ()
{
    return (m_enabledServices);
}

}
