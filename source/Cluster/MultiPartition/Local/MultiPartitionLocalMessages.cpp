/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayaraman Iyer                                               *
 ***************************************************************************/

#include "Cluster/MultiPartition/Local/MultiPartitionLocalMessages.h"
#include "Cluster/MultiPartition/Local/MultiPartitionLocalTypes.h"
#include "Cluster/MultiPartition/Local/MultiPartitionLocalObjectManager.h"
#include "Framework/Attributes/AttributeResourceId.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/FrameworkToolKit.h"

namespace WaveNs
{

//
// DeleteLocalPartition Message.
//

MultiPartitionDeleteLocalPartitionMessage::MultiPartitionDeleteLocalPartitionMessage ()
    : ManagementInterfaceMessage (MultiPartitionLocalObjectManager::getServiceName (), MULTI_PARTITION_DELETE_LOCAL_PARTITION_INSTANCE),
    m_partitionName            (""),
    m_senderServiceId          (0),
    m_isPartialCleanup         (false),
    m_partialCleanupTag        (FRAMEWORK_ERROR)

{
}

MultiPartitionDeleteLocalPartitionMessage::MultiPartitionDeleteLocalPartitionMessage (const string &partitionName)
    : ManagementInterfaceMessage (MultiPartitionLocalObjectManager::getServiceName (),MULTI_PARTITION_DELETE_LOCAL_PARTITION_INSTANCE),
    m_partitionName            (partitionName),
    m_senderServiceId          (0),
    m_isPartialCleanup         (false),
    m_partialCleanupTag        (FRAMEWORK_ERROR)
{
}

MultiPartitionDeleteLocalPartitionMessage::~MultiPartitionDeleteLocalPartitionMessage ()
{
}

void MultiPartitionDeleteLocalPartitionMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();
    
     addSerializableAttribute (new AttributeString      (&m_partitionName,                  "partitionName"));
     addSerializableAttribute (new AttributeUI32        (&m_senderServiceId,                "senderServiceId"));
     addSerializableAttribute (new AttributeObjectId    (&m_ownerPartitionManagedObjectId,  "ownerPartitionManagedObjectId"));
     addSerializableAttribute (new AttributeBool        (&m_isPartialCleanup,               "isPartialCleanup"));
     addSerializableAttribute (new AttributeResourceId  (&m_partialCleanupTag,              "partialCleanupTag"));
}

string MultiPartitionDeleteLocalPartitionMessage::getPartitionName(void) const
{
    return m_partitionName;
}

void   MultiPartitionDeleteLocalPartitionMessage::setPartitionName(const string &partitionName)
{
    m_partitionName = partitionName;
}

void    MultiPartitionDeleteLocalPartitionMessage::setSenderServiceId(const UI32 &senderServiceId)
{
    m_senderServiceId = senderServiceId;
}

UI32    MultiPartitionDeleteLocalPartitionMessage::getSenderServiceId(void) const  
{
    return m_senderServiceId;
}

ObjectId MultiPartitionDeleteLocalPartitionMessage::getOwnerPartitionManagedObjectId() const
{
    return (m_ownerPartitionManagedObjectId);
}

void MultiPartitionDeleteLocalPartitionMessage::setOwnerPartitionManagedObjectId (const ObjectId &objId)
{
    m_ownerPartitionManagedObjectId = objId;
}

bool MultiPartitionDeleteLocalPartitionMessage::getIsPartialCleanup () const
{
    return m_isPartialCleanup;
}

void MultiPartitionDeleteLocalPartitionMessage::setPartialCleanupTag (const ResourceId &partialCleanupTag)
{
    m_isPartialCleanup  = true;

    m_partialCleanupTag = partialCleanupTag;
}

ResourceId MultiPartitionDeleteLocalPartitionMessage::getPartialCleanupTag ()
{
    prismAssert (true == m_isPartialCleanup, __FILE__, __LINE__);

    return m_partialCleanupTag;
}

}

