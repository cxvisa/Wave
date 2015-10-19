/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/WaveFrameworkInitializeWorkerStartServicesContext.h"

namespace WaveNs
{

WaveFrameworkInitializeWorkerStartServicesContext::WaveFrameworkInitializeWorkerStartServicesContext (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismSynchronousLinearSequencerContext (pPrismAsynchronousContext, pWaveElement, pSteps, numberOfSteps),
      m_prismBootMode                (WAVE_BOOT_FIRST_TIME),
      m_waveBootPhase                (WAVE_BOOT_PHASE_ALL_PHASES),
      m_pPrismBootAgent              (NULL),
      m_isSchemaChangedOnFwdl        (false),
      m_isSchemaUpgradedSuccessfully (false)
{
}

WaveFrameworkInitializeWorkerStartServicesContext::~WaveFrameworkInitializeWorkerStartServicesContext ()
{
    m_pPrismBootAgent = NULL;
}

PrismBootAgent *WaveFrameworkInitializeWorkerStartServicesContext::getPPrismBootAgent ()
{
    return (m_pPrismBootAgent);
}

void WaveFrameworkInitializeWorkerStartServicesContext::setPPrismBootAgent (PrismBootAgent *pPrismBootAgent)
{
    m_pPrismBootAgent = pPrismBootAgent;
}

PrismBootMode WaveFrameworkInitializeWorkerStartServicesContext::getPrismBootMode () const
{
    return (m_prismBootMode);
}

void WaveFrameworkInitializeWorkerStartServicesContext::setPrismBootMode (PrismBootMode prismBootMode)
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
