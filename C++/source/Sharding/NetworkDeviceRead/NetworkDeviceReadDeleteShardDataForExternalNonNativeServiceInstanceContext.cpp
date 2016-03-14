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

ObjectId NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceContext::getServiceInstanceObjectId () const
{
    return (m_serviceInstanceObjectId);
}

void NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceContext::setServiceInstanceObjectId (const ObjectId &serviceInstanceObjectId)
{
    m_serviceInstanceObjectId = serviceInstanceObjectId;
}

}
