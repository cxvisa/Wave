/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEWORKER_H
#define WAVEWORKER_H

#include "Framework/ObjectModel/WaveElement.h"
#include "Framework/Utils/WaveAsynchronousContext.h"

namespace WaveNs
{

class WaveObjectManager;
class WaveManagedObjectQueryContext;
class WaveManagedObject;
class WaveAsynchronousContextForBootPhases;
class WaveAsynchronousContextForPostbootPhase;
class WaveAsynchronousContextForShutDownPhases;
class WaveAsynchronousContextForExternalStateSynchronization;
class WaveAsynchronousContextForConfigReplayEnd;
class WaveAsynchronousContextForFileReplayEnd;
class WaveAsynchronousContextForSlotFailover;
class WaveAsynchronousContextForMultiPartitionCleanup;
class WaveAsynchronousContextForUpgradePhase;
class FailoverAsynchronousContext;
class WaveAsynchronousContextForDebugInformation;
class WaveObjectManagerStatisticsTracker;
class WaveManagedObjectSynchronousQueryContextForDeletion;
class WaveManagedObjectSynchronousQueryContextForUpdate;
class WaveSendMulticastContext;
class WaveObjectManagerCommitTransactionContext;
class CliBlockContext;
class WaveBrokerPublishMessage;


class WaveWorker : public WaveElement
{
    private :
        virtual void initialize                         (WaveAsynchronousContextForBootPhases                   *pWaveAsynchronousContextForBootPhases);
        virtual void listenForEvents                    (WaveAsynchronousContextForBootPhases                   *pWaveAsynchronousContextForBootPhases);
        virtual void install                            (WaveAsynchronousContextForBootPhases                   *pWaveAsynchronousContextForBootPhases);
        virtual void enable                             (WaveAsynchronousContextForBootPhases                   *pWaveAsynchronousContextForBootPhases);
        virtual void upgrade                            (WaveAsynchronousContextForUpgradePhase                 *pWaveAsynchronousContextForUpgradePhase);
        virtual void boot                               (WaveAsynchronousContextForBootPhases                   *pWaveAsynchronousContextForBootPhases);
        virtual void hainstall                          (WaveAsynchronousContextForBootPhases                   *pWaveAsynchronousContextForBootPhases);
        virtual void haboot                             (WaveAsynchronousContextForBootPhases                   *pWaveAsynchronousContextForBootPhases);
        virtual void postboot                           (WaveAsynchronousContextForPostbootPhase                *pWaveAsynchronousContextForPostbootPhase);
        virtual void heartBeatFailure                   (WaveAsynchronousContext                               *pWaveAsynchronousContext);
        virtual void externalStateSynchronization       (WaveAsynchronousContextForExternalStateSynchronization *pWaveAsynchronousContextForExternalStateSynchronization);
        virtual void configReplayEnd                    (WaveAsynchronousContextForConfigReplayEnd              *pWaveAsynchronousContextForConfigReplayEnd);
        virtual void fileReplayEnd                      (WaveAsynchronousContextForFileReplayEnd                *pWaveAsynchronousContextForFileReplayEnd);
        virtual void slotFailover                       (WaveAsynchronousContextForSlotFailover                 *pWaveAsynchronousContextForSlotFailover);
        virtual void multiPartitionCleanup              (WaveAsynchronousContextForMultiPartitionCleanup        *pWaveAsynchronousContextForMultiPartitionCleanup);
        virtual void multiPartitionPartialCleanup       (WaveAsynchronousContextForMultiPartitionCleanup        *pWaveAsynchronousContextForMultiPartitionCleanup);
        virtual void shutdown                           (WaveAsynchronousContextForShutDownPhases               *pWaveAsynchronousContextForShutDownPhases);
        virtual void uninstall                          (WaveAsynchronousContextForShutDownPhases               *pWaveAsynchronousContextForShutDownPhases);
        virtual void disable                            (WaveAsynchronousContextForShutDownPhases               *pWaveAsynchronousContextForShutDownPhases);
        virtual void uninitialize                       (WaveAsynchronousContextForShutDownPhases               *pWaveAsynchronousContextForShutDownPhases);
        virtual void destruct                           (WaveAsynchronousContextForShutDownPhases               *pWaveAsynchronousContextForShutDownPhases);
        virtual void backendSyncUp                      (WaveAsynchronousContext                               *pWaveAsynchronousContext);

