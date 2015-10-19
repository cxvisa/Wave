/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Boot/PersistentWithDefaultPrismBootAgent.h"
#include "Framework/Core/WaveFrameworkConfiguration.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/LocationManagement/LocationBase.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/ObjectRelationalMapping/OrmRepository.h"
#include "Framework/Database/DatabaseObjectManagerGetLatestInstanceIdForTableMessage.h"

#include <vector>

using namespace std;

namespace WaveNs
{

PersistentWithDefaultPrismBootAgent::PersistentWithDefaultPrismBootAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : PrismBootAgent (pWaveObjectManager, currentFrameworkSequenceGenerator)
{
}

PersistentWithDefaultPrismBootAgent::~PersistentWithDefaultPrismBootAgent ()
{
}

ResourceId PersistentWithDefaultPrismBootAgent::execute (const WaveBootPhase &waveBootPhase)
{
    WaveNs::PrismSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PersistentWithDefaultPrismBootAgent::createFrameworkConfigurationFromPersistedConfigurationStep),

        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PersistentWithDefaultPrismBootAgent::initializePrismServicesDuringPrePhaseStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PersistentWithDefaultPrismBootAgent::enablePrismServicesDuringPrePhaseStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PersistentWithDefaultPrismBootAgent::listenForEventsPrismServicesDuringPrePhaseStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PersistentWithDefaultPrismBootAgent::installPrismServicesDuringPrePhaseStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PersistentWithDefaultPrismBootAgent::bootPrismServicesDuringPrePhaseStep),

        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PersistentWithDefaultPrismBootAgent::databaseSanityCheckStep), 

        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PersistentWithDefaultPrismBootAgent::initializeLocalPrismServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PersistentWithDefaultPrismBootAgent::enableLocalPrismServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PersistentWithDefaultPrismBootAgent::listenForEventsLocalPrismServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PersistentWithDefaultPrismBootAgent::installLocalPrismServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PersistentWithDefaultPrismBootAgent::bootLocalPrismServicesStep),

        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PersistentWithDefaultPrismBootAgent::connectToKnownLocationsStep),

        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PersistentWithDefaultPrismBootAgent::initializeGlobalPrismServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PersistentWithDefaultPrismBootAgent::enableGlobalPrismServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PersistentWithDefaultPrismBootAgent::listenForEventsGlobalPrismServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PersistentWithDefaultPrismBootAgent::installGlobalPrismServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PersistentWithDefaultPrismBootAgent::bootGlobalPrismServicesStep),

        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PersistentWithDefaultPrismBootAgent::updateDatabaseForeignKeyConstraintsStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PersistentWithDefaultPrismBootAgent::updateUserDefinedKeyCombinationConstraintsAndKeysStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PersistentWithDefaultPrismBootAgent::prismSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PersistentWithDefaultPrismBootAgent::prismSynchronousLinearSequencerFailedStep)
    };

    PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext = new PrismSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    ResourceId status = pPrismSynchronousLinearSequencerContext->execute ();

    return (status);
}

ResourceId PersistentWithDefaultPrismBootAgent::createFrameworkConfigurationFromPersistedConfigurationStep (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext)
{
    string                      prismConfigurationfileName   = (WaveFrameworkObjectManager::getInstance ())->getConfigurationFileName ();
    WaveFrameworkConfiguration waveFrameworkConfiguration;
    ResourceId                  status                       = WAVE_MESSAGE_ERROR;

    status = waveFrameworkConfiguration.loadConfiguration (prismConfigurationfileName);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "PersistentWithDefaultPrismBootAgent::createFrameworkConfigurationFromPersistedConfigurationStep : How can this be.  We detected that there was a configuration file.  And now it is not available???");
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
        pThisLocation->setClusterPrimaryLocationId (waveFrameworkConfiguration.m_clusterPrimaryLocationId);
        pThisLocation->setClusterPrimaryPort       (waveFrameworkConfiguration.m_clusterPrimaryPort);

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

        status = WAVE_MESSAGE_SUCCESS;
    }

    return (status);
}

ResourceId PersistentWithDefaultPrismBootAgent::connectToKnownLocationsStep (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext)
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

            trace (TRACE_LEVEL_ERROR, string ("PersistentWithDefaultPrismBootAgent::createFrameworkConfigurationFromPersistedConfigurationStep : Failed to connect to ") + ipAddress + ":" + port + ".");
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

bool PersistentWithDefaultPrismBootAgent::isAPersistentBoot ()
{
    return (true);
}

WaveBootReason PersistentWithDefaultPrismBootAgent::getReason () const
{
    return (WAVE_BOOT_PERSISTENT_WITH_DEFAULT_BOOT);
}

}
