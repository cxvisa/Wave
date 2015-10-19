/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#include "Framework/DistributedLog/DistributedLogSynchronousLinearSequencerContext.h"

namespace WaveNs
{

DistributedLogSynchronousLinearSequencerContext::DistributedLogSynchronousLinearSequencerContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveSynchronousLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps),
    m_numberOfLogEntries (0)
{
}

DistributedLogSynchronousLinearSequencerContext::DistributedLogSynchronousLinearSequencerContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveSynchronousLinearSequencerContext (pWaveAsynchronousContext, pWaveElement, pSteps, numberOfSteps),
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
