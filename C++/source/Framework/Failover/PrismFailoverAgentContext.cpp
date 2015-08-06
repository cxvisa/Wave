/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Failover/PrismFailoverAgentContext.h"

namespace WaveNs
{

PrismFailoverAgentContext::PrismFailoverAgentContext (WaveElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext)
    : PrismAsynchronousContext (pCaller, pCallback, pCallerContext),
      m_serviceToBeIgnored     (0),
      m_isConfigurationChange  (false)
{
}

PrismFailoverAgentContext::~PrismFailoverAgentContext ()
{
}

void PrismFailoverAgentContext::setFailedLocationIds (const vector<LocationId> &failedLocationIds)
{
    m_failedLocationIds = failedLocationIds;
}

vector<LocationId> &PrismFailoverAgentContext::getFailedLocationIds ()
{
    return (m_failedLocationIds);
}

void PrismFailoverAgentContext::setServiceToBeIgnored (const WaveServiceId &serviceToBeIgnored)
{
    m_serviceToBeIgnored = serviceToBeIgnored;
}

WaveServiceId PrismFailoverAgentContext::getServiceToBeIgnored () const
{
    return (m_serviceToBeIgnored);
}

bool PrismFailoverAgentContext::getIsConfigurationChange () const
{
    return m_isConfigurationChange;
}

void PrismFailoverAgentContext::setIsConfigurationChange (const bool isConfigurationChange)
{
    m_isConfigurationChange = isConfigurationChange;
}


}
