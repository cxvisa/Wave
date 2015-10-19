/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vadiraj C S                                                  *
 ***************************************************************************/

#include "Framework/Zeroize/WaveZeroizeAgentContext.h"

namespace WaveNs
{

WaveZeroizeAgentContext::WaveZeroizeAgentContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveSynchronousLinearSequencerContext (pWaveAsynchronousContext, pWaveElement, pSteps, numberOfSteps)
{
}

WaveZeroizeAgentContext::~WaveZeroizeAgentContext ()
{
}

vector<WaveServiceId> &WaveZeroizeAgentContext::getZeroizableServices ()
{
    return (m_zeroizableServices);
}

}
