/***************************************************************************
 *   Copyright (C) 2012 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#ifndef INTERLOCATION_MULTICAST_MESSAGE_H
#define INTERLOCATION_MULTICAST_MESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"
#include "Framework/Utils/WaveMutex.h"
#include <vector>
#include <set>
#include <string>
#include <map>

using namespace std;

namespace WaveNs
{

class InterLocationMulticastMessage : public WaveMessage
{
 public:

                                             InterLocationMulticastMessage              ();
    virtual                                 ~InterLocationMulticastMessage              ();

            string                          &getSerializedStringToSend                  ();
            void                             setSerializedStringToSend                  (const string &serializedString);

            ResourceId                       getStatusForALocation                      (LocationId &locationId);
            void                             setStatusForALocation                      (LocationId &locationId, ResourceId &locationStatus);

            void                             getLocationIdsToSend                       (set<LocationId> &locationIdsToSend);
            void                             setLocationIdsToSend                       (set<LocationId> &locationIdsToSend);
            InterLocationMulticastMessage   &operator ++                                ();
            InterLocationMulticastMessage   &operator --                                ();
            void                             setMessageIdForMessageToMulticast          (const UI32 &messageId);
            UI32                             getMessageIdForMessageToMulticast          ();
            bool                             areAllMessageRepliesReceived                 ();

            void                             messageOperationAccess                     ();
            void                             messageOperationReleaseAccess              ();

            bool                             isMessageSentToThisLocation                (const LocationId &locationId);
            bool                             isMessageSentToThisLocationNotReplied      (const LocationId &locationId) const;
            void                             setMessageRepliedToThisLocation            (const LocationId &locationId);
 protected:
 private:
            void                             lockAccess                                 ();
            void                             unlockAccess                               ();

 public:
 protected:
 private:

    string                          m_serializedStringToSend;
    map<LocationId, ResourceId>     m_locationStatus;
    map<LocationId, LocationId>     m_locationsReplied;
    set<LocationId>                 m_locationIdsToSend;
    UI32                            m_numberOfMessagesSentAndOutStanding;
    UI32                            m_messageIdForMessageToMulticast;
    WaveMutex                      m_accessMutex;
    WaveMutex                      m_messageAccessMutex;
};

}

#endif //INTERLOCATION_MULTICAST_MESSAGE_H
