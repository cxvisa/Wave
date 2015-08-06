/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/ConfigReplayEnd/ConfigReplayEndAgentContext.h"

namespace WaveNs
{

ConfigReplayEndAgentContext::ConfigReplayEndAgentContext (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismSynchronousLinearSequencerContext (pPrismAsynchronousContext, pWaveElement, pSteps, numberOfSteps)
{
}

ConfigReplayEndAgentContext::~ConfigReplayEndAgentContext ()
{
}

vector<WaveServiceId> &ConfigReplayEndAgentContext::getEnabledServices ()
{
    return (m_enabledServices);
}

}
