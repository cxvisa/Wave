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
                                RequestForShardOwnerMessage (const vector<string> &resourceNames, const ResourceId &shardingCategory);
        virtual                ~RequestForShardOwnerMessage ();

                vector<string>  getResourceNames            () const;
                void            setResourceNames            (const vector<string> &resourceNames);

                ResourceId      getShardingCategory         () const;
                void            setShardingCategory         (const ResourceId &shardingCategory);

                vector<string>  getApplicationInstanceNames () const;
                void            setApplicationInstanceNames (const vector<string> &applicationInstanceNames);

    // Now the Data Members

    private :
        vector<string> m_resourceNames;
        ResourceId     m_shardingCategory;
        vector<string> m_applicationInstanceNames;

    protected :
    public :
};

}

#endif // REQUESTFORSHARDOWNERMESSAGE_H
