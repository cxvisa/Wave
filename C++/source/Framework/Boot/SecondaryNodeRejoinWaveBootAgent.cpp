/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Aashish Akhouri                                    *
 ***************************************************************************/

#include "Framework/Boot/SecondaryNodeRejoinWaveBootAgent.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Core/ApplicationSpecificServices.h"
#include "Framework/Utils/FrameworkToolKit.h"

namespace WaveNs
{
/// Name
/// SecondaryNodeRejoinWaveBootAgent
/// Description
/// Constructor
/// Input
/// WaveObjectManager: Owner object manager
/// FrameworkSequenceGenerator: Sequence of services to be booted for 
/// rejoin in pre and post boot phase 
/// Output
/// none
/// Return
/// none
SecondaryNodeRejoinWaveBootAgent::SecondaryNodeRejoinWaveBootAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : WaveBootAgent (pWaveObjectManager, currentFrameworkSequenceGenerator),
      m_waveBootPhase (WAVE_BOOT_PHASE_ALL_PHASES)
{
}
/// Name
/// SecondaryNodeRejoinWaveBootAgent
/// Description
/// Destructor
/// Input
/// None
/// Output
/// none
/// Return
/// none
SecondaryNodeRejoinWaveBootAgent::~SecondaryNodeRejoinWaveBootAgent ()
{
}
/// Name
/// execute
/// Description
/// Calls the sequence of functions defines in the 
/// base class to execute the pre and post boot
/// Input
/// const WaveBootPhase : Pre(Phase1 of rejoin) or Post(Phase2 of rejoin)
/// Output
/// none
/// Return
/// none
ResourceId SecondaryNodeRejoinWaveBootAgent::execute (const WaveBootPhase &waveBootPhase)
{
    m_waveBootPhase = waveBootPhase;

    if (WAVE_BOOT_PHASE_PRE_PHASE == waveBootPhase)
    {
        trace (TRACE_LEVEL_DEBUG, "SecondaryNodeRejoinWaveBootAgent::execute : Pre Phase.");

        WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
        {
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeRejoinWaveBootAgent::initializeWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeRejoinWaveBootAgent::enableWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeRejoinWaveBootAgent::listenForEventsWaveServicesDuringPrePhaseStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeRejoinWaveBootAgent::bootWaveServicesDuringPrePhaseStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeRejoinWaveBootAgent::waveSynchronousLinearSequencerSucceededStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeRejoinWaveBootAgent::waveSynchronousLinearSequencerFailedStep)
        };

        WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext = new WaveSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

        ResourceId status = pWaveSynchronousLinearSequencerContext->execute ();

        return (status);
    }
    else if (WAVE_BOOT_PHASE_POST_PHASE == waveBootPhase)
    {
        trace (TRACE_LEVEL_INFO, "SecondaryNodeRejoinWaveBootAgent::execute : Post Phase.");

        WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
        {
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeRejoinWaveBootAgent::initializeLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeRejoinWaveBootAgent::enableWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeRejoinWaveBootAgent::listenForEventsWaveServicesStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeRejoinWaveBootAgent::bootWaveServicesStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeRejoinWaveBootAgent::waveSynchronousLinearSequencerSucceededStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeRejoinWaveBootAgent::waveSynchronousLinearSequencerFailedStep)
        };

        WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext = new WaveSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

        ResourceId status = pWaveSynchronousLinearSequencerContext->execute ();

        return (status);
    }
    else if (WAVE_BOOT_PHASE_AFTER_POST_PHASE == waveBootPhase)
    {
        trace (TRACE_LEVEL_INFO, "SecondaryNodeRejoinWaveBootAgent::execute : Phase 3");
        WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
        {
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeRejoinWaveBootAgent::initializeLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeRejoinWaveBootAgent::enableWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeRejoinWaveBootAgent::listenForEventsWaveServicesStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeRejoinWaveBootAgent::bootWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeRejoinWaveBootAgent::backendSyncUpStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeRejoinWaveBootAgent::waveSynchronousLinearSequencerSucceededStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeRejoinWaveBootAgent::waveSynchronousLinearSequencerFailedStep)
        };

        WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext = new WaveSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

        ResourceId status = pWaveSynchronousLinearSequencerContext->execute ();

        return (status);
    }

    return (WAVE_MESSAGE_SUCCESS);
}
/// Name
/// execute
/// Description
/// Whether rejoin boot is persistent: QUESTION: SAGAR??
/// Input
/// None
/// Output
/// none
/// Return
/// bool: 
bool SecondaryNodeRejoinWaveBootAgent::isAPersistentBoot ()
{
    return (true);
}

/// Name
/// isToBeExcludedForEnableAndBoot
/// Description
/// QUESTION:SAGAR
/// Input
/// const WaveServiceId
/// Output
/// none
/// Return
/// bool:
bool SecondaryNodeRejoinWaveBootAgent::isToBeExcludedFromInitializeDuringPrePhase (const WaveServiceId &waveServiceId)
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

bool SecondaryNodeRejoinWaveBootAgent::isToBeExcludedFromInitializePhase (const WaveServiceId &waveServiceId)
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

bool SecondaryNodeRejoinWaveBootAgent::isToBeExcludedForEnableAndBoot (const WaveServiceId& waveServiceId)
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
/// Name
/// willBeAPrimaryLocation
/// Description
/// This function will always return false because 
/// the rejoining node will not be a primary location.
/// Input
/// none
/// Output
/// none
/// Return
/// bool:Always false
bool SecondaryNodeRejoinWaveBootAgent::willBeAPrimaryLocation ()
{
    return (false);
}


bool SecondaryNodeRejoinWaveBootAgent::isToBeExcludedFromCurrentBootPhase (WaveServiceId waveServiceId)
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



/// Name
/// getReason
/// Description
/// Returns reason for boot , which is Rejoin
/// Input
/// none
/// Output
/// none
/// Return
/// WaveBootReason: Rejoin of secondary node

WaveBootReason SecondaryNodeRejoinWaveBootAgent::getReason () const
{
    return (WAVE_BOOT_SECONDARY_NODE_REJOIN_BOOT);
}

}
