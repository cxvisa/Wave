/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/Local/PrismEvent.h"
#include "Framework/Utils/TraceUtils.h"

namespace WaveNs
{

PrismEvent::PrismEvent (WaveServiceId serviceCode, UI32 operationCode)
    : PrismMessage (serviceCode, operationCode),
      m_referenceCountForEventNotifications (1)
{
    setType (WAVE_MESSAGE_TYPE_EVENT);
}

PrismEvent::~PrismEvent ()
{
    if (0 != m_referenceCountForEventNotifications)
    {
        trace (TRACE_LEVEL_FATAL, "PrismEvent::~PrismEvent : Trying to delete an event while it is still being used by a listener.");
    }
}

void PrismEvent::setupAttributesForSerialization ()
{
    PrismMessage::setupAttributesForSerialization ();
}

UI32 PrismEvent::getReferenceCountForEventNotifications () const
{
    PrismEvent *pTempEvent = (PrismEvent *) this; // Consciously overriding the const behavior.

    UI32 referenceCountForEventNotifications = 0;

    pTempEvent->m_referenceCountForEventNotificationsMutex.lock ();

    referenceCountForEventNotifications = pTempEvent->m_referenceCountForEventNotifications;

    pTempEvent->m_referenceCountForEventNotificationsMutex.unlock ();

    return (referenceCountForEventNotifications);
}

UI32 PrismEvent::incrementReferenceCountForEventNotifications () const
{
    PrismEvent *pTempEvent = (PrismEvent *) this; // Consciously overriding the const behavior.

    UI32 referenceCountForEventNotifications = 0;

    pTempEvent->m_referenceCountForEventNotificationsMutex.lock ();

    pTempEvent->m_referenceCountForEventNotifications++;
    referenceCountForEventNotifications = pTempEvent->m_referenceCountForEventNotifications;

    pTempEvent->m_referenceCountForEventNotificationsMutex.unlock ();

    return (referenceCountForEventNotifications);
}

UI32 PrismEvent::decrementReferenceCountForEventNotifications () const
{
    PrismEvent *pTempEvent = (PrismEvent *) this; // Consciously overriding the const behavior.

    UI32 referenceCountForEventNotifications = 0;

    pTempEvent->m_referenceCountForEventNotificationsMutex.lock ();

    pTempEvent->m_referenceCountForEventNotifications--;
    referenceCountForEventNotifications = pTempEvent->m_referenceCountForEventNotifications;

    pTempEvent->m_referenceCountForEventNotificationsMutex.unlock ();

    return (referenceCountForEventNotifications);
}

void PrismEvent::setReferenceCountForEventNotifications (const UI32 &referenceCountForEventNotifications)
{
    m_referenceCountForEventNotificationsMutex.lock ();

    m_referenceCountForEventNotifications = referenceCountForEventNotifications;

    m_referenceCountForEventNotificationsMutex.unlock ();
}

}
