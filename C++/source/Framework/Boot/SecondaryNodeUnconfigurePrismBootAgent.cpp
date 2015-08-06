/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Boot/SecondaryNodeUnconfigurePrismBootAgent.h"
#include "Framework/Utils/FrameworkToolKit.h"

namespace WaveNs
{

SecondaryNodeUnconfigurePrismBootAgent::SecondaryNodeUnconfigurePrismBootAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : PrismBootAgent (pWaveObjectManager, currentFrameworkSequenceGenerator)
{
}

SecondaryNodeUnconfigurePrismBootAgent::~SecondaryNodeUnconfigurePrismBootAgent ()
{
}

ResourceId SecondaryNodeUnconfigurePrismBootAgent::execute (const WaveBootPhase &waveBootPhase)
{
    WaveNs::PrismSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeUnconfigurePrismBootAgent::initializePrismServicesDuringPrePhaseStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeUnconfigurePrismBootAgent::enablePrismServicesDuringPrePhaseStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeUnconfigurePrismBootAgent::listenForEventsPrismServicesDuringPrePhaseStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeUnconfigurePrismBootAgent::bootPrismServicesDuringPrePhaseStep),

        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeUnconfigurePrismBootAgent::initializePrismServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeUnconfigurePrismBootAgent::enablePrismServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeUnconfigurePrismBootAgent::listenForEventsPrismServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeUnconfigurePrismBootAgent::bootPrismServicesStep),

        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeUnconfigurePrismBootAgent::prismSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SecondaryNodeUnconfigurePrismBootAgent::prismSynchronousLinearSequencerFailedStep)
    };

    PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext = new PrismSynchronousLinearSequencerContext (reinterpret_cast<PrismMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    ResourceId status = pPrismSynchronousLinearSequencerContext->execute ();

    return (status);
}

bool SecondaryNodeUnconfigurePrismBootAgent::isAPersistentBoot ()
{
    return (false);
}

bool SecondaryNodeUnconfigurePrismBootAgent::isToBeExcludedForEnableAndBoot (const WaveServiceId &prismServiceId)
{
    if (true == (FrameworkToolKit::isALocalService (prismServiceId)))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

bool SecondaryNodeUnconfigurePrismBootAgent::isToBeExcludedFromInitializeDuringPrePhase  (const WaveServiceId &prismServiceId)
{
    if (true == (FrameworkToolKit::isALocalService (prismServiceId)))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

bool SecondaryNodeUnconfigurePrismBootAgent::isToBeExcludedFromInitializePhase (const WaveServiceId &prismServiceId)
{
    if (true == (FrameworkToolKit::isALocalService (prismServiceId)))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

bool SecondaryNodeUnconfigurePrismBootAgent::willBeAPrimaryLocation ()
{
    return (true);
}

WaveBootReason SecondaryNodeUnconfigurePrismBootAgent::getReason () const
{
    return (WAVE_BOOT_SECONDARY_NODE_UNCONFIGURE_BOOT);
}

}
