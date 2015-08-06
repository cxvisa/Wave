/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/Local/WaveEvent.h"
#include "Framework/Utils/TraceUtils.h"

namespace WaveNs
{

WaveEvent::WaveEvent (WaveServiceId serviceCode, UI32 operationCode)
    : WaveMessage (serviceCode, operationCode),
      m_referenceCountForEventNotifications (1)
{
    setType (WAVE_MESSAGE_TYPE_EVENT);
}

WaveEvent::~WaveEvent ()
{
    if (0 != m_referenceCountForEventNotifications)
    {
        trace (TRACE_LEVEL_FATAL, "WaveEvent::~WaveEvent : Trying to delete an event while it is still being used by a listener.");
    }
}

void WaveEvent::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();
}

UI32 WaveEvent::getReferenceCountForEventNotifications () const
{
    WaveEvent *pTempEvent = (WaveEvent *) this; // Consciously overriding the const behavior.

    UI32 referenceCountForEventNotifications = 0;

    pTempEvent->m_referenceCountForEventNotificationsMutex.lock ();

    referenceCountForEventNotifications = pTempEvent->m_referenceCountForEventNotifications;

    pTempEvent->m_referenceCountForEventNotificationsMutex.unlock ();

    return (referenceCountForEventNotifications);
}

UI32 WaveEvent::incrementReferenceCountForEventNotifications () const
{
    WaveEvent *pTempEvent = (WaveEvent *) this; // Consciously overriding the const behavior.

    UI32 referenceCountForEventNotifications = 0;

    pTempEvent->m_referenceCountForEventNotificationsMutex.lock ();

    pTempEvent->m_referenceCountForEventNotifications++;
    referenceCountForEventNotifications = pTempEvent->m_referenceCountForEventNotifications;

    pTempEvent->m_referenceCountForEventNotificationsMutex.unlock ();

    return (referenceCountForEventNotifications);
}

UI32 WaveEvent::decrementReferenceCountForEventNotifications () const
{
    WaveEvent *pTempEvent = (WaveEvent *) this; // Consciously overriding the const behavior.

    UI32 referenceCountForEventNotifications = 0;

    pTempEvent->m_referenceCountForEventNotificationsMutex.lock ();

    pTempEvent->m_referenceCountForEventNotifications--;
    referenceCountForEventNotifications = pTempEvent->m_referenceCountForEventNotifications;

    pTempEvent->m_referenceCountForEventNotificationsMutex.unlock ();

    return (referenceCountForEventNotifications);
}

void WaveEvent::setReferenceCountForEventNotifications (const UI32 &referenceCountForEventNotifications)
{
    m_referenceCountForEventNotificationsMutex.lock ();

    m_referenceCountForEventNotifications = referenceCountForEventNotifications;

    m_referenceCountForEventNotificationsMutex.unlock ();
}

}
