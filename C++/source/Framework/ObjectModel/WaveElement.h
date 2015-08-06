/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMELEMENT_H
#define PRISMELEMENT_H

#include "Framework/Utils/StringUtils.h"
//#include "Framework/Messaging/Local/WaveMessage.h"
#include "Framework/Trace/TraceMessages.h"
#include "Framework/Utils/PrismLinearSequencerContext.h"
#include "Framework/Utils/PrismSynchronousLinearSequencerContext.h"
#include "Framework/ObjectModel/ObjectId.h"
#include "Framework/ObjectRelationalMapping/OrmRepository.h"
#include "Framework/ObjectModel/WaveClientSessionContext.h"

#include <vector>

using namespace std;

namespace WaveNs
{

class WaveMessage;
class WaveEvent;
class WaveElement;
class WaveObjectManager;
class WaveObjectManagerCommitTransactionContext;
class WaveManagedObjectQueryContext;
class WaveManagedObjectSynchronousQueryContext;
class WaveManagedObjectSynchronousQueryContextForDeletion;
class WaveManagedObjectSynchronousQueryContextForUpdate;
class WaveManagedObject;
class ManagementInterfaceMessage;
class ManagementInterfaceServiceIndependentMessage;
class WaveServiceIndependentMessage;
class WaveSendToClusterContext;
class WaveSendToClientsContext;
class WaveSendMulticastContext;
class CliBlockContext;
class WaveBrokerPublishMessage;

typedef void (WaveElement::* WaveMessageHandler)                  (WaveMessage *pWaveMessage);
typedef void (WaveElement::* WaveEventHandler)                    (const WaveEvent *&pWaveEvent);
typedef void (WaveElement::* WaveMessageResponseHandler)          (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, void *pContext);
typedef void (WaveElement::* PrismTimerExpirationHandler)          (TimerHandle timerHandle, void *pContext);
typedef void (*WaveServiceIndependentMessageHandler)                (WaveServiceIndependentMessage *pWaveServiceIndependentMessage);
typedef void (*ManagementInterfaceServiceIndependentMessageHandler) (ManagementInterfaceServiceIndependentMessage *pManagementInterfaceServiceIndependentMessage);

typedef void (WaveElement::* WaveBrokerPublishMessageHandler)      (const WaveBrokerPublishMessage * const pWaveBrokerPublishMessage);

class WaveElement
{
    private :
                void setPWaveObjectManager              (WaveObjectManager *pWaveObjectManager);

        virtual void updateTimeConsumedInThisThread     (const UI32 &operationCode, const UI32 &sequencerStepIndex, const UI32 &numberOfSeconds, const SI32 &numberOfNanoSeconds) = 0;
        virtual void updateRealTimeConsumedInThisThread (const UI32 &operationCode, const UI32 &sequencerStepIndex, const UI32 &numberOfSeconds, const SI32 &numberOfNanoSeconds) = 0;

    protected :
                                              WaveElement                                         (WaveObjectManager *pWaveObjectManager);
                                              WaveElement                                         (const WaveElement &prismElement);
                WaveElement                 &operator =                                           (const WaveElement &prismElement);
        virtual WaveMessageStatus             send                                                 (WaveMessage *pWaveMessage, WaveMessageResponseHandler pWaveMessageCallback, void *pWaveMessageContext, UI32 timeOutInMilliSeconds = 0, LocationId locationId = 0, WaveElement *pWaveMessageSender = NULL) = 0;
        virtual WaveMessageStatus             sendOneWay                                           (WaveMessage *pWaveMessage, const LocationId &locationId = 0) = 0;
        virtual WaveMessageStatus             sendOneWayToFront                                    (WaveMessage *pWaveMessage, const LocationId &locationId = 0) = 0;
        virtual WaveMessageStatus             sendSynchronously                                    (WaveMessage *pWaveMessage, const LocationId &locationId = 0) = 0;
        virtual void                          sendToWaveCluster                                    (WaveSendToClusterContext *pWaveSendToClusterContext) = 0;
        virtual void                          sendMulticast                                        (WaveSendMulticastContext *pWaveSendMulticastContext) = 0;
        virtual void                          sendOneWayToWaveCluster                              (WaveSendToClusterContext *pWaveSendToClusterContext) = 0;
        virtual WaveMessageStatus             recall                                               (WaveMessage *pWaveMessage) = 0;
        virtual WaveMessageStatus             reply                                                (WaveMessage *pWaveMessage) = 0;
        virtual WaveMessageStatus             broadcast                                            (WaveEvent *pWaveEvent) = 0;
        virtual void                          trace                                                (TraceLevel traceLevel, const string &stringToTrace) = 0;
        virtual void                          tracePrintf                                          (TraceLevel traceLevel, const bool &addNewLine, const bool &suppressPrefix, const char * const pFormat, ...) = 0;
        virtual void                          tracePrintf                                          (TraceLevel traceLevel, const char * const pFormat, ...) = 0;
        virtual void                          prismAssert                                          (bool isAssertNotRequired, const char *pFileName, UI32 lineNumber) = 0;
        virtual ResourceId                    startTimer                                           (TimerHandle &timerHandle, timeval &startInterval, timeval &periodicInterval, PrismTimerExpirationHandler pPrismTimerExpirationCallback, void *pPrismTimerExpirationContext = NULL, WaveElement *pPrismTimerSender = NULL) = 0;
        virtual ResourceId                    startTimer                                           (TimerHandle &timerHandle, UI32 timeInMilliSeconds, PrismTimerExpirationHandler pPrismTimerExpirationCallback, void *pPrismTimerExpirationContext = NULL, WaveElement *pPrismTimerSender = NULL) = 0;
        virtual ResourceId                    deleteTimer                                          (TimerHandle timerHandle) = 0;

