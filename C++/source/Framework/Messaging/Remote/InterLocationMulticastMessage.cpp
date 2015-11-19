/***************************************************************************
 *   Copyright (C) 2012 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#include "Framework/Messaging/Remote/InterLocationTypes.h"
#include "Framework/Messaging/Remote/InterLocationMulticastMessage.h"
#include "Framework/Messaging/Remote/InterLocationMessageTransportObjectManager.h"
#include "Framework/Utils/TraceUtils.h"
#include <vector>
#include <string>
#include <map>

namespace WaveNs
{
InterLocationMulticastMessage::InterLocationMulticastMessage ()
    : WaveMessage (InterLocationMessageTransportObjectManager::getWaveServiceId (), INTERLOCATION_MESSAGE_FOR_MULTICAST_SEND),
    m_numberOfMessagesSentAndOutStanding (0)
{
}

InterLocationMulticastMessage::~InterLocationMulticastMessage ()
{
}

string &InterLocationMulticastMessage::getSerializedStringToSend ()
{
    return (m_serializedStringToSend);
}

void InterLocationMulticastMessage::setSerializedStringToSend (const string &serializedString)
{
    m_serializedStringToSend = serializedString;
}

ResourceId InterLocationMulticastMessage::getStatusForALocation (LocationId &locationId)
{
    lockAccess ();

    ResourceId status = m_locationStatus [locationId];

    unlockAccess ();

    return (status);
}

void InterLocationMulticastMessage::setStatusForALocation (LocationId &locationId, ResourceId &locationStatus)
{
    lockAccess ();

    m_locationStatus [locationId] = locationStatus;

    unlockAccess ();
}

void InterLocationMulticastMessage::getLocationIdsToSend (set<LocationId> &locationIdsToSend)
{
    locationIdsToSend = m_locationIdsToSend;
}

void InterLocationMulticastMessage::setLocationIdsToSend (set<LocationId> &locationIdsToSend)
{
    m_locationIdsToSend = locationIdsToSend;
}

InterLocationMulticastMessage &InterLocationMulticastMessage::operator ++ ()
{
    lockAccess ();

    ++m_numberOfMessagesSentAndOutStanding;

    unlockAccess ();

    return (*this);

}

InterLocationMulticastMessage &InterLocationMulticastMessage::operator -- ()
{
    lockAccess ();

    --m_numberOfMessagesSentAndOutStanding;

    unlockAccess ();

    return (*this);
}

void InterLocationMulticastMessage::setMessageIdForMessageToMulticast (const UI32 &messageId)
{
    m_messageIdForMessageToMulticast = messageId;
}

UI32 InterLocationMulticastMessage::getMessageIdForMessageToMulticast ()
{
    return (m_messageIdForMessageToMulticast);
}

void InterLocationMulticastMessage::lockAccess ()
{
    m_accessMutex.lock ();
}

void InterLocationMulticastMessage::unlockAccess ()
{
    m_accessMutex.unlock ();
}

bool InterLocationMulticastMessage::areAllMessageRepliesReceived ()
{
    lockAccess ();

    if (0 == m_numberOfMessagesSentAndOutStanding)
    {
        unlockAccess ();
        return (true);
    }

    unlockAccess ();
    return (false);
}

void InterLocationMulticastMessage::messageOperationAccess ()
{
    m_messageAccessMutex.lock ();
}

void InterLocationMulticastMessage::messageOperationReleaseAccess ()
{
    m_messageAccessMutex.unlock ();
}

bool InterLocationMulticastMessage::isMessageSentToThisLocation (const LocationId &locationId)
{
    set<LocationId>::iterator it;

    it = m_locationIdsToSend.find (locationId);

    if (it != m_locationIdsToSend.end ())
    {
        return (true);
    }

    return (false);
}

bool InterLocationMulticastMessage::isMessageSentToThisLocationNotReplied (const LocationId &locationId) const
{
    map<LocationId, LocationId>::const_iterator element    = m_locationsReplied.find (locationId);
    map<LocationId, LocationId>::const_iterator endElement = m_locationsReplied.end ();

    if (element == endElement)
    {
        return (true);
    }

    return (false);
}

void InterLocationMulticastMessage::setMessageRepliedToThisLocation (const LocationId &locationId)
{
    map<LocationId, LocationId>::iterator element    = m_locationsReplied.find (locationId);
    map<LocationId, LocationId>::iterator endElement = m_locationsReplied.end ();

    if (element == endElement)
    {
        m_locationsReplied [locationId] = locationId;
    }
    else
    {
        waveAssert (false, __FILE__, __LINE__);
    }
}

}

