/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorkerProxy.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorkerReadinessMessage.h"
#include "Framework/Utils/SystemErrorUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceMessageBase.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorkerResponseMessage.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceInputConfiguration.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceManagerDelegateMessage.h"
#include "Framework/Utils/FdUtils.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceManager.h"

#include <errno.h>

namespace WaveNs
{

MapReduceWorkerProxy::MapReduceWorkerProxy (const SI32 &readSocket, const SI32 &writeSocket)
    : m_readSocket                              (readSocket),
      m_writeSocket                             (writeSocket),
      m_pPendingMapReduceManagerDelegateMessage (NULL)
{
}

MapReduceWorkerProxy::~MapReduceWorkerProxy ()
{
    WaveNs::tracePrintf (TRACE_LEVEL_DEBUG, "MapReduceWorkerProxy::~MapReduceWorkerProxy : RFD : %d, WFD : %d", m_readSocket, m_writeSocket);

    ::close (m_readSocket);
    ::close (m_writeSocket);

    resetPendingMapReduceManagerDelegateMessage ();
}

void MapReduceWorkerProxy::receiveMessageFromWorker (string &messageFromManager)
{
    FdUtils::receiveMessageFromSocket (m_readSocket, messageFromManager);
}

MapReduceWorkerReadinessMessage *MapReduceWorkerProxy::receiveWorkerReadynessMessage ()
{
    string messageFromWorker;

    receiveMessageFromWorker (messageFromWorker);

    if ("" != messageFromWorker)
    {
        MapReduceMessageType mapReduceMessageType = MapReduceMessageBase::getType (messageFromWorker);

        if (MAP_REDUCE_MESSAGE_TYPE_READY == mapReduceMessageType)
        {
            MapReduceWorkerReadinessMessage *pMapReduceWorkerReadinessMessage = instantiateWorkerReadynessMessage ();

            waveAssert (NULL != pMapReduceWorkerReadinessMessage, __FILE__, __LINE__);

            pMapReduceWorkerReadinessMessage->loadFromSerializedData2 (messageFromWorker);

            return (pMapReduceWorkerReadinessMessage);
        }
    }

    return (NULL);
}

MapReduceMessageBase *MapReduceWorkerProxy::receiveWorkerMessage ()
{
    string messageFromWorker;

    receiveMessageFromWorker (messageFromWorker);

    if ("" != messageFromWorker)
    {
        MapReduceMessageType mapReduceMessageType = MapReduceMessageBase::getType (messageFromWorker);

        if (MAP_REDUCE_MESSAGE_TYPE_READY == mapReduceMessageType)
        {
            MapReduceWorkerReadinessMessage *pMapReduceWorkerReadinessMessage = instantiateWorkerReadynessMessage ();

            waveAssert (NULL != pMapReduceWorkerReadinessMessage, __FILE__, __LINE__);

            pMapReduceWorkerReadinessMessage->loadFromSerializedData2 (messageFromWorker);

            return (pMapReduceWorkerReadinessMessage);
        }
        else if (MAP_REDUCE_MESSAGE_TYPE_RESPONSE == mapReduceMessageType)
        {
            MapReduceWorkerResponseMessage *pMapReduceWorkerResponseMessage = instantiateWorkerResponseMessage ();

            waveAssert (NULL != pMapReduceWorkerResponseMessage, __FILE__, __LINE__);

            pMapReduceWorkerResponseMessage->loadFromSerializedData2 (messageFromWorker);

            return (pMapReduceWorkerResponseMessage);
        }
    }

    return (NULL);
}

bool MapReduceWorkerProxy::processWorkerReadynessMessageAndDelegate (MapReduceInputConfiguration *pMapReduceInputConfiguration, MapReduceWorkerReadinessMessage *pMapReduceWorkerReadinessMessage)
{
    waveAssert (NULL != pMapReduceInputConfiguration,     __FILE__, __LINE__);
    waveAssert (NULL != pMapReduceWorkerReadinessMessage, __FILE__, __LINE__);

    MapReduceManagerDelegateMessage *pMapReduceManagerDelegateMessage = pMapReduceInputConfiguration->getNextWork (pMapReduceWorkerReadinessMessage);

    if (NULL == pMapReduceManagerDelegateMessage)
    {
        return (false);
    }

    m_pPendingMapReduceManagerDelegateMessage = pMapReduceManagerDelegateMessage;

    bool sendStatus = sendWorkerReadinessMessage (pMapReduceManagerDelegateMessage);

    return (sendStatus);
}

bool MapReduceWorkerProxy::sendWorkerReadinessMessage (MapReduceManagerDelegateMessage *pMapReduceManagerDelegateMessage)
{
    waveAssert (NULL != pMapReduceManagerDelegateMessage, __FILE__, __LINE__);

    string serializedData;

    pMapReduceManagerDelegateMessage->serialize2 (serializedData);

          UI32  sizeOfSerializedData            = serializedData.length ();
    const char *pBuffer                         = serializedData.c_str ();
          UI32  sizeOfSerializedDataOverNetwork = htonl (sizeOfSerializedData);

    SI32  writeStatus          = 0;

    writeStatus = ::write (m_writeSocket, &sizeOfSerializedDataOverNetwork, sizeof (sizeOfSerializedData));

    if (-1 == writeStatus)
    {
        return (false);
    }

    while (sizeOfSerializedData > 0)
    {
        writeStatus = ::write (m_writeSocket, serializedData.c_str (), sizeOfSerializedData);

        if (-1 == writeStatus)
        {
            return (false);
        }
        else
        {
            sizeOfSerializedData -= writeStatus;

            pBuffer += writeStatus;
        }
    }

    return (true);
}

MapReduceWorkerResponseMessage *MapReduceWorkerProxy::receiveWorkerResponseMessage ()
{
    string messageFromWorker;

    receiveMessageFromWorker (messageFromWorker);

    if ("" != messageFromWorker)
    {
        MapReduceMessageType mapReduceMessageType = MapReduceMessageBase::getType (messageFromWorker);

        if (MAP_REDUCE_MESSAGE_TYPE_RESPONSE == mapReduceMessageType)
        {
            MapReduceWorkerResponseMessage *pMapReduceWorkerResponseMessage = instantiateWorkerResponseMessage ();

            waveAssert (NULL != pMapReduceWorkerResponseMessage, __FILE__, __LINE__);

            pMapReduceWorkerResponseMessage->loadFromSerializedData2 (messageFromWorker);

            return (pMapReduceWorkerResponseMessage);
        }
    }

    return (NULL);
}

void MapReduceWorkerProxy::resetPendingMapReduceManagerDelegateMessage ()
{
    if (NULL != m_pPendingMapReduceManagerDelegateMessage)
    {
        delete (m_pPendingMapReduceManagerDelegateMessage);

        m_pPendingMapReduceManagerDelegateMessage = NULL;
    }
}

void MapReduceWorkerProxy::errorOutPendingMapReduceManagerDelegateMessage (MapReduceManager *pMapReduceManager)
{
    waveAssert (NULL != pMapReduceManager, __FILE__, __LINE__);

    if (NULL != m_pPendingMapReduceManagerDelegateMessage)
    {
        pMapReduceManager->errorOutMapReduceWorkerInput (m_pPendingMapReduceManagerDelegateMessage);
    }
}

}
