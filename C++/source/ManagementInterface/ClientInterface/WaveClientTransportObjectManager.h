/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVECLIENTTRANSPORTOBJECTMANAGER_H
#define WAVECLIENTTRANSPORTOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"
#include "ManagementInterface/ClientInterface/WaveManagementServerMap.h"

namespace WaveNs
{

class ManagementInterfaceMessage;
class WaveManagementServer;

class WaveClientTransportObjectManager : public WaveLocalObjectManager
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
                ManagementInterfaceMessage *findMessage                 (UI32 waveMessageId);
                ManagementInterfaceMessage *removeMessage               (UI32 waveMessageId);
                void                        getPendingMessagesForServer (const UI32 &serverId, vector<ManagementInterfaceMessage *> &messagesVector);

            // Now the data members

            private :
                map<UI32, ManagementInterfaceMessage *> m_messagesMap;
                WaveMutex                              m_accessMutex;

            protected :
            public:
        };

                                    WaveClientTransportObjectManager                ();
        void                        managementInterfaceMessageHandler               (ManagementInterfaceMessage *pManagementInterfaceMessage);
        void                        managementInterfaceMessagePostToServerStep      (WaveLinearSequencerContext *pWaveLinearSequencerContext);

        void                        lockAccess                                      ();
        void                        unlockAccess                                    ();
        void                        lockAccess1                                     ();
        void                        unlockAccess1                                   ();
        void                        lockAccessForServerIdConnectionStatus           ();
        void                        unlockAccessForServerIdConnectionStatus         ();

        WaveMessageStatus           sendToBeUsedByReceiverThreads                   (ManagementInterfaceMessage *pManagementInterfaceMessage);
        void                        callbackForSendUsedByReceiverThreads            (FrameworkStatus frameworkStatus, ManagementInterfaceMessage *pManagementInterfaceMessage, void *pContext);
        ManagementInterfaceMessage *getPendingMessage                               (const UI32 &messageId);
        void                        replyToBeUsedByReceiverThreads                  (ManagementInterfaceMessage *pManagementInterfaceMessage);
        void                        replyToBeUsedByReceiverThreads                  (UI32 waveMessageId);
        void                        getPendingMessagesForServer                     (const UI32 &serverId, vector<ManagementInterfaceMessage *> &messagesVector);
        void                        replyToRemoteMessagesPendingForServer           (const UI32 &serverId, ResourceId completionStatus);

        ResourceId                  connectToNewManagementInterfaceServer           (const string &waveClientName, const string &waveClientNameWithoutExtension, const string &serverIpAddress, const SI32 &serverPort, UI32 &serverId);
        WaveManagementServer       *getServer                                       (const string &serverIpAddress, const SI32 &serverPort);
        UI32                        getServerId                                     (const string &serverIpAddress, const SI32 &serverPort);
        UI32                        getServerIdIfKnown                              (const string &serverIpAddress, const SI32 &serverPort);
        UI32                        getServerIdIfKnownForUniqueServerIdentifier     (const string &serverIpAddress, const SI32 &serverPort, const UI32 &uniqueServerIdentifierFromServerPerspective);
        void                        addServiceCache                                 (const UI32 &serverId, const vector<string> &serviceNames, const vector<UI32> &serviceIds);
        ResourceId                  postToServer                                    (ManagementInterfaceMessage *pManagementInterfaceMessage);


        WaveServiceId              getWaveServiceIdForServiceName                 (const UI32 &serverId, const string &serviceName);
        string                      getWaveServiceNameForServiceId                 (const UI32 &serverId, const WaveServiceId &serviceId);
        void                        addServerId                                     (const UI32 &serverId);
        void                        removeServerId                                  (const UI32 &serverId);
        bool                        validateIfInTheMiddleOfConnectingToServer       (const UI32 &serverId);

    protected :
    public :
        virtual                                  ~WaveClientTransportObjectManager  ();

        static  WaveClientTransportObjectManager *getInstance                       ();
        static  WaveServiceId                    getWaveServiceId                 ();
        void                                      disconnectFromServer              (const UI32 &serverId, const bool removeFromCache = true);
        void                                      disconnectFromServer              (const string &serverIpAddress, const SI32 &serverPort);
        void                                      replyToPendingMessagesForServer   (const string &serverIpAddress, const SI32 &serverPort);

        void                                      updateMessageVersionAndSerializationTypeForServer    (const string &serverIpAddress, const SI32 &serverPort, const string &version);

    // Now the Data Members

    private :
        MessageMap              m_remoteMessagesMap;
        WaveMutex              m_accessMutexForReceiverThreads;
        WaveMutex              m_accessMutexForMessagesMap;
        WaveMutex              m_accessServerIdConnectionStatus;

        set<UI32>               m_serverIdSet;                     // If there is entry in this set, it means client is in middle of connecting to server.
        WaveManagementServerMap m_serversMap;

    protected :
    public :

    friend class WaveClientReceiverThread;
    friend class WaveClientSynchronousConnection;
};

}

#endif // WAVECLIENTTRANSPORTOBJECTMANAGER_H
