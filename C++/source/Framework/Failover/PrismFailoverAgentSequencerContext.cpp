/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Failover/PrismFailoverAgentSequencerContext.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/StringUtils.h"

namespace WaveNs
{

PrismFailoverAgentSequencerContext::PrismFailoverAgentSequencerContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps),
      m_serviceToBeIgnored                   (0),
      m_isConfigurationChange                (false),
      m_olderPrimaryLocationId               (0),
      m_isPrincipalChangedWithThisFailover   (false),
      m_anyConfiguraitonChangeTrackingNumber (0)
{
}

PrismFailoverAgentSequencerContext::PrismFailoverAgentSequencerContext (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pPrismAsynchronousContext, pWaveElement, pSteps, numberOfSteps),
       m_serviceToBeIgnored                   (0),
       m_isConfigurationChange                (false),
       m_olderPrimaryLocationId               (0),
       m_isPrincipalChangedWithThisFailover   (false),
       m_anyConfiguraitonChangeTrackingNumber (0)
{
}

PrismFailoverAgentSequencerContext::~PrismFailoverAgentSequencerContext ()
{
}

void PrismFailoverAgentSequencerContext::setFailedLocationIds (const vector<LocationId> &failedLocationIds)
{
    m_failedLocationIds = failedLocationIds;
}

vector<LocationId> &PrismFailoverAgentSequencerContext::getFailedLocationIds ()
{
    return (m_failedLocationIds);
}

void PrismFailoverAgentSequencerContext::setServiceToBeIgnored (const WaveServiceId &serviceToBeIgnored)
{
    m_serviceToBeIgnored = serviceToBeIgnored;
}

WaveServiceId PrismFailoverAgentSequencerContext::getServiceToBeIgnored () const
{
    return (m_serviceToBeIgnored);
}

void PrismFailoverAgentSequencerContext::setSecondaryNodeStatus (const string &secondaryNodeIpAddress, const SI32 &secondaryNodePort, ResourceId status)
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
        trace (TRACE_LEVEL_FATAL, string ("PrismFailoverAgentSequencerContext::setSecondaryNodeStatus : This node (") + secondaryNodeIpAddress + ":" + secondaryNodePort + ") status is already set.");
        waveAssert (false, __FILE__, __LINE__);
    }
}

void PrismFailoverAgentSequencerContext::updateSecondaryNodeStatus (const string &secondaryNodeIpAddress, const SI32 &secondaryNodePort, ResourceId status)
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
        trace (TRACE_LEVEL_FATAL, string ("PrismFailoverAgentSequencerContext::updateSecondaryNodeStatus : This node (") + secondaryNodeIpAddress + ":" + secondaryNodePort + ") status is not previously set.");
        waveAssert (false, __FILE__, __LINE__);
    }
}

ResourceId PrismFailoverAgentSequencerContext::getSecondaryNodeStatus (const string &secondaryNodeIpAddress, const SI32 &secondaryNodePort)
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
        trace (TRACE_LEVEL_FATAL, string ("PrismFailoverAgentSequencerContext::getSecondaryNodeStatus : This node (") + secondaryNodeIpAddress + ":" + secondaryNodePort + ") status is not set.");
        waveAssert (false, __FILE__, __LINE__);
        return (WAVE_MESSAGE_ERROR);
    }
}

bool PrismFailoverAgentSequencerContext::isSecondaryNodeStatusSet (const string &secondaryNodeIpAddress, const SI32 &secondaryNodePort)
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

bool PrismFailoverAgentSequencerContext::getIsConfigurationChange () const
{
    return m_isConfigurationChange;
}

void PrismFailoverAgentSequencerContext::setIsConfigurationChange (const bool isConfigurationChange)
{
    m_isConfigurationChange = isConfigurationChange;
}

void PrismFailoverAgentSequencerContext::setOlderPrimaryLocationId (LocationId olderPrimary)
{
    m_olderPrimaryLocationId = olderPrimary;
}

LocationId PrismFailoverAgentSequencerContext::getOlderPrimaryLocationId () const
{
    return (m_olderPrimaryLocationId);
}

bool PrismFailoverAgentSequencerContext::getIsPrincipalChangedWithThisFailover () const
{
    return m_isPrincipalChangedWithThisFailover;
}

void PrismFailoverAgentSequencerContext::setIsPrincipalChangedWithThisFailover (const bool isPrincipalChangedWithThisFailover)
{
    m_isPrincipalChangedWithThisFailover = isPrincipalChangedWithThisFailover;
}

void PrismFailoverAgentSequencerContext::setConnectedLocationVector (const vector<LocationId> &connectedLocationIds)
{
    m_connectedLocationIds = connectedLocationIds;
}

void PrismFailoverAgentSequencerContext::getConnectedLocationVector (vector <LocationId> &connectedLocationdIds)
{
    connectedLocationdIds  = m_connectedLocationIds;
}

void PrismFailoverAgentSequencerContext::setUnknownWaveNodeLocationIds (const vector<LocationId> &failedLocationIds)
{
    m_unknownWaveNodeLocationIds = failedLocationIds;
}

vector<LocationId> PrismFailoverAgentSequencerContext::getUnknownWaveNodeLocationIds ()
{
    return (m_unknownWaveNodeLocationIds);
}

void PrismFailoverAgentSequencerContext::setAnyConfigurationChangeTrackingNumber (const UI64 &trackingNumber)
{
    m_anyConfiguraitonChangeTrackingNumber = trackingNumber;
}

UI64 PrismFailoverAgentSequencerContext::getAnyConfigurationChangeTrackingNumber () const
{
    return (m_anyConfiguraitonChangeTrackingNumber);
}

}
