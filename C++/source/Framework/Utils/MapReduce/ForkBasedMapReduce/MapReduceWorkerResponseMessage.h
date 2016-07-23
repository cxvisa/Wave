/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef MAPREDUCEWORKERRESPONSEMESSAGE_H
#define MAPREDUCEWORKERRESPONSEMESSAGE_H

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceMessageBase.h"

namespace WaveNs
{

class MapReduceWorkerResponseMessage : public MapReduceMessageBase
{
    private :
    protected :
        virtual void setupAttributesForSerialization ();

    public :
                 MapReduceWorkerResponseMessage ();
        virtual ~MapReduceWorkerResponseMessage ();

        // Now the data members

    private :
    protected :
    public :
};

}

#endif // MAPREDUCEWORKERRESPONSEMESSAGE_H
