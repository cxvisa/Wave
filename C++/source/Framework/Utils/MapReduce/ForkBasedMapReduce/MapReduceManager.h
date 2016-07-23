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

class MapReduceManager
{
    private :
    protected :
    public :
                           MapReduceManager (const MapReduceInputConfiguration *m_pMapReduceInputConfiguration);
        virtual           ~MapReduceManager ();

                ResourceId mapReduce        ();

        // Now the data members

    private :
        const MapReduceInputConfiguration *m_pMapReduceInputConfiguration;

    protected :
    public :

        static const SI32 s_MAX_PARTITIONS_LIMIT = 500;
};

}

#endif // MAPREDUCEMANAGER_H
