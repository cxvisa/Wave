/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/PortScanner/PortScannerMapReducer.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/PortScanner/PortScannerInputConfiguration.h"
#include "Framework/Utils/PortScanner/PortScannerWorker.h"
#include "Framework/Utils/PortScanner/PortScannerWorkerProxy.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorkerResponseMessage.h"
#include "Framework/Utils/PortScanner/PortScannerWorkerOutput.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/PortScanner/PortScannerWorkerInput.h"

#include <netdb.h>

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

void PortScannerMapReducer::consumeMapReduceWorkerOutput (MapReduceWorkerResponseMessage *pMapReduceWorkerResponseMessage)
{
    WaveNs::waveAssert (NULL != pMapReduceWorkerResponseMessage, __FILE__, __LINE__);

    PortScannerWorkerOutput *pPortScannerWorkerOutput = dynamic_cast<PortScannerWorkerOutput *> (pMapReduceWorkerResponseMessage);

    WaveNs::waveAssert (NULL != pPortScannerWorkerOutput, __FILE__, __LINE__);

    vector<UI32> allOpenPortsVector     = pPortScannerWorkerOutput->getAllOpenPorts     ();
    vector<UI32> allClosedPortsVector   = pPortScannerWorkerOutput->getAllClosedPorts   ();
    vector<UI32> allTimedOutPortsVector = pPortScannerWorkerOutput->getAllTimedOutPorts ();
    vector<UI32> allNotTriedPortsVector = pPortScannerWorkerOutput->getAllNotTriedPorts ();

    m_allOpenPorts.insert     (allOpenPortsVector.begin     (), allOpenPortsVector.end     ());
    m_allClosedPorts.insert   (allClosedPortsVector.begin   (), allClosedPortsVector.end   ());
    m_allTimedOutPorts.insert (allTimedOutPortsVector.begin (), allTimedOutPortsVector.end ());
    m_allNotTriedPorts.insert (allNotTriedPortsVector.begin (), allNotTriedPortsVector.end ());
}

void PortScannerMapReducer::errorOutMapReduceWorkerInput (MapReduceManagerDelegateMessage *pMapReduceManagerDelegateMessage)
{
    WaveNs::waveAssert (NULL != pMapReduceManagerDelegateMessage, __FILE__, __LINE__);

    PortScannerWorkerInput *pPortScannerWorkerInput = dynamic_cast<PortScannerWorkerInput *> (pMapReduceManagerDelegateMessage);

    WaveNs::waveAssert (NULL != pPortScannerWorkerInput, __FILE__, __LINE__);

    UI32Range inputPortRange = pPortScannerWorkerInput->getPortRange ();

    vector<UI32> inputPortsVector;

    inputPortRange.getUI32RangeVector (inputPortsVector);

    // TODO : For now we always onsiders errored out port range proessing a not tried ports.
    //        We shpuld pass a reason code (resource id) into this member function and insert
    //        ports into timed out / not tried as per the reason code.

    m_allNotTriedPorts.insert (inputPortsVector.begin (), inputPortsVector.end ());
}

void PortScannerMapReducer::printReport ()
{
    WaveNs::tracePrintf (TRACE_LEVEL_INFO, true, false, "PortScannerMapReducer::printReport : Currently open ports : %u", m_allOpenPorts.size ());

    set<UI32>::const_iterator elementForAllOpenPorts    = m_allOpenPorts.begin ();
    set<UI32>::const_iterator endElementForAllOpenPorts = m_allOpenPorts.end   ();

    setservent (1);

    while (endElementForAllOpenPorts != elementForAllOpenPorts)
    {
        struct servent *pServiceEntry = getservbyport (htons ((int) (*elementForAllOpenPorts)), "tcp");

        WaveNs::tracePrintf (TRACE_LEVEL_INFO, true, true, "%5u %s", *elementForAllOpenPorts, pServiceEntry != NULL ? pServiceEntry->s_name : "Unknown");

        elementForAllOpenPorts++;
    }

    endservent ();

    WaveNs::tracePrintf (TRACE_LEVEL_INFO, true, false, "PortScannerMapReducer::printReport : Currently Closed ports    : %u", m_allClosedPorts.size   ());
    WaveNs::tracePrintf (TRACE_LEVEL_INFO, true, false, "PortScannerMapReducer::printReport : Currently Timed out ports : %u", m_allTimedOutPorts.size ());
    WaveNs::tracePrintf (TRACE_LEVEL_INFO, true, false, "PortScannerMapReducer::printReport : Currently Not Tried ports : %u", m_allNotTriedPorts.size ());
}

}
