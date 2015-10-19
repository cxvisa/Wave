/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Failover/WaveFailoverAgent.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/WaveFrameworkMessages.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"
#include "Cluster/CentralClusterConfigObjectManager.h"
#include "Framework/Failover/WaveFailoverAgentContext.h"
#include "Framework/Failover/WaveFailoverAgentSequencerContext.h"
#include "Framework/Database/DatabaseObjectManagerBackupMessage.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Persistence/PersistenceObjectManager.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Core/PrimaryChangedEvent.h"
#include "Framework/ObjectModel/WaveManagedObjectToolKit.h"
#include "Cluster/Local/WaveNode.h"
#include "Framework/Core/WaveNodeBackendSyncUpAgent.h"

#include <string>
#include <set>
#include <fstream>
#include <algorithm>

using namespace std;

namespace WaveNs
{
static const UI32       s_primaryChangedPhase0TimeoutInMilliseconds = 900000; // 15 * 60 * 1000
static const UI32       s_primaryChangedPhase1TimeoutInMilliseconds = 900000; // 15 * 60 * 1000

WaveFailoverAgent::WaveFailoverAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : WaveWorker (pWaveObjectManager),
      m_currentFrameworkSequenceGenerator (currentFrameworkSequenceGenerator)
{
}

WaveFailoverAgent::~WaveFailoverAgent ()
{
}

void WaveFailoverAgent::execute (WaveFailoverAgentContext *pWaveFailoverAgentContext)
{
    WaveNs::WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFailoverAgent::failoverWaveServicesStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFailoverAgent::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFailoverAgent::prismLinearSequencerFailedStep)
    };

    WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext = new WaveFailoverAgentSequencerContext (pWaveFailoverAgentContext, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pWaveFailoverAgentSequencerContext->setFailedLocationIds (pWaveFailoverAgentContext->getFailedLocationIds());
    pWaveFailoverAgentSequencerContext->setServiceToBeIgnored (pWaveFailoverAgentContext->getServiceToBeIgnored());
    pWaveFailoverAgentSequencerContext->setIsConfigurationChange (pWaveFailoverAgentContext->getIsConfigurationChange ());

    pWaveFailoverAgentSequencerContext->holdAll ();
    pWaveFailoverAgentSequencerContext->start ();
}

void WaveFailoverAgent::failoverWaveServicesStep (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFailoverAgent::failoverWaveServicesStep");
    vector<WaveServiceId> serviceIdsToFailover;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;
    vector<LocationId>     failedLocationIds       = pWaveFailoverAgentSequencerContext->getFailedLocationIds ();
    //WaveServiceId         serviceToBeIgnored      = pWaveFailoverAgentContext->getServiceToBeIgnored ();
    UI32                   index                   = 0;
    bool                   isConfigurationChange   = pWaveFailoverAgentSequencerContext->getIsConfigurationChange ();
    bool                   isPrincipalChangedWithThisFailover = pWaveFailoverAgentSequencerContext->getIsPrincipalChangedWithThisFailover ();

    m_currentFrameworkSequenceGenerator.getFailoverSequence (serviceIdsToFailover);
    numberOfServices = serviceIdsToFailover.size ();

    trace (TRACE_LEVEL_DEBUG, string ("WaveFailoverAgent::failoverWaveServicesStep : Number of services : ") + numberOfServices);

    for (i = 0; i < numberOfServices; i++)
    {
        index = numberOfServices - 1 - i;

        //if ((false == (isToBeExcludedForFailover (serviceIdsToFailover[index]))) && (serviceToBeIgnored != serviceIdsToFailover[index]))
        if (false == (isToBeExcludedForFailover (serviceIdsToFailover[index])))
        {
            WaveFailoverObjectManagerMessage prismFailoverObjectManagerMessage (serviceIdsToFailover[index], getFailoverReason (), isPrincipalChangedWithThisFailover);

            (prismFailoverObjectManagerMessage.getFailedLocationIds ()) = failedLocationIds;

            prismFailoverObjectManagerMessage.setIsConfigurationChange (isConfigurationChange);
            
            ResourceId status = sendSynchronously (&prismFailoverObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, "WaveBootAgent::failoverWaveServicesStep : Could not Failover a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToFailover[index]));
                trace (TRACE_LEVEL_FATAL, "WaveBootAgent::failoverWaveServicesStep : Status                       : " + FrameworkToolKit::localize (status));
                waveAssert (false, __FILE__, __LINE__);
                pWaveFailoverAgentSequencerContext->executeNextStep(status);
                return;
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "Failed-Over " + FrameworkToolKit::getServiceNameById (serviceIdsToFailover[index]));
            }
        }
        else
        {
            trace (TRACE_LEVEL_DEBUG, "Skipped " + FrameworkToolKit::getServiceNameById (serviceIdsToFailover[index]));
        }
    }

    pWaveFailoverAgentSequencerContext->executeNextStep(WAVE_MESSAGE_SUCCESS);
}

void WaveFailoverAgent::initializeWaveGlobalServicesDuringPrePhaseStep (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFailoverAgent::initializeWaveGlobalServicesDuringPrePhaseStep Entering");

    vector<WaveServiceId> serviceIdsToInitialize;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getInitializeSequenceDuringPrePhase (serviceIdsToInitialize);
    numberOfServices = serviceIdsToInitialize.size ();


    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (isToBeExcludedDuringPrePhase (serviceIdsToInitialize [i])))
        {
            WaveInitializeObjectManagerMessage prismInitializeObjectManagerMessage (serviceIdsToInitialize[i], getBootReason ());

            ResourceId status = sendSynchronously (&prismInitializeObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveFailoverAgent::initializeWaveGlobalServicesDuringPrePhaseStep : Could not send a message to Initialize a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInitialize[i]) + ", Status : " + FrameworkToolKit::localize (status));
                waveAssert (false, __FILE__, __LINE__);
                pWaveFailoverAgentSequencerContext->executeNextStep(status);
            }

            status = prismInitializeObjectManagerMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveFailoverAgent::initializeWaveGlobalServicesDuringPrePhaseStep : Could not Initialize a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInitialize[i]) + ", Status : " + FrameworkToolKit::localize (status));
                waveAssert (false, __FILE__, __LINE__);
                pWaveFailoverAgentSequencerContext->executeNextStep(status);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "Initialized " + FrameworkToolKit::getServiceNameById (serviceIdsToInitialize[i]));
            }
        }
    }    

    pWaveFailoverAgentSequencerContext->executeNextStep(WAVE_MESSAGE_SUCCESS);
}

void WaveFailoverAgent::enableWaveGlobalServicesDuringPrePhaseStep (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFailoverAgent::enableWaveGlobalServicesDuringPrePhaseStep");

    vector<WaveServiceId> serviceIdsToEnableDuringPrePhase;
    UI32                   i                                 = 0;
    UI32                   numberOfServices                  = 0;

    m_currentFrameworkSequenceGenerator.getEnableSequenceDuringPrePhase (serviceIdsToEnableDuringPrePhase);
    numberOfServices = serviceIdsToEnableDuringPrePhase.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (isToBeExcludedDuringPrePhase (serviceIdsToEnableDuringPrePhase[i])))
        {
            WaveEnableObjectManagerMessage prismEnableObjectManagerMessage (serviceIdsToEnableDuringPrePhase[i], getBootReason ());

            ResourceId status = sendSynchronously (&prismEnableObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, "WaveBootAgent::enableWaveGlobalServicesStep : Could not Enable a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToEnableDuringPrePhase[i]));
                trace (TRACE_LEVEL_FATAL, "WaveBootAgent::enableWaveGlobalServicesStep : Status                     : " + FrameworkToolKit::localize (status));
                waveAssert (false, __FILE__, __LINE__);
                pWaveFailoverAgentSequencerContext->executeNextStep(status);
                return;
            }
            else
            {
                status = prismEnableObjectManagerMessage.getCompletionStatus ();

                if (WAVE_MESSAGE_SUCCESS != status)
                {
                    trace (TRACE_LEVEL_FATAL, "WaveBootAgent::enableWaveGlobalServicesStep : Could not Enable a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToEnableDuringPrePhase[i]));
                    trace (TRACE_LEVEL_FATAL, "WaveBootAgent::enableWaveGlobalServicesStep : Status                     : " + FrameworkToolKit::localize (status));
                    waveAssert (false, __FILE__, __LINE__);
                    pWaveFailoverAgentSequencerContext->executeNextStep(status);
                    return;
                }

                trace (TRACE_LEVEL_INFO, "Enabled " + FrameworkToolKit::getServiceNameById (serviceIdsToEnableDuringPrePhase[i]));
            }
        }
        else
        {
            trace (TRACE_LEVEL_DEVEL, "Skipped " + FrameworkToolKit::getServiceNameById (serviceIdsToEnableDuringPrePhase[i]));
        }
    }

    pWaveFailoverAgentSequencerContext->executeNextStep(WAVE_MESSAGE_SUCCESS);
}

