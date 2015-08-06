/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMOBJECTMANAGER_H
#define PRISMOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveElement.h"
#include "Framework/MultiThreading/WaveThread.h"
#include <map>
#include <vector>
#include <set>
#include <string>
#include "Framework/Types/Types.h"
#include "Framework/Utils/PrismAsynchronousContext.h"
#include "Framework/Utils/DatabaseQueryCursor.h"
#include "Framework/Messaging/Local/WaveEvent.h"
#include "Framework/ObjectModel/ObjectId.h"
#include "Framework/ObjectRelationalMapping/CompositionEntry.h"
#include "Framework/ObjectRelationalMapping/RelationshipEntry.h"
#include "Framework/ObjectModel/WaveManagedObjectAsynchronousPluginContext.h"
#include "Framework/ObjectRelationalMapping/ModifiedManagedObjectSchemaDifference.h"
#include "Framework/ObjectModel/WaveManagedObjectQueryContextBase.h"
//#include "Framework/Persistence/WaveConfigurationAttributes.h"

using namespace std;

namespace WaveNs
{

class WaveThread;
class WaveWorker;
class WaveEvent;
class PrismInitializeObjectManagerMessage;
class PrismListenForEventsObjectManagerMessage;
class PrismInstallObjectManagerMessage;
class PrismEnableObjectManagerMessage;
class PrismBootObjectManagerMessage;
class PrismUpgradeObjectManagerMessage;
class PrismHaInstallObjectManagerMessage;
class PrismHaBootObjectManagerMessage;
class PrismShutdownObjectManagerMessage;
class PrismUninstallObjectManagerMessage;
class PrismDisableObjectManagerMessage;
class PrismUninitializeObjectManagerMessage;
class PrismPingObjectManagerMessage;
class WaveLinearSequencerContext;
class WaveLinearSequencerContextForUpgradePhase;
class PrismSynchronousLinearSequencerContext;
class TimerObjectManagerAddTimerMessage;
class PrismTimerExpiredObjectManagerMessage;
class WaveObjectManagerCollectValidationDataMessage;
class WaveObjectManagerValidateClusterCreationMessage;
class WaveObjectManagerSendValidationResultsMessage;
class DatabaseObjectManagerExecuteQueryMessage;
class PrismPauseObjectManagerMessage;
class PrismResumeObjectManagerMessage;
class PrismSetCpuAffinityObjectManagerMessage;
class WaveAsynchronousContextForBootPhases;
class WaveAsynchronousContextForPostbootPhase;
class WaveAsynchronousContextForShutDownPhases;
class WaveAsynchronousContextForExternalStateSynchronization;
class WaveAsynchronousContextForConfigReplayEnd;
class WaveAsynchronousContextForFileReplayEnd;
class WaveAsynchronousContextForSlotFailover;
class WaveAsynchronousContextForMultiPartitionCleanup;
class WaveAsynchronousContextForUpgradePhase;
class PrismHeartbeatFailureObjectManagerMessage;
class PrismExternalStateSynchronizationObjectManagerMessage;
class PrismConfigReplayEndObjectManagerMessage;
class PrismFileReplayEndObjectManagerMessage;
class PrismSlotFailoverObjectManagerMessage;
class PrismMultiPartitionCleanupObjectManagerMessage;
class WaveObjectManagerBackendSyncUpMessage;
class WaveObjectManagerHaSyncCollectValidationDataMessage;
class WaveObjectManagerHaSyncValidateDataMessage;
class WaveObjectManagerHaSyncSendValidationResultsMessage;

class WaveManagedObject;
class WaveManagedObjectQueryContext;
class WaveManagedObjectSynchronousQueryContext;
class WaveManagedObjectSynchronousQueryContextForDeletion;
class WaveManagedObjectSynchronousQueryContextForUpdate;
class DatabaseQueryCursor;

class WaveManagedObjectLoadOperationalDataWorker;
class PrismPostbootWorker;
class WaveSendToClusterContext;
class WaveSendToClientsContext;

class MessageHistory;
class WaveObjectManagerMessageHistoryConfigMessage;
class WaveObjectManagerMessageHistoryDumpMessage;

class WaveManagedObjectUpdateWorker;
class WaveManagedObjectCreateWorker;
class WaveManagedObjectDeleteWorker;
class WaveClientDataObjectGetWorker;
class FailoverAsynchronousContext;

class WaveDebugInformationWorker;
class WaveAsynchronousContextForDebugInformation;
class WaveObjectManagerStatisticsTracker;

class UnifiedClientBackendDetails;
class WaveLinearSequencerContextForShutdownPhase;
class WaveSendMulticastContext;
class InterLocationMulticastMessage;

class WaveObjectManagerCommitTransactionContext;
class CliBlockContext;
class WaveConfigurationAttributes;

class WaveDeliverBrokerPublishMessageWorker;

class WaveObjectManager : public WaveElement
{
    private :
        class WaveMessageResponseContext
        {
            private :
            protected :
            public :
                              WaveMessageResponseContext       (WaveMessage *pWaveMessage, WaveElement *pWaveMessageSender, WaveMessageResponseHandler pWaveMessageSenderCallback, void *pWaveMessageSenderContext);
                void          executeResponseCallback           (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, bool isMessageRecalled = false);
                void          executeResponseCallback           (FrameworkStatus frameworkStatus);
                void          setIsMessageTimedOut              (bool isMessageTimedOut);
                bool          getIsMessageTimedOut              ();
                WaveMessage *getPWaveMessage                  ();
                WaveMessage *getPInputMessageInResponseContext ();
                void          setPInputMessageInResponseContext (WaveMessage *pWaveMessage);
                bool          getIsTimerStarted                 () const;
                void          setIsTimerStarted                 (const bool &isTimerStarted);
                TimerHandle   getTimerHandle                    () const;
                void          setTimerHandle                    (const TimerHandle &timerHandle);

            // Now the data members

            private :
                WaveMessage                *m_pWaveMessage;
                WaveElement                *m_pWaveMessageSender;
                WaveMessageResponseHandler  m_pWaveMessageSenderCallback;
                void                        *m_pWaveMessageSenderContext;
                bool                         m_isMessageTimedOut;
                WaveMessage                *m_pInputMessageInResponseContext;
                bool                         m_isTimerStarted;
                TimerHandle                  m_timerHandle;

            protected :
            public :
        };

        class PrismOperationMapContext
        {
            private :
            protected :
            public :
                     PrismOperationMapContext (WaveElement *pWaveElement, WaveMessageHandler pWaveMessageHandler);
                void executeMessageHandler    (WaveMessage *&pWaveMessage);

            // Now the data members

            private :
                WaveElement        *m_pWaveElementThatHandlesTheMessage;
                WaveMessageHandler  m_pWaveMessageHandler;

            protected :
            public :
        };

        class WaveEventMapContext
        {
            private :
            protected :
            public :
                     WaveEventMapContext (WaveElement *pWaveElement, WaveEventHandler pWaveEventHandler);
                void executeEventHandler  (const WaveEvent *&pWaveEvent);

            // Now the data members

            private :
                WaveElement      *m_pWaveElementThatHandlesTheEvent;
                WaveEventHandler  m_pWaveEventHandler;

            protected :
            public :
        };

        class WaveEventListenerMapContext
        {
            private :
            protected :
            public :
                 WaveEventListenerMapContext (const WaveServiceId &eventListenerServiceId, const LocationId &eventListenerLocationId);
                ~WaveEventListenerMapContext ();

                WaveServiceId getEventListenerServiceId  () const;
                LocationId     getEventListenerLocationId () const;

            // Now the data members

            private :
                WaveServiceId m_eventListenerSericeId;
                LocationId     m_eventListenerLocationId;

            protected :
            public :
        };

        class WaveManagedObjectForUpdate
        {
            public:
                virtual         ~WaveManagedObjectForUpdate ();
                virtual void    getSqlForUpdate             (string &sql) = 0;
        };

        class WaveManagedObjectUpdateSingle: public WaveManagedObjectForUpdate
        {
            private :
            protected :
            public :
                                WaveManagedObjectUpdateSingle   (WaveManagedObject *updateObject);
                virtual         ~WaveManagedObjectUpdateSingle  ();
                        void    getSqlForUpdate                 (string &sql);
            // Now the data members
            private :
                        WaveManagedObject*  m_pUpdateWaveManagedObject;
            protected :
            public :

        };

