/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/Types/DateTime.h" // map template member.
#include "Framework/ObjectModel/SerializableObject.h"
#include "Framework/Persistence/PersistenceLocalObjectManagerPushConfigToKernelMessaage.h"

#ifndef PERSISTENCEOBJECTMANAGER_H
#define PERSISTENCEOBJECTMANAGER_H

namespace WaveNs
{

class PersistenceObjectManagerExecuteTransactionMessage;
class PersistenceObjectManagerCopySchemaMessage;
class PersistenceObjectManagerCopyFileMessage;
class PrismAsynchronousContext;
class DatabaseObjectManagerExecuteTransactionMessage;
class DatabaseObjectManagerExecuteCopySchemaMessage;
class PersistenceLocalObjectManagerSetStartupFileMessage;
class PersistenceExecuteTransactionContext;
class PersistenceObjectManagerCompareDBMessage;
class WaveMessage;
class WaveAsynchronousContextForBootPhases;
class ConfigurationManagedObject;
class PersistenceObjectManagerInitializeBeforeBootCompleteMessage;
class PersistenceObjectManagerUpdateInstanceIdMesssage;
class WaveAsynchronousContextForDebugInformation;
class PersistenceObjectManagerPrintOrmMessage;
class XPathStringManagedObject;
class WaveConfigManagedObject;
class PersistenceObjectManagerAddXPathStringsMessage;
class WaveLinearSequencerContext;
class PersistenceObjectManagerDeleteXPathStringsMessage;
class PersistenceObjectManagerGetLastUpdateTimestampsForXPathStringsMessage;
class PersistenceObjectManagerResetXPathStringsTimestampsMessage;
class PersistenceLocalObjectManagerExecuteTransactionMessage;
class PersistenceObjectManagerGetAllClassNamesMessage;
class WaveSendMulticastContext;
class PersistenceObjectManagerAddDelayedTransactionMessage;
class PersistenceObjectManagerExecuteTransactionAsynchronousContext;

class PersistenceObjectManager : public WaveObjectManager
{
    private :
                                            PersistenceObjectManager                                                ();
                void                        shutdown                                                                (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases);
                void                        initialize                                                              (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                void                        install                                                                 (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                void                        boot                                                                    (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

        virtual void                        getDebugInformation                                                     (WaveAsynchronousContextForDebugInformation *pWaveAsynchronousContextForDebugInformation);
        virtual void                        resetDebugInformation                                                   (WaveAsynchronousContextForDebugInformation *pWaveAsynchronousContextForDebugInformation);

                ResourceId                  copySchemaLocal                                                         (const string &sourceSchema, const string &destSchema);

        virtual WaveMessage               *createMessageInstance                                                   (const UI32 &operationCode);
        virtual WaveManagedObject          *createManagedObjectInstance                                             (const string &managedClassName);


        // XPathStringManagedObject and its cache related functions.

                string                      getSqlToUpdateXPathStringObjects                                        (const vector<string> &xPathStringsVectorForTimestampUpdate, map<string, DateTime> &xPathStringToOriginalDatetimestampMap);

                void                        flushXPathStringToXPathStringManagedObjectMap                           ();
                void                        addXPathStringManagedObjectToCache                                      (XPathStringManagedObject *pXPathStringManagedObject);
                void                        flushAndRePopulateXPathStringToXPathStringManagedObjectMapAsCache       ();

                XPathStringManagedObject   *getXPathStringManagedObjectFromCache                                    (const string &xPathString);

                void                        addWaveConfigManagedObjectToCache                                       (WaveConfigManagedObject *pWaveConfigManagedObject);
                WaveConfigManagedObject    *getWaveConfigManagedObjectFromCache                                     (const string &configName);
                void                        flushWaveConfigManagedObjectMap                                         ();
                void                        flushAndRePopulateWaveConfigManagedObjectCache                          ();

                void                        restoreOriginalTimestampsForCachedXPathStringManagedObjects             (const map<string, DateTime> &xPathStringToOriginalDatetimestampMap);

                void                        getAllClassNamesMessageHandler                                          (PersistenceObjectManagerGetAllClassNamesMessage *pPersistenceObjectManagerGetAllClassNamesMessage);
         static void                        getAllClassNamesMessageStaticHandler                                    (PersistenceObjectManagerGetAllClassNamesMessage *pPersistenceObjectManagerGetAllClassNamesMessage);

                void                        addDelayedTransactionMessageHandler                                     (PersistenceObjectManagerAddDelayedTransactionMessage *pPersistenceObjectManagerAddDelayedTransactionMessage);
                void                        addDelayedTransactionStep                                               (WaveLinearSequencerContext *pWaveLinearSequencerContext);
    
                UI32                        isDelayedTransactionsEmpty                                              ();
                void                        addDelayedTransaction                                                   (const string &delayedSqlTransaction);
                string                      getDelayedTransactions                                                  ();
                void                        clearDelayedTransactions                                                ();

    protected :
    public :
        virtual                            ~PersistenceObjectManager                                                ();
        static  PersistenceObjectManager   *getInstance                                                             ();
        static  WaveServiceId              getWaveServiceId                                                       ();

                void                        initializeConfigurationManagedObjectBeforeBootCompleteMessageHandler    (PersistenceObjectManagerInitializeBeforeBootCompleteMessage *pPersistenceObjectManagerInitializeBeforeBootCompleteMessage);
                void                        updateInstanceIdMessageHandler                                          (PersistenceObjectManagerUpdateInstanceIdMesssage *pPersistenceObjectManagerUpdateInstanceIdMesssage);
                void                        updateInstanceId                                                        ();
                void                        executeTransactionMessageHandler                                        (PersistenceObjectManagerExecuteTransactionMessage *pPersistenceObjectManagerExecuteTransactionMessage);
                void                        executeTransactionSendRequestToAllLocationsForPreparePhaseStep          (PersistenceExecuteTransactionContext *pPersistenceExecuteTransactionContext);
                void                        executeTransactionSendRequestToAllLocationsForPreparePhaseCallback      (FrameworkStatus frameworkStatus, PersistenceLocalObjectManagerExecuteTransactionMessage *pPersistenceLocalObjectManagerExecuteTransactionMessage, void *pContext);
                void                        executeTransactionSendRequestToAllLocationsForPreparePhaseCallback2     (WaveSendMulticastContext *pWaveSendMulticastContext);
                void                        executeTransactionSendRequestToAllLocationsForCommittRollbackPhaseStep  (PersistenceExecuteTransactionContext *pPersistenceExecuteTransactionContext);
                void                        executeTransactionSendRequestToAllLocationsForCommittCallback           (WaveSendMulticastContext *pWaveSendMulticastContext);
                void                        executeTransactionSendRequestToAllLocationsForRollbackCallback          (WaveSendMulticastContext *pWaveSendMulticastContext);

                void                        executePushWaveConfigurationToFileOnAllLocationsStep                    (PersistenceExecuteTransactionContext *pPersistenceExecuteTransactionContext);
                void                        executePushWaveConfigurationToKernelOnAllLocationsStep                  (PersistenceExecuteTransactionContext *pPersistenceExecuteTransactionContext);
                void                        pushConfigToKernelMessageCallback                                       (WaveSendToClusterContext *pWaveSendToClusterContext);

                void                        copySchemaMessageHandler                                                (PersistenceObjectManagerCopySchemaMessage *pPersistenceObjectManagerCopySchemaMessage);
                void                        copySchemaSendRequestToAllLocationsForPreparePhaseStep                  (PersistenceExecuteTransactionContext *pPersistenceExecuteTransactionContext);
                void                        copySchemaSendRequestCallback                                           (FrameworkStatus frameworkStatus, DatabaseObjectManagerExecuteCopySchemaMessage *pDatabaseObjectManagerExecuteCopySchemaMessage, void *pContext);
                void                        copySchemaSendRequestToAllLocationsForPreparePhaseCallback2             (FrameworkStatus frameworkStatus, DatabaseObjectManagerExecuteCopySchemaMessage *pDatabaseObjectManagerExecuteCopySchemaMessage, void *pContext);
                void                        savePrismConfiguration                                                  (PersistenceExecuteTransactionContext *pPersistenceExecuteTransactionContext);

                void                        copyFileMessageHandler                                                  (PersistenceObjectManagerCopyFileMessage *pPersistenceObjectManagerCopySchemaMessage);
                void                        copyFileSendRequestToAllLocationsForPreparePhaseStep                    (PersistenceExecuteTransactionContext *pPersistenceExecuteTransactionContext);
                void                        copyFileRequestCallback                                                 (FrameworkStatus frameworkStatus, PersistenceLocalObjectManagerSetStartupFileMessage *pPersistenceLocalObjectManagerSetStartupFileMessage, void *pContext);
                void                        copyFileSendRequestToAllLocationsForPreparePhaseCallback2               (WaveSendToClusterContext *pWaveSendToClusterContext);
                void                        savePrismConfigurationAtAllLocationsStep                                (PersistenceExecuteTransactionContext *pPersistenceExecuteTransactionContext);
                void                        savePrismConfigurationAtAllLocationsCallback                            (WaveSendToClusterContext *pWaveSendToClusterContext);

        //static  void                      setSchemaDropRequiredDuringBoot                                            (const bool &schemaDropRequiredDuringBoot);
                void                        compareDBMessageHandler                                                 (PersistenceObjectManagerCompareDBMessage *pPersistenceObjectManagerCompareDBMessage);        
                void                        sendGetCksumMessageRequestToAllLocationsStep                            (PersistenceExecuteTransactionContext *pPersistenceExecuteTransactionContext);
                void                        sendGetCksumMessageRequestToAllLocationsStepCallback                    (WaveSendToClusterContext *pWaveSendToClusterContext);
        inline  string                      getIPAndPortForLocationId                                               (LocationId location);                       
        static  string                      getPrismServiceName                                                     ();
                void                        restoreDataBase                                                         ();
                void                        printOrmMessageHandler                                                  (PersistenceObjectManagerPrintOrmMessage *pPersistenceObjectManagerPrintOrmMessage);

                void                        addXPathStringsMessageHandler                                           (PersistenceObjectManagerAddXPathStringsMessage *pPersistenceObjectManagerAddXPathStringsMessage);
                void                        createXPathStringManagedObjectsStep                                     (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                        xPathStringManagedObjectsCommitCallback                                 (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, void *pContext);
                void                        deleteXPathStringsMessageHandler                                        (PersistenceObjectManagerDeleteXPathStringsMessage *pPersistenceObjectManagerDeleteXPathStringsMessage);
                void                        deleteXPathStringManagedObjectsStep                                     (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void                        getLastUpdateTimestampsForXPathStringsMessageHandler                    (PersistenceObjectManagerGetLastUpdateTimestampsForXPathStringsMessage *pPersistenceObjectManagerGetLastUpdateTimestampsForXPathStringsMessage);
                void                        getLastUpdateTimestampsForXPathStringsStep                              (WaveLinearSequencerContext *pWaveLinearSequencerContext);

                void                        resetXPathStringsTimestampsMessageHandler                               (PersistenceObjectManagerResetXPathStringsTimestampsMessage *pPersistenceObjectManagerResetXPathStringsTimestampsMessage);
                void                        resetXPathStringsTimestampsStep                                         (WaveLinearSequencerContext *pWaveLinearSequencerContext);
        static  void                        setAnyConfigurationChangeTrackingNumber                                 (UI64 &trackingNumber);
        static  UI64                        getAnyConfigurationChangeTrackingNumber                                 ();
                string                      getWaveConfigSerializedData                                             ();
    // Now the data members

    private :
                ConfigurationManagedObject                 *m_pConfigurationManagedObject;
                map<string, XPathStringManagedObject *>     m_XPathStringToXPathStringManagedObjectMapAsCache;
                map<string, WaveConfigManagedObject *>      m_configNameToWaveConfigManagedObjectMapAsCache;
                string                                      m_delayedCommitTransactions;
        static  UI64                                        m_anyConfiguraitonChangeTrackingNumber;
        static  PrismMutex                                  m_anyConfiguraitonChangeTrackingNumberMutex;

    protected :
    public :
};

}

#endif // PERSISTENCEOBJECTMANAGER_H
