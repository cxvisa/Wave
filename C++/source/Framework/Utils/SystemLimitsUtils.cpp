/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/SystemLimitsUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/SystemErrorUtils.h"
#include "Framework/Utils/AssertUtils.h"

#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <poll.h>

namespace WaveNs
{

bool SystemLimitsUtils::getMaxNumberOfOpenFiles (UI32 &softLimit, UI32 &hardLimit)
{
    SI32   rlimitStatus = 0;
    rlimit rlim;

    rlimitStatus = getrlimit (RLIMIT_NOFILE, &rlim);

    if (-1 == rlimitStatus)
    {
        WaveNs::tracePrintf (TRACE_LEVEL_ERROR, true, false, "SystemLimitsUtils::getMaxNumberOfOpenFiles : Failed to get limits.  Status : %d, %s", SystemErrorUtils::getErrorStringForErrorNumber(errno));

        softLimit = 0;
        hardLimit = 0;

        return (false);
    }
    else
    {
        softLimit = rlim.rlim_cur;
        hardLimit = rlim.rlim_max;

        return (true);
    }
}

bool SystemLimitsUtils::getFileDescriptorsCurrentlyInUse (vector<UI32> &fileDescriptorsCurrentlyInUse)
{
    fileDescriptorsCurrentlyInUse.clear ();

    UI32 softLimit = 0;
    UI32 hardLimit = 0;
    bool status    = getMaxNumberOfOpenFiles (softLimit, hardLimit);
    UI32 i         = 0;

    if (false == status)
    {
        WaveNs::tracePrintf (TRACE_LEVEL_ERROR, true, false, "SystemLimitsUtils::getFileDescriptorsCurrentlyInUse : Filed to obtain MaxNumberOfOpenFiles.");

        return (false);
    }

    struct pollfd *pPollFds = new pollfd[softLimit];

    WaveNs::waveAssert (NULL != pPollFds, __FILE__, __LINE__);

    for (i = 0; i < softLimit; i++)
    {
        pPollFds[i].fd = i;
        pPollFds[i].events = 0;
    }

    int pollStatus = poll (pPollFds, softLimit, 0);

    if (-1 == pollStatus)
    {
        WaveNs::tracePrintf (TRACE_LEVEL_ERROR, true, false, "SystemLimitsUtils::getFileDescriptorsCurrentlyInUse : Filed to poll. errno : %d, %s", errno, SystemErrorUtils::getErrorStringForErrorNumber(errno));

        delete[] (pPollFds);

        return (false);
    }

    for (i = 0; i < softLimit; i++)
    {
        if (0 == (pPollFds[i].revents & POLLNVAL))
        {
            fileDescriptorsCurrentlyInUse.push_back (i);
        }
    }

    delete[] (pPollFds);

    return (true);
}

}