        class WaveManagedObjectUpdateMultiple: public WaveManagedObjectForUpdate
        {
            private :
            protected :
            public :
                                WaveManagedObjectUpdateMultiple     (WaveManagedObjectSynchronousQueryContextForUpdate * pWaveManagedObjectSynchronousQueryContextForUpdate);
                virtual         ~WaveManagedObjectUpdateMultiple    ();
                        void    getSqlForUpdate                     (string &sql);
            // Now the data members
            private :
                        WaveManagedObjectSynchronousQueryContextForUpdate*  m_pWaveManagedObjectSynchronousQueryContextForUpdate;
            protected :
            public :

        };

        class WaveManagedObjectForDelete
        {
            public:
                virtual         ~WaveManagedObjectForDelete ();
                virtual void    getSqlForDelete             (string &sql) = 0;
        };

        class WaveManagedObjectDeleteSingle: public WaveManagedObjectForDelete
        {
            private :
            protected :
            public :
                                WaveManagedObjectDeleteSingle   (ObjectId deleteObjectId);
                virtual         ~WaveManagedObjectDeleteSingle  ();
                        void    getSqlForDelete                 (string &sql);
            // Now the data members
            private :
                        ObjectId m_deleteObjectId;
            protected :
            public :

        };

        class WaveManagedObjectDeleteMultiple: public WaveManagedObjectForDelete
        {
            private :
            protected :
            public :
                                WaveManagedObjectDeleteMultiple     (WaveManagedObjectSynchronousQueryContextForDeletion* pWaveManagedObjectSynchronousQueryContextForDeletion);
                                WaveManagedObjectDeleteMultiple     (WaveManagedObjectSynchronousQueryContextForDeletion* pWaveManagedObjectSynchronousQueryContextForDeletion, bool deleteOnlyCompositions, set<string> relationsSet);
                                WaveManagedObjectDeleteMultiple     ( WaveManagedObjectSynchronousQueryContextForDeletion* pWaveManagedObjectSynchronousQueryContextForDeletion,
                                                bool partialDeleteFromVectorComposition, string parentClassName, string compositionName);
                virtual         ~WaveManagedObjectDeleteMultiple    ();
                        void    getSqlForDelete                     (string &sql);
            // Now the data members
            private :
                        WaveManagedObjectSynchronousQueryContextForDeletion*  m_pWaveManagedObjectSynchronousQueryContextForDeletion;
                        bool        m_deleteOnlyCompositions;
                        set<string> m_relationsSet;
                        bool        m_partialDeleteFromVectorComposition;
                        string      m_parentClassName;
                        string      m_compositionName;
            protected :
            public :

        };

        class WaveBrokerPublishMessageHandlerContext
        {
            private :
            protected :
            public :
                                                 WaveBrokerPublishMessageHandlerContext (WaveBrokerPublishMessageHandler waveBrokerPublishMessageHandler, WaveElement *pSubscriber);
                                                ~WaveBrokerPublishMessageHandlerContext ();

                WaveBrokerPublishMessageHandler  getWaveBrokerPublishMessageHandler     ();
                WaveElement                    *getPSubscriber                         ();

            // Now the data members

            private :
                WaveBrokerPublishMessageHandler  m_waveBrokerPublishMessageHandler;
                WaveElement                    *m_pSubscriber;
            protected :
            public :
        };

