/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 ***************************************************************************/

#ifndef WAVEFRAMEWORKMESSAGES_H
#define WAVEFRAMEWORKMESSAGES_H

#include "Framework/Messaging/Local/WaveMessage.h"
#include "ManagementInterface/ManagementInterfaceMessage.h"
#include "Framework/ObjectModel/WaveElement.h"
#include "Framework/ObjectModel/ObjectId.h"
#include "Framework/Core/WaveFrameworkObjectManagerInitializeWorker.h"

#include <vector>
#include <string>

using namespace std;

namespace WaveNs
{

class WaveBrokerPublishMessage;

class WaveInitializeObjectManagerMessage : public WaveMessage
{
    private :
    protected :
    public :
                       WaveInitializeObjectManagerMessage (WaveServiceId id, const WaveBootReason &reason);

        WaveBootReason getReason                           () const;

    // Now the data members

    private :
        WaveBootReason m_reason;

    protected :
    public :
};

class WaveInstallObjectManagerMessage : public WaveMessage
{
    private :
    protected :
    public :
                       WaveInstallObjectManagerMessage (WaveServiceId id, const WaveBootReason &reason);

        WaveBootReason getReason                        () const;

    // Now the data members

    private :
        WaveBootReason m_reason;

    protected :
    public :
};

class WaveEnableObjectManagerMessage : public WaveMessage
{
    private :
    protected :
    public :
                       WaveEnableObjectManagerMessage (WaveServiceId id, const WaveBootReason &reason);
        WaveBootReason getReason                       () const;

    // Now the data members

    private :
        WaveBootReason m_reason;

    protected :
    public :
};

class WaveUpgradeObjectManagerMessage : public WaveMessage
{
    private :
    protected :
    public :
                       WaveUpgradeObjectManagerMessage (WaveServiceId id, const WaveBootReason &reason);
        WaveBootReason getReason                        () const;

    // Now the data members

    private :
        WaveBootReason m_reason;

    protected :
    public :
};

class WaveBootObjectManagerMessage : public WaveMessage
{
    private :
    protected :
    public :
                       WaveBootObjectManagerMessage (WaveServiceId id, const WaveBootReason &reason, const bool &rollBackFlag = false);
        WaveBootReason getReason                     () const;
        bool           getRollBackFlag               () const;
    // Now the data members

    private :
        WaveBootReason m_reason;
        bool           m_rollBackFlag;
    protected :
    public :
};

class WaveHaInstallObjectManagerMessage : public WaveMessage
{
    private :
    protected :
    public :
                       WaveHaInstallObjectManagerMessage (WaveServiceId id, const WaveBootReason &reason);

        WaveBootReason getReason                        () const;
    // Now the data members
    private :
        WaveBootReason m_reason;

    protected :
    public :
};

class WaveHaBootObjectManagerMessage : public WaveMessage
{
    private :
    protected :
    public :
                       WaveHaBootObjectManagerMessage (WaveServiceId id, const WaveBootReason &reason);
        WaveBootReason getReason                     () const;
    // Now the data members
    private :
        WaveBootReason m_reason;
    protected :
    public :
};

class WavePostbootObjectManagerMessage : public WaveMessage
{
    private :
        virtual void setupAttributesForSerialization ();
    protected :
    public :
                       WavePostbootObjectManagerMessage (WaveServiceId id, SI8 passNum, string passName, UI32 slotNum, UI32 recoveryType);
        SI8            getPassNum                    () const;
        string         getPassName                   () const;
        UI32           getSlotNum                    () const;
        UI32           getRecoveryType               () const;
    // Now the data members
    private :
        SI8            m_passNum;
        string         m_passName;
        UI32           m_slotNum;
        UI32           m_recoveryType;
    protected :
    public :
};

class WaveShutdownObjectManagerMessage : public WaveMessage
{
    private :
    protected :
    public :
        WaveShutdownObjectManagerMessage (WaveServiceId id);

    // Now the data members

    private :
    protected :
    public :
};

class WaveDisableObjectManagerMessage : public WaveMessage
{
    private :
    protected :
    public :
        WaveDisableObjectManagerMessage (WaveServiceId id);

    // Now the data members

    private :
    protected :
    public :
};

class WaveUninstallObjectManagerMessage : public WaveMessage
{
    private :
    protected :
    public :
        WaveUninstallObjectManagerMessage (WaveServiceId id);

