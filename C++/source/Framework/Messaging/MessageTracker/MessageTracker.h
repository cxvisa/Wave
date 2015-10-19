/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef MESSAGETRACKER_H
#define MESSAGETRACKER_H

#include "Framework/Types/Types.h"
#include "Framework/MultiThreading/WavePosixThread.h"
#include "Framework/Utils/WaveMutex.h"

#include <map>
#include <vector>

using namespace std;

namespace WaveNs
{

class WaveMessage;

class MessageTracker
{
    private :
        static bool isAKnownMessage (const WaveMessage *pWaveMessage);
        static bool isAKnownMessageWithBt (const WaveMessage *pWaveMessage);
        static void clearCurrentlyAllocatedMessagesWithBt ();

        static void getMessagesForAThread    (const WaveThreadId &prismThreadId, vector<WaveServiceId> &messageServiceIds, vector<UI32> &messageOperationCodes, vector<WaveMessageType> &messageTypes, vector<string> &btStrings); // no-lock

    protected :
    public :
        static void addToMessageTracker      (const WaveMessage *pWaveMessage);
        static void deleteFromMessageTracker (const WaveMessage *pWaveMessage);
        static void getMessages              (const WaveServiceId &waveServiceId, vector<WaveServiceId> &messageServiceIds, vector<UI32> &messageOperationCodes, vector<WaveMessageType> &messageTypes, vector<string> &btStrings);
        static void changeBtTrackerState     (const bool &btTrackerState);

    // Now the data members

    private :
        static map<WaveThreadId, map<const WaveMessage *, const WaveMessage *> > m_currentlyAllocatedMessagesByThread;
        static map<const WaveMessage *, WaveThreadId>                             m_currentlyAllocatedMessages;

        static bool                                                                 m_trackingMessagesWithBt;
        static map<const WaveMessage *, string>                                    m_currentlyAllocatedMessagesWithBt;

        static WaveMutex                                                           m_messageTrackerMutex;

    protected :
    public :
};

}

#endif // MESSAGETRACKER_H
