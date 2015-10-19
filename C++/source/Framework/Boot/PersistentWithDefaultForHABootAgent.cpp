/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#include "Framework/Boot/PersistentWithDefaultForHABootAgent.h"
#include "Framework/Core/WaveFrameworkConfiguration.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/LocationManagement/LocationBase.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/ObjectRelationalMapping/OrmRepository.h"
#include "Framework/Database/DatabaseObjectManagerGetLatestInstanceIdForTableMessage.h"
#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"
#include "Framework/Database/DatabaseObjectManager.h"

#include <vector>

using namespace std;

namespace WaveNs
{

PersistentWithDefaultForHABootAgent::PersistentWithDefaultForHABootAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : WaveBootAgent (pWaveObjectManager, currentFrameworkSequenceGenerator)
{
}

PersistentWithDefaultForHABootAgent::~PersistentWithDefaultForHABootAgent ()
{
}

ResourceId PersistentWithDefaultForHABootAgent::execute (const WaveBootPhase &waveBootPhase)
{
    WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultForHABootAgent::createFrameworkConfigurationFromPersistedConfigurationStep),

        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultForHABootAgent::initializeWaveServicesDuringPrePhaseStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultForHABootAgent::enableWaveServicesDuringPrePhaseStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultForHABootAgent::listenForEventsWaveServicesDuringPrePhaseStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultForHABootAgent::installWaveServicesDuringPrePhaseStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultForHABootAgent::bootWaveServicesDuringPrePhaseStep),

        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultForHABootAgent::initializeLocalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultForHABootAgent::enableLocalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultForHABootAgent::listenForEventsLocalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultForHABootAgent::installLocalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultForHABootAgent::bootLocalWaveServicesStep),


        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultForHABootAgent::initializeGlobalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultForHABootAgent::enableGlobalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultForHABootAgent::listenForEventsGlobalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultForHABootAgent::installGlobalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultForHABootAgent::bootGlobalWaveServicesStep),

        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultForHABootAgent::waveSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&PersistentWithDefaultForHABootAgent::waveSynchronousLinearSequencerFailedStep)
    };

    WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext = new WaveSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    ResourceId status = pWaveSynchronousLinearSequencerContext->execute ();

    return (status);
}

ResourceId PersistentWithDefaultForHABootAgent::createFrameworkConfigurationFromPersistedConfigurationStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    string                      waveConfigurationfileName   = (WaveFrameworkObjectManager::getInstance ())->getConfigurationFileName ();
    WaveFrameworkConfiguration waveFrameworkConfiguration;
    ResourceId                  status                       = WAVE_MESSAGE_ERROR;

    status = waveFrameworkConfiguration.loadConfiguration (waveConfigurationfileName);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "PersistentWithDefaultForHABootAgent::createFrameworkConfigurationFromPersistedConfigurationStep : How can this be.  We detected that there was a configuration file.  And now it is not available???");
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

ResourceId PersistentWithDefaultForHABootAgent::connectToKnownLocationsStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
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

            trace (TRACE_LEVEL_ERROR, string ("PersistentWithDefaultForHABootAgent::createFrameworkConfigurationFromPersistedConfigurationStep : Failed to connect to ") + ipAddress + ":" + port + ".");
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

bool PersistentWithDefaultForHABootAgent::isAPersistentBoot ()
{
    return (true);
}

WaveBootReason PersistentWithDefaultForHABootAgent::getReason () const
{
    return (WAVE_BOOT_PERSISTENT_WITH_DEFAULT_BOOT);
}

bool PersistentWithDefaultForHABootAgent::isToBeExcludedFromInitializeDuringPrePhase (const WaveServiceId &waveServiceId)
{
    if (((WaveFrameworkObjectManager::getWaveServiceId               ()) == waveServiceId) ||
        (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

bool PersistentWithDefaultForHABootAgent::isToBeExcludedForEnableAndBoot (const WaveServiceId& waveServiceId)
{
    if (((WaveFrameworkObjectManager::getWaveServiceId               ()) == waveServiceId) ||
        (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

bool PersistentWithDefaultForHABootAgent::isToBeExcludedFromInstallDuringPrePhase (const WaveServiceId &waveServiceId)
{
    if ((waveServiceId == (DatabaseObjectManager::getWaveServiceId ())) ||
        (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

bool PersistentWithDefaultForHABootAgent::isToBeExcludedFromInitializePhase (const WaveServiceId &waveServiceId)
{
    if (((WaveFrameworkObjectManager::getWaveServiceId               ()) == waveServiceId) ||
        (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))))
    {
        return (true);
    }
    else
    {         
        return (false);
    }
}

bool PersistentWithDefaultForHABootAgent::isToBeExcludedFromInstall (const WaveServiceId &waveServiceId)
{
    if (((WaveFrameworkObjectManager::getWaveServiceId               ()) == waveServiceId) ||
        (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

}
