/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Geetha Aparna                                                *
 ***************************************************************************/

#include "Framework/Shutdown/WaveSecondaryNodeRejoinShutdownAgent.h"
#include "Framework/Shutdown/WaveShutdownAgentContext.h"

namespace WaveNs
{

WaveSecondaryNodeRejoinShutdownAgent::WaveSecondaryNodeRejoinShutdownAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : WaveShutdownAgent (pWaveObjectManager, currentFrameworkSequenceGenerator)
{
}

WaveSecondaryNodeRejoinShutdownAgent::~WaveSecondaryNodeRejoinShutdownAgent ()
{
}

ResourceId WaveSecondaryNodeRejoinShutdownAgent::execute ()
{
    WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveSecondaryNodeRejoinShutdownAgent::getListOfEnabledServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveSecondaryNodeRejoinShutdownAgent::shutdownServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveSecondaryNodeRejoinShutdownAgent::disableServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveSecondaryNodeRejoinShutdownAgent::uninitializeServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveSecondaryNodeRejoinShutdownAgent::shutdownPostPhaseServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveSecondaryNodeRejoinShutdownAgent::disablePostPhaseServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveSecondaryNodeRejoinShutdownAgent::uninitializePostPhaseServicesStep),

        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveSecondaryNodeRejoinShutdownAgent::prismSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveSecondaryNodeRejoinShutdownAgent::prismSynchronousLinearSequencerFailedStep)
    };

    WaveShutdownAgentContext *pWaveShutdownAgentContext = new WaveShutdownAgentContext (reinterpret_cast<WaveAsynchronousContext *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    ResourceId status = pWaveShutdownAgentContext->execute ();

    return (status);
}

}

