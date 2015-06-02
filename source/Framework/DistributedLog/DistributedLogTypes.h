/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#ifndef DISTRIBUTEDLOGTYPES_H
#define DISTRIBUTEDLOGTYPES_H

namespace WaveNs
{

typedef enum
{
    DISTRIBUTED_LOG_ADD_LOG_ENTRY = 0,
    DISTRIBUTED_LOG_UPDATE_MAX_LOG_ENTRIES,
    DISTRIBUTED_LOG_ADD_LOG_ENTRY_MANAGEMENT_INTERFACE,
    DISTRIBUTED_LOG_UPDATE_MAX_LOG_ENTRIES_MANAGEMENT_INTERFACE,
    DISTRIBUTED_LOG_INVOKE_ADD_LOG_API,
    DISTRIBUTED_LOG_UPDATE_IN_MEMORY_LOG_ID
} DistributedLogTypes;

}

#endif // DISTRIBUTEDLOGTYPES_H
