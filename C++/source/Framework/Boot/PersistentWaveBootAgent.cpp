/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Boot/PersistentWaveBootAgent.h"
#include "Framework/Core/WaveFrameworkConfiguration.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Core/FrameworkObjectManagerMessages.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/LocationManagement/LocationBase.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/ObjectRelationalMapping/OrmRepository.h"
#include "Framework/ObjectRelationalMapping/OrmTable.h"
#include "Framework/Database/DatabaseObjectManagerGetLatestInstanceIdForTableMessage.h"
#include "Framework/Database/DatabaseObjectManagerEmptyMessage.h"
#include "Framework/Database/DatabaseObjectManagerRestoreMessage.h"
#include "Framework/Database/DatabaseObjectManagerCleanPreparedTransactionsMessage.h"
#include "Cluster/Local/WaveNode.h"
#include <vector>
#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"
#include "Cluster/WaveCluster.h"
#include "Framework/ObjectModel/WaveManagedObjectToolKit.h"
#include "Framework/Persistence/PersistenceObjectManagerUpdateInstanceIdMesssage.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContext.h"

using namespace std;

namespace WaveNs
{

PersistentWaveBootAgent::PersistentWaveBootAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : WaveBootAgent (pWaveObjectManager, currentFrameworkSequenceGenerator),
      m_isRollBackDataBaseValid (false),
      m_isRollCfgFileIsValid (true),
      m_waveBootPhase (WAVE_BOOT_PHASE_ALL_PHASES)
{
}

PersistentWaveBootAgent::~PersistentWaveBootAgent ()
{
}

ResourceId PersistentWaveBootAgent::execute (const WaveBootPhase &waveBootPhase)
{
    m_waveBootPhase = waveBootPhase;

    if (WAVE_BOOT_PHASE_ALL_PHASES == m_waveBootPhase)
    {
        WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
        {
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::createFrameworkConfigurationFromPersistedConfigurationStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::initializeWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::enableWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::upgradeWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::listenForEventsWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::bootWaveServicesDuringPrePhaseStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::rollBackDataBase),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::databaseSanityCheckStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::initializeLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::enableLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::upgradeLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::listenForEventsLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::bootLocalWaveServicesStep),

            //reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::connectToKnownLocationsStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::initializeGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::enableGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::upgradeGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::listenForEventsGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::bootGlobalWaveServicesStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::updateDatabaseForeignKeyConstraintsStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::updateUserDefinedKeyCombinationConstraintsAndKeysStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::waveSynchronousLinearSequencerSucceededStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::waveSynchronousLinearSequencerFailedStep)
        };
    
        WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext = new WaveSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

        ResourceId status = pWaveSynchronousLinearSequencerContext->execute ();
        
        // Cleanup Upgrade data structures after Persistent boot 

        /* FIXME: Commenting it for now as this will be required while executing BIST for db_conversion. Can be uncommented once Unit testing is done.
                  Moreover this celanup should happen in all boot mode cases when getDetectSchemaChange is true and not only in persistent boot.
        if (true ==  FrameworkToolKit::getDetectSchemaChange ())
        {
            OrmRepository *pOrmRepository = OrmRepository::getInstance ();

            pOrmRepository->getMOSchemaInfoRepository().cleanupSchemaDifferenceInfo ();
            vector<string> tableNames = pOrmRepository->getTableNames (); 
        
            for (unsigned int i=0; i < tableNames.size (); i++)
            {
                (pOrmRepository->getTableByName (tableNames[i]))->cleanupManagedObjectAttributes ();
            }
        }*/

