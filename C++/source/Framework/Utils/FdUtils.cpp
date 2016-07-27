/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/FdUtils.h"
#include "Framework/Types/UI32Range.h"
#include "Framework/Utils/SystemErrorUtils.h"
#include "Framework/Utils/SystemLimitsUtils.h"
#include "Framework/Utils/TraceUtils.h"

#include <errno.h>

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

void FdUtils::receiveMessageFromSocket (const SI32 &socket, string &message)
{
    message = "";

    UI32 sizeOfDataToReceive = 0;

    SI32 status = ::read (socket, &sizeOfDataToReceive, sizeof (sizeOfDataToReceive));

    if (-1 == status)
    {
        WaveNs::tracePrintf (TRACE_LEVEL_DEBUG, "FdUtils::receiveMessageFromSocket : Data read failed for fd : %d with status : %d : %s", socket, errno, (SystemErrorUtils::getErrorStringForErrorNumber(errno)).c_str ());
    }
    else if (0 == status)
    {
        return;
    }
    else
    {
        sizeOfDataToReceive = ntohl (sizeOfDataToReceive);

        const UI32 originalSizeOfDataToReceive = sizeOfDataToReceive;

        WaveNs::tracePrintf (TRACE_LEVEL_DEBUG, "FD %d, number of bytes to read : %d", socket, originalSizeOfDataToReceive);

        char *pBuffer     = new char[originalSizeOfDataToReceive + 1];
        char *pTempBuffer = pBuffer;

        waveAssert (NULL != pBuffer,     __FILE__, __LINE__);
        waveAssert (NULL != pTempBuffer, __FILE__, __LINE__);

        while (sizeOfDataToReceive > 0)
        {
            status = ::read (socket, pTempBuffer, sizeOfDataToReceive);

            if (-1 == status)
            {
                WaveNs::tracePrintf (TRACE_LEVEL_DEBUG, "FdUtils::receiveMessageFromSocket : Data read failed for fd : %d during message read with status : %d : %s", socket, errno, (SystemErrorUtils::getErrorStringForErrorNumber(errno)).c_str ());

                delete[] pBuffer;

                return;
            }
            else if (0 == status)
            {
                WaveNs::tracePrintf (TRACE_LEVEL_DEBUG, "FD %d, could not read when number of bytes remaining : %d", socket, status, sizeOfDataToReceive);

                delete[] pBuffer;

                return;
            }
            else
            {
                sizeOfDataToReceive -= status;
                pTempBuffer         += status;
            }
        }

        pBuffer[originalSizeOfDataToReceive] = '\0';

        WaveNs::tracePrintf (TRACE_LEVEL_DEBUG, true, false, "FD : %d, Data Read : %s", socket, pBuffer);

        message = pBuffer;

        delete[] pBuffer;

        return;
    }

    return;
}

}
