/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef MESSAGETRACKER_H
#define MESSAGETRACKER_H

#include "Framework/Types/Types.h"
#include "Framework/MultiThreading/PrismPosixThread.h"
#include "Framework/Utils/PrismMutex.h"

#include <map>
#include <vector>

using namespace std;

namespace WaveNs
{

class PrismMessage;

class MessageTracker
{
    private :
        static bool isAKnownMessage (const PrismMessage *pPrismMessage);
        static bool isAKnownMessageWithBt (const PrismMessage *pPrismMessage);
        static void clearCurrentlyAllocatedMessagesWithBt ();

        static void getMessagesForAThread    (const PrismThreadId &prismThreadId, vector<WaveServiceId> &messageServiceIds, vector<UI32> &messageOperationCodes, vector<WaveMessageType> &messageTypes, vector<string> &btStrings); // no-lock

    protected :
    public :
        static void addToMessageTracker      (const PrismMessage *pPrismMessage);
        static void deleteFromMessageTracker (const PrismMessage *pPrismMessage);
        static void getMessages              (const WaveServiceId &prismServiceId, vector<WaveServiceId> &messageServiceIds, vector<UI32> &messageOperationCodes, vector<WaveMessageType> &messageTypes, vector<string> &btStrings);
        static void changeBtTrackerState     (const bool &btTrackerState);

    // Now the data members

    private :
        static map<PrismThreadId, map<const PrismMessage *, const PrismMessage *> > m_currentlyAllocatedMessagesByThread;
        static map<const PrismMessage *, PrismThreadId>                             m_currentlyAllocatedMessages;

        static bool                                                                 m_trackingMessagesWithBt;
        static map<const PrismMessage *, string>                                    m_currentlyAllocatedMessagesWithBt;

        static PrismMutex                                                           m_messageTrackerMutex;

    protected :
    public :
};

}

#endif // MESSAGETRACKER_H
