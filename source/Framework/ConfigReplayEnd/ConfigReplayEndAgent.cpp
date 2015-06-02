/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/ConfigReplayEnd/ConfigReplayEndAgent.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/PrismFrameworkMessages.h"
#include "Framework/ConfigReplayEnd/ConfigReplayEndAgentContext.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"

namespace WaveNs
{

ConfigReplayEndAgent::ConfigReplayEndAgent (WaveObjectManager *pWaveObjectManager) 
    : WaveWorker (pWaveObjectManager) 
{
}

ConfigReplayEndAgent::~ConfigReplayEndAgent ()
{
}

ResourceId ConfigReplayEndAgent::execute ()
{
    WaveNs::PrismSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&ConfigReplayEndAgent::getListOfEnabledServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&ConfigReplayEndAgent::sendConfigReplayEndStep),

        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&ConfigReplayEndAgent::prismSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&ConfigReplayEndAgent::prismSynchronousLinearSequencerFailedStep)
    };

    ConfigReplayEndAgentContext *pConfigReplayEndAgentContext = new ConfigReplayEndAgentContext (reinterpret_cast<PrismAsynchronousContext *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    ResourceId status = pConfigReplayEndAgentContext->execute ();

    return (status);
}

ResourceId ConfigReplayEndAgent::getListOfEnabledServicesStep (ConfigReplayEndAgentContext *pConfigReplayEndAgentContext)
{
    vector<PrismServiceId> &enabledServices = pConfigReplayEndAgentContext->getEnabledServices ();

    WaveObjectManager::getListOfEnabledServices (enabledServices);

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId ConfigReplayEndAgent::sendConfigReplayEndStep (ConfigReplayEndAgentContext *pConfigReplayEndAgentContext)
{
    vector<PrismServiceId> &serviceIdsToSendConfigReplayEnd = pConfigReplayEndAgentContext->getEnabledServices ();
    UI32                    i                    = 0;
    UI32                    numberOfServices     = 0;

    numberOfServices = serviceIdsToSendConfigReplayEnd.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (requiresConfigReplayEndNotification (serviceIdsToSendConfigReplayEnd[i])))
        {
            continue;
        }

        PrismConfigReplayEndObjectManagerMessage *prismConfigReplayEndObjectManagerMessage = new PrismConfigReplayEndObjectManagerMessage (serviceIdsToSendConfigReplayEnd[i]);

        ResourceId status = sendSynchronously (prismConfigReplayEndObjectManagerMessage);

        delete prismConfigReplayEndObjectManagerMessage;

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "PrismConfigReplayEndAgent::sendConfigReplayEndStep: Could not send Config Replay End to a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToSendConfigReplayEnd[i]));
            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Successfully sent ConfigReplayEnd " + FrameworkToolKit::getServiceNameById (serviceIdsToSendConfigReplayEnd[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

bool ConfigReplayEndAgent::requiresConfigReplayEndNotification(const PrismServiceId &prismServiceId)
{
    if (((PrismFrameworkObjectManager::getPrismServiceId               ()) == prismServiceId) ||
        (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (prismServiceId))))
    {
        return (false);
    }
    else
    {
        return (true);
    }
}

}
