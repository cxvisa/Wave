/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Boot/HaStandbyWaveBootAgent.h"
#include "Framework/Core/WaveFrameworkConfiguration.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/LocationManagement/LocationBase.h"
#include "Framework/Utils/StringUtils.h"
#include <vector>
#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"
#include "Framework/ObjectModel/WaveManagedObjectToolKit.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContext.h"

namespace WaveNs
{

HaStandbyWaveBootAgent::HaStandbyWaveBootAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : WaveBootAgent (pWaveObjectManager, currentFrameworkSequenceGenerator),
      m_waveBootPhase (WAVE_BOOT_PHASE_ALL_PHASES)
{
}

HaStandbyWaveBootAgent::~HaStandbyWaveBootAgent ()
{
}

ResourceId HaStandbyWaveBootAgent::execute (const WaveBootPhase &waveBootPhase)
{
    m_waveBootPhase = waveBootPhase;

    if (WAVE_BOOT_PHASE_ALL_PHASES == m_waveBootPhase)
    {
        WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
        {
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::initializeWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::enableWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::listenForEventsWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::bootWaveServicesDuringPrePhaseStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::initializeLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::enableLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::upgradeLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::listenForEventsLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::bootLocalWaveServicesStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::initializeGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::enableGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::upgradeGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::listenForEventsGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::bootGlobalWaveServicesStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::updateDatabaseForeignKeyConstraintsStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::updateUserDefinedKeyCombinationConstraintsAndKeysStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::prismSynchronousLinearSequencerSucceededStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::prismSynchronousLinearSequencerFailedStep)
        };
    
        WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext = new WaveSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

        ResourceId status = pWaveSynchronousLinearSequencerContext->execute ();

        return (status);
    }
    else if (WAVE_BOOT_PHASE_PRE_PHASE == waveBootPhase)
    {
        trace (TRACE_LEVEL_DEBUG, "HaStandbyWaveBootAgent::execute : Pre Phase.");
        WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
        {
//            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::resetLocationRole),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::initializeWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::enableWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::listenForEventsWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::haInstallWaveServicesDuringPrePhaseStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::haBootWaveServicesDuringPrePhaseStep),

         // This should happen only after suceesful schema conversion. Schema conversion on standby is attempted after this step. Hence, commenting. 
         //   reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::updateDatabaseForeignKeyConstraintsStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::prismSynchronousLinearSequencerSucceededStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::prismSynchronousLinearSequencerFailedStep)
        };

        WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext = new WaveSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

        ResourceId status = pWaveSynchronousLinearSequencerContext->execute ();

        return (status);
    }
    else if (WAVE_BOOT_PHASE_POST_PHASE == waveBootPhase)
    {
        trace (TRACE_LEVEL_DEBUG, "HaStandbyWaveBootAgent::execute : Post Phase.");

        WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
        {
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::initializeLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::enableLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::upgradeLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::listenForEventsLocalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::haBootLocalWaveServicesStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::initializeGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::enableGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::upgradeGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::listenForEventsGlobalWaveServicesStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::haBootGlobalWaveServicesStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::updateDatabaseForeignKeyConstraintsStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::updateUserDefinedKeyCombinationConstraintsAndKeysStep),

            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::prismSynchronousLinearSequencerSucceededStep),
            reinterpret_cast<WaveSynchronousLinearSequencerStep> (&HaStandbyWaveBootAgent::prismSynchronousLinearSequencerFailedStep)
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

bool HaStandbyWaveBootAgent::isAPersistentBoot ()
{
    return (false);
}

WaveBootReason HaStandbyWaveBootAgent::getReason () const
{
    return (WAVE_BOOT_HASTANDBY_BOOT);
}

bool HaStandbyWaveBootAgent::isToBeExcludedForEnableAndBoot (const WaveServiceId& waveServiceId)
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

bool HaStandbyWaveBootAgent::isToBeExcludedFromInstallDuringPrePhase (const WaveServiceId &waveServiceId)
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

bool HaStandbyWaveBootAgent::isToBeExcludedFromInstall (const WaveServiceId &waveServiceId)
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

bool HaStandbyWaveBootAgent::isToBeExcludedFromInitializeDuringPrePhase (const WaveServiceId &waveServiceId)
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

bool HaStandbyWaveBootAgent::isToBeExcludedFromInitializePhase (const WaveServiceId &waveServiceId)
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

bool HaStandbyWaveBootAgent::isToBeExcludedFromCurrentBootPhase (const WaveServiceId &waveServiceId)
{
    return (false);
}

ResourceId HaStandbyWaveBootAgent::haInstallWaveServicesDuringPrePhaseStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToInstall;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getInstallSequenceDuringPrePhase (serviceIdsToInstall);
    numberOfServices = serviceIdsToInstall.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
        {
            if (true != (FrameworkToolKit::isALocalService (serviceIdsToInstall[i])))
            {
                continue;
            }
        }

