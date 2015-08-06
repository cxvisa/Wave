/***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef BOOTCOMPLETEFORTHISLOCATIONEVENT_H
#define BOOTCOMPLETEFORTHISLOCATIONEVENT_H

#include "Framework/Messaging/Local/WaveEvent.h"

namespace WaveNs
{

class BootCompleteForThisLocationEvent : public WaveEvent
{
    private :
    protected :
        virtual void setupAttributesForSerialization ();

    public :
                 BootCompleteForThisLocationEvent (bool flagSchemaChange);
        virtual ~BootCompleteForThisLocationEvent ();
        bool     needLogAfterSchemaChange         () const;

    // Now the data members

    private :
        bool            m_logSchemaChangeFlag;
    protected :
    public :
};

}

#endif // BOOTCOMPLETEFORTHISLOCATIONEVENT_H
