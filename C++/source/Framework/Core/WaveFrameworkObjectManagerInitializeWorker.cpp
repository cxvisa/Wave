/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 ***************************************************************************/

#include "Framework/Core/WaveFrameworkObjectManagerInitializeWorker.h"
#include "Framework/Core/WaveFrameworkInitializeWorkerStartServicesContext.h"
#include "Framework/Boot/FirstTimeWaveBootAgent.h"
#include "Framework/Boot/RecoverWaveBootAgent.h"
#include "Framework/Boot/PersistentWaveBootAgent.h"
#include "Framework/Boot/PersistentWithDefaultWaveBootAgent.h"
#include "Framework/Boot/SecondaryNodeConfigureWaveBootAgent.h"
#include "Framework/Boot/SecondaryNodeUnconfigureWaveBootAgent.h"
#include "Framework/Boot/SecondaryNodeRejoinWaveBootAgent.h"
#include "Framework/Boot/HaStandbyWaveBootAgent.h"
#include "Framework/Boot/PersistentWithDefaultForHABootAgent.h"
#include "Framework/Core/FrameworkSequenceGenerator.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Core/WaveFrameworkConfiguration.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Core/WaveFrameworkConfigurationWorker.h"
#include "Framework/Boot/BootTypes.h"
#include "Framework/Boot/BootCompleteForThisLocationEvent.h"
#include "Framework/Boot/HaBootCompleteForThisLocationEvent.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"
#include "Framework/Core/FrameworkObjectManagerMessages.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Persistence/PersistenceObjectManagerInitializeBeforeBootCompleteMessage.h"
#include "Framework/Database/DatabaseStandaloneTransaction.h"
#include "Framework/Database/DatabaseObjectManagerExecuteTransactionMessage.h"
#include "Framework/ObjectRelationalMapping/ManagedObjectSchemaInfoRepository.h"
#include "Framework/Core/Wave.h"
#include "Framework/Persistence/PersistenceToolKit.h"
#include "Framework/Shutdown/WaveShutdownAgent.h"

namespace WaveNs
{

bool WaveFrameworkObjectManagerInitializeWorker::m_initialBootcompleted = false;
WaveMutex WaveFrameworkObjectManagerInitializeWorker::m_initialBootcompletedMutex;
bool WaveFrameworkObjectManagerInitializeWorker::m_initialSchemaInfoObjectSaved = false;
WaveMutex WaveFrameworkObjectManagerInitializeWorker::m_initialSchemaInfoObjectSavedMutex;

WaveFrameworkObjectManagerInitializeWorker::WaveFrameworkObjectManagerInitializeWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker            (pWaveObjectManager),
      m_pWaveBootAgent     (NULL)
{
    addEventType (BOOT_COMPLETE_FOR_THIS_LOCATION);
    addEventType (FRAMEWORK_OBJECT_MANAGER_BROADCAST_ADDITION_OF_NEW_NODES_EVENT);
    addEventType (FRAMEWORK_OBJECT_MANAGER_NODES_ADDITION_TO_CLUSTER_COMPLETED_EVENT);
    addEventType (FRAMEWORK_OBJECT_MANAGER_LOCAL_NODE_DELETED_EVENT);
    addEventType (FRAMEWORK_OBJECT_MANAGER_DELETE_CLUSTER_EVENT);
    addEventType (FRAMEWORK_OBJECT_MANAGER_BROADCAST_PHASE3_START_EVENT);
    addEventType (FRAMEWORK_OBJECT_MANAGER_BROADCAST_PHASE3_COMPLETE_EVENT);
    addEventType (FRAMEWORK_OBJECT_MANAGER_POST_BOOT_STARTED_EVENT);
    addEventType (FRAMEWORK_OBJECT_MANAGER_POST_BOOT_COMPLETED_EVENT);
    addEventType (FRAMEWORK_OBJECT_MANAGER_CONFIG_REPLAY_STARTED_EVENT);
    addEventType (FRAMEWORK_OBJECT_MANAGER_CONFIG_REPLAY_COMPLETED_EVENT);
    addEventType (FRAMEWORK_OBJECT_MANAGER_NODE_READY_FOR_ALL_COMMANDS_EVENT);
    addEventType (FRAMEWORK_OBJECT_MANAGER_PRIMARY_CHANGED_EVENT);
    addEventType (FRAMEWORK_OBJECT_MANAGER_BROADCAST_FAILOVER_COMPLETE_EVENT);
    addEventType (HA_BOOT_COMPLETE_FOR_THIS_LOCATION);

    addOperationMap (FRAMEWORK_OBJECT_MANAGER_UPDATE_DATABASE_SCHEMA, reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManagerInitializeWorker::FrameworkUpdateDatabaseSchema));
}

WaveFrameworkObjectManagerInitializeWorker::~WaveFrameworkObjectManagerInitializeWorker ()
{
}

