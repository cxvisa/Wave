/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Sharding/NetworkDeviceRead/RequestForShardOwnerContext.h"

namespace WaveNs
{

RequestForShardOwnerContext::RequestForShardOwnerContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps)
{
}

RequestForShardOwnerContext::~RequestForShardOwnerContext ()
{
}


string RequestForShardOwnerContext::getResourceName () const
{
    return (m_resourceName);
}

void RequestForShardOwnerContext::setResourceName (const string &resourceName)
{
    m_resourceName = resourceName;
}

ResourceId RequestForShardOwnerContext::getShardingCategory () const
{
    return (m_shardingCategory);
}

void RequestForShardOwnerContext::setShardingCategory (const ResourceId &shardingCategory)
{
    m_shardingCategory = shardingCategory;
}

string RequestForShardOwnerContext::getApplicationInstanceName () const
{
    return (m_applicationInstanceName);
}

void RequestForShardOwnerContext::setApplicationInstanceName (const string &applicationInstanceName)
{
    m_applicationInstanceName = applicationInstanceName;
}

ObjectId RequestForShardOwnerContext::getApplicationInstanceObjectId () const
{
    return (m_applicationInstanceObjectId);
}

void RequestForShardOwnerContext::setApplicationInstanceObjectId (const ObjectId &applicationInstanceObjectId)
{
    m_applicationInstanceObjectId = applicationInstanceObjectId;
}

ObjectId RequestForShardOwnerContext::getNewApplicationInstanceObjectId () const
{
    return (m_newApplicationInstanceObjectId);
}

void RequestForShardOwnerContext::setNewApplicationInstanceObjectId (const ObjectId &newApplicationInstanceObjectId)
{
    m_newApplicationInstanceObjectId = newApplicationInstanceObjectId;
}

ObjectId RequestForShardOwnerContext::getShardingCategoryObjectId () const
{
    return (m_shardingCategoryObjectId);
}

void RequestForShardOwnerContext::setShardingCategoryObjectId (const ObjectId &shardingCategoryObjectId)
{
    m_shardingCategoryObjectId = shardingCategoryObjectId;
}

}
