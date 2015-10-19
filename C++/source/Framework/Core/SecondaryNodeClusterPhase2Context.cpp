/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anand Kumar Subramanian                                      *
 ***************************************************************************/

#include "Framework/Core/SecondaryNodeClusterPhase2Context.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Trace/TraceMessages.h"


namespace WaveNs
{

SecondaryNodeClusterPhase2Context::SecondaryNodeClusterPhase2Context(WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps, bool resetSecondaryNodeClusterCreationFlag)
    : SecondaryNodeClusterContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps, false, false)
{
    m_resetSecondaryNodeClusterCreationFlag = resetSecondaryNodeClusterCreationFlag;
}

SecondaryNodeClusterPhase2Context::SecondaryNodeClusterPhase2Context(WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps, bool resetSecondaryNodeClusterCreationFlag)
    : SecondaryNodeClusterContext (pWaveAsynchronousContext, pWaveElement, pSteps, numberOfSteps, false, false)
{
     m_resetSecondaryNodeClusterCreationFlag = resetSecondaryNodeClusterCreationFlag;
}

SecondaryNodeClusterPhase2Context::~SecondaryNodeClusterPhase2Context()
{
    if (m_resetSecondaryNodeClusterCreationFlag)
    {
        (WaveFrameworkObjectManager::getInstance ())->setSecondaryNodeClusterCreationFlag (false);
        (WaveFrameworkObjectManager::getInstance ())->resumePostponedMessages ();
    }
}

}