        virtual void failover                           (FailoverAsynchronousContext                            *pFailoverAsynchronousContext);

        virtual void getDebugInformation                (WaveAsynchronousContextForDebugInformation             *pWaveAsynchronousContextForDebugInformation);
        virtual void resetDebugInformation              (WaveAsynchronousContextForDebugInformation             *pWaveAsynchronousContextForDebugInformation);

        virtual void updateTimeConsumedInThisThread     (const UI32 &operationCode, const UI32 &sequencerStepIndex, const UI32 &numberOfSeconds, const SI32 &numberOfNanoSeconds);
        virtual void updateRealTimeConsumedInThisThread (const UI32 &operationCode, const UI32 &sequencerStepIndex, const UI32 &numberOfSeconds, const SI32 &numberOfNanoSeconds);

    protected :

        virtual WaveMessageStatus             send                                      (WaveMessage *pWaveMessage, WaveMessageResponseHandler pWaveMessageCallback, void *pWaveMessageContext, UI32 timeOutInMilliSeconds = 0, LocationId locationId = 0, WaveElement *pWaveMessageSender = NULL);
        virtual WaveMessageStatus             sendOneWay                                (WaveMessage *pWaveMessage, const LocationId &locationId = 0);
        virtual WaveMessageStatus             sendOneWayToFront                         (WaveMessage *pWaveMessage, const LocationId &locationId = 0);
        virtual WaveMessageStatus             sendSynchronously                         (WaveMessage *pWaveMessage, const LocationId &locationId = 0);
        virtual void                          sendToWaveCluster                         (WaveSendToClusterContext *pWaveSendToClusterContext);
        virtual void                          sendMulticast                             (WaveSendMulticastContext *pWaveSendMulticastContext);
        virtual void                          sendOneWayToWaveCluster                   (WaveSendToClusterContext *pWaveSendToClusterContext);
        virtual WaveMessageStatus             recall                                    (WaveMessage *pWaveMessage);
        virtual WaveMessageStatus             reply                                     (WaveMessage *pWaveMessage);
        virtual WaveMessageStatus             reply                                     (const WaveEvent *&pWaveEvent);
        virtual WaveMessageStatus             broadcast                                 (WaveEvent *pWaveEvent);
        virtual void                          trace                                     (TraceLevel traceLevel, const string &stringToTrace);
        virtual void                          tracePrintf                               (TraceLevel traceLevel, const bool &addNewLine, const bool &suppressPrefix, const char * const pFormat, ...);
        virtual void                          tracePrintf                               (TraceLevel traceLevel, const char * const pFormat, ...);
        virtual void                          waveAssert                               (bool isAssertNotRequired, const char *pFileName, UI32 lineNumber);
                void                          addOperationMap                           (UI32 operationCode, WaveMessageHandler pWaveMessageHandler, WaveElement *pWaveElement = NULL);
                void                          removeOperationMap                        (const UI32 &operationCode);
                void                          addServiceIndependentOperationMap         (UI32 operationCode, WaveServiceIndependentMessageHandler pWaveServiceIndependentMessageHandler);
                void                          addServiceIndependentOperationMap         (UI32 operationCode, ManagementInterfaceServiceIndependentMessageHandler pManagementInterfaceServiceIndependentMessageHandler);
                void                          removeServiceIndependentOperationMap      (UI32 operationCode);
        virtual ResourceId                    startTimer                                (TimerHandle &timerHandle, timeval &startInterval, timeval &periodicInterval, WaveTimerExpirationHandler pWaveTimerExpirationCallback, void *pWaveTimerExpirationContext = NULL, WaveElement *pWaveTimerSender = NULL);
        virtual ResourceId                    startTimer                                (TimerHandle &timerHandle, UI32 timeInMilliSeconds, WaveTimerExpirationHandler pWaveTimerExpirationCallback, void *pWaveTimerExpirationContext = NULL, WaveElement *pWaveTimerSender = NULL);
        virtual ResourceId                    deleteTimer                               (TimerHandle timerHandle);

