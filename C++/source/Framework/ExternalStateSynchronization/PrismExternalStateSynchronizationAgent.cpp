/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/ExternalStateSynchronization/PrismExternalStateSynchronizationAgent.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/PrismFrameworkMessages.h"
#include "Framework/ExternalStateSynchronization/PrismExternalStateSynchronizationAgentContext.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"

namespace WaveNs
{

PrismExternalStateSynchronizationAgent::PrismExternalStateSynchronizationAgent (WaveObjectManager *pWaveObjectManager, UI32 fssStageNumber, ResourceId serviceType)
    : WaveWorker (pWaveObjectManager),
      m_fssStageNumber (fssStageNumber),
      m_serviceType (serviceType)    
{
}

PrismExternalStateSynchronizationAgent::~PrismExternalStateSynchronizationAgent ()
{
}

ResourceId PrismExternalStateSynchronizationAgent::execute ()
{
    WaveNs::PrismSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismExternalStateSynchronizationAgent::getListOfEnabledServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismExternalStateSynchronizationAgent::externalStateSynchronizationServicesStep),

        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismExternalStateSynchronizationAgent::prismSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismExternalStateSynchronizationAgent::prismSynchronousLinearSequencerFailedStep)
    };

    PrismExternalStateSynchronizationAgentContext *pPrismExternalStateSynchronizationAgentContext = new PrismExternalStateSynchronizationAgentContext (reinterpret_cast<PrismAsynchronousContext *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    ResourceId status = pPrismExternalStateSynchronizationAgentContext->execute ();

    return (status);
}

ResourceId PrismExternalStateSynchronizationAgent::getListOfEnabledServicesStep (PrismExternalStateSynchronizationAgentContext *pPrismExternalStateSynchronizationAgentContext)
{
    vector<WaveServiceId> &enabledServices = pPrismExternalStateSynchronizationAgentContext->getEnabledServices ();

    WaveObjectManager::getListOfEnabledServices (enabledServices);

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId PrismExternalStateSynchronizationAgent::externalStateSynchronizationServicesStep (PrismExternalStateSynchronizationAgentContext *pPrismExternalStateSynchronizationAgentContext)
{
    vector<WaveServiceId> &serviceIdsToExternalStateSynchronization = pPrismExternalStateSynchronizationAgentContext->getEnabledServices ();
    UI32                    i                    = 0;
    UI32                    numberOfServices     = 0;

    numberOfServices = serviceIdsToExternalStateSynchronization.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (requiresExternalStateSynchronization (serviceIdsToExternalStateSynchronization[i])))
        {
            continue;
        }

        PrismExternalStateSynchronizationObjectManagerMessage prismExternalStateSynchronizationObjectManagerMessage (serviceIdsToExternalStateSynchronization[i], m_fssStageNumber, m_serviceType);

        ResourceId status = sendSynchronously (&prismExternalStateSynchronizationObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "PrismBootAgent::ExternalStateSynchronizationServicesStep : Could not ExternalStateSynchronization a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToExternalStateSynchronization[i]));
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
                
bool PrismExternalStateSynchronizationAgent::requiresExternalStateSynchronization (const WaveServiceId &waveServiceId)
{
    if (((PrismFrameworkObjectManager::getWaveServiceId               ()) == waveServiceId) ||
        (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))) ||
        (false == PrismFrameworkObjectManager::isExternalStateSynchronizationRequired (waveServiceId)))
    {
        return (false);
    }
    else
    {
        return (true);
    }
}

}