        if (true == (isToBeExcludedFromInstallDuringPrePhase (serviceIdsToInstall[i])))
        {
            continue;
        }

        WaveHaInstallObjectManagerMessage prismHaInstallObjectManagerMessage (serviceIdsToInstall[i], getReason ());

        ResourceId status = sendSynchronously (&prismHaInstallObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("HaStandbyWaveBootAgent::installWaveServicesDuringPrePhaseStep : Could not send a message to Install a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInstall[i]) + ", Status : " + FrameworkToolKit::localize (status));

            return (status);
        }

        status = prismHaInstallObjectManagerMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("HaStandbyWaveBootAgent::installWaveServicesDuringPrePhaseStep : Could not Install a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInstall[i]) + ", Status : " + FrameworkToolKit::localize (status));

            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Installed " + FrameworkToolKit::getServiceNameById (serviceIdsToInstall[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId HaStandbyWaveBootAgent::haInstallWaveServicesStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToInstall;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getInstallSequence (serviceIdsToInstall);
    numberOfServices = serviceIdsToInstall.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
        {
            if (true != (FrameworkToolKit::isALocalService (serviceIdsToInstall[i])))
            {
                continue;
            }
        }

        WaveHaInstallObjectManagerMessage prismHaInstallObjectManagerMessage (serviceIdsToInstall[i], getReason ());

        ResourceId status = sendSynchronously (&prismHaInstallObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::hainstallWaveServicesStep : Could not send a message to Install a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInstall[i]) + ", Status : " + FrameworkToolKit::localize (status));
            return (status);
        }

        status = prismHaInstallObjectManagerMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::installWaveServicesStep : Could not Install a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInstall[i]) + ", Status : " + FrameworkToolKit::localize (status));
            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Installed " + FrameworkToolKit::getServiceNameById (serviceIdsToInstall[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId HaStandbyWaveBootAgent::haBootLocalWaveServicesStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToBoot;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getBootSequence (serviceIdsToBoot);
    numberOfServices = serviceIdsToBoot.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (true == (FrameworkToolKit::isALocalService (serviceIdsToBoot[i])))
        {
            if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToBoot[i])))
            {
                continue;
            }

            WaveHaBootObjectManagerMessage prismHaBootObjectManagerMessage (serviceIdsToBoot[i], getReason ());

            ResourceId status = sendSynchronously (&prismHaBootObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("HaStandbyWaveBootAgent::bootLocalWaveServicesStep : Could not send a message to Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }

            status = prismHaBootObjectManagerMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("HaStandbyWaveBootAgent::bootLocalWaveServicesStep : Could not Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "Booted " + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]));
            }
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}


ResourceId HaStandbyWaveBootAgent::haBootGlobalWaveServicesStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToBoot;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getBootSequence (serviceIdsToBoot);
    numberOfServices = serviceIdsToBoot.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (FrameworkToolKit::isALocalService (serviceIdsToBoot[i])))
        {
            if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToBoot[i])))
            {
                continue;
            }

            WaveHaBootObjectManagerMessage prismHaBootObjectManagerMessage (serviceIdsToBoot[i], getReason ());

            ResourceId status = sendSynchronously (&prismHaBootObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("HaStandyWaveBootAgent::habootGlobalWaveServicesStep : Could not send a message to Boot a service : ") + FrameworkToolKit::getServiceNameById(serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }

            status = prismHaBootObjectManagerMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("HaStandyWaveBootAgent::habootGlobalWaveServicesStep : Could not Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "Booted " + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]));
            }
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId HaStandbyWaveBootAgent::haBootWaveServicesStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToBoot;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getBootSequence (serviceIdsToBoot);
    numberOfServices = serviceIdsToBoot.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
        {
            if (true != (FrameworkToolKit::isALocalService (serviceIdsToBoot[i])))
            {
                continue;
            }
        }

        if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToBoot[i])))
        {
            continue;
        }

        if (true == (isToBeExcludedFromCurrentBootPhase (serviceIdsToBoot[i])))
        {
            continue;
        }

        WaveHaBootObjectManagerMessage prismHaBootObjectManagerMessage (serviceIdsToBoot[i], getReason ());

        ResourceId status = sendSynchronously (&prismHaBootObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("haStandbyWaveBootAgent::bootWaveServicesStep : Could not send a message to Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));
            return (status);
        }

        status = prismHaBootObjectManagerMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("haStandbyWaveBootAgent::bootWaveServicesStep : Could not Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));
            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Booted " + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId HaStandbyWaveBootAgent::haBootWaveServicesDuringPrePhaseStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToBoot;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getBootSequenceDuringPrePhase (serviceIdsToBoot);
    numberOfServices = serviceIdsToBoot.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
        {
            if (true != (FrameworkToolKit::isALocalService (serviceIdsToBoot[i])))
            {
                continue;
            }
        }

        if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToBoot[i])))
        {
            continue;
        }

        WaveHaBootObjectManagerMessage prismHaBootObjectManagerMessage (serviceIdsToBoot[i], getReason ());

        ResourceId status = sendSynchronously (&prismHaBootObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("HaStansbyWaveBootAgent::bootWaveServicesDuringPrePhaseStep : Could not send a message to Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));

            return (status);
        }

        status = prismHaBootObjectManagerMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("HaStansbyWaveBootAgent::bootWaveServicesDuringPrePhaseStep : Could not Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));

            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Booted " + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}
                 
ResourceId HaStandbyWaveBootAgent::resetLocationRole (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    LocationBase *pThisLocation = (WaveFrameworkObjectManager::getInstance ())->getThisLocation ();

    waveAssert (NULL != pThisLocation, __FILE__, __LINE__);

    LocationRole    thisLocationRole = pThisLocation->getLocationRole ();
 
    if ((LOCATION_PRIMARY == thisLocationRole) || (LOCATION_PRIMARY_UNCONFIRMED == thisLocationRole))
    {
        pThisLocation->setLocationRole (LOCATION_PRIMARY_UNCONFIRMED);    

        pThisLocation->setClusterPrimaryLocationId (pThisLocation->getLocationId ());
        pThisLocation->setClusterPrimaryPort       (pThisLocation->getPort ());
    }
    else if ((LOCATION_SECONDARY == thisLocationRole) || (LOCATION_SECONDARY_UNCONFIRMED == thisLocationRole))
    {
        pThisLocation->setLocationRole (LOCATION_SECONDARY_UNCONFIRMED);    

        pThisLocation->setClusterPrimaryLocationId (pThisLocation->getLocationId ());
        pThisLocation->setClusterPrimaryPort       (pThisLocation->getPort ());
    }

    return (WAVE_MESSAGE_SUCCESS);
}

}