        virtual void                          addLightPulseType                         (const string &lightPulseName, WaveElement *pWaveElement = NULL);

        virtual void                          holdMessages                              ();
        virtual void                          holdHighPriorityMessages                  ();
        virtual void                          holdEvents                                ();
        virtual void                          holdAll                                   ();
        virtual void                          unholdMessages                            ();
        virtual void                          unholdHighPriorityMessages                ();
        virtual void                          unholdEvents                              ();
        virtual void                          unholdAll                                 ();

        virtual UI32                          getNumberOfPendingTimerExpirationMessages ();
        virtual UI32                          getNumberOfPendingNormalMessages          ();
        virtual UI32                          getNumberOfPendingHighPriorityMessages    ();

                void                          addManagedClass                           (const string &managedClassName);

        virtual void                          startTransaction                          ();
        virtual bool                          isTransactionInProgress                   ();
        virtual ResourceId                    commitTransaction                         (WaveObjectManagerCommitTransactionContext *pWaveObjectManagerCommitTransactionContext = NULL);
        virtual void                          rollbackTransaction                       ();
        virtual void                          addWaveConfigEntry                        (Attribute *attribute);
        virtual void                          updateWaveConfigEntry                     (Attribute *attribute);
        virtual void                          getWaveConfigEntry                        (string &configName, Attribute *attribute, bool &configFound);
        virtual void                          updateWaveManagedObject                   (WaveManagedObject *pWaveManagedObject);
        virtual void                          updateMultipleWaveManagedObjects          (WaveManagedObjectSynchronousQueryContextForUpdate *pWaveManagedObjectSynchronousQueryContextForUpdate);
        virtual void                          deleteWaveManagedObject                   (const ObjectId &objectId);
        virtual void                          deleteWaveManagedObject                   (WaveManagedObjectSynchronousQueryContextForDeletion *pWaveManagedObjectSynchronousQueryContextForDeletion);
        virtual void                          deleteMultipleWaveManagedObjects          (WaveManagedObjectSynchronousQueryContextForDeletion *pWaveManagedObjectSynchronousQueryContextForDeletion);
        virtual void                          deleteManagedObjectCompositions           (WaveManagedObjectSynchronousQueryContextForDeletion *pWaveManagedObjectSynchronousQueryContextForDeletion, const set<string> relationsSet = set<string>());
        virtual void                          deleteManagedObjectCompositions           (const ObjectId &objectId, const set<string> relationsSet = set<string>());
    virtual void                          deletePartialManagedObjectCompositions    (const string &parentClassName, const string &compositionName, WaveManagedObjectSynchronousQueryContextForDeletion *pQueryContextForDeletionOnChildMO);
        virtual bool                          isManagedClassSupported                   (const string &managedClass);

        virtual void                          addRelationship                           (const string &parentClassName, const string &childClassName, const string &relationshipName, const ObjectId &parentObjectId, const ObjectId &childObjectId);
        virtual void                          deleteRelationship                        (const string &parentClassName, const string &childClassName, const string &relationshipName, const ObjectId &parentObjectId, const ObjectId &childObjectId);
        virtual void                          addToComposition                          (const string &parentClassName, const string &childCalssName, const string &compositionName, const ObjectId &parentObjectId, const ObjectId &childObjectId);
        virtual void                          deleteFromComposition                     (const string &parentClassName, const string &childCalssName, const string &compositionName, const ObjectId &parentObjectId, const ObjectId &childObjectId);
        virtual void                          addToAssociation                          (const string &parentClassName, const string &childCalssName, const string &associationName, const ObjectId &parentObjectId, const ObjectId &childObjectId);
        virtual void                          deleteFromAssociation                     (const string &parentClassName, const string &childCalssName, const string &associationName, const ObjectId &parentObjectId, const ObjectId &childObjectId);

