/**
 *  @file: LastConfigReplayCompletedEvent.h
 *  Copyright (C) 2013 Vidyasagara Guntaka                 
 *  All rights reserved.
 *  Description:Class Definition for LastConfigReplayCompleted
 *              event.This event is thrown by the framework when
 *              LastConfigReplay completes.
 *  
 *  Author : Brian Adaniya
 *  Date: 01/06/2013
 */

#ifndef LASTCONFIGREPLAYCOMPLETEDEVENT_H
#define LASTCONFIGREPLAYCOMPLETEDEVENT_H

#include "Framework/Messaging/Local/WaveEvent.h"

namespace WaveNs
{

class LastConfigReplayCompletedEvent : public WaveEvent
{
    private :
    protected :
        virtual void                    setupAttributesForSerialization         ();

    public :
                                        LastConfigReplayCompletedEvent          ();
                                        LastConfigReplayCompletedEvent          (const ResourceId &completionStatus);
        virtual                        ~LastConfigReplayCompletedEvent          ();

                ResourceId              getLastConfigReplayCompletedEventStatus () const;
                void                    setLastConfigReplayCompletedEventStatus (const ResourceId &completionStatus);

    // Now the data members

    private :
        ResourceId                      m_lastConfigReplayCompletedEventStatus;

    protected :
    public :
};

}

#endif //LASTCONFIGREPLAYCOMPLETEDEVENT_H

