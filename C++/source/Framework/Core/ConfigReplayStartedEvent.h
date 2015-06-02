/**
 *  @file: ConfigReplayStartedEvent.h
 *  Copyright (C) 2010 Vidyasagara Guntaka                 
 *  All rights reserved.
 *  Description:Class Definition for ConfigReplayStart
 *              event.This event is thrown by the framework
 *              when config replay starts.
 *  
 *  Author : Aashish Akhouri
 *  Date: 10/20/2010
 */

#ifndef CONFIGREPLAYSTARTEDEVENT_H
#define CONFIGREPLAYSTARTEDEVENT_H
#include "Framework/Messaging/Local/PrismEvent.h"

namespace WaveNs
{

class ConfigReplayStartedEvent : public PrismEvent
{
    private :
    protected :
        virtual void setupAttributesForSerialization ();

    public :
                 ConfigReplayStartedEvent ();
                 ConfigReplayStartedEvent (const bool &flag);
        virtual ~ConfigReplayStartedEvent ();
                bool getConfigFileReplayFlag () const;
                void setConfigFileReplayFlag (const bool &flag);

    private :
                bool m_configFileReplayFlag;
    protected :
    public :
};

}

#endif //CONFIGREPLAYSTARTEDEVENT_H

