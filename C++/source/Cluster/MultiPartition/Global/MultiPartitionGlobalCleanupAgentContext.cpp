/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayaraman Iyer                                               *
 ***************************************************************************/

#include "Cluster/MultiPartition/Global/MultiPartitionGlobalCleanupAgentContext.h"

namespace WaveNs
{

MultiPartitionGlobalCleanupAgentContext::MultiPartitionGlobalCleanupAgentContext (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismSynchronousLinearSequencerContext (pPrismAsynchronousContext, pWaveElement, pSteps, numberOfSteps)
{
}

MultiPartitionGlobalCleanupAgentContext::~MultiPartitionGlobalCleanupAgentContext ()
{
}

vector<WaveServiceId> &MultiPartitionGlobalCleanupAgentContext::getEnabledServices ()
{
    return (m_enabledServices);
}

}
