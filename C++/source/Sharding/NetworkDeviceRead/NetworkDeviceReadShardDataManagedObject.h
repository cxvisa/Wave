/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef NETWORKDEVICEREADSHARDDATAMANAGEDOBJECT_H
#define NETWORKDEVICEREADSHARDDATAMANAGEDOBJECT_H

#include "ServiceManagement/Global/ShardData.h"

namespace WaveNs
{

class NetworkDeviceReadShardDataManagedObject : public ShardData
{
    private :
        void setupAttributesForPersistence ();
        void setupAttributesForCreate      ();

    protected :
    public :
                 NetworkDeviceReadShardDataManagedObject (WaveObjectManager *pWaveObjectManager);
        virtual ~NetworkDeviceReadShardDataManagedObject ();

        static string getClassName ();

        ObjectId getNetworkDeviceReadShardingCategory () const;
        void     setNetworkDeviceReadShardingCategory (const ObjectId &networkDeviceReadShardingCategory);

        ObjectId getServiceInstance () const;
        void     setServiceInstance (const ObjectId &serviceInstance);

    // Now the Data Members

    private :
        ObjectId m_networkDeviceReadShardingCategory;
        ObjectId m_service;
        ObjectId m_serviceInstance;
        vector<String> m_

    protected :
    public :
};

}

#endif // NETWORKDEVICEREADSHARDDATAMANAGEDOBJECT_H
