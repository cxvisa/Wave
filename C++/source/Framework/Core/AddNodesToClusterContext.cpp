/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/AddNodesToClusterContext.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"

namespace WaveNs
{

AddNodesToClusterContext::AddNodesToClusterContext (WaveMessage *pWaveMessage, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : CreateClusterWithNodesContext (pWaveMessage, pPrismElement, pSteps, numberOfSteps)
{
}

AddNodesToClusterContext::~AddNodesToClusterContext ()
{
}

}
