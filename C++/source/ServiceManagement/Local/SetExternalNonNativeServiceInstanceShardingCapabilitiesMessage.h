/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SETEXTERNALNONNATIVESERVICEINSTANCESHARDINGCAPABILITIESMESSAGE_H
#define SETEXTERNALNONNATIVESERVICEINSTANCESHARDINGCAPABILITIESMESSAGE_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

using namespace WaveNs;

namespace WaveNs
{

class SetExternalNonNativeServiceInstanceShardingCapabilitiesMessage : public ManagementInterfaceMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                 SetExternalNonNativeServiceInstanceShardingCapabilitiesMessage ();
                 SetExternalNonNativeServiceInstanceShardingCapabilitiesMessage (const string &applicationName, const string &applicationInstanceName, const vector<ResourceId> shardingCapabilities);
        virtual ~SetExternalNonNativeServiceInstanceShardingCapabilitiesMessage ();

                 string             getApplicationName          () const;
                 void               setApplicationName          (const string &applicationName);

                 string             getApplicationInstanceName  () const;
                 void               setApplicationInstanceName  (const string &applicationInstanceName);

                 vector<ResourceId> getShardingCapabilities     () const;
                 void               setShardingCapabilities     (const vector<ResourceId> shardingCapabilities);

    // Now the Data Members

    private :
        string             m_applicationName;
        string             m_applicationInstanceName;
        vector<ResourceId> m_shardingCapabilities;

    protected :
    public :
};

}

#endif // SETEXTERNALNONNATIVESERVICEINSTANCESHARDINGCAPABILITIESMESSAGE_H