        return (status);
    }
    else if (WAVE_BOOT_PREPARE_FOR_HA_FAILOVER_PHASE == m_waveBootPhase)
    {
        WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
        {
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::resetLocationRole),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::initializeWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::enableWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::listenForEventsWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::bootWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::rollBackDataBase),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::initializeLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::enableLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::listenForEventsLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::bootLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::initializeGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::enableGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::listenForEventsGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::bootGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::waveSynchronousLinearSequencerSucceededStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::waveSynchronousLinearSequencerFailedStep)
        };

        WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext = new WaveSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

        ResourceId status = pWaveSynchronousLinearSequencerContext->execute ();

        return (status);
    }
    else if (WAVE_BOOT_ROLL_BACK_BOOT_PHASE_BEFORE_PHASE_0 == m_waveBootPhase)
    {
        WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
        {
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::createFrameworkConfigurationFromPersistedConfigurationStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::initializeWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::enableWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::listenForEventsWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::bootWaveServicesDuringPrePhaseStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::rollBackDataBase),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::initializeLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::enableLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::listenForEventsLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::bootLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::initializeGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::enableGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::listenForEventsGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::bootGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::backendSyncUpStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::waveSynchronousLinearSequencerSucceededStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::waveSynchronousLinearSequencerFailedStep)
        };

        WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext = new WaveSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

        ResourceId status = pWaveSynchronousLinearSequencerContext->execute ();

        return (status);
    }
    else if (WAVE_BOOT_ROLL_BACK_BOOT_PHASE == m_waveBootPhase)
    {
        WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
        {
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::resetLocationRole),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::disconnectFromAllConnectedLocations),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::initializeGlobalWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::enableGlobalWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::listenForEventsGlobalServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::bootGlobalWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::rollBackDataBase),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::initializeLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::enableLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::listenForEventsLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::bootLocalWaveServicesStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::initializeGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::enableGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::listenForEventsGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::bootGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::backendSyncUpStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::waveSynchronousLinearSequencerSucceededStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::waveSynchronousLinearSequencerFailedStep)
        };
    
        WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext = new WaveSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

        ResourceId status = pWaveSynchronousLinearSequencerContext->execute ();

        return (status);
    }
    else if (WAVE_BOOT_ROLL_BACK_BOOT_PHASE_AFTER_PHASE_2 == m_waveBootPhase)
    {
        WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
        {

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::resetLocationRole),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::disconnectFromAllConnectedLocations),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::initializeWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::enableWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::listenForEventsWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::bootWaveServicesDuringPrePhaseStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::rollBackDataBase),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::initializeLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::enableLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::listenForEventsLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::bootLocalWaveServicesStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::initializeGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::enableGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::listenForEventsGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::bootGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::backendSyncUpStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::waveSynchronousLinearSequencerSucceededStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::waveSynchronousLinearSequencerFailedStep)
        };

        WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext = new WaveSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

        ResourceId status = pWaveSynchronousLinearSequencerContext->execute ();

        return (status);
    
    }
    else if (WAVE_BOOT_RESET_NODE_TO_UNCONFIRM_ROLE == m_waveBootPhase)
    {
        WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
        {

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::resetLocationRole),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::disconnectFromAllConnectedLocations),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::initializeGlobalWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::enableGlobalWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::listenForEventsGlobalServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::bootGlobalWaveServicesDuringPrePhaseStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::initializeGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::enableGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::listenForEventsGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::bootGlobalWaveServicesStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::waveSynchronousLinearSequencerSucceededStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWaveBootAgent::waveSynchronousLinearSequencerFailedStep)
        };

        WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext = new WaveSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

        ResourceId status = pWaveSynchronousLinearSequencerContext->execute ();

        return (status);
    }
    else
    {
        return (WAVE_MESSAGE_ERROR);
    }

}

