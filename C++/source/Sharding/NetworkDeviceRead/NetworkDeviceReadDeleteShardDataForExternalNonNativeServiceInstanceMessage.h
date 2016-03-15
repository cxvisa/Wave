/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef NETWORKDEVICEREADDELETESHARDDATAFOREXTERNALNONNATIVESERVICEINSTANCEMESSAGE_H
#define NETWORKDEVICEREADDELETESHARDDATAFOREXTERNALNONNATIVESERVICEINSTANCEMESSAGE_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

class NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage : public ManagementInterfaceMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                 NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage ();
                 NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage (const ObjectId &serviceInstanceObjectId);
                 NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage (const vector<ObjectId> &serviceInstanceObjectIds);
        virtual ~NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage ();

        vector<ObjectId> getServiceInstanceObjectIds () const;
        void             setServiceInstanceObjectIds (const vector<ObjectId> &serviceInstanceObjectIds);

    // Now the Data Members

    private :
        vector<ObjectId> m_serviceInstanceObjectIds;

    protected :
    public :
};

}

#endif // NETWORKDEVICEREADDELETESHARDDATAFOREXTERNALNONNATIVESERVICEINSTANCEMESSAGE_H
