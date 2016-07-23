/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorkerResponseMessage.h"

namespace WaveNs
{

MapReduceWorkerResponseMessage::MapReduceWorkerResponseMessage ()
    : MapReduceMessageBase ()
{
    setMapReduceMesageType (MAP_REDUCE_MESSAGE_TYPE_RESPONSE);
}

MapReduceWorkerResponseMessage::~MapReduceWorkerResponseMessage ()
{
}

void MapReduceWorkerResponseMessage::setupAttributesForSerialization ()
{
    MapReduceMessageBase::setupAttributesForSerialization ();
}

}
