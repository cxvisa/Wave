/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Boot/SecondaryNodeConfigureWaveBootAgent.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Core/ApplicationSpecificServices.h"

namespace WaveNs
{

SecondaryNodeConfigureWaveBootAgent::SecondaryNodeConfigureWaveBootAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : WaveBootAgent (pWaveObjectManager, currentFrameworkSequenceGenerator),
      m_waveBootPhase (WAVE_BOOT_PHASE_ALL_PHASES)
{
}

SecondaryNodeConfigureWaveBootAgent::~SecondaryNodeConfigureWaveBootAgent ()
{
}

ResourceId SecondaryNodeConfigureWaveBootAgent::execute (const WaveBootPhase &waveBootPhase)
{
    m_waveBootPhase = waveBootPhase;

    if (WAVE_BOOT_PHASE_ALL_PHASES == waveBootPhase)
    {
        trace (TRACE_LEVEL_DEBUG, "SecondaryNodeConfigureWaveBootAgent::execute : All Phases.");

        WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
        {
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeConfigureWaveBootAgent::initializeWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeConfigureWaveBootAgent::enableWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeConfigureWaveBootAgent::listenForEventsWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeConfigureWaveBootAgent::installWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeConfigureWaveBootAgent::bootWaveServicesDuringPrePhaseStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeConfigureWaveBootAgent::initializeLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeConfigureWaveBootAgent::enableWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeConfigureWaveBootAgent::listenForEventsWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeConfigureWaveBootAgent::installLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeConfigureWaveBootAgent::bootWaveServicesStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeConfigureWaveBootAgent::prismSynchronousLinearSequencerSucceededStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeConfigureWaveBootAgent::prismSynchronousLinearSequencerFailedStep)
        };

        WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext = new WaveSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

        ResourceId status = pWaveSynchronousLinearSequencerContext->execute ();

        return (status);
    }
    else if (WAVE_BOOT_PHASE_PRE_PHASE == waveBootPhase)
    {
        trace (TRACE_LEVEL_DEBUG, "SecondaryNodeConfigureWaveBootAgent::execute : Pre Phase.");

        WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
        {
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeConfigureWaveBootAgent::initializeWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeConfigureWaveBootAgent::enableWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeConfigureWaveBootAgent::listenForEventsWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeConfigureWaveBootAgent::installWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeConfigureWaveBootAgent::bootWaveServicesDuringPrePhaseStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeConfigureWaveBootAgent::prismSynchronousLinearSequencerSucceededStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeConfigureWaveBootAgent::prismSynchronousLinearSequencerFailedStep)
        };

        WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext = new WaveSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

        ResourceId status = pWaveSynchronousLinearSequencerContext->execute ();

        return (status);
    }
    else if ((WAVE_BOOT_PHASE_POST_PHASE == waveBootPhase) || WAVE_BOOT_PHASE_AFTER_POST_PHASE == waveBootPhase)
    {
        if (WAVE_BOOT_PHASE_POST_PHASE == waveBootPhase)
        {
            trace (TRACE_LEVEL_DEBUG, "SecondaryNodeConfigureWaveBootAgent::execute : Post Phase.");
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "SecondaryNodeConfigureWaveBootAgent::execute : Phase 3");
        }

        WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
        {
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeConfigureWaveBootAgent::initializeLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeConfigureWaveBootAgent::enableWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeConfigureWaveBootAgent::listenForEventsWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeConfigureWaveBootAgent::installLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeConfigureWaveBootAgent::bootWaveServicesStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeConfigureWaveBootAgent::prismSynchronousLinearSequencerSucceededStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeConfigureWaveBootAgent::prismSynchronousLinearSequencerFailedStep)
        };

        WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext = new WaveSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

        ResourceId status = pWaveSynchronousLinearSequencerContext->execute ();

        return (status);
    }

    return (WAVE_MESSAGE_SUCCESS);
}

bool SecondaryNodeConfigureWaveBootAgent::isAPersistentBoot ()
{
    return (true);
}

bool SecondaryNodeConfigureWaveBootAgent::isToBeExcludedForEnableAndBoot (const WaveServiceId& waveServiceId)
{
    if (((WaveFrameworkObjectManager::getWaveServiceId               ()) == waveServiceId) ||
        (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

bool SecondaryNodeConfigureWaveBootAgent::willBeAPrimaryLocation ()
{
    return (false);
}

bool SecondaryNodeConfigureWaveBootAgent::isToBeExcludedFromInstallDuringPrePhase (const WaveServiceId &waveServiceId)
{
    if ((waveServiceId == (DatabaseObjectManager::getWaveServiceId ())) ||
        (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

bool SecondaryNodeConfigureWaveBootAgent::isToBeExcludedFromInstall (const WaveServiceId &waveServiceId)
{
    if (((WaveFrameworkObjectManager::getWaveServiceId               ()) == waveServiceId) ||
        (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

bool SecondaryNodeConfigureWaveBootAgent::isToBeExcludedFromInitializeDuringPrePhase (const WaveServiceId &waveServiceId)
{
    if (((WaveFrameworkObjectManager::getWaveServiceId               ()) == waveServiceId) ||
        (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

bool SecondaryNodeConfigureWaveBootAgent::isToBeExcludedFromInitializePhase (const WaveServiceId &waveServiceId)
{
    if (((WaveFrameworkObjectManager::getWaveServiceId               ()) == waveServiceId) ||
        (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

bool SecondaryNodeConfigureWaveBootAgent::isToBeExcludedFromCurrentBootPhase (WaveServiceId waveServiceId)
{

    ApplicationSpecificServices *pApplicationSpecificServices = ApplicationSpecificServices::getInstance ();

    if ((WAVE_BOOT_PHASE_POST_PHASE == m_waveBootPhase) && (true == pApplicationSpecificServices->isApplicationSpecificServiceId (waveServiceId)))
    {
        return (true);
    }
    else if ((WAVE_BOOT_PHASE_AFTER_POST_PHASE == m_waveBootPhase) && (false == pApplicationSpecificServices->isApplicationSpecificServiceId (waveServiceId)))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

WaveBootReason SecondaryNodeConfigureWaveBootAgent::getReason () const
{
    return (WAVE_BOOT_SECONDARY_NODE_CONFIGURE_BOOT);
}

}
