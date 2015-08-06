/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/DetachFromClusterAsynchronousContext.h"

namespace WaveNs
{

DetachFromClusterAsynchronousContext::DetachFromClusterAsynchronousContext (WaveElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext)
    : PrismAsynchronousContext (pCaller, pCallback, pCallerContext),
      m_reasonForDetachingFromCluster (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED)
{
}

DetachFromClusterAsynchronousContext::~DetachFromClusterAsynchronousContext ()
{
}

FrameworkObjectManagerFailoverReason DetachFromClusterAsynchronousContext::getReasonForDetachingFromCluster () const
{
    return (m_reasonForDetachingFromCluster);
}

void DetachFromClusterAsynchronousContext::setReasonForDetachingFromCluster (const FrameworkObjectManagerFailoverReason &reasonForDetachingFromCluster)
{
    m_reasonForDetachingFromCluster = reasonForDetachingFromCluster;
}


}
