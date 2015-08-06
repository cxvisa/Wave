/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMEVENT_H
#define PRISMEVENT_H

#include "Framework/Messaging/Local/PrismMessage.h"
#include "Framework/Utils/PrismMutex.h"

namespace WaveNs
{

class PrismEvent : public PrismMessage
{
    private :
        UI32 getReferenceCountForEventNotifications       () const;
        UI32 incrementReferenceCountForEventNotifications () const;
        UI32 decrementReferenceCountForEventNotifications () const;
        void setReferenceCountForEventNotifications       (const UI32 &referenceCountForEventNotifications);

    protected :
                     PrismEvent                      (WaveServiceId serviceCode, UI32 operationCode);
        virtual void setupAttributesForSerialization ();

    public :
        ~PrismEvent ();

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
