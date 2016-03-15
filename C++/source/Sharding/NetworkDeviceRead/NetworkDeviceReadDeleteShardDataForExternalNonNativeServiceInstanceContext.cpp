/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Sharding/NetworkDeviceRead/NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceContext.h"

namespace WaveNs
{

NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceContext::NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps)
{
}

NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceContext::~NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceContext ()
{
}

vector<ObjectId> NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceContext::getServiceInstanceObjectIds () const
{
    return (m_serviceInstanceObjectIds);
}

void NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceContext::setServiceInstanceObjectIds (const vector<ObjectId> &serviceInstanceObjectIds)
{
    m_serviceInstanceObjectIds = serviceInstanceObjectIds;
}

}
