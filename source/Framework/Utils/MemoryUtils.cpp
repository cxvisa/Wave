/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/MemoryUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Types/Types.h"

#include <malloc.h>

namespace WaveNs
{

void MemoryUtils::releaseUnusedMemoryToSystem()
{
    SI32 trimResult = 0;

    trimResult =  malloc_trim ((sizeof (void *)) * 1024 * 100 * 2);

    #if 1
    if (1 == trimResult)
    {
        trace (TRACE_LEVEL_DEVEL, "MemoryUtils::releaseUnusedMemoryToSystem : Successfully released unused memory back to system.");
    }
    else
    {
        trace (TRACE_LEVEL_DEVEL, "MemoryUtils::releaseUnusedMemoryToSystem : Failed to release unused memory back to system.");
    }
    #endif
}

}
