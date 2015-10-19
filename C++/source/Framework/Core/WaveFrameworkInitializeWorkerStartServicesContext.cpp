/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/WaveFrameworkInitializeWorkerStartServicesContext.h"

namespace WaveNs
{

WaveFrameworkInitializeWorkerStartServicesContext::WaveFrameworkInitializeWorkerStartServicesContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveSynchronousLinearSequencerContext (pWaveAsynchronousContext, pWaveElement, pSteps, numberOfSteps),
      m_prismBootMode                (WAVE_BOOT_FIRST_TIME),
      m_waveBootPhase                (WAVE_BOOT_PHASE_ALL_PHASES),
      m_pWaveBootAgent              (NULL),
      m_isSchemaChangedOnFwdl        (false),
      m_isSchemaUpgradedSuccessfully (false)
{
}

WaveFrameworkInitializeWorkerStartServicesContext::~WaveFrameworkInitializeWorkerStartServicesContext ()
{
    m_pWaveBootAgent = NULL;
}

WaveBootAgent *WaveFrameworkInitializeWorkerStartServicesContext::getPWaveBootAgent ()
{
    return (m_pWaveBootAgent);
}

void WaveFrameworkInitializeWorkerStartServicesContext::setPWaveBootAgent (WaveBootAgent *pWaveBootAgent)
{
    m_pWaveBootAgent = pWaveBootAgent;
}

WaveBootMode WaveFrameworkInitializeWorkerStartServicesContext::getWaveBootMode () const
{
    return (m_prismBootMode);
}

void WaveFrameworkInitializeWorkerStartServicesContext::setWaveBootMode (WaveBootMode prismBootMode)
{
    m_prismBootMode = prismBootMode;
}

WaveBootPhase WaveFrameworkInitializeWorkerStartServicesContext::getWaveBootPhase () const
{
    return (m_waveBootPhase);
}

void WaveFrameworkInitializeWorkerStartServicesContext::setWaveBootPhase (const WaveBootPhase &waveBootPhase)
{
    m_waveBootPhase = waveBootPhase;
}

bool WaveFrameworkInitializeWorkerStartServicesContext::isSchemaChangedOnFwdl () const
{
    return (m_isSchemaChangedOnFwdl);
}

void WaveFrameworkInitializeWorkerStartServicesContext::setSchemaChangedOnFwdl (bool hasChanged)
{
    m_isSchemaChangedOnFwdl = hasChanged;
}

bool WaveFrameworkInitializeWorkerStartServicesContext::getIsSchemaUpgradedSuccessfully () const
{
    return (m_isSchemaUpgradedSuccessfully);
}

void WaveFrameworkInitializeWorkerStartServicesContext::setIsSchemaUpgradedSuccessfully (const bool &isSchemaUpgradedSuccessfully)
{
    m_isSchemaUpgradedSuccessfully = isSchemaUpgradedSuccessfully;
}

}
