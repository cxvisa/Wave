/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PORTSCANNERMAPREDUCER_H
#define PORTSCANNERMAPREDUCER_H

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceManager.h"

#include <set>

using namespace std;

namespace WaveNs
{

class PortScannerInputConfiguration;
class MapReduceWorkerResponseMessage;

class PortScannerMapReducer : public MapReduceManager
{
    private :
        virtual MapReduceWorker      *createMapReduceWorker        (const SI32 &readSocket, const SI32 &writeSocket);
        virtual MapReduceWorkerProxy *createMapReduceWorkerProxy   (const SI32 &readSocket, const SI32 &writeSocket);
        virtual void                  consumeMapReduceWorkerOutput (MapReduceWorkerResponseMessage *pMapReduceWorkerResponseMessage);
        virtual void                  errorOutMapReduceWorkerInput (MapReduceManagerDelegateMessage *pMapReduceManagerDelegateMessage, const MapReduceProcessingStatus &mapReduceProcessingStatus);

    protected :
    public :
                      PortScannerMapReducer (PortScannerInputConfiguration *pPortScannerInputConfiguration);
        virtual      ~PortScannerMapReducer ();

                void  printReport           ();

    // Now the data members

    private :
        set<UI32> m_allOpenPorts;
        set<UI32> m_allClosedPorts;
        set<UI32> m_allTimedOutPorts;
        set<UI32> m_allNotTriedPorts;

    protected :
    public :
};

}

#endif // PORTSCANNERMAPREDUCER_H
