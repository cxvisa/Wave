/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/PortScanner/PortScannerWorker.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/FdUtils.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorkerReadinessMessage.h"
#include "Framework/Utils/PortScanner/PortScannerWorkerInput.h"
#include "Framework/Utils/PortScanner/PortScannerWorkerReadinessData.h"

namespace WaveNs
{

PortScannerWorker::PortScannerWorker (const SI32 &readSocket, const SI32 &writeSocket)
 : MapReduceWorker (readSocket, writeSocket)
{
}

PortScannerWorker::~PortScannerWorker ()
{
}

MapReduceWorkerReadinessMessage *PortScannerWorker::instantiateWorkerReadynessMessage ()
{
    PortScannerWorkerReadinessData *pPortScannerWorkerReadinessData = new PortScannerWorkerReadinessData ();

    waveAssert (NULL != pPortScannerWorkerReadinessData, __FILE__, __LINE__);

          UI32 numberOfPortsThatCanBeHandledSimultaneously = 0;

    const bool status                                      = FdUtils::getNumberOfAvailableFds (numberOfPortsThatCanBeHandledSimultaneously);

    if (! status)
    {
        waveAssert (status, __FILE__, __LINE__);
    }

    pPortScannerWorkerReadinessData->setNumberOfPortsToScanFor (numberOfPortsThatCanBeHandledSimultaneously);

    return (pPortScannerWorkerReadinessData);
}

MapReduceManagerDelegateMessage *PortScannerWorker::instantiateMapReduceManagerDelegateMessage ()
{
    return (new PortScannerWorkerInput ());
}

MapReduceWorkerResponseMessage *PortScannerWorker::process (MapReduceManagerDelegateMessage *pMapReduceManagerDelegateMessage)
{
    return (NULL);
}

}
