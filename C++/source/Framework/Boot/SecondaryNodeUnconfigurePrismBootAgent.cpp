/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Boot/SecondaryNodeUnconfigureWaveBootAgent.h"
#include "Framework/Utils/FrameworkToolKit.h"

namespace WaveNs
{

SecondaryNodeUnconfigureWaveBootAgent::SecondaryNodeUnconfigureWaveBootAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : WaveBootAgent (pWaveObjectManager, currentFrameworkSequenceGenerator)
{
}

SecondaryNodeUnconfigureWaveBootAgent::~SecondaryNodeUnconfigureWaveBootAgent ()
{
}

ResourceId SecondaryNodeUnconfigureWaveBootAgent::execute (const WaveBootPhase &waveBootPhase)
{
    WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeUnconfigureWaveBootAgent::initializeWaveServicesDuringPrePhaseStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeUnconfigureWaveBootAgent::enableWaveServicesDuringPrePhaseStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeUnconfigureWaveBootAgent::listenForEventsWaveServicesDuringPrePhaseStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeUnconfigureWaveBootAgent::bootWaveServicesDuringPrePhaseStep),

        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeUnconfigureWaveBootAgent::initializeWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeUnconfigureWaveBootAgent::enableWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeUnconfigureWaveBootAgent::listenForEventsWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeUnconfigureWaveBootAgent::bootWaveServicesStep),

        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeUnconfigureWaveBootAgent::prismSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SecondaryNodeUnconfigureWaveBootAgent::prismSynchronousLinearSequencerFailedStep)
    };

    WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext = new WaveSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    ResourceId status = pWaveSynchronousLinearSequencerContext->execute ();

    return (status);
}

bool SecondaryNodeUnconfigureWaveBootAgent::isAPersistentBoot ()
{
    return (false);
}

bool SecondaryNodeUnconfigureWaveBootAgent::isToBeExcludedForEnableAndBoot (const WaveServiceId &waveServiceId)
{
    if (true == (FrameworkToolKit::isALocalService (waveServiceId)))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

bool SecondaryNodeUnconfigureWaveBootAgent::isToBeExcludedFromInitializeDuringPrePhase  (const WaveServiceId &waveServiceId)
{
    if (true == (FrameworkToolKit::isALocalService (waveServiceId)))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

bool SecondaryNodeUnconfigureWaveBootAgent::isToBeExcludedFromInitializePhase (const WaveServiceId &waveServiceId)
{
    if (true == (FrameworkToolKit::isALocalService (waveServiceId)))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

bool SecondaryNodeUnconfigureWaveBootAgent::willBeAPrimaryLocation ()
{
    return (true);
}

WaveBootReason SecondaryNodeUnconfigureWaveBootAgent::getReason () const
{
    return (WAVE_BOOT_SECONDARY_NODE_UNCONFIGURE_BOOT);
}

}