                void                          prismLinearSequencerSucceededStep                    (PrismLinearSequencerContext *pPrismLinearSequencerContext);
                void                          prismLinearSequencerFailedStep                       (PrismLinearSequencerContext *pPrismLinearSequencerContext);
                void                          prismLinearSequencerStartTransactionStep             (PrismLinearSequencerContext *pPrismLinearSequencerContext);
                void                          prismLinearSequencerCommitTransactionStep            (PrismLinearSequencerContext *pPrismLinearSequencerContext);
                ResourceId                    prismSynchronousLinearSequencerSucceededStep         (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
                ResourceId                    prismSynchronousLinearSequencerFailedStep            (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
                ResourceId                    prismSynchronousLinearSequencerStartTransactionStep  (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
                ResourceId                    prismSynchronousLinearSequencerCommitTransactionStep (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);


        virtual void                          holdMessages                                         ()                                                                                    = 0;
        virtual void                          holdHighPriorityMessages                             ()                                                                                    = 0;
        virtual void                          holdEvents                                           ()                                                                                    = 0;
        virtual void                          holdAll                                              ()                                                                                    = 0;
        virtual void                          unholdMessages                                       ()                                                                                    = 0;
        virtual void                          unholdHighPriorityMessages                           ()                                                                                    = 0;
        virtual void                          unholdEvents                                         ()                                                                                    = 0;
        virtual void                          unholdAll                                            ()                                                                                    = 0;

        virtual UI32                          getNumberOfPendingTimerExpirationMessages            ()                                                                                    = 0;
        virtual UI32                          getNumberOfPendingNormalMessages                     ()                                                                                    = 0;
        virtual UI32                          getNumberOfPendingHighPriorityMessages               ()                                                                                    = 0;

        virtual void                          startTransaction                                     ()                                                                                    = 0;
        virtual bool                          isTransactionInProgress                              ()                                                                                    = 0;
        virtual ResourceId                    commitTransaction                                    (WaveObjectManagerCommitTransactionContext *pWaveObjectManagerCommitTransactionContext = NULL) = 0;
        virtual void                          rollbackTransaction                                  ()                                                                                    = 0;
        virtual void                          updateWaveManagedObject                              (WaveManagedObject *pWaveManagedObject)                                               = 0;
        virtual void                          deleteWaveManagedObject                              (const ObjectId &objectId)                                                            = 0;
        virtual void                          deleteWaveManagedObject                              (WaveManagedObjectSynchronousQueryContextForDeletion *pWaveManagedObjectSynchronousQueryContextForDeletion) = 0;

        virtual void                          updateMultipleWaveManagedObjects                     (WaveManagedObjectSynchronousQueryContextForUpdate *pWaveManagedObjectSynchronousQueryContextForUpdate)     = 0;
        virtual void                          deleteMultipleWaveManagedObjects                     (WaveManagedObjectSynchronousQueryContextForDeletion *pWaveManagedObjectSynchronousQueryContextForDeletion) = 0;
        virtual void                          deleteManagedObjectCompositions                      (WaveManagedObjectSynchronousQueryContextForDeletion *pWaveManagedObjectSynchronousQueryContextForDeletion, const set<string> relationsSet = set<string>()) = 0;
        virtual void                          deleteManagedObjectCompositions                      (const ObjectId &objectId, const set<string> relationsSet = set<string>()) = 0;

        virtual bool                          isManagedClassSupported                              (const string &managedClass) = 0;

        virtual void                          addRelationship                                      (const string &parentClassName, const string &childClassName, const string &relationshipName, const ObjectId &parentObjectId, const ObjectId &childObjectId) = 0;
        virtual void                          deleteRelationship                                   (const string &parentClassName, const string &childClassName, const string &relationshipName, const ObjectId &parentObjectId, const ObjectId &childObjectId) = 0;
        virtual void                          addToComposition                                     (const string &parentClassName, const string &childCalssName, const string &compositionName, const ObjectId &parentObjectId, const ObjectId &childObjectId) = 0;
        virtual void                          deleteFromComposition                                (const string &parentClassName, const string &childCalssName, const string &compositionName, const ObjectId &parentObjectId, const ObjectId &childObjectId) = 0;
        virtual void                          addToAssociation                                     (const string &parentClassName, const string &childCalssName, const string &associationName, const ObjectId &parentObjectId, const ObjectId &childObjectId) = 0;
        virtual void                          deleteFromAssociation                                (const string &parentClassName, const string &childCalssName, const string &associationName, const ObjectId &parentObjectId, const ObjectId &childObjectId) = 0;

        virtual void                          query                                                (WaveManagedObjectQueryContext *pWaveManagedObjectQueryConttex)                       = 0;
        virtual vector<WaveManagedObject *>  *querySynchronouslyLocalManagedObjectsForLocationId   (const LocationId &locationId, const string &className) = 0;
        virtual vector<WaveManagedObject *>  *querySynchronouslyLocalManagedObjectsForLocationId   (const LocationId &locationId, const string &className, const vector<string> &selectFields) = 0;
        virtual vector<WaveManagedObject *>  *querySynchronouslyLocalManagedObjectsForLocationId   (const LocationId &locationId, WaveManagedObjectSynchronousQueryContext *pWaveManagedObjectSynchronousQueryContext) = 0;
        virtual vector<WaveManagedObject *>  *querySynchronously                                   (WaveManagedObjectSynchronousQueryContext *pWaveManagedObjectSynchronousQueryContext) = 0;
        virtual ResourceId                    querySynchronouslyForCount                           (WaveManagedObjectSynchronousQueryContext *pWaveManagedObjectSynchronousQueryContext, UI32 &count) = 0;
        virtual ResourceId                    querySynchronouslyForCount                           (const string &managedClassName, UI32 &count, const string &schema = OrmRepository::getWaveCurrentSchema ()) = 0;
        virtual ResourceId                    querySynchronouslyForCount                           (const string &managedClassName, const string &fieldName, const string &range, UI32 &count, const string &schema = OrmRepository::getWaveCurrentSchema ()) = 0;
        virtual vector<WaveManagedObject *>  *querySynchronously                                   (const string &managedClassName, const string &schema = OrmRepository::getWaveCurrentSchema ())                                                      = 0;
        virtual vector<WaveManagedObject *>  *querySynchronously                                   (const string &managedClassName, vector<ObjectId> &objectIds, const string &schema = OrmRepository::getWaveCurrentSchema ())                         = 0;
        virtual vector<WaveManagedObject *>  *querySynchronouslyByName                             (const string &managedClassName, const string &managedObjectName, const string &schema = OrmRepository::getWaveCurrentSchema ())                     = 0;
        virtual WaveManagedObject            *queryManagedObject                                   (const ObjectId &managedObjectId, const string &schema = OrmRepository::getWaveCurrentSchema ())                                                     = 0;
        virtual vector<WaveManagedObject *>  *queryManagedObjectAssociatedWithSlot                 (const string &managedClassName, UI32 slotNumber, LocationId locationId = 0, const string &schema = OrmRepository::getWaveCurrentSchema ())                                     = 0;

        virtual TraceClientId                 getTraceClientId                                     ()                                                                                    = 0;
        virtual void                          addEventType                                         (const UI32 &eventOperationCode)                                                      = 0;

        virtual WaveObjectManager            *getPWaveObjectManager                                () const;

        virtual void                          listenForEvent                                       (WaveServiceId prismServiceId, UI32 sourceOperationCode, WaveEventHandler pWaveEventHandler, WaveElement *pWaveElement = NULL, const LocationId &sourceLocationId = 0) = 0;

        virtual ResourceId                    sendSynchronouslyToWaveClient                        (const string &waveClientName, ManagementInterfaceMessage *pManagementInterfaceMessage, const SI32 &Instance = 0) = 0;
        virtual WaveMessageStatus             sendToWaveServer                                     (const UI32 &waveServerId, ManagementInterfaceMessage *pManagementInterfaceMessage, WaveMessageResponseHandler messageCallback, WaveElement *pWaveMessageSender, void *pInputContext, UI32 timeOutInMilliSeconds) = 0;
        virtual ResourceId                    sendToWaveClient                                     (const string &waveClientName, ManagementInterfaceMessage *pManagementInterfaceMessage, WaveMessageResponseHandler pWaveMessageCallback, void *pWaveMessageContext = NULL, UI32 timeOutInMilliSeconds = 0, const SI32 &Instance = 0) = 0;
        virtual void                          sendToWaveClients                                    (WaveSendToClientsContext *pWaveSendToClientsContext) = 0;
        virtual void                          printfToWaveClientSession                            (const WaveClientSessionContext &waveClientContext, const char * const pFormat, ...) = 0;
        virtual void                          printfToAllWaveClientSessions                        (const WaveClientSessionContext &waveClientContext, const char * const pFormat, ...) = 0;
        virtual ResourceId                    addLog                                               (ResourceId logType, ResourceId logDescriptionType, const vector<Attribute *> &logDescriptionArguments) = 0;
        virtual bool                          isBeingSurrogated                                    () = 0;

        virtual ResourceId                    updateHardwareSynchronizationState                   (ResourceId hardwareSynchronizationState, const vector<LocationId> &locationIds) = 0;
        virtual ResourceId                    updateHardwareSynchronizationState                   (ResourceId hardwareSynchronizationState, LocationId locationId = 0) = 0;

        virtual void                          deleteAllManagedObjectInstances                      (const string &className) = 0;

        virtual void                          postponeMessageHandling                              (WaveMessage *pWaveMessage) = 0;
        virtual void                          resumeAllPostponedMessages                           () = 0;
        virtual ResourceId                    blockCli                                             (const CliBlockContext &cliBlockContext, const bool &clusterWide) = 0;
        virtual ResourceId                    unblockCli                                           (const CliBlockContext &cliBlockContext, const bool &clusterWide) = 0;

        virtual WaveMessageBrokerStatus       connectToMessageBroker                               (const string &brokerName, const string &brokerIpAddress, const SI32 &brokerPort) = 0;
        virtual WaveMessageBrokerStatus       subscribeToMessageBroker                             (const string &brokerName, const vector<string> &topicNames, const vector<WaveBrokerPublishMessageHandler> publishMessageHandlers, WaveElement *pSubscriber = NULL) = 0;
        virtual WaveMessageBrokerStatus       subscribeToMessageBroker                             (const string &brokerName, const vector<string> &topicNames, WaveBrokerPublishMessageHandler publishMessageHandler, WaveElement *pSubscriber = NULL) = 0;
        virtual WaveMessageBrokerStatus       subscribeToMessageBroker                             (const string &brokerName, const string &topicName, WaveBrokerPublishMessageHandler publishMessageHandler, WaveElement *pSubscriber = NULL) = 0;
        virtual WaveMessageBrokerStatus       unsubscribeToMessageBroker                           (const string &brokerName, const vector<string> &topicNames, WaveElement *pSubscriber = NULL) = 0;
        virtual WaveMessageBrokerStatus       unsubscribeToMessageBroker                           (const string &brokerName, const string &topicName, WaveElement *pSubscriber = NULL) = 0;
        virtual WaveMessageBrokerStatus       publishToMessageBroker                               (const string &brokerName, WaveBrokerPublishMessage *pWaveBrokerPublishMessage, WaveElement *pSubscriber = NULL) = 0;

    public :
        virtual                   ~WaveElement                ();
        virtual WaveManagedObject *createManagedObjectInstance (const string &managedClassName);
        virtual WaveMessage      *createMessageInstance       (const UI32 &operationCode);

    // Now the data members

    private :
    protected :
        WaveObjectManager *m_pWaveObjectManager;

    public :

    friend class PrismLinearSequencerContext;
    friend class DatabaseObjectManagerExecuteQueryWorker;
    friend class PrismSynchronousLinearSequencerContext;
};

}

#endif //PRISMELEMENT_H
