/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Boot/HaStandbyPrismBootAgent.h"
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

HaStandbyPrismBootAgent::HaStandbyPrismBootAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : PrismBootAgent (pWaveObjectManager, currentFrameworkSequenceGenerator),
      m_waveBootPhase (WAVE_BOOT_PHASE_ALL_PHASES)
{
}

HaStandbyPrismBootAgent::~HaStandbyPrismBootAgent ()
{
}

ResourceId HaStandbyPrismBootAgent::execute (const WaveBootPhase &waveBootPhase)
{
    m_waveBootPhase = waveBootPhase;

    if (WAVE_BOOT_PHASE_ALL_PHASES == m_waveBootPhase)
    {
        WaveNs::PrismSynchronousLinearSequencerStep sequencerSteps[] =
        {
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::initializePrismServicesDuringPrePhaseStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::enablePrismServicesDuringPrePhaseStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::listenForEventsPrismServicesDuringPrePhaseStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::bootPrismServicesDuringPrePhaseStep),

            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::initializeLocalPrismServicesStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::enableLocalPrismServicesStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::upgradeLocalPrismServicesStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::listenForEventsLocalPrismServicesStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::bootLocalPrismServicesStep),

            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::initializeGlobalPrismServicesStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::enableGlobalPrismServicesStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::upgradeGlobalPrismServicesStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::listenForEventsGlobalPrismServicesStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::bootGlobalPrismServicesStep),

            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::updateDatabaseForeignKeyConstraintsStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::updateUserDefinedKeyCombinationConstraintsAndKeysStep),

            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::prismSynchronousLinearSequencerSucceededStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::prismSynchronousLinearSequencerFailedStep)
        };
    
        PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext = new PrismSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

        ResourceId status = pPrismSynchronousLinearSequencerContext->execute ();

        return (status);
    }
    else if (WAVE_BOOT_PHASE_PRE_PHASE == waveBootPhase)
    {
        trace (TRACE_LEVEL_DEBUG, "HaStandbyPrismBootAgent::execute : Pre Phase.");
        WaveNs::PrismSynchronousLinearSequencerStep sequencerSteps[] =
        {
//            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::resetLocationRole),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::initializePrismServicesDuringPrePhaseStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::enablePrismServicesDuringPrePhaseStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::listenForEventsPrismServicesDuringPrePhaseStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::haInstallPrismServicesDuringPrePhaseStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::haBootPrismServicesDuringPrePhaseStep),

         // This should happen only after suceesful schema conversion. Schema conversion on standby is attempted after this step. Hence, commenting. 
         //   reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::updateDatabaseForeignKeyConstraintsStep),

            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::prismSynchronousLinearSequencerSucceededStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::prismSynchronousLinearSequencerFailedStep)
        };

        PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext = new PrismSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

        ResourceId status = pPrismSynchronousLinearSequencerContext->execute ();

        return (status);
    }
    else if (WAVE_BOOT_PHASE_POST_PHASE == waveBootPhase)
    {
        trace (TRACE_LEVEL_DEBUG, "HaStandbyPrismBootAgent::execute : Post Phase.");

        WaveNs::PrismSynchronousLinearSequencerStep sequencerSteps[] =
        {
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::initializeLocalPrismServicesStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::enableLocalPrismServicesStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::upgradeLocalPrismServicesStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::listenForEventsLocalPrismServicesStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::haBootLocalPrismServicesStep),

            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::initializeGlobalPrismServicesStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::enableGlobalPrismServicesStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::upgradeGlobalPrismServicesStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::listenForEventsGlobalPrismServicesStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::haBootGlobalPrismServicesStep),

            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::updateDatabaseForeignKeyConstraintsStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::updateUserDefinedKeyCombinationConstraintsAndKeysStep),

            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::prismSynchronousLinearSequencerSucceededStep),
            reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HaStandbyPrismBootAgent::prismSynchronousLinearSequencerFailedStep)
        };

        PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext = new PrismSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

        ResourceId status = pPrismSynchronousLinearSequencerContext->execute ();
        return (status);
    }
    else
    {
        return (WAVE_MESSAGE_ERROR);
    }

}

bool HaStandbyPrismBootAgent::isAPersistentBoot ()
{
    return (false);
}

WaveBootReason HaStandbyPrismBootAgent::getReason () const
{
    return (WAVE_BOOT_HASTANDBY_BOOT);
}

bool HaStandbyPrismBootAgent::isToBeExcludedForEnableAndBoot (const WaveServiceId& waveServiceId)
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

bool HaStandbyPrismBootAgent::isToBeExcludedFromInstallDuringPrePhase (const WaveServiceId &waveServiceId)
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

