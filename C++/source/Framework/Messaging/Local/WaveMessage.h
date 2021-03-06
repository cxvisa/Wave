/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMESSAGE_H
#define WAVEMESSAGE_H

#include "Framework/Types/Types.h"
#include <map>
#include <vector>
#include "Framework/ObjectModel/SerializableObject.h"
#include "Framework/ObjectModel/WaveClientSessionContext.h"
#include "Framework/MultiThreading/WavePosixThread.h"

using namespace std;

namespace WaveNs
{

template<class T> class WaveMessageQueue;

class WaveMutex;
class WaveCondition;
class WaveSendToClusterContext;

class WaveMessage : virtual public SerializableObject
{
    private :
        class WaveMessageBuffer
        {
            private :
            protected :
            public :
                                    WaveMessageBuffer (UI32 size, const void *pBuffer, bool ownedByMesage = false);
                                    WaveMessageBuffer (const WaveMessageBuffer &waveMessagebuffer);
                                   ~WaveMessageBuffer ();
                WaveMessageBuffer &operator =         (const WaveMessageBuffer &waveMessageBuffer);

                void                destroy            ();
                UI32                getSize            () const;
                void               *getPBuffer         () const;
                void                setPBuffer         (void *pBuffer);
                void                invalidateBuffer   ();

            // Now the data members

            private :
                UI32  m_size;
                void *m_pBuffer;

            protected :
            public :
        };

        void            setIsOneWayMessage           (bool isOneWayMessage);
        bool            getIsSynchronousMessage      () const;
        void            setIsSynchronousMessage      (bool isSynchronousMessage);
        WaveMutex     *getPSynchronizingMutex       () const;
        void            setPSynchronizingMutex       (WaveMutex *pWaveMutex);
        WaveCondition *getPSynchronizingCondition   () const;
        void            setPSynchronizingCondition   (WaveCondition *pWaveCondition);
        WaveThreadId   getWaveMessageCreatorThreadId () const;

    protected :
                              WaveMessage                    (WaveServiceId serviceCode, UI32 operationCode);
                              WaveMessage                    (const WaveMessage &waveMessage);
        virtual void          setupAttributesForSerialization ();
        virtual void          setupAttributesForSerializationInAttributeOrderFormat ();
                void          setType                         (WaveMessageType type);
        virtual void          setServiceCode                  (const WaveServiceId &serviceCode);

                void          copyBuffersFrom                 (const WaveMessage &waveMessage);

                void          setMessageId                    (const UI32 &messageId);
                void          setSenderServiceCode            (const WaveServiceId &senderServiceCode);
                void                        setIsMessageSupportedWhenServiceIsPaused    (bool isMessageSupportedWhenServiceIsPaused);

    public :
        virtual                          ~WaveMessage                             ();
                WaveMessage             &operator =                               (const WaveMessage &waveMessage);
                WaveMessageType           getType                                  () const;
                UI32                      getMessageId                             () const;
                UI32                      getMessageIdAtOriginatingLocation        () const;
                void                      setMessageIdAtOriginatingLocation        (const UI32 &messageIdAtOriginatingLocation);
                UI32                      getOriginalMessageId                     () const;
                void                      setOriginalMessageId                     (const UI32 &originalMessageId);
                WaveServiceId            getServiceCode                           () const;
                UI32                      getOperationCode                         () const;
                WaveServiceId            getSenderServiceCode                     () const;
                LocationId                getSenderLocationId                      () const;
                void                      setSenderLocationId                      (const LocationId &locationId);
                LocationId                getReceiverLocationId                    () const;
                bool                      getIsLastReply                           () const;
                void                      setIsLastReply                           (bool isLastReply);
                ResourceId                getCompletionStatus                      () const;
                void                      setCompletionStatus                      (const ResourceId completionStatus);
                WaveMessagePriority       getPriority                              () const;
                void                      setPriority                              (WaveMessagePriority priority);
                bool                      getIsOneWayMessage                       () const;

                UI32                      getNumberOfBuffers                       () const;
                void                      getBufferTags                            (vector<UI32> &bufferTagsVector) const;

        virtual WaveMessageStatus         addBuffer                                (UI32 tag, UI32 size, const void *pBuffer, bool bufferWillBeOwnedByMessage = false);
        virtual void                     *findBuffer                               (UI32 tag, UI32 &size) const;
        virtual void                     *transferBufferToUser                     (UI32 tag, UI32 &size);
        virtual WaveMessageStatus         removeBuffer                             (UI32 tag);
        virtual void                      copyFromRemoteResponse                   (WaveMessage *pRemoteWaveMessageResponse);

                void                      setDropReplyAcrossLocations              (const bool &dropReplyAcrossLocations);
                bool                      getDropReplyAcrossLocations              () const;
                void                      removeAllBuffers                         ();
                void                      transferAllBuffers                       (WaveMessage *pWaveMessage);

