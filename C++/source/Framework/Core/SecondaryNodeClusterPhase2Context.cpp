/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anand Kumar Subramanian                                      *
 ***************************************************************************/

#include "Framework/Core/SecondaryNodeClusterPhase2Context.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"
#include "Framework/Trace/TraceMessages.h"


namespace WaveNs
{

SecondaryNodeClusterPhase2Context::SecondaryNodeClusterPhase2Context(WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps, bool resetSecondaryNodeClusterCreationFlag)
    : SecondaryNodeClusterContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps, false, false)
{
    m_resetSecondaryNodeClusterCreationFlag = resetSecondaryNodeClusterCreationFlag;
}

SecondaryNodeClusterPhase2Context::SecondaryNodeClusterPhase2Context(PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps, bool resetSecondaryNodeClusterCreationFlag)
    : SecondaryNodeClusterContext (pPrismAsynchronousContext, pWaveElement, pSteps, numberOfSteps, false, false)
{
     m_resetSecondaryNodeClusterCreationFlag = resetSecondaryNodeClusterCreationFlag;
}

SecondaryNodeClusterPhase2Context::~SecondaryNodeClusterPhase2Context()
{
    if (m_resetSecondaryNodeClusterCreationFlag)
    {
        (PrismFrameworkObjectManager::getInstance ())->setSecondaryNodeClusterCreationFlag (false);
        (PrismFrameworkObjectManager::getInstance ())->resumePostponedMessages ();
    }
}

}

