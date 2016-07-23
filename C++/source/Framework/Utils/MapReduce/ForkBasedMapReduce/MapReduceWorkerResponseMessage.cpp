/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorkerResponseMessage.h"

namespace WaveNs
{

MapReduceWorkerResponseMessage::MapReduceWorkerResponseMessage ()
    : SerializableObject ()
{
}

MapReduceWorkerResponseMessage::~MapReduceWorkerResponseMessage ()
{
}

void MapReduceWorkerResponseMessage::setupAttributesForSerialization ()
{
    SerializableObject::setupAttributesForSerialization ();
}

}
