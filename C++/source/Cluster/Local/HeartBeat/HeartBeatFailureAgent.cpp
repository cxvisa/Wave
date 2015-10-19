/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Cluster/Local/HeartBeat/HeartBeatFailureAgent.h"
#include "Cluster/Local/HeartBeat/HeartBeatObjectManager.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/WaveFrameworkMessages.h"
#include "Cluster/Local/HeartBeat/HeartBeatFailureAgentContext.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"

namespace WaveNs
{

HeartBeatFailureAgent::HeartBeatFailureAgent (WaveObjectManager *pWaveObjectManager, IpV4Address ipAddress, UI16 portNumber)
    : WaveWorker (pWaveObjectManager), 
	m_ipAddress  (ipAddress),
	m_portNumber (portNumber)
{
}

HeartBeatFailureAgent::~HeartBeatFailureAgent ()
{
}

ResourceId HeartBeatFailureAgent::execute ()
{
    WaveNs::PrismSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HeartBeatFailureAgent::getListOfEnabledServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HeartBeatFailureAgent::sendHeartBeatFailureStep),

        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HeartBeatFailureAgent::prismSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&HeartBeatFailureAgent::prismSynchronousLinearSequencerFailedStep)
    };

    HeartBeatFailureAgentContext *pHeartBeatFailureAgentContext = new HeartBeatFailureAgentContext (reinterpret_cast<PrismAsynchronousContext *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    ResourceId status = pHeartBeatFailureAgentContext->execute ();

    return (status);
}

ResourceId HeartBeatFailureAgent::getListOfEnabledServicesStep (HeartBeatFailureAgentContext *pHeartBeatFailureAgentContext)
{
    vector<WaveServiceId> &enabledServices = pHeartBeatFailureAgentContext->getEnabledServices ();

    WaveObjectManager::getListOfEnabledServices (enabledServices);

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId HeartBeatFailureAgent::sendHeartBeatFailureStep (HeartBeatFailureAgentContext *pHeartBeatFailureAgentContext)
{
    vector<WaveServiceId> &serviceIdsToSendHeartBeatFailure = pHeartBeatFailureAgentContext->getEnabledServices ();
    UI32                    i                    = 0;
    UI32                    numberOfServices     = 0;

    numberOfServices = serviceIdsToSendHeartBeatFailure.size ();

    trace (TRACE_LEVEL_INFO, "PrismHeartbeatFailureAgent::sendHeartBeatFailureStep: Initiate heartbeat failure for all services.");

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (requiresHeartBeatFailureNotification (serviceIdsToSendHeartBeatFailure[i])))
        {
            continue;
        }

        PrismHeartbeatFailureObjectManagerMessage *prismHeartbeatFailureObjectManagerMessage = new PrismHeartbeatFailureObjectManagerMessage (serviceIdsToSendHeartBeatFailure[i], m_ipAddress, m_portNumber);

        ResourceId status = sendOneWay (prismHeartbeatFailureObjectManagerMessage);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "PrismHeartbeatFailureAgent::sendHeartBeatFailureStep: Could not send Heartbeat Failure to a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToSendHeartBeatFailure[i]));
            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_DEVEL, "Successfully sent SendHeartBeatFailure " + FrameworkToolKit::getServiceNameById (serviceIdsToSendHeartBeatFailure[i]));
        }
    }

    trace (TRACE_LEVEL_INFO, "PrismHeartbeatFailureAgent::sendHeartBeatFailureStep: Finish heartbeat failure for all services.");
    return (WAVE_MESSAGE_SUCCESS);
}

bool HeartBeatFailureAgent::requiresHeartBeatFailureNotification(const WaveServiceId &waveServiceId)
{
    if (((HeartBeatObjectManager::getWaveServiceId               ()) == waveServiceId) ||
        (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))))
    {
        return (false);
    }
    else
    {
        return (true);
    }
}

}