        static  WaveMessageType           getType                                  (const string &serializedData, const UI8 serializationType = SERIALIZE_WITH_ATTRIBUTE_NAME); // const string& messageVersion = "");
        static  UI32                      getMessageIdAtOriginatingLocation        (const string &serializedData, const UI8 serializationType = SERIALIZE_WITH_ATTRIBUTE_NAME); // const string& messageVersion = "");
        static  UI32                      getWaveClientMessageId                   (const string &serializedData, const UI8 serializationType = SERIALIZE_WITH_ATTRIBUTE_NAME); // const string& messageVersion = "");
        static  UI32                      getMessageCompletionStatus               (const string &serializedData, const UI8 serializationType = SERIALIZE_WITH_ATTRIBUTE_NAME); // const string& messageVersion = "");
        static  bool                      getIsLastReply                           (const string &serializedData, const UI8 serializationType = SERIALIZE_WITH_ATTRIBUTE_NAME); // const string& messageVersion = "");     

        static  WaveMessage             *createAndLoadFromSerializedData2         (const string &serializedData, const WaveServiceId &assumedServiceCode = 0, const UI8 serializationType = SERIALIZE_WITH_ATTRIBUTE_NAME); // const string& targetMessageVersion = "");
        static  WaveMessage             *createAndLoadFromSerializedData2         (const UI8 *pData, const UI32 dataSize);

                void                      setWaveClientOriginatingLocationId       (const LocationId &waveClientOriginatingLocationId);
                LocationId                getWaveClientOriginatingLocationId       () const;
                void                      setWaveNativeClientId                    (const UI32 &waveNativeClientId);
                UI32                      getWaveNativeClientId                    () const;
                void                      setWaveUserClientId                      (const UI32 &waveUserClientId);
                UI32                      getWaveUserClientId                      () const;
                void                      setWaveClientMessageId                   (const UI32 &waveClientMessageId);
                UI32                      getWaveClientMessageId                   () const;

                WaveClientSessionContext  getWaveClientSessionContext              () const;

        virtual WaveMessage             *clone                                    ();
                string                    getMessageString                         ();
                void                      setMessageString                         (string errorString);
                UI32                      getTransactionCounter                    () const;
                void                      setTransactionCounter                    (const UI32 transactionCounter);
                string                    getNestedSql                             () const;
                void                      setNestedSql                             (const string &nestedSql);
                void                      appendNestedSql                          (const string &nestedSql);
                bool                      getIsConfigurationChanged                 () const;
                void                      setIsConfigurationChanged                 (const bool &isConfigurationChanged);
                bool                      getIsConfigurationFlagSetByUser          () const;
                bool                      getIsConfigurationTimeChanged             () const;
                void                      setIsConfigurationTimeChanged             (const bool &isConfigurationTimeChanged);
                void                      setSurrogatingForLocationId              (LocationId disconnectedLocation);
                LocationId                getSurrogatingForLocationId              () const;
                void                      setNeedSurrogateSupportFlag              (bool needSurrogateSupport);
                bool                      getNeedSurrogateSupportFlag              () const;
                void                      setIsMessageBeingSurrogatedFlag          (bool isMessageBeingSurrogated);
                bool                      getIsMessageBeingSurrogatedFlag          () const;

                void                      addStatusPropagation                     (ResourceId statusResourceId, const string &localizedStatus);
                void                      addStatusPropagation                     (ResourceId statusResourceId, const string &localizedStatus, LocationId locationId);
                void                      addClusterStatusPropagation              (WaveSendToClusterContext *pWaveSendToClusterContext, ResourceId overAllCompletionStatus);
                bool                      getStatusPropagationByLocationId         (ResourceId &statusResourceId, string &localizedStatus, LocationId locationId);
                bool                      getAllStatusPropagation                  (vector<ResourceId> &statusResourceIds, vector<string> &localizedStatus, vector<LocationId> &locationIds);
                void                      clearStatusPropagation                   ();
                UI32                      getNumberOfStatusPropagation             () const;
      virtual   void                      updateForCompletionStatusDuringSurrogacy ();

                bool                      getIsMessageSupportedWhenServiceIsPaused () const;

                void                      addXPathStringsVectorForTimestampUpdate  (const vector<string> &xPathStringsVectorForTimestampUpdate);
                void                      addXPathStringForTimestampUpdate         (const string &xPathString);
                vector<string>            getXPathStringsVectorForTimestampUpdate  () const;

               // Multi Partition.
                void                      setPartitionName                          (const string &partitionName);
                string                    getPartitionName                          (void) const ;
                void                      setPartitionLocationIdForPropagation      (const LocationId &partitionLocationIdForPropagation);
                LocationId                getPartitionLocationIdForPropagation      () const;
                void                      setIsPartitionContextPropagated           (const bool &isPartitionContextPropagated);
                bool                      getIsPartitionContextPropagated           () const;

                void                      setIsAConfigurationIntent                (bool isAConfigurationIntent);
                bool                      getIsAConfigurationIntent                () const;

                void                      setIsConfigurationIntentStored           (bool isConfigurationIntentStored);
                bool                      getIsConfigurationIntentStored           () const;

                void                      setIsALastConfigReplay                   (bool isALastConfigReplay);
                bool                      getIsALastConfigReplay                   () const;

