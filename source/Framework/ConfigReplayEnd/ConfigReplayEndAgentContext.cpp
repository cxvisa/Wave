/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/ConfigReplayEnd/ConfigReplayEndAgentContext.h"

namespace WaveNs
{

ConfigReplayEndAgentContext::ConfigReplayEndAgentContext (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismSynchronousLinearSequencerContext (pPrismAsynchronousContext, pPrismElement, pSteps, numberOfSteps)
{
}

ConfigReplayEndAgentContext::~ConfigReplayEndAgentContext ()
{
}

vector<PrismServiceId> &ConfigReplayEndAgentContext::getEnabledServices ()
{
    return (m_enabledServices);
}

}