ResourceId PersistentWaveBootAgent::disconnectFromAllConnectedLocations (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    (WaveFrameworkObjectManager::getInstance())->disconnectFromAllKnownLocations ();

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId PersistentWaveBootAgent::resetLocationRole (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    LocationBase *pThisLocation = (WaveFrameworkObjectManager::getInstance ())->getThisLocation ();

    waveAssert (NULL != pThisLocation, __FILE__, __LINE__);

    LocationRole    thisLocationRole = pThisLocation->getLocationRole ();
 
    if ((LOCATION_SECONDARY_CLUSTER_PHASE_0 == thisLocationRole) || (LOCATION_SECONDARY_CLUSTER_PHASE_1 == thisLocationRole) || (LOCATION_SECONDARY_CLUSTER_PHASE_2 == thisLocationRole) || (LOCATION_SECONDARY_CLUSTER_PHASE_3 == thisLocationRole))
    {
        pThisLocation->setLocationRole (LOCATION_STAND_ALONE);
        pThisLocation->setClusterPrimaryLocationId (pThisLocation->getLocationId ());
        pThisLocation->setClusterPrimaryPort       (pThisLocation->getPort ());

        m_isRollBackDataBaseValid = true;
    }
    else if ((LOCATION_SECONDARY_REJOIN_PHASE_0 == thisLocationRole) || (LOCATION_SECONDARY_REJOIN_PHASE_1 == thisLocationRole) || (LOCATION_SECONDARY_REJOIN_PHASE_2 == thisLocationRole) || (LOCATION_SECONDARY_REJOIN_PHASE_3 == thisLocationRole))
    {
        m_isRollBackDataBaseValid = true;

        pThisLocation->setLocationRole (LOCATION_SECONDARY_UNCONFIRMED);
        pThisLocation->setClusterPrimaryLocationId (pThisLocation->getLocationId ());
        pThisLocation->setClusterPrimaryPort       (pThisLocation->getPort ());
    }
    else if ((LOCATION_SECONDARY == thisLocationRole) || (LOCATION_SECONDARY_UNCONFIRMED == thisLocationRole) || (LOCATION_PRIMARY_UNCONFIRMED == thisLocationRole))
    {
        pThisLocation->setLocationRole (LOCATION_SECONDARY_UNCONFIRMED);    

        pThisLocation->setClusterPrimaryLocationId (pThisLocation->getLocationId ());
        pThisLocation->setClusterPrimaryPort       (pThisLocation->getPort ());
    }
    else if (LOCATION_PRIMARY == thisLocationRole)
    {
        pThisLocation->setLocationRole (LOCATION_PRIMARY_UNCONFIRMED);    

        pThisLocation->setClusterPrimaryLocationId (pThisLocation->getLocationId ());
        pThisLocation->setClusterPrimaryPort       (pThisLocation->getPort ());
    }
    else if (LOCATION_STAND_ALONE == thisLocationRole)
    {
        pThisLocation->setClusterPrimaryLocationId (pThisLocation->getLocationId ());
        pThisLocation->setClusterPrimaryPort       (pThisLocation->getPort ());
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, "There is no other Phase Possible for timer timeout");

        waveAssert (false, __FILE__, __LINE__);

        return (WAVE_MESSAGE_ERROR);
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId PersistentWaveBootAgent::createFrameworkConfigurationFromPersistedConfigurationStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    string                      waveConfigurationfileName   = (WaveFrameworkObjectManager::getInstance ())->getConfigurationFileName ();
    WaveFrameworkConfiguration waveFrameworkConfiguration;
    ResourceId                  status                       = WAVE_MESSAGE_ERROR;

    status = waveFrameworkConfiguration.loadConfiguration (waveConfigurationfileName);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "PersistentWaveBootAgent::createFrameworkConfigurationFromPersistedConfigurationStep : How can this be.  We detected that there was a configuration file.  And now it is not available???");
        waveAssert (false, __FILE__, __LINE__);

        status = WAVE_MESSAGE_ERROR;
    }
    else
    {
        LocationBase *pThisLocation = (WaveFrameworkObjectManager::getInstance ())->getThisLocation ();

        waveAssert (NULL != pThisLocation, __FILE__, __LINE__);

        FrameworkToolKit::setLastUsedLocationId (waveFrameworkConfiguration.m_lastUsedLocationId);

        pThisLocation->setLocationRole             (static_cast<LocationRole> (waveFrameworkConfiguration.m_thisLocationRole));
        pThisLocation->setLocationId               (waveFrameworkConfiguration.m_thisLocationLocationId);
        pThisLocation->resetIpAddress              (waveFrameworkConfiguration.m_thisLocationIpAddress);

        FrameworkToolKit::setIsDbRestoreIncomplete (waveFrameworkConfiguration.m_dbRestoreIncomplete);

        if (LOCATION_STAND_ALONE == (pThisLocation->getLocationRole ()))
        {
            trace (TRACE_LEVEL_INFO, "PersistentWaveBootAgent::createFrameworkConfigurationFromPersistedConfigurationStep : Setting Location Role To : " + FrameworkToolKit::localize (LOCATION_STAND_ALONE));

            pThisLocation->setClusterPrimaryLocationId (waveFrameworkConfiguration.m_clusterPrimaryLocationId);
            pThisLocation->setClusterPrimaryPort       (waveFrameworkConfiguration.m_clusterPrimaryPort);
        }
        else
        {
            if (WAVE_BOOT_ROLL_BACK_BOOT_PHASE_BEFORE_PHASE_0 == m_waveBootPhase)
            {
                // this can happen only when in unconfirmed state this node receive rejoin request and node failed in phase 0 before setting state as phase 0
                m_isRollBackDataBaseValid = false;

                (WaveFrameworkObjectManager::getInstance ())->setIsStartupValid (waveFrameworkConfiguration.m_isStartupValid);
                (WaveFrameworkObjectManager::getInstance ())->setStartupFileType (waveFrameworkConfiguration.m_startupFileType);
                (WaveFrameworkObjectManager::getInstance ())->setStartupFileName (waveFrameworkConfiguration.m_startupFileName);

                pThisLocation->setClusterPrimaryLocationId (pThisLocation->getLocationId ());
                pThisLocation->setClusterPrimaryPort       (pThisLocation->getPort ());

                pThisLocation->setLocationRole (LOCATION_SECONDARY_UNCONFIRMED);

                return (WAVE_MESSAGE_SUCCESS);
            }
            else if (LOCATION_PRIMARY == (pThisLocation->getLocationRole ()))
            {
                trace (TRACE_LEVEL_INFO, "PersistentWaveBootAgent::createFrameworkConfigurationFromPersistedConfigurationStep : Re-Setting Location Role To : " + FrameworkToolKit::localize (LOCATION_PRIMARY_UNCONFIRMED));

                pThisLocation->setLocationRole (LOCATION_PRIMARY_UNCONFIRMED);
            }
            else if (LOCATION_SECONDARY == (pThisLocation->getLocationRole ()))
            {
                trace (TRACE_LEVEL_INFO, "PersistentWaveBootAgent::createFrameworkConfigurationFromPersistedConfigurationStep : Re-Setting Location Role To : " + FrameworkToolKit::localize (LOCATION_SECONDARY_UNCONFIRMED));

                pThisLocation->setLocationRole (LOCATION_SECONDARY_UNCONFIRMED);
            }
            else if ((LOCATION_SECONDARY_CLUSTER_PHASE_0 == (pThisLocation->getLocationRole ())) || (LOCATION_SECONDARY_CLUSTER_PHASE_1 == (pThisLocation->getLocationRole ())) || (LOCATION_SECONDARY_CLUSTER_PHASE_2 == (pThisLocation->getLocationRole ())) || (LOCATION_SECONDARY_CLUSTER_PHASE_3 == (pThisLocation->getLocationRole ())))
            {
                pThisLocation->setLocationRole (LOCATION_STAND_ALONE);

                // if dbRestoreIncomplete flag is set then restoring the db will be taken care in PersistenceOM::boot. Hence, no need to execute rollBackDataBase again here. 

                 m_isRollBackDataBaseValid = (true == waveFrameworkConfiguration.m_dbRestoreIncomplete) ? false : true;    

                (WaveFrameworkObjectManager::getInstance ())->setIsStartupValid (waveFrameworkConfiguration.m_isStartupValid);
                (WaveFrameworkObjectManager::getInstance ())->setStartupFileType (waveFrameworkConfiguration.m_startupFileType);
                (WaveFrameworkObjectManager::getInstance ())->setStartupFileName (waveFrameworkConfiguration.m_startupFileName);

                pThisLocation->setClusterPrimaryLocationId (pThisLocation->getLocationId ());
                pThisLocation->setClusterPrimaryPort       (pThisLocation->getPort ());                
            
                return (WAVE_MESSAGE_SUCCESS);    
            }
            else if ((LOCATION_SECONDARY_REJOIN_PHASE_0 == pThisLocation->getLocationRole ()) || (LOCATION_SECONDARY_REJOIN_PHASE_1 == pThisLocation->getLocationRole ()) || (LOCATION_SECONDARY_REJOIN_PHASE_2 == pThisLocation->getLocationRole ()) || (LOCATION_SECONDARY_REJOIN_PHASE_3 == pThisLocation->getLocationRole ()))
            {
               trace (TRACE_LEVEL_INFO, "PersistentWaveBootAgent::createFrameworkConfigurationFromPersistedConfigurationStep : Handling Reboot in the middle of Rejoin Phase , Re-Setting Location Role To : " + FrameworkToolKit::localize (LOCATION_SECONDARY_UNCONFIRMED));

                m_isRollBackDataBaseValid = true;

                pThisLocation->setLocationRole (LOCATION_SECONDARY_UNCONFIRMED);
            }
    
            pThisLocation->setClusterPrimaryLocationId (pThisLocation->getLocationId ());
            pThisLocation->setClusterPrimaryPort       (pThisLocation->getPort ());
        }

        UI32 numberOfKnownLocations = waveFrameworkConfiguration.m_knownLocationIpAddresses.size ();
        UI32 i                      = 0;

        for (i = 0; i < numberOfKnownLocations; i++)
        {
            pThisLocation->addKnownLocation (waveFrameworkConfiguration.m_knownLocationLocationIds[i], waveFrameworkConfiguration.m_knownLocationIpAddresses[i], waveFrameworkConfiguration.m_knownLocationPorts[i]);
        }

        UI32 numberOfKnownSubLocations = waveFrameworkConfiguration.m_knownSubLocationIpAddresses.size ();

        for (i = 0; i < numberOfKnownSubLocations; i++)
        {
            pThisLocation->addSubLocation (waveFrameworkConfiguration.m_knownSubLocationLocationIds[i], waveFrameworkConfiguration.m_knownSubLocationIpAddresses[i], waveFrameworkConfiguration.m_knownSubLocationPorts[i]);
        }

        (WaveFrameworkObjectManager::getInstance ())->setIsStartupValid (waveFrameworkConfiguration.m_isStartupValid);
        (WaveFrameworkObjectManager::getInstance ())->setStartupFileType (waveFrameworkConfiguration.m_startupFileType);
        (WaveFrameworkObjectManager::getInstance ())->setStartupFileName (waveFrameworkConfiguration.m_startupFileName);


        // if dbRestoreIncomplete flag is set then restoring the db will be taken care in PersistenceOM::boot. Hence, no need to execute rollBackDataBase again here. 
        if (true == waveFrameworkConfiguration.m_dbRestoreIncomplete)
        {
            m_isRollBackDataBaseValid = false;    
        }

        status = WAVE_MESSAGE_SUCCESS;
    }

    return (status);
}

