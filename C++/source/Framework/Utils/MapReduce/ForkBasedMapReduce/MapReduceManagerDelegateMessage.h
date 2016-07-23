/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef MAPREDUCEMANAGERDELEGATEMESSAGE_H
#define MAPREDUCEMANAGERDELEGATEMESSAGE_H

#include "Framework/ObjectModel/SerializableObject.h"

namespace WaveNs
{

class MapReduceManagerDelegateMessage : public SerializableObject
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
