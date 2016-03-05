/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef NETWORKDEVICEREADSHARDINGCATEGORYMANAGEDOBJECT_H
#define NETWORKDEVICEREADSHARDINGCATEGORYMANAGEDOBJECT_H

#include "ServiceManagement/Global/ShardableResourceCategory.h"

#include <vector>

using namespace std;

namespace WaveNs
{

class NetworkDeviceReadShardingCategoryManagedObject : public ShardableResourceCategory
{
    private :
        void setupAttributesForPersistence ();
        void setupAttributesForCreate      ();

    protected :
    public :
                 NetworkDeviceReadShardingCategoryManagedObject (WaveObjectManager *pWaveObjectManager);
        virtual ~NetworkDeviceReadShardingCategoryManagedObject ();

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

#endif // NETWORKDEVICEREADSHARDINGCATEGORYMANAGEDOBJECT_H
