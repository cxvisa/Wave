/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceManager.h"
#include "Framework/Utils/SystemErrorUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/FdUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorkerProxy.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorker.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceMessageBase.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorkerReadinessMessage.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorkerResponseMessage.h"
#include "Framework/Utils/FrameworkToolKit.h"

#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <map>

using namespace std;

namespace WaveNs
{

MapReduceManager::MapReduceManager (MapReduceInputConfiguration *pMapReduceInputConfiguration)
    : m_pMapReduceInputConfiguration (pMapReduceInputConfiguration)
{
}

MapReduceManager::~MapReduceManager ()
{
}

ResourceId MapReduceManager::mapReduce ()
{
    SI32                                i;
    SI32                                numberOfPartitions          = m_pMapReduceInputConfiguration->getAdjustedMaximumNumberOfPartitionsRequired ();
    int                               **pipeFdsForShardsForReading;
    int                               **pipeFdsForShardsForWriting;
    SI32                                childIndex = 0;
    SI32                                pipeStatus = 0;
    map<pid_t, SI32>                    pidToChildIndexMap;
    map<SI32, MapReduceWorkerProxy *>   readFdToWorkerProxy;

    if (numberOfPartitions > s_MAX_PARTITIONS_LIMIT)
    {
        numberOfPartitions = s_MAX_PARTITIONS_LIMIT;
    }

    tracePrintf (TRACE_LEVEL_DEBUG, "MapReduceManager::mapReduce : Number of partitions computed : %d in reality, Requested : %d", numberOfPartitions, m_pMapReduceInputConfiguration->getMaximumNumberOfPartitions ());

    pipeFdsForShardsForReading = new int*[numberOfPartitions];

    for (i = 0; i < numberOfPartitions; i++)
    {
        pipeFdsForShardsForReading[i] = new int[2];

        pipeFdsForShardsForReading[i][0] = -1;
        pipeFdsForShardsForReading[i][1] = -1;
    }

    pipeFdsForShardsForWriting = new int*[numberOfPartitions];

    for (i = 0; i < numberOfPartitions; i++)
    {
        pipeFdsForShardsForWriting[i] = new int[2];

        pipeFdsForShardsForWriting[i][0] = -1;
        pipeFdsForShardsForWriting[i][1] = -1;
    }

    pid_t pid = 0;

    for (i = 0; i < numberOfPartitions; i++)
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
                close (pipeFdsForShardsForWriting[i][1]);

                WaveNs::tracePrintf (TRACE_LEVEL_DEBUG, "PID %d, Child Index : %d", getpid (), childIndex);
            }
        }

        MapReduceWorker *pMapReduceWorker = createMapReduceWorker (pipeFdsForShardsForWriting[childIndex][0], pipeFdsForShardsForReading[childIndex][1]);

        waveAssert (NULL != pMapReduceWorker, __FILE__, __LINE__);

        while (true)
        {
            bool status = false;

            status = pMapReduceWorker->sendWorkerReadinessMessage ();

            if (! status)
            {
                break;
            }

            MapReduceManagerDelegateMessage *pMapReduceManagerDelegateMessage = pMapReduceWorker->receiveManagerDelegateMessage ();

            if (NULL == pMapReduceManagerDelegateMessage)
            {
                break;
            }

            status = pMapReduceWorker->processAndSendWorkerResponseMessage (pMapReduceManagerDelegateMessage);

            if (! status)
            {
                break;
            }
        }

        delete pMapReduceWorker;

        exit (childIndex);
    }
    else
    {
        for (i = 0; i < numberOfPartitions; i++)
        {
            MapReduceWorkerProxy *pMapReduceWorkerProxy = createMapReduceWorkerProxy (pipeFdsForShardsForReading[i][0], pipeFdsForShardsForWriting[i][1]);

            waveAssert (NULL != pMapReduceWorkerProxy, __FILE__, __LINE__);

            readFdToWorkerProxy[pipeFdsForShardsForReading[i][0]] = pMapReduceWorkerProxy;

        }

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

            const UI32 timeoutInMilliSecondsForManager = m_pMapReduceInputConfiguration->getTimeoutInMilliSecondsForManager ();

            timeOut.tv_sec = timeoutInMilliSecondsForManager / 1000;
            timeOut.tv_usec = (timeoutInMilliSecondsForManager % 1000) * 1000;

            SI32 selectStatus = select (maxFdToSelect + 1, &pipeFdSetForReadingForThisIteration, NULL, NULL, &timeOut);

            WaveNs::tracePrintf (TRACE_LEVEL_DEBUG, "Select Status : %d, %d", selectStatus, FdUtils::fdCount (&pipeFdSetForReadingForThisIteration));

            for (i = 0; i <= maxFdToSelect; i++)
            {
                if (FD_ISSET(i, &pipeFdSetForReadingForThisIteration))
                {
                    WaveNs::tracePrintf (TRACE_LEVEL_DEBUG, "FD : %d", i);

                    MapReduceWorkerProxy *pMapReduceWorkerProxy = readFdToWorkerProxy[i];

                    waveAssert (NULL != pMapReduceWorkerProxy, __FILE__, __LINE__);

                    MapReduceMessageBase *pMapReduceMessageBase = pMapReduceWorkerProxy->receiveWorkerMessage ();

                    if (NULL == pMapReduceMessageBase)
                    {
                        WaveNs::tracePrintf (TRACE_LEVEL_DEBUG, "FD %d, Closed communications.", i);

                        FD_CLR (i, &pipeFdSetForReading);

                        delete pMapReduceWorkerProxy;
                    }
                    else
                    {
                        MapReduceMessageType             mapReduceMessageType             = pMapReduceMessageBase->getMapReduceMessageType ();
                        MapReduceWorkerReadinessMessage *pMapReduceWorkerReadinessMessage = NULL;
                        MapReduceWorkerResponseMessage  *pMapReduceWorkerResponseMessage  = NULL;
                        bool                             status                           = false;

                        switch (mapReduceMessageType)
                        {
                            case MAP_REDUCE_MESSAGE_TYPE_READY :
                                WaveNs::tracePrintf (TRACE_LEVEL_DEBUG, true, false, "FD %d, Can Accept Work.", i);

                                pMapReduceWorkerReadinessMessage = dynamic_cast<MapReduceWorkerReadinessMessage *> (pMapReduceMessageBase);

                                waveAssert (NULL != pMapReduceWorkerReadinessMessage, __FILE__, __LINE__);

                                status = processWorkerReady (pMapReduceWorkerProxy, pMapReduceWorkerReadinessMessage);

                                if (false == status)
                                {
                                    FD_CLR (i, &pipeFdSetForReading);

                                    delete pMapReduceWorkerProxy;
                                }

                                break;

                            case MAP_REDUCE_MESSAGE_TYPE_RESPONSE :
                                WaveNs::tracePrintf (TRACE_LEVEL_DEBUG, true, false, "FD %d, Finished work and responded.", i);

                                pMapReduceWorkerResponseMessage = dynamic_cast<MapReduceWorkerResponseMessage *> (pMapReduceMessageBase);

                                waveAssert (NULL != pMapReduceWorkerResponseMessage, __FILE__, __LINE__);

                                status = processWorkerResponse (pMapReduceWorkerProxy, pMapReduceWorkerResponseMessage);

                                if (false == status)
                                {
                                    FD_CLR (i, &pipeFdSetForReading);

                                    delete pMapReduceWorkerProxy;
                                }

                                break;

                            default :
                                WaveNs::tracePrintf (TRACE_LEVEL_FATAL, true, false, "FD %d, Unexpected message from worker.  Status : %s", i, (FrameworkToolKit::localize (mapReduceMessageType)).c_str ());

                                FD_CLR (i, &pipeFdSetForReading);

                                delete pMapReduceWorkerProxy;

                                break;
                        }

                        delete pMapReduceMessageBase;
                    }
                }
            }
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

bool MapReduceManager::processWorkerReady (MapReduceWorkerProxy *pMapReduceWorkerProxy, MapReduceWorkerReadinessMessage *pMapReduceWorkerReadinessMessage)
{
    waveAssert (NULL != pMapReduceWorkerProxy,            __FILE__, __LINE__);
    waveAssert (NULL != pMapReduceWorkerReadinessMessage, __FILE__, __LINE__);

    bool moreWork = pMapReduceWorkerProxy->processWorkerReadynessMessageAndDelegate (m_pMapReduceInputConfiguration, pMapReduceWorkerReadinessMessage);

    return (moreWork);
}

bool MapReduceManager::processWorkerResponse (MapReduceWorkerProxy *pMapReduceWorkerProxy, MapReduceWorkerResponseMessage  *pMapReduceWorkerResponseMessage)
{
    waveAssert (NULL != pMapReduceWorkerProxy,            __FILE__, __LINE__);
    waveAssert (NULL != pMapReduceWorkerResponseMessage, __FILE__, __LINE__);

    consumeMapReduceWorkerOutput (pMapReduceWorkerResponseMessage);

    return (true);
}

}
