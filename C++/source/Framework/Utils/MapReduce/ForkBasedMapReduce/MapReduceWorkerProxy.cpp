/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorkerProxy.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorkerReadinessMessage.h"

namespace WaveNs
{

MapReduceWorkerProxy::MapReduceWorkerProxy (const SI32 &readSocket, const SI32 &writeSocket)
    : m_readSocket  (readSocket),
      m_writeSocket (writeSocket)
{
}

MapReduceWorkerProxy::~MapReduceWorkerProxy ()
{
    ::close (m_readSocket);
    ::close (m_writeSocket);
}

MapReduceWorkerReadinessMessage *MapReduceWorkerProxy::receiveWorkerReadynessMessage ()
{
    return (NULL);
}

bool MapReduceWorkerProxy::processWorkerReadynessMessageAndDelegate (MapReduceWorkerReadinessMessage *pMapReduceWorkerReadinessMessage)
{
    return (false);
}

MapReduceWorkerResponseMessage *MapReduceWorkerProxy::receiveWorkerResponseMessage ()
{
    return (NULL);
}

}
