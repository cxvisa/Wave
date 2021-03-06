/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/DestroyClusterContext.h"

namespace WaveNs
{

DestroyClusterContext::DestroyClusterContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : DeleteNodesFromClusterContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps),
      m_thisLocationRoleBeforeDestroy (LOCATION_STAND_ALONE),
      m_reasonForDestroyingCluster (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED),
      m_isRebootRequired (true)
{
}

DestroyClusterContext::DestroyClusterContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : DeleteNodesFromClusterContext (pWaveAsynchronousContext, pWaveElement, pSteps, numberOfSteps),
      m_thisLocationRoleBeforeDestroy (LOCATION_STAND_ALONE),
      m_reasonForDestroyingCluster (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED),
      m_isRebootRequired (true)
{
}

DestroyClusterContext::~DestroyClusterContext ()
{
}

LocationRole DestroyClusterContext::getThisLocationRoleBeforeDestroy () const
{
    return (m_thisLocationRoleBeforeDestroy);
}

void DestroyClusterContext::setThisLocationRoleBeforeDestroy (const LocationRole &thisLocationRoleBeforeDestroy)
{
    m_thisLocationRoleBeforeDestroy = thisLocationRoleBeforeDestroy;
}

FrameworkObjectManagerFailoverReason DestroyClusterContext::getReasonForDestroyingCluster () const
{
    return (m_reasonForDestroyingCluster);
}

void DestroyClusterContext::setReasonForDestroyingCluster (const FrameworkObjectManagerFailoverReason &reasonForDestroyingCluster)
{
    m_reasonForDestroyingCluster = reasonForDestroyingCluster;
}

void DestroyClusterContext::setIsRebootRequired (const bool &isRebootRequired)
{
    m_isRebootRequired = isRebootRequired;
}

bool DestroyClusterContext::getIsRebootRequired () const
{
    return (m_isRebootRequired);
}

}
