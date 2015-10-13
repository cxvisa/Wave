/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Boot/SecondaryNodeConfigurePrismBootAgent.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Core/ApplicationSpecificServices.h"

namespace WaveNs
{

SecondaryNodeConfigurePrismBootAgent::SecondaryNodeConfigurePrismBootAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : PrismBootAgent (pWaveObjectManager, currentFrameworkSequenceGenerator),
      m_waveBootPhase (WAVE_BOOT_PHASE_ALL_PHASES)
{
}

SecondaryNodeConfigurePrismBootAgent::~SecondaryNodeConfigurePrismBootAgent ()
{
}

ResourceId SecondaryNodeConfigurePrismBootAgent::execute (const WaveBootPhase &waveBootPhase)
{
    m_waveBootPhase = waveBootPhase;

    if (WAVE_BOOT_PHASE_ALL_PHASES == waveBootPhase)
    {
        trace (TRACE_LEVEL_DEBUG, "SecondaryNodeConfigurePrismBootAgent::execute : All Phases.");

        WaveNs::PrismSynchronousLinearSequencerStep sequencerSteps[] =
        {
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeConfigurePrismBootAgent::initializePrismServicesDuringPrePhaseStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeConfigurePrismBootAgent::enablePrismServicesDuringPrePhaseStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeConfigurePrismBootAgent::listenForEventsPrismServicesDuringPrePhaseStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeConfigurePrismBootAgent::installPrismServicesDuringPrePhaseStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeConfigurePrismBootAgent::bootPrismServicesDuringPrePhaseStep),

            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeConfigurePrismBootAgent::initializeLocalPrismServicesStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeConfigurePrismBootAgent::enablePrismServicesStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeConfigurePrismBootAgent::listenForEventsPrismServicesStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeConfigurePrismBootAgent::installLocalPrismServicesStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeConfigurePrismBootAgent::bootPrismServicesStep),

            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeConfigurePrismBootAgent::prismSynchronousLinearSequencerSucceededStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeConfigurePrismBootAgent::prismSynchronousLinearSequencerFailedStep)
        };

        PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext = new PrismSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

        ResourceId status = pPrismSynchronousLinearSequencerContext->execute ();

        return (status);
    }
    else if (WAVE_BOOT_PHASE_PRE_PHASE == waveBootPhase)
    {
        trace (TRACE_LEVEL_DEBUG, "SecondaryNodeConfigurePrismBootAgent::execute : Pre Phase.");

        WaveNs::PrismSynchronousLinearSequencerStep sequencerSteps[] =
        {
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeConfigurePrismBootAgent::initializePrismServicesDuringPrePhaseStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeConfigurePrismBootAgent::enablePrismServicesDuringPrePhaseStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeConfigurePrismBootAgent::listenForEventsPrismServicesDuringPrePhaseStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeConfigurePrismBootAgent::installPrismServicesDuringPrePhaseStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeConfigurePrismBootAgent::bootPrismServicesDuringPrePhaseStep),

            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeConfigurePrismBootAgent::prismSynchronousLinearSequencerSucceededStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeConfigurePrismBootAgent::prismSynchronousLinearSequencerFailedStep)
        };

        PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext = new PrismSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

        ResourceId status = pPrismSynchronousLinearSequencerContext->execute ();

        return (status);
    }
    else if ((WAVE_BOOT_PHASE_POST_PHASE == waveBootPhase) || WAVE_BOOT_PHASE_AFTER_POST_PHASE == waveBootPhase)
    {
        if (WAVE_BOOT_PHASE_POST_PHASE == waveBootPhase)
        {
            trace (TRACE_LEVEL_DEBUG, "SecondaryNodeConfigurePrismBootAgent::execute : Post Phase.");
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "SecondaryNodeConfigurePrismBootAgent::execute : Phase 3");
        }

        WaveNs::PrismSynchronousLinearSequencerStep sequencerSteps[] =
        {
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeConfigurePrismBootAgent::initializeLocalPrismServicesStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeConfigurePrismBootAgent::enablePrismServicesStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeConfigurePrismBootAgent::listenForEventsPrismServicesStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeConfigurePrismBootAgent::installLocalPrismServicesStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeConfigurePrismBootAgent::bootPrismServicesStep),

            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeConfigurePrismBootAgent::prismSynchronousLinearSequencerSucceededStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeConfigurePrismBootAgent::prismSynchronousLinearSequencerFailedStep)
        };

        PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext = new PrismSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

        ResourceId status = pPrismSynchronousLinearSequencerContext->execute ();

        return (status);
    }

    return (WAVE_MESSAGE_SUCCESS);
}

bool SecondaryNodeConfigurePrismBootAgent::isAPersistentBoot ()
{
    return (true);
}

bool SecondaryNodeConfigurePrismBootAgent::isToBeExcludedForEnableAndBoot (const WaveServiceId& waveServiceId)
{
    if (((PrismFrameworkObjectManager::getWaveServiceId               ()) == waveServiceId) ||
        (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

bool SecondaryNodeConfigurePrismBootAgent::willBeAPrimaryLocation ()
{
    return (false);
}

bool SecondaryNodeConfigurePrismBootAgent::isToBeExcludedFromInstallDuringPrePhase (const WaveServiceId &waveServiceId)
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

bool SecondaryNodeConfigurePrismBootAgent::isToBeExcludedFromInstall (const WaveServiceId &waveServiceId)
{
    if (((PrismFrameworkObjectManager::getWaveServiceId               ()) == waveServiceId) ||
        (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

bool SecondaryNodeConfigurePrismBootAgent::isToBeExcludedFromInitializeDuringPrePhase (const WaveServiceId &waveServiceId)
{
    if (((PrismFrameworkObjectManager::getWaveServiceId               ()) == waveServiceId) ||
        (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

bool SecondaryNodeConfigurePrismBootAgent::isToBeExcludedFromInitializePhase (const WaveServiceId &waveServiceId)
{
    if (((PrismFrameworkObjectManager::getWaveServiceId               ()) == waveServiceId) ||
        (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

bool SecondaryNodeConfigurePrismBootAgent::isToBeExcludedFromCurrentBootPhase (WaveServiceId waveServiceId)
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

WaveBootReason SecondaryNodeConfigurePrismBootAgent::getReason () const
{
    return (WAVE_BOOT_SECONDARY_NODE_CONFIGURE_BOOT);
}

}