ResourceId WaveFrameworkObjectManagerInitializeWorker::startWaveServices (const WaveBootMode &prismBootMode, const WaveBootPhase &waveBootPhase)
{
    trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManagerInitializeWorker::startWaveServices : Entering ...");

    WaveSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFrameworkObjectManagerInitializeWorker::determineNodeBootModeStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFrameworkObjectManagerInitializeWorker::chooseABootAgentStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFrameworkObjectManagerInitializeWorker::runTheBootAgentStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFrameworkObjectManagerInitializeWorker::saveConfigurationStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFrameworkObjectManagerInitializeWorker::informServicesToInitializeBeforeBootComplete),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFrameworkObjectManagerInitializeWorker::declareBootCompleteStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFrameworkObjectManagerInitializeWorker::prismSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFrameworkObjectManagerInitializeWorker::prismSynchronousLinearSequencerFailedStep),
    };

    WaveFrameworkInitializeWorkerStartServicesContext *pWaveFrameworkInitializeWorkerStartServicesContext = new WaveFrameworkInitializeWorkerStartServicesContext (reinterpret_cast<WaveAsynchronousContext *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pWaveFrameworkInitializeWorkerStartServicesContext->setWaveBootMode (prismBootMode);
    pWaveFrameworkInitializeWorkerStartServicesContext->setWaveBootPhase (waveBootPhase);

    ResourceId status = pWaveFrameworkInitializeWorkerStartServicesContext->execute ();

    // Indicate Framework bringup is completed;

    WaveFrameworkObjectManager::releaseBootSynchronizationMutex ();

    if (WAVE_MESSAGE_SUCCESS == status)
    {
        trace (TRACE_LEVEL_INFO, "Wave is now ready to serve.");
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManagerInitializeWorker::startWaveServices : Wave failed to come up.  Exiting ...");
//        waveAssert (false, __FILE__, __LINE__);
    }

    //(WaveFrameworkObjectManager::getInstance ())->setTraceLevel (TRACE_LEVEL_INFO);

    trace(TRACE_LEVEL_PERF_END, "Wave Bootup.");
    return (status);
}


//void WaveFrameworkObjectManagerInitializeWorker::buildDatabaseSchemaInfoRepository (const WaveFrameworkConfiguration &waveFrameworkConfiguration, ManagedObjectSchemaInfoRepository &dBSchemaRepository, vector<pair<string, UI32> >&tableClassIdTuples)
ResourceId WaveFrameworkObjectManagerInitializeWorker::buildDatabaseSchemaInfoRepository (const WaveFrameworkConfiguration &waveFrameworkConfiguration, ManagedObjectSchemaInfoRepository &dBSchemaRepository)
{
    ResourceId status = FRAMEWORK_SUCCESS;

    vector<string> managedObjectNames;
    vector<string> managedObjectFieldNamesStrings;
    vector<string> managedObjectFieldTypesStrings;
    vector<UI32> classIds;
    vector<UI32> parentClassIds;
    vector<string> userDefinedKeyCombinationsFieldNames;
    vector<string> userDefinedKeyCombinationsFieldTypes;
    vector<string> managedObjectFieldExpandedTypesStrings;
    vector<string> fieldTypesStrings;
//    tableClassIdTuples.clear();

    const size_t numElems = waveFrameworkConfiguration.getSchemaChangeInfo (managedObjectNames, managedObjectFieldNamesStrings, managedObjectFieldTypesStrings, classIds, parentClassIds, userDefinedKeyCombinationsFieldNames,userDefinedKeyCombinationsFieldTypes, managedObjectFieldExpandedTypesStrings);

    if (numElems)
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManagerInitializeWorker::buildDatabaseSchemaInfoRepository: reading from configuration file.");
        if (!managedObjectFieldExpandedTypesStrings.size ())
        {
            fieldTypesStrings = managedObjectFieldTypesStrings;
        }
        else
        {
            fieldTypesStrings = managedObjectFieldExpandedTypesStrings;
        }

        for (size_t i = 0; i < numElems; ++i)
        {
            ManagedObjectSchemaInfo *pSchemaInfoObj = new CompositeManagedObjectSchemaInfo (managedObjectNames[i], classIds[i], parentClassIds[i]);
            vector<string> fields;
            vector<string> types;

            tokenize (managedObjectFieldNamesStrings[i], fields, ':');
            tokenize (fieldTypesStrings[i], types, ':');

            for (size_t j = 0; j < fields.size (); ++j)
            {
                pSchemaInfoObj->addFieldTypeTuple (fields[j], types[j]);
            }

            if (userDefinedKeyCombinationsFieldNames.size () > 0)
            {
                vector<string> userDefinedFieldNames;
                vector<string> userDefinedFieldTypes;

                tokenize (userDefinedKeyCombinationsFieldNames[i], userDefinedFieldNames, ':');
                tokenize (userDefinedKeyCombinationsFieldTypes[i], userDefinedFieldTypes, ':');

                for (size_t k = 0; k < userDefinedFieldNames.size (); ++k)
                {
                    pSchemaInfoObj->addUserDefinedFieldTypeTuple (userDefinedFieldNames[k], userDefinedFieldTypes[k]);
                }
            }

            dBSchemaRepository.addSchemaInfoObject (pSchemaInfoObj);
 //           tableClassIdTuples.push_back (pair<string, UI32>(managedObjectNames[i], classIds[i]));
        }

    }
    else
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManagerInitializeWorker::buildDatabaseSchemaInfoRepository: reading from upgradeMO in db.");

        DatabaseSchema  databaseSchema;
        status = DatabaseSchema::getDatabaseSchema (databaseSchema);

        if (FRAMEWORK_SUCCESS != status)
        {
            return (status);
        }

        databaseSchema.convertDatabaseSchemaToManagedObjectSchemaInfoRepository (dBSchemaRepository);
    }

    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManagerInitializeWorker::buildDatabaseSchemaInfoRepository: Populate DBSchemaInfo Repository with RelationshipPointers");
    dBSchemaRepository.populateSchemaInfoObjectsWithRelationshipPointers ();

    return (status);
}

