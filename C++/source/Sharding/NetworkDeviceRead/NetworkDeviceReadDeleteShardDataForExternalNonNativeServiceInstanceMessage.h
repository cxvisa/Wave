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
        virtual ~NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage ();

        ObjectId getServiceInstanceObjectId () const;
        void     setServiceInstanceObjectId (const ObjectId &serviceInstanceObjectId);

    // Now the Data Members

    private :
        ObjectId m_serviceInstanceObjectId;

    protected :
    public :
};

}

#endif // NETWORKDEVICEREADDELETESHARDDATAFOREXTERNALNONNATIVESERVICEINSTANCEMESSAGE_H