ResourceId PersistentWaveBootAgent::connectToKnownLocationsStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    LocationBase       *pThisLocation                = (WaveFrameworkObjectManager::getInstance ())->getThisLocation ();
    vector<LocationId>  knownRemoteLocations;
    UI32                numberOfKnownRemoteLocations = 0;
    UI32                i                            = 0;
    string              ipAddress                    = "";
    SI32                port                         = 0;

    waveAssert (NULL != pThisLocation, __FILE__, __LINE__);

    pThisLocation->getKnownRemoteLocations (knownRemoteLocations);
    numberOfKnownRemoteLocations = knownRemoteLocations.size ();

    for (i = 0; i < numberOfKnownRemoteLocations; i++)
    {
        ResourceId connectionStatus = pThisLocation->connectToRemoteLocation (knownRemoteLocations[i], 60, 60);

        if (FRAMEWORK_SUCCESS != connectionStatus)
        {
            ipAddress = FrameworkToolKit::getIpAddressForLocationId (knownRemoteLocations[i]);
            port      = FrameworkToolKit::getPortForLocationId (knownRemoteLocations[i]);

            trace (TRACE_LEVEL_ERROR, string ("PersistentWaveBootAgent::connectToKnownLocationsStep : Failed to connect to ") + ipAddress + ":" + port + ".");
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId PersistentWaveBootAgent::rollBackDataBase (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    trace (TRACE_LEVEL_INFO, string("PersistentWaveBootAgent::rollBackDataBase: m_isRollBackDataBaseValid = ") + m_isRollBackDataBaseValid);
    if (false == m_isRollBackDataBaseValid)
    {
        return (WAVE_MESSAGE_SUCCESS);
    }

    // removing the cfg file to make sure if node rebooted in the middle of rollback.It should come clean.

    const string    waveConfigurationfileName   = (WaveFrameworkObjectManager::getInstance ())->getConfigurationFileName ();
    vector<string>  output;
    SI32            cmdStatus                    = 0;

    trace (TRACE_LEVEL_WARN, string ("PersistentWaveBootAgent::rollBackDataBase: deleting file ") + waveConfigurationfileName);

    cmdStatus = FrameworkToolKit::systemCommandOutput ((string ("/bin/rm -rf ") + waveConfigurationfileName).c_str(), output);

    if ( cmdStatus != 0 )
    {        
        trace (TRACE_LEVEL_ERROR, string("PersistentWaveBootAgent::rollBackDataBase: Cmd to delete file ")+ waveConfigurationfileName + string(" failed with error message : ") + output[0]);
    }

    cleanPreparedTransactions ();
    emptyDatabaseToRollBack ();
    reloadPreviousDataBase  ();

    if ( (WAVE_MESSAGE_SUCCESS == FrameworkToolKit::isConnectedToHaPeerLocation ()) && (true == FrameworkToolKit::getIsLiveSyncEnabled ()) )
    {
        trace (TRACE_LEVEL_INFO, "PersistentWaveBootAgent::rollBackDatabase: Rollback database on standby is triggered");

        FrameworkObjectManagerRollbackStandbyOnActiveRollbackMessage rollbackStandbyOnActiveRollbackMessage;
        ResourceId                                                   status = WAVE_MESSAGE_SUCCESS;

        status = sendSynchronously (&rollbackStandbyOnActiveRollbackMessage, FrameworkToolKit::getHaPeerLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "PersistentWaveBootAgent::rollBackDataBase: Unable to perform rollback on STANDBY. Status: " + FrameworkToolKit::localize (status));
            FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
        }
        else
        {
            status = rollbackStandbyOnActiveRollbackMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS == status)
            {
                trace (TRACE_LEVEL_INFO, "PersistentWaveBootAgent::rollBackDataBase: Succeeded in performing rollback on STANDBY.");
            }
            else
            {
                trace (TRACE_LEVEL_ERROR, "PersistentWaveBootAgent::rollBackDataBase: Failed to perform rollback on STANDBY. Status: " + FrameworkToolKit::localize (status));
                FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_FAILED);
            }
        }
    }
    else if ((FrameworkToolKit::getSyncState () == IN_SYNC) && (false == FrameworkToolKit::getIsLiveSyncEnabled ()))
    {
        // DB previously in sync from sync dump. but live transaction sync not supported. So set out of sync and notify on sync update fail
        trace (TRACE_LEVEL_WARN, "PersistentWaveBootAgent::rollBackDataBase: Live sync disabled. Notify sync update failure on first update after sync dump.");
        FrameworkToolKit::notifySyncUpdateFailure(WAVE_MESSAGE_ERROR_CLUSTER_DB_HASYNC_NOT_SUPPORTED);
    }
    else
    {
        trace (TRACE_LEVEL_INFO, "PersistentWaveBootAgent::rollBackDatabase: Rollback db on standby will not be initiated as Peer is disconnected.");
    }

    if (true == m_isRollCfgFileIsValid)
    {
        FrameworkToolKit::rollbackCfgFile ();
    }
    else
    {
        m_isRollCfgFileIsValid = true;
    }

    FrameworkToolKit::saveWaveConfiguration (true);

    PersistenceObjectManagerUpdateInstanceIdMesssage message;

    ResourceId  status  = sendSynchronously (&message); 

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "PersistentWaveBootAgent::rollBackDataBase : Could not send message to update instance Id.  Status : " + FrameworkToolKit::localize (status));
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        status = message.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "PersistentWaveBootAgent::rollBackDataBase : Not able to update Instance Id  Completion Status : " + FrameworkToolKit::localize (status));
            waveAssert (false, __FILE__, __LINE__);
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

