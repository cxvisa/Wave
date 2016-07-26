/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef MAPREDUCEWORKER_H
#define MAPREDUCEWORKER_H

#include "Framework/Types/Types.h"

namespace WaveNs
{

class MapReduceWorkerReadinessMessage;
class MapReduceManagerDelegateMessage;
class MapReduceWorkerResponseMessage;
class MapReduceMessageBase;

class MapReduceWorker
{
    private :
        void                  receiveMessageFromManager (string &messageFromManager);
        MapReduceMessageBase *receiveManagerMessage     ();
        bool                  sendMessageToManager      (MapReduceMessageBase *pMapReduceMessageBase);

    protected :
        virtual MapReduceWorkerReadinessMessage *instantiateWorkerReadynessMessage          () = 0;
        virtual MapReduceManagerDelegateMessage *instantiateMapReduceManagerDelegateMessage () = 0;
        virtual MapReduceWorkerResponseMessage  *process                                    (MapReduceManagerDelegateMessage *pMapReduceManagerDelegateMessage) = 0;

    public :
                                                 MapReduceWorker                            (const SI32 &readSocket, const SI32 &writeSocket);
        virtual                                 ~MapReduceWorker                            ();

        virtual bool                             sendWorkerReadinessMessage                 ();
        virtual MapReduceManagerDelegateMessage *receiveManagerDelegateMessage              ();
        virtual bool                             processAndSendWorkerResponseMessage        (MapReduceManagerDelegateMessage *pMapReduceManagerDelegateMessage);

        // Now the data members

    private :
        SI32 m_readSocket;
        SI32 m_writeSocket;

    protected :
    public :
};

}

#endif // MAPREDUCEWORKER_H
