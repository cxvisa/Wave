/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/PortScanner/PortScannerMapReducer.h"
#include "Framework/Utils/PortScanner/PortScannerInputConfiguration.h"
#include "Framework/Utils/PortScanner/PortScannerWorker.h"
#include "Framework/Utils/PortScanner/PortScannerWorkerProxy.h"

namespace WaveNs
{

PortScannerMapReducer::PortScannerMapReducer (PortScannerInputConfiguration *pPortScannerInputConfiguration)
    : MapReduceManager (pPortScannerInputConfiguration)
{
}

PortScannerMapReducer::~PortScannerMapReducer ()
{
}

MapReduceWorker *PortScannerMapReducer::createMapReduceWorker (const SI32 &readSocket, const SI32 &writeSocket)
{
    return (new PortScannerWorker (readSocket, writeSocket));
}

MapReduceWorkerProxy *PortScannerMapReducer::createMapReduceWorkerProxy (const SI32 &readSocket, const SI32 &writeSocket)
{
    return (new PortScannerWorkerProxy (readSocket, writeSocket));
}

}
