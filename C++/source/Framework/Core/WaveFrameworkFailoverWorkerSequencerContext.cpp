/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/WaveFrameworkFailoverWorkerSequencerContext.h"
#include "Framework/Failover/WaveFailoverAgent.h"

namespace WaveNs
{

WaveFrameworkFailoverWorkerSequencerContext::WaveFrameworkFailoverWorkerSequencerContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveAsynchronousContext, pWaveElement, pSteps, numberOfSteps),
      m_thisLocationRole(LOCATION_STAND_ALONE),
      m_failoverReason      (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED),
      m_pWaveFailoverAgent (NULL),
      m_serviceToBeIgnored(0)
{
}

WaveFrameworkFailoverWorkerSequencerContext::~WaveFrameworkFailoverWorkerSequencerContext ()
{
    if (NULL != m_pWaveFailoverAgent)
    {
        delete m_pWaveFailoverAgent;
        m_pWaveFailoverAgent = NULL;
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

WaveFailoverAgent *WaveFrameworkFailoverWorkerSequencerContext::getPWaveFailoverAgent () const
{
    return (m_pWaveFailoverAgent);
}

void WaveFrameworkFailoverWorkerSequencerContext::setPWaveFailoverAgent (WaveFailoverAgent *pWaveFailoverAgent)
{
    m_pWaveFailoverAgent = pWaveFailoverAgent;
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