        virtual void                          query                                     (WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext);
        virtual vector<WaveManagedObject *> *querySynchronouslyLocalManagedObjectsForLocationId (const LocationId &locationId, const string &className);
        virtual vector<WaveManagedObject *> *querySynchronouslyLocalManagedObjectsForLocationId (const LocationId &locationId, const string &className, const vector<string> &selectFields);
        virtual vector<WaveManagedObject *> *querySynchronouslyLocalManagedObjectsForLocationId (const LocationId &locationId, WaveManagedObjectSynchronousQueryContext *pWaveManagedObjectSynchronousQueryContext);
        virtual vector<WaveManagedObject *> *querySynchronously                         (WaveManagedObjectSynchronousQueryContext *pWaveManagedObjectSynchronousQueryContext);
        virtual WaveManagedObject           *createInMemoryManagedObject                (const  string &className);
        virtual ResourceId                   querySynchronouslyForCount                 (WaveManagedObjectSynchronousQueryContext *pWaveManagedObjectSynchronousQueryContext, UI32 &count);
        virtual ResourceId                   querySynchronouslyForCount                 (const string &managedClassName, UI32 &count, const string &schema = OrmRepository::getWaveCurrentSchema ());
        virtual ResourceId                   querySynchronouslyForCount                 (const string &managedClassName, const string &fieldName, const string &range, UI32 &count, const string &schema = OrmRepository::getWaveCurrentSchema ());
        virtual ResourceId                   querySynchronouslyForCountForManagedObjectByName (const string &managedClassName, const string &nameValue, UI32 &count, const string &schema = OrmRepository::getWaveCurrentSchema ());

        virtual vector<WaveManagedObject *> *querySynchronously                         (const string &managedClassName, const string &schema = OrmRepository::getWaveCurrentSchema ());
        virtual vector<WaveManagedObject *> *querySynchronously                         (const string &managedClassName, vector<ObjectId> &objectIds, const string &schema = OrmRepository::getWaveCurrentSchema ());
        virtual vector<WaveManagedObject *> *querySynchronouslyByName                   (const string &managedClassName, const string &managedObjectName, const string &schema = OrmRepository::getWaveCurrentSchema ());
        virtual WaveManagedObject           *queryManagedObject                         (const ObjectId &managedObjectId, const string &schema = OrmRepository::getWaveCurrentSchema ());

        virtual vector<WaveManagedObject *> *queryManagedObjectAssociatedWithSlot       (const string &managedClassName, UI32 slotNumber, LocationId locationId = 0, const string &schema = OrmRepository::getWaveCurrentSchema ());

        virtual TraceClientId                  getTraceClientId                         ();

        virtual void                           addEventType                             (const UI32 &eventOperationCode);

                void                           setCpuAffinity                           (const vector<UI32> &cpuAffinityVector);
                WaveServiceId                 getServiceId                             ();

        virtual void                           listenForEvent                           (WaveServiceId waveServiceId, UI32 sourceOperationCode, WaveEventHandler pWaveEventHandler, WaveElement *pWaveElement = NULL, const LocationId &sourceLocationId = 0);
        virtual ResourceId                     sendSynchronouslyToWaveClient            (const string &waveClientName, ManagementInterfaceMessage *pManagementInterfaceMessage, const SI32 &Instance = 0);
        virtual WaveMessageStatus              sendToWaveServer                         (const UI32 &waveServerId, ManagementInterfaceMessage *pManagementInterfaceMessage, WaveMessageResponseHandler messageCallback, WaveElement *pWaveMessageSender, void *pInputContext, UI32 timeOutInMilliSeconds);
        virtual ResourceId                     sendToWaveClient                         (const string &waveClientName, ManagementInterfaceMessage *pManagementInterfaceMessage, WaveMessageResponseHandler pWaveMessageCallback, void *pWaveMessageContext = NULL, UI32 timeOutInMilliSeconds = 0, const SI32 &Instance = 0);
        virtual void                          sendToWaveClients                         (WaveSendToClientsContext *pWaveSendToClientsContext);
        virtual ResourceId                    sendOneWayToAllWaveClients                (ManagementInterfaceMessage *pManagementInterfaceMessage);
        virtual WaveManagedObject             *createManagedObjectInstance              (const string &managedClassName);
                void                           addManagedClass                          (const string &managedClassName, WaveElement *pOwnerForInstantiation = NULL);
        virtual WaveMessage                  *createMessageInstance                    (const UI32 &operationCode);

