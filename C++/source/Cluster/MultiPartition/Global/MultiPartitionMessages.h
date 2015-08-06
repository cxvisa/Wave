/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayaraman Iyer                                               *
 ***************************************************************************/

#ifndef MULTIPARTITIONMESSAGES_H
#define MULTIPARTITIONMESSAGES_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

class MultiPartitionAddPartitionMessage : public ManagementInterfaceMessage
{
    private :
        void                    setupAttributesForSerialization  ();

    protected :
    public :
                                MultiPartitionAddPartitionMessage (void);
                                MultiPartitionAddPartitionMessage (const string &partitionName);
                                MultiPartitionAddPartitionMessage (const string &partitionName, const LocationId &partitionLocationId);
        virtual                ~MultiPartitionAddPartitionMessage (void);

                string          getPartitionName                    (void) const;
                void            setPartitionName                    (const string &partitionName);

                void            setPartitionLocationId        (const LocationId &partitionLocationId);
                LocationId      getPartitionLocationId        (void) const ; 

                void            setCreatedWavePartitionManagedObjectId  (const ObjectId &createdWavePartitionManagedObjectId);
                ObjectId        getCreatedWavePartitionManagedObjectId (void) const;

    // Now the data members
    private :
                string          m_partitionName;
                LocationId      m_partitionLocationId;
                ObjectId        m_createdWavePartitionManagedObjectId;

    protected :
    public :
};

class MultiPartitionDeletePartitionMessage : public ManagementInterfaceMessage
{
    private :
        void                    setupAttributesForSerialization  ();

    protected :
    public :
                                MultiPartitionDeletePartitionMessage (void);
                                MultiPartitionDeletePartitionMessage (const string &partitionName);
                                MultiPartitionDeletePartitionMessage (const string &partitionName, const LocationId &partitionLocationId);
        virtual                ~MultiPartitionDeletePartitionMessage (void);

                string          getPartitionName                    (void) const;
                void            setPartitionName                    (const string &partitionName);

                void            setPartitionLocationId       (const LocationId &partitionLocationId);
                LocationId      getPartitionLocationId       (void) const ; 

                void            setSenderServiceId           (const UI32 &senderServiceId);
                UI32            getSenderServiceId           (void) const ; 
                bool            getIsPartialCleanup          () const;

                void            setPartialCleanupTag         (const ResourceId &partialCleanupTag);
                ResourceId      getPartialCleanupTag         ();


    // Now the data members
    private :
                string          m_partitionName;
                UI32            m_senderServiceId;
                LocationId      m_partitionLocationId;
                bool            m_isPartialCleanup;
                ResourceId      m_partialCleanupTag;


    protected :
    public :
};

class MultiPartitionObjectManagerGetObjectIdForPartitionNameMessage : public WaveMessage
{
    private :
        void                    setupAttributesForSerialization                                 ();

    protected :
    public :
                                MultiPartitionObjectManagerGetObjectIdForPartitionNameMessage   ();
                                MultiPartitionObjectManagerGetObjectIdForPartitionNameMessage   (const string &partitionName);
        virtual                ~MultiPartitionObjectManagerGetObjectIdForPartitionNameMessage   ();

                void            setPartitionName                                                (const string &partitionName);
                string          getPartitionName                                                () const;

                void            setPartitionObjectId                                            (const ObjectId &partitionObjectId);
                ObjectId        getPartitionObjectId                                            () const;

    // Now the data members
    private :
                string          m_partitionName;        // input
                ObjectId        m_partitionObjectId;    // output

    protected :
    public :
};

}

#endif // MULTIPARTITIONMESSAGES_H
