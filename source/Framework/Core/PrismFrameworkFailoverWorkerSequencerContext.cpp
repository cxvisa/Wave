/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/PrismFrameworkFailoverWorkerSequencerContext.h"
#include "Framework/Failover/PrismFailoverAgent.h"

namespace WaveNs
{

PrismFrameworkFailoverWorkerSequencerContext::PrismFrameworkFailoverWorkerSequencerContext (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismLinearSequencerContext (pPrismAsynchronousContext, pPrismElement, pSteps, numberOfSteps),
      m_thisLocationRole(LOCATION_STAND_ALONE),
      m_failoverReason      (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED),
      m_pPrismFailoverAgent (NULL),
      m_serviceToBeIgnored(0)
{
}

PrismFrameworkFailoverWorkerSequencerContext::~PrismFrameworkFailoverWorkerSequencerContext ()
{
    if (NULL != m_pPrismFailoverAgent)
    {
        delete m_pPrismFailoverAgent;
        m_pPrismFailoverAgent = NULL;
    }
}

LocationRole PrismFrameworkFailoverWorkerSequencerContext::getThisLocationRole () const
{
    return (m_thisLocationRole);
}

void PrismFrameworkFailoverWorkerSequencerContext::setThisLocationRole (const LocationRole &thisLocationRole)
{
    m_thisLocationRole = thisLocationRole;
}

FrameworkObjectManagerFailoverReason PrismFrameworkFailoverWorkerSequencerContext::getFailoverReason () const
{
    return (m_failoverReason);
}

void PrismFrameworkFailoverWorkerSequencerContext::setFailoverReason (const FrameworkObjectManagerFailoverReason &failoverReason)
{
    m_failoverReason = failoverReason;
}

UI32 PrismFrameworkFailoverWorkerSequencerContext::getNumberOfFailedLocations () const
{
    return (m_failedLocationIds.size ());
}

LocationId PrismFrameworkFailoverWorkerSequencerContext::getFailedLocationAtIndex (const UI32 &index) const
{
    return (m_failedLocationIds[index]);
}

void PrismFrameworkFailoverWorkerSequencerContext::addFailedLocationId (const LocationId &failedLocationId)
{
    m_failedLocationIds.push_back (failedLocationId);
}

PrismFailoverAgent *PrismFrameworkFailoverWorkerSequencerContext::getPPrismFailoverAgent () const
{
    return (m_pPrismFailoverAgent);
}

void PrismFrameworkFailoverWorkerSequencerContext::setPPrismFailoverAgent (PrismFailoverAgent *pPrismFailoverAgent)
{
    m_pPrismFailoverAgent = pPrismFailoverAgent;
}

void PrismFrameworkFailoverWorkerSequencerContext::setServiceToBeIgnored (const PrismServiceId &serviceToBeIgnored)
{
    m_serviceToBeIgnored = serviceToBeIgnored;
}

PrismServiceId PrismFrameworkFailoverWorkerSequencerContext::getServiceToBeIgnored () const
{
    return (m_serviceToBeIgnored);
}

}
