/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayaraman Iyer                                               *
 ***************************************************************************/

#ifndef MULTIPARTITIONCLEANUPAGENT_H
#define MULTIPARTITIONCLEANUPAGENT_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class MultiPartitionCleanupAgentContext;

class MultiPartitionCleanupAgent : protected WaveWorker
{
    private :
    protected :
    public :
                            MultiPartitionCleanupAgent            (WaveObjectManager *pWaveObjectManager, string &partitionName, UI32 senderServiceId , ObjectId &ownerPartitionManagedObjectId);
        virtual            ~MultiPartitionCleanupAgent            ();
        virtual ResourceId  execute                             ();

                ResourceId  getListOfEnabledServicesStep        (MultiPartitionCleanupAgentContext *pMultiPartitionCleanupAgentContext);
                ResourceId  sendMultiPartitionCleanupStep         (MultiPartitionCleanupAgentContext *pMultiPartitionCleanupAgentContext);

                bool        requiresMultiPartitionCleanupNotification (const PrismServiceId &prismServiceId);
                ObjectId    getOwnerPartitionManagedObjectId    () const ;
                bool        getIsPartialCleanup                 () const;

                void        setPartialCleanupTag                (const ResourceId &partialCleanupTag);
                ResourceId  getPartialCleanupTag                ();


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

#endif // SLOTFAILOVERAGENT_H