ResourceId WaveFrameworkObjectManagerInitializeWorker::performSchemaConversion (const WaveFrameworkConfiguration &waveFrameworkConfiguration, bool ignoreConfigFile)
{
    ResourceId status = FRAMEWORK_SUCCESS;

    //vector<pair<string, UI32> > tableClassIdTuples;

    OrmRepository *pOrmRepository = OrmRepository::getInstance ();
    waveAssert(NULL != pOrmRepository, __FILE__, __LINE__);

    trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManagerInitializeWorker::performSchemaConversion : Entering ...... ");

    ManagedObjectSchemaInfoRepository & moSchemaInfoRepository  = pOrmRepository->getMOSchemaInfoRepository ();

    ManagedObjectSchemaInfoRepository dBSchemaRepository;
    //buildDatabaseSchemaInfoRepository (waveFrameworkConfiguration, dBSchemaRepository, tableClassIdTuples);

    if (ignoreConfigFile)
    {
        DatabaseSchema  databaseSchema;
        status = DatabaseSchema::getDatabaseSchema (databaseSchema);

        if (FRAMEWORK_SUCCESS == status)
        {
            databaseSchema.convertDatabaseSchemaToManagedObjectSchemaInfoRepository (dBSchemaRepository);

            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManagerInitializeWorker::performSchemaConversion: Populate DBSchemaInfo Repository with RelationshipPointers");
            dBSchemaRepository.populateSchemaInfoObjectsWithRelationshipPointers ();
        }
    }
    else
    {
        status = buildDatabaseSchemaInfoRepository (waveFrameworkConfiguration, dBSchemaRepository);
    }

    //pOrmRepository->updateTableId (tableClassIdTuples);
    pOrmRepository->buildMoSchemaRepository ();

    if (FRAMEWORK_SUCCESS == status)
    {
        status = moSchemaInfoRepository.handleDatabaseSchemaDifferences (dBSchemaRepository);
    }

    return (status);
}