                void                initializeHandler                            (PrismInitializeObjectManagerMessage *pInitializeMessage);
                void                initializeInitializeWorkersStep              (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                initializeInitializeWorkersStepCallback      (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                void                initializeInitializeSelfStep                 (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                initializeInitializeSelfStepCallback         (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        virtual void                initialize                                   (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

                void                listenForEventsHandler                       (PrismListenForEventsObjectManagerMessage *pListenForEventsMessage);
                void                listenForEventsWorkersStep                   (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                listenForEventsWorkersStepCallback           (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                void                listenForEventsSelfStep                      (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                listenForEventsSelfStepCallback              (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        virtual void                listenForEvents                              (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

                void                installHandler                               (PrismInstallObjectManagerMessage *pInstallMessage);
                void                installInstallWorkersStep                    (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                installInstallWorkersStepCallback            (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                void                installInstallSelfStep                       (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                installInstallSelfStepCallback               (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        virtual void                install                                      (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

        static  void                addServiceToEnabledServicesList              (const WaveServiceId &prismServiceId);
        static  void                removeServiceFromEnabledServicesList         (const WaveServiceId &prismServiceId);

                void                enableHandler                                (PrismEnableObjectManagerMessage *pEnableMessage);
                void                enableEnableWorkersStep                      (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                enableEnableWorkersStepCallback              (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                void                enableEnableSelfStep                         (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                enableEnableSelfStepCallback                 (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        virtual void                enable                                       (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

                void                upgradeHandler                               (PrismUpgradeObjectManagerMessage *pUpgradeMessage);
                void                upgradeDefaultValueStep                      (WaveLinearSequencerContextForUpgradePhase *pWaveLinearSequencerContextForUpgradePhase);
                void                upgradeUpgradeWorkersStep                    (WaveLinearSequencerContextForUpgradePhase *pWaveLinearSequencerContextForUpgradePhase);
                void                upgradeUpgradeWorkersStepCallback            (WaveAsynchronousContextForUpgradePhase *pWaveAsynchronousContextForUpgradePhase);
                void                upgradeUpgradeSelfStep                       (WaveLinearSequencerContextForUpgradePhase *pWaveLinearSequencerContextForUpgradePhase);
                void                upgradeUpgradeSelfStepCallback               (WaveAsynchronousContextForUpgradePhase *pWaveAsynchronousContextForUpgradePhase);
        virtual void                upgrade                                      (WaveAsynchronousContextForUpgradePhase *pWaveAsynchronousContextForUpgradePhase);

                void                bootHandler                                  (PrismBootObjectManagerMessage *pBootMessage);
                void                bootBootWorkersStep                          (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                bootBootWorkersStepCallback                  (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                void                bootBootSelfStep                             (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                bootBootSelfStepCallback                     (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        virtual void                boot                                         (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

                void                hainstallHandler                             (PrismHaInstallObjectManagerMessage *pHaInstallMessage);
                void                hainstallInstallWorkersStep                  (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                hainstallInstallWorkersStepCallback          (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                void                hainstallInstallSelfStep                     (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                hainstallInstallSelfStepCallback             (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        virtual void                hainstall                                    (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

                void                habootHandler                                (PrismHaBootObjectManagerMessage *pHaBootMessage);
                void                habootBootWorkersStep                        (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                habootBootWorkersStepCallback                (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                void                habootBootSelfStep                           (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                habootBootSelfStepCallback                   (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        virtual void                haboot                                       (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

        virtual void                postboot                                     (WaveAsynchronousContextForPostbootPhase *pWaveAsynchronousContextForPostbootPhase);
        virtual void                postbootCallback                             (GetHardwareConfigurationDetailsForPostbootContext *pGetHardwareConfigurationDetailsForPostbootContext);
        virtual ResourceId          postbootValidateAllOwnedManagedClassNames    (const string passName, vector<string> &managedObjectNamesInPass);

                void                shutdownHandler                              (PrismShutdownObjectManagerMessage *pShutdownMessage);
                void                shutdownShutdownWorkersStep                  (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                shutdownShutdownWorkersStepCallback          (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases);
                void                shutdownShutdownSelfStep                     (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                shutdownShutdownSelfStepCallback             (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases);
        virtual void                shutdown                                     (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases);
                void                notifyStep                                   (WaveLinearSequencerContextForShutdownPhase *pWaveLinearSequencerContext);
                void                uninstallHandler                             (PrismUninstallObjectManagerMessage *pUninstallMessage);
                void                uninstallUninstallWorkersStep                (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                uninstallUninstallWorkersStepCallback        (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases);
                void                uninstallUninstallSelfStep                   (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                uninstallUninstallSelfStepCallback           (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases);
        virtual void                uninstall                                    (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases);

                void                disableHandler                               (PrismDisableObjectManagerMessage *pDisableMessage);
                void                disableUnlistenEventsStep                    (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                disableDisableWorkersStep                    (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                disableDisableWorkersStepCallback            (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases);
                void                disableDisableSelfStep                       (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                disableDisableSelfStepCallback               (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases);
        virtual void                disable                                      (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases);

                void                uninitializeHandler                          (PrismUninitializeObjectManagerMessage *pUninitializeMessage);
                void                uninitializeUninitializeWorkersStep          (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                uninitializeUninitializeWorkersStepCallback  (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases);
                void                uninitializeUninitializeSelfStep             (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                uninitializeUninitializeSelfStepCallback     (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases);
        virtual void                uninitialize                                 (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases);

                void                destructHandler                              (PrismDestructObjectManagerMessage *pDestructMessage);
                void                destructDestructWorkersStep                  (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                destructDestructWorkersStepCallback          (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases);
                void                destructDestructSelfStep                     (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                destructDestructSelfStepCallback             (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases);
        virtual void                destruct                                     (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases);

                void                heartbeatFailureHandler                      (PrismHeartbeatFailureObjectManagerMessage *pHearbeatFailureMessage);
                void                heartbeatFailureWorkersStep                  (WaveLinearSequencerContext  *pWaveLinearSequencerContext);
                void                heartbeatFailureWorkersStepCallback          (PrismAsynchronousContext     *pPrismAsynchronousContext);
                void                heartbeatFailureSelfStep                     (WaveLinearSequencerContext  *pWaveLinearSequencerContext);
                void                heartbeatFailureSelfStepCallback             (PrismAsynchronousContext     *pPrismAsynchronousContext);
        virtual void                heartbeatFailure                             (PrismAsynchronousContext     *pPrismAsynchronousContext);

                void                configReplayEndHandler                       (PrismConfigReplayEndObjectManagerMessage *pConfigReplayEndMessage);
                void                configReplayEndWorkersStep                   (WaveLinearSequencerContext  *pWaveLinearSequencerContext);
                void                configReplayEndWorkersStepCallback           (WaveAsynchronousContextForConfigReplayEnd *pWaveAsynchronousContextForConfigReplayEnd);
                void                configReplayEndSelfStep                      (WaveLinearSequencerContext  *pWaveLinearSequencerContext);
                void                configReplayEndSelfStepCallback              (WaveAsynchronousContextForConfigReplayEnd *pWaveAsynchronousContextForConfigReplayEnd);
        virtual void                configReplayEnd                              (WaveAsynchronousContextForConfigReplayEnd *pWaveAsynchronousContextForConfigReplayEnd);

                void                fileReplayEndHandler                         (PrismFileReplayEndObjectManagerMessage *pFileReplayEndMessage);
                void                fileReplayEndWorkersStep                     (WaveLinearSequencerContext  *pWaveLinearSequencerContext);
                void                fileReplayEndWorkersStepCallback             (WaveAsynchronousContextForFileReplayEnd *pWaveAsynchronousContextForFileReplayEnd);
                void                fileReplayEndSelfStep                        (WaveLinearSequencerContext  *pWaveLinearSequencerContext);
                void                fileReplayEndSelfStepCallback                (WaveAsynchronousContextForFileReplayEnd *pWaveAsynchronousContextForFileReplayEnd);
        virtual void                fileReplayEnd                                (WaveAsynchronousContextForFileReplayEnd *pWaveAsynchronousContextForFileReplayEnd);

                void                slotFailoverHandler                          (PrismSlotFailoverObjectManagerMessage *pSlotFailoverMessage);
                void                slotFailoverWorkersStep                      (WaveLinearSequencerContext  *pWaveLinearSequencerContext);
                void                slotFailoverWorkersStepCallback              (WaveAsynchronousContextForSlotFailover *pWaveAsynchronousContextForSlotFailover);
                void                slotFailoverSelfStep                         (WaveLinearSequencerContext  *pWaveLinearSequencerContext);
                void                slotFailoverSelfStepCallback                 (WaveAsynchronousContextForSlotFailover *pWaveAsynchronousContextForSlotFailover);
        virtual void                slotFailover                                 (WaveAsynchronousContextForSlotFailover *pWaveAsynchronousContextForSlotFailover);

                void                multiPartitionCleanupHandler                   (PrismMultiPartitionCleanupObjectManagerMessage *pMultiPartitionCleanupMessage);
                void                multiPartitionCleanupWorkersStep               (WaveLinearSequencerContext  *pWaveLinearSequencerContext);
                void                multiPartitionCleanupWorkersStepCallback       (WaveAsynchronousContextForMultiPartitionCleanup *pWaveAsynchronousContextForMultiPartitionCleanup);
                void                multiPartitionCleanupSelfStep                  (WaveLinearSequencerContext  *pWaveLinearSequencerContext);
                void                multiPartitionCleanupSelfStepCallback          (WaveAsynchronousContextForMultiPartitionCleanup *pWaveAsynchronousContextForMultiPartitionCleanup);
        virtual void                multiPartitionCleanup                          (WaveAsynchronousContextForMultiPartitionCleanup *pWaveAsynchronousContextForMultiPartitionCleanup);
        virtual void                multiPartitionPartialCleanup                   (WaveAsynchronousContextForMultiPartitionCleanup *pWaveAsynchronousContextForMultiPartitionCleanup);

                void                externalStateSynchronizationHandler                      (PrismExternalStateSynchronizationObjectManagerMessage *pExternalStateSynchronizationMessage);
                void                externalStateSynchronizationWorkersStep                  (WaveLinearSequencerContext  *pWaveLinearSequencerContext);
                void                externalStateSynchronizationWorkersStepCallback          (WaveAsynchronousContextForExternalStateSynchronization *pWaveAsynchronousContextForExternalStateSynchronization);
                void                externalStateSynchronizationSelfStep                     (WaveLinearSequencerContext  *pWaveLinearSequencerContext);
                void                externalStateSynchronizationSelfStepCallback             (WaveAsynchronousContextForExternalStateSynchronization *pWaveAsynchronousContextForExternalStateSynchronization);
        virtual void                externalStateSynchronization                             (WaveAsynchronousContextForExternalStateSynchronization *pWaveAsynchronousContextForExternalStateSynchronization);
                void                backendSyncUpHandler                         (WaveObjectManagerBackendSyncUpMessage *pPrismHeartbeatFailureObjectManagerMessage);
                void                backendSyncUpWorkersStep                     (WaveLinearSequencerContext  *pWaveLinearSequencerContext);
                void                backendSyncUpWorkersStepCallback             (PrismAsynchronousContext     *pPrismAsynchronousContext);
                void                backendSyncUpSelfStep                        (WaveLinearSequencerContext  *pWaveLinearSequencerContext);
                void                backendSyncUpSelfStepCallback                (PrismAsynchronousContext     *pPrismAsynchronousContext);
        virtual void                backendSyncUp                                (PrismAsynchronousContext     *pPrismAsynchronousContext);
                void                pauseHandler                                 (PrismPauseObjectManagerMessage *pPrismPauseObjectManagerMessage);
                void                resumeHandler                                (PrismResumeObjectManagerMessage *pPrismResumeObjectManagerMessage);

                void                pingHandler                                  (PrismPingObjectManagerMessage *pPingMessage);

                void                setCpuAffinityHandler                        (PrismSetCpuAffinityObjectManagerMessage *pPrismSetCpuAffinityObjectManagerMessage);

                void                clusterCreateCollectValidationDataHandler             (WaveObjectManagerCollectValidationDataMessage *pWaveObjectManagerCollectValidationDataMessage);
                void                clusterCreateCollectValidationDataWorkersStep         (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                clusterCreateCollectValidationDataWorkersStepCallback (PrismAsynchronousContext *pPrismAsynchronousContext);
                void                clusterCreateCollectValidationDataSelfStep            (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                clusterCreateCollectValidationDataSelfStepCallback    (PrismAsynchronousContext *pPrismAsynchronousContext);
        virtual void                clusterCreateCollectValidationData                    (WaveObjectManagerCollectValidationDataMessage *pMessage, PrismAsynchronousContext *pPrismAsynchronousContext);

                void                clusterCreateValidateHandler                          (WaveObjectManagerValidateClusterCreationMessage *pWaveObjectManagerValidateClusterCreationMessage);
                void                clusterCreateValidateWorkersStep                      (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                clusterCreateValidateWorkersStepCallback              (PrismAsynchronousContext *pPrismAsynchronousContext);
                void                clusterCreateValidateSelfStep                         (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                clusterCreateValidateSelfStepCallback                 (PrismAsynchronousContext *pPrismAsynchronousContext);
        virtual void                clusterCreateValidate                                 (WaveObjectManagerValidateClusterCreationMessage *pMessage, PrismAsynchronousContext *pPrismAsynchronousContext);

                void                clusterCreateSendValidationResultsHandler             (WaveObjectManagerSendValidationResultsMessage *pWaveObjectManagerSendValidationResultsMessage);
                void                clusterCreateSendValidationResultsWorkersStep         (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                clusterCreateSendValidationResultsWorkersStepCallback (PrismAsynchronousContext *pPrismAsynchronousContext);
                void                clusterCreateSendValidationResultsSelfStep            (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                clusterCreateSendValidationResultsSelfStepCallback    (PrismAsynchronousContext *pPrismAsynchronousContext);
        virtual void                clusterCreateSendValidationResults                    (WaveObjectManagerSendValidationResultsMessage *pMessage, PrismAsynchronousContext *pPrismAsynchronousContext);

                void                failoverHandler                                       (PrismFailoverObjectManagerMessage *pPrismFailvoerObjectManagerMessage);
                void                failoverWorkersStep                                   (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                failoverWorkersStepCallback                           (FailoverAsynchronousContext *pFailoverAsynchronousContext);
                void                failoverSelfStep                                      (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                failoverSelfStepCallback                              (FailoverAsynchronousContext *pFailoverAsynchronousContext);
        // virtual void                failover                                              (FrameworkObjectManagerFailoverReason failoverReason, vector<LocationId> failedLocationIds, PrismAsynchronousContext *pPrismAsynchronousContext);
        virtual void                failover                                              (FailoverAsynchronousContext *pFailoverAsynchronousContext);

                void                haSyncCollectValidationDataHandler                    (WaveObjectManagerHaSyncCollectValidationDataMessage *pWaveObjectManagerHaSyncCollectValidationDataMessage);
                void                haSyncCollectValidationDataWorkersStep                (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                haSyncCollectValidationDataSelfStep                   (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                haSyncCollectValidationDataSelfStepCallback           (PrismAsynchronousContext *pPrismAsynchronousContext);
        virtual void                haSyncCollectValidationData                           (WaveObjectManagerHaSyncCollectValidationDataMessage *pMessage, PrismAsynchronousContext *pPrismAsynchronousContext);

                void                haSyncValidateDataHandler                             (WaveObjectManagerHaSyncValidateDataMessage *pWaveObjectManagerHaSyncValidateDataMessage);
                void                haSyncValidateDataWorkersStep                         (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                haSyncValidateDataSelfStep                            (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                haSyncValidateDataSelfStepCallback                    (PrismAsynchronousContext *pPrismAsynchronousContext);
        virtual void                haSyncValidateData                                    (WaveObjectManagerHaSyncValidateDataMessage *pMessage, PrismAsynchronousContext *pPrismAsynchronousContext);

                void                haSyncSendValidationResultsHandler                    (WaveObjectManagerHaSyncSendValidationResultsMessage *pWaveObjectManagerHaSyncSendValidationResultsMessage);
                void                haSyncSendValidationResultsWorkersStep                (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                haSyncSendValidationResultsSelfStep                   (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                haSyncSendValidationResultsSelfStepCallback           (PrismAsynchronousContext *pPrismAsynchronousContext);
        virtual void                haSyncSendValidationResults                           (WaveObjectManagerHaSyncSendValidationResultsMessage *pMessage, PrismAsynchronousContext *pPrismAsynchronousContext);

        virtual void                getDebugInformation                                   (WaveAsynchronousContextForDebugInformation *pWaveAsynchronousContextForDebugInformation);
        virtual void                resetDebugInformation                                 (WaveAsynchronousContextForDebugInformation *pWaveAsynchronousContextForDebugInformation);

                void                setAssociatedWaveThread                     (WaveThread *pAssociatedWaveThread);
                bool                isOperationCodeSupported                     (UI32 operationCode);
                bool                isEventOperationCodeSupported                (UI32 eventOperationCode);
                bool                isEventOperationCodeSupportedForListening    (const LocationId &eventSourceLocationId, const WaveServiceId &eventSourceServiceId, const UI32 &eventOperationCode);
                bool                isAKnownMessage                              (UI32 prismMessageId);
                void                handleWaveMessage                           (WaveMessage *pWaveMessage);
                void                handleWaveEvent                             (const WaveEvent *&pWaveEvent);
                void                handleWaveMessageResponse                   (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, bool isMessageRecalled = false);
                void                handleWaveMessageResponseWhenTimeOutExpired (FrameworkStatus frameworkStatus, UI32 prismMessageId);
                void                addWorker                                    (WaveWorker *pWorker);
                void                removeWorker                                 (WaveWorker *pWorker);
        static  bool                isEventAllowedBeforeEnabling                 (const UI32 &eventOperationCode);
        static  bool                canInstantiateServiceAtThisTime              (const string &prismServiceName);

        virtual WaveMessage       *createMessageInstance                        (const UI32 &operationCode);
                WaveMessage       *createMessageInstanceWrapper                 (const UI32 &operationCode);
        virtual WaveEvent         *createEventInstance                          (const UI32 &eventOperationCode);
        virtual WaveManagedObject  *createManagedObjectInstance                  (const string &managedClassName);
                WaveManagedObject  *createManagedObjectInstanceWrapper           (const string &managedClassName);

                void                addEventListener                             (const UI32 &eventOperationCode, const WaveServiceId &listenerWaveServiceId, const LocationId &listenerLocationId);
                void                removeEventListener                          (const UI32 &eventOperationCode, const WaveServiceId &listenerWaveServiceId, const LocationId &listenerLocationId);
                void                getEventListeners                            (const UI32 &eventOperationCode, vector<WaveEventListenerMapContext *> &eventListeners);

                void                trackObjectCreatedDuringCurrentTransaction   (WaveManagedObject *pWaveManagedObject);
                void                trackObjectDeletedDuringCurrentTransaction   (WaveManagedObject *pWaveManagedObject);

        virtual void                tracePrintf                                  (TraceLevel traceLevel, const bool &addNewLine, const bool &suppressPrefix, const char * const pFormat, va_list &variableArguments);
        virtual void                tracePrintf                                  (TraceLevel traceLevel, const char * const pFormat, va_list &variableArguments);

        virtual void                printfToAllWaveClientSessions                (const WaveClientSessionContext &waveClientSessionContext, const char * const pFormat, va_list &variableArguments);

                void                computeDisconnectedNodesIfSurrogateStep      (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                sendPhase1MessageToAllNodesStep              (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                sendPhase1MessageToAllNodesCallback          (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                computeFailedNodesForPhase1Step              (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                sendPhase2MessageToAllNodesIfApplicableStep  (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                sendPhase2MessageToAllNodesIfApplicableCallback (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                computeOverallStatusStep                     (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                waveObjectManagerMessageHistoryConfigMessageHandler (WaveObjectManagerMessageHistoryConfigMessage *pWaveObjectManagerMessageHistoryConfigMessage);
                void                waveObjectManagerMessageHistoryDumpMessageHandler   (WaveObjectManagerMessageHistoryDumpMessage   *pWaveObjectManagerMessageHistoryDumpMessage);
                void                addMessageToMessageHistory                   (WaveMessage *pWaveMessage, WaveMessageHistoryLogType messageHistoryLogType);
                void                addMessageToMessageHistoryCalledFromSend     (WaveMessage *pWaveMessage);
                void                addMessageToMessageHistoryCalledFromReply    (WaveMessage *pWaveMessage);
                void                addMessageToMessageHistoryCalledFromHandle   (WaveMessage *pWaveMessage);
                bool                isServiceStringRegisteredWithService         (const string &serviceString);
                ResourceId          executeMessageReplyDuringSurrogacy           (ManagementInterfaceMessage *pManagementInterfaceMessage, WaveMessageResponseHandler pManagementInterfaceMessageCallback, void *pManagementInterfaceMessageContext = NULL);
                void                sendPhase1MessageToAllInstancesStep          (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                sendPhase1MessageToAllInstancesCallback      (FrameworkStatus frameworkStatus, ManagementInterfaceMessage *pWaveMessage, WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                sendPhase2MessageToAllInstancesIfApplicableStep  (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                sendPhase2MessageToAllInstancesIfApplicableCallback (FrameworkStatus frameworkStatus, ManagementInterfaceMessage *pWaveMessage, WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                computeFailedInstancesForPhase1Step           (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                computeOverallInstancesStatusStep            (WaveLinearSequencerContext *pWaveLinearSequencerContext);

        virtual void                updateTimeConsumedInThisThread                        (const UI32 &operationCode, const UI32 &sequencerStepIndex, const UI32 &numberOfSeconds, const SI32 &numberOfNanoSeconds);
        virtual void                updateRealTimeConsumedInThisThread                    (const UI32 &operationCode, const UI32 &sequencerStepIndex, const UI32 &numberOfSeconds, const SI32 &numberOfNanoSeconds);

                void                clearAllTimingsAccumulatedForSequencerSteps           ();

                void                getAllTimingsAccumulatedForSequencerSteps             (string &allTimingsAccumulatedForSequencerSteps);

        static  bool                isManagedObjectBeingTrackedForCreations               (const string &managedObject);
                WaveWorker         *getPWaveManagedObjectCreateWorker                     ();


               void                 addPartitionNameToSetOfPartitionNamesReferencedInCurrentTransaction (const string &partitionName);
               set<string>         &getSetOfPartitionNamesReferencedInCurrentTransaction                (void);

                void                checkIfUpgradeIsNecessary                                           (const map<string, ModifiedManagedObjectSchemaDifference*>& modifiedMoInSchema);

               ResourceId           sendOneWayForStoringConfigurationIntent                                   (WaveMessage *pWaveMessage);
               ResourceId           sendOneWayForRemovingConfigurationIntent                                  (const UI32 &configurationIntentMessageId);

               void                 deliverWaveBrokerPublishedEvent                                     (const string &brokerName, const string &topicName, WaveBrokerPublishMessage *pWaveBrokerPublishMessage);

    protected :
                bool                getIsEnabled                                 ();
                                                                 WaveObjectManager                            (const string &objectManagerName, const UI32 &stackSize = 0, const vector<UI32> *pCpuAffinityVector = NULL);
                                                                 WaveObjectManager                            (const WaveObjectManager &prismObjectManager);
        virtual                                                 ~WaveObjectManager                            ();
                string                                           getName                                      () const;
                WaveObjectManager                              &operator =                                    (const WaveObjectManager &prismObjectManager);
                void                                             addOperationMap                              (UI32 operationCode, WaveMessageHandler pMessageHandler, WaveElement *pWaveElement = NULL);
                void                                             addServiceIndependentOperationMap            (UI32 operationCode, WaveServiceIndependentMessageHandler pWaveServiceIndependentMessageHandler);
                void                                             addServiceIndependentOperationMap            (UI32 operationCode, ManagementInterfaceServiceIndependentMessageHandler pManagementInterfaceServiceIndependentMessageHandler);
                void                                             removeServiceIndependentOperationMap         (UI32 operationCode);
                void                                             removeOperationMap                           (const UI32 &operationCode);
        virtual void                                             addEventType                                 (const UI32 &eventOperationCode);
        virtual void                                             listenForEvent                               (WaveServiceId prismServiceId, UI32 sourceOperationCode, WaveEventHandler pWaveEventHandler, WaveElement *pWaveElement = NULL, const LocationId &sourceLocationId = 0);
        virtual void                                             unlistenEvents                               ();
                void                                             addResponseMap                               (UI32 prismMessageId, WaveMessageResponseContext *pWaveMessageResponseContext);
                WaveMessageResponseContext                     *removeResponseMap                            (UI32 prismMessageId);
                PrismOperationMapContext                        *getWaveMessageHandler                       (UI32 operationCode, UI32 messageHandlerServiceCode = 0, UI32 thisServiceId = 0);
                WaveEventMapContext                            *getWaveEventHandler                         (const LocationId &eventSourceLocationId, const WaveServiceId &eventSourceServiceId, const UI32 &eventOperationCode);
                WaveObjectManager::WaveMessageResponseContext *getResponseContext                            (UI32 prismMessageId);
                void                                             setIsEnabled                                 (bool isEnabled);
        virtual TraceClientId                                    getTraceClientId                             ();

                void                                             addManagedClass                              (const string &managedClassName, WaveElement *pOwnerForInstantiation = NULL);
                void                                             addManagedClassWithoutOwnership              (const string &managedClassName);
        static  void                                             addOwnerForManagedClass                      (const string &managedClassName, WaveObjectManager *pWaveObjectManager);
        static  WaveObjectManager                               *getOwnerForManagedClass                      (const string &managedClassName);
                ResourceId                                       ValidateAllOwnedManagedClassNames            ( const vector<string> &managedObjectNames );


        virtual WaveMessageStatus                                postToRemoteLocation                         (WaveMessage *pWaveMessage);
        virtual WaveMessageStatus                                postToRemoteLocation                         (InterLocationMulticastMessage *pWaveMessage, set<LocationId> locationsToSent);
        virtual WaveMessageStatus                                postToHaPeerLocation                         (WaveMessage *pWaveMessage);
        virtual WaveMessageStatus                                send                                         (WaveMessage *pWaveMessage, WaveMessageResponseHandler pWaveMessageCallback, void *pWaveMessageContext, UI32 timeOutInMilliSeconds = 0, LocationId locationId = 0, WaveElement *pWaveMessageSender = NULL);
                void                                             sendTimerExpiredCallback                     (TimerHandle timerHandle, void *pContext);
        virtual WaveMessageStatus                                sendOneWay                                   (WaveMessage *pWaveMessage, const LocationId &locationId = 0);
        virtual WaveMessageStatus                                sendOneWayToFront                            (WaveMessage *pWaveMessage, const LocationId &locationId = 0);
        virtual WaveMessageStatus                                sendSynchronously                            (WaveMessage *pWaveMessage, const LocationId &locationId = 0);
                ResourceId                                       sendSynchronouslyForBackEndAttributesMap     ( GetHardwareConfigurationDetailsForPostbootContext *pContext );
                ResourceId                                       sendSynchronouslyForAGroup                   ( GetHardwareConfigurationDetailsForPostbootContext *pContext );

        virtual bool                                             isBeingSurrogated                            ();

		/**
		 @addtogroup PartialSuccess
         @{
		 */

		/**
		 @brief sendToWaveCluster sends the message to all the nodes in the cluster. The message to be sent can be set
				in WaveSendToClusterContext. Similarly partialSuccess flag can be set to true in WaveSendToClusterContext
				before calling sendToWaveCluster.\n

         <b>Update</b>: Return status is now enhanced based on new flag m_returnSuccessForPartialSuccessFlag see below
			for more details.\n

		 @return if m_returnSuccessForPartialSuccessFlag is set then\n\n
				 WAVE_MESSAGE_SUCCES is returned if all or any node succeeds.\n
				 WAVE_MESSAGE_ERROR_FAILED_ON_ALL_NODES is returned if all nodes fail.\n\n
				 If m_returnSuccessForPartialSuccessFlag is not set then\n
				 WAVE_MESSAGE_SUCCESS is returned only if all nodes succeed else returns WAVE_MESSAGE_ERROR_FAILED_ON_ALL_NODES.\n

		 @see WaveSendToClusterContext
		 */
        virtual void                                             sendToWaveCluster                                  (WaveSendToClusterContext *pWaveSendToClusterContext);

        virtual void                                             sendMulticast                                      (WaveSendMulticastContext *pWaveSendMulticastContext);
                void                                             performSendMulticast                               (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                                             performSendMulticastLocalCallback                  (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, void *pContext);
                void                                             performSendMulticastRemoteCallback                 (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, void *pContext);

		/**
		 @}
		 */
        virtual void                                             sendOneWayToWaveCluster                            (WaveSendToClusterContext *pWaveSendToClusterContext);

        virtual WaveMessageStatus                                recall                                             (WaveMessage *pWaveMessage);
                WaveMessageStatus                                recallButDoNotDeleteResponseMap                    (WaveMessage *pWaveMessage);
        virtual WaveMessageStatus                                reply                                              (WaveMessage *pWaveMessage);
        virtual WaveMessageStatus                                broadcast                                          (WaveEvent *pWaveEvent);
        virtual WaveMessageStatus                                reply                                              (const WaveEvent *&pWaveEvent);

        virtual void                                             trace                                              (TraceLevel traceLevel, const string &stringToTrace);
        virtual void                                             tracePrintf                                        (TraceLevel traceLevel, const bool &addNewLine, const bool &suppressPrefix, const char * const pFormat, ...);
        virtual void                                             tracePrintf                                        (TraceLevel traceLevel, const char * const pFormat, ...);
        virtual void                                             waveAssert                                        (bool isAssertNotRequired, const char *pFileName, UI32 lineNumber);
        virtual ResourceId                                       startTimer                                         (TimerHandle &timerHandle, timeval &startInterval, timeval &periodicInterval, PrismTimerExpirationHandler pPrismTimerExpirationCallback, void *pPrismTimerExpirationContext = NULL, WaveElement *pPrismTimerSender = NULL);
        virtual ResourceId                                       startTimer                                         (TimerHandle &timerHandle,UI32 timeInMilliSeconds, PrismTimerExpirationHandler pPrismTimerExpirationCallback, void *pPrismTimerExpirationContext = NULL, WaveElement *pPrismTimerSender = NULL);
        void                                                     timerExpiredHandler                                (PrismTimerExpiredObjectManagerMessage *pTimerExpiredMessage);
        virtual ResourceId                                       deleteTimer                                        (TimerHandle timerHandle);
        virtual ResourceId                                       deleteAllTimersForService                          ();

        virtual void                                             holdMessages                                       ();
        virtual void                                             holdHighPriorityMessages                           ();
        virtual void                                             holdEvents                                         ();
        virtual void                                             holdAll                                            ();
        virtual void                                             unholdMessages                                     ();
        virtual void                                             unholdHighPriorityMessages                         ();
        virtual void                                             unholdEvents                                       ();
        virtual void                                             unholdAll                                          ();

        virtual UI32                                             getNumberOfPendingTimerExpirationMessages          ();
        virtual UI32                                             getNumberOfPendingNormalMessages                   ();
        virtual UI32                                             getNumberOfPendingHighPriorityMessages             ();

        virtual bool                                             isALocalPrismService                               ();

                void                                             registerEventListenerHandler                       (WaveObjectManagerRegisterEventListenerMessage *pWaveObjectManagerRegisterEventListenerMessage);

                void                                             setupPartitionForMOsBeingCommitted                 (vector<WaveManagedObject *> *&partitionManagedObjectsForGarbageCollection);

        virtual void                                             startTransaction                                   ();
        virtual bool                                             isTransactionInProgress                            ();
        virtual ResourceId                                       commitTransaction                                  (WaveObjectManagerCommitTransactionContext *pWaveObjectManagerCommitTransactionContext = NULL);
        virtual void                                             rollbackTransaction                                ();
        virtual void                                             addWaveConfigEntry                                 (Attribute *attribute);
        virtual void                                             updateWaveConfigEntry                              (Attribute *attribute);
        virtual void                                             getWaveConfigEntry                                 (string &configName, Attribute *attribute, bool &configFound);
        virtual void                                             updateWaveManagedObject                            (WaveManagedObject *pWaveManagedObject);
        virtual void                                             updateMultipleWaveManagedObjects                   (WaveManagedObjectSynchronousQueryContextForUpdate *pWaveManagedObjectSynchronousQueryContextForUpdate);
        virtual void                                             deleteWaveManagedObject                            (const ObjectId &objectId);
        virtual void                                             deleteWaveManagedObject                            (WaveManagedObjectSynchronousQueryContextForDeletion *pWaveManagedObjectSynchronousQueryContextForDeletion);
        virtual void                                             deleteMultipleWaveManagedObjects                   (WaveManagedObjectSynchronousQueryContextForDeletion *pWaveManagedObjectSynchronousQueryContextForDeletion);

        /**
        * @brief Deletes the compositions of MO's matching the passed query context. The objects themselves are
        *        not deleted.
        *        The compositions passed for deletions must support canBeEmpty. Otherwise this API will assert.
        * @param pWaveManagedObjectSynchronousQueryContextForDeletion - query context of the MO's whose compositions
        *        need to be deleted.
        * @param relationsSet - set of compositions to be deleted.
        *        For deleting all compositions pass empty set, or don't pass this parameter at all.
        * @retval void - Void or Empty.
        */
        virtual void                                             deleteManagedObjectCompositions                    (WaveManagedObjectSynchronousQueryContextForDeletion *pWaveManagedObjectSynchronousQueryContextForDeletion, const set<string> relationsSet = set<string>());

        /**
        * @brief Deletes the compositions of the MO with passed objectId. The object itself is not deleted.
        *        The compositions passed for deletions must support canBeEmpty. Otherwise this API will assert.
        * @param objectId - Object Id MO's whose compositions need to be deleted.
        * @param relationsSet - set of compositions to be deleted.
        *        For deleting all compositions pass empty set, or don't pass this parameter at all.
        * @retval void - Void or Empty.
        */
        virtual void                                             deleteManagedObjectCompositions                    (const ObjectId &objectId, const set<string> relationsSet = set<string>());

        virtual void                                             deletePartialManagedObjectCompositions             (const string &parentClassName, const string &compositionName, WaveManagedObjectSynchronousQueryContextForDeletion *pQueryContextForDeletionOnChildMO);

        virtual bool                                             isManagedClassSupported                            (const string &managedClass);
        virtual void                                             addRelationship                                    (const string &parentClassName, const string &childClassName, const string &relationshipName, const ObjectId &parentObjectId, const ObjectId &childObjectId);
        virtual void                                             deleteRelationship                                 (const string &parentClassName, const string &childClassName, const string &relationshipName, const ObjectId &parentObjectId, const ObjectId &childObjectId);
        virtual void                                             addToComposition                                   (const string &parentClassName, const string &childCalssName, const string &compositionName, const ObjectId &parentObjectId, const ObjectId &childObjectId);
        virtual void                                             deleteFromComposition                              (const string &parentClassName, const string &childCalssName, const string &compositionName, const ObjectId &parentObjectId, const ObjectId &childObjectId);
        virtual void                                             addToAssociation                                   (const string &parentClassName, const string &childCalssName, const string &associationName, const ObjectId &parentObjectId, const ObjectId &childObjectId);
        virtual void                                             deleteFromAssociation                              (const string &parentClassName, const string &childCalssName, const string &associationName, const ObjectId &parentObjectId, const ObjectId &childObjectId);

        virtual void                                             query                                              (WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext);
                void                                             queryCallback                                      (FrameworkStatus frameworkStatus, DatabaseObjectManagerExecuteQueryMessage *pDatabaseObjectManagerExecuteQueryMessage, void *pContext);
        virtual vector<WaveManagedObject *>                     *querySynchronouslyLocalManagedObjectsForLocationId (const LocationId &locationId, const string &className);
        virtual vector<WaveManagedObject *>                     *querySynchronouslyLocalManagedObjectsForLocationId (const LocationId &locationId, const string &className, const vector<string> &selectFields);
        virtual vector<WaveManagedObject *>                     *querySynchronouslyLocalManagedObjectsForLocationId (const LocationId &locationId, WaveManagedObjectSynchronousQueryContext *pWaveManagedObjectSynchronousQueryContext);
        virtual vector<WaveManagedObject *>                     *querySynchronously                                 (WaveManagedObjectSynchronousQueryContext *pWaveManagedObjectSynchronousQueryContext);
        virtual vector<WaveManagedObject *>                     *querySynchronously                                 (const string &managedClassName, const string &schema = OrmRepository::getWaveCurrentSchema ());
        virtual vector<WaveManagedObject *>                     *querySynchronously                                 (const string &managedClassName, vector<ObjectId> &objectIds, const string &schema = OrmRepository::getWaveCurrentSchema ());
        virtual vector<WaveManagedObject *>                     *querySynchronouslyByName                           (const string &managedClassName, const string &managedObjectName, const string &schema = OrmRepository::getWaveCurrentSchema ());
        virtual WaveManagedObject                               *queryManagedObject                                 (const ObjectId &managedObjectId, const string &schema = OrmRepository::getWaveCurrentSchema ());
        virtual ResourceId                                       querySynchronouslyForCount                         (WaveManagedObjectSynchronousQueryContext *pWaveManagedObjectSynchronousQueryContext, UI32 &count);
        virtual ResourceId                                       querySynchronouslyForCount                         (const string &managedClassName, UI32 &count, const string &schema = OrmRepository::getWaveCurrentSchema ());
        virtual ResourceId                                       querySynchronouslyForCount                         (const string &managedClassName, const string &fieldName, const string &range, UI32 &count, const string &schema = OrmRepository::getWaveCurrentSchema ());
        virtual vector<WaveManagedObject *>                     *queryManagedObjectAssociatedWithSlot               (const string &managedClassName, UI32 slotNumber, LocationId locationId = 0, const string &schema = OrmRepository::getWaveCurrentSchema ());

        virtual pthread_t                                        getPthreadId                                       ();

                void                                             setTraceLevel                                      (const TraceLevel &traceLevel);

                void                                             setCpuAffinity                                     (const vector<UI32> &cpuAffinityVector);

                void                                             associateWithVirtualWaveObjectManager              (WaveObjectManager *pAssociatedVirtualWaveObjectManager);

        virtual ResourceId                                       sendSynchronouslyToWaveClient                      (const string &waveClientName, ManagementInterfaceMessage *pManagementInterfaceMessage, const SI32 &Instnace = 0);
        virtual WaveMessageStatus                                sendToWaveServer                                   (const UI32 &waveServerId, ManagementInterfaceMessage *pManagementInterfaceMessage, WaveMessageResponseHandler messageCallback, WaveElement *pWaveMessageSender, void *pInputContext, UI32 timeOutInMilliSeconds);
        virtual ResourceId                                       sendToWaveClient                                   (const string &waveClientName, ManagementInterfaceMessage *pManagementInterfaceMessage, WaveMessageResponseHandler pWaveMessageCallback, void *pWaveMessageContext = NULL, UI32 timeOutInMilliSeconds = 0, const SI32 &Instnace = 0);
        virtual void                                             sendToWaveClients                                  (WaveSendToClientsContext *pWaveSendToClientsContext);
        virtual ResourceId                                       sendOneWayToAllWaveClients                         (ManagementInterfaceMessage *pManagementInterfaceMessage);
                bool                                             getAllowAutomaticallyUnlistenForEvents             () const;
                void                                             setAllowAutomaticallyUnlistenForEvents             (const bool &allowAutomaticallyUnlistenForEvents);

                vector<WaveWorker *>                             getWorkers                                         ();   // postboot requires the list of workers on which the function will be invoked
                                                                                                                          // since postboot is derived from WaveWorker & it is friend of WaveObjectManager
                                                                                                                          // we can return the list of worker

        virtual void                                             printfToWaveClientSession                          (const WaveClientSessionContext &waveClientSessionContext, const char * const pFormat, ...);
        virtual void                                             printfToWaveClientSession                          (const WaveClientSessionContext &waveClientSessionContext, const char * const pFormat, va_list &variableArguments);
        virtual void                                             printfToAllWaveClientSessions                      (const WaveClientSessionContext &waveClientSessionContext, const char * const pFormat, ...);
        virtual void                                             printfToWaveClientSessionOver                      (const WaveClientSessionContext &waveClientSessionContext);
        virtual ResourceId                                       addLog                                             (ResourceId logType, ResourceId logDescriptionType, const vector<Attribute *> &logDescriptionArguments);
                void                                             updateMessageHistoryConfig                         (bool requestedMessageHistoryState, UI32 requestedMessageHistoryMaxSize);
                void                                             getMessageHistoryDumpStringVector                  (vector<string> &messageHistoryDumpStringVector);
                void                                             restrictMessageHistoryLogging                      (bool messageHistoryLogInsideSend, bool messageHistoryLogInsideReply, bool messageHistoryLogInsideHandleMessage);
        virtual bool                                             isOperationAllowedBeforeEnabling                   (const UI32 &operationCode);

                void                                             registerLock                                       (const string &serviceString);
                ResourceId                                       acquireLock                                        (const string &serviceString);
                ResourceId                                       releaseLock                                        (const string &serviceString);

                void                                             zeroizeWorkersStep                                 (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                                             zeroizeWorkersStepCallback                         (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases) ;
                void                                             zeroizeSelfStep                                    (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                                             zeroizeSelfStepCallback                            (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases);
                void                                             zeroizeHandler                                     (PrismZeroizeObjectManagerMessage *pMessage);

        virtual void                                             zeroize                                            (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases);

                void                                             databaseSanityCheckHandler                         (WaveObjectManagerDatabaseSanityCheckMessage *pMessage);

                void                                             checkBasicDatabaseSanityWorkersStep                (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                                             checkBasicDatabaseSanityWorkersStepCallback        (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                void                                             checkBasicDatabaseSanitySelfStep                   (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                                             checkBasicDatabaseSanitySelfStepCallback           (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        virtual void                                             dbBasicSanityCheck                                 (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

                void                                             checkIncorrectEntriesWorkersStep                   (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                                             checkIncorrectEntriesWorkersStepCallback           (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                void                                             checkIncorrectEntriesSelfStep                      (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                                             checkIncorrectEntriesSelfStepCallback              (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        virtual void                                             dbInconsistencyCheck                               (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);



        virtual ResourceId                                       updateHardwareSynchronizationState                 (ResourceId hardwareSynchronizationState, const vector<LocationId> &locationIds);
        virtual ResourceId                                       updateHardwareSynchronizationState                 (ResourceId hardwareSynchronizationState, LocationId locationId = 0);
        virtual void                                             postponeMessageHandling                            (WaveMessage *pWaveMessage);
        virtual void                                             resumeAllPostponedMessages                         ();
        virtual ResourceId                                       blockCli                                           (const CliBlockContext &cliBlockContext, const bool &clusterWide);
        virtual ResourceId                                       unblockCli                                         (const CliBlockContext &cliBlockContext, const bool &clusterWide);


        /**
         * This API has few limitations.
         * 1. The MO/class 'className' should not be part of any c++ inheritance hierarchy.
         * 2. The table/MO should have a relation pointing to it or the MO should have 1-m relation point from it.
         *    This means the MO should have its own DerivationsInstances table.
         * So, Use deleteMultipleWaveManagedObjects API to avoid these limitations.
         */
        virtual void                                             deleteAllManagedObjectInstances                     (const string &className);

                WaveObjectManagerStatisticsTracker              *getPWaveObjectManagerStatisticsTracker              () const;

        virtual void                                             populatePostbootMap                                 ();
                void                                             setPostbootMap                                      (const map<string, vector<string> > &postbootManagedObjectNames);
                void                                             getPostbootMap                                      (map<string, vector<string> > &postbootManagedObjectNames) const;

                void                                             getManageObjectNamesFromPostbootMap                 (const string passName, vector<string> &managedObjectNamesInPass );

                bool                                             checkForDuplicationInBackEndAttributesMap           (GetHardwareConfigurationDetailsForPostbootContext *pGetHardwareConfigurationDetailsForPostbootContext );

                void                                             getAssociatedAttributeClone                         (string parentClassName, Attribute *pAttribute, Attribute *&pAssociatedAttribute );

                void                                             postbootForCompositeChild                           (Attribute *pAttribute, GetHardwareConfigurationDetailsForPostbootContext *pGetHardwareConfigurationDetailsForPostbootContext);

                void                                             postbootForChoiceGroup                              (GetHardwareConfigurationDetailsForPostbootContext *pGetHardwareConfigurationDetailsForPostbootContext );

        virtual void                                             applyPartitionFiltersWithPropagatedPartitionContext (WaveManagedObjectQueryContextBase *pWaveManagedObjectQueryContextBase);

        virtual void                                             bootStrapSelf                                       ();

        virtual WaveMessageBrokerStatus                          connectToMessageBroker                              (const string &brokerName, const string &brokerIpAddress, const SI32 &brokerPort);
        virtual WaveMessageBrokerStatus                          subscribeToMessageBroker                            (const string &brokerName, const vector<string> &topicNames, const vector<WaveBrokerPublishMessageHandler> publishMessageHandlers, WaveElement *pSubscriber = NULL);
        virtual WaveMessageBrokerStatus                          subscribeToMessageBroker                            (const string &brokerName, const vector<string> &topicNames, WaveBrokerPublishMessageHandler publishMessageHandler, WaveElement *pSubscriber = NULL);
        virtual WaveMessageBrokerStatus                          subscribeToMessageBroker                            (const string &brokerName, const string &topicName, WaveBrokerPublishMessageHandler publishMessageHandler, WaveElement *pSubscriber = NULL);
        virtual WaveMessageBrokerStatus                          unsubscribeToMessageBroker                          (const string &brokerName, const vector<string> &topicNames, WaveElement *pSubscriber = NULL);
        virtual WaveMessageBrokerStatus                          unsubscribeToMessageBroker                          (const string &brokerName, const string &topicName, WaveElement *pSubscriber = NULL);
        virtual WaveMessageBrokerStatus                          publishToMessageBroker                              (const string &brokerName, WaveBrokerPublishMessage *pWaveBrokerPublishMessage, WaveElement *pSubscriber = NULL);

                bool                                             isAKnownWaveBrokerBasedMessageSubscription          (const string &brokerName, const string &topicName) const;

    public :
        static void                getListOfEnabledServices                    (vector<WaveServiceId> &enabledServices);
        static bool                isServiceEnabled                            (const WaveServiceId &prismServiceId);

        // The following is a special function for consuming all pending messages.  This is not to be used in general.
        // This is being implemented so that the CSCN based application can consume Wave messages as well.

               void                consumeAllPendingMessages                   ();
               WaveMessage       *getPInputMesage                             () const;

               WaveServiceId      getServiceId                                ();

        static void                addClientListeningForManagedObjectCreate    (const string &waveManagedObjectName, const string &waveClientName);
        static void                removeClientListeningForManagedObjectCreate (const string &waveManagedObjectName, const string &waveClientName);

                void               setBackendAttributeMap                      (const map<string, map<string,UnifiedClientBackendDetails*> > &backendAttributeMap);
                void               getBackendAttributeMap                      (map<string, map<string,UnifiedClientBackendDetails*> > &backendAttributeMap) const;
        virtual ResourceId         postbootValidate                            (WaveAsynchronousContextForPostbootPhase *pWaveAsynchronousContextForPostbootPhase);
        virtual WaveManagedObject *createInMemoryManagedObject                 (const  string &className);
                void               getAllOwnedManagedObjectClassNames          (vector<string> &ownedManagedObjectClassNames) const ;
                void               checkMessageAttributesInSerialization       ();

        static  void               endOfLifeService                            (WaveServiceId prismServiceId);
        static  void               bootStrapService                            (WaveServiceId prismServiceId);

    // Now the data members

    private :
               string                                                               m_name;
               WaveThread                                                         *m_pAssociatedWaveThread;
               map<UI32, PrismOperationMapContext *>                                m_operationsMap;
               map<UI32, UI32>                                                      m_supportedEvents;
               map<LocationId, map<UI32, map<UI32, WaveEventMapContext *> *> *>    m_eventsMap;
               map<UI32, WaveMessageResponseContext *>                             m_responsesMap;
               map<UI32, vector<WaveEventListenerMapContext *> *>                  m_eventListenersMap;
               map<string, vector<string> >                                         m_postbootManagedObjectNames;
               WaveMutex                                                           m_responsesMapMutex;
               WaveMutex                                                           m_sendReplyMutexForResponseMap;
               vector<WaveWorker *>                                                 m_workers;
               bool                                                                 m_isEnabled;
               WaveMutex                                                           m_isEnabledMutex;
               TraceClientId                                                        m_traceClientId;

               map<string, string>                                                  m_managedClasses;
               map<string, string>                                                  m_managedViews;
               bool                                                                 m_isTransactionOn;
               vector<WaveManagedObject *>                                          m_objectsCreatedDuringCurrentTransaction;
               vector<CompositionEntry>                                             m_compositionEntriesCreatedDuringCurrentTrasnaction;
               vector<AssociationEntry>                                             m_associationEntriesCreatedDuringCurrentTrasnaction;
               vector<RelationshipEntry>                                            m_relationshipEntriesCreatedDuringCurrentTransaction;
               vector<WaveManagedObject *>                                          m_objectsUpdatedIndividuallyDuringCurrentTransaction;
               vector<WaveManagedObjectForUpdate *>                                 m_objectsUpdatedDuringCurrentTransaction;
               vector<ObjectId>                                                     m_objectsDeletedIndividuallyDuringCurrentTransaction;
               vector<WaveManagedObjectForDelete *>                                 m_objectsDeletedDuringCurrentTransaction;
               vector<string>                                                       m_managedObjectsDeletedAtTheBeginingOfTransaction;
               vector<CompositionEntry>                                             m_compositionEntriesDeletedDuringCurrentTransaction;
               vector<AssociationEntry>                                             m_associationEntriesDeletedDuringCurrentTrasnaction;
               vector<RelationshipEntry>                                            m_relationshipEntriesDeletedDuringCurrentTransaction;

               vector<WaveConfigurationAttributes>                                  m_configurationsCreatedDuringCurrentTransaction;
               vector<WaveConfigurationAttributes>                                  m_configurationsUpdatedDuringCurrentTransaction;


               vector<UI32>                                                         m_cpuAffinityVector;

               WaveObjectManager                                                   *m_pAssociatedVirtualWaveObjectManager; // This filed will be used only by the derived classes of type WaveLocalObjectManager to represent virtual/global service corresponding to that locla service.

        static map<string, WaveElement *>                                          m_ownersForCreatingManagedObjectInstances;
        static WaveMutex                                                           m_createManagedObjectInstanceWrapperMutex;
               map<UI32, WaveElement *>                                            m_ownersForCreatingMessageInstances;
               WaveMutex                                                           m_createMessageInstanceWrapperMutex;

               bool                                                                 m_allowAutomaticallyUnlistenForEvents;

               WaveManagedObjectLoadOperationalDataWorker                          *m_pWaveManagedObjectLoadOperationalDataWorker;
               PrismPostbootWorker                                                 *m_pPrismPostbootWorker;
               WaveMessage                                                        *m_pInputMessage;

               vector<MessageHistory *>                                             m_messageHistoryVector;
               bool                                                                 m_messageHistoryState;
               UI32                                                                 m_messageHistoryMaxSize;
               UI32                                                                 m_messageHistoryNextSlotInVector;
               bool                                                                 m_messageHistoryLogInsideSend;
               bool                                                                 m_messageHistoryLogInsideReply;
               bool                                                                 m_messageHistoryLogInsideHandleMessage;
        static map<string, WaveServiceId>                                          m_serviceStringServiceIdMap;
        static WaveMutex                                                           m_serviceStringServiceIdMapMutex;
               set<string>                                                          m_serviceStrings;

               WaveManagedObjectUpdateWorker                                       *m_pWaveManagedObjectUpdateWorker;
               WaveManagedObjectCreateWorker                                       *m_pWaveManagedObjectCreateWorker;
               WaveDebugInformationWorker                                          *m_pWaveDebugInformationWorker;
               WaveObjectManagerStatisticsTracker                                  *m_pWaveObjectManagerStatisticsTracker;
                WaveManagedObjectDeleteWorker                                      *m_pWaveManagedObjectDeleteWorker;
                WaveClientDataObjectGetWorker                                      *m_pWaveClientDataObjectGetWorker;

               map<UI32, map<UI32, UI64> >                                          m_secondsForMessageHandlerSequencerSteps;
               map<UI32, map<UI32, SI64> >                                          m_nanoSecondsForMessageHandlerSequencerSteps;

               map<UI32, map<UI32, UI64> >                                          m_realSecondsForMessageHandlerSequencerSteps;
               map<UI32, map<UI32, SI64> >                                          m_realNanoSecondsForMessageHandlerSequencerSteps;
               map<string, map<string, UnifiedClientBackendDetails*> >              m_backendAttributeMap; // map of boot or shutdown phase, <taskname, backendDetails>
               set<string>                                                          m_setOfPartitionNamesReferencedInCurrentTransaction;
        static WaveMutex                                                           m_postponedMessageQueueMutex;
               WaveMessageQueue<WaveMessage>                                      m_postponedMessageQueue;

        static map<string, map<string, string> >                                    m_clientsListeningForCreateByManagedObject;
        static map<string, map<string, string> >                                    m_clientsListeningForUpdateByManagedObject;
        static map<string, map<string, string> >                                    m_clientsListeningForDeleteByManagedObject;
        static map<string, map<string, string> >                                    m_managedObjectsForCreateByClient;
        static map<string, map<string, string> >                                    m_managedObjectsForUpdateByClient;
        static map<string, map<string, string> >                                    m_managedObjectsForDeleteByClient;
        static WaveMutex                                                           m_clientsListeningMutex;
               WaveMutex                                                           m_workersMutex;
        static WaveServiceMode                                                      m_waveServiceLaunchMode;
               WaveServiceMode                                                      m_waveServiceMode;
               UI32                                                                 m_serviceId;

               map<string, map<string, WaveBrokerPublishMessageHandlerContext *> >  m_waveBrokerBasedMessageSubscriberInformationMap;

               WaveDeliverBrokerPublishMessageWorker                               *m_pWaveDeliverBrokerPublishMessageWorker;

    protected :
    public :

    friend class Wave;
    friend class WaveClient;
    friend class WaveSystemManagement;
    friend class WaveThread;
    friend class WaveWorker;
    friend class WaveManagedObject;
    friend class WaveMessageFactory;
    friend class ApplicationServiceRepository;
    friend class ApplicationServiceUtils;
    friend class WaveManagedObjectFactory;
    friend class DatabaseObjectManagerExecuteQueryWorker;
	friend class DatabaseQueryCursor;
    friend class PrismPostbootWorker;
    friend class WaveDebugInformationWorker;
    friend class WaveCliTraceShell;
    friend class ObjectTracker;
    friend class WaveObjectManagerToolKit;
    friend class WaveClientSynchronousConnection;
    friend class WaveManagedObjectCreateWorker;
    friend class WaveManagedObjectUpdateWorker;
    friend class WaveManagedObjectDeleteWorker;
    friend class WaveClientDataObjectGetWorker;
    friend class PrismSynchronousLinearSequencerContext;
    friend class ManagementInterfaceObjectManager;
    friend class WaveMessageBroker;
    friend class WaveMessageBrokerClient;

    friend void tracePrintf (TraceLevel traceLevel, const bool &addNewLine, const bool &suppressPrefix, const char * const pFormat, ...);
    friend void tracePrintf (TraceLevel traceLevel, const char * const pFormat, ...);

};

}

#endif //PRISMOBJECTMANAGER_H
