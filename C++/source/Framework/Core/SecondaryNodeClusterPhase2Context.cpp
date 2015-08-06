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

SecondaryNodeClusterPhase2Context::SecondaryNodeClusterPhase2Context(WaveMessage *pWaveMessage, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps, bool resetSecondaryNodeClusterCreationFlag)
    : SecondaryNodeClusterContext (pWaveMessage, pPrismElement, pSteps, numberOfSteps, false, false)
{
    m_resetSecondaryNodeClusterCreationFlag = resetSecondaryNodeClusterCreationFlag;
}

SecondaryNodeClusterPhase2Context::SecondaryNodeClusterPhase2Context(PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps, bool resetSecondaryNodeClusterCreationFlag)
    : SecondaryNodeClusterContext (pPrismAsynchronousContext, pPrismElement, pSteps, numberOfSteps, false, false)
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

