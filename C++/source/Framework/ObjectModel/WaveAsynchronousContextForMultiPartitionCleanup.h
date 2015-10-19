/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayaraman Iyer                                               *
 ***************************************************************************/

#ifndef WAVEASYNCHRONOUSCONTEXTFORMULTIPARTITIONCLEANUP_H
#define WAVEASYNCHRONOUSCONTEXTFORMULTIPARTITIONCLEANUP_H

#include "Framework/Utils/WaveAsynchronousContext.h"

namespace WaveNs
{

class WaveAsynchronousContextForMultiPartitionCleanup : public WaveAsynchronousContext
{
    private :
    protected :
    public :
                        WaveAsynchronousContextForMultiPartitionCleanup (WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext = NULL);
        virtual        ~WaveAsynchronousContextForMultiPartitionCleanup ();

        string          getPartitionName                                 () const;
        void            setPartitionName                                 (const string &partitionName);

        ObjectId        getOwnerPartitionManagedObjectId                 () const;
        void            setOwnerPartitionManagedObjectId                 (const ObjectId &objId);
        bool            getIsPartialCleanup                              () const;

        void            setPartialCleanupTag                             (const ResourceId &partialCleanupTag);
        ResourceId      getPartialCleanupTag                             ();

    // Now the data members

    private :
        string        m_partitionName;
        ObjectId      m_ownerPartitionManagedObjectId; 
        bool          m_isPartialCleanup;
        ResourceId    m_partialCleanupTag;


    protected :
    public :
};

}

#endif // WAVEASYNCHRONOUSCONTEXTFORMULTIPARTITIONCLEANUP_H
