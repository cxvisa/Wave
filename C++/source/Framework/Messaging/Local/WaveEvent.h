/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMEVENT_H
#define PRISMEVENT_H

#include "Framework/Messaging/Local/WaveMessage.h"
#include "Framework/Utils/PrismMutex.h"

namespace WaveNs
{

class WaveEvent : public WaveMessage
{
    private :
        UI32 getReferenceCountForEventNotifications       () const;
        UI32 incrementReferenceCountForEventNotifications () const;
        UI32 decrementReferenceCountForEventNotifications () const;
        void setReferenceCountForEventNotifications       (const UI32 &referenceCountForEventNotifications);

    protected :
                     WaveEvent                      (WaveServiceId serviceCode, UI32 operationCode);
        virtual void setupAttributesForSerialization ();

    public :
        ~WaveEvent ();

    // Now the data members

    private :
        UI32       m_referenceCountForEventNotifications;
        PrismMutex m_referenceCountForEventNotificationsMutex;

    protected :
    public :

    friend class WaveObjectManager;
};

}

#endif // PRISMEVENT_H