void WaveFailoverAgent::listenForEventsWaveGlobalServicesDuringPrePhaseStep (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFailoverAgent::listenForEventsWaveGlobalServicesDuringPrePhaseStep Entering");

    vector<WaveServiceId> serviceIdsToEnableDuringPrePhase;
    UI32                   i                                 = 0;
    UI32                   numberOfServices                  = 0;

    m_currentFrameworkSequenceGenerator.getEnableSequenceDuringPrePhase (serviceIdsToEnableDuringPrePhase);
    numberOfServices = serviceIdsToEnableDuringPrePhase.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (isToBeExcludedDuringPrePhase (serviceIdsToEnableDuringPrePhase[i])))
        {
            WaveListenForEventsObjectManagerMessage prismListenForEventsObjectManagerMessage (serviceIdsToEnableDuringPrePhase[i]);

            ResourceId status = sendSynchronously (&prismListenForEventsObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, "WaveFailoverAgent::listenForEventsWaveGlobalServicesDuringPrePhaseStep : Could not send Listen for Event message a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToEnableDuringPrePhase[i]));
                trace (TRACE_LEVEL_FATAL, "WaveFailoverAgent::listenForEventsWaveGlobalServicesDuringPrePhaseStep : Status                     : " + FrameworkToolKit::localize (status));

                waveAssert (false, __FILE__, __LINE__);

                pWaveFailoverAgentSequencerContext->executeNextStep(status);
                return;
            }
            else
            {
                status  = prismListenForEventsObjectManagerMessage.getCompletionStatus ();

                if (WAVE_MESSAGE_SUCCESS != status)
                {
                    trace (TRACE_LEVEL_FATAL, "WaveBootAgent::listenForEventsWaveGlobalServicesDuringPrePhaseStep : Could not send Listen for Event message a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToEnableDuringPrePhase[i]));
                    trace (TRACE_LEVEL_FATAL, "WaveBootAgent::listenForEventsWaveGlobalServicesDuringPrePhaseStep : Status                     : " + FrameworkToolKit::localize (status));

                    waveAssert (false, __FILE__, __LINE__);

                    pWaveFailoverAgentSequencerContext->executeNextStep(status);
                    return;
                }
                
                trace (TRACE_LEVEL_INFO, "Listen For Event Done " + FrameworkToolKit::getServiceNameById (serviceIdsToEnableDuringPrePhase[i]));
            }
        }
        else
        {
            trace (TRACE_LEVEL_DEVEL, "Skipped " + FrameworkToolKit::getServiceNameById (serviceIdsToEnableDuringPrePhase[i]));
        }
    }

    pWaveFailoverAgentSequencerContext->executeNextStep(WAVE_MESSAGE_SUCCESS);
}

void WaveFailoverAgent::bootWaveGlobalServicesDuringPrePhaseStep (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext)
{
    vector<WaveServiceId> serviceIdsToBoot;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getBootSequenceDuringPrePhase (serviceIdsToBoot);
    numberOfServices = serviceIdsToBoot.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == isToBeExcludedDuringPrePhase (serviceIdsToBoot[i]))
        {
            WaveBootObjectManagerMessage prismBootObjectManagerMessage (serviceIdsToBoot[i], getBootReason ());

            ResourceId status = sendSynchronously (&prismBootObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveFailoverAgent::bootWaveGlobalServicesDuringPrePhaseStep : Could not send a message to Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));
                waveAssert (false, __FILE__, __LINE__);
                pWaveFailoverAgentSequencerContext->executeNextStep(WAVE_MESSAGE_ERROR);
            }

            status = prismBootObjectManagerMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveFailoverAgent::bootWaveGlobalServicesDuringPrePhaseStep : Could not Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));
                waveAssert (false, __FILE__, __LINE__);
                pWaveFailoverAgentSequencerContext->executeNextStep(WAVE_MESSAGE_ERROR);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "Booted " + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]));
            }
        }
    }

    pWaveFailoverAgentSequencerContext->executeNextStep(WAVE_MESSAGE_SUCCESS);      
}

void WaveFailoverAgent::initializeWaveGlobalServicesStep (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext)
{
    vector<WaveServiceId> serviceIdsToInitialize;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getInitializeSequence (serviceIdsToInitialize);
    numberOfServices = serviceIdsToInitialize.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == isToBeExcluded (serviceIdsToInitialize[i]))
        {
            WaveInitializeObjectManagerMessage prismInitializeObjectManagerMessage (serviceIdsToInitialize[i], getBootReason ());

            ResourceId status = sendSynchronously (&prismInitializeObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("mFailoverAgent::initializeWaveGlobalServicesStep : Could not send a message to Initialize a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInitialize[i]) + ",  Status : " + FrameworkToolKit::localize (status));
                waveAssert (false, __FILE__, __LINE__);
                pWaveFailoverAgentSequencerContext->executeNextStep(status);
            }

            status = prismInitializeObjectManagerMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveFailoverAgent::initializeWaveGlobalServicesStep : Could not Initialize a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInitialize[i]) + ", Status : " + FrameworkToolKit::localize (status));
                waveAssert (false, __FILE__, __LINE__);
                pWaveFailoverAgentSequencerContext->executeNextStep(status);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "Initialized " + FrameworkToolKit::getServiceNameById (serviceIdsToInitialize[i]));
            }
        }
    }

    pWaveFailoverAgentSequencerContext->executeNextStep(WAVE_MESSAGE_SUCCESS);
}

void WaveFailoverAgent::enableWaveGlobalServicesStep (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFailoverAgent::enableWaveGlobalServicesStep");
    vector<WaveServiceId> serviceIdsToEnable;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getBootSequence (serviceIdsToEnable);
    numberOfServices = serviceIdsToEnable.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (isToBeExcluded (serviceIdsToEnable[i])))
        {
            WaveEnableObjectManagerMessage prismEnableObjectManagerMessage (serviceIdsToEnable[i], getBootReason ());

            ResourceId status = sendSynchronously (&prismEnableObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, "WaveBootAgent::enableWaveGlobalServicesStep : Could not Enable a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]));
                trace (TRACE_LEVEL_FATAL, "WaveBootAgent::enableWaveGlobalServicesStep : Status                     : " + FrameworkToolKit::localize (status));
                waveAssert (false, __FILE__, __LINE__);
                pWaveFailoverAgentSequencerContext->executeNextStep(status);
                return;
            }
            else
            {
                status = prismEnableObjectManagerMessage.getCompletionStatus ();

                if (WAVE_MESSAGE_SUCCESS != status)
                {
                    trace (TRACE_LEVEL_FATAL, string ("WaveFailoverAgent::enableWaveGlobalServicesStep : Could not Enable a service ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));

                    waveAssert (false, __FILE__, __LINE__);

                    pWaveFailoverAgentSequencerContext->executeNextStep(status);
                    return;
                }

                trace (TRACE_LEVEL_INFO, "Enabled " + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]));
            }
        }
        else
        {
            trace (TRACE_LEVEL_DEVEL, "Skipped " + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]));
        }
    }

    pWaveFailoverAgentSequencerContext->executeNextStep(WAVE_MESSAGE_SUCCESS);
}

