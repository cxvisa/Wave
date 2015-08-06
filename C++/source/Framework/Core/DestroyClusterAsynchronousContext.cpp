/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/DestroyClusterAsynchronousContext.h"

namespace WaveNs
{

DestroyClusterAsynchronousContext::DestroyClusterAsynchronousContext (PrismElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext)
    : PrismAsynchronousContext     (pCaller, pCallback, pCallerContext),
      m_reasonForDestroyingCluster (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED),
      m_originalRequester          (0),
      m_isRebootRequired           (true),
      m_isPreparingForAddNode      (false)
{
}

DestroyClusterAsynchronousContext::~DestroyClusterAsynchronousContext ()
{
}

FrameworkObjectManagerFailoverReason DestroyClusterAsynchronousContext::getReasonForDestroyingCluster () const
{
    return (m_reasonForDestroyingCluster);
}

void DestroyClusterAsynchronousContext::setReasonForDestroyingCluster (const FrameworkObjectManagerFailoverReason &reasonForDestroyingCluster)
{
    m_reasonForDestroyingCluster = reasonForDestroyingCluster;
}

WaveServiceId DestroyClusterAsynchronousContext::getOriginalRequester () const
{
    return (m_originalRequester);
}

void DestroyClusterAsynchronousContext::setOriginalRequester (const WaveServiceId &originalRequester)
{
    m_originalRequester = originalRequester;
}

void DestroyClusterAsynchronousContext::setIsRebootRequired (const bool &isRebootRequired)
{
    m_isRebootRequired = isRebootRequired;
}

bool DestroyClusterAsynchronousContext::getIsRebootRequired () const
{
    return (m_isRebootRequired);
}

void DestroyClusterAsynchronousContext::setPreparingForAddNode (const bool &isPreparingForAddNode)
{
    m_isPreparingForAddNode = isPreparingForAddNode;
}

bool DestroyClusterAsynchronousContext::getIsPreparingForAddNode () const
{
    return (m_isPreparingForAddNode);
}

}
