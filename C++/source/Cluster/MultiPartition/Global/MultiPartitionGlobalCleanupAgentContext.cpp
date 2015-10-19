/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayaraman Iyer                                               *
 ***************************************************************************/

#include "Cluster/MultiPartition/Global/MultiPartitionGlobalCleanupAgentContext.h"

namespace WaveNs
{

MultiPartitionGlobalCleanupAgentContext::MultiPartitionGlobalCleanupAgentContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveSynchronousLinearSequencerContext (pWaveAsynchronousContext, pWaveElement, pSteps, numberOfSteps)
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
