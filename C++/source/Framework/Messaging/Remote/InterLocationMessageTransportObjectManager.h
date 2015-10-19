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
                       WaveMessageStatus   addMessage                                    (WaveMessage *pWaveMessage, UI32 waveMessageId = 0);
                       WaveMessage       *findMessage                                   (UI32 waveMessageId);
                       WaveMessage       *findMessageWithLock                           (UI32 waveMessageId);
                       WaveMessage       *removeMessage                                 (UI32 waveMessageId);
                       void                getPendingMessagesForRemoteLocationForReplying (LocationId locationId, vector<WaveMessage *> &messagesVector);

            // Now the data members

            private :
                map<UI32, WaveMessage *> m_messagesMap;
                WaveMutex                m_accessMutex;

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
        void                replyToBeUsedByReceiverThreads                  (UI32 waveMessageId);
        void                getPendingMessagesForRemoteLocationForReplying  (LocationId locationId, vector<WaveMessage *> &messagesVector);
        void                replyToRemoteMessagesPendingOnLocation          (LocationId locationId, ResourceId completionStatus);

        void                interLocationEventTransportHandler              (const WaveEvent *&pWaveEvent);

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
        WaveMutex m_accessMutexForReceiverThreads;
        WaveMutex m_accessMutexForMessagesMap;
        WaveMutex m_globalAccessMutexForMulticastMessaging;
    protected :
    public :
        friend class InterLocationMessageReceiverThread;
        friend class WaveFrameworkObjectManager;
};

}

#endif // INTERLOCATIONMESSAGETRANSPORTOBJECTMANAGER_H
