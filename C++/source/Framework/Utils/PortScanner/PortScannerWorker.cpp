/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/PortScanner/PortScannerWorker.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/FdUtils.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorkerReadinessMessage.h"
#include "Framework/Utils/PortScanner/PortScannerInputConfiguration.h"
#include "Framework/Utils/PortScanner/PortScannerWorkerInput.h"
#include "Framework/Utils/PortScanner/PortScannerWorkerReadinessData.h"
#include "Framework/Utils/PortScanner/PortScanner.h"
#include "Framework/Utils/PortScanner/PortScannerWorkerOutput.h"

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
    PortScannerWorkerInput *pPortScannerWorkerInput = dynamic_cast<PortScannerWorkerInput *> (pMapReduceManagerDelegateMessage);

    waveAssert (NULL != pPortScannerWorkerInput, __FILE__, __LINE__);

    PortScannerInputConfiguration portScannerInputConfiguration;

    portScannerInputConfiguration.setIpAddress             (pPortScannerWorkerInput->getIpAddress             ());
    portScannerInputConfiguration.setPortRange             (pPortScannerWorkerInput->getPortRange             ());
    portScannerInputConfiguration.setTimeoutInMilliSeconds (pPortScannerWorkerInput->getTimeoutInMilliSeconds ());

    set<UI32> allOpenPorts;
    set<UI32> allClosedPorts;
    set<UI32> allTimedOutPorts;
    set<UI32> allNotTriedPorts;

    // TODO : Currently we always launch the default port scanner
    //        Default scanner is TCP only and it is based on connect calls.
    //        In future we can examine command line arguments and launch various
    //        Port scanner (ex. UDP based, TCP/SYN scan based etc.,).
    //        Based on features we support, we may decide to launch more than one scanner in parallel.

    PortScanner::scanPorts (portScannerInputConfiguration, allOpenPorts, allClosedPorts, allTimedOutPorts, allNotTriedPorts);

    vector<UI32> allOpenPortsVector;
    vector<UI32> allClosedPortsVector;
    vector<UI32> allTimedOutPortsVector;
    vector<UI32> allNotTriedPortsVector;

    allOpenPortsVector.insert     (allOpenPortsVector.begin     (), allOpenPorts.begin     (), allOpenPorts.end ());
    allClosedPortsVector.insert   (allClosedPortsVector.begin   (), allClosedPorts.begin   (), allClosedPorts.end ());
    allTimedOutPortsVector.insert (allTimedOutPortsVector.begin (), allTimedOutPorts.begin (), allTimedOutPorts.end ());
    allNotTriedPortsVector.insert (allNotTriedPortsVector.begin (), allNotTriedPorts.begin (), allNotTriedPorts.end ());

    PortScannerWorkerOutput *pPortScannerWorkerOutput = new PortScannerWorkerOutput ();

    waveAssert (NULL != pPortScannerWorkerOutput, __FILE__, __LINE__);

    pPortScannerWorkerOutput->setAllOpenPorts     (allOpenPortsVector);
    pPortScannerWorkerOutput->setAllClosedPorts   (allClosedPortsVector);
    pPortScannerWorkerOutput->setAllTimedOutPorts (allTimedOutPortsVector);
    pPortScannerWorkerOutput->setAllNotTriedPorts (allNotTriedPortsVector);

    return (pPortScannerWorkerOutput);
}

}
