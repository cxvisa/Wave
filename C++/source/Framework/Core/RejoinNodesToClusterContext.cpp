/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/RejoinNodesToClusterContext.h"

namespace WaveNs
{

RejoinNodesToClusterContext::RejoinNodesToClusterContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : DeleteNodesFromClusterContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps)
{
}

RejoinNodesToClusterContext::~RejoinNodesToClusterContext ()
{
}

}
