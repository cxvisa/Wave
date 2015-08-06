/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Shutdown/PrismFinalizeWorker.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"
#include "Framework/Core/PrismFinalizeWorkerShutdownServicesContext.h"
#include "Framework/Shutdown/PrismSecondaryNodeRejoinShutdownAgent.h"
#include "Framework/Shutdown/PrismSecondaryNodeConfigureShutdownAgent.h"

namespace WaveNs
{

PrismFinalizeWorker::PrismFinalizeWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager),
      m_pPrismShutdownAgent (NULL)  
{
}

PrismFinalizeWorker::~PrismFinalizeWorker ()
{
   m_pPrismShutdownAgent = NULL;
}

ResourceId PrismFinalizeWorker::shutdownPrismServices (const PrismShutdownMode &prismShutdownMode)
{
    trace (TRACE_LEVEL_DEVEL, "PrismFinalizeWorker::shutdownPrismServices : Entering ...");

    PrismSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismFinalizeWorker::chooseAShutdownAgentStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismFinalizeWorker::runTheShutdownAgentStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismFinalizeWorker::destroyAShutdownAgentStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismFinalizeWorker::prismSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismFinalizeWorker::prismSynchronousLinearSequencerFailedStep),
    };

    PrismFinalizeWorkerShutdownServicesContext *pPrismFinalizeWorkerShutdownServicesContext = new PrismFinalizeWorkerShutdownServicesContext (reinterpret_cast<PrismAsynchronousContext *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pPrismFinalizeWorkerShutdownServicesContext->setPrismShutdownMode (prismShutdownMode);

    ResourceId status = pPrismFinalizeWorkerShutdownServicesContext->execute ();

    return (status);
}

ResourceId PrismFinalizeWorker::chooseAShutdownAgentStep (PrismFinalizeWorkerShutdownServicesContext *pPrismFinalizeWorkerShutdownServicesContext)
{
    trace (TRACE_LEVEL_DEVEL, "PrismFinalizeWorker::chooseAShutdownAgentStep : Entering ...");

    FrameworkSequenceGenerator &frameworkSequenceGenerator = PrismFrameworkObjectManager::getCurrentFrameworkSequenceGenerator ();
    PrismShutdownMode           prismShutdownMode          = pPrismFinalizeWorkerShutdownServicesContext->getPrismShutdownMode ();

    if ((WAVE_SHUTDOWN_SECONDARY_CONFIGURE == prismShutdownMode) || (WAVE_SHUTDOWN_STANDBY_CONFIGURE == prismShutdownMode))
    {
        m_pPrismShutdownAgent = new PrismSecondaryNodeConfigureShutdownAgent (m_pWaveObjectManager, frameworkSequenceGenerator);
    }
    else if ((WAVE_SHUTDOWN_SECONDARY_REJOIN == prismShutdownMode) || (WAVE_SHUTDOWN_SECONDARY_ROLLBACK == prismShutdownMode))
    {
        m_pPrismShutdownAgent = new PrismSecondaryNodeRejoinShutdownAgent (m_pWaveObjectManager, frameworkSequenceGenerator);
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, string ("PrismFinalizeWorker::chooseAShutdownAgentStep : Unknown Prism Shutdown Mode : ") + (UI32) prismShutdownMode);
        waveAssert (false, __FILE__, __LINE__);
    }

    waveAssert (NULL != m_pPrismShutdownAgent, __FILE__, __LINE__);

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId PrismFinalizeWorker::runTheShutdownAgentStep (PrismFinalizeWorkerShutdownServicesContext *pPrismFinalizeWorkerShutdownServicesContext)
{
    trace (TRACE_LEVEL_DEVEL, "PrismFinalizeWorker::runTheShutdownAgentStep : Entering ...");

    ResourceId status = m_pPrismShutdownAgent->execute ();

    return (status);
}

ResourceId PrismFinalizeWorker::destroyAShutdownAgentStep (PrismFinalizeWorkerShutdownServicesContext *pPrismFinalizeWorkerShutdownServicesContext)
{
    trace (TRACE_LEVEL_DEVEL, "PrismFinalizeWorker::destroyAShutdownAgentStep : Entering ...");

    if (NULL != m_pPrismShutdownAgent)
    {
        delete m_pPrismShutdownAgent;
    }

    m_pPrismShutdownAgent =  NULL;

    return (WAVE_MESSAGE_SUCCESS);
}

}
