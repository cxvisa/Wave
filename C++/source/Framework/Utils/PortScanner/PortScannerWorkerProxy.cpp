/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/PortScanner/PortScannerWorkerProxy.h"

namespace WaveNs
{

PortScannerWorkerProxy::PortScannerWorkerProxy (const SI32 &readSocket, const SI32 &writeSocket)
    : MapReduceWorkerProxy(readSocket, writeSocket)
{
}

PortScannerWorkerProxy::~PortScannerWorkerProxy ()
{

}

}
