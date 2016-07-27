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
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceManagerDelegateMessage.h"

#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

namespace WaveNs
{

MapReduceManager::MapReduceManager (MapReduceInputConfiguration *pMapReduceInputConfiguration)
    : m_pMapReduceInputConfiguration (pMapReduceInputConfiguration),
      m_pPipeFdsForShardsForReading  (NULL),
      m_pPipeFdsForShardsForWriting  (NULL),
      m_childIndex (-1)
{
    waveAssert (NULL != m_pMapReduceInputConfiguration, __FILE__, __LINE__);

    m_numberOfPartitions = m_pMapReduceInputConfiguration->getAdjustedMaximumNumberOfPartitionsRequired ();

    if (m_numberOfPartitions > s_MAX_PARTITIONS_LIMIT)
    {
        m_numberOfPartitions = s_MAX_PARTITIONS_LIMIT;
    }

    tracePrintf (TRACE_LEVEL_DEBUG, "MapReduceManager::MapReduceManager : Number of partitions computed : %d in reality, Requested : %d", m_numberOfPartitions, m_pMapReduceInputConfiguration->getMaximumNumberOfPartitions ());

    allocatePipeFdsForShards ();
}

MapReduceManager::~MapReduceManager ()
{
}

void MapReduceManager::allocatePipeFdsForShards ()
{
    SI32 i = 0;

    m_pPipeFdsForShardsForReading = new int*[m_numberOfPartitions];

    for (i = 0; i < m_numberOfPartitions; i++)
    {
        m_pPipeFdsForShardsForReading[i] = new int[2];

        m_pPipeFdsForShardsForReading[i][0] = -1;
        m_pPipeFdsForShardsForReading[i][1] = -1;
    }

    m_pPipeFdsForShardsForWriting = new int*[m_numberOfPartitions];

    for (i = 0; i < m_numberOfPartitions; i++)
    {
        m_pPipeFdsForShardsForWriting[i] = new int[2];

        m_pPipeFdsForShardsForWriting[i][0] = -1;
        m_pPipeFdsForShardsForWriting[i][1] = -1;
    }
}

void MapReduceManager::releaseAllocatedPipeFdsForShards ()
{
    SI32 i = 0;

    for (i = 0; i < m_numberOfPartitions; i++)
    {
        delete[] (m_pPipeFdsForShardsForReading[i]);
        delete[] (m_pPipeFdsForShardsForWriting[i]);
    }

    delete[] m_pPipeFdsForShardsForReading;
    delete[] m_pPipeFdsForShardsForWriting;
}

ResourceId MapReduceManager::mapReduce ()
{
    SI32      i                 = 0;
    SI32      pipeStatus        = 0;
    pid_t     pid               = 0;
    ResourceId processingStatus = WAVE_MESSAGE_SUCCESS;

    // Launch Worker per partition required using fork.

    for (i = 0; i < m_numberOfPartitions; i++)
    {
        // First create Read and Write Pipes.

        pipeStatus = pipe (m_pPipeFdsForShardsForReading[i]);

        if (0 != pipeStatus)
        {
            WaveNs::tracePrintf (TRACE_LEVEL_ERROR, true, false, "Failed to create read pipe : iteration : %d, errno : %d, %s", i, errno, (SystemErrorUtils::getErrorStringForErrorNumber (errno)).c_str ());

            exit (-1);
        }

        pipeStatus = pipe (m_pPipeFdsForShardsForWriting[i]);

        if (0 != pipeStatus)
        {
            WaveNs::tracePrintf (TRACE_LEVEL_ERROR, true, false, "Failed to create write pipe : iteration : %d, %d, %s", i, errno, (SystemErrorUtils::getErrorStringForErrorNumber (errno)).c_str ());

            exit (-2);
        }

        pid = fork ();

        if (0 < pid)
        {
            // In parent (manager) close the ends as soon as we do not need in order to save the number of open fds.

            m_pidToChildIndexMap[pid] = i;

            close (m_pPipeFdsForShardsForReading[i][1]);
            close (m_pPipeFdsForShardsForWriting[i][0]);
        }
        else if (0 == pid)
        {
            // For child process, mark the index so that we can deal with the pipe fd arrays etc.,
            // Also, child can use it for its own purposes.

            m_childIndex = i;
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
        processChild ();
    }
    else
    {
        processingStatus = processParent ();
    }

    return (processingStatus);
}

void MapReduceManager::processChild ()
{
    SI32 i = 0;

    // First close all of the unnecessary FDs that parent kept open.
    // We need to do this because, port scanning functionality requires using more FDs.
    // We would like to have as many available FDs as possible.

    // loop is bound by m_childIndex since parent created pipes till that index before launching this child process.

    for (i = 0; i <= m_childIndex; i++)
    {
        if (m_childIndex != i)
        {
            ::close (m_pPipeFdsForShardsForReading[i][0]);
            ::close (m_pPipeFdsForShardsForWriting[i][1]);
        }
        else
        {
            ::close (m_pPipeFdsForShardsForReading[i][0]);
            ::close (m_pPipeFdsForShardsForWriting[i][1]);

            WaveNs::tracePrintf (TRACE_LEVEL_DEBUG, "PID %d, Child Index : %d", getpid (), m_childIndex);
        }
    }

    // Use the appropriate FD ends and create the Map Reduce Worker that this child represents.
    // Please not that the Pipe FD array names used are from the Manager perspective.

    MapReduceWorker *pMapReduceWorker = createMapReduceWorker (m_pPipeFdsForShardsForWriting[m_childIndex][0], m_pPipeFdsForShardsForReading[m_childIndex][1]);

    waveAssert (NULL != pMapReduceWorker, __FILE__, __LINE__);

    // Map Reduce Worker (child) always does the following:
    // 1.  Send a readiness message back to manager to indicate how much load it can take currently.
    // 2.  Waits and reads Manager Delegate Message (aka Worker Input)
    // 3.  Processes the Input and generates Worker Output (aka Worker Response) message and sends it back to manager.

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

        delete pMapReduceManagerDelegateMessage;

        if (! status)
        {
            break;
        }
    }

    delete pMapReduceWorker;

    releaseAllocatedPipeFdsForShards ();

    exit (0);
}

ResourceId MapReduceManager::processParent ()
{
    SI32 i = 0;

    for (i = 0; i < m_numberOfPartitions; i++)
    {
        MapReduceWorkerProxy *pMapReduceWorkerProxy = createMapReduceWorkerProxy (m_pPipeFdsForShardsForReading[i][0], m_pPipeFdsForShardsForWriting[i][1]);

        waveAssert (NULL != pMapReduceWorkerProxy, __FILE__, __LINE__);

        m_readFdToWorkerProxy[m_pPipeFdsForShardsForReading[i][0]] = pMapReduceWorkerProxy;
    }

    fd_set         pipeFdSetForReading;
    struct timeval timeOut;
    SI32           maxFdToSelect = 0;

    FD_ZERO (&pipeFdSetForReading);

    map<pid_t, SI32>::const_iterator element    = m_pidToChildIndexMap.begin ();
    map<pid_t, SI32>::const_iterator endElement = m_pidToChildIndexMap.end   ();

    while (endElement != element)
    {
        SI32 fdToSelect = m_pPipeFdsForShardsForReading[element->second][0];

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

        if (-1 == selectStatus)
        {
           if (EINTR == errno)
           {
               continue;
           }
           else
           {
               break;
           }
        }
        else if (0 == selectStatus)
        {
            break;
        }
        else
        {
            for (i = 0; i <= maxFdToSelect; i++)
            {
                if (FD_ISSET(i, &pipeFdSetForReadingForThisIteration))
                {
                    WaveNs::tracePrintf (TRACE_LEVEL_DEBUG, "FD : %d", i);

                    MapReduceWorkerProxy *pMapReduceWorkerProxy = m_readFdToWorkerProxy[i];

                    waveAssert (NULL != pMapReduceWorkerProxy, __FILE__, __LINE__);

                    MapReduceMessageBase *pMapReduceMessageBase = pMapReduceWorkerProxy->receiveWorkerMessage ();

                    if (NULL == pMapReduceMessageBase)
                    {
                        WaveNs::tracePrintf (TRACE_LEVEL_DEBUG, "FD %d, Closed communications.", i);

                        FD_CLR (i, &pipeFdSetForReading);

                        pMapReduceWorkerProxy->errorOutPendingMapReduceManagerDelegateMessage(this);

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

                                    pMapReduceWorkerProxy->errorOutPendingMapReduceManagerDelegateMessage(this);

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

                                    pMapReduceWorkerProxy->errorOutPendingMapReduceManagerDelegateMessage(this);

                                    delete pMapReduceWorkerProxy;
                                }

                                break;

                            default :
                                WaveNs::tracePrintf (TRACE_LEVEL_FATAL, true, false, "FD %d, Unexpected message from worker.  Status : %s", i, (FrameworkToolKit::localize (mapReduceMessageType)).c_str ());

                                FD_CLR (i, &pipeFdSetForReading);

                                pMapReduceWorkerProxy->errorOutPendingMapReduceManagerDelegateMessage(this);

                                delete pMapReduceWorkerProxy;

                                break;
                        }

                        delete pMapReduceMessageBase;
                    }
                }
            }
        }
    }

    releaseAllocatedPipeFdsForShards ();

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

    pMapReduceWorkerProxy->resetPendingMapReduceManagerDelegateMessage ();

    consumeMapReduceWorkerOutput (pMapReduceWorkerResponseMessage);

    return (true);
}

}
