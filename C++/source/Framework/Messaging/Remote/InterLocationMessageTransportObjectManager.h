/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef INTERLOCATIONMESSAGETRANSPORTOBJECTMANAGER_H
#define INTERLOCATIONMESSAGETRANSPORTOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"
#include <vector>

namespace WaveNs
{

class WaveThread;
class InterLocationMulticastMessage;

class InterLocationMessageTransportObjectManager : public WaveLocalObjectManager
{
    private :
        class MessageMap
        {
            private :
                void lockAccess ();
                void unlockAccess ();
            protected :
            public :
                                           MessageMap                                    ();
                                          ~MessageMap                                    ();
                       WaveMessageStatus   addMessage                                    (WaveMessage *pWaveMessage, UI32 prismMessageId = 0);
                       WaveMessage       *findMessage                                   (UI32 prismMessageId);
                       WaveMessage       *findMessageWithLock                           (UI32 prismMessageId);
                       WaveMessage       *removeMessage                                 (UI32 prismMessageId);
                       void                getPendingMessagesForRemoteLocationForReplying (LocationId locationId, vector<WaveMessage *> &messagesVector);

            // Now the data members

            private :
                map<UI32, WaveMessage *> m_messagesMap;
                PrismMutex                m_accessMutex;

            protected :
            public:
        };

                            InterLocationMessageTransportObjectManager      ();

        void                initialize                                      (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        void                listenForEvents                                 (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        void                interLocationMessageTransportHandler            (WaveMessage *pWaveMessage);
        void                interLocationMulticastMessageTransportHandler   (InterLocationMulticastMessage *pInterLocationMulticastMessage);

        void                lockAccess                                      ();
        void                unlockAccess                                    ();
        void                lockAccess1                                     ();
        void                unlockAccess1                                   ();
        WaveMessageStatus   sendToBeUsedByReceiverThreads                   (WaveMessage *pWaveMessage);
        void                callbackForSendUsedByReceiverThreads            (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, void *pContext);
        WaveMessage       *getPendingMessage                               (const UI32 &messageId);
        WaveMessage       *getPendingMessageWithoutRemove                  (const UI32 &messageId);
        void                replyToBeUsedByReceiverThreads                  (WaveMessage *pWaveMessage);
        void                replyToBeUsedByReceiverThreads                  (UI32 prismMessageId);
        void                getPendingMessagesForRemoteLocationForReplying  (LocationId locationId, vector<WaveMessage *> &messagesVector);
        void                replyToRemoteMessagesPendingOnLocation          (LocationId locationId, ResourceId completionStatus);

        void                interLocationEventTransportHandler              (const PrismEvent *&pPrismEvent);

        void                lockGlobalAccessMutexForMulticastMessaging      ();
        void                unlockGlobalAccessMutexForMulticastMessaging    ();

    protected :
    public :
        virtual                                            ~InterLocationMessageTransportObjectManager ();
        static  InterLocationMessageTransportObjectManager *getInstance                                ();
        static  WaveServiceId                              getWaveServiceId                          ();

        static  WaveThread                                *getWaveThread                             ();

    // Now the data members

    private :
        MessageMap m_remoteMessagesMap;
        PrismMutex m_accessMutexForReceiverThreads;
        PrismMutex m_accessMutexForMessagesMap;
        PrismMutex m_globalAccessMutexForMulticastMessaging;
    protected :
    public :
        friend class InterLocationMessageReceiverThread;
        friend class PrismFrameworkObjectManager;
};

}

#endif // INTERLOCATIONMESSAGETRANSPORTOBJECTMANAGER_H
