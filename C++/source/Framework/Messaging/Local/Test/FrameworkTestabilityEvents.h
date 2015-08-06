/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef FRAMEWORKTESTABILITYEVENTS_H
#define FRAMEWORKTESTABILITYEVENTS_H

#include "Framework/Messaging/Local/WaveEvent.h"
#include "Framework/Messaging/Local/Test/FrameworkLocalMessagingTestTypes.h"

namespace WaveNs
{

class FrameworkTestabilityEvent1 : public WaveEvent
{
    private :
    protected :
        virtual void setupAttributesForSerialization ();

    public :
                FrameworkTestabilityEvent1 ();
               ~FrameworkTestabilityEvent1 ();

        UI32    getEventUI32               () const;
        void    setEventUI32               (const UI32 &eventUI32);
        string  getEventString             () const;
        void    setEventString             (const string &eventString);

    // Now the data members

    private :
        UI32   m_eventUI32;
        string m_eventString;

    protected :
    public :
};

}

#endif // FRAMEWORKTESTABILITYEVENTS_H
