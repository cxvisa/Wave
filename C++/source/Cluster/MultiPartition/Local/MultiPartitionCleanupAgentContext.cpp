/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayaraman Iyer                                               *
 ***************************************************************************/

#include "Cluster/MultiPartition/Local/MultiPartitionCleanupAgentContext.h"

namespace WaveNs
{

MultiPartitionCleanupAgentContext::MultiPartitionCleanupAgentContext (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismSynchronousLinearSequencerContext (pPrismAsynchronousContext, pPrismElement, pSteps, numberOfSteps)
{
}

MultiPartitionCleanupAgentContext::~MultiPartitionCleanupAgentContext ()
{
}

vector<PrismServiceId> &MultiPartitionCleanupAgentContext::getEnabledServices ()
{
    return (m_enabledServices);
}

}