        virtual void                           printfToWaveClientSession                (const WaveClientSessionContext &waveClientSessionContext, const char * const pFormat, ...);
        virtual void                           printfToAllWaveClientSessions            (const WaveClientSessionContext &waveClientSessionContext, const char * const pFormat, ...);
        virtual ResourceId                     addLog                                   (ResourceId logType, ResourceId logDescriptionType, const vector<Attribute *> &logDescriptionArguments);
                void                           registerLock                             (const string &serviceString);
        virtual bool                           isBeingSurrogated                        ();

        virtual ResourceId                     updateHardwareSynchronizationState       (ResourceId hardwareSynchronizationState, const vector<LocationId> &locationIds);
        virtual ResourceId                     updateHardwareSynchronizationState       (ResourceId hardwareSynchronizationState, LocationId locationId = 0);

        virtual void                           postponeMessageHandling                  (WaveMessage *pWaveMessage);
        virtual void                           resumeAllPostponedMessages               ();

        /**
         * This API has few limitations.
         * 1. The MO/class 'className' should not be part of any c++ inheritance hierarchy.
         * 2. The table/MO should have a relation pointing to it or the MO should have 1-m relation point from it.
         *    This means the MO should have its own DerivationsInstances table.
         * So, Use deleteMultipleWaveManagedObjects API to avoid these limitations.
         */
        virtual void                           deleteAllManagedObjectInstances          (const string &className);
        virtual void                           dbBasicSanityCheck                       (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        virtual void                           dbInconsistencyCheck                     (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

        virtual void						   zeroize (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases);
                WaveObjectManagerStatisticsTracker  *getPWaveObjectManagerStatisticsTracker () const;

        virtual ResourceId                     blockCli                                  (const CliBlockContext &cliBlockContext, const bool &clusterWide);
        virtual ResourceId                     unblockCli                                (const CliBlockContext &cliBlockContext, const bool &clusterWide);

        virtual WaveMessageBrokerStatus        connectToMessageBroker                    (const string &brokerName, const string &brokerIpAddress, const SI32 &brokerPort);
        virtual WaveMessageBrokerStatus        subscribeToMessageBroker                  (const string &brokerName, const vector<string> &topicNames, const vector<WaveBrokerPublishMessageHandler> publishMessageHandlers, WaveElement *pSubscriber = NULL);
        virtual WaveMessageBrokerStatus        subscribeToMessageBroker                  (const string &brokerName, const vector<string> &topicNames, WaveBrokerPublishMessageHandler publishMessageHandler, WaveElement *pSubscriber = NULL);
        virtual WaveMessageBrokerStatus        subscribeToMessageBroker                  (const string &brokerName, const string &topicName, WaveBrokerPublishMessageHandler publishMessageHandler, WaveElement *pSubscriber = NULL);
        virtual WaveMessageBrokerStatus        unsubscribeToMessageBroker                (const string &brokerName, const vector<string> &topicNames, WaveElement *pSubscriber = NULL);
        virtual WaveMessageBrokerStatus        unsubscribeToMessageBroker                (const string &brokerName, const string &topicName, WaveElement *pSubscriber = NULL);
        virtual WaveMessageBrokerStatus        publishToMessageBroker                    (const string &brokerName, WaveBrokerPublishMessage *pWaveBrokerPublishMessage, WaveElement *pSubscriber = NULL);

                void                           deliverWaveBrokerPublishedEvent           (const string &brokerName, const string &topicName, WaveBrokerPublishMessage *pWaveBrokerPublishMessage);

    public :
                 WaveWorker (WaveObjectManager *pWaveObjectManager);
                 WaveWorker (WaveObjectManager *pWaveObjectManager, const bool &linkWorkerToParentObjectManager);

        virtual ~WaveWorker ();


    // Now the data members

    private :
        bool m_linkWorkerToParentObjectManager;

    protected :
    public :

    friend class WaveObjectManager;
    friend class WavePostbootWorker;
    friend class WaveShutdownWorker;
    friend class WaveDebugInformationWorker;
};

}

#endif //WAVEWORKER_H
