/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Types/Types.h"
#include "Framework/Redundancy/RedundancyOptimizerBase.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/SystemErrorUtils.h"
#include "Framework/Utils/PortScanner/PortScanner.h"
#include "Framework/Utils/PortScanner/PortScannerInputConfiguration.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceManager.h"

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;
using namespace WaveNs;

int main (int argc, char *argv[])
{
    PortScannerInputConfiguration tcpPortScannerInputConfiguration;

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