ResourceId WaveFrameworkObjectManagerInitializeWorker::determineNodeBootModeStep (WaveFrameworkInitializeWorkerStartServicesContext *pWaveFrameworkInitializeWorkerStartServicesContext)
{
    trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManagerInitializeWorker::determineNodeBootModeStep : Entering ...");

    if (WAVE_BOOT_UNKNOWN != (pWaveFrameworkInitializeWorkerStartServicesContext->getWaveBootMode ()))
    {
        return (WAVE_MESSAGE_SUCCESS);
    }

    OrmRepository *pOrmRepository = OrmRepository::getInstance ();

    waveAssert (NULL != pOrmRepository, __FILE__, __LINE__);

    WaveFrameworkConfigurationWorker *pWaveFrameworkConfigurationWorker = (WaveFrameworkObjectManager::getInstance ())->getPConfigurationWorker ();

    waveAssert (NULL != pWaveFrameworkConfigurationWorker, __FILE__, __LINE__);

    if (WAVE_MGMT_INTF_ROLE_SERVER == (FrameworkToolKit::getManagementInterfaceRole ()))
    {
        ifstream configBackupFile(((WaveFrameworkObjectManager::getInstance ())->getConfigurationBackupFileName ()).c_str());
        if (configBackupFile.is_open())
        {
            configBackupFile.close();
            string cpBackupFileCmd  = "/bin/mv " + (WaveFrameworkObjectManager::getInstance ())->getConfigurationBackupFileName () + " " + (WaveFrameworkObjectManager::getInstance ())->getConfigurationFileName ();
            system (cpBackupFileCmd.c_str());
        }
    }

    ResourceId status = pWaveFrameworkConfigurationWorker->loadWaveConfiguration ((WaveFrameworkObjectManager::getInstance ())->getConfigurationFileName ());

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        pWaveFrameworkInitializeWorkerStartServicesContext->setWaveBootMode (WAVE_BOOT_FIRST_TIME);

        trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManagerInitializeWorker::determineNodeBootModeStep : The Wave Framework Configuration file does not exist.  We will treat this as a first time boot for Wave.");

        pOrmRepository->buildMoSchemaRepository ();
    }
    else
    {
        string                      prismConfigurationfileName   = (WaveFrameworkObjectManager::getInstance ())->getConfigurationFileName ();
        WaveFrameworkConfiguration waveFrameworkConfiguration;
        ResourceId                  status1                      = WAVE_MESSAGE_ERROR;

        status1 = waveFrameworkConfiguration.loadConfiguration (prismConfigurationfileName);

        waveAssert (WAVE_MESSAGE_SUCCESS == status1, __FILE__, __LINE__);

        ResourceId startupFileType = waveFrameworkConfiguration.getStartupFileType();

        if (LOCATION_STAND_ALONE == (waveFrameworkConfiguration.getThisLocationRole ()))
        {
            if (((startupFileType == WAVE_PERSISTENCE_DEFAULT_FILE) ||
                 (startupFileType == WAVE_PERSISTENCE_DEFAULT_FILE_AT_LOCAL_NODE) ||
                 (startupFileType == WAVE_PERSISTENCE_REGULAR_FILE)) &&
                 (waveFrameworkConfiguration.getIsStartupValid() == false))
            {
                pWaveFrameworkInitializeWorkerStartServicesContext->setWaveBootMode (WAVE_BOOT_PERSISTENT_WITH_DEFAULT);
            }
            else
            {
                pWaveFrameworkInitializeWorkerStartServicesContext->setWaveBootMode (WAVE_BOOT_PERSISTENT);
            }
        }
        else
        {
            pWaveFrameworkInitializeWorkerStartServicesContext->setWaveBootMode (WAVE_BOOT_PERSISTENT);
        }

        if (true ==  FrameworkToolKit::getDetectSchemaChange ())
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManagerInitializeWorker::determineNodeBootModeStep : detectSchemaChange flag is true, checking for schema changes..");

            DatabaseStandaloneTransaction* dbObject = new DatabaseStandaloneTransaction ();
            if (NULL == dbObject)
            {
                trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManagerInitializeWorker::determineNodeBootModeStep : failed to allocate memory for DatabaseStandaloneTransaction");
                waveAssert (false, __FILE__, __LINE__);
            }

            dbObject->establishDbConnection ();

            // 1. check the location role of a local node.
            // 2. if not SA, Primary or Secondary, rollback db,
            // 3. rollback cfg.

            //1.
            LocationRole    thisNodeLocationRole    = waveFrameworkConfiguration.getThisLocationRole ();
            ResourceId      rollbackStatus          = FRAMEWORK_SUCCESS;

            if ((thisNodeLocationRole != LOCATION_STAND_ALONE) && (thisNodeLocationRole != LOCATION_PRIMARY) && (thisNodeLocationRole != LOCATION_PRIMARY_UNCONFIRMED) && (thisNodeLocationRole != LOCATION_SECONDARY) && (thisNodeLocationRole != LOCATION_SECONDARY_UNCONFIRMED))
            {
                // delete cfg file
                vector<string>  output;
                string          cmdString = string ("/bin/rm -rf ") + prismConfigurationfileName;
                SI32            cmdStatus = FrameworkToolKit::systemCommandOutput (cmdString.c_str(), output);

                if ( 0 != cmdStatus )
                {
                    rollbackStatus = FRAMEWORK_ERROR;
                    trace (TRACE_LEVEL_ERROR, string("WaveFrameworkObjectManagerInitializeWorker::determineNodeBootModeStep: failed to delete file ")+ prismConfigurationfileName);
                }
                else
                {
                    // 2. rollback the database.
                    rollbackStatus = dbObject->rollbackDatabase ();

                    //3. rollback cfg file
                    if (FRAMEWORK_ERROR != rollbackStatus)
                    {
                        rollbackStatus = dbObject->rollbackConfigFile (waveFrameworkConfiguration);
                    }
                }
            }

            ResourceId databaseSchemaUpgradeStatus  = FRAMEWORK_ERROR;

            if (FRAMEWORK_SUCCESS == rollbackStatus)
            {
                databaseSchemaUpgradeStatus  = performSchemaConversion (waveFrameworkConfiguration);
            }
            else
            {
                pOrmRepository->buildMoSchemaRepository ();
            }


            if ((databaseSchemaUpgradeStatus != FRAMEWORK_SUCCESS) && (WAVE_SCHEMA_UPGRADE_NOT_REQUIRED != databaseSchemaUpgradeStatus))
            {
                pWaveFrameworkInitializeWorkerStartServicesContext->setWaveBootMode (WAVE_BOOT_FIRST_TIME);
                pWaveFrameworkInitializeWorkerStartServicesContext->setSchemaChangedOnFwdl (true);

                if (FRAMEWORK_STATUS_SCHEMA_UPGRADE_FOR_FW_DOWNGRADE_NOT_SUPPORTED == databaseSchemaUpgradeStatus)
                {
                    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManagerInitializeWorker::determineNodeBootModeStep : FWDL is a downgrade case and schema change is detected; hence, will go for a first time boot");
                    (WaveFrameworkObjectManager::getInstance ())->setDbConversionStatus (DATABASE_SCHEMA_CONVERSION_NOT_ATTEMPTED);
                }
                else
                {
                    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManagerInitializeWorker::determineNodeBootModeStep : Schema change detected are not supported by db conversion, will treat as first time boot");
                    (WaveFrameworkObjectManager::getInstance ())->setDbConversionStatus (DATABASE_SCHEMA_CONVERSION_FAILED);
                }
            }
            else
            {
                // If we have successfully upgraded the database schema then record it in the context.
                // Then after running the boot agent - meaning after Framework data structures have been initialized with the prior .cfg file
                // It can be saved again with the proper values.
                // If we were to save at this point, Framework data structures which carry uninitialized data will be captured into the .cfg file.

                if (WAVE_SCHEMA_UPGRADE_NOT_REQUIRED != databaseSchemaUpgradeStatus)
                {
                    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManagerInitializeWorker::determineNodeBootModeStep : Schema Upgrade Successful");
                    pWaveFrameworkInitializeWorkerStartServicesContext->setIsSchemaUpgradedSuccessfully (true);
                    (WaveFrameworkObjectManager::getInstance ())->setDbConversionStatus (DATABASE_SCHEMA_CONVERSION_SUCCEEDED);
                }
                else
                {
                    (WaveFrameworkObjectManager::getInstance ())->setDbConversionStatus (DATABASE_SCHEMA_CONVERSION_SUCCEEDED);
                    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManagerInitializeWorker::determineNodeBootModeStep : Schema Upgrade Not Required, treating it as Success ");
                }
            }

            if (WAVE_BOOT_PERSISTENT != pWaveFrameworkInitializeWorkerStartServicesContext->getWaveBootMode ())
            {
                trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManagerInitializeWorker::determineNodeBootModeStep : shutting down the database");
                if (NULL != dbObject)
                {
                    dbObject->shutdownDatabase ();
                    delete dbObject;
                    dbObject = NULL;
                }
            }
        }
        else
        {
            // update the table-ids for Orm from the database.
            //pOrmRepository->buildMoSchemaRepository (1);
            pOrmRepository->buildMoSchemaRepository ();
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveFrameworkObjectManagerInitializeWorker::chooseABootAgentStep (WaveFrameworkInitializeWorkerStartServicesContext *pWaveFrameworkInitializeWorkerStartServicesContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManagerInitializeWorker::chooseABootAgentStep : Entering ...");

    FrameworkSequenceGenerator &frameworkSequenceGenerator = WaveFrameworkObjectManager::getCurrentFrameworkSequenceGenerator ();
    WaveBootMode               prismBootMode              = pWaveFrameworkInitializeWorkerStartServicesContext->getWaveBootMode ();

    trace (TRACE_LEVEL_INFO, string ("Boot Mode is ") + prismBootMode);

    if (WAVE_BOOT_FIRST_TIME == prismBootMode)
    {
        m_pWaveBootAgent = new FirstTimeWaveBootAgent (m_pWaveObjectManager, frameworkSequenceGenerator);
    }
    else if (WAVE_BOOT_PERSISTENT == prismBootMode)
    {
        m_pWaveBootAgent = new PersistentWaveBootAgent (m_pWaveObjectManager, frameworkSequenceGenerator);
    }
    else if (WAVE_BOOT_PERSISTENT_WITH_DEFAULT == prismBootMode)
    {
        m_pWaveBootAgent = new PersistentWithDefaultWaveBootAgent (m_pWaveObjectManager, frameworkSequenceGenerator);
    }
    else if (WAVE_BOOT_SECONDARY_CONFIGURE == prismBootMode)
    {
        m_pWaveBootAgent = new SecondaryNodeConfigureWaveBootAgent (m_pWaveObjectManager, frameworkSequenceGenerator);
    }
    else if (WAVE_BOOT_SECONDARY_UNCONFIGURE == prismBootMode)
    {
        m_pWaveBootAgent = new SecondaryNodeUnconfigureWaveBootAgent (m_pWaveObjectManager, frameworkSequenceGenerator);
    }
    else if (WAVE_BOOT_SECONDARY_REJOIN == prismBootMode)
    {
        m_pWaveBootAgent = new SecondaryNodeRejoinWaveBootAgent (m_pWaveObjectManager, frameworkSequenceGenerator);
    }
    else if (WAVE_BOOT_HASTANDBY == prismBootMode)
    {
        m_pWaveBootAgent = new HaStandbyWaveBootAgent (m_pWaveObjectManager, frameworkSequenceGenerator);
    }
    else if (WAVE_BOOT_PREPARE_FOR_HA_BOOT == prismBootMode)
    {
        m_pWaveBootAgent = new PersistentWithDefaultForHABootAgent (m_pWaveObjectManager, frameworkSequenceGenerator);
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, string ("WaveFrameworkObjectManagerInitializeWorker::chooseABootAgentStep : Unknown Wave Boot Mode : ") + (UI32) prismBootMode);
        waveAssert (false, __FILE__, __LINE__);
    }

    waveAssert (NULL != m_pWaveBootAgent, __FILE__, __LINE__);

    if (NULL == m_pWaveBootAgent)
    {
        return (WAVE_MESSAGE_ERROR);
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveFrameworkObjectManagerInitializeWorker::runTheBootAgentStep (WaveFrameworkInitializeWorkerStartServicesContext *pWaveFrameworkInitializeWorkerStartServicesContext)
{
    trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManagerInitializeWorker::runTheBootAgentStep : Entering ...");
    FrameworkSequenceGenerator &frameworkSequenceGenerator = WaveFrameworkObjectManager::getCurrentFrameworkSequenceGenerator ();

    //return (m_pWaveBootAgent->execute (pWaveFrameworkInitializeWorkerStartServicesContext->getWaveBootPhase ()));
    ResourceId status = m_pWaveBootAgent->execute (pWaveFrameworkInitializeWorkerStartServicesContext->getWaveBootPhase ());
    if (WAVE_MESSAGE_ERROR_DATABASE_INCONSISTENT == status)
    {
        WaveShutdownAgent *pShutdownAgent = new WaveShutdownAgent (m_pWaveObjectManager, frameworkSequenceGenerator);
        status = pShutdownAgent->execute ();
        delete pShutdownAgent;
        if (status != WAVE_MESSAGE_SUCCESS)
        {
            trace(TRACE_LEVEL_FATAL,"WaveFrameworkObjectManagerInitializeWorker::runTheBootAgentStep: Shutting down all services failed\n");
            return status;
        }
        else
        {
            trace (TRACE_LEVEL_INFO, string ("WaveFrameworkObjectManagerInitializeWorker::runTheBootAgentStep : Boot Mode is ") + WAVE_BOOT_FIRST_TIME);
            delete m_pWaveBootAgent;
            m_pWaveBootAgent = new RecoverWaveBootAgent (m_pWaveObjectManager, frameworkSequenceGenerator);
            status = m_pWaveBootAgent->execute (WAVE_BOOT_PHASE_PRE_PHASE);
            if (status != WAVE_MESSAGE_SUCCESS)
            {
                trace(TRACE_LEVEL_FATAL,"WaveFrameworkObjectManagerInitializeWorker::runTheBootAgentStep: Shutting down all services failed\n");
                return status;
            }
            else
            {
                delete m_pWaveBootAgent;
                m_pWaveBootAgent = new RecoverWaveBootAgent (m_pWaveObjectManager, frameworkSequenceGenerator);
                return (m_pWaveBootAgent->execute (WAVE_BOOT_PHASE_POST_PHASE));
            }
        }
    }
    else
    {
        return status;
    }
}

ResourceId WaveFrameworkObjectManagerInitializeWorker::destroyABootAgentStep (WaveFrameworkInitializeWorkerStartServicesContext *pWaveFrameworkInitializeWorkerStartServicesContext)
{
    trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManagerInitializeWorker::destroyABootAgentStep : Entering ...");

    if (NULL != m_pWaveBootAgent)
    {
        delete m_pWaveBootAgent;
    }

    m_pWaveBootAgent =  NULL;

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveFrameworkObjectManagerInitializeWorker::saveConfigurationStep (WaveFrameworkInitializeWorkerStartServicesContext *pWaveFrameworkInitializeWorkerStartServicesContext)
{
    trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManagerInitializeWorker::saveConfigurationStep : Entering ...");

    if (WAVE_MGMT_INTF_ROLE_SERVER == (FrameworkToolKit::getManagementInterfaceRole ()))
    {
        trace (TRACE_LEVEL_DEBUG, "Saving Bootstrap configuration since we successfully upgraded DB Schema in this boot cycle.");

        // 1. take a cfg file backup.
        string backupCfgFileCmd = "/bin/cp " + (WaveFrameworkObjectManager::getInstance ())->getConfigurationFileName () + " " + (WaveFrameworkObjectManager::getInstance ())->getConfigurationBackupFileName ();
        vector<string>  output;
        SI32            cmdStatus;

        cmdStatus = FrameworkToolKit::systemCommandOutput (backupCfgFileCmd, output);

        if (0 != cmdStatus)
        {
            trace (TRACE_LEVEL_WARN, "WaveFrameworkObjectManagerInitializeWorker::saveConfigurationStep: failed to make configuration fiel backup.");
            system ((string ("/bin/rm -rf ") + (WaveFrameworkObjectManager::getInstance ())->getConfigurationBackupFileName ()).c_str());
        }

        // 2. save prism configuration
        FrameworkToolKit::saveWaveConfiguration ();

        if (true == (DatabaseObjectManager::getIsDatabaseEnabled ()))
        {
            if (false == getInitialSchemaInfoObjectSaved())
            {
                tracePrintf (TRACE_LEVEL_INFO,true,false, "WaveFrameworkObjectManagerInitializeWorker::saveConfigurationStep: Saving SchemaInfoObject in database.");
                populateSchemaUpgradeTableInDb ();

                setInitialSchemaInfoObjectSaved (true);
            }
            else
            {
                tracePrintf (TRACE_LEVEL_INFO,true,false, "WaveFrameworkObjectManagerInitializeWorker::saveConfigurationStep: SchemaInfoObject is already saved.");
            }

            // 3. rename fwdl_dump_file to declare db conversion successful.
            //string databaseFwdlBackupFile   = FrameworkToolKit::getProcessInitialWorkingDirectory () + "/" + DatabaseObjectManager::getDatabaseDirectory() + "/" + FrameworkToolKit::getDatabaseBackupFileForFwdl();

            string databaseFwdlBackupFile   = FrameworkToolKit::getDatabaseBackupFileForFwdl();
            string dbConversionCompleteCmd  = "/bin/mv " + databaseFwdlBackupFile + " " + databaseFwdlBackupFile + ".done";

            system (dbConversionCompleteCmd.c_str());

            tracePrintf (TRACE_LEVEL_INFO,true,false, "WaveFrameworkObjectManagerInitializeWorker::saveConfigurationStep: executed command [%s]", dbConversionCompleteCmd.c_str());
        }

        // 4. remove the cfg backup file.
        string removeCfgBackupFile = "/bin/rm -rf " + (WaveFrameworkObjectManager::getInstance ())->getConfigurationBackupFileName ();

        system (removeCfgBackupFile.c_str());

//        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManagerInitializeWorker::saveConfigurationStep: Beginning System Call SYNC");
//        sync ();
//        trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManagerInitializeWorker::saveConfigurationStep: Ending System Call SYNC");
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveFrameworkObjectManagerInitializeWorker::informServicesToInitializeBeforeBootComplete (WaveFrameworkInitializeWorkerStartServicesContext *pWaveFrameworkInitializeWorkerStartServicesContext)
{
    trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManagerInitializeWorker::informServicesToInitializeBeforeBootComplete : Entering ...");

    if ((WAVE_BOOT_PERSISTENT == pWaveFrameworkInitializeWorkerStartServicesContext->getWaveBootMode ())
       || ((WAVE_BOOT_HASTANDBY == pWaveFrameworkInitializeWorkerStartServicesContext->getWaveBootMode ()) && (FrameworkToolKit::isPrimaryLocation () || (LOCATION_STAND_ALONE == FrameworkToolKit::getThisLocationRole ()))))
    {
        PersistenceObjectManagerInitializeBeforeBootCompleteMessage pPersistenceObjectManagerInitializeBeforeBootCompleteMessage;

        ResourceId status = sendSynchronously (&pPersistenceObjectManagerInitializeBeforeBootCompleteMessage);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManagerInitializeWorker::informServicesToInitializeBeforeBootComplete : Could not send message to Initialize Service before boot complete. Status : " + FrameworkToolKit::localize (status));
            waveAssert (false, __FILE__, __LINE__);
        }
        else
        {
            if (WAVE_MESSAGE_SUCCESS != pPersistenceObjectManagerInitializeBeforeBootCompleteMessage.getCompletionStatus ())
            {
                trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManagerInitializeWorker::informServicesToInitializeBeforeBootComplete FAILED");
                waveAssert (false, __FILE__, __LINE__);
            }
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveFrameworkObjectManagerInitializeWorker::declareBootCompleteStep (WaveFrameworkInitializeWorkerStartServicesContext *pWaveFrameworkInitializeWorkerStartServicesContext)
{
    trace (TRACE_LEVEL_DEBUG, "WaveFrameworkObjectManagerInitializeWorker::declareBootCompleteStep : Entering ...");

    if ((WAVE_BOOT_PHASE_PRE_PHASE != (pWaveFrameworkInitializeWorkerStartServicesContext->getWaveBootPhase ())) && (WAVE_BOOT_PHASE_POST_PHASE != (pWaveFrameworkInitializeWorkerStartServicesContext->getWaveBootPhase ())) && (WAVE_BOOT_PREPARE_FOR_HA_FAILOVER_PHASE != (pWaveFrameworkInitializeWorkerStartServicesContext->getWaveBootPhase ())))
    {
        PersistenceToolKit::clearConfigurationManagedObject ();

        BootCompleteForThisLocationEvent *pBootCompleteForThisLocationEvent = new BootCompleteForThisLocationEvent (pWaveFrameworkInitializeWorkerStartServicesContext->isSchemaChangedOnFwdl ());

        broadcast (pBootCompleteForThisLocationEvent);
    }
    else if ((WAVE_BOOT_HASTANDBY == pWaveFrameworkInitializeWorkerStartServicesContext->getWaveBootMode ()) && (WAVE_BOOT_PHASE_PRE_PHASE != pWaveFrameworkInitializeWorkerStartServicesContext->getWaveBootPhase ()))
    {
        // Need to broadcast HaBootComplete on standby only when the DB is not EMPTY and atleast Framework services are UP.
        HaBootCompleteForThisLocationEvent *pHaBootCompleteForThisLocationEvent = new HaBootCompleteForThisLocationEvent ();

        broadcast (pHaBootCompleteForThisLocationEvent);
    }

    setInitialBootCompleted (true);

    m_postbootDebug.initialize(); // add the debug command for postboot in shell

    return (WAVE_MESSAGE_SUCCESS);
}

bool WaveFrameworkObjectManagerInitializeWorker::getInitialBootCompleted ()
{
    bool initialBootCompleted = false;

    m_initialBootcompletedMutex.lock ();

    initialBootCompleted = m_initialBootcompleted;

    m_initialBootcompletedMutex.unlock ();

    return (initialBootCompleted);
}

void WaveFrameworkObjectManagerInitializeWorker::setInitialBootCompleted (const bool &initialBootCompleted)
{
    m_initialBootcompletedMutex.lock ();

    m_initialBootcompleted = initialBootCompleted;

    m_initialBootcompletedMutex.unlock ();
}

void WaveFrameworkObjectManagerInitializeWorker::FrameworkUpdateDatabaseSchema (FrameworkObjectManagerUpdateDatabaseSchema *pFrameworkObjectManagerUpdateDatabaseSchema)
{
    ResourceId status = WAVE_MESSAGE_SUCCESS;

    string prismConfigurationfileName   = (WaveFrameworkObjectManager::getInstance ())->getConfigurationFileName ();
    WaveFrameworkConfiguration waveFrameworkConfiguration;

    status = waveFrameworkConfiguration.loadConfiguration (prismConfigurationfileName);

    waveAssert (WAVE_MESSAGE_SUCCESS == status, __FILE__, __LINE__);

    status = performSchemaConversion(waveFrameworkConfiguration);

    pFrameworkObjectManagerUpdateDatabaseSchema->setCompletionStatus((status == FRAMEWORK_SUCCESS) ? WAVE_MESSAGE_SUCCESS: WAVE_MESSAGE_ERROR);

    reply(pFrameworkObjectManagerUpdateDatabaseSchema);

}

/*
 Function Name: populateSchemaUpgradeTableInDb
 Achieves     :
     // 1. Delete all the rows from the table for MoSchemaInfoManagedObject/DROP and CREATE a table.
     // 2. Get sql for populating all rows in the table from OrmRepository.
     // 3. apply this sql.
*/
void WaveFrameworkObjectManagerInitializeWorker::populateSchemaUpgradeTableInDb ()
{
    string sqlToDropAndCreateSchemaUpgradeTable = string ("DELETE FROM " + OrmRepository::getWaveCurrentSchema () + "." + OrmRepository::getSchemaUpgradeTableName () + ";\n"
                                                        + "DELETE FROM " + OrmRepository::getWaveStartSchema () + "." + OrmRepository::getSchemaUpgradeTableName () + ";\n");

    string sqlToInsertUpgradeTableInCurrentSchema = "";
    OrmRepository *pOrmRepository  = OrmRepository::getInstance ();
    pOrmRepository->generateSqlToPopulateUpgradeTable (sqlToInsertUpgradeTableInCurrentSchema, OrmRepository::getWaveCurrentSchema ());

    string sqlToInsertUpgradeTableInStartSchema = "";
    pOrmRepository->generateSqlToPopulateUpgradeTable (sqlToInsertUpgradeTableInStartSchema, OrmRepository::getWaveStartSchema ());

    string sqlToDropAndRecreateUpgradeTable = sqlToDropAndCreateSchemaUpgradeTable + sqlToInsertUpgradeTableInCurrentSchema + sqlToInsertUpgradeTableInStartSchema;

    trace (TRACE_LEVEL_DEBUG, "populateSchemaUpgradeTableInDb : sqlToDropAndRecreateUpgradeTable = " + sqlToDropAndRecreateUpgradeTable + "\n");

    DatabaseObjectManagerExecuteTransactionMessage message (sqlToDropAndRecreateUpgradeTable);
    ResourceId                                     status  = WAVE_MESSAGE_SUCCESS;

    status = sendSynchronously (&message);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManagerInitializeWorker::populateSchemaUpgradeTableInDb: Could not send message to create schemaInfo Object to represent the Object Relational Mapping. Status : " + FrameworkToolKit::localize (status));
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        status = message.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkObjectManagerInitializeWorker::populateSchemaUpgradeTableInDb:: failed to updated schemaInfo object in db. Status : " + FrameworkToolKit::localize (status));
            waveAssert (false, __FILE__, __LINE__);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkObjectManagerInitializeWorker::populateSchemaUpgradeTableInDb: updated schemaInfo object in db successfully.");
        }
    }

}

bool WaveFrameworkObjectManagerInitializeWorker::getInitialSchemaInfoObjectSaved ()
{
    m_initialSchemaInfoObjectSavedMutex.lock();

    bool schemaInfoSaved = m_initialSchemaInfoObjectSaved;
    m_initialSchemaInfoObjectSavedMutex.unlock ();

    return (schemaInfoSaved);
}

void WaveFrameworkObjectManagerInitializeWorker::setInitialSchemaInfoObjectSaved (bool isSchemaInfoObjectSaved)
{
    m_initialSchemaInfoObjectSavedMutex.lock ();
    m_initialSchemaInfoObjectSaved = isSchemaInfoObjectSaved;
    m_initialSchemaInfoObjectSavedMutex.unlock ();
}

}