void PersistentWaveBootAgent::cleanPreparedTransactions ()
{
    trace (TRACE_LEVEL_INFO, "PersistentWaveBootAgent::cleanPreparedTransactions: Entering ...");

    DatabaseObjectManagerCleanPreparedTransactionsMessage databaseObjectManagerCleanPreparedTransactionsMessage;
    ResourceId                                            cleanPreparedTransactionsStatus                        = WAVE_MESSAGE_SUCCESS;

    cleanPreparedTransactionsStatus = sendSynchronously (&databaseObjectManagerCleanPreparedTransactionsMessage); 

    if (WAVE_MESSAGE_SUCCESS != cleanPreparedTransactionsStatus)
    {
        trace (TRACE_LEVEL_FATAL, "PersistentWaveBootAgent::cleanPreparedTransactions: Could not send message to Clean Prepared Transactions. Status : " + FrameworkToolKit::localize (cleanPreparedTransactionsStatus));
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        cleanPreparedTransactionsStatus = databaseObjectManagerCleanPreparedTransactionsMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS == cleanPreparedTransactionsStatus)
        {
            trace (TRACE_LEVEL_INFO, "PersistentWaveBootAgent::cleanPreparedTransactions: Succeeded in cleaning previously Prepared Transactions.");
        }
        else
        {
            trace (TRACE_LEVEL_FATAL, "PersistentWaveBootAgent::cleanPreparedTransactions: Failed to clean previously Prepared Transactions. Status : " + FrameworkToolKit::localize (cleanPreparedTransactionsStatus));
            waveAssert (false, __FILE__, __LINE__);
        }
    }
}

