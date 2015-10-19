/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Boot/FirstTimeWaveBootAgent.h"
#include "Framework/Utils/FrameworkToolKit.h"

namespace WaveNs
{

FirstTimeWaveBootAgent::FirstTimeWaveBootAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : WaveBootAgent (pWaveObjectManager, currentFrameworkSequenceGenerator)
{
}

FirstTimeWaveBootAgent::~FirstTimeWaveBootAgent ()
{
}

WaveBootReason FirstTimeWaveBootAgent::getReason () const
{
    return (WAVE_BOOT_FIRST_TIME_BOOT);
}

ResourceId FirstTimeWaveBootAgent::execute (const WaveBootPhase &waveBootPhase)
{
    WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&FirstTimeWaveBootAgent::initializeWaveServicesDuringPrePhaseStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&FirstTimeWaveBootAgent::enableWaveServicesDuringPrePhaseStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&FirstTimeWaveBootAgent::listenForEventsWaveServicesDuringPrePhaseStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&FirstTimeWaveBootAgent::installWaveServicesDuringPrePhaseStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&FirstTimeWaveBootAgent::bootWaveServicesDuringPrePhaseStep),

        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&FirstTimeWaveBootAgent::initializeLocalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&FirstTimeWaveBootAgent::enableLocalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&FirstTimeWaveBootAgent::listenForEventsLocalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&FirstTimeWaveBootAgent::installLocalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&FirstTimeWaveBootAgent::bootLocalWaveServicesStep),

        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&FirstTimeWaveBootAgent::initializeGlobalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&FirstTimeWaveBootAgent::enableGlobalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&FirstTimeWaveBootAgent::listenForEventsGlobalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&FirstTimeWaveBootAgent::installGlobalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&FirstTimeWaveBootAgent::bootGlobalWaveServicesStep),

        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&FirstTimeWaveBootAgent::saveWaveConfigurationStep),

        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&FirstTimeWaveBootAgent::prismSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&FirstTimeWaveBootAgent::prismSynchronousLinearSequencerFailedStep)
    };

    WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext = new WaveSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    ResourceId status = pWaveSynchronousLinearSequencerContext->execute ();

    return (status);
}

ResourceId FirstTimeWaveBootAgent::saveWaveConfigurationStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    if (WAVE_MGMT_INTF_ROLE_SERVER != (FrameworkToolKit::getManagementInterfaceRole ()))
    {
        return (WAVE_MESSAGE_SUCCESS);
    }

    trace (TRACE_LEVEL_INFO,   "FirstTimeWaveBootAgent::saveWaveConfigurationStep : replay file name " + FrameworkToolKit::getStartupFileName ());

    FrameworkToolKit::setStartupFileType (WAVE_PERSISTENCE_REGULAR_FILE);
    FrameworkToolKit::setIsStartupValid (false);

    ResourceId status = FrameworkToolKit::saveWaveConfiguration ();

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR,   "FirstTimeWaveBootAgent::saveWaveConfigurationStep : Could not save configuration");
    }

    return (status);
}

}
