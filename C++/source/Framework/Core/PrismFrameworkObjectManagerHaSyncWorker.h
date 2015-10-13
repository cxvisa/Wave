/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Leifang Hu                                            *
 ***************************************************************************/

#ifndef PRISMFRAMEWORKOBJECTMANAGERHASYNCWORKER_H
#define PRISMFRAMEWORKOBJECTMANAGERHASYNCWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Core/FrameworkObjectManagerMessages.h"
#include "Framework/Core/HaSyncWorkerSequencerContext.h"
#include "Framework/Utils/ServerStreamingSocket.h"
#include "Framework/Utils/WaveMutex.h"

namespace WaveNs
{

class FrameworkObjectManagerStartHaSyncMessage;
class FrameworkObjectManagerInitHaIpAddressMessage;
class PrismFrameworkConfiguration;
class VcsClusterConfiguration;
class StartupFileConfiguration;

class PrismFrameworkObjectManagerHaSyncWorker : public WaveWorker
{
    private :
                void initHaIpAddressHandler (FrameworkObjectManagerInitHaIpAddressMessage *pFrameworkObjectManagerInitHaIpAddressMessage);
                void initHaIpAddressStep    (WaveLinearSequencerContext *pWaveLinearSequencerContext);

                void startHaSyncDumpHandler (FrameworkObjectManagerStartHaSyncMessage *pFrameworkObjectManagerStartHaSyncMessage);
                void connectToHaPeerStep    (StartHaSyncDumpContext *pWaveLinearSequencerContext);
                void ccmdConnectToHaPeerStep          (StartHaSyncDumpContext *pWaveLinearSequencerContext);
                void haSyncCollectValidationDataStep  (StartHaSyncDumpContext *pWaveLinearSequencerContext);
                void haSyncValidateVersionStep        (StartHaSyncDumpContext *pWaveLinearSequencerContext);
                void haSyncValidateVersionCallback    (FrameworkStatus frameworkStatus, FrameworkObjectManagerGetFirmwareVersionMessage *pFrameworkObjectManagerGetFirmwareVersionMessage, void *pContext);
                void haSyncCreateStandbyMessageStep   (StartHaSyncDumpContext *pWaveLinearSequencerContext);
                void haSyncGetStartupDataStep         (StartHaSyncDumpContext *pWaveLinearSequencerContext);
                void haSyncGetVcsClusterDataStep      (StartHaSyncDumpContext *pWaveLinearSequencerContext);
                void haSyncGetConfigurationFileStep   (StartHaSyncDumpContext *pWaveLinearSequencerContext);
                void haSyncCreateDatabaseDumpStep     (StartHaSyncDumpContext *pWaveLinearSequencerContext);
                void haSyncGetValidationDetailsStep   (StartHaSyncDumpContext *pWaveLinearSequencerContext);
                void haSyncSendDatabaseDumpStep       (StartHaSyncDumpContext *pWaveLinearSequencerContext);
                void haSyncSendDatabaseDumpCallback   (FrameworkStatus frameworkStatus, PrismHaSyncConfigureStandbyMessage *pPrismHaSyncConfigureStandbyMessage, void *pContext);
                bool isServiceToBeExcludedInHaSyncCommunications (const WaveServiceId &waveServiceId);
                void createDatabaseBackupBuffer       (char * &pDatabaseBackupBuffer, SI32 &sizeOfBackupFile);
                void resumeDatabase                   ();
                void haSyncGetValidationResultsStep   (StartHaSyncDumpContext *pWaveLinearSequencerContext);
                void setSyncCompletionStatusStep      (StartHaSyncDumpContext *pWaveLinearSequencerContext);
                void haSyncFailedStep                 (StartHaSyncDumpContext *pWaveLinearSequencerContext);
                void configureStandbyHandler               (PrismHaSyncConfigureStandbyMessage *pPrismHaSyncConfigureStandbyMessage);
                void removePreviousDatabaseBackupFile      (ReceiveHaSyncDumpContext *pReceiveHaSyncDumpContext);
                void configureStandbyValidateVersionStep   (ReceiveHaSyncDumpContext *pReceiveHaSyncDumpContext);
                void configureStandbyValidateServicesStep  (ReceiveHaSyncDumpContext *pReceiveHaSyncDumpContext);
                void configureStandbyShutdownServicesStep  (ReceiveHaSyncDumpContext *pReceiveHaSyncDumpContext);
                void standbyConnectToHaPeerStep            (ReceiveHaSyncDumpContext *pReceiveHaSyncDumpContext);
                void configureStandbyBootServicesPrePhaseStep   (ReceiveHaSyncDumpContext *pReceiveHaSyncDumpContext);
                void configureStandbyEmptyDatabaseStep     (ReceiveHaSyncDumpContext *pReceiveHaSyncDumpContext);
                void configureStandbyLoadDatabaseFromActiveDatabaseStep (ReceiveHaSyncDumpContext *pReceiveHaSyncDumpContext);
                void configureStandbyConvertDatabaseStep   (ReceiveHaSyncDumpContext *pReceiveHaSyncDumpContext);
                void loadPrismConfigurationStep            (ReceiveHaSyncDumpContext *pReceiveHaSyncDumpContext);
                void savePrismConfigurationStep            (ReceiveHaSyncDumpContext *pReceiveHaSyncDumpContext);
                void configureStandbyUpdatePrismConfigurationFileStep (ReceiveHaSyncDumpContext *pReceiveHaSyncDumpContext);
                void configureStandbyServicesPostPhaseStep (ReceiveHaSyncDumpContext *pReceiveHaSyncDumpContext);
               	void configureStandbyUpdateVcsConfigStep   (ReceiveHaSyncDumpContext *pReceiveHaSyncDumpContext);
               	void configureStandbyUpdateStartupFileStep (ReceiveHaSyncDumpContext *pReceiveHaSyncDumpContext);
               	void copyStartupSchemaStep                 (ReceiveHaSyncDumpContext *pReceiveHaSyncDumpContext);
               	void updateInstanceIdStep                  (ReceiveHaSyncDumpContext *pReceiveHaSyncDumpContext);
               	void copyRunningStartupStep                (ReceiveHaSyncDumpContext *pReceiveHaSyncDumpContext);
                void configureStandbySetInSyncStep         (ReceiveHaSyncDumpContext *pReceiveHaSyncDumpContext);

