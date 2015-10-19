/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/ExternalStateSynchronization/WaveExternalStateSynchronizationAgent.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/WaveFrameworkMessages.h"
#include "Framework/ExternalStateSynchronization/WaveExternalStateSynchronizationAgentContext.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"

namespace WaveNs
{

WaveExternalStateSynchronizationAgent::WaveExternalStateSynchronizationAgent (WaveObjectManager *pWaveObjectManager, UI32 fssStageNumber, ResourceId serviceType)
    : WaveWorker (pWaveObjectManager),
      m_fssStageNumber (fssStageNumber),
      m_serviceType (serviceType)    
{
}

WaveExternalStateSynchronizationAgent::~WaveExternalStateSynchronizationAgent ()
{
}

ResourceId WaveExternalStateSynchronizationAgent::execute ()
{
    WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveExternalStateSynchronizationAgent::getListOfEnabledServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveExternalStateSynchronizationAgent::externalStateSynchronizationServicesStep),

        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveExternalStateSynchronizationAgent::waveSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveExternalStateSynchronizationAgent::waveSynchronousLinearSequencerFailedStep)
    };

    WaveExternalStateSynchronizationAgentContext *pWaveExternalStateSynchronizationAgentContext = new WaveExternalStateSynchronizationAgentContext (reinterpret_cast<WaveAsynchronousContext *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    ResourceId status = pWaveExternalStateSynchronizationAgentContext->execute ();

    return (status);
}

ResourceId WaveExternalStateSynchronizationAgent::getListOfEnabledServicesStep (WaveExternalStateSynchronizationAgentContext *pWaveExternalStateSynchronizationAgentContext)
{
    vector<WaveServiceId> &enabledServices = pWaveExternalStateSynchronizationAgentContext->getEnabledServices ();

    WaveObjectManager::getListOfEnabledServices (enabledServices);

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveExternalStateSynchronizationAgent::externalStateSynchronizationServicesStep (WaveExternalStateSynchronizationAgentContext *pWaveExternalStateSynchronizationAgentContext)
{
    vector<WaveServiceId> &serviceIdsToExternalStateSynchronization = pWaveExternalStateSynchronizationAgentContext->getEnabledServices ();
    UI32                    i                    = 0;
    UI32                    numberOfServices     = 0;

    numberOfServices = serviceIdsToExternalStateSynchronization.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (requiresExternalStateSynchronization (serviceIdsToExternalStateSynchronization[i])))
        {
            continue;
        }

        WaveExternalStateSynchronizationObjectManagerMessage waveExternalStateSynchronizationObjectManagerMessage (serviceIdsToExternalStateSynchronization[i], m_fssStageNumber, m_serviceType);

        ResourceId status = sendSynchronously (&waveExternalStateSynchronizationObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveBootAgent::ExternalStateSynchronizationServicesStep : Could not ExternalStateSynchronization a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToExternalStateSynchronization[i]));
            waveAssert (false, __FILE__, __LINE__);
            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_DEVEL, "ExternalStateSynchronization " + FrameworkToolKit::getServiceNameById (serviceIdsToExternalStateSynchronization[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}
                
bool WaveExternalStateSynchronizationAgent::requiresExternalStateSynchronization (const WaveServiceId &waveServiceId)
{
    if (((WaveFrameworkObjectManager::getWaveServiceId               ()) == waveServiceId) ||
        (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))) ||
        (false == WaveFrameworkObjectManager::isExternalStateSynchronizationRequired (waveServiceId)))
    {
        return (false);
    }
    else
    {
        return (true);
    }
}

}
