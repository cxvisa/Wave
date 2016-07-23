/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef MAPREDUCEMANAGERDELEGATEMESSAGE_H
#define MAPREDUCEMANAGERDELEGATEMESSAGE_H

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceMessageBase.h"

namespace WaveNs
{

class MapReduceManagerDelegateMessage : public MapReduceMessageBase
{
    private :
    protected :
        virtual void setupAttributesForSerialization ();

    public :
                 MapReduceManagerDelegateMessage ();
        virtual ~MapReduceManagerDelegateMessage ();

        // Now the data members

    private :
    protected :
    public :
};

}

#endif // MAPREDUCEMANAGERDELEGATEMESSAGE_H