    // Now the data members

    private :
    protected :
    public :
};

class WaveUninitializeObjectManagerMessage : public WaveMessage
{
    private :
    protected :
    public :
        WaveUninitializeObjectManagerMessage (WaveServiceId id);

    // Now the data members

    private :
    protected :
    public :
};

class WaveDestructObjectManagerMessage : public WaveMessage
{
    private :
    protected :
    public :
        WaveDestructObjectManagerMessage (WaveServiceId id);

    // Now the data members

    private :
    protected :
    public :
};

class WavePingObjectManagerMessage : public WaveMessage
{
    private :
        WavePingObjectManagerMessage (WaveServiceId id);

    protected :
    public :

    // Now the data members

    private :
    protected :
    public:
};

class WaveTimerExpiredObjectManagerMessage : public WaveMessage
{
    private :
    protected :
    public :
                                               WaveTimerExpiredObjectManagerMessage (WaveServiceId id, TimerHandle m_timerId, WaveTimerExpirationHandler pWaveTimerExpirationCallback, void *pWaveTimerExpirationContext, WaveElement *pWaveTimerSender);
                                               WaveTimerExpiredObjectManagerMessage (const WaveTimerExpiredObjectManagerMessage &waveTimerExpiredObjectManagerMessage);
        WaveTimerExpiredObjectManagerMessage &operator =                            (const WaveTimerExpiredObjectManagerMessage &waveTimerExpiredObjectManagerMessage);
        WaveTimerExpirationHandler            getTimerExpirationCallback            ();
        void                                  *getTimerExpirationContext             ();
        TimerHandle                            getTimerId                            ();
        WaveElement                          *getTimerSender                        ();

    // Now the data members

    private :
        TimerHandle                  m_timerId;
        WaveTimerExpirationHandler  m_pWaveTimerExpirationCallback;
        void                        *m_pWaveTimerExpirationContext;
        WaveElement                *m_pWaveTimerSender;

    protected :
    public :

};

class WaveObjectManagerDatabaseSanityCheckMessage : public WaveMessage
{
    private :
    protected :
    public :
                       WaveObjectManagerDatabaseSanityCheckMessage (WaveServiceId id, const WaveBootReason &bootReason);
        WaveBootReason getBootReason                               () const;

    // Now the data members

    private :
        WaveBootReason  m_bootReason;

    protected :
    public :
};

class WaveObjectManagerCollectValidationDataMessage : public WaveMessage
{
    private :
    protected :
    public :
              WaveObjectManagerCollectValidationDataMessage (WaveServiceId id);
             ~WaveObjectManagerCollectValidationDataMessage ();
        void  setValidationDetails                           (void *const pData, const UI32 &size, bool willBeOwnedByMessage = false);
        void  getValidationDetails                           (void *&pData, UI32 &size);

    // Now the data members

    private :
    protected :
    public:
};

class WaveObjectManagerValidateClusterCreationMessage : public WaveMessage
{
    private :
    protected :
    public :
                WaveObjectManagerValidateClusterCreationMessage (WaveServiceId id);
                ~WaveObjectManagerValidateClusterCreationMessage ();
        void  setValidationDetails                             (void *const pData, const UI32 &size, bool willBeOwnedByMessage = false);
        void  getValidationDetails                             (void *&pData, UI32 &size);
        void  setValidationResults                             (void *const pData, const UI32 &size, bool willBeOwnedByMessage = false);
        void  getValidationResults                             (void *&pData, UI32 &size);

    // Now the data members

    private :
    protected :
    public:
};

class WaveObjectManagerSendValidationResultsMessage : public WaveMessage
{
    private :
    protected :
    public :
              WaveObjectManagerSendValidationResultsMessage (WaveServiceId id);
             ~WaveObjectManagerSendValidationResultsMessage ();
        void  addValidationResults                           (const string &ipAddress, const SI32 &port, void *pValidationResults, const UI32 &validationResultsSize);
        void  getValidationResults                           (const string &ipAddress, const SI32 &port, void *&pValidationResults, UI32 &validationResultsSize);
        UI32  getNumberOfLocationsThatSentValidationResults  ();
        void  getLocationDetailsAtIndex                      (const UI32 &index, string &ipAddress, SI32 &port);

    // Now the data members

