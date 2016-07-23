/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Types/Types.h"
#include "Framework/Redundancy/RedundancyOptimizerBase.h"
#include "Framework/Utils/PortScanner/TcpPortScanner.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/SystemErrorUtils.h"
#include "Framework/Utils/PortScanner/TcpPortScannerInputConfiguration.h"

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceManager.h"
using namespace std;
using namespace WaveNs;

int main (int argc, char *argv[])
{
    TcpPortScannerInputConfiguration tcpPortScannerInputConfiguration;

    bool parsingStatus = tcpPortScannerInputConfiguration.parseCommandLineInputs (argc, argv);

    if (! parsingStatus)
    {
        exit (-1);
    }

    MapReduceManager mapReduceManager (&tcpPortScannerInputConfiguration);

    mapReduceManager.mapReduce();

    //TcpPortScanner::scanPorts (tcpPortScannerInputConfiguration);

    return (0);
}
