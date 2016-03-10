/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Sharding/NetworkDeviceRead/RequestForShardOwnerContext.h"

#include "Framework/ObjectModel/WaveManagedObjectToolKit.h"
#include "Framework/ObjectModel/WaveObjectManagerToolKit.h"
#include "ServiceManagement/Local/ExternalNonNativeServiceInstanceManagedObject.h"
namespace WaveNs
{

RequestForShardOwnerContext::RequestForShardOwnerContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps)
{
}

RequestForShardOwnerContext::~RequestForShardOwnerContext ()
{
}

vector<string> RequestForShardOwnerContext::getResourceNames () const
{
    return (m_resourceNames);
}

void RequestForShardOwnerContext::setResourceNames (const vector<string> &resourceNames)
{
    m_resourceNames = resourceNames;
}

ResourceId RequestForShardOwnerContext::getShardingCategory () const
{
    return (m_shardingCategory);
}

void RequestForShardOwnerContext::setShardingCategory (const ResourceId &shardingCategory)
{
    m_shardingCategory = shardingCategory;
}

vector<string> RequestForShardOwnerContext::getApplicationInstanceNames () const
{
    return (m_applicationInstanceNames);
}

void RequestForShardOwnerContext::setApplicationInstanceNames (const vector<string> &applicationInstanceNames)
{
    m_applicationInstanceNames = applicationInstanceNames ;
}

ObjectId RequestForShardOwnerContext::getShardingCategoryObjectId () const
{
    return (m_shardingCategoryObjectId);
}

void RequestForShardOwnerContext::setShardingCategoryObjectId (const ObjectId &shardingCategoryObjectId)
{
    m_shardingCategoryObjectId = shardingCategoryObjectId;
}

map<string, ObjectId> &RequestForShardOwnerContext::getApplicationInstanceObjectIdByResourceNameMap ()
{
    return (m_applicationInstanceObjectIdByResourceNameMap);
}

map<ObjectId, UI32> &RequestForShardOwnerContext::getShardOwnerCountsByapplicationInstanceObjectIdMap ()
{
    return (m_shardOwnerCountsByapplicationInstanceObjectIdMap);
}

const ObjectId RequestForShardOwnerContext::getApplicationInstanceObjectIdWithMinimalShardOwnerCount () const
{
    ObjectId applicationInstanceObjectIdWithMinimalShardOwnerCount = ObjectId::NullObjectId;
    UI32     minimalCount                                          = UINT32_MAX;
    UI32     count                                                 = 0;

    map<ObjectId, UI32>::const_iterator element    = m_shardOwnerCountsByapplicationInstanceObjectIdMap.begin ();
    map<ObjectId, UI32>::const_iterator endElement = m_shardOwnerCountsByapplicationInstanceObjectIdMap.end   ();

    while (endElement != element)
    {
        count = element->second;

        if (minimalCount > count)
        {
            minimalCount                                          = count;
            applicationInstanceObjectIdWithMinimalShardOwnerCount = element->first;
        }

        element++;
    }

    return (applicationInstanceObjectIdWithMinimalShardOwnerCount);
}

map<ObjectId, string> &RequestForShardOwnerContext::getApplicationInstanceNameByObjectIdMap ()
{
    return (m_applicationInstanceNameByObjectIdMap);
}

void RequestForShardOwnerContext::incrementShardOwnerCountForApplicationInstanceObjectId (const ObjectId applicationInstanceObjectId)
{
    UI32 count = m_shardOwnerCountsByapplicationInstanceObjectIdMap[applicationInstanceObjectId];

    m_shardOwnerCountsByapplicationInstanceObjectIdMap[applicationInstanceObjectId] = count + 1;
}

void RequestForShardOwnerContext::populateApplicationInstanceNameByObjectIdMap ()
{
    map<string, ObjectId>::const_iterator element                       = m_applicationInstanceObjectIdByResourceNameMap.begin ();
    map<string, ObjectId>::const_iterator endElement                    = m_applicationInstanceObjectIdByResourceNameMap.end   ();
    ObjectId                              applicationInstanceObjectId   = ObjectId::NullObjectId;
    vector<ObjectId>                      applicationInstanceObjectIds;
    string                                applicationInstanceName;
    set<ObjectId>                         applicationObjectIdSet;

    while (endElement != element)
    {
        applicationInstanceObjectId = element->second;

        if (ObjectId::NullObjectId != applicationInstanceObjectId)
        {
            applicationObjectIdSet.insert (applicationInstanceObjectId);
        }
        else
        {
            WaveNs::waveAssert (false, __FILE__, __LINE__);
        }

        element++;
    }

    if (applicationObjectIdSet.empty ())
    {
        return;
    }

    applicationInstanceObjectIds.insert (applicationInstanceObjectIds.begin (), applicationObjectIdSet.begin (), applicationObjectIdSet.end ());

    WaveManagedObjectSynchronousQueryContext synchronousQueryContext (ExternalNonNativeServiceInstanceManagedObject::getClassName ());

    synchronousQueryContext.addObjectIds   (applicationInstanceObjectIds);
    synchronousQueryContext.addSelectField ("name");

    vector<WaveManagedObject *> *pQueryResults = WaveObjectManagerToolKit::querySynchronously (&synchronousQueryContext);

    WaveNs::waveAssert (NULL != pQueryResults, __FILE__, __LINE__);

    vector<WaveManagedObject *>::const_iterator element1    = pQueryResults->begin ();
    vector<WaveManagedObject *>::const_iterator endElement1 = pQueryResults->end   ();

    while (endElement1 != element1)
    {
        WaveManagedObject *pWaveManagedObject = *element1;

        WaveNs::waveAssert (NULL != pWaveManagedObject, __FILE__, __LINE__);

        ExternalNonNativeServiceInstanceManagedObject *pExternalNonNativeServiceInstanceManagedObject = dynamic_cast<ExternalNonNativeServiceInstanceManagedObject *> (pWaveManagedObject);

        WaveNs::waveAssert (NULL != pExternalNonNativeServiceInstanceManagedObject, __FILE__, __LINE__);

        applicationInstanceObjectId = pExternalNonNativeServiceInstanceManagedObject->getObjectId ();
        applicationInstanceName     = pExternalNonNativeServiceInstanceManagedObject->getName     ();

        m_applicationInstanceNameByObjectIdMap[applicationInstanceObjectId] = applicationInstanceName;

        element1++;
    }

    WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector (pQueryResults);
}

}