    private :
        vector<string> m_ipAddressesVector;
        vector<SI32>   m_portsVector;

    protected :
    public:
};

class WaveObjectManagerHaSyncCollectValidationDataMessage : public WaveMessage
{
    private :
    protected :
    public :
              WaveObjectManagerHaSyncCollectValidationDataMessage (WaveServiceId id);
             ~WaveObjectManagerHaSyncCollectValidationDataMessage ();
        void  setValidationDetails                           (void *const pData, const UI32 &size, bool willBeOwnedByMessage = false);
        void  getValidationDetails                           (void *&pData, UI32 &size);

    // Now the data members

    private :
    protected :
    public:
};

class WaveObjectManagerHaSyncValidateDataMessage : public WaveMessage
{
    private :
    protected :
    public :
                WaveObjectManagerHaSyncValidateDataMessage (WaveServiceId id);
                ~WaveObjectManagerHaSyncValidateDataMessage ();
        void  setValidationDetails                             (void *const pData, const UI32 &size, bool willBeOwnedByMessage = false);
        void  getValidationDetails                             (void *&pData, UI32 &size);
        void  setValidationResults                             (void *const pData, const UI32 &size, bool willBeOwnedByMessage = false);
        void  getValidationResults                             (void *&pData, UI32 &size);

    // Now the data members

    private :
    protected :
    public:
};

class WaveObjectManagerHaSyncSendValidationResultsMessage : public WaveMessage
{
    private :
    protected :
    public :
              WaveObjectManagerHaSyncSendValidationResultsMessage (WaveServiceId id);
             ~WaveObjectManagerHaSyncSendValidationResultsMessage ();
        void  addValidationResults                           (void *pValidationResults, const UI32 &validationResultsSize);
        void  getValidationResults                           (void *&pValidationResults, UI32 &validationResultsSize);

    // Now the data members

    private :

    protected :
    public:
};


class WaveObjectManagerRegisterEventListenerMessage : public WaveMessage
{
    private :
    protected :
    public :
              WaveObjectManagerRegisterEventListenerMessage (WaveServiceId id, const UI32 &operationCodeToListenFor, const WaveServiceId &listenerWaveServiceId, const LocationId &listenerLocationId);
             ~WaveObjectManagerRegisterEventListenerMessage ();

        UI32           getOperationCodeToListenFor           () const;
        void           setOperationCodeToListenFor           (const UI32 &operationCodeToListenFor);
        WaveServiceId getListenerWaveServiceId             () const;
        void           setListenerWaveServiceId             (const WaveServiceId &listenerWaveServiceId);
        LocationId     getListenerLocationId                 () const;
        void           setListenerLocationId                 (const LocationId &listenerLocationId);

    // Now the data members

    private :
        UI32           m_operationCodeToListenFor;
        WaveServiceId m_listenerWaveServiceId;
        LocationId     m_listenerLocationId;

    protected :
    public :
};

class WaveFailoverObjectManagerMessage : public WaveMessage
{
    private :
    protected :
    public :
                                                      WaveFailoverObjectManagerMessage (WaveServiceId id, const FrameworkObjectManagerFailoverReason &failoverReason, const bool isPrincipalChangedWithThisFailover);
        virtual                                      ~WaveFailoverObjectManagerMessage ();

                FrameworkObjectManagerFailoverReason  getFailoverReason                 () const;
                vector<LocationId>                   &getFailedLocationIds              ();
                bool                                  getIsPrincipalChangedWithThisFailover () const;

    // Now the data members

    private :
        FrameworkObjectManagerFailoverReason m_failoverReason;
        vector<LocationId>                   m_failedLocationIds;
        bool                                 m_isPrincipalChangedWithThisFailover;

    protected :
    public :
};

class WavePauseObjectManagerMessage : public WaveMessage
{
    private :
    protected :
    public :
        WavePauseObjectManagerMessage (WaveServiceId id);

    // Now the data members

    private :
    protected :
    public :
};

class WaveResumeObjectManagerMessage : public WaveMessage
{
    private :
    protected :
    public :
        WaveResumeObjectManagerMessage (WaveServiceId id);

    // Now the data members

    private :
    protected :
    public :
};

class WaveSetCpuAffinityObjectManagerMessage : public WaveMessage
{
    private :
    protected :
    public :
                     WaveSetCpuAffinityObjectManagerMessage (WaveServiceId id);

