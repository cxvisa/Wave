/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef MANAGEMENTINTERFACEOBJECTMANAGER_H
#define MANAGEMENTINTERFACEOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"
#include "ManagementInterface/WaveManagementClientMap.h"

namespace WaveNs
{

typedef void (*WaveUserGetInstanceFunction)              (vector<SI32> &connectedInstanceVector);

class ManagementInterfaceMessage;
class WaveManagementClient;
class ManagementInterfaceClientListMessage;

class ManagementInterfaceObjectManager : public WaveLocalObjectManager
{
    private :
        class MessageMap
        {
            private :
                void lockAccess ();
                void unlockAccess ();

            protected :
            public :
                                            MessageMap                  ();
                                            ~MessageMap                  ();
                WaveMessageStatus           addMessage                  (ManagementInterfaceMessage *pManagementInterfaceMessage);
                ManagementInterfaceMessage *findMessage                 (UI32 prismMessageId);
                ManagementInterfaceMessage *removeMessage               (UI32 prismMessageId);
                void                        getPendingMessagesForClient (const UI32 &clientId, vector<ManagementInterfaceMessage *> &messagesVector);

            // Now the data members

            private :
                map<UI32, ManagementInterfaceMessage *> m_messagesMap;
                PrismMutex                              m_accessMutex;

            protected :
            public:
        };

                                    ManagementInterfaceObjectManager           ();
        void                        managementInterfaceMessageHandler          (ManagementInterfaceMessage *pManagementInterfaceMessage);
        void                        managementInterfaceMessagePostToClientStep (PrismLinearSequencerContext *pPrismLinearSequencerContext);

        void                        lockAccess                                 ();
        void                        unlockAccess                               ();
        void                        lockAccess1                                ();
        void                        unlockAccess1                              ();
        WaveMessageStatus           sendToBeUsedByReceiverThreads              (ManagementInterfaceMessage *pManagementInterfaceMessage);
        void                        callbackForSendUsedByReceiverThreads       (FrameworkStatus frameworkStatus, ManagementInterfaceMessage *pManagementInterfaceMessage, void *pContext);
        ManagementInterfaceMessage *getPendingMessage                          (const UI32 &messageId);
        ManagementInterfaceMessage *getPendingMessageWithOutRemove             (const UI32 &messageId);
        void                        replyToBeUsedByReceiverThreads             (ManagementInterfaceMessage *pManagementInterfaceMessage);
        void                        replyToBeUsedByReceiverThreads             (UI32 prismMessageId);
        void                        getPendingMessagesForClient                (const UI32 &clientId, vector<ManagementInterfaceMessage *> &messagesVector);
        void                        replyToRemoteMessagesPendingForClient      (const UI32 &clientId, ResourceId completionStatus);

        ResourceId                  connectToNewManagementInterfaceClient      (const string &clientName, const string &clientIpAddress, const SI32 &clientPort, const WaveServiceId &userInterfaceServiceId, const string &serverIpAddressFromClientPerspective, const string &messageVersion, const UI32 &serverUniqueIdentifierFromServerPerspective = 0);
        WaveManagementClient       *getClient                                  (const string &clientIpAddress, const SI32 &clientPort);
        bool                        isAKnownClient                             (const string &ipAddress, const UI32 &port);
        UI32                        getClientId                                (const string &clientIpAddress, const SI32 &clientPort);
        UI32                        getClientId                                (const string &clientName);
        ResourceId                  postToClient                               (ManagementInterfaceMessage *pManagementInterfaceMessage);
        static ResourceId           postToClientWrapper                        (ManagementInterfaceMessage *pManagementInterfaceMessage);

        void                        disconnectFromClient                       (const UI32 &clientId);
        void                        disconnectFromClient                       (const string &clientIpAddress, const SI32 &clientPort);
        void                        sendTimerExpiredCallback                   (TimerHandle timerHandle, void *pContext);
        void                        managementInterfaceClientListHandler       (ManagementInterfaceClientListMessage *pManagementInterfaceClientListMessage);
        virtual     PrismMessage    *createMessageInstance                     (const UI32 &operationCode);
        void                        getClientsInformation                      (PrismLinearSequencerContext *pPrismLinearSequencerContext);    
    
    protected :
    public :
        virtual                                  ~ManagementInterfaceObjectManager ();

        static  ManagementInterfaceObjectManager *getInstance                      ();
        static  WaveServiceId                    getWaveServiceId                ();
                void                        	  disconnectFromClient 		   (const string &clientIpAddress);
        static 	void 				  removeInstanceClient 		   (UI32 argc, vector<string> argv);
        static 	void 			          registerDebugShellEntries 	   ();
                bool                              isAKnownClient                   (const string &clientName);
        static  string                       getServiceName                        ();        
    // Now the data members

    private :
        MessageMap              m_remoteMessagesMap;
        PrismMutex              m_accessMutexForReceiverThreads;
        PrismMutex              m_accessMutexForMessagesMap;

        WaveManagementClientMap m_clientsMap;
        static WaveUserGetInstanceFunction        m_pWaveUserGetInstanceFunction;
    protected :
    public :

    friend class ManagementInterfaceReceiverThread;

};

}

#endif // MANAGEMENTINTERFACEOBJECTMANAGER_H
