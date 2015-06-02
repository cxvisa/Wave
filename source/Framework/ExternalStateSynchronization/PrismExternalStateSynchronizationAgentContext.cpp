/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/ExternalStateSynchronization/PrismExternalStateSynchronizationAgentContext.h"

namespace WaveNs
{

PrismExternalStateSynchronizationAgentContext::PrismExternalStateSynchronizationAgentContext (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismSynchronousLinearSequencerContext (pPrismAsynchronousContext, pPrismElement, pSteps, numberOfSteps)
{
}

PrismExternalStateSynchronizationAgentContext::~PrismExternalStateSynchronizationAgentContext ()
{
}

vector<PrismServiceId> &PrismExternalStateSynchronizationAgentContext::getEnabledServices ()
{
    return (m_enabledServices);
}

}