                void startHaSyncUpdateHandler              (FrameworkObjectManagerHaSyncUpdateMessage *pFrameworkObjectManagerHaSyncUpdateMessage);
                void haSyncUpdateValidationStep            (StartHaSyncDumpContext *pWaveLinearSequencerContext);

                void getFirmwareVersionHandler             (FrameworkObjectManagerGetFirmwareVersionMessage *pFrameworkObjectManagerGetFirmwareVersionMessage);
               	void sendFirmwareVersionStep               (ReceiveHaSyncDumpContext *pReceiveHaSyncDumpContext);
                void sendFirmwareVersionCallback           (FrameworkStatus frameworkStatus, FrameworkObjectManagerGetFirmwareVersionMessage *pFrameworkObjectManagerGetFirmwareVersionMessage, void *pContext);

                void startCcmdHaSyncDumpHandler            (FrameworkObjectManagerStartCcmdHaSyncMessage *pFrameworkObjectManagerStartCcmdHaSyncMessage);
                void startCcmdHaSyncUpdateHandler          (FrameworkObjectManagerCcmdHaSyncUpdateMessage *pFrameworkObjectManagerCcmdHaSyncUpdateMessage);
                void ccmdHaSyncUpdateValidationStep        (StartHaSyncDumpContext *pWaveLinearSequencerContext);

               	string getFirmwareVersion                  ();
               	void   setFirmwareVersion                  (const string &firmwareVersion);
               	void   setSyncDumpComplete                 (const bool &syncDumpComplete);
                bool   getFirmwareVersionMatch             ();
                void   setFirmwareVersionMatch             (const bool &firmwareVersionMatch);
               	void   enableLiveSync                      ();
               	void   setSyncState                        (const UI32 &syncState);
                void   setStandbySyncState                 (const UI32 &syncState);
                void   setSyncServicedAsStandby            (const bool &syncServicedAsStandby);           
                void   resumeLocalPersistence              ();
                void   pauseLocalPersistence              ();
    protected :
    public :
                PrismFrameworkObjectManagerHaSyncWorker (WaveObjectManager *pWaveObjectManager);
        virtual ~PrismFrameworkObjectManagerHaSyncWorker ();
        static  PrismFrameworkObjectManagerHaSyncWorker *getInstance ();
                WaveMessage *createMessageInstance (const UI32 &operationCode);

               	bool getSyncDumpComplete                  ();
                void initializeHaPeerServerCommunications ();
                bool acceptHaPeerConnection (ServerStreamingSocket &newSocket);
                ResourceId connectToHaPeer (const string &ipAddress, const SI32 &port);
                void disconnectFromHaPeer (const string &ipAddress, const SI32 &port, const bool &closePeerServerSocket = true);
                ResourceId setFrameworkConfigurationFromConfigurationFile (const PrismFrameworkConfiguration &prismFrameworkConfiguration);
                void endHaSyncHandler (FrameworkObjectManagerEndHaSyncMessage *pFrameworkObjectManagerEndHaSyncMessage);
                void setSyncStateHandler (FrameworkObjectManagerSetSyncStateMessage *pFrameworkObjectManagerSetSyncStateMessage);
                void getSyncStateHandler (FrameworkObjectManagerGetSyncStateMessage *pFrameworkObjectManagerGetSyncStateMessage);
                UI32 getStandbySyncState                 ();
                bool getSyncServicedAsStandby            ();
                UI32 getSyncState                        ();
    // Now the Data Members
    private :
        string     m_firmwareVersion;
        bool       m_syncDumpComplete;
        bool       m_firmwareVersionMatch;
        WaveMutex m_syncDumpCompleteMutex;
        UI32       m_syncState;
        WaveMutex m_syncStateMutex;
        UI32       m_standbySyncState;
        WaveMutex m_standbySyncStateMutex;
        bool       m_syncServicedAsStandby;
        WaveMutex m_syncServicedAsStandbyMutex;
        bool       m_isDbDropNeeded;
        UI32       m_dbSchemaType;
        UI32       m_myHaVersion;
        UI32       m_peerHaVersion;

    protected :
    public :
               friend class PrismFrameworkObjectManager;
               friend class PrismFrameworkConfigurationWorker;

};

}

#endif // PRISMFRAMEWORKOBJECTMANAGERHASYNCWORKER_H