void PersistentWaveBootAgent::emptyDatabaseToRollBack ()
{
    trace (TRACE_LEVEL_INFO, "PersistentWaveBootAgent::emptyDatabaseToRollBack Entering ...");

    DatabaseObjectManagerEmptyMessage message;
    ResourceId                        status  = sendSynchronously (&message);

    if (WAVE_MESSAGE_SUCCESS != status)
    {         trace (TRACE_LEVEL_FATAL, "PersistentWaveBootAgent::emptyDatabaseToRollBack : Could not send message to empty database.  Status : " + FrameworkToolKit::localize (status));
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        status = message.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "PersistentWaveBootAgent::emptyDatabaseToRollBack : Message to empty database failed.  Completion Status : " + FrameworkToolKit::localize (status));
            waveAssert (false, __FILE__, __LINE__);
        }
    }
}

void PersistentWaveBootAgent::reloadPreviousDataBase ()
{
    trace (TRACE_LEVEL_INFO, "PersistentWaveBootAgent::reloadPreviousDataBase Entering....");

    string backupFileName = string (FrameworkToolKit::getProcessInitialWorkingDirectory () + "/" + FrameworkToolKit::getDatabaseBackupFileName2 ());

    DatabaseObjectManagerRestoreMessage message (backupFileName);
    message.setDataOnlyRestore (true);

    ResourceId                          status  = sendSynchronously (&message);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "PersistentWaveBootAgent::reloadPreviousDataBase : Could not send message to restore database.  Status : " + FrameworkToolKit::localize (status));
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        status = message.getCompletionStatus ();

        if (WAVE_MESSAGE_ERROR_DB_RESTORE_FAILED == status)
        {
            trace (TRACE_LEVEL_FATAL, "PersistentWaveBootAgent::reloadPreviousDataBase : Not Able to Restore DB from Backed Up File. Completion Status : " + FrameworkToolKit::localize (status));
            trace (TRACE_LEVEL_FATAL, "PersistentWaveBootAgent::reloadPreviousDataBase : Going For Extreme Recovery By going to default/startup configuration");

            status = FrameworkToolKit::changeWaveConfigurationValidity ( false );
            if ( status != WAVE_MESSAGE_SUCCESS  )
            {
                trace (TRACE_LEVEL_FATAL, ("PersistentWaveBootAgent::reloadPreviousDataBase : Removing CFG file failed in extreme Recoverycase "));
            }
            int rc = system ("/sbin/reboot -f");

            if (0 != rc)
            {
                // handle the error
            }

            sleep (300);
    
            trace (TRACE_LEVEL_FATAL, ("System is not rebooting, Manual recovery is required"));
        
            waveAssert (false, __FILE__, __LINE__);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "PersistentWaveBootAgent::reloadPreviousDataBase : SUCCESSFULLY rollback to the last known valid previous DB configuration.");
        }
    }
}

