/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef REQUESTFORSHARDOWNERCONTEXT_H
#define REQUESTFORSHARDOWNERCONTEXT_H

#include "Framework/ObjectModel/ObjectId.h"
#include "Framework/Utils/WaveLinearSequencerContext.h"

namespace WaveNs
{

class RequestForShardOwnerContext : public WaveLinearSequencerContext
{
    private :
    protected :
    public :
                 RequestForShardOwnerContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual ~RequestForShardOwnerContext ();

        string      getResourceName                   () const;
        void        setResourceName                   (const string &resourceName);

        ResourceId  getShardingCategory               () const;
        void        setShardingCategory               (const ResourceId &shardingCategory);

        string      getApplicationInstanceName        () const;
        void        setApplicationInstanceName        (const string &applicationInstanceName);

        ObjectId    getApplicationInstanceObjectId    () const;
        void        setApplicationInstanceObjectId    (const ObjectId &applicationInstanceObjectId);

        ObjectId    getNewApplicationInstanceObjectId () const;
        void        setNewApplicationInstanceObjectId (const ObjectId &newApplicationInstanceObjectId);

        ObjectId    getShardingCategoryObjectId       () const;
        void        setShardingCategoryObjectId       (const ObjectId &shardingCategoryObjectId);

    // Now the Data Members

    private :
        string     m_resourceName;
        ResourceId m_shardingCategory;
        string     m_applicationInstanceName;
        ObjectId   m_applicationInstanceObjectId;
        ObjectId   m_newApplicationInstanceObjectId;
        ObjectId   m_shardingCategoryObjectId;

    protected :
    public :
};

}

#endif // REQUESTFORSHARDOWNERCONTEXT_H