        vector<UI32> getCpuAffinityVector                    () const;
        void         setCpuAffinityVector                    (const vector<UI32> &cpuAffinityVector);

    // Now the data members

    private :
        vector<UI32> m_cpuAffinityVector;

    protected :
    public :
};

class WaveListenForEventsObjectManagerMessage : public WaveMessage
{
    private :
    protected :
    public :
        WaveListenForEventsObjectManagerMessage (WaveServiceId id);

    // Now the data members

    private :
    protected :
    public :
};

class WaveLoadOperationalDataForManagedObjectObjectManagerMessage : public WaveMessage
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
    public :
        WaveLoadOperationalDataForManagedObjectObjectManagerMessage ();
        WaveLoadOperationalDataForManagedObjectObjectManagerMessage (WaveServiceId id, ObjectId objectId, const vector<string> &operationalDataFields);

        ObjectId       getObjectId              () const;
        vector<string> getOperationalDataFields () const;

    // Now the data members

    private :
        ObjectId       m_objectId;
        vector<string> m_operationalDataFields;

    protected :
    public :
};

class WaveHeartbeatFailureObjectManagerMessage : public WaveMessage
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
    public :
        WaveHeartbeatFailureObjectManagerMessage (WaveServiceId id, IpV4Address ipAddress, UI16 portNumber);

        IpV4Address  getIpAddress () const;
		UI16         getPortNumber () const;

	// Now the data members
    private :
		IpV4Address m_ipAddress;
		UI16        m_portNumber;
    protected :
    public :
};

class WaveExternalStateSynchronizationObjectManagerMessage : public WaveMessage
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
    public :
        WaveExternalStateSynchronizationObjectManagerMessage (WaveServiceId id, UI32 fssStageNumber, ResourceId serviceType);

		UI32         getFssStageNumber () const;
		ResourceId   getServiceType() const;

	// Now the data members
    private :
        UI32          m_fssStageNumber;
        ResourceId    m_serviceType;
    protected :
    public :
};

class WaveConfigReplayEndObjectManagerMessage : public WaveMessage
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
    public :
        WaveConfigReplayEndObjectManagerMessage (WaveServiceId id);

	// Now the data members
    private :
    protected :
    public :
};

class WaveFileReplayEndObjectManagerMessage : public WaveMessage
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
    public :
        WaveFileReplayEndObjectManagerMessage (WaveServiceId id);

	// Now the data members
    private :
    protected :
    public :
};

class WaveSlotFailoverObjectManagerMessage : public WaveMessage
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
    public :
        WaveSlotFailoverObjectManagerMessage (WaveServiceId id, UI32 slotNumber);
        UI32    getSlotNumber () const;


	// Now the data members
    private :
        UI32          m_slotNumber;
    protected :
    public :
};

class WaveMultiPartitionCleanupObjectManagerMessage : public WaveMessage
{
    private :
        virtual     void    setupAttributesForSerialization                 ();

    protected :
    public :
        WaveMultiPartitionCleanupObjectManagerMessage    (WaveServiceId id, string &partitionName, ObjectId &ownerPartitionManagedObjectId);
        string      getPartitionName                                   () const;
        ObjectId    getOwnerPartitionManagedObjectId                   () const ;

        bool        getIsPartialCleanup                                () const;

        void        setPartialCleanupTag                               (const ResourceId &partialCleanupTag);
        ResourceId  getPartialCleanupTag                               ();

        // Now the data members
    private :
        string        m_partitionName;
        ObjectId      m_ownerPartitionManagedObjectId;
        bool          m_isPartialCleanup;
        ResourceId    m_partialCleanupTag;


    protected :
    public :
};

class WaveObjectManagerBackendSyncUpMessage : public WaveMessage
{
    private :
    protected :
    public :
              WaveObjectManagerBackendSyncUpMessage (WaveServiceId id);


    // Now the data members

    private :

    protected :
    public :
};


class WaveObjectManagerMessageHistoryDumpMessage : public WaveMessage
{
    private :
        virtual void                   setupAttributesForSerialization ();
    protected :
    public :
                                       WaveObjectManagerMessageHistoryDumpMessage (WaveServiceId id);
        virtual                       ~WaveObjectManagerMessageHistoryDumpMessage ();

                vector<string>        &getMessageHistoryDumpStringVector          ();
                void                   setMessageHistoryDumpStringVector          (vector<string> &messageHistoryDumpStringVector);

