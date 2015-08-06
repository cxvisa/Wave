/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Aashish Akhouri                                              *
 ***************************************************************************/

#ifndef WAVENODELOCALNODEDELETEDEVENT_H
#define WAVENODELOCALNODEDELETEDEVENT_H
#include "Framework/Messaging/Local/WaveEvent.h"

namespace WaveNs
{

class WaveNodeLocalNodeDeletedEvent : public WaveEvent
{
    private :
    protected :
        virtual void setupAttributesForSerialization ();

    public :
                 WaveNodeLocalNodeDeletedEvent ();
        virtual ~WaveNodeLocalNodeDeletedEvent ();

    private :
    protected :
    public :
};

}

#endif //WAVENODELOCALNODEDELETEDEVENT_H
