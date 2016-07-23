/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/PortScanner/PortScannerWorkerReadinessData.h"
#include "Framework/Attributes/Attributes.h"

namespace WaveNs
{

PortScannerWorkerReadinessData::PortScannerWorkerReadinessData ()
    : MapReduceWorkerReadinessMessage (),
      m_numberOfPortsToScanFor        (0)
{
}

PortScannerWorkerReadinessData::~PortScannerWorkerReadinessData ()
{
}

void PortScannerWorkerReadinessData::setupAttributesForSerialization ()
{
    MapReduceWorkerReadinessMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeUI32 (&m_numberOfPortsToScanFor, "numberOfPortsToScanFor"));
}

UI32 PortScannerWorkerReadinessData::getNumberOfPortsToScanFor () const
{
    return (m_numberOfPortsToScanFor);
}

void PortScannerWorkerReadinessData::setNumberOfPortsToScanFor (const UI32 &numberOfPortsToScanFor)
{
    m_numberOfPortsToScanFor = numberOfPortsToScanFor;
}

}
