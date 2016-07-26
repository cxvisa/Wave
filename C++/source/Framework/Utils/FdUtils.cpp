/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/FdUtils.h"
#include "Framework/Types/UI32Range.h"
#include "Framework/Utils/SystemLimitsUtils.h"
#include "Framework/Utils/TraceUtils.h"

namespace WaveNs
{

void FdUtils::fdCopy (fd_set *pSource, fd_set *pDestination)
{
    SI32 i = 0;

    FD_ZERO (pDestination);

    for (i = 0; i < FD_SETSIZE; i++)
    {
        if (FD_ISSET(i, pSource))
        {
            FD_SET (i, pDestination);
        }
    }
}

SI32 FdUtils::fdMax (fd_set *pSource)
{
    SI32 i = 0;

    for (i = FD_SETSIZE - 1; i >= 0; i--)
    {
        if (FD_ISSET(i, pSource))
        {
            return (i);
        }
    }

    return (-1);
}

SI32 FdUtils::fdCount (fd_set *pSource)
{
    SI32 i     = 0;
    SI32 count = 0;

    for (i = 0; i < FD_SETSIZE; i++)
    {
        if (FD_ISSET(i, pSource))
        {
            count++;
        }
    }

    return (count);
}

bool FdUtils::getNumberOfAvailableFds (UI32 &getNumberOfAvailableFds)
{
    UI32 softLimit = 0;
    UI32 hardLimit = 0;

    bool status = SystemLimitsUtils::getMaxNumberOfOpenFiles (softLimit, hardLimit);

    if (true == status)
    {
        tracePrintf (TRACE_LEVEL_DEBUG, true, false, "FdUtils::getNumberOfAvailableFds : Soft limit on open files : %u, Hard limit on open files : %u", softLimit, hardLimit);
    }
    else
    {
        tracePrintf (TRACE_LEVEL_ERROR, true, false, "FdUtils::getNumberOfAvailableFds : Could not obtain System Limits for maximum number of open files.");
    }

    vector<UI32> fileDescriptorsCurrentlyInUse;

    status = SystemLimitsUtils::getFileDescriptorsCurrentlyInUse (fileDescriptorsCurrentlyInUse);

    if (true == status)
    {
        tracePrintf (TRACE_LEVEL_DEBUG, true, false, "FdUtils::getNumberOfAvailableFds : Currently In Use File Descriptors :");

        vector<UI32>::const_iterator element    = fileDescriptorsCurrentlyInUse.begin ();
        vector<UI32>::const_iterator endElement = fileDescriptorsCurrentlyInUse.end   ();

        while (endElement != element)
        {
            tracePrintf (TRACE_LEVEL_DEBUG, true, true, "%u", *element);

            element++;
        }

        const string inUseFileDescriptorRangeString = UI32Range::getUI32RangeStringFromVector (fileDescriptorsCurrentlyInUse);

        tracePrintf (TRACE_LEVEL_DEBUG, true, false, "FdUtils::getNumberOfAvailableFds : Currently In Use : %s", inUseFileDescriptorRangeString.c_str ());

        getNumberOfAvailableFds = softLimit - (fileDescriptorsCurrentlyInUse.size ());

        // Round it off to nearest 100 multiple.
        // 100 is arbitrarily chosen and this can be adjusted by any reasonable value.

        getNumberOfAvailableFds -= getNumberOfAvailableFds % 100;
    }
    else
    {
        tracePrintf (TRACE_LEVEL_ERROR, true, false, "FdUtils::getNumberOfAvailableFds : Could not obtain currently in use file descriptors.");
    }

    return (status);
}

}
