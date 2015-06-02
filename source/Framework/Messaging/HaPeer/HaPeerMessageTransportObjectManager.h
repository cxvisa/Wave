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

class PrismThread;

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
                       WaveMessageStatus   addMessage                          (PrismMessage *pPrismMessage);
                       PrismMessage       *findMessage                         (UI32 prismMessageId);
                       PrismMessage       *removeMessage                       (UI32 prismMessageId);
                       void                getPendingMessagesForRemoteLocation (LocationId locationId, vector<PrismMessage *> &messagesVector);

            // Now the data members

            private :
                map<UI32, PrismMessage *> m_messagesMap;
                PrismMutex                m_accessMutex;

            protected :
            public:
        };

                            HaPeerMessageTransportObjectManager ();

        void                initialize                                 (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        void                listenForEvents                            (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        void                haPeerMessageTransportHandler              (PrismMessage *pPrismMessage);
        void                lockAccess                                 ();
        void                unlockAccess                               ();
        void                lockAccess1                                ();
        void                unlockAccess1                              ();
        WaveMessageStatus   sendToBeUsedByReceiverThreads              (PrismMessage *pPrismMessage);
        void                callbackForSendUsedByReceiverThreads       (FrameworkStatus frameworkStatus, PrismMessage *pPrismMessage, void *pContext);
        PrismMessage       *getPendingMessage                          (const UI32 &messageId);
        void                replyToBeUsedByReceiverThreads             (PrismMessage *pPrismMessage);
        void                replyToBeUsedByReceiverThreads             (UI32 prismMessageId);
        void                getPendingMessagesForRemoteLocation        (LocationId locationId, vector<PrismMessage *> &messagesVector);
        void                replyToRemoteMessagesPendingOnLocation     (LocationId locationId, ResourceId completionStatus);

        void                haPeerEventTransportHandler                (PrismEvent *pPrismEvent);

    protected :
    public :
        virtual                                            ~HaPeerMessageTransportObjectManager ();
        static  HaPeerMessageTransportObjectManager *getInstance                                ();
        static  PrismServiceId                              getPrismServiceId                          ();

        static  PrismThread                                *getPrismThread                             ();

    // Now the data members

    private :
        MessageMap m_remoteMessagesMap;
        PrismMutex m_accessMutexForReceiverThreads;
        PrismMutex m_accessMutexForMessagesMap;

    protected :
    public :
        friend class HaPeerMessageReceiverThread;
        friend class PrismFrameworkObjectManager;
        friend class PrismFrameworkObjectManagerHaSyncWorker;
};

}

#endif // HAPEERMESSAGETRANSPORTOBJECTMANAGER_H
