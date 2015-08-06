/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Timer/Test/FrameworkTimerTestContexts.h"

namespace WaveNs
{

FrameworkTimerTestContext::FrameworkTimerTestContext (WaveMessage *pWaveMessage, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismLinearSequencerContext (pWaveMessage, pPrismElement, pSteps, numberOfSteps),
      m_numberOfFailures (0)
{
}

FrameworkTimerTestContext::~FrameworkTimerTestContext ()
{
}

UI32 FrameworkTimerTestContext::getNumberOfFailures ()
{
    return (m_numberOfFailures);
}

void FrameworkTimerTestContext::setNumberOfFailures (UI32 numberOfFailures)
{
    m_numberOfFailures = numberOfFailures;
}

void FrameworkTimerTestContext::incrementNumberOfFailures ()
{
    m_numberOfFailures++;
}

void FrameworkTimerTestContext::incrementNumberOfFailures (UI32 numberOfFailures)
{
    m_numberOfFailures += numberOfFailures;
}

}
