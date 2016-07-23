/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorker.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorkerReadinessMessage.h"

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

bool MapReduceWorker::sendWorkerReadinessMessage ()
{
    MapReduceWorkerReadinessMessage *pMapReduceWorkerReadinessMessage = instantiateWorkerReadynessMessage ();

    waveAssert (NULL != pMapReduceWorkerReadinessMessage, __FILE__, __LINE__);

    string serializedData;

    pMapReduceWorkerReadinessMessage->serialize2 (serializedData);

          UI32  sizeOfSerializedData = serializedData.length ();
    const char *pBuffer              = serializedData.c_str ();

    SI32  writeStatus          = 0;

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

MapReduceManagerDelegateMessage *MapReduceWorker::receiveManagerDelegateMessage ()
{
    return (NULL);
}

bool MapReduceWorker::processAndSendWorkerResponseMessage (MapReduceManagerDelegateMessage *pMapReduceManagerDelegateMessage)
{
    return (false);
}

}
