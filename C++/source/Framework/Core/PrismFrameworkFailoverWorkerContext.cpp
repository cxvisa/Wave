/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/PrismFrameworkFailoverWorkerContext.h"

namespace WaveNs
{

PrismFrameworkFailoverWorkerContext::PrismFrameworkFailoverWorkerContext (PrismElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext)
    : PrismAsynchronousContext (pCaller, pCallback, pCallerContext),
      m_thisLocationRole       (LOCATION_STAND_ALONE),
      m_failoverReason         (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED),
      m_serviceToBeIgnored     (0),
      m_secondaryControlledFailoverDueToPrimaryRemoval (false),
      m_isConfigurationChange  (false)
{
}

PrismFrameworkFailoverWorkerContext::~PrismFrameworkFailoverWorkerContext ()
{
}

LocationRole PrismFrameworkFailoverWorkerContext::getThisLocationRole () const
{
    return (m_thisLocationRole);
}

void PrismFrameworkFailoverWorkerContext::setThisLocationRole (const LocationRole &thisLocationRole)
{
    m_thisLocationRole = thisLocationRole;
}

FrameworkObjectManagerFailoverReason PrismFrameworkFailoverWorkerContext::getFailoverReason () const
{
    return (m_failoverReason);
}

void PrismFrameworkFailoverWorkerContext::setFailoverReason (const FrameworkObjectManagerFailoverReason &failoverReason)
{
    m_failoverReason = failoverReason;
}

UI32 PrismFrameworkFailoverWorkerContext::getNumberOfFailedLocations () const
{
    return (m_failedLocationIds.size ());
}

LocationId PrismFrameworkFailoverWorkerContext::getFailedLocationAtIndex (const UI32 &index) const
{
    return (m_failedLocationIds[index]);
}

void PrismFrameworkFailoverWorkerContext::addFailedLocationId (const LocationId &failedLocationId)
{
    m_failedLocationIds.push_back (failedLocationId);
}

void PrismFrameworkFailoverWorkerContext::getFailedLocationIds (vector<LocationId> &failedLocationIds)
{
    failedLocationIds = m_failedLocationIds;
}

void PrismFrameworkFailoverWorkerContext::setServiceToBeIgnored (const WaveServiceId &serviceToBeIgnored)
{
    m_serviceToBeIgnored = serviceToBeIgnored;
}

WaveServiceId PrismFrameworkFailoverWorkerContext::getServiceToBeIgnored () const
{
    return (m_serviceToBeIgnored);
}

void PrismFrameworkFailoverWorkerContext::setSecondaryControlledFailoverDueToPrimaryRemoval()
{
    m_secondaryControlledFailoverDueToPrimaryRemoval = true;
}

bool PrismFrameworkFailoverWorkerContext::isSecondaryControlledFailoverDueToPrimaryRemoval () const
{
   return m_secondaryControlledFailoverDueToPrimaryRemoval;
}

bool PrismFrameworkFailoverWorkerContext::getIsConfigurationChange () const
{
    return m_isConfigurationChange;
}

void PrismFrameworkFailoverWorkerContext::setIsConfigurationChange (const bool isConfigurationChange)
{
    m_isConfigurationChange = isConfigurationChange;
}

}
