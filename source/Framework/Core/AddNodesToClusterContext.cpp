/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/AddNodesToClusterContext.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"

namespace WaveNs
{

AddNodesToClusterContext::AddNodesToClusterContext (PrismMessage *pPrismMessage, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : CreateClusterWithNodesContext (pPrismMessage, pPrismElement, pSteps, numberOfSteps)
{
}

AddNodesToClusterContext::~AddNodesToClusterContext ()
{
}

}