bool HaStandbyPrismBootAgent::isToBeExcludedFromInstall (const WaveServiceId &waveServiceId)
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

bool HaStandbyPrismBootAgent::isToBeExcludedFromInitializeDuringPrePhase (const WaveServiceId &waveServiceId)
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

bool HaStandbyPrismBootAgent::isToBeExcludedFromInitializePhase (const WaveServiceId &waveServiceId)
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

bool HaStandbyPrismBootAgent::isToBeExcludedFromCurrentBootPhase (const WaveServiceId &waveServiceId)
{
    return (false);
}

ResourceId HaStandbyPrismBootAgent::haInstallPrismServicesDuringPrePhaseStep (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext)
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

        PrismHaInstallObjectManagerMessage prismHaInstallObjectManagerMessage (serviceIdsToInstall[i], getReason ());

        ResourceId status = sendSynchronously (&prismHaInstallObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("HaStandbyPrismBootAgent::installPrismServicesDuringPrePhaseStep : Could not send a message to Install a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInstall[i]) + ", Status : " + FrameworkToolKit::localize (status));

            return (status);
        }

        status = prismHaInstallObjectManagerMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("HaStandbyPrismBootAgent::installPrismServicesDuringPrePhaseStep : Could not Install a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInstall[i]) + ", Status : " + FrameworkToolKit::localize (status));

            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Installed " + FrameworkToolKit::getServiceNameById (serviceIdsToInstall[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId HaStandbyPrismBootAgent::haInstallPrismServicesStep (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext)
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

        PrismHaInstallObjectManagerMessage prismHaInstallObjectManagerMessage (serviceIdsToInstall[i], getReason ());

        ResourceId status = sendSynchronously (&prismHaInstallObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("PrismBootAgent::hainstallPrismServicesStep : Could not send a message to Install a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInstall[i]) + ", Status : " + FrameworkToolKit::localize (status));
            return (status);
        }

        status = prismHaInstallObjectManagerMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("PrismBootAgent::installPrismServicesStep : Could not Install a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInstall[i]) + ", Status : " + FrameworkToolKit::localize (status));
            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Installed " + FrameworkToolKit::getServiceNameById (serviceIdsToInstall[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId HaStandbyPrismBootAgent::haBootLocalPrismServicesStep (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext)
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

            PrismHaBootObjectManagerMessage prismHaBootObjectManagerMessage (serviceIdsToBoot[i], getReason ());

            ResourceId status = sendSynchronously (&prismHaBootObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("HaStandbyPrismBootAgent::bootLocalPrismServicesStep : Could not send a message to Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }

            status = prismHaBootObjectManagerMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("HaStandbyPrismBootAgent::bootLocalPrismServicesStep : Could not Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));
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


ResourceId HaStandbyPrismBootAgent::haBootGlobalPrismServicesStep (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext)
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

            PrismHaBootObjectManagerMessage prismHaBootObjectManagerMessage (serviceIdsToBoot[i], getReason ());

            ResourceId status = sendSynchronously (&prismHaBootObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("HaStandyPrismBootAgent::habootGlobalPrismServicesStep : Could not send a message to Boot a service : ") + FrameworkToolKit::getServiceNameById(serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }

            status = prismHaBootObjectManagerMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("HaStandyPrismBootAgent::habootGlobalPrismServicesStep : Could not Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));
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

ResourceId HaStandbyPrismBootAgent::haBootPrismServicesStep (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext)
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

        PrismHaBootObjectManagerMessage prismHaBootObjectManagerMessage (serviceIdsToBoot[i], getReason ());

        ResourceId status = sendSynchronously (&prismHaBootObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("haStandbyPrismBootAgent::bootPrismServicesStep : Could not send a message to Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));
            return (status);
        }

        status = prismHaBootObjectManagerMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("haStandbyPrismBootAgent::bootPrismServicesStep : Could not Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));
            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Booted " + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId HaStandbyPrismBootAgent::haBootPrismServicesDuringPrePhaseStep (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext)
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

        PrismHaBootObjectManagerMessage prismHaBootObjectManagerMessage (serviceIdsToBoot[i], getReason ());

        ResourceId status = sendSynchronously (&prismHaBootObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("HaStansbyPrismBootAgent::bootPrismServicesDuringPrePhaseStep : Could not send a message to Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));

            return (status);
        }

        status = prismHaBootObjectManagerMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("HaStansbyPrismBootAgent::bootPrismServicesDuringPrePhaseStep : Could not Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));

            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Booted " + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}
                 
ResourceId HaStandbyPrismBootAgent::resetLocationRole (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext)
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
