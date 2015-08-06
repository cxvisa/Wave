/***************************************************************************
 *  @file   : PrimaryChangedEvent.h                                        *
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Description : Please, see in PrimaryChangedEvent.cpp                  *
 *   Author      : Pritee Ghosh                                            *
 *   Date        : 03/02/2011                                              *
 ***************************************************************************/

#ifndef PRIMARYCHANGEDEVENT_H
#define PRIMARYCHANGEDEVENT_H
#include "Framework/Messaging/Local/WaveEvent.h"

namespace WaveNs
{

class PrimaryChangedEvent : public WaveEvent
{
    private :

    protected :
        virtual void        setupAttributesForSerialization ();

    public :
                            PrimaryChangedEvent ();
        virtual            ~PrimaryChangedEvent ();
                LocationId  getNewPrimaryLocationId () const;
                void        setNewPrimaryLocationId (const LocationId location);
            

    // Now the data members
    
    private :
                LocationId  m_newPrimaryLocationId;
    protected :
    public :
};

}

#endif // PRIMARYCHANGEDEVENT_H
