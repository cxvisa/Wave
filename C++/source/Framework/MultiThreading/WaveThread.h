/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMTHREAD_H
#define PRISMTHREAD_H

#include "Framework/MultiThreading/PrismPosixThread.h"
#include "Framework/MultiThreading/WaveMessageQueue.cpp"
#include "Framework/Utils/PrismMutex.h"
#include "Framework/Utils/PrismCondition.h"
#include "Framework/Core/WaveServiceMap.h"

namespace WaveNs
{

class WaveObjectManager;
class TimerWorker;

typedef enum
{
    WAVE_THREAD_MESSAGE_QUEUE_SUCCESS = 0,
    WAVE_THREAD_MESSAGE_QUEUE_NO_MESSAGES_TO_PROCESS
} WaveThreadMessageQueueStatus;

class WaveThread : public PrismPosixThread
{
    private :
        WaveMessage       *getNextMessageToProcess                                ();
        WaveMessageStatus   submitMessage                                          (WaveMessage *pWaveMessage);
        WaveMessageStatus   submitMessageAtFront                                   (WaveMessage *pWaveMessage);
        WaveMessageStatus   submitMessageAtBack                                    (WaveMessage *pWaveMessage);
        WaveMessageStatus   recallMessage                                          (WaveMessage *pWaveMessage);
        UI32                recallTimerExpirationMessagesForTimer                  (const TimerHandle &timerHandle);
        WaveMessageStatus   submitReplyMessage                                     (WaveMessage *pWaveMessage);
        WaveMessageStatus   submitEvent                                            (WaveEvent *pWaveEvent);
        WaveObjectManager *getWaveObjectManagerForOperationCode                  (UI32 operationCode);
        WaveObjectManager *getWaveObjectManagerForEventOperationCode             (UI32 eventOperationCode);
        WaveObjectManager *getWaveObjectManagerForEventOperationCodeForListening (const LocationId &eventSourceLocationId, const WaveServiceId &eventSourceServiceId, const UI32 &eventOperationCode);
        WaveObjectManager *getWaveObjectManagerForWaveMessageId                 (UI32 prismMessageId);
        WaveObjectManager *getWaveObjectManagerForManagedClass                   (const string &managedClass);
        WaveServiceId      getWaveServiceId                                      () const;
        bool                hasWaveObjectManagers                                 ();
        void                initializeHoldCounts                                   ();
        void                holdMessages                                           ();
        void                holdHighPriorityMessages                               ();
        void                holdEvents                                             ();
        void                holdFrameworkMessages                                  ();
        void                holdAll                                                ();
        void                unholdMessages                                         ();
        void                unholdHighPriorityMessages                             ();
        void                unholdEvents                                           ();
        void                unholdFrameworkMessages                                ();
        void                unholdAll                                              ();
        UI32                getNumberOfPendingTimerExpirationMessages              ();
        UI32                getNumberOfPendingNormalMessages                       ();
        UI32                getNumberOfPendingHighPriorityMessages                 ();

        void                emptyIncomingMessageQueuesForDisable                   (vector<WaveMessage *> &incomingMessages);

        void                setCpuAffinity                                         (const vector<UI32> &cpuAffinityVector);

        void                requestForThreadTermination                            ();

    protected :
                                  WaveThread            (WaveServiceId id, const string &serviceName, const UI32 &stackSize = 0, const vector<UI32> *pCpuAffinityVector = NULL);
                                  WaveThread            (WaveServiceId id, WaveObjectManager *pWaveObjectManager, const string &serviceName, const UI32 &stackSize = 0, const vector<UI32> *pCpuAffinityVector = NULL);

        virtual                   ~WaveThread           ();
        virtual WaveThreadStatus  start                  ();
        virtual WaveThreadStatus  consumePendingMessages ();
                void              addWaveObjectManager   (WaveObjectManager *pWaveObjectManager);

    public :

        static void               getListOfServiceIds                     (vector<WaveServiceId> &serviceIds);
        static WaveThread       *getWaveThreadForServiceId              (WaveServiceId id);
        static vector<UI32>       getCpuAffinityVectorForServiceId        (WaveServiceId id);
        static WaveThreadId      getSelf                                 ();
        static string             getPrismServiceNameForServiceId         (const WaveServiceId &id);
        static WaveServiceId     getWaveServiceIdForServiceName         (const string &prismServiceName);
        static WaveThread       *getWaveThreadForMessageRemoteTransport ();
        static WaveThread       *getWaveThreadForMessageHaPeerTransport ();
        static WaveThreadStatus   joinAllThreads                          ();

               vector<UI32>       getCpuAffinityVector                    () const;

        static WaveObjectManager *getWaveObjectManagerForCurrentThread    ();
        static WaveServiceId     getWaveServiceIdForCurrentThread       ();


    // Now the member variables

    private :
               WaveServiceId                          m_waveServiceId;

               WaveMessageQueue<WaveMessage>         m_messages;
               WaveMessageQueue<WaveMessage>         m_messageResponses;
               WaveMessageQueue<WaveMessage>         m_highPriorityMessages;
               WaveMessageQueue<WaveMessage>         m_highPriorityMessageResponses;
               WaveMessageQueue<WaveMessage>         m_events;
               WaveMessageQueue<WaveMessage>         m_timerExpirations;
               WaveMessageQueue<WaveMessage>         m_timerExpirationResponses;
               WaveMessageQueue<WaveMessage>         m_frameworkMessages;
               WaveMessageQueue<WaveMessage>         m_frameworkMessageResponses;
               WaveMessageQueue<WaveMessage>         m_frameworkResumeMessages;

               PrismMutex                              m_gateKeeper;
               PrismMutex                              m_wakeupCaller;
               PrismCondition                          m_wakeupCondition;

               PrismMutex                              m_messagesMutex;
               UI32                                    m_messagesHoldCount;
               PrismMutex                              m_highPriorityMessagesMutex;
               UI32                                    m_highPriorityMessagesHoldCount;
               PrismMutex                              m_eventsMutex;
               UI32                                    m_eventsHoldCount;
               PrismMutex                              m_frameworkMessagesMutex;
               UI32                                    m_frameworkMessagesHoldCount;
               PrismMutex                              m_frameworkResumeMessagesMutex;
               UI32                                    m_frameworkResumeMessagesHoldCount;

               vector<WaveObjectManager *>             m_pWaveObjectManagers;

               vector<UI32>                            m_cpuAffinityVector;

        static map<WaveThreadId, WaveObjectManager *> m_prismThreadIdToWaveObjectManagerMap;
        static PrismMutex                              m_prismThreadIdToWaveObjectManagerMapMutex;

               bool                                    m_terminateThread;

    protected :
    public :

        friend class WaveObjectManager;
        friend class PrismFrameworkObjectManager;
        friend class TimerWorker;
        friend class WaveMessageFactory;
        friend class WaveManagedObjectFactory;
};

}

#endif //PRISMTHREAD_H
