/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/WaveFrameworkFailoverWorkerSequencerContext.h"
#include "Framework/Failover/PrismFailoverAgent.h"

namespace WaveNs
{

WaveFrameworkFailoverWorkerSequencerContext::WaveFrameworkFailoverWorkerSequencerContext (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pPrismAsynchronousContext, pWaveElement, pSteps, numberOfSteps),
      m_thisLocationRole(LOCATION_STAND_ALONE),
      m_failoverReason      (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED),
      m_pPrismFailoverAgent (NULL),
      m_serviceToBeIgnored(0)
{
}

WaveFrameworkFailoverWorkerSequencerContext::~WaveFrameworkFailoverWorkerSequencerContext ()
{
    if (NULL != m_pPrismFailoverAgent)
    {
        delete m_pPrismFailoverAgent;
        m_pPrismFailoverAgent = NULL;
    }
}

LocationRole WaveFrameworkFailoverWorkerSequencerContext::getThisLocationRole () const
{
    return (m_thisLocationRole);
}

void WaveFrameworkFailoverWorkerSequencerContext::setThisLocationRole (const LocationRole &thisLocationRole)
{
    m_thisLocationRole = thisLocationRole;
}

FrameworkObjectManagerFailoverReason WaveFrameworkFailoverWorkerSequencerContext::getFailoverReason () const
{
    return (m_failoverReason);
}

void WaveFrameworkFailoverWorkerSequencerContext::setFailoverReason (const FrameworkObjectManagerFailoverReason &failoverReason)
{
    m_failoverReason = failoverReason;
}

UI32 WaveFrameworkFailoverWorkerSequencerContext::getNumberOfFailedLocations () const
{
    return (m_failedLocationIds.size ());
}

LocationId WaveFrameworkFailoverWorkerSequencerContext::getFailedLocationAtIndex (const UI32 &index) const
{
    return (m_failedLocationIds[index]);
}

void WaveFrameworkFailoverWorkerSequencerContext::addFailedLocationId (const LocationId &failedLocationId)
{
    m_failedLocationIds.push_back (failedLocationId);
}

PrismFailoverAgent *WaveFrameworkFailoverWorkerSequencerContext::getPPrismFailoverAgent () const
{
    return (m_pPrismFailoverAgent);
}

void WaveFrameworkFailoverWorkerSequencerContext::setPPrismFailoverAgent (PrismFailoverAgent *pPrismFailoverAgent)
{
    m_pPrismFailoverAgent = pPrismFailoverAgent;
}

void WaveFrameworkFailoverWorkerSequencerContext::setServiceToBeIgnored (const WaveServiceId &serviceToBeIgnored)
{
    m_serviceToBeIgnored = serviceToBeIgnored;
}

WaveServiceId WaveFrameworkFailoverWorkerSequencerContext::getServiceToBeIgnored () const
{
    return (m_serviceToBeIgnored);
}

}
