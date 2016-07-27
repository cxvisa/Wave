/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef TCPPORTSCANNERUTILS_H
#define TCPPORTSCANNERUTILS_H

#include <sys/select.h>
#include "Framework/Types/Types.h"
#include "Framework/Utils/PortScanner/PortScannerInputConfiguration.h"

#include <string>
#include <set>

using namespace std;

namespace WaveNs
{

class PortScanner
{
    private :
        static bool computeNumberOfPortsToScanInABatch (UI32 &numberOfPortsToScanInABatch);

    protected :
    public :
        static bool       scanForIpPorts (const string &ipAddress, set<UI32> inputPorts, const UI32 &timeoutInMilliSeconds, set<UI32> &openPorts, set<UI32> &closedPorts, set<UI32> &timedOutPorts, set<UI32> &notTriedPorts);
        static ResourceId scanPorts      (const PortScannerInputConfiguration &portScannerInputConfiguration, set<UI32> &allOpenPorts, set<UI32> &allClosedPorts, set<UI32> &allTimedOutPorts, set<UI32> &allNotTriedPorts);
        static ResourceId scanPorts      (const PortScannerInputConfiguration &portScannerInputConfiguration);

        // Now the data members

    private :
    protected :
    public :
};

}

#endif // TCPPORTSCANNERUTILS_H
