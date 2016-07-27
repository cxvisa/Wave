/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorker.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorkerReadinessMessage.h"
#include "Framework/Utils/SystemErrorUtils.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceMessageBase.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceManagerDelegateMessage.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorkerResponseMessage.h"
#include "Framework/Utils/FdUtils.h"

#include <errno.h>

namespace WaveNs
{

MapReduceWorker::MapReduceWorker (const SI32 &readSocket, const SI32 &writeSocket)
    : m_readSocket  (readSocket),
      m_writeSocket (writeSocket)
{
}

MapReduceWorker::~MapReduceWorker()
{
    ::close (m_readSocket);
    ::close (m_writeSocket);
}

bool MapReduceWorker::sendMessageToManager (MapReduceMessageBase *pMapReduceMessageBase)
{
    waveAssert (NULL != pMapReduceMessageBase, __FILE__, __LINE__);

    string serializedData;

    pMapReduceMessageBase->serialize2 (serializedData);

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

bool MapReduceWorker::sendWorkerReadinessMessage ()
{
    MapReduceWorkerReadinessMessage *pMapReduceWorkerReadinessMessage = instantiateWorkerReadynessMessage ();

    waveAssert (NULL != pMapReduceWorkerReadinessMessage, __FILE__, __LINE__);

    const bool status = sendMessageToManager (pMapReduceWorkerReadinessMessage);

    delete (pMapReduceWorkerReadinessMessage);

    return (status);
}

void MapReduceWorker::receiveMessageFromManager (string &messageFromManager)
{
    FdUtils::receiveMessageFromSocket (m_readSocket, messageFromManager);
}

MapReduceManagerDelegateMessage *MapReduceWorker::receiveManagerDelegateMessage ()
{
    string messageFromManager;

    receiveMessageFromManager (messageFromManager);

    if ("" != messageFromManager)
    {
        MapReduceMessageType mapReduceMessageType = MapReduceMessageBase::getType (messageFromManager);

        if (MAP_REDUCE_MESSAGE_TYPE_DELEGATE == mapReduceMessageType)
        {
            MapReduceManagerDelegateMessage *pMapReduceManagerDelegateMessage = instantiateMapReduceManagerDelegateMessage ();

            waveAssert (NULL != pMapReduceManagerDelegateMessage, __FILE__, __LINE__);

            pMapReduceManagerDelegateMessage->loadFromSerializedData2 (messageFromManager);

            return (pMapReduceManagerDelegateMessage);
        }
    }

    return (NULL);
}

MapReduceMessageBase *MapReduceWorker::receiveManagerMessage ()
{
    string messageFromManager;

    receiveMessageFromManager (messageFromManager);

    if ("" != messageFromManager)
    {
        MapReduceMessageType mapReduceMessageType = MapReduceMessageBase::getType (messageFromManager);

        if (MAP_REDUCE_MESSAGE_TYPE_DELEGATE == mapReduceMessageType)
        {
            MapReduceManagerDelegateMessage *pMapReduceManagerDelegateMessage = instantiateMapReduceManagerDelegateMessage ();

            waveAssert (NULL != pMapReduceManagerDelegateMessage, __FILE__, __LINE__);

            pMapReduceManagerDelegateMessage->loadFromSerializedData2 (messageFromManager);

            return (pMapReduceManagerDelegateMessage);
        }
    }

    return (NULL);
}

bool MapReduceWorker::processAndSendWorkerResponseMessage (MapReduceManagerDelegateMessage *pMapReduceManagerDelegateMessage)
{
    MapReduceWorkerResponseMessage *pMapReduceWorkerResponseMessage = process (pMapReduceManagerDelegateMessage);

    if (NULL == pMapReduceWorkerResponseMessage)
    {
        return (false);

    }

    bool status = sendMessageToManager (pMapReduceWorkerResponseMessage);

    delete pMapReduceWorkerResponseMessage;

    return (status);
}

}
