/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Cluster/Local/HeartBeat/HeartBeatFailureAgentContext.h"

namespace WaveNs
{

HeartBeatFailureAgentContext::HeartBeatFailureAgentContext (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismSynchronousLinearSequencerContext (pPrismAsynchronousContext, pPrismElement, pSteps, numberOfSteps)
{
}

HeartBeatFailureAgentContext::~HeartBeatFailureAgentContext ()
{
}

vector<PrismServiceId> &HeartBeatFailureAgentContext::getEnabledServices ()
{
    return (m_enabledServices);
}

}
