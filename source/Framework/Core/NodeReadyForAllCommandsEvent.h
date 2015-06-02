/**
 *  @file: NodeReadyForAllCommandsEvent.h
 *  Copyright (C) 2010 Vidyasagara Guntaka                 
 *  All rights reserved.
 *  Description:Class Definition for the event that denotes that
 *              the node is ready to pricess all commands from
 *              cli.This event is thrown by the framework.
 *  
 *  Author : Aashish Akhouri
 *  Date: 10/20/2010
 */
#ifndef NODEREADYFORALLCOMMANDSEVENT_H
#define NODEREADYFORALLCOMMANDSEVENT_H
#include "Framework/Messaging/Local/PrismEvent.h"

namespace WaveNs
{

class NodeReadyForAllCommandsEvent : public PrismEvent
{
    private :
    protected :
        virtual void setupAttributesForSerialization ();

    public :
                 NodeReadyForAllCommandsEvent ();
                 NodeReadyForAllCommandsEvent (const ResourceId &recoveryType);
        virtual ~NodeReadyForAllCommandsEvent ();
                 ResourceId   getRecoveryType () const;
         void    setRecoveryType (const ResourceId &recoveryType);

    private :
                 ResourceId   m_recoveryType;
    protected :
    public :
};

}

#endif //NODEREADYFORALLCOMMANDSEVENT_H

