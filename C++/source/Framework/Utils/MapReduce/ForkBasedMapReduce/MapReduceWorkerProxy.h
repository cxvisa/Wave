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
class MapReduceMessageBase;
class MapReduceInputConfiguration;
class MapReduceManager;

class MapReduceWorkerProxy
{
    private :
        void receiveMessageFromWorker   (string &messageFromManager);
        bool sendWorkerReadinessMessage (MapReduceManagerDelegateMessage *pMapReduceManagerDelegateMessage);

    protected :
        virtual MapReduceWorkerReadinessMessage *instantiateWorkerReadynessMessage          () = 0;
        virtual MapReduceManagerDelegateMessage *instantiateMapReduceManagerDelegateMessage () = 0;
        virtual MapReduceWorkerResponseMessage  *instantiateWorkerResponseMessage           () = 0;
        virtual MapReduceManagerDelegateMessage *process                                    (MapReduceWorkerReadinessMessage *pMapReduceWorkerReadinessMessage) = 0;

    public :
                                                 MapReduceWorkerProxy                           (const SI32 &readSocket, const SI32 &writeSocket);
        virtual                                 ~MapReduceWorkerProxy                           ();

        virtual MapReduceWorkerReadinessMessage *receiveWorkerReadynessMessage                  ();
        virtual bool                             processWorkerReadynessMessageAndDelegate       (MapReduceInputConfiguration *pMapReduceInputConfiguration, MapReduceWorkerReadinessMessage *pMapReduceWorkerReadinessMessage);
        virtual MapReduceWorkerResponseMessage  *receiveWorkerResponseMessage                   ();
        virtual MapReduceMessageBase            *receiveWorkerMessage                           ();

                void                             resetPendingMapReduceManagerDelegateMessage    ();
                void                             errorOutPendingMapReduceManagerDelegateMessage (MapReduceManager *pMapReduceManager);

        // Now the data members

    private :
        SI32 m_readSocket;
        SI32 m_writeSocket;

        MapReduceManagerDelegateMessage *m_pPendingMapReduceManagerDelegateMessage;

    protected :
    public :
};

}

#endif // MAPREDUCEWORKERPROXY_H
