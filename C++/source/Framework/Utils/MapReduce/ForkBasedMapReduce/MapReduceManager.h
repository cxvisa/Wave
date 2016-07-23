/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef MAPREDUCEMANAGER_H
#define MAPREDUCEMANAGER_H

#include "Framework/Types/Types.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceInputConfiguration.h"

namespace WaveNs
{

class MapReduceWorker;
class MapReduceWorkerProxy;
class MapReduceWorkerReadinessMessage;
class MapReduceWorkerResponseMessage;

class MapReduceManager
{
    private :
        bool processWorkerReady    (MapReduceWorkerProxy *pMapReduceWorkerProxy, MapReduceWorkerReadinessMessage *pMapReduceWorkerReadinessMessage);
        bool processWorkerResponse (MapReduceWorkerProxy *pMapReduceWorkerProxy, MapReduceWorkerResponseMessage  *pMapReduceWorkerResponseMessage);

    protected :
        virtual MapReduceWorker      *createMapReduceWorker      (const SI32 &readSocket, const SI32 &writeSocket) = 0;
        virtual MapReduceWorkerProxy *createMapReduceWorkerProxy (const SI32 &readSocket, const SI32 &writeSocket) = 0;

    public :
                           MapReduceManager (MapReduceInputConfiguration *m_pMapReduceInputConfiguration);
        virtual           ~MapReduceManager ();

                ResourceId mapReduce        ();

        // Now the data members

    private :
        MapReduceInputConfiguration *m_pMapReduceInputConfiguration;

    protected :
    public :

        static const SI32 s_MAX_PARTITIONS_LIMIT = 500;
};

}

#endif // MAPREDUCEMANAGER_H
