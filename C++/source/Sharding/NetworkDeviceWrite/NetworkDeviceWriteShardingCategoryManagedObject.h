/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef NETWORKDEVICEWRITESHARDINGCATEGORYMANAGEDOBJECT_H
#define NETWORKDEVICEWRITESHARDINGCATEGORYMANAGEDOBJECT_H

#include "ServiceManagement/Global/ShardableResourceCategory.h"

#include <vector>

using namespace std;

namespace WaveNs
{

class NetworkDeviceWriteShardingCategoryManagedObject : public ShardableResourceCategory
{
    private :
        void setupAttributesForPersistence ();
        void setupAttributesForCreate      ();

    protected :
    public :
                 NetworkDeviceWriteShardingCategoryManagedObject (WaveObjectManager *pWaveObjectManager);
        virtual ~NetworkDeviceWriteShardingCategoryManagedObject ();

        static string getClassName ();

        vector<ObjectId> getShardData        () const;
        void             addToShardData      (const ObjectId &shardData);
        void             deleteFromShardData (const ObjectId &shardData);
        void             setShardData        (const vector<ObjectId> &shardData);

    // Now the Data Members

    private :
        vector<ObjectId> m_shardData;

    protected :
    public :
};

}

#endif // NETWORKDEVICEWRITESHARDINGCATEGORYMANAGEDOBJECT_H
