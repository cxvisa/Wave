/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anil ChannaveeraSetty                                        *
 ***************************************************************************/

#include "Framework/Core/SecondaryNodeClusterPhase3Context.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Trace/TraceMessages.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"

namespace WaveNs
{

SecondaryNodeClusterPhase3Context::SecondaryNodeClusterPhase3Context(WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps, bool resetSecondaryNodeClusterCreationFlag, bool clusterHaSyncInProgressFlag)
    : SecondaryNodeClusterContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps, false, clusterHaSyncInProgressFlag)
{
    m_resetSecondaryNodeClusterCreationFlag = resetSecondaryNodeClusterCreationFlag;
}

SecondaryNodeClusterPhase3Context::SecondaryNodeClusterPhase3Context(WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps, bool resetSecondaryNodeClusterCreationFlag, bool clusterHaSyncInProgressFlag)
    : SecondaryNodeClusterContext (pWaveAsynchronousContext, pWaveElement, pSteps, numberOfSteps, clusterHaSyncInProgressFlag)
{
    m_resetSecondaryNodeClusterCreationFlag = resetSecondaryNodeClusterCreationFlag;
}

SecondaryNodeClusterPhase3Context::~SecondaryNodeClusterPhase3Context()
{
    if (m_resetSecondaryNodeClusterCreationFlag)
    {   
        (WaveFrameworkObjectManager::getInstance ())->setSecondaryNodeClusterCreationFlag (false);
        if (true == (WaveFrameworkObjectManager::getInstance ())->getNeedNotifyClusterReadyState())
        {
            trace (TRACE_LEVEL_INFO, "SecondaryNodeClusterPhase3Context::Destructor: Notify on ClusterReady event for secondary join success event");
            bool readyState = true;
            (WaveFrameworkObjectManager::getInstance ())->notifyClusterReadyState (readyState);
            (WaveFrameworkObjectManager::getInstance ())->setNeedNotifyClusterReadyState (false);
        }

        (WaveFrameworkObjectManager::getInstance ())->resumePostponedMessages ();
    }
}

}
