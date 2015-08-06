/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Amit Agrawal                                                 *
 ***************************************************************************/

#include "Framework/Postboot/PrismPostbootAgentContext.h"

namespace WaveNs
{

PrismPostbootAgentContext::PrismPostbootAgentContext (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismSynchronousLinearSequencerContext (pPrismAsynchronousContext, pWaveElement, pSteps, numberOfSteps)
{
}

PrismPostbootAgentContext::~PrismPostbootAgentContext ()
{
}

vector<WaveServiceId> &PrismPostbootAgentContext::getEnabledServices ()
{
    return (m_enabledServices);
}

}
