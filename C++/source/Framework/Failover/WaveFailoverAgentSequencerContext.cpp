/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Failover/WaveFailoverAgentSequencerContext.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/StringUtils.h"

namespace WaveNs
{

WaveFailoverAgentSequencerContext::WaveFailoverAgentSequencerContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps),
      m_serviceToBeIgnored                   (0),
      m_isConfigurationChange                (false),
      m_olderPrimaryLocationId               (0),
      m_isPrincipalChangedWithThisFailover   (false),
      m_anyConfiguraitonChangeTrackingNumber (0)
{
}

WaveFailoverAgentSequencerContext::WaveFailoverAgentSequencerContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveAsynchronousContext, pWaveElement, pSteps, numberOfSteps),
       m_serviceToBeIgnored                   (0),
       m_isConfigurationChange                (false),
       m_olderPrimaryLocationId               (0),
       m_isPrincipalChangedWithThisFailover   (false),
       m_anyConfiguraitonChangeTrackingNumber (0)
{
}

WaveFailoverAgentSequencerContext::~WaveFailoverAgentSequencerContext ()
{
}

void WaveFailoverAgentSequencerContext::setFailedLocationIds (const vector<LocationId> &failedLocationIds)
{
    m_failedLocationIds = failedLocationIds;
}

vector<LocationId> &WaveFailoverAgentSequencerContext::getFailedLocationIds ()
{
    return (m_failedLocationIds);
}

void WaveFailoverAgentSequencerContext::setServiceToBeIgnored (const WaveServiceId &serviceToBeIgnored)
{
    m_serviceToBeIgnored = serviceToBeIgnored;
}

WaveServiceId WaveFailoverAgentSequencerContext::getServiceToBeIgnored () const
{
    return (m_serviceToBeIgnored);
}

void WaveFailoverAgentSequencerContext::setSecondaryNodeStatus (const string &secondaryNodeIpAddress, const SI32 &secondaryNodePort, ResourceId status)
{
    string                            uniqueTag = secondaryNodeIpAddress + "#" + secondaryNodePort;
    map<string, ResourceId>::iterator element   = m_secondaryNodesStatus.find (uniqueTag);
    map<string, ResourceId>::iterator end       = m_secondaryNodesStatus.end ();

    if (end == element)
    {
        m_secondaryNodesStatus[uniqueTag] = status;
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, string ("WaveFailoverAgentSequencerContext::setSecondaryNodeStatus : This node (") + secondaryNodeIpAddress + ":" + secondaryNodePort + ") status is already set.");
        waveAssert (false, __FILE__, __LINE__);
    }
}

void WaveFailoverAgentSequencerContext::updateSecondaryNodeStatus (const string &secondaryNodeIpAddress, const SI32 &secondaryNodePort, ResourceId status)
{
    string                            uniqueTag = secondaryNodeIpAddress + "#" + secondaryNodePort;
    map<string, ResourceId>::iterator element   = m_secondaryNodesStatus.find (uniqueTag);
    map<string, ResourceId>::iterator end       = m_secondaryNodesStatus.end ();

    if (end != element)
    {
        m_secondaryNodesStatus[uniqueTag] = status;
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, string ("WaveFailoverAgentSequencerContext::updateSecondaryNodeStatus : This node (") + secondaryNodeIpAddress + ":" + secondaryNodePort + ") status is not previously set.");
        waveAssert (false, __FILE__, __LINE__);
    }
}

ResourceId WaveFailoverAgentSequencerContext::getSecondaryNodeStatus (const string &secondaryNodeIpAddress, const SI32 &secondaryNodePort)
{
    string                            uniqueTag = secondaryNodeIpAddress + "#" + secondaryNodePort;
    map<string, ResourceId>::iterator element   = m_secondaryNodesStatus.find (uniqueTag);
    map<string, ResourceId>::iterator end       = m_secondaryNodesStatus.end ();

    if (end != element)
    {
        return (m_secondaryNodesStatus[uniqueTag]);
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, string ("WaveFailoverAgentSequencerContext::getSecondaryNodeStatus : This node (") + secondaryNodeIpAddress + ":" + secondaryNodePort + ") status is not set.");
        waveAssert (false, __FILE__, __LINE__);
        return (WAVE_MESSAGE_ERROR);
    }
}

bool WaveFailoverAgentSequencerContext::isSecondaryNodeStatusSet (const string &secondaryNodeIpAddress, const SI32 &secondaryNodePort)
{
    string                            uniqueTag = secondaryNodeIpAddress + "#" + secondaryNodePort;
    map<string, ResourceId>::iterator element   = m_secondaryNodesStatus.find (uniqueTag);
    map<string, ResourceId>::iterator end       = m_secondaryNodesStatus.end ();

    if (end != element)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

bool WaveFailoverAgentSequencerContext::getIsConfigurationChange () const
{
    return m_isConfigurationChange;
}

void WaveFailoverAgentSequencerContext::setIsConfigurationChange (const bool isConfigurationChange)
{
    m_isConfigurationChange = isConfigurationChange;
}

void WaveFailoverAgentSequencerContext::setOlderPrimaryLocationId (LocationId olderPrimary)
{
    m_olderPrimaryLocationId = olderPrimary;
}

LocationId WaveFailoverAgentSequencerContext::getOlderPrimaryLocationId () const
{
    return (m_olderPrimaryLocationId);
}

bool WaveFailoverAgentSequencerContext::getIsPrincipalChangedWithThisFailover () const
{
    return m_isPrincipalChangedWithThisFailover;
}

void WaveFailoverAgentSequencerContext::setIsPrincipalChangedWithThisFailover (const bool isPrincipalChangedWithThisFailover)
{
    m_isPrincipalChangedWithThisFailover = isPrincipalChangedWithThisFailover;
}

void WaveFailoverAgentSequencerContext::setConnectedLocationVector (const vector<LocationId> &connectedLocationIds)
{
    m_connectedLocationIds = connectedLocationIds;
}

void WaveFailoverAgentSequencerContext::getConnectedLocationVector (vector <LocationId> &connectedLocationdIds)
{
    connectedLocationdIds  = m_connectedLocationIds;
}

void WaveFailoverAgentSequencerContext::setUnknownWaveNodeLocationIds (const vector<LocationId> &failedLocationIds)
{
    m_unknownWaveNodeLocationIds = failedLocationIds;
}

vector<LocationId> WaveFailoverAgentSequencerContext::getUnknownWaveNodeLocationIds ()
{
    return (m_unknownWaveNodeLocationIds);
}

void WaveFailoverAgentSequencerContext::setAnyConfigurationChangeTrackingNumber (const UI64 &trackingNumber)
{
    m_anyConfiguraitonChangeTrackingNumber = trackingNumber;
}

UI64 WaveFailoverAgentSequencerContext::getAnyConfigurationChangeTrackingNumber () const
{
    return (m_anyConfiguraitonChangeTrackingNumber);
}

}
