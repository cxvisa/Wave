/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PORTSCANNERMAPREDUCER_H
#define PORTSCANNERMAPREDUCER_H

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceManager.h"

namespace WaveNs
{

class PortScannerInputConfiguration;

class PortScannerMapReducer : public MapReduceManager
{
    private :
        virtual MapReduceWorker      *createMapReduceWorker      (const SI32 &readSocket, const SI32 &writeSocket);
        virtual MapReduceWorkerProxy *createMapReduceWorkerProxy (const SI32 &readSocket, const SI32 &writeSocket);

    protected :
    public :
                 PortScannerMapReducer (const PortScannerInputConfiguration *pPortScannerInputConfiguration);
        virtual ~PortScannerMapReducer ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // PORTSCANNERMAPREDUCER_H
