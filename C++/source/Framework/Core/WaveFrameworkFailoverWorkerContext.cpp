/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/WaveFrameworkFailoverWorkerContext.h"

namespace WaveNs
{

WaveFrameworkFailoverWorkerContext::WaveFrameworkFailoverWorkerContext (WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext)
    : WaveAsynchronousContext (pCaller, pCallback, pCallerContext),
      m_thisLocationRole       (LOCATION_STAND_ALONE),
      m_failoverReason         (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED),
      m_serviceToBeIgnored     (0),
      m_secondaryControlledFailoverDueToPrimaryRemoval (false),
      m_isConfigurationChange  (false)
{
}

WaveFrameworkFailoverWorkerContext::~WaveFrameworkFailoverWorkerContext ()
{
}

LocationRole WaveFrameworkFailoverWorkerContext::getThisLocationRole () const
{
    return (m_thisLocationRole);
}

void WaveFrameworkFailoverWorkerContext::setThisLocationRole (const LocationRole &thisLocationRole)
{
    m_thisLocationRole = thisLocationRole;
}

FrameworkObjectManagerFailoverReason WaveFrameworkFailoverWorkerContext::getFailoverReason () const
{
    return (m_failoverReason);
}

void WaveFrameworkFailoverWorkerContext::setFailoverReason (const FrameworkObjectManagerFailoverReason &failoverReason)
{
    m_failoverReason = failoverReason;
}

UI32 WaveFrameworkFailoverWorkerContext::getNumberOfFailedLocations () const
{
    return (m_failedLocationIds.size ());
}

LocationId WaveFrameworkFailoverWorkerContext::getFailedLocationAtIndex (const UI32 &index) const
{
    return (m_failedLocationIds[index]);
}

void WaveFrameworkFailoverWorkerContext::addFailedLocationId (const LocationId &failedLocationId)
{
    m_failedLocationIds.push_back (failedLocationId);
}

void WaveFrameworkFailoverWorkerContext::getFailedLocationIds (vector<LocationId> &failedLocationIds)
{
    failedLocationIds = m_failedLocationIds;
}

void WaveFrameworkFailoverWorkerContext::setServiceToBeIgnored (const WaveServiceId &serviceToBeIgnored)
{
    m_serviceToBeIgnored = serviceToBeIgnored;
}

WaveServiceId WaveFrameworkFailoverWorkerContext::getServiceToBeIgnored () const
{
    return (m_serviceToBeIgnored);
}

void WaveFrameworkFailoverWorkerContext::setSecondaryControlledFailoverDueToPrimaryRemoval()
{
    m_secondaryControlledFailoverDueToPrimaryRemoval = true;
}

bool WaveFrameworkFailoverWorkerContext::isSecondaryControlledFailoverDueToPrimaryRemoval () const
{
   return m_secondaryControlledFailoverDueToPrimaryRemoval;
}

bool WaveFrameworkFailoverWorkerContext::getIsConfigurationChange () const
{
    return m_isConfigurationChange;
}

void WaveFrameworkFailoverWorkerContext::setIsConfigurationChange (const bool isConfigurationChange)
{
    m_isConfigurationChange = isConfigurationChange;
}

}
