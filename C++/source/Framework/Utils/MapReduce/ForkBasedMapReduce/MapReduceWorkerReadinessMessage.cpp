/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorkerReadinessMessage.h"

namespace WaveNs
{

MapReduceWorkerReadinessMessage::MapReduceWorkerReadinessMessage ()
    : MapReduceMessageBase ()
{
    setMapReduceMesageType (MAP_REDUCE_MESSAGE_TYPE_READY);
}

MapReduceWorkerReadinessMessage::~MapReduceWorkerReadinessMessage ()
{
}

void MapReduceWorkerReadinessMessage::setupAttributesForSerialization ()
{
    MapReduceMessageBase::setupAttributesForSerialization ();
}

}
