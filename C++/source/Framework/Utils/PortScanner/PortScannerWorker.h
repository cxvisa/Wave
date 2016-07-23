/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PORTSCANNERWORKER_H
#define PORTSCANNERWORKER_H

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorker.h"

namespace WaveNs
{

class PortScannerWorker : public MapReduceWorker
{
    private :
    protected :
        virtual MapReduceWorkerReadinessMessage *instantiateWorkerReadynessMessage          ();
        virtual MapReduceManagerDelegateMessage *instantiateMapReduceManagerDelegateMessage ();
        virtual MapReduceWorkerResponseMessage  *process                                    (MapReduceManagerDelegateMessage *pMapReduceManagerDelegateMessage);

    public :
                 PortScannerWorker (const SI32 &readSocket, const SI32 &writeSocket);
        virtual ~PortScannerWorker ();

        // Now the data members

    private :
    protected :
    public :
};

}

#endif // PORTSCANNERWORKER_H
