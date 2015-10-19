/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Failover/WaveFailoverAgentContext.h"

namespace WaveNs
{

WaveFailoverAgentContext::WaveFailoverAgentContext (WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext)
    : WaveAsynchronousContext (pCaller, pCallback, pCallerContext),
      m_serviceToBeIgnored     (0),
      m_isConfigurationChange  (false)
{
}

WaveFailoverAgentContext::~WaveFailoverAgentContext ()
{
}

void WaveFailoverAgentContext::setFailedLocationIds (const vector<LocationId> &failedLocationIds)
{
    m_failedLocationIds = failedLocationIds;
}

vector<LocationId> &WaveFailoverAgentContext::getFailedLocationIds ()
{
    return (m_failedLocationIds);
}

void WaveFailoverAgentContext::setServiceToBeIgnored (const WaveServiceId &serviceToBeIgnored)
{
    m_serviceToBeIgnored = serviceToBeIgnored;
}

WaveServiceId WaveFailoverAgentContext::getServiceToBeIgnored () const
{
    return (m_serviceToBeIgnored);
}

bool WaveFailoverAgentContext::getIsConfigurationChange () const
{
    return m_isConfigurationChange;
}

void WaveFailoverAgentContext::setIsConfigurationChange (const bool isConfigurationChange)
{
    m_isConfigurationChange = isConfigurationChange;
}


}
