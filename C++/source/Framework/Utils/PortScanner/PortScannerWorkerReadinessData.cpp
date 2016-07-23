/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/PortScanner/PortScannerWorkerReadinessData.h"

namespace WaveNs
{

PortScannerWorkerReadinessData::PortScannerWorkerReadinessData ()
    : MapReduceWorkerReadinessMessage ()
{
}

PortScannerWorkerReadinessData::~PortScannerWorkerReadinessData ()
{
}

void PortScannerWorkerReadinessData::setupAttributesForSerialization ()
{
    MapReduceWorkerReadinessMessage::setupAttributesForSerialization ();
}

}
