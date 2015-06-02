/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayraman Iyer                                                *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveAsynchronousContextForMultiPartitionCleanup.h"
#include "Framework/Utils/AssertUtils.h"

namespace WaveNs
{

WaveAsynchronousContextForMultiPartitionCleanup::WaveAsynchronousContextForMultiPartitionCleanup (PrismElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext)
    : PrismAsynchronousContext  (pCaller, pCallback, pCallerContext),
      m_isPartialCleanup        (false),
      m_partialCleanupTag       (FRAMEWORK_ERROR)
{
}

WaveAsynchronousContextForMultiPartitionCleanup::~WaveAsynchronousContextForMultiPartitionCleanup ()
{
}

string WaveAsynchronousContextForMultiPartitionCleanup::getPartitionName () const
{
    return (m_partitionName);
}

void WaveAsynchronousContextForMultiPartitionCleanup::setPartitionName (const string &partitionName)
{
    m_partitionName = partitionName;
}

ObjectId WaveAsynchronousContextForMultiPartitionCleanup::getOwnerPartitionManagedObjectId() const
{
    return (m_ownerPartitionManagedObjectId);
}

void WaveAsynchronousContextForMultiPartitionCleanup::setOwnerPartitionManagedObjectId (const ObjectId &objId)
{
    m_ownerPartitionManagedObjectId = objId;
}

bool WaveAsynchronousContextForMultiPartitionCleanup::getIsPartialCleanup () const
{
    return m_isPartialCleanup;
}

void WaveAsynchronousContextForMultiPartitionCleanup::setPartialCleanupTag (const ResourceId &partialCleanupTag)
{
    m_isPartialCleanup = true;

    m_partialCleanupTag = partialCleanupTag;
}

ResourceId WaveAsynchronousContextForMultiPartitionCleanup::getPartialCleanupTag ()
{
    prismAssert (true == m_isPartialCleanup, __FILE__, __LINE__);

    return m_partialCleanupTag;
}

}

