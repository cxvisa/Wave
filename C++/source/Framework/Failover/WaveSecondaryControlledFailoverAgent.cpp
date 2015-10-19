/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Failover/WaveSecondaryControlledFailoverAgent.h"
#include "Framework/Failover/WaveFailoverAgentContext.h"
#include "Framework/Failover/WaveFailoverAgentSequencerContext.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"

namespace WaveNs
{

WaveSecondaryControlledFailoverAgent::WaveSecondaryControlledFailoverAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : WaveFailoverAgent (pWaveObjectManager, currentFrameworkSequenceGenerator),m_failoverDueToPrimaryRemoval (false)
{
}

WaveSecondaryControlledFailoverAgent::~WaveSecondaryControlledFailoverAgent ()
{
}

FrameworkObjectManagerFailoverReason WaveSecondaryControlledFailoverAgent::getFailoverReason () const
{
    return (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_CONTROLLED);
}

void WaveSecondaryControlledFailoverAgent::setFailoverDueToPrimaryRemoval ()
{
     m_failoverDueToPrimaryRemoval = true;
}

bool  WaveSecondaryControlledFailoverAgent::getFailoverDueToPrimaryRemoval () const
{
    return m_failoverDueToPrimaryRemoval;
}

void WaveSecondaryControlledFailoverAgent::execute (WaveFailoverAgentContext *pWaveFailoverAgentContext)
{

    //call the base class execute if it is not the case of primary removal
    if(!getFailoverDueToPrimaryRemoval()) 
    {
        WaveFailoverAgent::execute (pWaveFailoverAgentContext);
        return;
    }

    WaveNs::WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryControlledFailoverAgent::resetThisLocationToPrimaryStep),

        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryControlledFailoverAgent::initializeWaveGlobalServicesDuringPrePhaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryControlledFailoverAgent::enableWaveGlobalServicesDuringPrePhaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryControlledFailoverAgent::listenForEventsWaveGlobalServicesDuringPrePhaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryControlledFailoverAgent::bootWaveGlobalServicesDuringPrePhaseStep),

        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryControlledFailoverAgent::initializeWaveGlobalServicesStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryControlledFailoverAgent::enableWaveGlobalServicesStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryControlledFailoverAgent::listenForEventsWaveGlobalServicesStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryControlledFailoverAgent::bootWaveGlobalServicesStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryControlledFailoverAgent::pausePersistenceForPrimaryChangeStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryControlledFailoverAgent::informSecondaryLocationsToChangePrimaryStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryControlledFailoverAgent::informSecondaryLocationsToChangePrimaryPhase1Step),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryControlledFailoverAgent::resumeDatabaseDumpStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryControlledFailoverAgent::backendSyncUpStep),

        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryControlledFailoverAgent::informSecondaryLocationsToChangePrimaryPhase2Step),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryControlledFailoverAgent::informSecondaryLocationsToChangePrimaryPhase3Step),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryControlledFailoverAgent::broadcastPrimaryChangedEventForPlugins), 
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryControlledFailoverAgent::failoverWaveServicesStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryControlledFailoverAgent::removeOldPrimaryLocationStep), 
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryControlledFailoverAgent::informSecondaryLocationsToRemoveFailedFromKnownLocationsStep), 
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryControlledFailoverAgent::startHeartBeatToSecondariesStep), 
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryControlledFailoverAgent::saveWaveConfiguration), 
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryControlledFailoverAgent::failoverForUnknownWaveNodeWaveServicesStep), 
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryControlledFailoverAgent::waveLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryControlledFailoverAgent::waveLinearSequencerFailedStep)
    };

    WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext = new WaveFailoverAgentSequencerContext (pWaveFailoverAgentContext, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pWaveFailoverAgentSequencerContext->setFailedLocationIds                    (pWaveFailoverAgentContext->getFailedLocationIds());
    pWaveFailoverAgentSequencerContext->setServiceToBeIgnored                   (pWaveFailoverAgentContext->getServiceToBeIgnored());
    pWaveFailoverAgentSequencerContext->setOlderPrimaryLocationId               (FrameworkToolKit::getClusterPrimaryLocationId());
    pWaveFailoverAgentSequencerContext->setAnyConfigurationChangeTrackingNumber (PersistenceLocalObjectManager::getAnyConfigurationChangeTrackingNumber ());

    trace (TRACE_LEVEL_DEBUG, string("WaveSecondaryControlledFailoverAgent::execute : set OlderPrimaryLocationId = ") + FrameworkToolKit::getClusterPrimaryLocationId());
    pWaveFailoverAgentSequencerContext->setIsPrincipalChangedWithThisFailover (true);
    
    pWaveFailoverAgentSequencerContext->holdAll ();
    pWaveFailoverAgentSequencerContext->start ();
}

bool WaveSecondaryControlledFailoverAgent::isToBeExcludedForFailover (const WaveServiceId &waveServiceId)
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


WaveBootReason WaveSecondaryControlledFailoverAgent::getBootReason () const
{
    return (WAVE_BOOT_SECONDARY_CONTROLLED_FAILOVER_BOOT);
}

}
