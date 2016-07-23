/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorkerReadinessMessage.h"

namespace WaveNs
{

MapReduceWorkerReadinessMessage::MapReduceWorkerReadinessMessage ()
    : SerializableObject ()
{
}

MapReduceWorkerReadinessMessage::~MapReduceWorkerReadinessMessage ()
{
}

void MapReduceWorkerReadinessMessage::setupAttributesForSerialization ()
{
    SerializableObject::setupAttributesForSerialization ();
}

}
