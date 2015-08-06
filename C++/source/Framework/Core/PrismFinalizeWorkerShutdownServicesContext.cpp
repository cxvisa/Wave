/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Geetha Aparna                                                *
 ***************************************************************************/

#include "Framework/Core/PrismFinalizeWorkerShutdownServicesContext.h"

namespace WaveNs
{

PrismFinalizeWorkerShutdownServicesContext::PrismFinalizeWorkerShutdownServicesContext (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismSynchronousLinearSequencerContext (pPrismAsynchronousContext, pWaveElement, pSteps, numberOfSteps),
      m_prismShutdownMode (WAVE_SHUTDOWN_SECONDARY_CONFIGURE)
{
}

PrismFinalizeWorkerShutdownServicesContext::~PrismFinalizeWorkerShutdownServicesContext ()
{
}

PrismShutdownMode PrismFinalizeWorkerShutdownServicesContext::getPrismShutdownMode () const
{
    return (m_prismShutdownMode);
}

void PrismFinalizeWorkerShutdownServicesContext::setPrismShutdownMode (const PrismShutdownMode &prismShutdownMode)
{
    m_prismShutdownMode = prismShutdownMode;
}

}

