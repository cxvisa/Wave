/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/PortScanner/PortScannerWorkerInput.h"
#include "Framework/Attributes/Attributes.h"
#include "Framework/Attributes/AttributeUI32Range.h"

namespace WaveNs
{

PortScannerWorkerInput::PortScannerWorkerInput ()
    : MapReduceManagerDelegateMessage (),
      m_timeoutInMilliSeconds         (0)
{
}

PortScannerWorkerInput::~PortScannerWorkerInput ()
{
}

void PortScannerWorkerInput::setupAttributesForSerialization ()
{
    MapReduceManagerDelegateMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeString    (&m_ipAddress, "ipAddress"));
    addSerializableAttribute (new AttributeUI32Range (&m_portRange, "portRange"));
    addSerializableAttribute (new AttributeUI32      (&m_timeoutInMilliSeconds, "timeoutInMilliSeconds"));
}

string PortScannerWorkerInput::getIpAddress () const
{
    return (m_ipAddress);
}

void PortScannerWorkerInput::setIpAddress (const string &ipAddress)
{
    m_ipAddress = ipAddress;
}

UI32Range PortScannerWorkerInput::getPortRange () const
{
    return (m_portRange);
}

void PortScannerWorkerInput::setPortRange (const UI32Range &portRange)
{
    m_portRange = portRange;
}

UI32 PortScannerWorkerInput::getTimeoutInMilliSeconds () const
{
    return (m_timeoutInMilliSeconds);
}

void PortScannerWorkerInput::setTimeoutInMilliSeconds (const UI32 &timeoutInMilliSeconds)
{
    m_timeoutInMilliSeconds = timeoutInMilliSeconds;
}
}
