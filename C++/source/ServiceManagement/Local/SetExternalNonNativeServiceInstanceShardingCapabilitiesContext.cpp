/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "ServiceManagement/Local/SetExternalNonNativeServiceInstanceShardingCapabilitiesContext.h"

#include "ServiceManagement/Local/ExternalNonNativeServiceInstanceManagedObject.h"
namespace WaveNs
{

SetExternalNonNativeServiceInstanceShardingCapabilitiesContext::SetExternalNonNativeServiceInstanceShardingCapabilitiesContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext                       (pWaveMessage, pWaveElement, pSteps, numberOfSteps),
      m_pExternalNonNativeServiceInstanceManagedObject (NULL)
{
}

SetExternalNonNativeServiceInstanceShardingCapabilitiesContext::~SetExternalNonNativeServiceInstanceShardingCapabilitiesContext ()
{
}

string SetExternalNonNativeServiceInstanceShardingCapabilitiesContext::getApplicationName () const
{
    return (m_applicationName);
}

void SetExternalNonNativeServiceInstanceShardingCapabilitiesContext::setApplicationName (const string &applicationName)
{
    m_applicationName = applicationName;
}

string SetExternalNonNativeServiceInstanceShardingCapabilitiesContext::getApplicationInstanceName () const
{
    return (m_applicationInstanceName);
}

void SetExternalNonNativeServiceInstanceShardingCapabilitiesContext::setApplicationInstanceName (const string &applicationInstanceName)
{
    m_applicationInstanceName = applicationInstanceName;
}

vector<ResourceId> SetExternalNonNativeServiceInstanceShardingCapabilitiesContext::getShardingCapabilities () const
{
    return (m_shardingCapabilities);
}

void SetExternalNonNativeServiceInstanceShardingCapabilitiesContext::setShardingCapabilities (const vector<ResourceId> shardingCapabilities)
{
    m_shardingCapabilities = shardingCapabilities;
}

ExternalNonNativeServiceInstanceManagedObject *SetExternalNonNativeServiceInstanceShardingCapabilitiesContext::getPExternalNonNativeServiceInstanceManagedObject ()
{
    return (m_pExternalNonNativeServiceInstanceManagedObject);
}

void SetExternalNonNativeServiceInstanceShardingCapabilitiesContext::setPExternalNonNativeServiceInstanceManagedObject (ExternalNonNativeServiceInstanceManagedObject *pExternalNonNativeServiceInstanceManagedObject)
{
    m_pExternalNonNativeServiceInstanceManagedObject = pExternalNonNativeServiceInstanceManagedObject;
}

vector<ObjectId> SetExternalNonNativeServiceInstanceShardingCapabilitiesContext::getShardingCapabilityObjectIds () const
{
    return (m_shardingCapabilityObjectIds);
}

void SetExternalNonNativeServiceInstanceShardingCapabilitiesContext::setShardingCapabilityObjectIds (const vector<ObjectId> &shardingCapabilityObjectIds)
{
    m_shardingCapabilityObjectIds = shardingCapabilityObjectIds;
}

}
