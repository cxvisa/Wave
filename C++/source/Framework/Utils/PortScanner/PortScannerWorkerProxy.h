/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PORTSCANNERWORKERPROXY_H
#define PORTSCANNERWORKERPROXY_H

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorkerProxy.h"

namespace WaveNs
{

class PortScannerWorkerProxy : public MapReduceWorkerProxy
{
    private :
    protected :
    public :
                 PortScannerWorkerProxy (const SI32 &readSocket, const SI32 &writeSocket);
        virtual ~PortScannerWorkerProxy ();


        // Now the data members

    private :
    protected :
    public :
};

}

#endif // PORTSCANNERWORKERPROXY_H
