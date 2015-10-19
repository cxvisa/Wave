/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Mithun B S                                                   *
 ***************************************************************************/

#include "Framework/Boot/RecoverWaveBootAgent.h"
#include "Framework/Boot/FirstTimeWaveBootAgent.h"
#include "Framework/Timer/TimerSignalObjectManager.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/LocationManagement/Location.h"

namespace WaveNs
{

RecoverWaveBootAgent::RecoverWaveBootAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : FirstTimeWaveBootAgent (pWaveObjectManager, currentFrameworkSequenceGenerator),
      m_waveBootPhase (WAVE_BOOT_PHASE_PRE_PHASE)
{
}

RecoverWaveBootAgent::~RecoverWaveBootAgent ()
{
}

ResourceId RecoverWaveBootAgent::execute (const WaveBootPhase &waveBootPhase)
{
    m_waveBootPhase = waveBootPhase;

    if (WAVE_BOOT_PHASE_PRE_PHASE == waveBootPhase)
    {
        WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
        {
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&RecoverWaveBootAgent::shutdownDatabaseStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&RecoverWaveBootAgent::updateFrameworkConfigurationToDefaultStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&RecoverWaveBootAgent::initializeWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&RecoverWaveBootAgent::enableWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&RecoverWaveBootAgent::listenForEventsWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&RecoverWaveBootAgent::installWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&RecoverWaveBootAgent::bootWaveServicesDuringPrePhaseStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&RecoverWaveBootAgent::waveSynchronousLinearSequencerSucceededStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&RecoverWaveBootAgent::waveSynchronousLinearSequencerFailedStep)
        };

        WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext = new WaveSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

        ResourceId status = pWaveSynchronousLinearSequencerContext->execute ();

        return (status);
    }
    else if (WAVE_BOOT_PHASE_POST_PHASE == waveBootPhase)
    {
        WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
        {
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&RecoverWaveBootAgent::initializeLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&RecoverWaveBootAgent::enableLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&RecoverWaveBootAgent::listenForEventsLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&RecoverWaveBootAgent::installLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&RecoverWaveBootAgent::bootLocalWaveServicesStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&RecoverWaveBootAgent::initializeGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&RecoverWaveBootAgent::enableGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&RecoverWaveBootAgent::listenForEventsGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&RecoverWaveBootAgent::installGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&RecoverWaveBootAgent::bootGlobalWaveServicesStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&RecoverWaveBootAgent::saveWaveConfigurationStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&RecoverWaveBootAgent::waveSynchronousLinearSequencerSucceededStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&RecoverWaveBootAgent::waveSynchronousLinearSequencerFailedStep)
        };

        WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext = new WaveSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

        ResourceId status = pWaveSynchronousLinearSequencerContext->execute ();

        return (status);
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId RecoverWaveBootAgent::shutdownDatabaseStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    bool                                        isShutdownOnReboot  = false;
    DatabaseObjectManagerShutdownMessage       *pMessage            = new DatabaseObjectManagerShutdownMessage (isShutdownOnReboot);

    ResourceId status = sendSynchronously (pMessage, FrameworkToolKit::getThisLocationId ());

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, string ("RecoverWaveBootAgent::shutdownDatabaseStep : Could not send a message to stop Database Server: Status : ") + FrameworkToolKit::localize (status));
        return (status);
    }

    status = pMessage->getCompletionStatus ();

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, string ("RecoverWaveBootAgent::shutdownDatabaseStep : Could not stop Database Server: Status : ") + FrameworkToolKit::localize (status));
        return (status);
    }
    else
    {
        trace (TRACE_LEVEL_INFO, "Database Server Stopped");
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId RecoverWaveBootAgent::updateFrameworkConfigurationToDefaultStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    trace (TRACE_LEVEL_INFO, "RecoverWaveBootAgent::updateFrameworkConfigurationToDefaultStep: Reverting the cfg to default values as we go back to First Time boot.");

    WaveFrameworkObjectManager *pTemp         = WaveFrameworkObjectManager::getInstance ();
    pTemp->resetFrameworkConfigurationToDefault ();

    trace (TRACE_LEVEL_INFO, "RecoverWaveBootAgent::updateFrameworkConfigurationToDefaultStep: saving default configuration.");
    FrameworkToolKit::saveWaveConfiguration ();

    return (WAVE_MESSAGE_SUCCESS);
}

bool RecoverWaveBootAgent::isToBeExcludedFromInitializeDuringPrePhase (const WaveServiceId &waveServiceId)
{
    if ((TimerSignalObjectManager::getWaveServiceId               ()) == waveServiceId ||
        ((true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))) && (WAVE_BOOT_PHASE_PRE_PHASE == m_waveBootPhase)))
    {   
        return (true);
    }
    else
    {   
        return (false);
    }
}

bool RecoverWaveBootAgent::isToBeExcludedForEnableAndBoot (const WaveServiceId &waveServiceId)
{
    if ((TimerSignalObjectManager::getWaveServiceId               ()) == waveServiceId ||
        ((true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))) && (WAVE_BOOT_PHASE_PRE_PHASE == m_waveBootPhase)))
    {   
        return (true);
    }
    else
    {   
        return (false);
    }
}

bool RecoverWaveBootAgent::isToBeExcludedFromInstallDuringPrePhase (const WaveServiceId &waveServiceId)
{
    if ((TimerSignalObjectManager::getWaveServiceId               ()) == waveServiceId ||
        ((true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))) && (WAVE_BOOT_PHASE_PRE_PHASE == m_waveBootPhase)))
    {   
        return (true);
    }
    else
    {   
        return (false);
    }
}

}
