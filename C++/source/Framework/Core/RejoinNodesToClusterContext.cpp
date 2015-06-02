/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/RejoinNodesToClusterContext.h"

namespace WaveNs
{

RejoinNodesToClusterContext::RejoinNodesToClusterContext (PrismMessage *pPrismMessage, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : DeleteNodesFromClusterContext (pPrismMessage, pPrismElement, pSteps, numberOfSteps)
{
}

RejoinNodesToClusterContext::~RejoinNodesToClusterContext ()
{
}

}
