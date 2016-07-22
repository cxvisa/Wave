/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Types/Types.h"
#include "Framework/Redundancy/RedundancyOptimizerBase.h"
#include "Framework/Utils/PortScanner/TcpPortScanner.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/SystemErrorUtils.h"
#include "Framework/Utils/PortScanner/TcpPortScannerInputConfiguration.h"

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;
using namespace WaveNs;

int main (int argc, char *argv[])
{
#if 0
    SI32           i;
    const SI32 numberOfShards = 100;
    int **pipeFdsForShardsForReading;
    int **pipeFdsForShardsForWriting;
    SI32 childIndex = 0;
    SI32 pipeStatus = 0;
    map<pid_t, SI32> pidToChildIndexMap;
#endif

    TcpPortScannerInputConfiguration tcpPortScannerInputConfiguration;

    bool parsingStatus = tcpPortScannerInputConfiguration.parseCommandLineInputs (argc, argv);

    if (! parsingStatus)
    {
        exit (-1);
    }

#if 0
    pipeFdsForShardsForReading = new int*[numberOfShards];

    for (i = 0; i < numberOfShards; i++)
    {
        pipeFdsForShardsForReading[i] = new int[2];
    }

    pipeFdsForShardsForWriting = new int*[numberOfShards];

    for (i = 0; i < numberOfShards; i++)
    {
        pipeFdsForShardsForWriting[i] = new int[2];
    }

    for (i = 0; i < numberOfShards; i++)
    {
        pipeStatus = pipe (pipeFdsForShardsForReading[i]);

        if (0 != pipeStatus)
        {
            WaveNs::tracePrintf (TRACE_LEVEL_ERROR, true, false, "Failed to create read pipe : %d, %s", errno, (SystemErrorUtils::getErrorStringForErrorNumber (errno)).c_str ());

            exit (-1);
        }

        pipeStatus = pipe (pipeFdsForShardsForWriting[i]);

        if (0 != pipeStatus)
        {
            WaveNs::tracePrintf (TRACE_LEVEL_ERROR, true, false, "Failed to create write pipe : %d, %s", errno, (SystemErrorUtils::getErrorStringForErrorNumber (errno)).c_str ());

            exit (-2);
        }
    }

    pid_t pid = 0;

    for (i = 0; i < numberOfShards; i++)
    {
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
        for (i = 0; i < numberOfShards; i++)
        {
            if (childIndex != i)
            {
                close (pipeFdsForShardsForReading[i][0]);
                close (pipeFdsForShardsForReading[i][1]);
                close (pipeFdsForShardsForWriting[i][0]);
                close (pipeFdsForShardsForWriting[i][1]);
            }
            else
            {
                close (pipeFdsForShardsForReading[i][0]);
                close (pipeFdsForShardsForWriting[i][1]);

                SI32 dataToSend = htons (childIndex);

                SI32 childWriteStatus = write (pipeFdsForShardsForReading[i][1], &dataToSend, sizeof (dataToSend));

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

        SI32 status = 0;

        while (true)
        {
            pid = wait (&status);

            if (-1 == pid)
            {
                break;
            }

            childIndex = pidToChildIndexMap[pid];

            WaveNs::tracePrintf (TRACE_LEVEL_INFO, "PID %d exited with status %d, childIndex : %d", pid, status >> 8, childIndex);

            SI32 dataToReceive = -1;

            SI32 parentReadStatus = read (pipeFdsForShardsForReading[childIndex][0], &dataToReceive, sizeof (dataToReceive));

            if (-1 == parentReadStatus)
            {
                WaveNs::tracePrintf (TRACE_LEVEL_INFO, "PID %d, data read failed : %d", pid, errno);
            }
            else
            {
                dataToReceive = ntohs (dataToReceive);

                WaveNs::tracePrintf (TRACE_LEVEL_INFO, "PID %d, data read : %d", pid, dataToReceive);
            }
        }
    }
#endif

    TcpPortScanner::scanPorts (tcpPortScannerInputConfiguration);

    return (0);
}
