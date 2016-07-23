/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceManager.h"
#include "Framework/Utils/SystemErrorUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/FdUtils.h"

#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <map>

using namespace std;

namespace WaveNs
{

MapReduceManager::MapReduceManager (const MapReduceInputConfiguration &mapReduceInputConfiguration)
    : m_mapReduceInputConfiguration (mapReduceInputConfiguration)
{
}

MapReduceManager::~MapReduceManager ()
{
}

ResourceId MapReduceManager::mapReduce ()
{
    SI32           i;
    const SI32 numberOfShards = 508;
    int **pipeFdsForShardsForReading;
    int **pipeFdsForShardsForWriting;
    SI32 childIndex = 0;
    SI32 pipeStatus = 0;
    map<pid_t, SI32> pidToChildIndexMap;

    pipeFdsForShardsForReading = new int*[numberOfShards];

    for (i = 0; i < numberOfShards; i++)
    {
        pipeFdsForShardsForReading[i] = new int[2];

        pipeFdsForShardsForReading[i][0] = -1;
        pipeFdsForShardsForReading[i][1] = -1;
    }

    pipeFdsForShardsForWriting = new int*[numberOfShards];

    for (i = 0; i < numberOfShards; i++)
    {
        pipeFdsForShardsForWriting[i] = new int[2];

        pipeFdsForShardsForWriting[i][0] = -1;
        pipeFdsForShardsForWriting[i][1] = -1;
    }

    pid_t pid = 0;

    for (i = 0; i < numberOfShards; i++)
    {
        pipeStatus = pipe (pipeFdsForShardsForReading[i]);

        if (0 != pipeStatus)
        {
            WaveNs::tracePrintf (TRACE_LEVEL_ERROR, true, false, "Failed to create read pipe : iteration : %d, errno : %d, %s", i, errno, (SystemErrorUtils::getErrorStringForErrorNumber (errno)).c_str ());

            exit (-1);
        }

        pipeStatus = pipe (pipeFdsForShardsForWriting[i]);

        if (0 != pipeStatus)
        {
            WaveNs::tracePrintf (TRACE_LEVEL_ERROR, true, false, "Failed to create write pipe : iteration : %d, %d, %s", i, errno, (SystemErrorUtils::getErrorStringForErrorNumber (errno)).c_str ());

            exit (-2);
        }

        pid = fork ();

        if (0 < pid)
        {
            pidToChildIndexMap[pid] = i;

            close (pipeFdsForShardsForReading[i][1]);
            close (pipeFdsForShardsForWriting[i][0]);
        }
        else if (0 == pid)
        {
            childIndex = i;
            break;
        }
        else
        {
            WaveNs::tracePrintf (TRACE_LEVEL_ERROR, true, false, "Failed to fork during iteration %d : %d, %s", i, errno, (SystemErrorUtils::getErrorStringForErrorNumber (errno)).c_str ());

            exit (-3);
        }
    }

    if (0 == pid)
    {
        for (i = 0; i <= childIndex; i++)
        {
            if (childIndex != i)
            {
                close (pipeFdsForShardsForReading[i][0]);
                close (pipeFdsForShardsForWriting[i][1]);
            }
            else
            {
                close (pipeFdsForShardsForReading[i][0]);

                close (pipeFdsForShardsForWriting[i][0]);
                close (pipeFdsForShardsForWriting[i][1]);

                WaveNs::tracePrintf (TRACE_LEVEL_INFO, "PID %d, data sent : %d", getpid (), childIndex);

                SI32 dataToSend = htonl (childIndex);

                errno = 0;

                SI32 childWriteStatus = write (pipeFdsForShardsForReading[i][1], &dataToSend, sizeof (dataToSend));

                WaveNs::tracePrintf (TRACE_LEVEL_INFO, "PID %d, data sent : %d using FD : %d, Write Status : %d, errno : %d, %s", getpid (), childIndex, pipeFdsForShardsForReading[i][1], childWriteStatus, errno, (SystemErrorUtils::getErrorStringForErrorNumber (errno)).c_str ());

                close (pipeFdsForShardsForReading[i][1]);

                if (-1 == childWriteStatus)
                {
                    return (errno);
                }
            }
        }

        return (childIndex);
    }
    else
    {
        //SI32 status = 0;
        fd_set pipeFdSetForReading;
        struct timeval timeOut;
        SI32 maxFdToSelect = 0;

        timeOut.tv_sec = 3;
        timeOut.tv_usec = 0;

        FD_ZERO (&pipeFdSetForReading);

        map<pid_t, SI32>::const_iterator element    = pidToChildIndexMap.begin ();
        map<pid_t, SI32>::const_iterator endElement = pidToChildIndexMap.end   ();

        while (endElement != element)
        {
            SI32 fdToSelect = pipeFdsForShardsForReading[element->second][0];

            if (fdToSelect > maxFdToSelect)
            {
                maxFdToSelect = fdToSelect;
            }

            FD_SET (fdToSelect, &pipeFdSetForReading);

            element++;
        }

        while (0 < (FdUtils::fdCount (&pipeFdSetForReading)))
        {
            fd_set pipeFdSetForReadingForThisIteration;

            FdUtils::fdCopy (&pipeFdSetForReading, &pipeFdSetForReadingForThisIteration);

            timeOut.tv_sec = 3;
            timeOut.tv_usec = 0;

            SI32 selectStatus = select (maxFdToSelect + 1, &pipeFdSetForReadingForThisIteration, NULL, NULL, &timeOut);

            WaveNs::tracePrintf (TRACE_LEVEL_INFO, "Select Status : %d, %d", selectStatus, FdUtils::fdCount (&pipeFdSetForReadingForThisIteration));

            for (i = 0; i <= maxFdToSelect; i++)
            {
                if (FD_ISSET(i, &pipeFdSetForReadingForThisIteration))
                {
                    WaveNs::tracePrintf (TRACE_LEVEL_INFO, "FD : %d", i);

                    SI32 dataToReceive = -1;

                    SI32 parentReadStatus = read (i, &dataToReceive, sizeof (dataToReceive));

                    if (-1 == parentReadStatus)
                    {
                        WaveNs::tracePrintf (TRACE_LEVEL_INFO, "data read failed for fd : %d with status : %d : %s", i, errno, (SystemErrorUtils::getErrorStringForErrorNumber(errno)).c_str ());
                    }
                    else if (0 == parentReadStatus)
                    {
                        FD_CLR (i, &pipeFdSetForReading);
                    }
                    else
                    {
                        dataToReceive = ntohl (dataToReceive);

                        WaveNs::tracePrintf (TRACE_LEVEL_INFO, "FD %d, number of bytes read : %d, data read : %d", i, parentReadStatus, dataToReceive);
                    }
                }
            }
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

}
