/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/ConfigReplayEnd/FileReplayEndAgent.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/PrismFrameworkMessages.h"
#include "Framework/ConfigReplayEnd/FileReplayEndAgentContext.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"

namespace WaveNs
{

FileReplayEndAgent::FileReplayEndAgent (WaveObjectManager *pWaveObjectManager) 
    : WaveWorker (pWaveObjectManager) 
{
}

FileReplayEndAgent::~FileReplayEndAgent ()
{
}

ResourceId FileReplayEndAgent::execute ()
{
    WaveNs::PrismSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&FileReplayEndAgent::getListOfEnabledServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&FileReplayEndAgent::sendFileReplayEndStep),

        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&FileReplayEndAgent::prismSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&FileReplayEndAgent::prismSynchronousLinearSequencerFailedStep)
    };

    FileReplayEndAgentContext *pFileReplayEndAgentContext = new FileReplayEndAgentContext (reinterpret_cast<PrismAsynchronousContext *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    ResourceId status = pFileReplayEndAgentContext->execute ();

    return (status);
}

ResourceId FileReplayEndAgent::getListOfEnabledServicesStep (FileReplayEndAgentContext *pFileReplayEndAgentContext)
{
    vector<WaveServiceId> &enabledServices = pFileReplayEndAgentContext->getEnabledServices ();

    WaveObjectManager::getListOfEnabledServices (enabledServices);

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId FileReplayEndAgent::sendFileReplayEndStep (FileReplayEndAgentContext *pFileReplayEndAgentContext)
{
    vector<WaveServiceId> &serviceIdsToSendFileReplayEnd = pFileReplayEndAgentContext->getEnabledServices ();
    UI32                    i                    = 0;
    UI32                    numberOfServices     = 0;

    numberOfServices = serviceIdsToSendFileReplayEnd.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (requiresFileReplayEndNotification (serviceIdsToSendFileReplayEnd[i])))
        {
            continue;
        }

        PrismFileReplayEndObjectManagerMessage *prismFileReplayEndObjectManagerMessage = new PrismFileReplayEndObjectManagerMessage (serviceIdsToSendFileReplayEnd[i]);

        ResourceId status = sendSynchronously (prismFileReplayEndObjectManagerMessage);

        delete prismFileReplayEndObjectManagerMessage;

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "PrismFileReplayEndAgent::sendFileReplayEndStep: Could not send File Replay End to a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToSendFileReplayEnd[i]));
            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Successfully sent FileReplayEnd " + FrameworkToolKit::getServiceNameById (serviceIdsToSendFileReplayEnd[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

bool FileReplayEndAgent::requiresFileReplayEndNotification(const WaveServiceId &prismServiceId)
{
    if (((PrismFrameworkObjectManager::getWaveServiceId               ()) == prismServiceId) ||
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
