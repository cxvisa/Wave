/**
 *  @file: PostBootCompletedEvent.h
 *  Copyright (C) 2010 Vidyasagara Guntaka                 
 *  All rights reserved.
 *  Description:Class Definition for PostBootCompleted
 *              event.This event is thrown by the framework when
 *              PostBoot completes.
 *  
 *  Author : Aashish Akhouri
 *  Date: 10/20/2010
 */
#ifndef POSTBOOTCOMPLETEDEVENT_H
#define POSTBOOTCOMPLETEDEVENT_H
#include "Framework/Messaging/Local/WaveEvent.h"

namespace WaveNs
{

class PostBootCompletedEvent : public WaveEvent
{
    private :
    protected :
        virtual void setupAttributesForSerialization ();

    public :
                 PostBootCompletedEvent ();
				 PostBootCompletedEvent (const UI32 &eventId, const UI32 &parameter);
        virtual ~PostBootCompletedEvent ();

                UI32 getPostBootCompletedEventId () const;
                UI32 getPostBootCompletedEventParameter () const;
                void setPostBootCompletedEventId (const UI32 &eventId);
                void setPostBootCompletedEventParameter (const UI32 &parameter);

    // Now the data members

    private :
                UI32 m_eventId;
                UI32 m_parameter;
    protected :
    public :


};

}

#endif //POSTBOOTCOMPLETEDEVENT_H

