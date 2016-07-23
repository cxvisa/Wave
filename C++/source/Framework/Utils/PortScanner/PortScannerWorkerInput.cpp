/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/PortScanner/PortScannerWorkerInput.h"

namespace WaveNs
{

PortScannerWorkerInput::PortScannerWorkerInput ()
    : MapReduceManagerDelegateMessage ()
{
}

PortScannerWorkerInput::~PortScannerWorkerInput ()
{
}

void PortScannerWorkerInput::setupAttributesForSerialization ()
{
    MapReduceManagerDelegateMessage::setupAttributesForSerialization ();
}

}
