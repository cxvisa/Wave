/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayaraman Iyer                                               *
 ***************************************************************************/

#include "Cluster/MultiPartition/Global/MultiPartitionGlobalCleanupAgentContext.h"

namespace WaveNs
{

MultiPartitionGlobalCleanupAgentContext::MultiPartitionGlobalCleanupAgentContext (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismSynchronousLinearSequencerContext (pPrismAsynchronousContext, pPrismElement, pSteps, numberOfSteps)
{
}

MultiPartitionGlobalCleanupAgentContext::~MultiPartitionGlobalCleanupAgentContext ()
{
}

vector<PrismServiceId> &MultiPartitionGlobalCleanupAgentContext::getEnabledServices ()
{
    return (m_enabledServices);
}

}
