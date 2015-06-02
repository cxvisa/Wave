/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Amit Agrawal                                                 *
 ***************************************************************************/

#include "Framework/Postboot/PrismPostbootAgentContext.h"

namespace WaveNs
{

PrismPostbootAgentContext::PrismPostbootAgentContext (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismSynchronousLinearSequencerContext (pPrismAsynchronousContext, pPrismElement, pSteps, numberOfSteps)
{
}

PrismPostbootAgentContext::~PrismPostbootAgentContext ()
{
}

vector<PrismServiceId> &PrismPostbootAgentContext::getEnabledServices ()
{
    return (m_enabledServices);
}

}
