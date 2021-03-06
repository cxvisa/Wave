/***************************************************************************
 *   Copyright (C) 2005-2017 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Guntaka                                          *
 ***************************************************************************/

#ifndef PERSISTENCELOCALOBJECTMANAGER_H
#define PERSISTENCELOCALOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/Persistence/PersistenceObjectManagerTypes.h"
#include "Framework/Persistence/StartupSchemaChangeEvent.h"
#include "Framework/Persistence/PersistenceLocalObjectManagerUpdateInstanceIdMesssage.h"
#include "Framework/Persistence/PersistenceLocalObjectManagerPushConfigToKernelMessaage.h"

namespace WaveNs
{

class PersistenceLocalObjectManagerSetStartupFileMessage;
class PersistenceLocalObjectManagerSaveWaveConfigurationMessage;
class PersistenceLocalObjectManagerCopySchemaMessage;
class PersistenceLocalObjectManagerCopyDefaultClusterMessage;
class PersistenceLocalObjectManagerSetConfigurationValidMessage;
class PersistenceLocalObjectManagerDebugSchemaChangeMessage;
class PersistenceLocalObjectManagerExecuteTransactionMessage;
class PersistenceLocalObjectManagerEnableTransactionMessage;
class PersistenceLocalObjectManagerSetLiveSyncEnableMessage;
class PersistenceLocalObjectManagerGetLiveSyncEnableMessage;
class PersistenceLocalExecuteTransactionContext;
class DatabaseObjectManagerExecuteTransactionMessage;
class WaveObjectModelWaveServerPage;
class WaveObjectModelPlantUmlWaveServerPage;
class WaveObjectModelPlantUmlDisplayWaveServerPage;
class WaveObjectModelDotGraphWaveServerPage;
class WaveObjectModelDotGraphDisplayWaveServerPage;

typedef ResourceId  (*UpdateGlobalConfigInKernelHandlerFunction)       (string &globalConfigs);

class PersistenceLocalObjectManager : public WaveLocalObjectManager
{
    private :
                                                PersistenceLocalObjectManager                   ();
                void                            setStartupFileMessageHandler                    (PersistenceLocalObjectManagerSetStartupFileMessage *pMessage);
                void                            copyDefaultClusterMessageHandler                (PersistenceLocalObjectManagerCopyDefaultClusterMessage *pMessage);
                void                            saveWaveConfigurationMessageHandler            (PersistenceLocalObjectManagerSaveWaveConfigurationMessage *pMessage);
                void                            copySchemaMessageHandler                        (PersistenceLocalObjectManagerCopySchemaMessage *pPersistenceLocalObjectManagerCopySchemaMessage);
                void                            setConfigurationValidMessageHandler             (PersistenceLocalObjectManagerSetConfigurationValidMessage *pPersistenceLocalObjectManagerSetConfigurationValidMessage);

                void                            debugSchemaChangeMessageHandler                 (PersistenceLocalObjectManagerDebugSchemaChangeMessage *pPersistenceLocalObjectManagerDebugSchemaChangeMessage);

        virtual WaveMessage                   *createMessageInstance                           (const UI32 &operationCode);
        virtual WaveEvent                     *createEventInstance                             (const UI32 &eventOperationCode);

        static  bool                            getDisableLocalCommitTransactions               ();
        static  void                            setDisableLocalCommitTransactions               (const bool &disableLocalCommitTransactions);
        static  bool                            getLiveSyncEnabled                              ();
        static  void                            setLiveSyncEnabled                              (const bool &liveSyncEnabled);

