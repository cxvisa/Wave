/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/PortScanner/PortScannerWorkerOutput.h"

namespace WaveNs
{

PortScannerWorkerOutput::PortScannerWorkerOutput ()
    : MapReduceWorkerResponseMessage ()
{
}

PortScannerWorkerOutput::~PortScannerWorkerOutput ()
{
}

void PortScannerWorkerOutput::setupAttributesForSerialization ()
{
    MapReduceWorkerResponseMessage::setupAttributesForSerialization ();
}
}
