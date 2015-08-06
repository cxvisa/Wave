/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Shutdown/PrismShutdownAgentContext.h"

namespace WaveNs
{

PrismShutdownAgentContext::PrismShutdownAgentContext (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismSynchronousLinearSequencerContext (pPrismAsynchronousContext, pPrismElement, pSteps, numberOfSteps)
{
}

PrismShutdownAgentContext::~PrismShutdownAgentContext ()
{
}

vector<WaveServiceId> &PrismShutdownAgentContext::getEnabledServices ()
{
    return (m_enabledServices);
}

}