void WaveFailoverAgent::listenForEventsWaveGlobalServicesStep (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFailoverAgent::listenForEventsWaveGlobalServicesStep");

    vector<WaveServiceId> serviceIdsToEnable;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getBootSequence (serviceIdsToEnable);
    numberOfServices = serviceIdsToEnable.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (isToBeExcluded (serviceIdsToEnable[i])))
        {
            WaveListenForEventsObjectManagerMessage prismListenForEventsObjectManagerMessage (serviceIdsToEnable[i]);

            ResourceId status = sendSynchronously (&prismListenForEventsObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, "WaveFailoverAgent::listenForEventsWaveGlobalServicesStep : Could not send a Message for Listen For Event to a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]));
                trace (TRACE_LEVEL_FATAL, "WaveFailoverAgent::listenForEventsWaveGlobalServicesStep : Status                     : " + FrameworkToolKit::localize (status));
                waveAssert (false, __FILE__, __LINE__);
                pWaveFailoverAgentSequencerContext->executeNextStep(status);
                return;
            }
            else
            {
                status = prismListenForEventsObjectManagerMessage.getCompletionStatus ();

                if (WAVE_MESSAGE_SUCCESS != status)
                {
                    trace (TRACE_LEVEL_FATAL, string ("WaveFailoverAgent::listenForEventsWaveGlobalServicesStep : Listen for Event failed to Completion for service :") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));

                    waveAssert (false, __FILE__, __LINE__);

                    pWaveFailoverAgentSequencerContext->executeNextStep(status);
                    return;
                }

                trace (TRACE_LEVEL_INFO, "Listen For Service " + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]));
            }
        }
        else
        {
            trace (TRACE_LEVEL_DEVEL, "Skipped " + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]));
        }
    }

    pWaveFailoverAgentSequencerContext->executeNextStep(WAVE_MESSAGE_SUCCESS);
}

void WaveFailoverAgent::bootWaveGlobalServicesStep (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext)
{
    vector<WaveServiceId> serviceIdsToBoot;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getBootSequence (serviceIdsToBoot);
    numberOfServices = serviceIdsToBoot.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (isToBeExcluded (serviceIdsToBoot[i])))
        {
            WaveBootObjectManagerMessage prismBootObjectManagerMessage (serviceIdsToBoot[i], getBootReason ());

            ResourceId status = sendSynchronously (&prismBootObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveFailoverAgent::bootWaveGlobalServicesStep : Could not send a message to Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));
                waveAssert (false, __FILE__, __LINE__);
                pWaveFailoverAgentSequencerContext->executeNextStep(status);
            }

            status = prismBootObjectManagerMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveFailoverAgent::bootWaveGlobalServicesStep : Could not Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));
                waveAssert (false, __FILE__, __LINE__);
                pWaveFailoverAgentSequencerContext->executeNextStep(status);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "Booted " + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]));
            }
        }
    }

    pWaveFailoverAgentSequencerContext->executeNextStep(WAVE_MESSAGE_SUCCESS);
}


void WaveFailoverAgent::removeOldPrimaryLocationStep (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext)
{
         trace (TRACE_LEVEL_DEVEL, "WaveFailoverAgent::removeOldPrimaryLocationStep");
         //If it is a controlled failover set the flag is the message
         if(FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_CONTROLLED == getFailoverReason ()) 
         {
             WaveFrameworkObjectManager *pWaveFrameworkObjectManager = WaveFrameworkObjectManager::getInstance ();
             waveAssert (NULL != pWaveFrameworkObjectManager, __FILE__, __LINE__);

             LocationId oldPrimaryLocationId = pWaveFailoverAgentSequencerContext->getOlderPrimaryLocationId ();
             pWaveFrameworkObjectManager->removeKnownLocation (oldPrimaryLocationId);
             tracePrintf (TRACE_LEVEL_INFO, "WaveFaioverAgent::removeOldPrimaryLocationStep::Removing the old primary location id %u due to controlled failover", oldPrimaryLocationId);
            
         }
         pWaveFailoverAgentSequencerContext->executeNextStep(WAVE_MESSAGE_SUCCESS);
}

void WaveFailoverAgent::resetThisLocationToPrimaryStep (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFailoverAgent::resetThisLocationToPrimaryStep");
    WaveFrameworkObjectManager *pWaveFrameworkObjectManager = WaveFrameworkObjectManager::getInstance ();

    waveAssert (NULL != pWaveFrameworkObjectManager, __FILE__, __LINE__);

    

    pWaveFrameworkObjectManager->resetLocationToPrimary ();

    pWaveFailoverAgentSequencerContext->executeNextStep(WAVE_MESSAGE_SUCCESS);
}

