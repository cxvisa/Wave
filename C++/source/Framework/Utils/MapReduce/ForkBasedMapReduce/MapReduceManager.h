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
                           MapReduceManager (const MapReduceInputConfiguration &mapReduceInputConfiguration);
        virtual           ~MapReduceManager ();

                ResourceId mapReduce        ();

        // Now the data members

    private :
        MapReduceInputConfiguration m_mapReduceInputConfiguration;

    protected :
    public :
};

}

#endif // MAPREDUCEMANAGER_H