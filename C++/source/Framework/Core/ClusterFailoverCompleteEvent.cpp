/***************************************************************************
 *   Copyright (C) 2011 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Anand Kumar Subramanian                                      *
 ***************************************************************************/


#include "Framework/Core/ClusterFailoverCompleteEvent.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"
#include "Framework/Attributes/AttributeResourceId.h"

namespace WaveNs
{

ClusterFailoverCompleteEvent::ClusterFailoverCompleteEvent (FrameworkObjectManagerFailoverReason failoverReason, vector<LocationId> &failedLocationIds, bool isPrincipalChangedWithThisFailover)
    : PrismEvent (PrismFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_BROADCAST_FAILOVER_COMPLETE_EVENT),
      m_failoverReason                      (failoverReason),
      m_failedLocationIds                   (failedLocationIds),
      m_isPrincipalChangedWithThisFailover  (isPrincipalChangedWithThisFailover)
{
}

ClusterFailoverCompleteEvent::~ClusterFailoverCompleteEvent ()
{
}

FrameworkObjectManagerFailoverReason ClusterFailoverCompleteEvent::getfailoverReason () const
{
    return (m_failoverReason);
}

void ClusterFailoverCompleteEvent::setFailoverReason (FrameworkObjectManagerFailoverReason failoverReason)
{
    m_failoverReason = failoverReason;
}

vector<LocationId> ClusterFailoverCompleteEvent::getFailoverReason () const
{
    return (m_failedLocationIds);
}

void ClusterFailoverCompleteEvent::setFailedLocationIds (const vector<LocationId> &failedLocationIds)
{
    m_failedLocationIds = failedLocationIds;
}

bool ClusterFailoverCompleteEvent::getIsPrincipalChangedWithThisFailover () const
{
    return (m_isPrincipalChangedWithThisFailover);
}

void ClusterFailoverCompleteEvent::setIsPrincipalChangedWithThisFailover (bool isPrincipalChangedWithThisFailover)
{
    m_isPrincipalChangedWithThisFailover = isPrincipalChangedWithThisFailover;
}

}
