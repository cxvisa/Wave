/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Sharding/ShardingCapabilitiesToolKit.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/AssertUtils.h"

#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContext.h"
#include "Framework/ObjectModel/WaveManagedObjectToolKit.h"
#include "Framework/ObjectModel/WaveObjectManagerToolKit.h"
#include "Framework/Utils/TraceUtils.h"
#include "ServiceManagement/Local/ExternalNonNativeServiceInstanceManagedObject.h"
#include "Sharding/NetworkDeviceRead/NetworkDeviceReadShardDataManagedObject.h"
#include "Sharding/NetworkDeviceRead/NetworkDeviceReadShardDataManagedObject.h"
#include "Sharding/NetworkDeviceRead/NetworkDeviceReadShardingCategoryManagedObject.h"
#include "Sharding/NetworkDeviceWrite/NetworkDeviceWriteShardDataManagedObject.h"
#include "Sharding/NetworkDeviceWrite/NetworkDeviceWriteShardingCategoryManagedObject.h"

namespace WaveNs
{

WaveMutex               ShardingCapabilitiesToolKit::m_mutex;
map<string, ResourceId> ShardingCapabilitiesToolKit::m_tokenToResourceIdMap;
map<string, string>     ShardingCapabilitiesToolKit::m_tokenToClassMap;

ShardingCapabilitiesToolKit::ShardingCapabilitiesToolKit ()
{
}

ShardingCapabilitiesToolKit::~ShardingCapabilitiesToolKit ()
{
}

void ShardingCapabilitiesToolKit::initialize ()
{
    m_mutex.lock ();

    vector<ResourceId> resourceIds;

    //WaveNs::trace (TRACE_LEVEL_INFO, "ShardingCapabilitiesToolKit::initialize");

    FrameworkToolKit::getResourceIdsForResourceEnum (WRC_ENUM_ExternalServiceShardingCategoryTokens, resourceIds);

    //WaveNs::tracePrintf (TRACE_LEVEL_INFO, true, false, "ShardingCapabilitiesToolKit::initialize : Number Of Tokens : %u, %08x", resourceIds.size (), WRC_ENUM_ExternalServiceShardingCategoryTokens);

    vector<ResourceId>::const_iterator element    = resourceIds.begin ();
    vector<ResourceId>::const_iterator endElement = resourceIds.end   ();

    while (endElement != element)
    {
        const ResourceId resourceId     = *element;
        const string     resourceString = FrameworkToolKit::localize (resourceId);

        if ((m_tokenToResourceIdMap.end ()) == (m_tokenToResourceIdMap.find (resourceString)))
        {
            m_tokenToResourceIdMap[resourceString] = resourceId;

            //WaveNs::tracePrintf (TRACE_LEVEL_INFO, true, false, "ShardingCapabilitiesToolKit::initialize : %s : %d, %s", resourceString.c_str (), resourceId, (FrameworkToolKit::localizeToSourceCodeEnum (resourceId)).c_str ());
        }
        else
        {
            WaveNs::waveAssert (false, __FILE__, __LINE__);
        }

        element++;
    }

    m_tokenToClassMap[FrameworkToolKit::localize (WAVE_EXTERNAL_SERVICE_SHARD_CATEGORY_TOKEN_NETWORK_DEVICE_READ)]  = NetworkDeviceReadShardingCategoryManagedObject::getClassName ();
    m_tokenToClassMap[FrameworkToolKit::localize (WAVE_EXTERNAL_SERVICE_SHARD_CATEGORY_TOKEN_NETWORK_DEVICE_WRITE)] = NetworkDeviceWriteShardingCategoryManagedObject::getClassName ();

    m_mutex.unlock ();
}

const string ShardingCapabilitiesToolKit::getClassNameByToken (const string &token)
{
    m_mutex.lock ();

    const string className = m_tokenToClassMap[token];

    m_mutex.unlock ();

    return (className);
}

const ResourceId ShardingCapabilitiesToolKit::getResourceIdFromToken (const string &token)
{
    m_mutex.lock ();

    const ResourceId resourceId = m_tokenToResourceIdMap[token];

    m_mutex.unlock ();

    return (resourceId);
}

const ObjectId ShardingCapabilitiesToolKit::getShardableResourceCategoryObjectIdByToken (const string &token)
{
    const string className = getClassNameByToken (token);

    vector<WaveManagedObject *> *pQueryResults = WaveObjectManagerToolKit::querySynchronouslyByName (className, token);

    WaveNs::waveAssert (NULL != pQueryResults, __FILE__, __LINE__);

    const UI32 numberOfQueryResults = pQueryResults->size ();

    tracePrintf (TRACE_LEVEL_INFO, true, false, "ShardingCapabilitiesToolKit::getShardableResourceCategoryObjectIdByToken : %s : %s : %d", className.c_str (), token.c_str (), numberOfQueryResults);

    ObjectId objectId = ObjectId::NullObjectId;

    if (0 == numberOfQueryResults)
    {
        return (ObjectId::NullObjectId);
    }
    else if (1 == numberOfQueryResults)
    {
        WaveManagedObject *pWaveManagedObject = (*pQueryResults)[0];

        WaveNs::waveAssert (NULL != pWaveManagedObject, __FILE__, __LINE__);

        objectId = pWaveManagedObject->getObjectId ();
    }
    else
    {
        WaveNs::waveAssert (false, __FILE__, __LINE__);
    }

    WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector (pQueryResults);

    return (objectId);
}

const vector<ObjectId>  ShardingCapabilitiesToolKit::getServiceInstanceObjectIdsForShardableResourceCategory (const ObjectId ShardableResourceCategoryObjectId)
{
    WaveManagedObjectSynchronousQueryContext synchronousQueryContext (ExternalNonNativeServiceInstanceManagedObject::getClassName ());

    vector<ObjectId> shardingCapabilities;

    shardingCapabilities.push_back (ShardableResourceCategoryObjectId);

    AttributeObjectIdVectorAssociation *pAttributeObjectIdVectorAssociation = new AttributeObjectIdVectorAssociation (shardingCapabilities, "shardingCapabilities", ExternalNonNativeServiceInstanceManagedObject::getClassName (), ObjectId::NullObjectId, ShardableResourceCategory::getClassName ());

    synchronousQueryContext.setAttributeObjectIdVectorAssociation (pAttributeObjectIdVectorAssociation);

    vector<WaveManagedObject *> *pQueryResults = WaveObjectManagerToolKit::querySynchronously (&synchronousQueryContext);

    WaveNs::waveAssert (NULL != pQueryResults, __FILE__, __LINE__);

    const UI32 numberOfQueryResults = pQueryResults->size ();
          UI32 i                    = 0;

    vector<ObjectId> serviceInstanceObjectIds;

    for (i = 0; i < numberOfQueryResults; i++)
    {
        WaveManagedObject *pWaveManagedObject = (*pQueryResults)[i];

        WaveNs::waveAssert (NULL != pWaveManagedObject, __FILE__, __LINE__);

        const ObjectId objectId = pWaveManagedObject->getObjectId ();
        const string   name     = pWaveManagedObject->getName     ();

        WaveNs::tracePrintf (TRACE_LEVEL_INFO, "ShardingCapabilitiesToolKit::getServiceInstanceObjectIdsForShardableResourceCategory : Name : %s", name.c_str ());

        serviceInstanceObjectIds.push_back (objectId);
    }

    return (serviceInstanceObjectIds);
}

const UI32 ShardingCapabilitiesToolKit::getNumberOfShardedResourcesByCategoryAndServiceInstance (const ObjectId ShardableResourceCategoryObjectId, const ObjectId &serviceInstanceObjectId)
{
    WaveManagedObjectSynchronousQueryContext synchronousQueryContext (NetworkDeviceReadShardDataManagedObject::getClassName ());

    // FIXME : Sagar : We need to get the class name and the fields dynamically.

    synchronousQueryContext.addAndAttribute (new AttributeObjectIdAssociation (ShardableResourceCategoryObjectId, "networkDeviceReadShardingCategory", NetworkDeviceReadShardingCategoryManagedObject::getClassName ()));
    synchronousQueryContext.addAndAttribute (new AttributeObjectIdAssociation (serviceInstanceObjectId,           "serviceInstance",                   ExternalNonNativeServiceInstanceManagedObject::getClassName ()));

    UI32 numberOfShardedResources = 0;

    WaveObjectManagerToolKit::querySynchronouslyForCount (&synchronousQueryContext, numberOfShardedResources);

    return (numberOfShardedResources);
}

const ObjectId ShardingCapabilitiesToolKit::getServiceInstanceObjectIdWithMinimalShardCategoryOwnership (const ObjectId shardableResourceCategoryObjectId)
{
    if (ObjectId::NullObjectId == shardableResourceCategoryObjectId)
    {
        return (shardableResourceCategoryObjectId);
    }

    vector<ObjectId> serviceInstanceObjectIds = getServiceInstanceObjectIdsForShardableResourceCategory (shardableResourceCategoryObjectId);

    vector<ObjectId>::const_iterator element                                                  = serviceInstanceObjectIds.begin ();
    vector<ObjectId>::const_iterator endElement                                               = serviceInstanceObjectIds.end   ();
    ObjectId                         ServiceInstanceObjectIdWithMinimalShardCategoryOwnership = ObjectId::NullObjectId;
    UI32                             minimalCount                                             = UINT32_MAX;

    while (endElement != element)
    {
        const ObjectId serviceInstanceObjectId = *element;

        UI32 count = getNumberOfShardedResourcesByCategoryAndServiceInstance (shardableResourceCategoryObjectId, serviceInstanceObjectId);

        if (minimalCount > count)
        {
            minimalCount                                             = count;
            ServiceInstanceObjectIdWithMinimalShardCategoryOwnership = serviceInstanceObjectId;
        }

        element++;
    }

    return (ServiceInstanceObjectIdWithMinimalShardCategoryOwnership);
}

void ShardingCapabilitiesToolKit::getServiceInstanceObjectIdToShardCategoryOwnershipCountMap (const ObjectId shardableResourceCategoryObjectId, map<ObjectId, UI32> &resultsMap)
{
    if (ObjectId::NullObjectId == shardableResourceCategoryObjectId)
    {
        return;
    }

    vector<ObjectId> serviceInstanceObjectIds = getServiceInstanceObjectIdsForShardableResourceCategory (shardableResourceCategoryObjectId);

    vector<ObjectId>::const_iterator element    = serviceInstanceObjectIds.begin ();
    vector<ObjectId>::const_iterator endElement = serviceInstanceObjectIds.end   ();

    while (endElement != element)
    {
        const ObjectId serviceInstanceObjectId = *element;

        UI32 count = getNumberOfShardedResourcesByCategoryAndServiceInstance (shardableResourceCategoryObjectId, serviceInstanceObjectId);

        resultsMap[serviceInstanceObjectId] = count;

        element++;
    }

    return;
}

const ObjectId ShardingCapabilitiesToolKit::getServiceInstanceObjectIdByshardableResourceCategoryAndReosurce (const ObjectId shardableResourceCategoryObjectId, const string &resourceName)
{
    WaveManagedObjectSynchronousQueryContext synchronousQueryContext (NetworkDeviceReadShardDataManagedObject::getClassName ());

    // FIXME : Sagar : We need to get the class name and the fields dynamically.

    synchronousQueryContext.addAndAttribute (new AttributeObjectIdAssociation (shardableResourceCategoryObjectId, "networkDeviceReadShardingCategory", NetworkDeviceReadShardingCategoryManagedObject::getClassName ()));
    synchronousQueryContext.addAndAttribute (new AttributeString              (resourceName,                      "name"));

    vector<WaveManagedObject *> *pQueryResults = WaveObjectManagerToolKit::querySynchronously (&synchronousQueryContext);

    WaveNs::waveAssert (NULL != pQueryResults, __FILE__, __LINE__);

    const UI32 numberOfQueryResults = pQueryResults->size ();

    tracePrintf (TRACE_LEVEL_INFO, true, false, "ShardingCapabilitiesToolKit::getServiceInstanceObjectIdByshardableResourceCategoryAndReosurce : %s : %d", resourceName.c_str (), numberOfQueryResults);

    ObjectId objectId = ObjectId::NullObjectId;

    if (0 == numberOfQueryResults)
    {
        return (ObjectId::NullObjectId);
    }
    else if (1 == numberOfQueryResults)
    {
        WaveManagedObject *pWaveManagedObject = (*pQueryResults)[0];

        WaveNs::waveAssert (NULL != pWaveManagedObject, __FILE__, __LINE__);

        NetworkDeviceReadShardDataManagedObject *pNetworkDeviceReadShardDataManagedObject = dynamic_cast<NetworkDeviceReadShardDataManagedObject *> (pWaveManagedObject);

        WaveNs::waveAssert (NULL != pNetworkDeviceReadShardDataManagedObject, __FILE__, __LINE__);


        objectId = pNetworkDeviceReadShardDataManagedObject->getServiceInstance ();
    }
    else
    {
        WaveNs::waveAssert (false, __FILE__, __LINE__);
    }

    WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector (pQueryResults);

    return (objectId);
}

void ShardingCapabilitiesToolKit::getServiceInstanceObjectIdsByshardableResourceCategoryAndReosurces (const ObjectId shardableResourceCategoryObjectId, const vector<string> &resourceNames, map<string, ObjectId> &resultsMap)
{
    WaveManagedObjectSynchronousQueryContext synchronousQueryContext (NetworkDeviceReadShardDataManagedObject::getClassName ());

    // FIXME : Sagar : We need to get the class name and the fields dynamically.

    synchronousQueryContext.createConditionSet ("A");
    synchronousQueryContext.addAttributeToConditionSet ("A", new AttributeObjectIdAssociation (shardableResourceCategoryObjectId, "networkDeviceReadShardingCategory", NetworkDeviceReadShardingCategoryManagedObject::getClassName ()));

    if (resourceNames.empty ())
    {
        synchronousQueryContext.combineConditionSets ("A");
    }
    else
    {
        synchronousQueryContext.createConditionSet ("B");

        vector<string>::const_iterator element    = resourceNames.begin ();
        vector<string>::const_iterator endElement = resourceNames.end   ();

        while (endElement != element)
        {
            synchronousQueryContext.addAttributeToConditionSet ("B", new AttributeString (*element, "name"), WAVE_ATTRIBUTE_CONCATENATION_OPERATOR_OR, WAVE_ATTRIBUTE_CONDITION_OPERATOR_EQUAL);

            element++;
        }

        synchronousQueryContext.combineConditionSets ("A * B");
    }

    vector<WaveManagedObject *> *pQueryResults = WaveObjectManagerToolKit::querySynchronously (&synchronousQueryContext);

    WaveNs::waveAssert (NULL != pQueryResults, __FILE__, __LINE__);

    const UI32 numberOfQueryResults = pQueryResults->size ();
          UI32 i                    = 0;

    tracePrintf (TRACE_LEVEL_INFO, true, false, "ShardingCapabilitiesToolKit::getServiceInstanceObjectIdByshardableResourceCategoryAndReosurce : Query Results : %d", numberOfQueryResults);

    ObjectId objectId = ObjectId::NullObjectId;

    for (i = 0; i < numberOfQueryResults; i++)
    {
        WaveManagedObject *pWaveManagedObject = (*pQueryResults)[i];

        WaveNs::waveAssert (NULL != pWaveManagedObject, __FILE__, __LINE__);

        NetworkDeviceReadShardDataManagedObject *pNetworkDeviceReadShardDataManagedObject = dynamic_cast<NetworkDeviceReadShardDataManagedObject *> (pWaveManagedObject);

        WaveNs::waveAssert (NULL != pNetworkDeviceReadShardDataManagedObject, __FILE__, __LINE__);

        objectId = pNetworkDeviceReadShardDataManagedObject->getServiceInstance ();

        resultsMap[pNetworkDeviceReadShardDataManagedObject->getName ()] = objectId;
    }

    WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector (pQueryResults);

    return;
}

}
