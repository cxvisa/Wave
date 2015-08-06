/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anil ChannaveeraSetty                                        *
 ***************************************************************************/

#include "Framework/Core/SecondaryNodeClusterPhase3Context.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"
#include "Framework/Trace/TraceMessages.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"

namespace WaveNs
{

SecondaryNodeClusterPhase3Context::SecondaryNodeClusterPhase3Context(WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps, bool resetSecondaryNodeClusterCreationFlag, bool clusterHaSyncInProgressFlag)
    : SecondaryNodeClusterContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps, false, clusterHaSyncInProgressFlag)
{
    m_resetSecondaryNodeClusterCreationFlag = resetSecondaryNodeClusterCreationFlag;
}

SecondaryNodeClusterPhase3Context::SecondaryNodeClusterPhase3Context(PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps, bool resetSecondaryNodeClusterCreationFlag, bool clusterHaSyncInProgressFlag)
    : SecondaryNodeClusterContext (pPrismAsynchronousContext, pWaveElement, pSteps, numberOfSteps, clusterHaSyncInProgressFlag)
{
    m_resetSecondaryNodeClusterCreationFlag = resetSecondaryNodeClusterCreationFlag;
}

SecondaryNodeClusterPhase3Context::~SecondaryNodeClusterPhase3Context()
{
    if (m_resetSecondaryNodeClusterCreationFlag)
    {   
        (PrismFrameworkObjectManager::getInstance ())->setSecondaryNodeClusterCreationFlag (false);
        if (true == (PrismFrameworkObjectManager::getInstance ())->getNeedNotifyClusterReadyState())
        {
            trace (TRACE_LEVEL_INFO, "SecondaryNodeClusterPhase3Context::Destructor: Notify on ClusterReady event for secondary join success event");
            bool readyState = true;
            (PrismFrameworkObjectManager::getInstance ())->notifyClusterReadyState (readyState);
            (PrismFrameworkObjectManager::getInstance ())->setNeedNotifyClusterReadyState (false);
        }

        (PrismFrameworkObjectManager::getInstance ())->resumePostponedMessages ();
    }
}

}
