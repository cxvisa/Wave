/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef HABOOTCOMPLETEFORTHISLOCATIONEVENT_H
#define HABOOTCOMPLETEFORTHISLOCATIONEVENT_H

#include "Framework/Messaging/Local/WaveEvent.h"

namespace WaveNs
{

class HaBootCompleteForThisLocationEvent : public WaveEvent
{
    private :
    protected :
        virtual void setupAttributesForSerialization ();

    public :
                 HaBootCompleteForThisLocationEvent ();
        virtual ~HaBootCompleteForThisLocationEvent ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // HABOOTCOMPLETEFORTHISLOCATIONEVENT_H
