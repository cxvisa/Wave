/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/ConfigReplayEnd/FileReplayEndAgentContext.h"

namespace WaveNs
{

FileReplayEndAgentContext::FileReplayEndAgentContext (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismSynchronousLinearSequencerContext (pPrismAsynchronousContext, pPrismElement, pSteps, numberOfSteps)
{
}

FileReplayEndAgentContext::~FileReplayEndAgentContext ()
{
}

vector<WaveServiceId> &FileReplayEndAgentContext::getEnabledServices ()
{
    return (m_enabledServices);
}

}