    // Now the data members

    private :
        vector<string>                 m_messageHistoryDumpStringVector;

    protected :
    public :
};

class WaveObjectManagerMessageHistoryConfigMessage : public WaveMessage
{
    private :
        virtual void                    setupAttributesForSerialization ();

    protected :
    public :
                                        WaveObjectManagerMessageHistoryConfigMessage (WaveServiceId id);
        virtual                        ~WaveObjectManagerMessageHistoryConfigMessage ();

                bool                    getMessageHistoryState                       () const;
                void                    setMessageHistoryState                       (bool messageHistoryState);
                UI32                    getMessageHistoryMaxSize                     () const;
                void                    setMessageHistoryMaxSize                     (UI32 messageHistoryMaxSize);

    // Now the data members

    private :
        bool                m_messageHistoryState;
        UI32                m_messageHistoryMaxSize;

    protected :
    public :
};

class WaveObjectManagerUpdateRelationshipMessage : public WaveMessage
{
    private:
    protected:
                void    setupAttributesForSerialization ();
    public:
                        WaveObjectManagerUpdateRelationshipMessage ();
                        WaveObjectManagerUpdateRelationshipMessage (WaveServiceId id);
                        WaveObjectManagerUpdateRelationshipMessage (WaveServiceId id, UI32 operationCode);
        virtual        ~WaveObjectManagerUpdateRelationshipMessage ();

        void            setRelationshipVariables    (const string &parentClassName, const string &childClassName, const string &relationshipName, const ObjectId &parentObjectId, const ObjectId &childObjectId);
        void            getRelationshipVariables    (string &parentClassName, string &childClassName, string &relationshipName, ObjectId &parentObjectId, ObjectId &childObjectId);

        void            setIsAddingRelationship     (const bool &isAddingRelationship);
        bool            getIsAddingRelationship     () const;

    // data member

    private:
                string      m_parentClassName;
                string      m_childClassName;
                string      m_relationshipName;
                ObjectId    m_parentObjectId;
                ObjectId    m_childObjectId;
                bool        m_isAddingRelationship;
};

class WaveObjectManagerUpdateWaveManagedObjectMessage: public WaveMessage
{
    private :
    protected :
        void setupAttributesForSerialization ();

    public :
                                WaveObjectManagerUpdateWaveManagedObjectMessage ();
                                WaveObjectManagerUpdateWaveManagedObjectMessage (WaveServiceId id);
                                WaveObjectManagerUpdateWaveManagedObjectMessage (WaveServiceId id, UI32 operationCode);
        virtual                ~WaveObjectManagerUpdateWaveManagedObjectMessage ();

                ObjectId        getInputWaveManagedObjectId                     () const;
                void            setInputWaveManagedObjectId                     (const ObjectId &waveManagedObjectId);

                ObjectId        getOperateOnWaveManagedObjectId                 () const;
                void            setOperateOnWaveManagedObjectId                 (const ObjectId &waveManagedObjectId);

                vector<UI32>    getAttributeUserTags                            () const;
                void            setAttributeUserTags                            (const vector<UI32> &attributeUserTags);

                vector<string>  getAttributeNames                               () const;
                void            setAttributeNames                               (const vector<string> &attributeNames);

                vector<string>  getAttributeValues                              () const;
                void            setAttributeValues                              (const vector<string> &attributeValues);

                ObjectId        getParentObjectId                               () const;
                void            setParentObjectId                               (const ObjectId &parentObjectId);

                UI32            getChildUserTag                                 () const;
                void            setChildUserTag                                 (const UI32 &childUserTag);

                UI32            getChoiceUserTag                                () const;
                void            setChoiceUserTag                                (const UI32 &choiceUserTag);

                bool            getIsPropagateErrorCodeNeeded                   () const;
                void            setIsPropagateErrorCodeNeeded                   (const bool isErrorCode);

                UI32            getChoiceUserTagNeedToRemove                    () const;
                void            setChoiceUserTagNeedToRemove                    (const UI32 &choiceUserTagNeedToRemove);

                UI32            getWarningResourceId                            () const;
                void            setWarningResourceId                            (const UI32 warningResourceId);

                bool            getConfigReplayInProgressFlag                   () const;
                void            setConfigReplayInProgressFlag                   (const bool isConfigReplayInProgress);
    // Now the data members