bool WaveFailoverAgent::isToBeExcludedForFailover (const WaveServiceId &waveServiceId)
{
    if (((WaveFrameworkObjectManager::getWaveServiceId ()) == waveServiceId) ||
        (true == (FrameworkToolKit::isALocalService (waveServiceId))) ||
        (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

void WaveFailoverAgent::createDatabaseDump ()
{
    string backupFileName = string (FrameworkToolKit::getProcessInitialWorkingDirectory () + "/" + FrameworkToolKit::getDatabaseBackupFileName ()); 

    DatabaseObjectManagerBackupMessage message (backupFileName);

    message.setDataOnlyBackup (true);

    ResourceId                         status  = sendSynchronously (&message);

    if (WAVE_MESSAGE_SUCCESS != status)
    {    
        trace (TRACE_LEVEL_FATAL, "WaveFailoverAgent::createDatabaseDump : Could not send message to backup database.  Status : " + FrameworkToolKit::localize (status));
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        status = message.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFailoverAgent::createDatabaseDump : Message to backup database failed.  Completion Status : " + FrameworkToolKit::localize (status));
            waveAssert (false, __FILE__, __LINE__);
        }    
        else 
        {    
             trace (TRACE_LEVEL_INFO, "WaveFailoverAgent::createDatabaseDump : Successfully backed up the database.");
        }    
    }
}

void WaveFailoverAgent::pausePersistenceForPrimaryChangeStep (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext)
{
    pausePersistence ();

    pWaveFailoverAgentSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFailoverAgent::informSecondaryLocationsToChangePrimaryStep (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFailoverAgent::informSecondaryLocationsToChangePrimaryStep");
    vector<LocationId>  connectedLocationIds;
    UI32                numberOfConnectedLocations = 0;
    UI32                i                          = 0;
    LocationId          thisLocationId             = FrameworkToolKit::getThisLocationId ();
    string              thisLocationIpAddress      = FrameworkToolKit::getThisLocationIpAddress ();
    UI32                thisLocationPort           = FrameworkToolKit::getThisLocationPort ();
    LocationId          locationId                 = FrameworkToolKit::getThisLocationId ();
    string              ipAddress                  = FrameworkToolKit::getThisLocationIpAddress ();
    UI32                port                       = FrameworkToolKit::getThisLocationPort ();

    vector<LocationId>  failedLocationIds          = pWaveFailoverAgentSequencerContext->getFailedLocationIds ();
    UI32                j                          = 0;
    UI32                found                      = 0;

    FrameworkToolKit::getConnectedLocations (connectedLocationIds);
    numberOfConnectedLocations = connectedLocationIds.size ();

    pWaveFailoverAgentSequencerContext->setConnectedLocationVector (connectedLocationIds);

    ++(*pWaveFailoverAgentSequencerContext);
    
    for (i = 0; i < numberOfConnectedLocations; i++)
    {
        found = 0;
        locationId = connectedLocationIds[i];
        ipAddress  = FrameworkToolKit::getIpAddressForLocationId (locationId);
        port       = FrameworkToolKit::getPortForLocationId      (locationId);

        trace (TRACE_LEVEL_INFO, string("WaveFailoverAgent::informSecondaryLocationsToChangePrimaryStep : Processing Location: ") + ipAddress + string (":") + port + string (":") + locationId + string(" Failed Loc: ") + failedLocationIds[0] + string ("."));

        for (j = 0; j < failedLocationIds.size(); j++) 
        {
            if(failedLocationIds[j] == locationId) 
            {
                trace (TRACE_LEVEL_INFO, string("WaveFailoverAgent::informSecondaryLocationsToChangePrimaryStep : Do not Inform Location ") + ipAddress + string (":") + port + string (":") + locationId + string(" Failed Loc: ") + failedLocationIds[j] + string ("."));
                found = 1;
                break;
            }
        }

        if(found) 
        {
            continue;
        }

        FrameworkObjectManagerPrimaryChangedMessage *pMessage = new FrameworkObjectManagerPrimaryChangedMessage(thisLocationId, thisLocationIpAddress, thisLocationPort);

        pMessage->setAnyConfigurationChangeTrackingNumber (pWaveFailoverAgentSequencerContext->getAnyConfigurationChangeTrackingNumber ());
        pMessage->setSchemaChangeVectors ();

         //If it is a controlled failover set the flag is the message
        if(FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_CONTROLLED == getFailoverReason ()) 
        {
            pMessage->setPrimaryChangeDueToControlledFailover ();
        }

        WaveMessageStatus status = send (pMessage, reinterpret_cast<WaveMessageResponseHandler> (&WaveFailoverAgent::informSecondaryLocationsToChangePrimaryCallback), pWaveFailoverAgentSequencerContext, s_primaryChangedPhase0TimeoutInMilliseconds, locationId);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, string ("WaveFailoverAgent::informSecondaryLocationsToChangePrimaryStep: Not able to inform secondary location : ") + locationId + string (" Error Code : ") + status);
            pWaveFailoverAgentSequencerContext->setSecondaryNodeStatus (ipAddress, port, status);
            (WaveFrameworkObjectManager::getInstance ())->disconnectFromLocation (locationId);
        }
        else
        {
             ++(*pWaveFailoverAgentSequencerContext);
        }

    }

    createDatabaseDump ();

    --(*pWaveFailoverAgentSequencerContext);

    if (0 == (pWaveFailoverAgentSequencerContext->getNumberOfCallbacksBeforeAdvancingToNextStep ()))
    {
        /* We need to advance to next steps here as all sends may be failed or completed within the same stack */
        pWaveFailoverAgentSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
}

void WaveFailoverAgent::informSecondaryLocationsToChangePrimaryCallback (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, void *pContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFailoverAgent::informSecondaryLocationsToChangePrimaryCallback");
    WaveFailoverAgentSequencerContext  *pWaveFailoverAgentSequencerContext = reinterpret_cast<WaveFailoverAgentSequencerContext *> (pContext);
    LocationId                           locationId;
    string                               ipAddress;
    SI32                                 port;

    --(*pWaveFailoverAgentSequencerContext);

    if (FRAMEWORK_SUCCESS == frameworkStatus)
    {
        waveAssert (NULL != pWaveMessage, __FILE__, __LINE__);

        ResourceId completionStatus = pWaveMessage->getCompletionStatus ();
        locationId                  = pWaveMessage->getReceiverLocationId ();
        ipAddress                   = FrameworkToolKit::getIpAddressForLocationId (locationId);
        port                        = FrameworkToolKit::getPortForLocationId (locationId);

        pWaveFailoverAgentSequencerContext->setSecondaryNodeStatus (ipAddress, port, completionStatus);

        if (WAVE_MESSAGE_SUCCESS != completionStatus)
        {
            trace (TRACE_LEVEL_ERROR, string ("WaveFailoverAgent::informSecondaryLocationsToChangePrimaryCallback : Case 1 - Informing ") + ipAddress + " failed : " + completionStatus);
            (WaveFrameworkObjectManager::getInstance ())->disconnectFromLocation (locationId);
        }
    }
    else
    {
        if (NULL != pWaveMessage)
        {
            locationId = pWaveMessage->getReceiverLocationId ();
            ipAddress  = FrameworkToolKit::getIpAddressForLocationId (locationId);
            port       = FrameworkToolKit::getPortForLocationId (locationId);

            pWaveFailoverAgentSequencerContext->setSecondaryNodeStatus (ipAddress, port, frameworkStatus);
            (WaveFrameworkObjectManager::getInstance ())->disconnectFromLocation (locationId);

            trace (TRACE_LEVEL_ERROR, string ("WaveFailoverAgent::informSecondaryLocationsToChangePrimaryCallback : Case 2 - Informing ") + ipAddress + " failed : " + frameworkStatus);
        }
    }

    if (NULL != pWaveMessage)
    {
        delete pWaveMessage;
    }

    if (0 == (pWaveFailoverAgentSequencerContext->getNumberOfCallbacksBeforeAdvancingToNextStep ()))
    {
        LocationId          locationId1 = 0;
        string              ipAddress1  = "";
        SI32                port1       = 0;
        vector<LocationId>  connectedLocationIds;
        UI32                numberOfConnectedLocations = 0;

        pWaveFailoverAgentSequencerContext->getConnectedLocationVector(connectedLocationIds);
        numberOfConnectedLocations = connectedLocationIds.size ();
    
        for (UI32 i = 0; i < numberOfConnectedLocations; i++)
        {
            locationId1 = connectedLocationIds[i];
            ipAddress1  = FrameworkToolKit::getIpAddressForLocationId (locationId1);
            port1       = FrameworkToolKit::getPortForLocationId      (locationId1);

            if (true != (pWaveFailoverAgentSequencerContext->isSecondaryNodeStatusSet (ipAddress1, port1)))
            {
                pWaveFailoverAgentSequencerContext->setSecondaryNodeStatus (ipAddress1, port1, FRAMEWORK_ERROR_FAILOVER_INFORM_SECONDARY_LOCATIONS_TIMED_OUT);
                (WaveFrameworkObjectManager::getInstance ())->disconnectFromLocation (locationId1);

                trace (TRACE_LEVEL_ERROR, string ("WaveFailoverAgent::informSecondaryLocationsToChangePrimaryCallback : Case 3 - Informing ") + ipAddress1 + " Timeout ");
            }
        }

        pWaveFailoverAgentSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
}

void WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase1Step (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase1Step: ");
    vector<LocationId>  connectedLocationIds;
    UI32                numberOfConnectedLocations = 0;

    vector<LocationId>  failedLocationIds          = pWaveFailoverAgentSequencerContext->getFailedLocationIds ();
    UI32                found                      = 0;

    ifstream            databaseBackupFile;
    SI32                sizeOfBackupFile           = 0;
    char               *pDatabaseBackupBuffer      = NULL;
    string backupFileName = string (FrameworkToolKit::getProcessInitialWorkingDirectory () + "/" + FrameworkToolKit::getDatabaseBackupFileName ());

    // Collect the Database backup buffer to be sent over to all of the known and connected secondaries.

    databaseBackupFile.open (backupFileName.c_str (), ios::binary);
    databaseBackupFile.seekg (0, ios::end);
    sizeOfBackupFile = databaseBackupFile.tellg ();

    waveAssert (0 != sizeOfBackupFile, __FILE__, __LINE__);

    if (0 < sizeOfBackupFile)
    {
        pDatabaseBackupBuffer = new char[sizeOfBackupFile];

        waveAssert (NULL != pDatabaseBackupBuffer, __FILE__, __LINE__);

        databaseBackupFile.seekg (0, ios::beg);
        databaseBackupFile.read (pDatabaseBackupBuffer, sizeOfBackupFile);
    }

    databaseBackupFile.close ();

    pWaveFailoverAgentSequencerContext->getConnectedLocationVector(connectedLocationIds);
    numberOfConnectedLocations = connectedLocationIds.size ();

    ++(*pWaveFailoverAgentSequencerContext);

    for (UI32 i = 0; i < numberOfConnectedLocations; i++)
    {
        found = 0;
        LocationId  locationId = connectedLocationIds[i];
        string      ipAddress  = FrameworkToolKit::getIpAddressForLocationId (locationId);
        UI32        port       = FrameworkToolKit::getPortForLocationId      (locationId);

        trace (TRACE_LEVEL_INFO, string("WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase1Step : Processing Location: ") + ipAddress + string (":") + port + string (":") + locationId + string(" Failed Loc: ") + failedLocationIds[0] + string ("."));


        // We will send primary changed phase1 message only to the locations that are known to us at this point.
        // Only to those locations that are succeeded as part of last phase.

        if (WAVE_MESSAGE_SUCCESS != (pWaveFailoverAgentSequencerContext->getSecondaryNodeStatus (ipAddress, port)))
        {
            trace (TRACE_LEVEL_DEVEL, string("WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase1Step : Skipping failed secondary Location : ") + ipAddress + string (":") + port + string (":") + locationId + string ("."));
            continue;
        }

        for (UI32 j = 0; j < failedLocationIds.size(); j++) 
        {
            if(failedLocationIds[j] == locationId) 
            {
                trace (TRACE_LEVEL_INFO, string("WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase1Step : Do not Inform Location ") + ipAddress + string (":") + port + string (":") + locationId + string(" Failed Loc: ") + failedLocationIds[j] + string ("."));
                found = 1;
                break;
            }
        }

        if(found) 
        {
            continue;
        }

        FrameworkObjectManagerPrimaryChangedPhase1Message *pMessage = new FrameworkObjectManagerPrimaryChangedPhase1Message();

        pMessage->setAnyConfigurationChangeTrackingNumber (pWaveFailoverAgentSequencerContext->getAnyConfigurationChangeTrackingNumber ());

        if (NULL != pDatabaseBackupBuffer)
        {
            pMessage->addBuffer (pMessage->getDatabaseBackupBufferTag (), sizeOfBackupFile, pDatabaseBackupBuffer, false);
        }
        else
        {
            trace (TRACE_LEVEL_ERROR, "WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase1Step : No Database Backup is being sent to the lcoation.");
        }

        ResourceId status = send (pMessage, reinterpret_cast<WaveMessageResponseHandler> (&WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase1Callback), pWaveFailoverAgentSequencerContext, s_primaryChangedPhase1TimeoutInMilliseconds, locationId);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, string ("WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase1Step: Not able to inform secondary location : ") + locationId + string (" Error Code : ") + status);
            pWaveFailoverAgentSequencerContext->updateSecondaryNodeStatus (ipAddress, port, status);
            (WaveFrameworkObjectManager::getInstance ())->disconnectFromLocation (locationId);
        }
        else
        {
             pWaveFailoverAgentSequencerContext->updateSecondaryNodeStatus (ipAddress, port, FRAMEWORK_ERROR_FAILOVER_INFORM_SECONDARY_LOCATIONS_PHASE1_UNKNOWN);
             ++(*pWaveFailoverAgentSequencerContext);
        }

    }

    --(*pWaveFailoverAgentSequencerContext);

    if (NULL != pDatabaseBackupBuffer)
    {
        delete [] pDatabaseBackupBuffer;
    }

    if (0 == (pWaveFailoverAgentSequencerContext->getNumberOfCallbacksBeforeAdvancingToNextStep ()))
    {
        /* We need to advance to next steps here as all sends may be failed or completed within the same stack */
        pWaveFailoverAgentSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
}

void WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase1Callback (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, void *pContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase1Callback");

    WaveFailoverAgentSequencerContext  *pWaveFailoverAgentSequencerContext = reinterpret_cast<WaveFailoverAgentSequencerContext *> (pContext);
    LocationId                           locationId;
    string                               ipAddress;
    SI32                                 port;

    --(*pWaveFailoverAgentSequencerContext);

    if (FRAMEWORK_SUCCESS == frameworkStatus)
    {
        waveAssert (NULL != pWaveMessage, __FILE__, __LINE__);

        ResourceId completionStatus = pWaveMessage->getCompletionStatus ();
        locationId                  = pWaveMessage->getReceiverLocationId ();
        ipAddress                   = FrameworkToolKit::getIpAddressForLocationId (locationId);
        port                        = FrameworkToolKit::getPortForLocationId (locationId);

        pWaveFailoverAgentSequencerContext->updateSecondaryNodeStatus (ipAddress, port, completionStatus);

        if (WAVE_MESSAGE_SUCCESS != completionStatus)
        {
            trace (TRACE_LEVEL_ERROR, string ("WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase1Callback : Case 1 - Informing ") + ipAddress + " failed : " + completionStatus);
            (WaveFrameworkObjectManager::getInstance ())->disconnectFromLocation (locationId);
        }
    }
    else
    {
        if (NULL != pWaveMessage)
        {
            locationId = pWaveMessage->getReceiverLocationId ();
            ipAddress  = FrameworkToolKit::getIpAddressForLocationId (locationId);
            port       = FrameworkToolKit::getPortForLocationId (locationId);

            pWaveFailoverAgentSequencerContext->updateSecondaryNodeStatus (ipAddress, port, frameworkStatus);
            (WaveFrameworkObjectManager::getInstance ())->disconnectFromLocation (locationId);

            trace (TRACE_LEVEL_ERROR, string ("WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase1Callback : Case 2 - Informing ") + ipAddress + " failed : " + frameworkStatus);
        }
    }

    if (NULL != pWaveMessage)
    {
        delete pWaveMessage;
    }

    if (0 == (pWaveFailoverAgentSequencerContext->getNumberOfCallbacksBeforeAdvancingToNextStep ()))
    {
        LocationId          locationId1 = 0;
        string              ipAddress1  = "";
        SI32                port1       = 0;
        vector<LocationId>  connectedLocationIds;
        UI32                numberOfConnectedLocations = 0;

        pWaveFailoverAgentSequencerContext->getConnectedLocationVector(connectedLocationIds);
        numberOfConnectedLocations = connectedLocationIds.size ();

        for (UI32 i = 0; i < numberOfConnectedLocations; i++)
        {
            locationId1 = connectedLocationIds[i];
            ipAddress1  = FrameworkToolKit::getIpAddressForLocationId (locationId1);
            port1       = FrameworkToolKit::getPortForLocationId      (locationId1);

            if (FRAMEWORK_ERROR_FAILOVER_INFORM_SECONDARY_LOCATIONS_PHASE1_UNKNOWN == (pWaveFailoverAgentSequencerContext->getSecondaryNodeStatus (ipAddress1, port1)))
            {
                pWaveFailoverAgentSequencerContext->updateSecondaryNodeStatus (ipAddress1, port1, FRAMEWORK_ERROR_FAILOVER_INFORM_SECONDARY_LOCATIONS_PHASE1_TIMED_OUT);
                (WaveFrameworkObjectManager::getInstance ())->disconnectFromLocation (locationId1);

                trace (TRACE_LEVEL_ERROR, string ("WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase1Callback : Case 3 - Informing ") + ipAddress1 + " Timeout ");
            }
        }

        pWaveFailoverAgentSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
}

void WaveFailoverAgent::resumeDatabaseDumpStep (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFailoverAgent::resumeDatabaseDumpStep");
    WaveResumeObjectManagerMessage message (DatabaseObjectManager::getWaveServiceId ());
    ResourceId                      status  = sendSynchronously (&message);
    
    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFailoverAgent::resumeDatabaseDumpStep : Could not resume Database.  Status : " + FrameworkToolKit::localize (status));
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        status = message.getCompletionStatus ();
        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFailoverAgent::resumeDatabaseDumpStep : Could not resume Database.  Completion Status : " + FrameworkToolKit::localize (status));
            waveAssert (false, __FILE__, __LINE__);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "WaveFailoverAgent::resumeDatabaseDumpStep : Successfully resumed Database.");
        }
    }

    resumePersistence ();

    pWaveFailoverAgentSequencerContext->executeNextStep(WAVE_MESSAGE_SUCCESS);
}

void WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase2Step (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase2Step: ");
    vector<LocationId>  connectedLocationIds;
    UI32                numberOfConnectedLocations = 0;
    UI32                i                          = 0;

    vector<LocationId>  failedLocationIds          = pWaveFailoverAgentSequencerContext->getFailedLocationIds ();
    UI32                j                          = 0;
    UI32                found                      = 0;

    pWaveFailoverAgentSequencerContext->getConnectedLocationVector(connectedLocationIds);
    numberOfConnectedLocations = connectedLocationIds.size ();

    ++(*pWaveFailoverAgentSequencerContext);
    
    for (i = 0; i < numberOfConnectedLocations; i++)
    {
        found = 0;
        LocationId  locationId = connectedLocationIds[i];
        string      ipAddress  = FrameworkToolKit::getIpAddressForLocationId (locationId);
        UI32        port       = FrameworkToolKit::getPortForLocationId      (locationId);

        trace (TRACE_LEVEL_INFO, string("WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase2Step : Processing Location: ") + ipAddress + string (":") + port + string (":") + locationId + string(" Failed Loc: ") + failedLocationIds[j] + string ("."));

        if (WAVE_MESSAGE_SUCCESS != (pWaveFailoverAgentSequencerContext->getSecondaryNodeStatus (ipAddress, port)))
        {
            trace (TRACE_LEVEL_DEVEL, string("WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase2Step : Skipping failed secondary Location : ") + ipAddress + string (":") + port + string (":") + locationId + string ("."));
            continue;
        }

        for (j = 0; j < failedLocationIds.size(); j++) {
            if(failedLocationIds[j] == locationId) {
                trace (TRACE_LEVEL_INFO, string("WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase2Step : Do not Inform Location ") + ipAddress + string (":") + port + string (":") + locationId + string(" Failed Loc: ") + failedLocationIds[j] + string ("."));
                found = 1;
                break;
            }
        }
        
        if(found) {
            continue;
        }

        FrameworkObjectManagerPrimaryChangedPhase2Message *pMessage = new FrameworkObjectManagerPrimaryChangedPhase2Message();

        ResourceId status = send (pMessage, reinterpret_cast<WaveMessageResponseHandler> (&WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase2Callback), pWaveFailoverAgentSequencerContext, 300000, locationId);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            pWaveFailoverAgentSequencerContext->updateSecondaryNodeStatus (ipAddress, port, status);
            (WaveFrameworkObjectManager::getInstance ())->disconnectFromLocation (locationId);

            trace (TRACE_LEVEL_ERROR, string ("WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase2Step: Not able to inform secondary location : ") + locationId + string (" Error Code : ") + status);
        }
        else
        {
            pWaveFailoverAgentSequencerContext->updateSecondaryNodeStatus (ipAddress, port, FRAMEWORK_ERROR_FAILOVER_INFORM_SECONDARY_LOCATIONS_PHASE2_UNKNOWN);
            ++(*pWaveFailoverAgentSequencerContext);
        }

    }
    
    --(*pWaveFailoverAgentSequencerContext);

    if (0 == (pWaveFailoverAgentSequencerContext->getNumberOfCallbacksBeforeAdvancingToNextStep ()))
    {
        /* We need to advance to next steps here as all sends may be failed or completed within the same stack */
        trace (TRACE_LEVEL_INFO, "WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase2Step: go next step ");
        pWaveFailoverAgentSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
}

void WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase2Callback (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, void *pContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase2Callback");

    WaveFailoverAgentSequencerContext  *pWaveFailoverAgentSequencerContext = reinterpret_cast<WaveFailoverAgentSequencerContext *> (pContext);
    LocationId                           locationId;
    string                               ipAddress;
    SI32                                 port;

    --(*pWaveFailoverAgentSequencerContext);

    if (FRAMEWORK_SUCCESS == frameworkStatus)
    {
        waveAssert (NULL != pWaveMessage, __FILE__, __LINE__);

        ResourceId completionStatus = pWaveMessage->getCompletionStatus ();
        locationId                  = pWaveMessage->getReceiverLocationId ();
        ipAddress                   = FrameworkToolKit::getIpAddressForLocationId (locationId);
        port                        = FrameworkToolKit::getPortForLocationId (locationId);

        pWaveFailoverAgentSequencerContext->updateSecondaryNodeStatus (ipAddress, port, completionStatus);

        if (WAVE_MESSAGE_SUCCESS != completionStatus)
        {
            trace (TRACE_LEVEL_ERROR, string ("WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase2Callback : Case 1 - Informing ") + ipAddress + " failed : " + completionStatus);
            (WaveFrameworkObjectManager::getInstance ())->disconnectFromLocation (locationId);
        }
    }
    else
    {
        if (NULL != pWaveMessage)
        {
            locationId = pWaveMessage->getReceiverLocationId ();
            ipAddress  = FrameworkToolKit::getIpAddressForLocationId (locationId);
            port       = FrameworkToolKit::getPortForLocationId (locationId);

            pWaveFailoverAgentSequencerContext->updateSecondaryNodeStatus (ipAddress, port, frameworkStatus);
            (WaveFrameworkObjectManager::getInstance ())->disconnectFromLocation (locationId);

            trace (TRACE_LEVEL_ERROR, string ("WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase2Callback : Case 2 - Informing ") + ipAddress + " failed : " + frameworkStatus);
        }
    }

    if (NULL != pWaveMessage)
    {
        delete pWaveMessage;
    }

    if (0 == (pWaveFailoverAgentSequencerContext->getNumberOfCallbacksBeforeAdvancingToNextStep ()))
    {
        LocationId          locationId1 = 0;
        string              ipAddress1  = "";
        SI32                port1       = 0;
        vector<LocationId>  connectedLocationIds;
        UI32                numberOfConnectedLocations = 0;

        pWaveFailoverAgentSequencerContext->getConnectedLocationVector(connectedLocationIds);
        numberOfConnectedLocations = connectedLocationIds.size ();

        for (UI32 i = 0; i < numberOfConnectedLocations; i++)
        {
            locationId1 = connectedLocationIds[i];
            ipAddress1  = FrameworkToolKit::getIpAddressForLocationId (locationId1);
            port1       = FrameworkToolKit::getPortForLocationId      (locationId1);

            if (FRAMEWORK_ERROR_FAILOVER_INFORM_SECONDARY_LOCATIONS_PHASE2_UNKNOWN == (pWaveFailoverAgentSequencerContext->getSecondaryNodeStatus (ipAddress1, port1)))
            {
                (WaveFrameworkObjectManager::getInstance ())->disconnectFromLocation (locationId1);
                pWaveFailoverAgentSequencerContext->updateSecondaryNodeStatus (ipAddress1, port1, FRAMEWORK_ERROR_FAILOVER_INFORM_SECONDARY_LOCATIONS_PHASE2_TIMED_OUT);
                trace (TRACE_LEVEL_ERROR, string ("WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase2Callback : Case 3 - Informing ") + ipAddress1 + " Timeout ");
            }
        }

        pWaveFailoverAgentSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
}

void WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase3Step (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase3Step: ");

    vector<LocationId>  connectedLocationIds;
    UI32                numberOfConnectedLocations = 0;
    UI32                i                          = 0;

    vector<LocationId>  failedLocationIds          = pWaveFailoverAgentSequencerContext->getFailedLocationIds ();
    UI32                j                          = 0;
    UI32                found                      = 0;

    pWaveFailoverAgentSequencerContext->getConnectedLocationVector(connectedLocationIds);
    numberOfConnectedLocations = connectedLocationIds.size ();

    ++(*pWaveFailoverAgentSequencerContext);

    for (i = 0; i < numberOfConnectedLocations; i++)
    {
        found = 0;
        LocationId  locationId = connectedLocationIds[i];
        string      ipAddress  = FrameworkToolKit::getIpAddressForLocationId (locationId);
        UI32        port       = FrameworkToolKit::getPortForLocationId      (locationId);

        trace (TRACE_LEVEL_INFO, string("WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase3Step : Processing Location: ") + ipAddress + string (":") + port + string (":") + locationId);

        if (WAVE_MESSAGE_SUCCESS != (pWaveFailoverAgentSequencerContext->getSecondaryNodeStatus (ipAddress, port)))
        {
            trace (TRACE_LEVEL_DEVEL, string("WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase3Step : Skipping failed secondary Location : ") + ipAddress + string (":") + port + string (":") + locationId + string ("."));
            continue;
        }

        for (j = 0; j < failedLocationIds.size(); j++) 
        {
            if(failedLocationIds[j] == locationId) 
            {
                trace (TRACE_LEVEL_INFO, string("WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase3Step : Do not Inform Location ") + ipAddress + string (":") + port + string (":") + locationId + string(" Failed Loc: ") + failedLocationIds[j] + string ("."));
                found = 1;
                break;
            }
        }

        if(found) 
        {
            continue;
        }

        FrameworkObjectManagerPrimaryChangedPhase3Message *pMessage = new FrameworkObjectManagerPrimaryChangedPhase3Message();

        ResourceId status = send (pMessage, reinterpret_cast<WaveMessageResponseHandler> (&WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase3Callback), pWaveFailoverAgentSequencerContext, 0, locationId);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, string ("WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase3Step: Not able to inform secondary location : ") + locationId + string (" Error Code : ") + status);
            (WaveFrameworkObjectManager::getInstance ())->disconnectFromLocation (locationId);
        }
        else
        {
             ++(*pWaveFailoverAgentSequencerContext);
        }

    }

    --(*pWaveFailoverAgentSequencerContext);

    if (0 == (pWaveFailoverAgentSequencerContext->getNumberOfCallbacksBeforeAdvancingToNextStep ()))
    {
        /* We need to advance to next steps here as all sends may be failed or completed within the same stack */
        trace (TRACE_LEVEL_INFO, "WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase3Step: go next step ");
        pWaveFailoverAgentSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
}

void WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase3Callback (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, void *pContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFailoverAgent::informSecondaryLocationsToChangePrimaryPhase3Callback");

    WaveFailoverAgentSequencerContext  *pWaveFailoverAgentSequencerContext = reinterpret_cast<WaveFailoverAgentSequencerContext *> (pContext);

    --(*pWaveFailoverAgentSequencerContext);

	waveAssert (NULL != pWaveMessage, __FILE__, __LINE__);

    if (FRAMEWORK_SUCCESS == frameworkStatus)
    {
        ResourceId completionStatus = pWaveMessage->getCompletionStatus ();
        LocationId locationId       = pWaveMessage->getReceiverLocationId ();

        if (WAVE_MESSAGE_SUCCESS != completionStatus)
        {
            (WaveFrameworkObjectManager::getInstance ())->disconnectFromLocation (locationId);
        }
    }
    else
    {
        LocationId  locationId = pWaveMessage->getReceiverLocationId ();

        (WaveFrameworkObjectManager::getInstance ())->disconnectFromLocation (locationId);
    }

    if (NULL != pWaveMessage)
    {
        delete pWaveMessage;
    }

    if (0 == (pWaveFailoverAgentSequencerContext->getNumberOfCallbacksBeforeAdvancingToNextStep ()))
    {
        pWaveFailoverAgentSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
} 

void WaveFailoverAgent::broadcastPrimaryChangedEventForPlugins (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFailoverAgent::broadcastPrimaryChangedEventForPlugins Entering....");

    PrimaryChangedEvent *pPrimaryChangedEvent = new PrimaryChangedEvent ();
    LocationId           newPrimaryLocationId = FrameworkToolKit::getClusterPrimaryLocationId ();

    pPrimaryChangedEvent->setNewPrimaryLocationId (newPrimaryLocationId);

    broadcast (pPrimaryChangedEvent);

    trace (TRACE_LEVEL_INFO, string("WaveFailoverAgent::broadcastPrimaryChangedEventForPlugins : broadcasted an event PrimaryChangedEvent with  New Primary LocationId is ") + newPrimaryLocationId);
    pWaveFailoverAgentSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS); 
}

void WaveFailoverAgent::saveWaveConfiguration (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext)
{
    FrameworkToolKit::saveWaveConfiguration(true);

    pWaveFailoverAgentSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);    
}

void WaveFailoverAgent::startHeartBeatToSecondariesStep(WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext)
{
   trace (TRACE_LEVEL_INFO, "WaveFailoverAgent::startHeartBeatToSecondariesStep: ");

    vector<LocationId>              knownLocationIds;
    vector<LocationId>              failedLocationIds = pWaveFailoverAgentSequencerContext->getFailedLocationIds ();
    WaveNode                        *pNode    = NULL;
    set<LocationId>                 locationIdSet;
    set<LocationId>::iterator       it;
    string                          ipAddress;
    UI32                            port = 0;
    UI32                            i = 0;

    FrameworkToolKit::getKnownLocations (knownLocationIds);

    UI32 numberOfKnownLocations = knownLocationIds.size ();
    
    vector<WaveManagedObject *> *pResults = querySynchronously (WaveNode::getClassName ());

    waveAssert (NULL != pResults, __FILE__, __LINE__);

    UI32 totalWaveNodes = pResults->size ();

    if ((totalWaveNodes - 1)!= numberOfKnownLocations)
    {
        trace (TRACE_LEVEL_WARN, string ("WaveFailoverAgent::startHeartBeatToSecondariesStep: Total wave nodes (") + totalWaveNodes + string (") does not match with the known locations (") + numberOfKnownLocations + string (")"));
    }

    if (1 > totalWaveNodes)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFailoverAgent::startHeartBeatToSecondariesStep: Wave node does not have itself in the database");
        waveAssert (false, __FILE__, __LINE__);
    }

    //Perform a union of locationId from known location and wave node 
    //set will not allow duplicate entries, so it is ok to insert the same locationId twice
    for (i = 0; i < numberOfKnownLocations; i++)
    {
        locationIdSet.insert (knownLocationIds[i]);
    }

    vector<LocationId> unknownWaveNodeLocationIds;

    for (i = 0; i < totalWaveNodes; i++)
    {
        pNode       = dynamic_cast<WaveNode *> ((*pResults)[i]);

        LocationId  waveNodeLocationId = pNode->getLocationId ();
        bool        foundWaveNode = false;

        if (waveNodeLocationId != FrameworkToolKit::getThisLocationId ())
        {
            for (UI32 n = 0; n < numberOfKnownLocations; n++)
            {
                if (waveNodeLocationId == knownLocationIds [n])
                {
                    foundWaveNode = true;
                    break;
                }
            }

            if (false == foundWaveNode)
            {
                unknownWaveNodeLocationIds.push_back (waveNodeLocationId);
            }
        }
    }

    LocationId locationId = 0;    

    for (it = locationIdSet.begin (); it != locationIdSet.end (); it++)
    {
        bool found = false;
        
        locationId = *it;

        //If the locationId corresponds to itself do not start heart beat

        if (locationId == FrameworkToolKit::getThisLocationId ())
        {
            continue;
        }

        //If the location is in the failed location vector, do not start the heart beat

        for (UI32 j = 0; j < failedLocationIds.size(); j++) 
        {
            if(failedLocationIds[j] == locationId) 
            {
                trace (TRACE_LEVEL_INFO, string("WaveFailoverAgent::startHeartBeatToSecondariesStep: Do not start Heartbeat with Location ") + ipAddress + string (":") + port + string (":") + locationId + string(" Failed Loc: ") + failedLocationIds[j] + string ("."));
    
                found = 1;
                break;
            }
        }

        if(found) 
        {
            continue;
        }

        if (FrameworkToolKit::isAKnownLocation (locationId))
        {
            ipAddress  = FrameworkToolKit::getIpAddressForLocationId (locationId);
            port       = FrameworkToolKit::getPortForLocationId      (locationId);
        }
        else
        {
            waveAssert (false , __FILE__, __LINE__);
        }
        

        StartHeartBeatMessage* pMessage = new StartHeartBeatMessage(); 
        pMessage->setDstIpAddress               (ipAddress);
        pMessage->setDstPortNumber              (port);
        pMessage->setHeartBeatInterval          (10000);
        pMessage->setHeartBeatFailureThreshold  (3);

        ResourceId status = sendSynchronously (pMessage);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
                  trace (TRACE_LEVEL_FATAL, string ("WaveFailoverAgent::startHeartBeatToSecondaryNodes: Could not start heart beating with Node : ") + ipAddress + string (", Port : ") + port + string (", Status = ") + FrameworkToolKit::localize (status));

                  waveAssert (false, __FILE__, __LINE__);
        }
        else
        {
           status = pMessage->getCompletionStatus ();

           if (WAVE_MESSAGE_SUCCESS != status)
           {
                      trace (TRACE_LEVEL_FATAL, string ("WaveFailoverAgent::startHeartBeatToSecondaryNodes : Could not start heart beating with Node : ") + ipAddress + string (", Port : ") + port + string (", Completion Status = ") + FrameworkToolKit::localize (status));
                      waveAssert (false, __FILE__, __LINE__);
           }

           trace (TRACE_LEVEL_INFO, string ("WaveFailoverAgent::startHeartBeatToSecondaryNodes :Started HeartBeat with node ") + ipAddress + string (":") + port);
        }

              delete pMessage;
      }
  
    WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector (pResults);
 
    // Disconnect from the node which got connected between the InformSecondaryLocationPhase 0 and Starting HeartBeat to secondary nodes.
    vector<LocationId>              connectedLocationIds;
    vector<LocationId>              actuallyConnectedLocationIds;
    UI32                            numberOfActuallyConnectedLocations;
    vector<LocationId>::iterator    locationIterator;

    pWaveFailoverAgentSequencerContext->getConnectedLocationVector (connectedLocationIds);
    FrameworkToolKit::getConnectedLocations (actuallyConnectedLocationIds);

    numberOfActuallyConnectedLocations = actuallyConnectedLocationIds.size ();

    for (UI32 location = 0; location < numberOfActuallyConnectedLocations; location ++)
    {
        locationIterator = find (connectedLocationIds.begin (), connectedLocationIds.end (), actuallyConnectedLocationIds [location]);
    
        if (locationIterator == connectedLocationIds.end ())
        {
            trace (TRACE_LEVEL_INFO, string ("disconnect from location in failover") + actuallyConnectedLocationIds [location]);
            (WaveFrameworkObjectManager::getInstance ())->disconnectFromLocation (actuallyConnectedLocationIds [location]);            
        }
    }

    // set the uknown location to trigger the failover in the next step

    pWaveFailoverAgentSequencerContext->setUnknownWaveNodeLocationIds (unknownWaveNodeLocationIds);

    trace (TRACE_LEVEL_INFO, "WaveFailoverAgent::startHeartBeatToSecondaryNodes: Exit ..");
    pWaveFailoverAgentSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);


}