                vector<string>            getlocalizedCompletionStatusForStatusPropagationVector () const;
                vector<ResourceId>        getcompletionStatusForStatusPropagationVector () const;
                vector<LocationId>        getlocationsForStatusPropagationVector () const;

                void                      setlocalizedCompletionStatusForStatusPropagationVector (const vector<string> localizedCompletionStatusForStatusPropagation);
                void                      setcompletionStatusForStatusPropagationVector          (const vector<ResourceId> completionStatusForStatusPropagation);
                void                      setlocationsForStatusPropagationVector                 (const vector<LocationId> locationsForStatusPropagation);

                void                      setTimeOutInMilliSeconds                               (const UI32 timeOutInMilliSeconds);  
                UI32                      getTimeOutInMilliSeconds                               () const;

                bool                      getIsPartitionNameSetByUser                            () const;

                bool                      checkToDisconnectNodeFromLocationAfterReply            () const ;
                void                      setDisconnectFromLocationAfterReply                    (const bool &disconnectFlag);

                bool                      checkToRemoveNodeFromKnownLocationAfterReply           () const;
                void                      setRemoveNodeFromKnownLocationAfterReply               (const bool &removeLocation);
            
                bool                      checkToSendForOneWayCommunication                      () const;
                void                      setToAllowSendForOneWayCommunication                   (const bool &allowSend);

    // Now the data members

    private :
               ResourceId                       m_type; // WaveMessageType
               ResourceId                       m_priority; // WaveMessagePriority
               WaveServiceId                   m_serviceCode;
               UI32                             m_operationCode;
               UI32                             m_waveClientMessageId;
               UI32                             m_messageId;
               UI32                             m_messageIdAtOriginatingLocation;
               WaveServiceId                   m_senderServiceCode;
               LocationId                       m_senderLocationId;
               LocationId                       m_receiverLocationId;
               bool                             m_isOneWayMessage;
               bool                             m_isSynchronousMessage;
               WaveMutex                      *m_pSynchronizingMutex;
               WaveCondition                  *m_pSynchronizingCondition;
               bool                             m_isLastReply;
               bool                             m_isACopy;
               UI32                             m_originalMessageId;
               ResourceId                       m_completionStatus;
               LocationId                       m_waveClientOriginatingLocationId;
               UI32                             m_waveNativeClientId;
               UI32                             m_waveUserClientId;
               map<UI32, WaveMessageBuffer *>  m_buffers;
               bool                             m_dropReplyAcrossLocations;
               string                           m_messageString;
               bool                             m_isConfigurationChanged;
               bool                             m_isConfigurationFlagSetByUser;
               string                           m_nestedSql;
               UI32                             m_transactionCounter;
               WaveThreadId                    m_waveMessageCreatorThreadId;
               LocationId                       m_surrogatingForLocationId;
               bool                             m_needSurrogateSupportFlag ;
               bool                             m_isMessageBeingSurrogatedFlag;

               vector<LocationId>               m_locationsForStatusPropagation;
               vector<ResourceId>               m_completionStatusForStatusPropagation;
               vector<string>                   m_localizedCompletionStatusForStatusPropagation;
               bool                             m_isMessageSupportedWhenServiceIsPaused;

               vector<string>                   m_xPathStringsVectorForTimestampUpdate;

               // Multi Partition.
               string                           m_partitionName;
               LocationId                       m_partitionLocationIdForPropagation;
               bool                             m_isPartitionContextPropagated;
               bool                             m_isPartitionNameSetByUser; // Not serialized.
                                                                            // Only to prevent copy of partitionName from m_pInputMessage during propagation.

               bool                             m_isConfigurationTimeChanged;
    
               bool                             m_isAConfigurationIntent;
               bool                             m_isConfigurationIntentStored;
               bool                             m_isALastConfigReplay;
               UI32                             m_timeOutInMilliSeconds;
               bool                             m_disconnectFromNodeAfterReply;
               bool                             m_removeNodeFromKnownLocationAfterReply;
               bool                             m_sendForOneWayConnection;

    protected :
    public :

    friend class WaveObjectManager;
    friend class WaveFrameworkObjectManager;
    friend class WaveThread;
    friend class RegressionTestObjectManager; // Delete this line as soon as possible.  Using it for testing in the initial phases ...
    friend class WaveClientTransportObjectManager;
    friend class WaveClientSynchronousConnection;
    friend class ManagementInterfaceObjectManager;
    friend class InterLocationMessageTransportObjectManager;
    friend class InterLocationMessageReceiverThread;
    friend class WaveClientReceiverThread;
    friend class WaveManagementClient;
    friend class WaveUserInterfaceObjectManager;
    friend class WaveMessagePayloadBase;
    friend class ManagementInterfaceReceiverThread;
    friend class ManagementInterfaceMessage;
    friend class DatabaseObjectManagerExecuteQueryMessage;
    friend class DatabaseObjectManagerExecuteQueryMessageForCount;
    friend class HaPeerMessageTransportObjectManager;
    friend class HaPeerMessageReceiverThread;
};

}

#endif //WAVEMESSAGE_H
