/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Shutdown/WaveFinalizeWorker.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Core/WaveFinalizeWorkerShutdownServicesContext.h"
#include "Framework/Shutdown/WaveSecondaryNodeRejoinShutdownAgent.h"
#include "Framework/Shutdown/WaveSecondaryNodeConfigureShutdownAgent.h"

namespace WaveNs
{

WaveFinalizeWorker::WaveFinalizeWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager),
      m_pWaveShutdownAgent (NULL)  
{
}

WaveFinalizeWorker::~WaveFinalizeWorker ()
{
   m_pWaveShutdownAgent = NULL;
}

ResourceId WaveFinalizeWorker::shutdownWaveServices (const WaveShutdownMode &prismShutdownMode)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFinalizeWorker::shutdownWaveServices : Entering ...");

    WaveSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFinalizeWorker::chooseAShutdownAgentStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFinalizeWorker::runTheShutdownAgentStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFinalizeWorker::destroyAShutdownAgentStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFinalizeWorker::prismSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFinalizeWorker::prismSynchronousLinearSequencerFailedStep),
    };

    WaveFinalizeWorkerShutdownServicesContext *pWaveFinalizeWorkerShutdownServicesContext = new WaveFinalizeWorkerShutdownServicesContext (reinterpret_cast<WaveAsynchronousContext *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pWaveFinalizeWorkerShutdownServicesContext->setWaveShutdownMode (prismShutdownMode);

    ResourceId status = pWaveFinalizeWorkerShutdownServicesContext->execute ();

    return (status);
}

ResourceId WaveFinalizeWorker::chooseAShutdownAgentStep (WaveFinalizeWorkerShutdownServicesContext *pWaveFinalizeWorkerShutdownServicesContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFinalizeWorker::chooseAShutdownAgentStep : Entering ...");

    FrameworkSequenceGenerator &frameworkSequenceGenerator = WaveFrameworkObjectManager::getCurrentFrameworkSequenceGenerator ();
    WaveShutdownMode           prismShutdownMode          = pWaveFinalizeWorkerShutdownServicesContext->getWaveShutdownMode ();

    if ((WAVE_SHUTDOWN_SECONDARY_CONFIGURE == prismShutdownMode) || (WAVE_SHUTDOWN_STANDBY_CONFIGURE == prismShutdownMode))
    {
        m_pWaveShutdownAgent = new WaveSecondaryNodeConfigureShutdownAgent (m_pWaveObjectManager, frameworkSequenceGenerator);
    }
    else if ((WAVE_SHUTDOWN_SECONDARY_REJOIN == prismShutdownMode) || (WAVE_SHUTDOWN_SECONDARY_ROLLBACK == prismShutdownMode))
    {
        m_pWaveShutdownAgent = new WaveSecondaryNodeRejoinShutdownAgent (m_pWaveObjectManager, frameworkSequenceGenerator);
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, string ("WaveFinalizeWorker::chooseAShutdownAgentStep : Unknown Wave Shutdown Mode : ") + (UI32) prismShutdownMode);
        waveAssert (false, __FILE__, __LINE__);
    }

    waveAssert (NULL != m_pWaveShutdownAgent, __FILE__, __LINE__);

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveFinalizeWorker::runTheShutdownAgentStep (WaveFinalizeWorkerShutdownServicesContext *pWaveFinalizeWorkerShutdownServicesContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFinalizeWorker::runTheShutdownAgentStep : Entering ...");

    ResourceId status = m_pWaveShutdownAgent->execute ();

    return (status);
}

ResourceId WaveFinalizeWorker::destroyAShutdownAgentStep (WaveFinalizeWorkerShutdownServicesContext *pWaveFinalizeWorkerShutdownServicesContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFinalizeWorker::destroyAShutdownAgentStep : Entering ...");

    if (NULL != m_pWaveShutdownAgent)
    {
        delete m_pWaveShutdownAgent;
    }

    m_pWaveShutdownAgent =  NULL;

    return (WAVE_MESSAGE_SUCCESS);
}

}