void WaveFailoverAgent::informSecondaryLocationsToRemoveFailedFromKnownLocationsStep (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFailoverAgent::informSecondaryLocationsToRemoveFailedFromKnownLocationsStep: ");
    vector<LocationId>  connectedLocationIds;
    UI32                numberOfConnectedLocations = 0;
    UI32                i                          = 0;

    vector<LocationId>  failedLocationIds          = pWaveFailoverAgentSequencerContext->getFailedLocationIds ();
    UI32                j                          = 0;
    UI32                found                      = 0;

    pWaveFailoverAgentSequencerContext->getConnectedLocationVector(connectedLocationIds);
    numberOfConnectedLocations = connectedLocationIds.size ();

    
    for (i = 0; i < numberOfConnectedLocations; i++)
    {
        found = 0;
        LocationId  locationId = connectedLocationIds[i];
        string      ipAddress  = FrameworkToolKit::getIpAddressForLocationId (locationId);
        UI32        port       = FrameworkToolKit::getPortForLocationId      (locationId);

        trace (TRACE_LEVEL_DEBUG, string("WaveFailoverAgent::informSecondaryLocationsToRemoveFailedFromKnownLocationsStep : Processing Location: ") + ipAddress + string (":") + port + string (":") + locationId + string (".")); 

        if (WAVE_MESSAGE_SUCCESS != (pWaveFailoverAgentSequencerContext->getSecondaryNodeStatus (ipAddress, port)))
        {
            trace (TRACE_LEVEL_DEVEL, string("WaveFailoverAgent::informSecondaryLocationsToRemoveFailedFromKnownLocationsStep : Skipping failed secondary Location : ") + ipAddress + string (":") + port + string (":") + locationId + string ("."));
            continue;
        }

        for (j = 0; j < failedLocationIds.size(); j++) {
            if(failedLocationIds[j] == locationId) {
                trace (TRACE_LEVEL_DEBUG, string("WaveFailoverAgent::informSecondaryLocationsToRemoveFailedFromKnownLocationsStep : Do not Inform Location ") + ipAddress + string (":") + port + string (":") + locationId + string(" Failed Loc: ") + failedLocationIds[j] + string ("."));
                found = 1;
                break;
            }
        }
        
        if(found) {
            continue;
        }

        FrameworkObjectManagerRemoveKnownLocationsMessage *pMessage = new FrameworkObjectManagerRemoveKnownLocationsMessage();

        pMessage->setFailedLocations (failedLocationIds);
        ResourceId status = sendOneWay (pMessage, locationId);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, string ("WaveFailoverAgent::informSecondaryLocationsToRemoveFailedFromKnownLocationsStep: Not able to inform secondary location : ") + locationId + string (" Error Code : ") + status);
        }

    }
    

    pWaveFailoverAgentSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

bool WaveFailoverAgent::isToBeExcluded (const WaveServiceId &waveServiceId)
{
    if (((WaveFrameworkObjectManager::getWaveServiceId ()) == waveServiceId) ||
        (true == (FrameworkToolKit::isALocalService (waveServiceId))) ||
        (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

bool WaveFailoverAgent::isToBeExcludedDuringPrePhase (const WaveServiceId &waveServiceId)
{
    if (((WaveFrameworkObjectManager::getWaveServiceId ()) == waveServiceId) ||
        (true == (FrameworkToolKit::isALocalService (waveServiceId))) ||
        (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

void WaveFailoverAgent::pausePersistence ()
{
    trace (TRACE_LEVEL_DEVEL, "WaveFailoverAgent::pausePersistence : Starting ...");

    WavePauseObjectManagerMessage message (PersistenceObjectManager::getWaveServiceId ());
    ResourceId                      status  = sendSynchronously (&message);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFailoverAgent::pausePersistence : Could not pause Persistence.  Status : " + FrameworkToolKit::localize (status));
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        status = message.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFailoverAgent::pausePersistence : Could not pause Persistence.  Completion Status : " + FrameworkToolKit::localize (status));            
            waveAssert (false, __FILE__, __LINE__);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "WaveFailoverAgent::pausePersistence : Successfully paused Persistence.");
        }
    }
}

void WaveFailoverAgent::resumePersistence ()
{
    trace (TRACE_LEVEL_DEVEL, "WaveFailoverAgent::resumePersistence : Starting ...");

    WaveResumeObjectManagerMessage message (PersistenceObjectManager::getWaveServiceId ());
    ResourceId                      status  = sendSynchronously (&message);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "WaveFailoverAgent::resumePersistence : Could not resume Persistence.  Status : " + FrameworkToolKit::localize (status));
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        status = message.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFailoverAgent::resumePersistence : Could not resume Persistence.  Completion Status : " + FrameworkToolKit::localize (status));
            waveAssert (false, __FILE__, __LINE__);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "WaveFailoverAgent::resumePersistence : Successfully resumed Persistence.");
        }
    }
}

void WaveFailoverAgent::failoverForUnknownWaveNodeWaveServicesStep (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFailoverAgent::failoverWaveServicesStep");
    vector<WaveServiceId> serviceIdsToFailover;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;
    vector<LocationId>     failedLocationIds       = pWaveFailoverAgentSequencerContext->getUnknownWaveNodeLocationIds ();
    //WaveServiceId         serviceToBeIgnored      = pWaveFailoverAgentContext->getServiceToBeIgnored ();
    UI32                   index                   = 0;
    bool                   isConfigurationChange   = pWaveFailoverAgentSequencerContext->getIsConfigurationChange ();
    bool                   isPrincipalChangedWithThisFailover = false;

    if (0 == failedLocationIds.size ())
    {
        pWaveFailoverAgentSequencerContext->executeNextStep(WAVE_MESSAGE_SUCCESS);

        return;
    }

    m_currentFrameworkSequenceGenerator.getFailoverSequence (serviceIdsToFailover);
    numberOfServices = serviceIdsToFailover.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        index = numberOfServices - 1 - i;

        //if ((false == (isToBeExcludedForFailover (serviceIdsToFailover[index]))) && (serviceToBeIgnored != serviceIdsToFailover[index]))
        if (false == (isToBeExcludedForFailover (serviceIdsToFailover[index])))
        {
            WaveFailoverObjectManagerMessage prismFailoverObjectManagerMessage (serviceIdsToFailover[index], FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_CONTROLLED, isPrincipalChangedWithThisFailover);

            (prismFailoverObjectManagerMessage.getFailedLocationIds ()) = failedLocationIds;

            prismFailoverObjectManagerMessage.setIsConfigurationChange (isConfigurationChange);

            ResourceId status = sendSynchronously (&prismFailoverObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, "WaveBootAgent::failoverWaveServicesStep : Could not Failover a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToFailover[index]));
                trace (TRACE_LEVEL_FATAL, "WaveBootAgent::failoverWaveServicesStep : Status                       : " + FrameworkToolKit::localize (status));
                waveAssert (false, __FILE__, __LINE__);
                pWaveFailoverAgentSequencerContext->executeNextStep(status);
                return;
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "failoverForUnknownWaveNodeWaveServicesStep Failed-Over " + FrameworkToolKit::getServiceNameById (serviceIdsToFailover[index]));
            }
        }
        else
        {
            trace (TRACE_LEVEL_DEBUG, "Skipped " + FrameworkToolKit::getServiceNameById (serviceIdsToFailover[index]));
        }
    }

    pWaveFailoverAgentSequencerContext->executeNextStep(WAVE_MESSAGE_SUCCESS);
}

void WaveFailoverAgent::backendSyncUpStep (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext)
{
    trace (TRACE_LEVEL_INFO, "WaveFailoverAgent::backendSyncUpStep: Send back end sync up to all plug-ins .... ");

    ResourceId status = WAVE_MESSAGE_SUCCESS;

    WaveNodeBackendSyncUpAgent *pWaveNodeBackendSyncUpAgent = new WaveNodeBackendSyncUpAgent (m_pWaveObjectManager);

    status = pWaveNodeBackendSyncUpAgent->execute ();

    delete pWaveNodeBackendSyncUpAgent;

    if (WAVE_MESSAGE_SUCCESS != status)
    {
       trace (TRACE_LEVEL_FATAL, string ("WaveFailoverAgent::backendSyncUpStep Failed : Status : ") + FrameworkToolKit::localize (status));
       waveAssert (false, __FILE__, __LINE__);
       pWaveFailoverAgentSequencerContext->executeNextStep(status);
    }

    pWaveFailoverAgentSequencerContext->executeNextStep(status);
    return;
}

}
