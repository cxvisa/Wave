/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceManagerDelegateMessage.h"

namespace WaveNs
{

MapReduceManagerDelegateMessage::MapReduceManagerDelegateMessage ()
    : MapReduceMessageBase ()
{
    setMapReduceMesageType (MAP_REDUCE_MESSAGE_TYPE_DELEGATE);
}

MapReduceManagerDelegateMessage::~MapReduceManagerDelegateMessage ()
{
}

void MapReduceManagerDelegateMessage::setupAttributesForSerialization ()
{
    MapReduceMessageBase::setupAttributesForSerialization ();
}

}
