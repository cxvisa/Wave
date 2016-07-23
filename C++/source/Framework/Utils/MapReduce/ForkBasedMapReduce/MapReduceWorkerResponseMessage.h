/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef MAPREDUCEWORKERRESPONSEMESSAGE_H
#define MAPREDUCEWORKERRESPONSEMESSAGE_H

#include "Framework/ObjectModel/SerializableObject.h"

namespace WaveNs
{

class MapReduceWorkerResponseMessage : public SerializableObject
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
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
