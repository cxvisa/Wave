/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef REQUESTFORSHARDOWNERCONTEXT_H
#define REQUESTFORSHARDOWNERCONTEXT_H

#include <map>

#include "Framework/ObjectModel/ObjectId.h"
#include "Framework/Utils/WaveLinearSequencerContext.h"

using namespace std;

namespace WaveNs
{

class RequestForShardOwnerContext : public WaveLinearSequencerContext
{
    private :
    protected :
    public :
                 RequestForShardOwnerContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual ~RequestForShardOwnerContext ();

        vector<string>  getResourceNames            () const;
        void            setResourceNames            (const vector<string> &resourceNames);

        ResourceId      getShardingCategory         () const;
        void            setShardingCategory         (const ResourceId &shardingCategory);

        vector<string>  getApplicationInstanceNames () const;
        void            setApplicationInstanceNames (const vector<string> &applicationInstanceNames);

        ObjectId    getShardingCategoryObjectId       () const;
        void        setShardingCategoryObjectId       (const ObjectId &shardingCategoryObjectId);

        map<string, ObjectId> &getApplicationInstanceObjectIdByResourceNameMap ();

        map<ObjectId, UI32>   &getShardOwnerCountsByapplicationInstanceObjectIdMap ();

        const ObjectId getApplicationInstanceObjectIdWithMinimalShardOwnerCount () const;

        map<ObjectId, string> &getApplicationInstanceNameByObjectIdMap ();

        void populateApplicationInstanceNameByObjectIdMap           ();
        void incrementShardOwnerCountForApplicationInstanceObjectId (const ObjectId applicationInstanceObjectId);

    // Now the Data Members

    private :
        vector<string>        m_resourceNames;
        ResourceId            m_shardingCategory;
        vector<string>        m_applicationInstanceNames;

        ObjectId              m_shardingCategoryObjectId;

        map<string, ObjectId> m_applicationInstanceObjectIdByResourceNameMap;
        map<ObjectId, UI32>   m_shardOwnerCountsByapplicationInstanceObjectIdMap;
        map<ObjectId, string> m_applicationInstanceNameByObjectIdMap;

    protected :
    public :
};

}

#endif // REQUESTFORSHARDOWNERCONTEXT_H
