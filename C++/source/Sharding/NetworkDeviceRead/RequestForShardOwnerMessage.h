/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef REQUESTFORSHARDOWNERMESSAGE_H
#define REQUESTFORSHARDOWNERMESSAGE_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

using namespace WaveNs;

namespace WaveNs
{

class RequestForShardOwnerMessage : public ManagementInterfaceMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                            RequestForShardOwnerMessage ();
                            RequestForShardOwnerMessage (const string &resourceName, const ResourceId &shardingCategory);
        virtual            ~RequestForShardOwnerMessage ();

                string      getResourceName             () const;
                void        setResourceName             (const string &resourceName);

                ResourceId  getShardingCategory         () const;
                void        setShardingCategory         (const ResourceId &shardingCategory);

                string      getApplicationInstanceName  () const;
                void        setApplicationInstanceName  (const string &applicationInstanceName);

    // Now the Data Members

    private :
        string     m_resourceName;
        ResourceId m_shardingCategory;
        string     m_applicationInstanceName;

    protected :
    public :
};

}

#endif // REQUESTFORSHARDOWNERMESSAGE_H