    private :
        ObjectId       m_inputWaveManagedObjectId;
        ObjectId       m_operateOnWaveManagedObjectId;
        vector<UI32>   m_attributeUserTags;
        vector<string> m_attributeNames;
        vector<string> m_attributeValues;
        ObjectId       m_parentObjectId;
        UI32           m_childUserTag;
        UI32           m_choiceUserTag;
        bool           m_isErrorCode;
        UI32           m_choiceUserTagNeedToRemove;
        UI32           m_warningResourceId;
        bool           m_isConfigReplayInProgress;

    protected :
    public :
};

class WaveObjectManagerCreateWaveManagedObjectMessage : public WaveObjectManagerUpdateWaveManagedObjectMessage
{
    private :
        void setupAttributesForSerialization ();

    protected:
    public:

                                WaveObjectManagerCreateWaveManagedObjectMessage     ();
                                WaveObjectManagerCreateWaveManagedObjectMessage     (WaveServiceId id);
        virtual                ~WaveObjectManagerCreateWaveManagedObjectMessage     ();

        string                  getManagedObjectClassNameNeedToBeCreated            () const;
        void                    setManagedObjectClassNameNeedToBeCreated            (const string &managedObjectClassName);

        ObjectId                getObjectId                                         () const;
        void                    setObjectId                                         (const ObjectId &objectId);

    // Now the data members
    private:
        string      m_managedObjectClassName;
        ObjectId    m_objectId;
    protected:
    public:

};


class WaveObjectManagerDeleteWaveManagedObjectMessage: public WaveObjectManagerUpdateWaveManagedObjectMessage
{
    private :
    protected :
        void setupAttributesForSerialization ();
    public :
                                WaveObjectManagerDeleteWaveManagedObjectMessage ();
                                WaveObjectManagerDeleteWaveManagedObjectMessage (WaveServiceId id);
                                WaveObjectManagerDeleteWaveManagedObjectMessage (WaveServiceId id, UI32 operationCode);
        virtual                ~WaveObjectManagerDeleteWaveManagedObjectMessage ();

                UI32            getIsMO                                         () const;
                void            setIsMO                                         (const UI32 &isMO);
    // Now the data members

    private :
        UI32           m_isMO;                          // Is the delete operation being done on a MO?

    protected :
    public :
};

class WaveObjectManagerDeleteWaveManagedObjectsMessage: public WaveObjectManagerDeleteWaveManagedObjectMessage
{

    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                                WaveObjectManagerDeleteWaveManagedObjectsMessage ();
                                WaveObjectManagerDeleteWaveManagedObjectsMessage (WaveServiceId id);
        virtual                ~WaveObjectManagerDeleteWaveManagedObjectsMessage ();

              vector<ObjectId>        getManagedObjectsIdVector                        () const;
              void                    setManagedObjectsIdVector                        (const vector<ObjectId> &ManagedObjectIdVector);

              vector<vector<string> > getAttributeNameVectorVector                     () const;
              void                    setAttributeNameVectorVector                     (const vector<vector<string> > &AttributeNameVectorVector);

              vector<vector<UI32> >   getAttributeUserTagVectorVector                  () const;
              void                    setAttributeUserTagVectorVector                  (const vector<vector<UI32> > &AttributeUserTagVectorVector);

    // Now the data members

    private :
            vector<ObjectId>        m_ManagedObjectIdVector;
            vector<vector<string> > m_AttributeNameVectorVector;
            vector<vector<UI32> >   m_AttributeUserTagVectorVector;
    protected :
    public :
};

class WaveZeroizeObjectManagerMessage : public WaveMessage
{
    private :
    protected :
    public :
        WaveZeroizeObjectManagerMessage (WaveServiceId id);

    // Now the data members

    private :
    protected :
    public :
};

class WaveObjectManagerGetDebugInformationMessage : public ManagementInterfaceMessage
{
    private :
                void                setupAttributesForSerialization                 ();
    protected :
    public :
                                    WaveObjectManagerGetDebugInformationMessage     ();
                                    WaveObjectManagerGetDebugInformationMessage     (const string &serviceName);
        virtual                    ~WaveObjectManagerGetDebugInformationMessage     ();

                void                setDebugInformation                             (const string &debugInformation);
                const   string &    getDebugInformation                             () const;

