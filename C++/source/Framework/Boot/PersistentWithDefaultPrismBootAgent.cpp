/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Boot/PersistentWithDefaultWaveBootAgent.h"
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

PersistentWithDefaultWaveBootAgent::PersistentWithDefaultWaveBootAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : WaveBootAgent (pWaveObjectManager, currentFrameworkSequenceGenerator)
{
}

PersistentWithDefaultWaveBootAgent::~PersistentWithDefaultWaveBootAgent ()
{
}

ResourceId PersistentWithDefaultWaveBootAgent::execute (const WaveBootPhase &waveBootPhase)
{
    WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultWaveBootAgent::createFrameworkConfigurationFromPersistedConfigurationStep),

        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultWaveBootAgent::initializeWaveServicesDuringPrePhaseStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultWaveBootAgent::enableWaveServicesDuringPrePhaseStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultWaveBootAgent::listenForEventsWaveServicesDuringPrePhaseStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultWaveBootAgent::installWaveServicesDuringPrePhaseStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultWaveBootAgent::bootWaveServicesDuringPrePhaseStep),

        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultWaveBootAgent::databaseSanityCheckStep), 

        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultWaveBootAgent::initializeLocalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultWaveBootAgent::enableLocalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultWaveBootAgent::listenForEventsLocalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultWaveBootAgent::installLocalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultWaveBootAgent::bootLocalWaveServicesStep),

        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultWaveBootAgent::connectToKnownLocationsStep),

        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultWaveBootAgent::initializeGlobalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultWaveBootAgent::enableGlobalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultWaveBootAgent::listenForEventsGlobalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultWaveBootAgent::installGlobalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultWaveBootAgent::bootGlobalWaveServicesStep),

        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultWaveBootAgent::updateDatabaseForeignKeyConstraintsStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultWaveBootAgent::updateUserDefinedKeyCombinationConstraintsAndKeysStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultWaveBootAgent::prismSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultWaveBootAgent::prismSynchronousLinearSequencerFailedStep)
    };

    WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext = new WaveSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    ResourceId status = pWaveSynchronousLinearSequencerContext->execute ();

    return (status);
}

ResourceId PersistentWithDefaultWaveBootAgent::createFrameworkConfigurationFromPersistedConfigurationStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    string                      prismConfigurationfileName   = (WaveFrameworkObjectManager::getInstance ())->getConfigurationFileName ();
    WaveFrameworkConfiguration waveFrameworkConfiguration;
    ResourceId                  status                       = WAVE_MESSAGE_ERROR;

    status = waveFrameworkConfiguration.loadConfiguration (prismConfigurationfileName);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "PersistentWithDefaultWaveBootAgent::createFrameworkConfigurationFromPersistedConfigurationStep : How can this be.  We detected that there was a configuration file.  And now it is not available???");
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

ResourceId PersistentWithDefaultWaveBootAgent::connectToKnownLocationsStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
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

            trace (TRACE_LEVEL_ERROR, string ("PersistentWithDefaultWaveBootAgent::createFrameworkConfigurationFromPersistedConfigurationStep : Failed to connect to ") + ipAddress + ":" + port + ".");
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

bool PersistentWithDefaultWaveBootAgent::isAPersistentBoot ()
{
    return (true);
}

WaveBootReason PersistentWithDefaultWaveBootAgent::getReason () const
{
    return (WAVE_BOOT_PERSISTENT_WITH_DEFAULT_BOOT);
}

}
