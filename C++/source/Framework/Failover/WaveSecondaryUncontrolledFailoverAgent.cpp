/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Failover/WaveSecondaryUncontrolledFailoverAgent.h"
#include "Framework/Failover/WaveFailoverAgentContext.h"
#include "Framework/Failover/WaveFailoverAgentSequencerContext.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"

namespace WaveNs
{

WaveSecondaryUncontrolledFailoverAgent::WaveSecondaryUncontrolledFailoverAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : WaveFailoverAgent (pWaveObjectManager, currentFrameworkSequenceGenerator)
{
}

WaveSecondaryUncontrolledFailoverAgent::~WaveSecondaryUncontrolledFailoverAgent ()
{
}

FrameworkObjectManagerFailoverReason WaveSecondaryUncontrolledFailoverAgent::getFailoverReason () const
{
    return (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED);
}

void WaveSecondaryUncontrolledFailoverAgent::execute (WaveFailoverAgentContext *pWaveFailoverAgentContext)
{
    WaveNs::WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryUncontrolledFailoverAgent::resetThisLocationToPrimaryStep),

        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryUncontrolledFailoverAgent::initializeWaveGlobalServicesDuringPrePhaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryUncontrolledFailoverAgent::enableWaveGlobalServicesDuringPrePhaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryUncontrolledFailoverAgent::listenForEventsWaveGlobalServicesDuringPrePhaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryUncontrolledFailoverAgent::bootWaveGlobalServicesDuringPrePhaseStep),

        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryUncontrolledFailoverAgent::initializeWaveGlobalServicesStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryUncontrolledFailoverAgent::enableWaveGlobalServicesStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryUncontrolledFailoverAgent::listenForEventsWaveGlobalServicesStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryUncontrolledFailoverAgent::bootWaveGlobalServicesStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryUncontrolledFailoverAgent::pausePersistenceForPrimaryChangeStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryUncontrolledFailoverAgent::informSecondaryLocationsToChangePrimaryStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryUncontrolledFailoverAgent::informSecondaryLocationsToChangePrimaryPhase1Step),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryUncontrolledFailoverAgent::resumeDatabaseDumpStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryUncontrolledFailoverAgent::backendSyncUpStep),

        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryUncontrolledFailoverAgent::informSecondaryLocationsToChangePrimaryPhase2Step),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryUncontrolledFailoverAgent::informSecondaryLocationsToChangePrimaryPhase3Step),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryUncontrolledFailoverAgent::broadcastPrimaryChangedEventForPlugins),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryUncontrolledFailoverAgent::failoverWaveServicesStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryUncontrolledFailoverAgent::startHeartBeatToSecondariesStep), 
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryUncontrolledFailoverAgent::saveWaveConfiguration), 
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryUncontrolledFailoverAgent::failoverForUnknownWaveNodeWaveServicesStep), 
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryUncontrolledFailoverAgent::waveLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSecondaryUncontrolledFailoverAgent::waveLinearSequencerFailedStep)
    };

    WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext = new WaveFailoverAgentSequencerContext (pWaveFailoverAgentContext, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pWaveFailoverAgentSequencerContext->setFailedLocationIds                    (pWaveFailoverAgentContext->getFailedLocationIds());
    pWaveFailoverAgentSequencerContext->setServiceToBeIgnored                   (pWaveFailoverAgentContext->getServiceToBeIgnored());
    pWaveFailoverAgentSequencerContext->setIsPrincipalChangedWithThisFailover   (true);
    pWaveFailoverAgentSequencerContext->setAnyConfigurationChangeTrackingNumber (PersistenceLocalObjectManager::getAnyConfigurationChangeTrackingNumber ());
    pWaveFailoverAgentSequencerContext->setOlderPrimaryLocationId               (FrameworkToolKit::getClusterPrimaryLocationId());

    trace (TRACE_LEVEL_DEBUG, string("WaveSecondaryUncontrolledFailoverAgent::execute: set OlderPrimaryLocationId = ") + FrameworkToolKit::getClusterPrimaryLocationId());

    pWaveFailoverAgentSequencerContext->holdAll ();
    pWaveFailoverAgentSequencerContext->start ();
}

bool WaveSecondaryUncontrolledFailoverAgent::isToBeExcludedForFailover (const WaveServiceId &waveServiceId)
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

WaveBootReason WaveSecondaryUncontrolledFailoverAgent::getBootReason () const
{
    return (WAVE_BOOT_SECONDARY_UNCONTROLLED_FAILOVER_BOOT);
}

}
