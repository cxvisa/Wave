/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/AddNodesToClusterContext.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"

namespace WaveNs
{

AddNodesToClusterContext::AddNodesToClusterContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : CreateClusterWithNodesContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps)
{
}

AddNodesToClusterContext::~AddNodesToClusterContext ()
{
}

}
