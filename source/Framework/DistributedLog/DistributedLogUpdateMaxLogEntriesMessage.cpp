/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#include "Framework/DistributedLog/DistributedLogUpdateMaxLogEntriesMessage.h"
#include "Framework/DistributedLog/DistributedLogTypes.h"
#include "Framework/DistributedLog/DistributedLogObjectManager.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/FrameworkToolKit.h"

namespace WaveNs
{

DistributedLogUpdateMaxLogEntriesMessage::DistributedLogUpdateMaxLogEntriesMessage ()
    : ManagementInterfaceMessage (DistributedLogObjectManager::getServiceName (), DISTRIBUTED_LOG_UPDATE_MAX_LOG_ENTRIES),
    m_maxLogEntries (10000)
{
}

DistributedLogUpdateMaxLogEntriesMessage::DistributedLogUpdateMaxLogEntriesMessage (const UI32 &maxLogEntries)
    : ManagementInterfaceMessage (DistributedLogObjectManager::getServiceName (), DISTRIBUTED_LOG_UPDATE_MAX_LOG_ENTRIES),
    m_maxLogEntries (maxLogEntries)
{
}

DistributedLogUpdateMaxLogEntriesMessage::~DistributedLogUpdateMaxLogEntriesMessage ()
{
}

void DistributedLogUpdateMaxLogEntriesMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();
    
     addSerializableAttribute (new AttributeUI32 (&m_maxLogEntries, "maxLogEntries"));
}

UI32 DistributedLogUpdateMaxLogEntriesMessage::getMaxLogEntries () const
{
    return (m_maxLogEntries);
}
 
}
