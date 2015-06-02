/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/PrismFrameworkInitializeWorkerStartServicesContext.h"

namespace WaveNs
{

PrismFrameworkInitializeWorkerStartServicesContext::PrismFrameworkInitializeWorkerStartServicesContext (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismSynchronousLinearSequencerContext (pPrismAsynchronousContext, pPrismElement, pSteps, numberOfSteps),
      m_prismBootMode                (WAVE_BOOT_FIRST_TIME),
      m_waveBootPhase                (WAVE_BOOT_PHASE_ALL_PHASES),
      m_pPrismBootAgent              (NULL),
      m_isSchemaChangedOnFwdl        (false),
      m_isSchemaUpgradedSuccessfully (false)
{
}

PrismFrameworkInitializeWorkerStartServicesContext::~PrismFrameworkInitializeWorkerStartServicesContext ()
{
    m_pPrismBootAgent = NULL;
}

PrismBootAgent *PrismFrameworkInitializeWorkerStartServicesContext::getPPrismBootAgent ()
{
    return (m_pPrismBootAgent);
}

void PrismFrameworkInitializeWorkerStartServicesContext::setPPrismBootAgent (PrismBootAgent *pPrismBootAgent)
{
    m_pPrismBootAgent = pPrismBootAgent;
}

PrismBootMode PrismFrameworkInitializeWorkerStartServicesContext::getPrismBootMode () const
{
    return (m_prismBootMode);
}

void PrismFrameworkInitializeWorkerStartServicesContext::setPrismBootMode (PrismBootMode prismBootMode)
{
    m_prismBootMode = prismBootMode;
}

WaveBootPhase PrismFrameworkInitializeWorkerStartServicesContext::getWaveBootPhase () const
{
    return (m_waveBootPhase);
}

void PrismFrameworkInitializeWorkerStartServicesContext::setWaveBootPhase (const WaveBootPhase &waveBootPhase)
{
    m_waveBootPhase = waveBootPhase;
}

bool PrismFrameworkInitializeWorkerStartServicesContext::isSchemaChangedOnFwdl () const
{
    return (m_isSchemaChangedOnFwdl);
}

void PrismFrameworkInitializeWorkerStartServicesContext::setSchemaChangedOnFwdl (bool hasChanged)
{
    m_isSchemaChangedOnFwdl = hasChanged;
}

bool PrismFrameworkInitializeWorkerStartServicesContext::getIsSchemaUpgradedSuccessfully () const
{
    return (m_isSchemaUpgradedSuccessfully);
}

void PrismFrameworkInitializeWorkerStartServicesContext::setIsSchemaUpgradedSuccessfully (const bool &isSchemaUpgradedSuccessfully)
{
    m_isSchemaUpgradedSuccessfully = isSchemaUpgradedSuccessfully;
}

}