    // Now the data members

    private :
                        string      m_debugInformation;

    protected :
    public :

};

class WaveObjectManagerResetDebugInformationMessage : public ManagementInterfaceMessage
{
    private :
    protected :
    public :
                                    WaveObjectManagerResetDebugInformationMessage   ();
                                    WaveObjectManagerResetDebugInformationMessage   (const string &serviceName);
        virtual                    ~WaveObjectManagerResetDebugInformationMessage   ();

    // Now the data members

    private :
    protected :
    public :

};

class WaveObjectManagerGetDataFromClientMessage : public WaveMessage
{
    private :
                    void            setupAttributesForSerialization                 ();
    protected :
    public :
                                    WaveObjectManagerGetDataFromClientMessage   ();
                                    WaveObjectManagerGetDataFromClientMessage   (WaveServiceId id);
                                    WaveObjectManagerGetDataFromClientMessage   (WaveServiceId id, UI32 commandCode, UI32 commandType, bool sendToClusterRequested = false );
        virtual                    ~WaveObjectManagerGetDataFromClientMessage   ();

                    void            setEnablePaginate               (const bool &enablePaginate);
                    bool            getEnablePaginate               () const;

                    void            setGlobalPluginServiceCode      (const UI32 &globalPluginServiceCode);
                    UI32            getGlobalPluginServiceCode      () const;

                    void            setLocalPluginServiceCode       (const UI32 &localPluginServiceCode);
                    UI32            getLocalPluginServiceCode       () const;

                    void            setClientName                   (const string &clientName);
                    void            getClientName                   (string &client) const;

                    void            setSelectedNodes                (const vector<LocationId> &selectedNodes);
                    void            getSelectedNodes                (vector<LocationId> &selectedNodes) const;

                    void            setCommandCode                  (const UI32 &commandCode);
                    UI32            getCommandCode                  () const ;

                    void            setCommandType                  (const UI32 &commandType);
                    UI32            getCommandType                  () const ;

                    void            setNumberOfRecordsRequested     (const UI32 &numberOfRecordsRequested);
                    UI32            getNumberOfRecordsRequested     () const;

                    void            setNumberOfCommandStrings       (const SI32 numberOfCommandStrings);
                    SI32            getNumberOfCommandStrings       () const;

                    void            setCommandStrings               (const vector<string> &commandStrings);
                    vector<string>  getCommandStrings               () const;

                    void            setSendToClusterRequested       (const bool &sendToClusterRequested );
                    bool            getSendToClusterRequested       () const;

                    void            addToMoreRecordsVector          (const bool &moreRecord);
                    void            getMoreRecordsVector            (vector<bool> &moreRecordsVector) const;

                    void            setNewServiceCode               (const UI32 &serviceCode);
                    void            copyClientDataFromMessage       (WaveMessage *pWaveMessage);
                    void            getDataSentFromAllClients       (vector<LocationId> &selectedNodes, vector<UI32> &clientStatus, vector<void *> &buffers, vector<bool> &moreRecordsVector);

                    void            copyAllBuffersFromMessage       (const WaveMessage *pWaveMessage);

 // Now the data members

    private :
    protected :
    public :
                bool                    m_enablePaginate;
                vector<bool>            m_moreRecordsVector;
                string                  m_clientName;
                UI32                    m_globalPluginServiceCode;
                UI32                    m_localPluginServiceCode;
                vector<LocationId>      m_selectedNodes;
                UI32                    m_commandCode;
                UI32                    m_commandType;
                UI32                    m_numberOfRecordsRequested;
                bool                    m_sendToClusterRequested;
                SI32                    m_numberOfCommandStrings;
                vector<string>          m_commandStrings;
};

class WaveDeliverBrokerPublishMessage : public WaveMessage
{
    private :
    protected :
    public :
                                  WaveDeliverBrokerPublishMessage (WaveServiceId id);
                                 ~WaveDeliverBrokerPublishMessage ();

        WaveBrokerPublishMessage *getPWaveBrokerPublishMessage    ();
        void                      setPWaveBrokerPublishMessage    (WaveBrokerPublishMessage *pWaveBrokerPublishMessage);

    // Now the data members

    private :
        WaveBrokerPublishMessage *m_pWaveBrokerPublishMessage;

    protected :
    public :
};

}

#endif //WAVEFRAMEWORKMESSAGES_H
