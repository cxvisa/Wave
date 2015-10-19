/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayaraman Iyer                                               *
 ***************************************************************************/

#include "Cluster/MultiPartition/Local/MultiPartitionCleanupAgentContext.h"

namespace WaveNs
{

MultiPartitionCleanupAgentContext::MultiPartitionCleanupAgentContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveSynchronousLinearSequencerContext (pWaveAsynchronousContext, pWaveElement, pSteps, numberOfSteps)
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
