/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Geetha Aparna                                                *
 ***************************************************************************/

#include "Framework/Shutdown/PrismSecondaryNodeRejoinShutdownAgent.h"
#include "Framework/Shutdown/PrismShutdownAgentContext.h"

namespace WaveNs
{

PrismSecondaryNodeRejoinShutdownAgent::PrismSecondaryNodeRejoinShutdownAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : PrismShutdownAgent (pWaveObjectManager, currentFrameworkSequenceGenerator)
{
}

PrismSecondaryNodeRejoinShutdownAgent::~PrismSecondaryNodeRejoinShutdownAgent ()
{
}

ResourceId PrismSecondaryNodeRejoinShutdownAgent::execute ()
{
    WaveNs::PrismSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismSecondaryNodeRejoinShutdownAgent::getListOfEnabledServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismSecondaryNodeRejoinShutdownAgent::shutdownServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismSecondaryNodeRejoinShutdownAgent::disableServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismSecondaryNodeRejoinShutdownAgent::uninitializeServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismSecondaryNodeRejoinShutdownAgent::shutdownPostPhaseServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismSecondaryNodeRejoinShutdownAgent::disablePostPhaseServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismSecondaryNodeRejoinShutdownAgent::uninitializePostPhaseServicesStep),

        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismSecondaryNodeRejoinShutdownAgent::prismSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismSecondaryNodeRejoinShutdownAgent::prismSynchronousLinearSequencerFailedStep)
    };

    PrismShutdownAgentContext *pPrismShutdownAgentContext = new PrismShutdownAgentContext (reinterpret_cast<PrismAsynchronousContext *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    ResourceId status = pPrismShutdownAgentContext->execute ();

    return (status);
}

}

