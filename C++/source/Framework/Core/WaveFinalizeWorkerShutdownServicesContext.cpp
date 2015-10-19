/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Geetha Aparna                                                *
 ***************************************************************************/

#include "Framework/Core/WaveFinalizeWorkerShutdownServicesContext.h"

namespace WaveNs
{

WaveFinalizeWorkerShutdownServicesContext::WaveFinalizeWorkerShutdownServicesContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveSynchronousLinearSequencerContext (pWaveAsynchronousContext, pWaveElement, pSteps, numberOfSteps),
      m_waveShutdownMode (WAVE_SHUTDOWN_SECONDARY_CONFIGURE)
{
}

WaveFinalizeWorkerShutdownServicesContext::~WaveFinalizeWorkerShutdownServicesContext ()
{
}

WaveShutdownMode WaveFinalizeWorkerShutdownServicesContext::getWaveShutdownMode () const
{
    return (m_waveShutdownMode);
}

void WaveFinalizeWorkerShutdownServicesContext::setWaveShutdownMode (const WaveShutdownMode &waveShutdownMode)
{
    m_waveShutdownMode = waveShutdownMode;
}

}

