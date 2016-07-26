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

    addSerializableAttribute (new AttributeUI32Vector (&m_allOpenPorts,     "allOpenPorts"));
    addSerializableAttribute (new AttributeUI32Vector (&m_allClosedPorts,   "allClosedPorts"));
    addSerializableAttribute (new AttributeUI32Vector (&m_allTimedOutPorts, "allTimedOutPorts"));
    addSerializableAttribute (new AttributeUI32Vector (&m_allNotTriedPorts, "allNotTriedPorts"));
}

vector<UI32> PortScannerWorkerOutput::getAllOpenPorts () const
{
    return (m_allOpenPorts);
}

void PortScannerWorkerOutput::setAllOpenPorts (const vector<UI32> &allOpenPorts)
{
    m_allOpenPorts = allOpenPorts;
}

vector<UI32> PortScannerWorkerOutput::getAllClosedPorts () const
{
    return (m_allClosedPorts);
}

void PortScannerWorkerOutput::setAllClosedPorts (const vector<UI32> &allClosedPorts)
{
    m_allClosedPorts = allClosedPorts;
}

vector<UI32> PortScannerWorkerOutput::getAllTimedOutPorts () const
{
    return (m_allTimedOutPorts);
}

void PortScannerWorkerOutput::setAllTimedOutPorts (const vector<UI32> &allTimedOutPorts)
{
    m_allTimedOutPorts = allTimedOutPorts;
}

vector<UI32> PortScannerWorkerOutput::getAllNotTriedPorts () const
{
    return (m_allNotTriedPorts);
}

void PortScannerWorkerOutput::setAllNotTriedPorts (const vector<UI32> &allNotTriedPorts)
{
    m_allNotTriedPorts = allNotTriedPorts;
}

}
