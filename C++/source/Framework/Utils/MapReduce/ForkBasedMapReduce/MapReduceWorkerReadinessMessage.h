/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef MAPREDUCEWORKERREADINESSMESSAGE_H
#define MAPREDUCEWORKERREADINESSMESSAGE_H

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceMessageBase.h"

namespace WaveNs
{

class MapReduceWorkerReadinessMessage : public MapReduceMessageBase
{
    private :
    protected :
        virtual void setupAttributesForSerialization ();

    public :
                 MapReduceWorkerReadinessMessage ();
        virtual ~MapReduceWorkerReadinessMessage ();

        // Now the data members

    private :
    protected :
    public :
};

}

#endif // MAPREDUCEWORKERREADINESSMESSAGE_H
