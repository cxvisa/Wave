/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef NETWORKDEVICEWRITESHARDDATAMANAGEDOBJECT_H
#define NETWORKDEVICEWRITESHARDDATAMANAGEDOBJECT_H

#include "ServiceManagement/Global/ShardData.h"

namespace WaveNs
{

class NetworkDeviceWriteShardDataManagedObject : public ShardData
{
    private :
        void setupAttributesForPersistence ();
        void setupAttributesForCreate      ();
        void setupKeys                     ();

    protected :
    public :
                 NetworkDeviceWriteShardDataManagedObject (WaveObjectManager *pWaveObjectManager);
        virtual ~NetworkDeviceWriteShardDataManagedObject ();

        static string getClassName ();

        ObjectId getNetworkDeviceWriteShardingCategory () const;
        void     setNetworkDeviceWriteShardingCategory (const ObjectId &networkDeviceWriteShardingCategory);

        ObjectId getServiceInstance () const;
        void     setServiceInstance (const ObjectId &serviceInstance);

    // Now the Data Members

    private :
        ObjectId m_networkDeviceWriteShardingCategory;
        ObjectId m_serviceInstance;

    protected :
    public :
};

}

#endif // NETWORKDEVICEWRITESHARDDATAMANAGEDOBJECT_H
