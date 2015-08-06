/**
 *  @file: ConfigReplayCompletedEvent.h
 *  Copyright (C) 2010 Vidyasagara Guntaka                 
 *  All rights reserved.
 *  Description:Class Definition for ConfigReplayCompletedEvent
 *              event.This event is thrown by the framework
 *              when config replay completes.
 *  
 *  Author : Aashish Akhouri
 *  Date: 10/20/2010
 */

#ifndef CONFIGREPLAYCOMPLETEDEVENT_H
#define CONFIGREPLAYCOMPLETEDEVENT_H
#include "Framework/Messaging/Local/WaveEvent.h"

namespace WaveNs
{

class ConfigReplayCompletedEvent : public WaveEvent
{
    private :
    protected :
        virtual void setupAttributesForSerialization ();

    public :
                 ConfigReplayCompletedEvent ();
                 ConfigReplayCompletedEvent (const ResourceId &recoveryType);
        virtual ~ConfigReplayCompletedEvent ();
                 ResourceId   getRecoveryType () const;
         void    setRecoveryType (const ResourceId &recoveryType);

    private :
                 ResourceId   m_recoveryType;
    protected :
    public :
};

}

#endif //CONFIGREPLAYCOMPLETEDEVENT_H

