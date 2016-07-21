/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef TCPPORTSCANNERUTILS_H
#define TCPPORTSCANNERUTILS_H

#include <sys/select.h>
#include "Framework/Types/Types.h"

#include <string>
#include <set>

using namespace std;

namespace WaveNs
{

class TcpPortScanner
{
    private :
        static void fdCopy (fd_set *pSource, fd_set *pDestination);
        static SI32 fdMax  (fd_set *pSource);

    protected :
    public :
        static bool       scanForIpV4TcpPorts (const string &ipV4Address, set<UI32> inputPorts, set<UI32> &openPorts, set<UI32> &closedPorts, set<UI32> &timedOutPorts, set<UI32> &notTriedPorts);
        static ResourceId scanPorts (vector<string> argv);
        // Now the data members

    private :
    protected :
    public :
};

}

#endif // TCPPORTSCANNERUTILS_H
