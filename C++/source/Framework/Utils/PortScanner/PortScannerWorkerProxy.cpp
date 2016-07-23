/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/PortScanner/PortScannerWorkerProxy.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceManagerDelegateMessage.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorkerReadinessMessage.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorkerResponseMessage.h"
#include "Framework/Utils/PortScanner/PortScannerWorkerInput.h"
#include "Framework/Utils/PortScanner/PortScannerWorkerOutput.h"
#include "Framework/Utils/PortScanner/PortScannerWorkerReadinessData.h"

namespace WaveNs
{

PortScannerWorkerProxy::PortScannerWorkerProxy (const SI32 &readSocket, const SI32 &writeSocket)
    : MapReduceWorkerProxy(readSocket, writeSocket)
{
}

PortScannerWorkerProxy::~PortScannerWorkerProxy ()
{
}

MapReduceWorkerReadinessMessage *PortScannerWorkerProxy::instantiateWorkerReadynessMessage ()
{
    return (new PortScannerWorkerReadinessData ());
}

MapReduceManagerDelegateMessage *PortScannerWorkerProxy::instantiateMapReduceManagerDelegateMessage ()
{
    return (new PortScannerWorkerInput ());
}

MapReduceWorkerResponseMessage *PortScannerWorkerProxy::instantiateWorkerResponseMessage ()
{
    return (new PortScannerWorkerOutput ());
}

MapReduceManagerDelegateMessage *PortScannerWorkerProxy::process (MapReduceWorkerReadinessMessage *pMapReduceWorkerReadinessMessage)
{
    return (NULL);
}

}
