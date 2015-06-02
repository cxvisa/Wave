/**
 *  @file: PostBootStartedEvent.h
 *  Copyright (C) 2010 Vidyasagara Guntaka                 
 *  All rights reserved.
 *  Description:Class Definition for PostBootStarted
 *              event.This event is thrown by the framework when
 *              PostBoot Starts.
 *  
 *  Author : Aashish Akhouri
 *  Date: 10/20/2010
 */
#ifndef POSTBOOTSTARTEDEVENT_H
#define POSTBOOTSTARTEDEVENT_H
#include "Framework/Messaging/Local/PrismEvent.h"

namespace WaveNs
{

class PostBootStartedEvent : public PrismEvent
{
    private :
    protected :
        virtual void setupAttributesForSerialization ();

    public :
                 PostBootStartedEvent ();
                 PostBootStartedEvent (const UI32 &eventId, const UI32 &parameter);
        virtual ~PostBootStartedEvent ();

                UI32 getPostBootStartedEventId () const; 
                UI32 getPostBootStartedEventParameter () const;
                void setPostBootStartedEventId (const UI32 &eventId);
                void setPostBootStartedEventParameter (const UI32 &parameter);

    private :
                UI32 m_eventId;
                UI32 m_parameter;
    protected :
    public :
};

}

#endif //POSTBOOTSTARTEDEVENT_H

