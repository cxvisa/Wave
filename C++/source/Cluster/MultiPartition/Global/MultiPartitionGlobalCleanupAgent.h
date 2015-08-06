/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayaraman Iyer                                               *
 ***************************************************************************/

#ifndef MULTIPARTITIONGLOBALCLEANUPAGENT_H
#define MULTIPARTITIONGLOBALCLEANUPAGENT_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class MultiPartitionGlobalCleanupAgentContext;

class MultiPartitionGlobalCleanupAgent : protected WaveWorker
{
    private :
    protected :
    public :
                            MultiPartitionGlobalCleanupAgent                    (WaveObjectManager *pWaveObjectManager, string &partitionName, UI32 senderServiceId , ObjectId &ownerPartitionManagedObjectId);
        virtual            ~MultiPartitionGlobalCleanupAgent                    ();
        virtual ResourceId  execute                                             ();

                ResourceId  getListOfEnabledServicesStep                        (MultiPartitionGlobalCleanupAgentContext *pMultiPartitionGlobalCleanupAgentContext);
                ResourceId  sendMultiPartitionGlobalCleanupStep                 (MultiPartitionGlobalCleanupAgentContext *pMultiPartitionGlobalCleanupAgentContext);

                bool        requiresMultiPartitionGlobalCleanupNotification     (const WaveServiceId &prismServiceId);
                ObjectId    getOwnerPartitionManagedObjectId                    () const ;
                bool        getIsPartialCleanup                                 () const;

                void        setPartialCleanupTag                                (const ResourceId &partialCleanupTag);
                ResourceId  getPartialCleanupTag                                ();

    // Now the data members

    private :
                string     m_partitionName;
                UI32       m_senderServiceId;
                ObjectId   m_ownerPartitionManagedObjectId; 
                bool       m_isPartialCleanup;
                ResourceId m_partialCleanupTag;

    protected :
    public :
};

}

#endif // MULTIPARTITIONGLOBALCLEANUPAGENT_H
