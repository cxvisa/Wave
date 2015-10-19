/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Failover/FailoverAsynchronousContext.h"

namespace WaveNs
{

FailoverAsynchronousContext::FailoverAsynchronousContext (WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext, FrameworkObjectManagerFailoverReason failoverReason, vector<LocationId> &failedLocationIds, bool isPrincipalChangedWithThisFailover)
    : WaveAsynchronousContext              (pCaller, pCallback, pCallerContext),
      m_failoverReason                      (failoverReason),
      m_failedLocationIds                   (failedLocationIds),
      m_isPrincipalChangedWithThisFailover  (isPrincipalChangedWithThisFailover)
{
}

FailoverAsynchronousContext::~FailoverAsynchronousContext ()
{
}

FrameworkObjectManagerFailoverReason FailoverAsynchronousContext::getfailoverReason () const
{
    return m_failoverReason;
}

vector<LocationId> FailoverAsynchronousContext::getfailedLocationIds () const
{
    return m_failedLocationIds;
}

bool FailoverAsynchronousContext::getIsPrincipalChangedWithThisFailover () const
{
    return m_isPrincipalChangedWithThisFailover;
}

}
