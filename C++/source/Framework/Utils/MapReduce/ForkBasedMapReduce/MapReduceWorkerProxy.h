/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef MAPREDUCEWORKERPROXY_H
#define MAPREDUCEWORKERPROXY_H

#include "Framework/Types/Types.h"

namespace WaveNs
{

class MapReduceWorkerReadinessMessage;
class MapReduceManagerDelegateMessage;
class MapReduceWorkerResponseMessage;

class MapReduceWorkerProxy
{
    private :
    protected :
        virtual MapReduceWorkerReadinessMessage *instantiateWorkerReadynessMessage          () = 0;
        virtual MapReduceManagerDelegateMessage *instantiateMapReduceManagerDelegateMessage () = 0;
        virtual MapReduceWorkerResponseMessage  *instantiateWorkerResponseMessage           () = 0;
        virtual MapReduceManagerDelegateMessage *process                                    (MapReduceWorkerReadinessMessage *pMapReduceWorkerReadinessMessage) = 0;

    public :
                 MapReduceWorkerProxy (const SI32 &readSocket, const SI32 &writeSocket);
        virtual ~MapReduceWorkerProxy ();

        virtual MapReduceWorkerReadinessMessage *receiveWorkerReadynessMessage            ();
        virtual bool                             processWorkerReadynessMessageAndDelegate (MapReduceWorkerReadinessMessage *pMapReduceWorkerReadinessMessage);
        virtual MapReduceWorkerResponseMessage  *receiveWorkerResponseMessage             ();

        // Now the data members

    private :
        SI32 m_readSocket;
        SI32 m_writeSocket;

    protected :
    public :
};

}

#endif // MAPREDUCEWORKERPROXY_H
