/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#include "Framework/DistributedLog/DistributedLogSynchronousLinearSequencerContext.h"

namespace WaveNs
{

DistributedLogSynchronousLinearSequencerContext::DistributedLogSynchronousLinearSequencerContext (PrismMessage *pPrismMessage, PrismElement *pPrismElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismSynchronousLinearSequencerContext (pPrismMessage, pPrismElement, pSteps, numberOfSteps),
    m_numberOfLogEntries (0)
{
}

DistributedLogSynchronousLinearSequencerContext::DistributedLogSynchronousLinearSequencerContext (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismSynchronousLinearSequencerContext (pPrismAsynchronousContext, pPrismElement, pSteps, numberOfSteps),
    m_numberOfLogEntries (0)
{
}

DistributedLogSynchronousLinearSequencerContext::~DistributedLogSynchronousLinearSequencerContext ()
{
}

UI64 DistributedLogSynchronousLinearSequencerContext::getNumberOfLogEntries () const
{
    return (m_numberOfLogEntries);
}

void DistributedLogSynchronousLinearSequencerContext::setNumberOfLogEntries (const UI64 &numberOfLogEntries)
{
    m_numberOfLogEntries = numberOfLogEntries;
}

}
