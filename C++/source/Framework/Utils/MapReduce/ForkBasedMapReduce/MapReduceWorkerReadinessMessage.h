/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef MAPREDUCEWORKERREADINESSMESSAGE_H
#define MAPREDUCEWORKERREADINESSMESSAGE_H

#include "Framework/ObjectModel/SerializableObject.h"

namespace WaveNs
{

class MapReduceWorkerReadinessMessage : public SerializableObject
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
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
