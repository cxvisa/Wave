/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vadiraj C S                                                  *
 ***************************************************************************/

#include "Framework/Zeroize/PrismZeroizeAgentContext.h"

namespace WaveNs
{

PrismZeroizeAgentContext::PrismZeroizeAgentContext (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismSynchronousLinearSequencerContext (pPrismAsynchronousContext, pPrismElement, pSteps, numberOfSteps)
{
}

PrismZeroizeAgentContext::~PrismZeroizeAgentContext ()
{
}

vector<WaveServiceId> &PrismZeroizeAgentContext::getZeroizableServices ()
{
    return (m_zeroizableServices);
}

}
