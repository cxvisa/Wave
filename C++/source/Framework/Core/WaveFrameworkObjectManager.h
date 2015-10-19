/***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEFRAMEWORKOBJECTMANAGER_H
#define WAVEFRAMEWORKOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"
#include "Framework/Core/FrameworkSequenceGeneratorFactory.h"
#include "Framework/Utils/ServerStreamingSocket.h"
#include "Framework/ObjectRelationalMapping/OrmRepository.h"
#include "Framework/Database/DatabaseStandaloneTransaction.h"

namespace WaveNs
{

class WaveFrameworkObjectManagerInitializeWorker;
class WaveFrameworkConfigurationWorker;
class WaveLinearSequencerContext;
class WaveInitializeObjectManagerMessage;
class LocationBase;
class WaveCreateClusterWithNodesMessage;
class WaveConfigureClusterSecondaryMessage;
class WaveConfigureClusterSecondaryHaPeerMessage;
class WaveConfigureClusterSecondaryPhase1Message;
class WaveConfigureClusterSecondaryHaPeerPhase1Message;
class WaveConfigureClusterSecondaryPhase2Message;
class WaveConfigureClusterSecondaryPhase3Message;
class WaveConfigureClusterSecondaryHaPeerPhase3Message;
class CreateClusterWithNodesContext;
class FrameworkObjectManagerAddNodesToClusterMessage;
class FrameworkObjectManagerDeleteNodesFromClusterMessage;
class FrameworkObjectManagerDestroyClusterMessage;
class AddNodesToClusterContext;
class DeleteNodesFromClusterContext;
class DeleteNodeOnSecondaryContext;
class FrameworkObjectManagerUnconfigureClusterSecondaryMessage;
class WaveConfigureClusterSecondaryMessage;
class FrameworkObjectManagerRejoinNodesToClusterMessage;
class FrameworkObjectManagerRejoinClusterSecondaryMessage;
class FrameworkObjectManagerRejoinClusterSecondaryHaPeerMessage;
class RejoinNodesToClusterContext;
class DestroyClusterContext;
class FrameworkObjectManagerDetachFromClusterMessage;
class FrameworkObjectManagerLostHeartBeatMessage;
class WaveFinalizeWorker;
class HeartBeatLostContext;
class DestroyClusterAsynchronousContext;
class DetachFromClusterAsynchronousContext;
class WaveFrameworkFailoverWorker;
class WaveFrameworkFailoverWorkerContext;
class DetachFromClusterContext;
class DatabaseObjectManagerBackupMessage;
class DatabaseObjectManagerCleanPreparedTransactionsMessage;
class DatabaseObjectManagerEmptyMessage;
class FrameworkObjectManagerUpdateListOfSecondariesMessage;
class UpdateListOfSecondariesContext;
class FrameworkObjectManagerPrimaryChangedMessage;
class FrameworkObjectManagerPrimaryChangedHaPeerMessage;
class FrameworkObjectManagerPrimaryChangedPhase1Message;
class FrameworkObjectManagerPrimaryChangedHaPeerPhase1Message;
class FrameworkObjectManagerPrimaryChangedPhase2Message;
class FrameworkObjectManagerPrimaryChangedPhase3Message;
class FrameworkObjectManagerPrimaryChangedHaPeerPhase3Message;
class WaveFrameworkObjectManagerServiceControlWorker;
class WaveAsynchronousContextForBootPhases;
class WaveFrameworkObjectManagerPostbootWorker;
class WaveFrameworkObjectManagerPostPersistentBootWorker;
class WaveFrameworkObjectManagerHaSyncWorker;
class WaveRejoinClusterSecondaryPhase1Message;
class WaveRejoinClusterSecondaryHaPeerPhase1Message;
class WaveRejoinClusterSecondaryPhase2Message;
class WaveRejoinClusterSecondaryPhase3Message;
class WaveRejoinClusterSecondaryHaPeerPhase3Message;
class FrameworkObjectManagerStartExternalStateSynchronizationMessage;
class FrameworkObjectManagerStartSlotFailoverMessage;
class FrameworkObjectManagerNewPrincipalEstablishedMessage;
class FrameworkObjectManagerSecondaryNodeFailureNotificationMessage;
class SecondaryNodeClusterContext;
class SecondaryNodeClusterPhase2Context;
class SecondaryNodeClusterPhase3Context;
class FrameworkObjectManagerDisconnectFromAllNodesMessage;
class FrameworkObjectManagerPrepareNodeForHAMessage;
class FrameworkObjectManagerDisconnectFromAllInstanceClientsMessage;
class FrameworkObjectManagerEstablishPrincipalAfterClusterRebootMessage;
class RejoinNodesToClusterContext;
class FrameworkObjectManagerResetNodeToUnconfirmRole;
class FrameworkObjectManagerRemoveKnownLocationsMessage;
class ZeroizeForFIPSMessage;
class ZeroizeForFIPSLinearSequencerContext;
class VcsClusterConfiguration;
class FrameworkObjectManagerPrepareForWarmRecoveryWithDefaultConfiguration;
class FrameworkObjectManagerStoreConfigurationIntentMessage;
class FrameworkObjectManagerRemoveConfigurationIntentMessage;
class FrameworkObjectManagerPrepareForHaFailoverWithPersistentConfiguration;
class FrameworkObjectManagerRollbackStandbyOnActiveRollbackMessage;
class WaveFrameworkReplayConfigMessage;

typedef SI32        (*GetInstancesFunction)                     (vector<SI32> &connectedInstancesVector);
typedef SI32        (*GetInstancesAndSubInstancesFunction)      (vector<SI32> &connectedInstancesVector, vector<SI32> &connectedSubInstancesVector);
typedef SI32        (*GetThisSlotInstanceFunction)              ();
typedef void        (*CreateDummySlotFunction)                  (const UI32 slotNumber);
typedef void        (*RaslogAssertFunction)                     (const string &file, const string &function, const UI32 line, const string &assertString);
typedef string      (*GetFirmwareVersionFunction)               ();
typedef int         (*HandleDcmFssConfigUpdateFunction)         (void *dcmConfigData);
typedef ResourceId  (*SetVcsClusterConfigHandlerFunction)       (VcsClusterConfiguration *pDcmVcsClusterConfigData, const UI32 &context);
typedef void        (*GetVcsClusterConfigHandlerFunction)       (VcsClusterConfiguration *pDcmVcsClusterConfigData, const UI32 &context);
typedef bool        (*NotifySyncUpdateFailureFunction)          (const ResourceId &reason);
typedef void        (*NotifyClusterReadyStateFunction)          (bool &readyState);

class WaveFrameworkObjectManager : WaveLocalObjectManager
{
    private :
                              WaveFrameworkObjectManager                                      ();
                             ~WaveFrameworkObjectManager                                      ();
                void          boot                                                             (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                LocationBase *getThisLocation                                                  () const;
        const   UI32          getThisLocationId                                                () const;
        static  void          setIsFrameworkReadyToBoot                                        (bool isFrameworkReadyToBoot);
        static  bool          getIsFrameworkReadyToBoot                                        ();
                void          getInstances                                                     (vector<SI32> &connectedInstanceVector);
                void          getInstancesAndSubInstances                                      (vector<SI32> &connectedInstanceVector, vector<SI32> &connectedSubInstanceVector);
                SI32          getThisSlotInstance                                              ();
                void          createDummySlot                                                  (const UI32 slotNumber);
                bool          isServiceToBeExcludedInClusterCommunications                     (const WaveServiceId &waveServiceId);

                void          createClusterWithNodesMessageHandler                             (WaveCreateClusterWithNodesMessage *pWaveCreateClusterWithNodesMessage);
                void          createClusterWithNodesValidateStep                               (CreateClusterWithNodesContext *pCreateClusterWithNodesContext);
                void          createClusterWithNodesCollectValidationDataStep                  (CreateClusterWithNodesContext *pCreateClusterWithNodesContext);
                void          createClusterWithNodesValidateLocationRoleStep                   (CreateClusterWithNodesContext *pCreateClusterWithNodesContext);
                void          createClusterWithNodesAddKnownLocationsStep                      (CreateClusterWithNodesContext *pCreateClusterWithNodesContext);
                void          createClusterWithNodesConnectToNewKnownLocationsStep             (CreateClusterWithNodesContext *pCreateClusterWithNodesContext);
                void          createClusterWithNodesReplayGlobalOnlyConfigIfRequiredStep       (CreateClusterWithNodesContext *pCreateClusterWithNodesContext);
                void          createClusterWithNodesPausePersistenceStep                       (CreateClusterWithNodesContext *pCreateClusterWithNodesContext);
                void          backUpDatabaseAfterSendingClusterPhase0Message                   ();
                void          createClusterWithNodesConfigureNewKnownLocationsStep             (CreateClusterWithNodesContext *pCreateClusterWithNodesContext);
                void          createClusterWithNodesConfigureNewKnownLocationsCallback         (FrameworkStatus frameworkStatus, WaveConfigureClusterSecondaryMessage *pWaveConfigureClusterSecondaryMessage, void *pContext);
                void          resumeDatabase                                                   ();
                void          createClusterWithNodesConfigureNewKnownLocationsPhase1Step       (CreateClusterWithNodesContext *pCreateClusterWithNodesContext);
                void          createClusterWithNodesConfigureNewKnownLocationsPhase1Callback   (FrameworkStatus frameworkStatus, WaveConfigureClusterSecondaryPhase1Message *pWaveConfigureClusterSecondaryPhase1Message, void *pContext);
                void          createClusterWithNodesConfigureNewKnownLocationsPhase2Step       (CreateClusterWithNodesContext *pCreateClusterWithNodesContext);
                void          createClusterWithNodesConfigureNewKnownLocationsPhase2Callback   (FrameworkStatus frameworkStatus, WaveConfigureClusterSecondaryPhase2Message *pWaveConfigureClusterSecondaryPhase2Message, void *pContext);
                void          createClusterWithNodesConfigureNewKnownLocationsPhase3Step       (CreateClusterWithNodesContext *pCreateClusterWithNodesContext);
                void          createClusterWithNodesConfigureNewKnownLocationsPhase3Callback   (FrameworkStatus frameworkStatus, WaveConfigureClusterSecondaryPhase3Message *pWaveConfigureClusterSecondaryPhase3Message, void *pContext);
                void          failoverforNodesFailedInPhase2                                   (CreateClusterWithNodesContext *pCreateClusterWithNodesContext);
                void          failoverforNodesFailedInPhase2Callback                           (WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext);
                void          failoverforNodesFailedInPhase3Callback                           (WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext);
                void          createClusterWithNodesResumeDatabaseStep                         (CreateClusterWithNodesContext *pCreateClusterWithNodesContext);
                void          createClusterWithNodesSendValidationResultsStep                  (CreateClusterWithNodesContext *pCreateClusterWithNodesContext);
                void          createClusterWithNodesSendListOfSecondariesToAllNodesStep        (CreateClusterWithNodesContext *pCreateClusterWithNodesContext);
                void          createClusterWithNodesSendListOfSecondariesToAllNodesCallback    (FrameworkStatus frameworkStatus, FrameworkObjectManagerUpdateListOfSecondariesMessage *pFrameworkObjectManagerUpdateListOfSecondariesMessage, void *pContext);
                void          sendReplyBackToClusterGlobalService                              (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void          startHeartBeatToSecondaryNodes                                   (CreateClusterWithNodesContext *pCreateClusterWithNodesContext);
                void          broadcastNewNodesAddedEventOnPrimaryStep                         (CreateClusterWithNodesContext *pCreateClusterWithNodesContext);
                void          configureSecondaryNodeMessageHandler                             (WaveConfigureClusterSecondaryMessage *pWaveConfigureClusterSecondaryMessage);
                void          configureSecondaryNodeHaPeerMessageHandler                       (WaveConfigureClusterSecondaryHaPeerMessage *pWaveConfigureClusterSecondaryHaPeerMessage);
                void          rollbackNodeIfRequiredStep                                       (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void          prepareNodeForAddNodeIfRequired                                  (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          prepareSecondaryNodeForAddNodeIfRequiredCallback                 (WaveAsynchronousContext *pWaveAsynchronousContext);
                void          preparePrimaryNodeForAddNodeIfRequiredCallBack                   (DestroyClusterAsynchronousContext *pDestroyClusterAsynchronousContext);
                void          configureSecondaryNodeValidateDefaultConfigurationStep           (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          configureSecondaryNodeValidateStep                               (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
		        //ResourceId    updateTableIdsInOrmWithSchemaInfoReceivedFromPrimary             (const vector<string> & managedObjectNamesForSchemaChange,const vector<UI32> & classIds,const vector<UI32>  & parentTableIds);
                bool          isSchemaReceivedFromPrimaryCompatible                            (const vector<string> & managedObjectNamesForSchemaChange,const vector<string> & fieldNamesStringsForSchemaChange,const vector<string> & fieldNamesTypesForSchemaChange,const vector<UI32> & classIds,const vector<UI32>  & parentTableIds);
                //string        generateSqlToAlterAuxilliaryTableNames                           (vector<string>& oldAuxilliaryTableNames,vector<string>& newAuxilliaryTableNames, vector<string>&parentTableNames, vector<string>& relatedToTableNames);
                //string        handleConstraintsForAuxilliaryTable                              (string WaveSchema, string &oldAuxilliaryTableName, string &newAuxilliaryTableName, string& parentTableName, string &relatedToTableName);
                void          configureSecondaryNodeValidateVersionStep                        (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          configureSecondaryNodeValidateServicesStep                       (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          configureSecondaryNodeAddNewKnownLocationsStep                   (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          configureSecondaryNodeConnectToNewKnownLocationsStep             (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          configureSecondaryNodeBackupCurrentDatabaseStep                  (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          configureSecondaryNodeCleanPreparedTransactionsStep              (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          configureSecondaryNodeEmptyDatabaseStep                          (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          configureSecondaryNodeLoadDatabaseFromPrimaryDatabaseStep        (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          configureSecondaryNodeUpdateInstanceIdsStep                      (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          configureSecondaryNodeShutdownServicesStep                       (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          configureSecondaryNodeNotifyHaPeerStep                           (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          configureSecondaryNodeConfigureMyLocationIdStep                  (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          configureSecondaryNodeBootServicesPrePhaseStep                   (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          configureSecondaryNodeBootServicesPrePhaseForStandbyStep         (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          configureSecondaryNodeSetLocationRoleOnStandbyStep               (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);

                void          checkHaPeerSyncStatusStep                                        (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          checkHaPeerSyncPostPhaseStep                                     (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context);
                void          configureClusterSecondaryHaPeerMessageCallback                   (FrameworkStatus frameworkStatus, WaveConfigureClusterSecondaryHaPeerMessage *pWaveConfigureClusterSecondaryHaPeerMessage, void *pContext);
                void          configureSecondaryHaPeerPrePhaseStep                             (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          configureSecondaryHaPeerPrePhaseCallback                         (FrameworkStatus frameworkStatus, WaveConfigureClusterSecondaryHaPeerPhase1Message *pWaveConfigureClusterSecondaryHaPeerPhase1Message, void *pContext);
                void          configureSecondaryHaPeerPostPhaseStep                            (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context);
                void          configureSecondaryHaPeerPostPhaseCallback                        (FrameworkStatus frameworkStatus, WaveConfigureClusterSecondaryHaPeerPhase3Message *pWaveConfigureClusterSecondaryHaPeerPhase3Message, void *pContext);
                void          configureSecondaryNodePhase1MessageHandler                       (WaveConfigureClusterSecondaryPhase1Message *pWaveConfigureClusterSecondaryPhase1Message);
                void          configureSecondaryNodeHaPeerPhase1MessageHandler                 (WaveConfigureClusterSecondaryHaPeerPhase1Message *pWaveConfigureClusterSecondaryHaPeerPhase1Message);
                void          updateLocationRoleStepInPhase1                                   (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);

                void          configureSecondaryNodePhase2MessageHandler                       (WaveConfigureClusterSecondaryPhase2Message *pWaveConfigureClusterSecondaryPhase2Message);
                void          updateLocationRoleStepInPhase2                                   (SecondaryNodeClusterPhase2Context *pSecondaryNodeClusterPhase2Context);
                void          configureSecondaryNodePhase2BootServicesPostPhaseStep            (SecondaryNodeClusterPhase2Context *pSecondaryNodeClusterPhase2Context);
                void          configureSecondaryNodePhase2ReplaceNodeIfNeededStep              (SecondaryNodeClusterPhase2Context *pSecondaryNodeClusterPhase2Context);
                void          configureSecondaryNodePhase2ConfigureThisLocationStep            (SecondaryNodeClusterPhase2Context *pSecondaryNodeClusterPhase2Context);
                void          configureSecondaryNodePhase3SendStartHearBeat                    (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context);
                void          configureSecondaryNodePhase3ExecutePostBootStep                  (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context);
                void          configureSecondaryNodePhase3MessageHandler                       (WaveConfigureClusterSecondaryPhase3Message *pWaveConfigureClusterSecondaryPhase3Message);
                void          configureSecondaryNodeHaPeerPhase3MessageHandler                 (WaveConfigureClusterSecondaryHaPeerPhase3Message *pWaveConfigureClusterSecondaryHaPeerPhase3Message);
                void          updateLocationRoleStepInPhase3                                   (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context);
                void          updateLocationRoleStepPhase3Complete                             (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context);
                void          configureSecondaryNodePhase3BootServicesAfterPostPhaseStep       (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context);
                void          configureSecondaryNodePhase3ReplayLocalOnlyConfigIfRequiredStep  (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context);
                void          updateListOfSecondariesMessageHandler                            (FrameworkObjectManagerUpdateListOfSecondariesMessage *pFrameworkObjectManagerUpdateListOfSecondariesMessage);
                void          updateListOfSecondariesSetupContextStep                          (UpdateListOfSecondariesContext *pUpdateListOfSecondariesContext);
                void          updateListOfSecondariesAddKnownLocationsStep                     (UpdateListOfSecondariesContext *pUpdateListOfSecondariesContext);
                void          updateListOfSecondariesConnectToNewKnownLocationsStep            (UpdateListOfSecondariesContext *pUpdateListOfSecondariesContext);
                void          broadcastListOfNewlyAddedNodesStep                               (UpdateListOfSecondariesContext *pUpdateListOfSecondariesContext);
                void          broadcastClusterPhase3StartEvent                                 (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context);
                void          broadcastClusterPhase3CompleteEvent                              (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context);
                void          broadcastNodesAdditionToClusterCompletedEvent                    (CreateClusterWithNodesContext *pCreateClusterWithNodesContext);

                void          broadcastPrimaryChangedEventForPlugins                           (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context);
                void          addNodesToClusterMessageHandler                                  (FrameworkObjectManagerAddNodesToClusterMessage *pFrameworkObjectManagerAddNodesToClusterMessage);
                void          addNodesToClusterValidateStep                                    (AddNodesToClusterContext *pAddNodesToClusterContext);
                void          addNodesToClusterAddKnownLocationsStep                           (AddNodesToClusterContext *pAddNodesToClusterContext);
                void          addNodesToClusterConnectToNewKnownLocationsStep                  (AddNodesToClusterContext *pAddNodesToClusterContext);
                void          addNodesToClusterConfigureNewKnownLocationsStep                  (AddNodesToClusterContext *pAddNodesToClusterContext);
                void          addNodesToClusterConfigureNewKnownLocationsCallback              (FrameworkStatus frameworkStatus, WaveConfigureClusterSecondaryMessage *pWaveConfigureClusterSecondaryMessage, void *pContext);

                void          deleteNodesFromClusterMessageHandler                             (FrameworkObjectManagerDeleteNodesFromClusterMessage *pFrameworkObjectManagerDeleteNodesFromClusterMessage);
                void          deleteNodesFromClusterValidateStep                               (DeleteNodesFromClusterContext *pDeleteNodesFromClusterContext);
                void          deleteNodesFromClusterUnconfigureKnownLocationsStep              (DeleteNodesFromClusterContext *pDeleteNodesFromClusterContext);
                void          deleteNodesFromClusterUnconfigureKnownLocationsCallback          (FrameworkStatus frameworkStatus, FrameworkObjectManagerUnconfigureClusterSecondaryMessage *pFrameworkObjectManagerUnconfigureClusterSecondaryMessage, void *pContext);
                void          deleteNodesFromClusterRemoveKnownLocationsStep                   (DeleteNodesFromClusterContext *pDeleteNodesFromClusterContext);
                void          deleteNodesFromClusterRunFailoverStep                            (DeleteNodesFromClusterContext *pDeleteNodesFromClusterContext);
                void          deleteNodesFromClusterRunFailoverCallback                        (WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext);

                void          unconfigureClusterSecondaryMessageHandler                        (FrameworkObjectManagerUnconfigureClusterSecondaryMessage *pFrameworkObjectManagerUnconfigureClusterSecondaryMessage);
                void          unconfigureClusterSecondaryValidateStep                          (DeleteNodeOnSecondaryContext *pDeleteNodeOnSecondaryContext);
                void          unconfigureClusterSecondarySendStopHeartBeat                     (DeleteNodeOnSecondaryContext *pDeleteNodeOnSecondaryContext);
                void          unconfigureClusterSecondaryDisconnectFromKnownLocationStep       (DeleteNodeOnSecondaryContext *pDeleteNodeOnSecondaryContext);
                void          unconfigureClusterSecondaryDisconnectFromConnectedLocationStep   (DeleteNodeOnSecondaryContext *pDeleteNodeOnSecondaryContext);
                void          unconfigureClusterSecondaryUpdateThisLocationStep                (DeleteNodeOnSecondaryContext *pDeleteNodeOnSecondaryContext);
                void          unconfigureClusterSecondaryNodeBootServicesStep                  (DeleteNodeOnSecondaryContext *pDeleteNodeOnSecondaryContext);
                void          unconfigureClusterSecondaryUnconfigureThisLocationStep           (DeleteNodeOnSecondaryContext *pDeleteNodeOnSecondaryContext);
                void          unconfigureClusterSecondaryRunFailoverStep                       (DeleteNodeOnSecondaryContext *pDeleteNodeOnSecondaryContext);
                void          unconfigureClusterBroadcastLocalNodeDeletedEventStep             (DeleteNodeOnSecondaryContext *pDeleteNodeOnSecondaryContext);
                void          unconfigureClusterSecondaryRunFailoverCallback                   (WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext);

                void          destroyClusterMessageHandler                                     (FrameworkObjectManagerDestroyClusterMessage *pFrameworkObjectManagerDestroyClusterMessage);
                void          destroyClusterMessageHandlerCallback                             (DestroyClusterAsynchronousContext *pDestroyClusterAsynchronousContext);
                void          destroyClusterAsynchronousHandler                                (DestroyClusterAsynchronousContext *pDestroyClusterAsynchronousContext);
                void          destroyClusterValidateStep                                       (DestroyClusterContext *pDestroyClusterContext);
                void          destroyClusterGetKnownLocationsStep                              (DestroyClusterContext *pDestroyClusterContext);
                void          destroyClusterUnconfigureKnownLocationsStep                      (DestroyClusterContext *pDestroyClusterContext);
                void          destroyClusterUnconfigureKnownLocationsCallback                  (FrameworkStatus frameworkStatus, FrameworkObjectManagerUnconfigureClusterSecondaryMessage *pFrameworkObjectManagerUnconfigureClusterSecondaryMessage, void *pContext);
                void          destroyClusterDeleteHeartBeatToKnownLocationsStep                (DestroyClusterContext *pDestroyClusterContext);
                void          destroyClusterTerminateClientConnectionsForKnownLocationsStep    (DestroyClusterContext *pDestroyClusterContext);
                void          destroyClusterRemoveKnownLocationsStep                           (DestroyClusterContext *pDestroyClusterContext);
                void          destroyClusterUnconfigureSelfStep                                (DestroyClusterContext *pDestroyClusterContext);
                void          destroyClusterRunFailoverStep                                    (DestroyClusterContext *pDestroyClusterContext);
                void          destroyClusterRunFailoverCallback                                (WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext);
                void          destroyClusterBroadcastDeleteClusterEventStep                    (DestroyClusterContext *pDestroyClusterContext);

//Methods on the Primary to process Rejoin
                void          rejoinNodesToClusterMessageHandler                               (FrameworkObjectManagerRejoinNodesToClusterMessage *pFrameworkObjectManagerRejoinNodesToClusterMessage);
                void          rejoinNodesToClusterValidateStep                                 (RejoinNodesToClusterContext *pRejoinNodesToClusterContext);
                void          rejoinNodesToClusterConnectToNodesStep                           (RejoinNodesToClusterContext *pRejoinNodesToClusterContext);
                void          rejoinNodesToClusterRejoinClusterSecondariesStep                 (RejoinNodesToClusterContext *pRejoinNodesToClusterContext);
                void          rejoinNodesToClusterRejoinClusterSecondaryCallback               (FrameworkStatus frameworkStatus, FrameworkObjectManagerRejoinClusterSecondaryMessage *pFrameworkObjectManagerRejoinClusterSecondaryMessage, void *pContext);
                void          rejoinNodesToClusterRejoinClusterSecondariesPhase1Step           (RejoinNodesToClusterContext *pRejoinNodesToClusterContext);
                void          rejoinNodesToClusterRejoinClusterSecondariesPhase1StepCallback   (FrameworkStatus frameworkStatus, WaveRejoinClusterSecondaryPhase1Message *pWaveRejoinClusterSecondaryPhase1Message, void *pContext);
                void          rejoinNodesToClusterRejoinClusterSecondariesPhase2Step           (RejoinNodesToClusterContext *pRejoinNodesToClusterContext);
                void          rejoinNodesToClusterRejoinClusterSecondariesPhase2StepCallback   (FrameworkStatus frameworkStatus, WaveRejoinClusterSecondaryPhase2Message *pWaveRejoinClusterSecondaryPhase2Message, void *pContext);
                void          failoverforNodesFailedInRejoinPhase2                             (RejoinNodesToClusterContext *pRejoinNodesToClusterContext);
                void          failoverforNodesFailedInRejoinPhase2Callback                     (WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext);
                void          rejoinNodesToClusterRejoinClusterSecondariesPhase3Step           (RejoinNodesToClusterContext *pRejoinNodesToClusterContext);
                void          rejoinNodesToClusterRejoinClusterSecondariesPhase3StepCallback   (FrameworkStatus frameworkStatus, WaveRejoinClusterSecondaryPhase3Message *pWaveRejoinClusterSecondaryPhase3Message, void *pContext);
                void          failoverforNodesFailedInRejoinPhase3Callback                     (WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext);
//Methods on the Secondary for handling Rejoin
                void          rejoinClusterSecondaryMessageHandler                             (FrameworkObjectManagerRejoinClusterSecondaryMessage *pFrameworkObjectManagerRejoinClusterSecondaryMessage);
                void          rejoinClusterSecondaryHaPeerMessageHandler                       (FrameworkObjectManagerRejoinClusterSecondaryHaPeerMessage *pFrameworkObjectManagerRejoinClusterSecondaryHaPeerMessage);
                void          rejoinClusterSecondaryHaPeerMessageCallback                      (FrameworkStatus frameworkStatus, FrameworkObjectManagerRejoinClusterSecondaryHaPeerMessage *pFrameworkObjectManagerRejoinClusterSecondaryHaPeerMessage, void *pContext);
                void          rejoinSecondaryHaPeerPrePhaseStep                                (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          rejoinSecondaryHaPeerPrePhaseCallback                            (FrameworkStatus frameworkStatus, WaveRejoinClusterSecondaryHaPeerPhase1Message *pWaveRejoinClusterSecondaryHaPeerPhase1Message, void *pContext);
                void          rejoinSecondaryHaPeerPostPhaseStep                               (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context);
                void          rejoinSecondaryHaPeerPostPhaseCallback                           (FrameworkStatus frameworkStatus, WaveRejoinClusterSecondaryHaPeerPhase3Message *pWaveRejoinClusterSecondaryHaPeerPhase3Message, void *pContext);
                void          rejoinSecondaryNodeValidateStep                                  (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          rejoinSecondaryNodeValidateVersionStep                           (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          rejoinSecondaryNodeValidateServicesStep                          (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          rejoinSecondaryNodeConnectToPrimaryStep                          (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          rejoinSecondaryNodeShutdownServicesStep                          (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          rejoinSecondaryNodeNotifyHaPeerStep                              (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          rejoinSecondaryNodeConfigureThisLocationStep                     (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          rejoinSecondaryNodeBootServicesPrePhaseStep                      (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          rejoinSecondaryNodeSetLocationRoleOnStandbyStep                  (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          rejoinClusterSecondaryPhase1MessageHandler                       (WaveRejoinClusterSecondaryPhase1Message *pWaveRejoinClusterSecondaryPhase1Message);
                void          rejoinClusterSecondaryHaPeerPhase1MessageHandler                 (WaveRejoinClusterSecondaryHaPeerPhase1Message *pWaveRejoinClusterSecondaryHaPeerPhase1Message);
                void          rejoinClusterSecondaryPhase2MessageHandler                       (WaveRejoinClusterSecondaryPhase2Message *pWaveRejoinClusterSecondaryPhase2Message);
                void          rejoinClusterSecondaryPhase3MessageHandler                       (WaveRejoinClusterSecondaryPhase3Message *pWaveRejoinClusterSecondaryPhase3Message);
                void          rejoinClusterSecondaryHaPeerPhase3MessageHandler                 (WaveRejoinClusterSecondaryHaPeerPhase3Message *pWaveRejoinClusterSecondaryHaPeerPhase3Message);
                void          updateLocationRoleStepInRejoinPhase1                             (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          updateLocationRoleStepInRejoinPhase2                             (SecondaryNodeClusterPhase2Context *pSecondaryNodeClusterPhase2Context);
                void          updateLocationRoleStepInRejoinPhase3                             (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context);
                void          updateLocationRoleStepInRejoinPhase3Complete                     (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context);
                void          rejoinSecondaryNodePhase2BootServicesPostPhaseStep               (SecondaryNodeClusterPhase2Context *pSecondaryNodeClusterPhase2Context);
                void          rejoinSecondaryNodePhase3BootServicesAfterPostPhaseStep          (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context);
                void          detachFromClusterMessageHandler                                  (FrameworkObjectManagerDetachFromClusterMessage *pFrameworkObjectManagerDetachFromClusterMessage);
                void          detachFromClusterMessageHandlerCallback                          (DetachFromClusterAsynchronousContext *pDetachFromClusterAsynchronousContext);
                void          detachFromClusterAsynchronousHandler                             (DetachFromClusterAsynchronousContext *pDetachFromClusterAsynchronousContext);
                void          detachFromClusterValidateStep                                    (DetachFromClusterContext *pDetachFromClusterContext);
                void          detachFromClusterTerminateClientConnectionsForKnownLocationsStep (DetachFromClusterContext *pDetachFromClusterContext);
                void          detachFromClusterDisconnectFromKnownLocationsStep                (DetachFromClusterContext *pDetachFromClusterContext);
                void          detachFromClusterUnconfigureThisLocationStep                     (DetachFromClusterContext *pDetachFromClusterContext);
                void          detachFromClusterRunFailoverStep                                 (DetachFromClusterContext *pDetachFromClusterContesxt);
                void          detachFromClusterRunFailoverCallback                             (WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext);

                void          lostHeartBeatMessageHandler                                      (FrameworkObjectManagerLostHeartBeatMessage *pFrameworkObjectManagerLostHeartBeatMessage);
                void          lostHeartBeatStep                                                (HeartBeatLostContext *pHeartBeatLostContext);
                void          lostHeartBeatPrimaryUncontrolledFailoverCallback                 (WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext);
                void          lostHeartBeatSecondaryUncontrolledFailoverCallback               (WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext);
                void          lostHeartBeatSecondaryControlledFailoverCallback                 (WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext);
                void          lostHeartBeatCleanupClusterDestroyClusterCallback                (DestroyClusterAsynchronousContext *pDestroyClusterAsynchronousContext);
                void          lostHeartBeatCleanupClusterDetachFromClusterCallback             (DetachFromClusterAsynchronousContext *pDetachFromClusterAsynchronousContext);

                void          primaryChangedMessageHandler                                     (FrameworkObjectManagerPrimaryChangedMessage *pFrameworkObjectManagerPrimaryChangedMessage);
                void          primaryChangedHaPeerMessageHandler                               (FrameworkObjectManagerPrimaryChangedHaPeerMessage *pFrameworkObjectManagerPrimaryChangedHaPeerMessage);
                void          primaryChangedValidateStep                                       (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void          primaryChangedNotifyHaPeerStep                                   (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          primaryChangedNotifyHaPeerMessageCallback                        (FrameworkStatus frameworkStatus, FrameworkObjectManagerPrimaryChangedHaPeerMessage *pFrameworkObjectManagerPrimaryChangedHaPeerMessage, void *pContext);
                void          primaryChangedHaPeerPrePhaseStep                                 (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          primaryChangedHaPeerPrePhaseCallback                             (FrameworkStatus frameworkStatus, FrameworkObjectManagerPrimaryChangedHaPeerPhase1Message *pFrameworkObjectManagerPrimaryChangedHaPeerPhase1Message, void *pContext);
                void          primaryChangedHaPeerPostPhaseStep                                (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context);
                void          primaryChangedHaPeerPostPhaseCallback                            (FrameworkStatus frameworkStatus, FrameworkObjectManagerPrimaryChangedHaPeerPhase3Message *pFrameworkObjectManagerPrimaryChangedHaPeerPhase3Message, void *pContext);
                void          primaryChangedStopHeartBeatToOldPrimayStep                       (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void          primaryChangedRemoveOldPrimaryLocationStep                       (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void          primaryChangedUpdatePrimaryDetailsStep                           (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          primaryChangedEmptyDatabaseStep                                  (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          primaryChangedLoadDatabaseFromPrimaryDatabaseStep                (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          primaryChangedPhase1MessageHandler                               (FrameworkObjectManagerPrimaryChangedPhase1Message *pFrameworkObjectManagerPrimaryChangedPhase1Message);
                void          primaryChangedHaPeerPhase1MessageHandler                         (FrameworkObjectManagerPrimaryChangedHaPeerPhase1Message *pFrameworkObjectManagerPrimaryChangedHaPeerPhase1Message);
                void          primaryChangedPhase2MessageHandler                               (FrameworkObjectManagerPrimaryChangedPhase2Message *pFrameworkObjectManagerPrimaryChangedPhase2Message);
                void          primaryChangedPhase3MessageHandler                               (FrameworkObjectManagerPrimaryChangedPhase3Message *pFrameworkObjectManagerPrimaryChangedPhase3Message);
                void          primaryChangedHaPeerPhase3MessageHandler                         (FrameworkObjectManagerPrimaryChangedHaPeerPhase3Message *pFrameworkObjectManagerPrimaryChangedHaPeerPhase3Message);
                void          prepareStandbyAfterClusterPhaseSync                              (SecondaryNodeClusterPhase3Context *pSecondaryNodeClusterPhase3Context);
                void          saveWaveConfigurationStep                                       (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void          resetNodeForClusterMergeHandler                                  (FrameworkObjectManagerResetNodeToUnconfirmRole *pFrameworkObjectManagerResetNodeToUnconfirmRole);
                void          stopHeartBeatToNode                                              (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void          disconnectFromAllNodes                                           (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void          disconnectFromAllConnectedNodes                                  ();
                void          resetNodeShutdownServicesStep                                    (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void          configureNodeForResetAndStartServices                            (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void          triggerUncontrolledFailoverForRemainingNodes                     (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void          triggerUncontrolledFailoverForRemainingNodesCallback             (WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext);
                void          removePreviousDatabaseBackupFile                                 (WaveLinearSequencerContext *pWaveLinearSequencerContext);

                void          startExternalStateSynchronizationHandler                         (FrameworkObjectManagerStartExternalStateSynchronizationMessage *pFrameworkObjectManagerStartExternalStateSynchronizationMessage);
                void          startSlotFailoverHandler                                         (FrameworkObjectManagerStartSlotFailoverMessage *pFrameworkObjectManagerStartSlotFailoverMessage);

                void          getKnownRemoteLocations                                          (vector<LocationId> &remoteLocaionsVector);
                void          getKnownLocations                                                (vector<LocationId> &knownLocaionsVector);
                void          getConnectedLocations                                            (vector<LocationId> &connectedLocaionsVector);
                void          getFullyConnectedLocations                                       (vector<LocationId> &connectedLocaionsVector);
                void          getKnownSubLocations                                             (vector<LocationId> &knownSubLocaionsVector);
                bool          isAKnownLocation                                                 (LocationId locationId);

                void          initializeLastUsedLocationId                                     ();
                LocationId    getNextLocationId                                                ();
        static  void          setIsInstantiated                                                (const bool &isInstantiated);

                LocationId    getLastUsedLocationIdInWaveFrameworkObjectManager               () const;
                void          setLastUsedLocationIdInWaveFrameworkObjectManager               (const LocationId &locationId);

        virtual WaveMessage *createMessageInstance                                            (const UI32 &operationCode);
                void          secondaryNodeClusterFailureStep                                  (SecondaryNodeClusterContext *pSecondaryNodeClusterContext);
                void          primaryNodeClusterSuccessStep                                    (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void          primaryNodeClusterFailureStep                                    (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void          cleanupManageObject                                              (LocationId locationId);
                void          deleteObjects                                                    (vector<WaveManagedObject *> *pResults);

                void          setActivationCompleted                                           (bool isActivationCompleted);
                bool          getActivationCompleted                                           ();
                string        getActivationCompletedTimeStamp                                  ();

                void          setWarmHaRecoveryPreparationInProgress                           (const bool &isWarmRecovery);
                bool          isWarmHaRecoveryPreparationInProgress                            ();

                void          incrementLineCardPostBootCount                                   ();
                UI32          getNumberOfLineCardPostBootCurrentlyRunning                      ();
                void          decrementLineCardPostBootCount                                   ();

                void          setPostBootStarted                                               (bool isPostBootStarted);
                bool          getPostBootStarted                                               ();
                string        getPostBootStartedTimeStamp                                      ();

                void          setPostBootCompleted                                             (bool isPostBootCompleted); 
                bool          getPostBootCompleted                                             ();
                string        getPostBootCompletedTimeStamp                                    ();

                void          setConfigReplayStarted                                           (bool isConfigreplayStarted);
                bool          getConfigReplayStarted                                           ();
                string        getConfigReplayStartedTimeStamp                                  ();

                void          setConfigReplayCompleted                                         (bool isConfigReplayCompleted);
                bool          getConfigReplayCompleted                                         ();
                string        getConfigReplayCompletedTimeStamp                                ();

                bool          getConfigReplayInProgress                                        ();

                void          setFileReplayStarted                                             (bool isFileReplayStarted);
                bool          getFileReplayStarted                                             ();
                string        getFileReplayStartedTimeStamp                                    ();

                void          setFileReplayCompleted                                           (bool isFileReplayCompleted);
                bool          getFileReplayCompleted                                           ();
                string        getFileReplayCompletedTimeStamp                                  ();

                bool          getFileReplayInProgress                                          ();

                void          fileReplayCompletedProcessing                                    (bool fileReplayCompleted);
                void          startFileReplayEndAgent                                          ();
                
                void          setNodeReadyForAllCommands                                       (bool isNodeReadyForAllCommands);
                bool          getNodeReadyForAllCommands                                       ();                
                string        getNodeReadyForAllCommandsTimeStamp                              ();

                void          generateTimeStamp                                                (string & timeString);
                void          startClusterPhaseTimer                                           (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void          stopClusterPhaseTimer                                            (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void          clusterPhaseTimerCallback                                        (TimerHandle timerHandle, void * pContext);

                void          createDatabaseBackupBuffer                                       (char * &pDatabaseBackupBuffer, SI32 &sizeOfBackupFile);
                ResourceId    createBufferForFileToSync                                        (const string &filenameToSync, char* &pfileBuffer, UI32 &sizeOfFileBuffer );  
                ResourceId    createFileForSyncBuffer                                          (const string &filenameToSync, char* &pfileBuffer, UI32 &sizeOfFileBuffer ); 

                bool          getIsPostBootNeededDuringRejoin                                  ();
                void          setIsPostBootNeededDuringRejoin                                  (const bool isPostBootNeededDuringRejoin);
                /** FIPSZeroize
                *  setter for isNodeZeroized flag. This flag set only when FIPSZeroize message is receeived.
                */
                void          setNodeZeroized                                                  (bool nodeZeroized);
                void          removeFailedLocationsFromKnownLocationsHandler                   (FrameworkObjectManagerRemoveKnownLocationsMessage *pFrameworkObjectManagerRemoveKnownLocationsMessage);
                void          raslogAssert                                                     (const string &file, const string &function, const UI32 line, const string &assertString);
                void          prepareNodeForHASupportHandler                                   ();
                void          prepareFrameworkForHaRecoveryMessageHandler                      (FrameworkObjectManagerPrepareForHaFailoverWithPersistentConfiguration *pFrameworkObjectManagerPrepareForHaFailoverWithPersistentConfiguration);
                void          pausePersistence                                                 ();
                void          resumePersistence                                                ();
                void          resumeDatabaseOperation                                          ();

                // For Cluster support for DB Upgrade
                //void          setTableIdsChangedForSchemaCompatibilityFlag                      (bool tableIdsChanged);
                //bool          getTableIdsChangedForSchemaCompatibilityFlag                      ();

                void          setAuxilliaryTableDetailsForSchemaConversion                      (vector<string> oldAuxilliaryTables, vector<string> newAuxilliaryTables, vector<string> parentTables, vector<string> relatedToTables);
                void          getAuxilliaryTableDetailsForSchemaConversion                      (vector<string>& oldAuxilliaryTables, vector<string>& newAuxilliaryTables, vector<string>& parentTables, vector<string>& relatedToTables);
                void          revertTableIdsIfRequired                                          ();

                void          storeConfigurationIntentMessageHandler                            (FrameworkObjectManagerStoreConfigurationIntentMessage *pFrameworkObjectManagerStoreConfigurationIntentMessage);
                void          removeConfigurationIntentMessageHandler                           (FrameworkObjectManagerRemoveConfigurationIntentMessage *pFrameworkObjectManagerRemoveConfigurationIntentMessage);

        static  void          storeConfigurationIntentStaticMessageHandler                      (FrameworkObjectManagerStoreConfigurationIntentMessage *pFrameworkObjectManagerStoreConfigurationIntentMessage);
        static  void          removeConfigurationIntentStaticMessageHandler                     (FrameworkObjectManagerRemoveConfigurationIntentMessage *pFrameworkObjectManagerRemoveConfigurationIntentMessage);
                
                void          rollbackStandbyOnActiveRollbackHandler                            (FrameworkObjectManagerRollbackStandbyOnActiveRollbackMessage *pFrameworkObjectManagerRollbackStandbyOnActiveRollbackMessage);
                void          replayConfigFileMessageHandler                                    (WaveFrameworkReplayConfigMessage *pWaveFrameworkReplayConfigMessage);

    protected :
        WaveFrameworkConfigurationWorker   *getPConfigurationWorker                               ();
        WaveFinalizeWorker                 *getPFinalizeWorker                                    ();
        WaveFrameworkObjectManagerInitializeWorker *getPInitializeWorker                          ();
    public :
        static  WaveFrameworkObjectManager *getInstance                                           ();
        static  string                       getServiceName                                        ();
        static  WaveServiceId               getWaveServiceId                                     ();
        static  void                         bootWave                                             ();
                void                         configureThisLocationAsLocation                       (SI32 port);
                bool                         addSubLocation                                        (LocationId locationId, string &ipAddress, SI32 port);
                void                         configureThisLocationAsSubLocation                    (LocationId parentLocationId, string &parentIpAddress, SI32 parentPort, LocationId locationId, string &ipAddress, SI32 port);
                void                         initializeServerCommunications                        ();
                void                         initializeClientCommunications                        ();
                bool                         acceptNewConnection                                   (ServerStreamingSocket &newSocket);
                void                         disconnectFromLocation                                (LocationId locationId, const bool &closePeerServerSocket = true);
                void                         disconnectFromLocation                                (const string &ipAddress, const SI32 &port, const bool &closePeerServerSocket = true);
                void                         removeKnownLocation                                   (const LocationId &locationId);
                ResourceId                   connectToLocation                                     (const string &ipAddress, const SI32 &port);
                ResourceId                   upgradeDatabase                                       ();
                void                         startTheWaveServices                                 ();
        static  void                         waitForWaveServicesToFinish                          ();
        static  void                         setFrameworkSequenceType                              (FrameworkSequenceType frameworkSequenceType);
        static  bool                         getIsInstantiated                                     ();
        static  FrameworkSequenceGenerator  &getCurrentFrameworkSequenceGenerator                  ();
        static  void                         setConfigurationFile                                  (const string &configurationFile);
        static  void                         setGlobalConfigurationFile                            (const string &globalConfigurationFile);
        static  void                         setLockFileForConfigurationFile                       (const string &lockFile);
        static  string                       getConfigurationFileName                              ();
        static  string                       getConfigurationBackupFileName                        ();
        static  string                       getGlobalConfigurationFileName                        ();
        static  string                       getGlobalConfigurationTempFileName                    ();
        static  string                       getLockFileForConfigurationFile                       ();
                ResourceId                   saveConfiguration                                     (const bool &syncToStandby);
                ResourceId                   changeWaveConfigurationValidity                      (const bool &validity ); 
        static  void                         configureAsLocation                                   (SI32 port);
        static  void                         configureAsSubLocation                                (LocationId parentLocationId, string &parentIpAddress, SI32 parentPort, LocationId locationId, string &ipAddress, SI32 port);
                void                         resetLocationToPrimary                                ();

        static  void                         acquireBootSynchronizationMutex                       ();
        static  void                         releaseBootSynchronizationMutex                       ();

                void                         dynamicallyExcludeServiceFromClusterCommunications    (const WaveServiceId &waveServiceId);
                bool                         isServiceDynamicallyExcludedFromClusterCommunications (const WaveServiceId &waveServiceId);

        static  void                         excludeServiceForClusterValidationPhase               (const WaveServiceId &waveServiceId);

        static  void                         setIpAddressForThisLocation                           (const string &ipAddressForThisLocation);
        static  string                       getIpAddressForThisLocation                           ();

        static  void                         updateIpAddressForThisLocation                        (const string &ipAddressForThisLocation);

        static  void                         setEthernetInterfaceForThisLocation                   (const string &ethernetInterfaceForThisLocation);
        static  string                       getEthernetInterfaceForThisLocation                   ();

                void                         setIsStartupValid                                     (const bool &isStartupValid);
                bool                         getIsStartupValid                                     ();
                void                         setStartupFileName                                    (const string &startupFileName);
                string                       getStartupFileName                                    () const;
                void                         setStartupFileType                                    (const ResourceId &startupFileType);
                ResourceId                   getStartupFileType                                    () const;

                void                         newPrincipalSelectedAfterFaioverMessageHandler        (FrameworkObjectManagerNewPrincipalEstablishedMessage *pFrameworkObjectManagerNewPrincipalEstablishedMessage);
                void                         validateNewPrincipalSelection                         (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                         processNewPrincipalEstablishedMessage                 (WaveLinearSequencerContext *pWaveLinearSequencerContext);

                void                         secondaryNodeFailureNotificationMessageHandler        (FrameworkObjectManagerSecondaryNodeFailureNotificationMessage *pFrameworkObjectManagerSecondaryNodeFailureNotificationMessage);
                void                         processSecondeyNodeFailureMessage                     (WaveLinearSequencerContext *pWaveLinearSequencerContext);


                bool                         getSecondaryNodeClusterCreationFlag                   ();
                void                         setSecondaryNodeClusterCreationFlag                   (bool secondaryNodeClusterCreationFlag);

                bool                         getPrimaryNodeClusterOperationFlag                    ();
                void                         setPrimaryNodeClusterOperationFlag                    (bool primaryNodeClusterOperationFlag);

                void                         resumePostponedMessages                               ();

                void                         disconnectFromAllNodesHandler                         (FrameworkObjectManagerDisconnectFromAllNodesMessage *pFrameworkObjectManagerDisconnectFromAllNodesMessage);
                void                         disconnectAllKnownLocationStep                        (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                         establishPrincipalAfterClusterRebootHandler           (FrameworkObjectManagerEstablishPrincipalAfterClusterRebootMessage* pFrameworkObjectManagerEstablishPrincipalAfterClusterRebootMessage);
                void                         establishPrincipalAfterClusterRebootStep              (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                 
                void                         invalidateClientStreamingSocketForRemoteLocation      (LocationId locationId);
        static  void                         disconnectFromAllKnownLocations                       (); 
                void                         disconnectFromAllInstanceClientsHandler 			   (FrameworkObjectManagerDisconnectFromAllInstanceClientsMessage *pFrameworkObjectManagerDisconnectFromAllInstanceClientsMessage);
                void                         disconnectAllInstanceClientsStep                      (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                         prepareNodeForWarmRecoveryWithDefaultConfiguration    (FrameworkObjectManagerPrepareForWarmRecoveryWithDefaultConfiguration *pFrameworkObjectManagerPrepareForWarmRecoveryWithDefaultConfiguration);
        static  void                         setGetInstancesFunction                               (GetInstancesFunction getInstancesFunction);
        static  void                         setGetThisSlotInstanceFunction                        (GetThisSlotInstanceFunction getThisSlotInstanceFunction);
        static  void                         setGetInstancesAndSubInstancesFunction                (GetInstancesAndSubInstancesFunction getInstancesAndSubInstancesFunction);
        static  void                         setCreateDummySlotFunction                            (CreateDummySlotFunction createDummySlotFunction);
        static  void                         setRaslogAssertFunction                               (RaslogAssertFunction raslogAssertFunction);

        static  void                         setGetFirmwareVersionFunction                         (GetFirmwareVersionFunction getFirmwareVersionFunction);
        static  void                         setHandleDcmFssConfigUpdateFunction                   (HandleDcmFssConfigUpdateFunction handleDcmFssConfigUpdateFunction);
        static  void                         setSetVcsClusterConfigHandlerFunction                 (SetVcsClusterConfigHandlerFunction setVcsClusterConfigHandlerFunction);
        static  void                         setGetVcsClusterConfigHandlerFunction                 (GetVcsClusterConfigHandlerFunction getVcsClusterConfigHandlerFunction);
        static  void                         setNotifySyncUpdateFailureFunction                    (NotifySyncUpdateFailureFunction notifySyncUpdateFailureFunction);
                bool                         notifySyncUpdateFailure                               (const ResourceId &reason);
        static  void                         setNotifyClusterReadyStateFunction                    (NotifyClusterReadyStateFunction notifyClusterReadyStateFunction);
                void                         notifyClusterReadyState                               (bool &readyState);
                bool                         getNeedNotifyClusterReadyState                        ();
                void                         setNeedNotifyClusterReadyState                        (bool needNotifyClusterReadyState);

                /** 
                * returns if FIPSZeroize flag value. This flag is set when FIPSZeroize message is received. 
                */
                bool                         isNodeZeroized                                        ();
                
                /** FIPSZeroize
                *  Handler for FIPSZeroize
                */
                void                         zeroizeForFIPSMessageHandler                          (ZeroizeForFIPSMessage*);
                void                         validateStandaloneStep                                (ZeroizeForFIPSLinearSequencerContext *pContext);
                void                         notifyAllClientSessionsStep                           (ZeroizeForFIPSLinearSequencerContext *pContext);
                void                         triggerFIPSZeroizeStep                                (ZeroizeForFIPSLinearSequencerContext *pContext);
                void                         zeroizeSuccessStep                                    (ZeroizeForFIPSLinearSequencerContext *pZeroizeForFIPSLinearSequencerContext);

         static string                       getFIPSZeroizeFile                                    ();
                void                         validateAndZeroizeAtBoot                              ();

                void                         setIsDBRestoreIncomplete                              (bool dbRestoreIncomplete);
                bool                         getIsDBRestoreIncomplete                              ();
                
                void                         setDbConversionStatus                                 (ResourceId dbConversionStatus);
                ResourceId                   getDbConversionStatus                                 () const;

                void                         rollbackCfgFile                                       ();
                string                       getFirmwareVersion                                    ();
                int                          handleDcmFssConfigUpdate                              (void *dcmConfigData);
                ResourceId                   setVcsClusterConfigData                               (VcsClusterConfiguration *pDcmVcsClusterConfigData, const UI32 &context);
                void                         getVcsClusterConfigData                               (VcsClusterConfiguration *pDcmVcsClusterConfigData, const UI32 &context);
                bool                         getIsSyncDumpCompleted                                ();
		static	bool						 isExternalStateSynchronizationRequired (WaveServiceId waveServiceId);
		static	void						 addToExternalStateSynchronizationRequiredList (WaveServiceId waveServiceId);
                UI32                         getSyncState                                          ();
                void                         setSyncState                                          (const UI32& syncState);
                UI32                         getStandbySyncState                                   ();
        static void                          addWaveThreadId                                      (const WaveThreadId &waveThreadId);
        static void                          removeWaveThreadId                                   (const WaveThreadId &waveThreadId);
        static void                          getAllWaveThreads                                    (map<WaveThreadId, WaveThreadId> &waveThreadsMap);
        static void                          deleteAllWaveThreads                                 ();
                bool                         getWaveConfigurationValidity                         ();
               ClientStreamingSocket*        getClientStreamingSocketForRemoteLocation             (LocationId locationId);
        static  SI32                         getLocationPort                                       ();
                void                         resetFrameworkConfigurationToDefault                  ();
    // Now the data members

    private :
               WaveFrameworkObjectManagerInitializeWorker     *m_pInitializeWorker;
               WaveFinalizeWorker                             *m_pWaveFinalizeWorker;
               WaveFrameworkConfigurationWorker               *m_pConfigurationWorker;
               WaveFrameworkFailoverWorker                    *m_pWaveFrameworkFailoverWorker;
               WaveFrameworkObjectManagerServiceControlWorker *m_pWaveFrameworkObjectManagerServiceControlWorker;
               WaveFrameworkObjectManagerPostbootWorker       *m_pWaveFrameworkObjectManagerPostbootWorker;
               WaveFrameworkObjectManagerPostPersistentBootWorker *m_pWaveFrameworkObjectManagerPostPersistentBootWorker;
               WaveFrameworkObjectManagerHaSyncWorker         *m_pWaveFrameworkObjectManagerHaSyncWorker;
               LocationBase                                    *m_pThisLocation;
               LocationId                                       m_lastUsedLocationId;

               map<WaveServiceId, WaveServiceId>              m_servicesToBeExcludedForClusterCommunications;
               WaveMutex                                       m_servicesToBeExcludedForClusterCommunicationsLock;

		static vector<WaveServiceId>                           m_externalStateSynchronizationRequiredList;
		static WaveMutex										m_externalStateSynchronizationRequiredListLock;

        static string                                           m_ipAddressForThisLocation;
        static WaveMutex                                       m_ipAddressForThisLocationMutex;

        static string                                           m_ethernetInterfaceForThisLocation;

               bool                                             m_isStartupValid;
               string                                           m_startupFileName;
               ResourceId                                       m_startupFileType;
               bool                                             m_secondaryNodeClusterCreationFlag;
               WaveMutex                                       m_secondaryNodeClusterCreationFlagMutex;

               bool                                             m_primaryNodeClusterOperationFlag;
               WaveMutex                                       m_primaryNodeClusterOperationFlagMutex;

               bool                                             m_activationCompleted;
               string                                           m_activationCompletedTimeStamp;
               WaveMutex                                       m_activationCompletedMutex;

               //Status related Port boot progress
               bool                                             m_postBootStarted;
               string                                           m_postBootStartedTimeStamp;
               bool                                             m_postBootCompleted;
               string                                           m_postBootCompletedTimeStamp;
               WaveMutex                                       m_postBootProgressMutex;
               UI32                                             m_numberOfLineCardPostBootInProgress;
               WaveMutex                                       m_lineCardPostBootMutex;

               bool                                             m_configReplayStarted;
               string                                           m_configReplayStartedTimeStamp;
               bool                                             m_configReplayCompleted;
               string                                           m_configReplayCompletedTimeStamp;
               WaveMutex                                       m_configReplayInProgressMutex;

               bool                                             m_fileReplayStarted;
               string                                           m_fileReplayStartedTimeStamp;
               bool                                             m_fileReplayCompleted;
               string                                           m_fileReplayCompletedTimeStamp;
               WaveMutex                                       m_fileReplayInProgressMutex;

               bool                                             m_nodeReadyForAllCommands;
               string                                           m_nodeReadyForAllCommandsTimeStamp;
               WaveMutex                                       m_nodeReadyForAllCommandsMutex;
               TimerHandle                                      m_clusterPhaseTimerHandler;

               bool                                             m_isPostBootNeededDuringRejoin;
               bool                                             m_needNotifyClusterReadyState;

               WaveMutex                                       m_nodeZeroizedMutex;
               /** FIPSZeroize
               *  FIPSZeroize Flag
               */
               bool                                             m_nodeZeroized;
               bool                                             m_isDBRestoreIncomplete;
               ResourceId                                       m_dbConversionStatus;
               ResourceId                                       m_tableIdsChangedForSchemaCompatibility;

               vector<string>                                   m_oldAuxilliaryTableNamesBeforeConversion;
               vector<string>                                   m_newAuxilliaryTableNamesAfterConversion;
               vector<string>                                   m_parentTableNamesForAuxilliaryTables;
               vector<string>                                   m_relatedToTableNamesForAuxilliaryTables;

               bool                                             m_isWarmHaRecoveryPreparationInProgress;
               WaveMutex                                       m_warmHaRecoveryPreparationInProgressMutex;


        static GetInstancesFunction                             m_getInstancesFunction;
        static GetInstancesAndSubInstancesFunction              m_getInstancesAndSubInstancesFunction;
        static GetThisSlotInstanceFunction                      m_getThisSlotInstanceFunction;
        static CreateDummySlotFunction                          m_createDummySlotFunction;
        static RaslogAssertFunction                             m_raslogAssertFunction;
        static GetFirmwareVersionFunction                       m_getFirmwareVersionFunction;
        static HandleDcmFssConfigUpdateFunction                 m_handleDcmFssConfigUpdateFunction;
        static SetVcsClusterConfigHandlerFunction               m_setVcsClusterConfigHandlerFunction;
        static GetVcsClusterConfigHandlerFunction               m_getVcsClusterConfigHandlerFunction;
        static NotifySyncUpdateFailureFunction                  m_notifySyncUpdateFailureFunction;
        static NotifyClusterReadyStateFunction                  m_notifyClusterReadyStateFunction;
    protected :
    public :

    friend class WaveFrameworkThread;
    friend class WaveObjectManager;
    friend class FrameworkToolKit;
    friend class WaveFrameworkObjectManagerInitializeWorker;
    friend class PersistentWaveBootAgent;
    friend class HaStandbyWaveBootAgent;
    friend class PersistentWithDefaultWaveBootAgent;
    friend class PersistentWithDefaultForHABootAgent;
    friend class WaveFailoverAgent;
    friend class WavePostbootAgent;
    friend class RecoverWaveBootAgent;
    friend class WaveFrameworkObjectManagerPostPersistentBootWorker;
    friend class WaveFrameworkObjectManagerHaSyncWorker;
    friend class QueryUtils;
    friend class WaveFrameworkConfigurationWorker;

    friend void                          trace              (TraceLevel traceLevel, const string &stringToTrace);
    friend void                          tracePrintf        (TraceLevel traceLevel, const bool &addNewLine, const bool &suppressPrefix, const char * const pFormat, ...);
    friend void                          tracePrintf        (TraceLevel traceLevel, const char * const pFormat, ...);

    friend void                          waveAssert        (bool isAssertRequired, const char *pFileName, UI32 lineNumber);
};

}

#endif //WAVEFRAMEWORKOBJECTMANAGER_H
