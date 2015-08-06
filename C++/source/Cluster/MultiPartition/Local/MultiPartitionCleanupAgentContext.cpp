/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayaraman Iyer                                               *
 ***************************************************************************/

#include "Cluster/MultiPartition/Local/MultiPartitionCleanupAgentContext.h"

namespace WaveNs
{

MultiPartitionCleanupAgentContext::MultiPartitionCleanupAgentContext (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismSynchronousLinearSequencerContext (pPrismAsynchronousContext, pWaveElement, pSteps, numberOfSteps)
{
}

MultiPartitionCleanupAgentContext::~MultiPartitionCleanupAgentContext ()
{
}

vector<WaveServiceId> &MultiPartitionCleanupAgentContext::getEnabledServices ()
{
    return (m_enabledServices);
}

}
