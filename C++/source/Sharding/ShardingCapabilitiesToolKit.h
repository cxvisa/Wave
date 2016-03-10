/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SHARDINGCAPABILITIESTOOLKIT_H
#define SHARDINGCAPABILITIESTOOLKIT_H

#include <string>
#include <map>

#include "Framework/Types/Types.h"
#include "Framework/Utils/WaveMutex.h"
#include "Framework/ObjectModel/ObjectId.h"

using namespace std;

namespace WaveNs
{

class ShardingCapabilitiesToolKit
{
    private :
                    ShardingCapabilitiesToolKit ();

        void static initialize                  ();

    protected :
    public :
        virtual                       ~ShardingCapabilitiesToolKit                                      ();

        static  const ResourceId       getResourceIdFromToken                                           (const string &token);

        static  const string           getClassNameByToken                                              (const string &token);

        static  const ObjectId         getShardableResourceCategoryObjectIdByToken                      (const string &token);

        static const vector<ObjectId>  getServiceInstanceObjectIdsForShardableResourceCategory          (const ObjectId ShardableResourceCategoryObjectId);

        static const UI32              getNumberOfShardedResourcesByCategoryAndServiceInstance          (const ObjectId ShardableResourceCategoryObjectId, const ObjectId &serviceInstanceObjectId);

        static const ObjectId          getServiceInstanceObjectIdWithMinimalShardCategoryOwnership      (const ObjectId shardableResourceCategoryObjectId);

        static const ObjectId          getServiceInstanceObjectIdByshardableResourceCategoryAndReosurce (const ObjectId shardableResourceCategoryObjectId, const string &resourceName);

    // Now the data members

    private :
        static WaveMutex               m_mutex;
        static map<string, ResourceId> m_tokenToResourceIdMap;
        static map<string, string>     m_tokenToClassMap;

    protected :
    public :

        friend class ServiceManagementObjectManager;
        friend class WaveClient;
};

}

#endif // SHARDINGCAPABILITIESTOOLKIT_H