bool PersistentWaveBootAgent::isAPersistentBoot ()
{
    return (true);
}

WaveBootReason PersistentWaveBootAgent::getReason () const
{
    return (WAVE_BOOT_PERSISTENT_BOOT);
}

bool PersistentWaveBootAgent::isToBeExcludedForEnableAndBoot (const WaveServiceId& waveServiceId)
{
    if ((WAVE_BOOT_ROLL_BACK_BOOT_PHASE == m_waveBootPhase) || (WAVE_BOOT_ROLL_BACK_BOOT_PHASE_AFTER_PHASE_2 == m_waveBootPhase) || (WAVE_BOOT_RESET_NODE_TO_UNCONFIRM_ROLE == m_waveBootPhase) || (WAVE_BOOT_ROLL_BACK_BOOT_PHASE_BEFORE_PHASE_0 == m_waveBootPhase) || (WAVE_BOOT_PREPARE_FOR_HA_FAILOVER_PHASE == m_waveBootPhase))
    {
        if (((WaveFrameworkObjectManager::getWaveServiceId ()) == waveServiceId) || (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }
    else
    {
        return (false);
    }
}

bool PersistentWaveBootAgent::isToBeExcludedFromInitializeDuringPrePhase (const WaveServiceId &waveServiceId)
{
    if ((WAVE_BOOT_ROLL_BACK_BOOT_PHASE == m_waveBootPhase) || (WAVE_BOOT_ROLL_BACK_BOOT_PHASE_AFTER_PHASE_2 == m_waveBootPhase) || (WAVE_BOOT_RESET_NODE_TO_UNCONFIRM_ROLE == m_waveBootPhase) || (WAVE_BOOT_ROLL_BACK_BOOT_PHASE_BEFORE_PHASE_0 == m_waveBootPhase) || (WAVE_BOOT_PREPARE_FOR_HA_FAILOVER_PHASE == m_waveBootPhase))
    {
        if (((WaveFrameworkObjectManager::getWaveServiceId ()) == waveServiceId) || (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }
    else
    {
        return (false);
    }
}

bool PersistentWaveBootAgent::isToBeExcludedFromInitializePhase (const WaveServiceId &waveServiceId)
{
    if ((WAVE_BOOT_ROLL_BACK_BOOT_PHASE == m_waveBootPhase) || (WAVE_BOOT_ROLL_BACK_BOOT_PHASE_AFTER_PHASE_2 == m_waveBootPhase) || (WAVE_BOOT_RESET_NODE_TO_UNCONFIRM_ROLE == m_waveBootPhase) || (WAVE_BOOT_ROLL_BACK_BOOT_PHASE_BEFORE_PHASE_0 == m_waveBootPhase) || (WAVE_BOOT_PREPARE_FOR_HA_FAILOVER_PHASE == m_waveBootPhase))
    {
        if (((WaveFrameworkObjectManager::getWaveServiceId ()) == waveServiceId) || (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }
    else
    {
        return (false);
    }
}

bool PersistentWaveBootAgent::getRollBackFlag () const
{
    if ((WAVE_BOOT_ROLL_BACK_BOOT_PHASE == m_waveBootPhase) || (WAVE_BOOT_ROLL_BACK_BOOT_PHASE_AFTER_PHASE_2 == m_waveBootPhase) || (WAVE_BOOT_ROLL_BACK_BOOT_PHASE_BEFORE_PHASE_0 == m_waveBootPhase))
    {
        return (true);
    }

    return (false);
}

}
