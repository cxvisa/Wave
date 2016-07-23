/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceManagerDelegateMessage.h"

namespace WaveNs
{

MapReduceManagerDelegateMessage::MapReduceManagerDelegateMessage ()
    : SerializableObject ()
{
}

MapReduceManagerDelegateMessage::~MapReduceManagerDelegateMessage ()
{
}

void MapReduceManagerDelegateMessage::setupAttributesForSerialization ()
{
    SerializableObject::setupAttributesForSerialization ();
}

}
