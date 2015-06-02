/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayaraman Iyer                                               *
 ***************************************************************************/

#ifndef MULTIPARTITIONLOCALMESSAGES_H
#define MULTIPARTITIONLOCALMESSAGES_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

class MultiPartitionDeleteLocalPartitionMessage : public ManagementInterfaceMessage
{
    private :
        void                    setupAttributesForSerialization  ();

    protected :
    public :
                                MultiPartitionDeleteLocalPartitionMessage (void);
                                MultiPartitionDeleteLocalPartitionMessage (const string &partitionName);
        virtual                ~MultiPartitionDeleteLocalPartitionMessage (void);

                string          getPartitionName                    (void) const;
                void            setPartitionName                    (const string &partitionName);

               void            setSenderServiceId               (const UI32 &senderServiceId);
                UI32            getSenderServiceId               (void) const ; 

                ObjectId        getOwnerPartitionManagedObjectId    () const ;
                void            setOwnerPartitionManagedObjectId    (const ObjectId &objId);

                bool            getIsPartialCleanup                 () const;

                void            setPartialCleanupTag                (const ResourceId &partialCleanupTag);
                ResourceId      getPartialCleanupTag                ();


    // Now the data members
    private :
                string          m_partitionName;
                UI32            m_senderServiceId;
                ObjectId        m_ownerPartitionManagedObjectId;
                bool            m_isPartialCleanup;
                ResourceId      m_partialCleanupTag;


    protected :
    public :
};
}

#endif // MULTIPARTITIONLOCALMESSAGES_H