    protected :
    public :
        virtual                                 ~PersistenceLocalObjectManager                   ();
        static  PersistenceLocalObjectManager   *getInstance                                     ();
        static  WaveServiceId                   getWaveServiceId                               ();
        static  string                           getServiceName                                  ();
        void                                     broadcastSchemaChangeEvent                      (SchemaType m_fromSchema, string fromSchemaPath = "", SchemaType toSchema = STARTUP_SCHEMA, string toSchemaPath = "", bool operationStatus = true);
        void                                     updateInstanceIdMessageHandler                  (PersistenceLocalObjectManagerUpdateInstanceIdMesssage *pPersistenceLocalObjectManagerUpdateInstanceIdMesssage);
        void                                     updateInstanceId                                ();
        void                                     executeTransactionMessageHandler                (PersistenceLocalObjectManagerExecuteTransactionMessage *pPersistenceLocalObjectManagerExecuteTransactionMessage);
        void                                     sendTransactionToDatabase                       (PersistenceLocalExecuteTransactionContext *pPersistenceLocalExecuteTransactionContext);
        void                                     handleTransactionResult                         (PersistenceLocalExecuteTransactionContext *pPersistenceLocalExecuteTransactionContext);
        void                                     executeTransactionSendRequestCallback           (FrameworkStatus frameworkStatus, DatabaseObjectManagerExecuteTransactionMessage *pDatabaseObjectManagerExecuteTransactionMessage, PersistenceLocalExecuteTransactionContext *pPersistenceLocalExecuteTransactionContext);
        void                                     executeTransactionSendRequestStandbyCallback    (FrameworkStatus frameworkStatus, DatabaseObjectManagerExecuteTransactionMessage *pDatabaseObjectManagerExecuteTransactionMessage, PersistenceLocalExecuteTransactionContext *pPersistenceLocalExecuteTransactionContext);
        void                                     enableTransactionMessageHandler                 (PersistenceLocalObjectManagerEnableTransactionMessage *pPersistenceLocalObjectManagerEnableTransactionMessage);
        void                                     setLiveSyncEnableMessageHandler                 (PersistenceLocalObjectManagerSetLiveSyncEnableMessage *pPersistenceLocalObjectManagerSetLiveSyncEnableMessage);
        void                                     getLiveSyncEnableMessageHandler                 (PersistenceLocalObjectManagerGetLiveSyncEnableMessage *pPersistenceLocalObjectManagerGetLiveSyncEnableMessage);
        void                                     install                                         (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        void                                     hainstall                                       (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        void                                     boot                                            (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        void                                     haboot                                          (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        void                                     shutdown                                        (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases);
        static  UI64                             getAnyConfigurationChangeTrackingNumber         ();
        static  void                             setAnyConfigurationChangeTrackingNumber         (UI64 &trackingNumber);
        static  void                             setUpdateGlobalConfigInKernelHandlerFunction    (UpdateGlobalConfigInKernelHandlerFunction updateGlobalConfigInKernelHandlerFunction);
        void                                     pushConfigToKernelMessageHandler                (PersistenceLocalObjectManagerPushConfigToKernelMessaage *pPersistenceLocalObjectManagerPushConfigToKernelMessaage);
                ResourceId                       updateGlobalConfigInKernel                      (string &globalConfigs);
    // Now the data members

    private :
        static  bool                            m_liveSyncEnabled;
        static  WaveMutex                      m_liveSyncEnabledMutex;
        static  bool                            m_disableLocalCommitTransactions;
        static  WaveMutex                      m_disableLocalCommitTransactionsMutex;
        static  string                          m_unsyncedPendingPrepareTransaction;
        static  UI64                            m_anyConfiguraitonChangeTrackingNumber;
        static  WaveMutex                      m_anyConfiguraitonChangeTrackingNumberMutex;
        static  UpdateGlobalConfigInKernelHandlerFunction m_updateGlobalConfigInKernelHandlerFunction;

        WaveObjectModelWaveServerPage                *m_pWaveObjectModelWaveServerPage;
        WaveObjectModelPlantUmlWaveServerPage        *m_pWaveObjectModelPlantUmlWaveServerPage;
        WaveObjectModelPlantUmlDisplayWaveServerPage *m_pWaveObjectModelPlantUmlDisplayWaveServerPage;
        WaveObjectModelDotGraphWaveServerPage        *m_pWaveObjectModelDotGraphWaveServerPage;
        WaveObjectModelDotGraphDisplayWaveServerPage *m_pWaveObjectModelDotGraphDisplayWaveServerPage;

    protected :
    public :

    friend class WaveObjectManager;
    friend class FrameworkToolKit;
    friend class PersistenceObjectManager;
};

}

#endif //PERSISTENCELOCALOBJECTMANAGER_H
