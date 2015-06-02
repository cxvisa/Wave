/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Cluster/Test/ClusterTestContexts.h"

namespace WaveNs
{

ClusterTestContext::ClusterTestContext (PrismMessage *pPrismMessage, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismLinearSequencerContext (pPrismMessage, pPrismElement, pSteps, numberOfSteps),
      m_numberOfFailures (0)
{
}

ClusterTestContext::~ClusterTestContext ()
{
}

UI32 ClusterTestContext::getNumberOfFailures ()
{
    return (m_numberOfFailures);
}

void ClusterTestContext::setNumberOfFailures (UI32 numberOfFailures)
{
    m_numberOfFailures = numberOfFailures;
}

void ClusterTestContext::incrementNumberOfFailures ()
{
    m_numberOfFailures++;
}

void ClusterTestContext::incrementNumberOfFailures (UI32 numberOfFailures)
{
    m_numberOfFailures += numberOfFailures;
}

}
