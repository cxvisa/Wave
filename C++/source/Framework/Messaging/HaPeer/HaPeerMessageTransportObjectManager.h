/***************************************************************************
 *   Copyright (C) 2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                          *
 ***************************************************************************/

#ifndef HAPEERMESSAGETRANSPORTOBJECTMANAGER_H
#define HAPEERMESSAGETRANSPORTOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"
#include <vector>

namespace WaveNs
{

class WaveThread;

class HaPeerMessageTransportObjectManager : public WaveLocalObjectManager
{
    private :
        class MessageMap
        {
            private :
                void lockAccess ();
                void unlockAccess ();
            protected :
            public :
                                           MessageMap                          ();
                                          ~MessageMap                          ();
                       WaveMessageStatus   addMessage                          (WaveMessage *pWaveMessage);
                       WaveMessage       *findMessage                         (UI32 prismMessageId);
                       WaveMessage       *removeMessage                       (UI32 prismMessageId);
                       void                getPendingMessagesForRemoteLocation (LocationId locationId, vector<WaveMessage *> &messagesVector);

            // Now the data members

            private :
                map<UI32, WaveMessage *> m_messagesMap;
                WaveMutex                m_accessMutex;

            protected :
            public:
        };

                            HaPeerMessageTransportObjectManager ();

        void                initialize                                 (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        void                listenForEvents                            (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        void                haPeerMessageTransportHandler              (WaveMessage *pWaveMessage);
        void                lockAccess                                 ();
        void                unlockAccess                               ();
        void                lockAccess1                                ();
        void                unlockAccess1                              ();
        WaveMessageStatus   sendToBeUsedByReceiverThreads              (WaveMessage *pWaveMessage);
        void                callbackForSendUsedByReceiverThreads       (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, void *pContext);
        WaveMessage       *getPendingMessage                          (const UI32 &messageId);
        void                replyToBeUsedByReceiverThreads             (WaveMessage *pWaveMessage);
        void                replyToBeUsedByReceiverThreads             (UI32 prismMessageId);
        void                getPendingMessagesForRemoteLocation        (LocationId locationId, vector<WaveMessage *> &messagesVector);
        void                replyToRemoteMessagesPendingOnLocation     (LocationId locationId, ResourceId completionStatus);

        void                haPeerEventTransportHandler                (WaveEvent *pWaveEvent);

    protected :
    public :
        virtual                                            ~HaPeerMessageTransportObjectManager ();
        static  HaPeerMessageTransportObjectManager *getInstance                                ();
        static  WaveServiceId                              getWaveServiceId                          ();

        static  WaveThread                                *getWaveThread                             ();

    // Now the data members

    private :
        MessageMap m_remoteMessagesMap;
        WaveMutex m_accessMutexForReceiverThreads;
        WaveMutex m_accessMutexForMessagesMap;

    protected :
    public :
        friend class HaPeerMessageReceiverThread;
        friend class PrismFrameworkObjectManager;
        friend class PrismFrameworkObjectManagerHaSyncWorker;
};

}

#endif // HAPEERMESSAGETRANSPORTOBJECTMANAGER_H
