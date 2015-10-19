/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/ConfigReplayEnd/FileReplayEndAgent.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/WaveFrameworkMessages.h"
#include "Framework/ConfigReplayEnd/FileReplayEndAgentContext.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
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
    WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&FileReplayEndAgent::getListOfEnabledServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&FileReplayEndAgent::sendFileReplayEndStep),

        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&FileReplayEndAgent::prismSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&FileReplayEndAgent::prismSynchronousLinearSequencerFailedStep)
    };

    FileReplayEndAgentContext *pFileReplayEndAgentContext = new FileReplayEndAgentContext (reinterpret_cast<WaveAsynchronousContext *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

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

        WaveFileReplayEndObjectManagerMessage *prismFileReplayEndObjectManagerMessage = new WaveFileReplayEndObjectManagerMessage (serviceIdsToSendFileReplayEnd[i]);

        ResourceId status = sendSynchronously (prismFileReplayEndObjectManagerMessage);

        delete prismFileReplayEndObjectManagerMessage;

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFileReplayEndAgent::sendFileReplayEndStep: Could not send File Replay End to a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToSendFileReplayEnd[i]));
            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Successfully sent FileReplayEnd " + FrameworkToolKit::getServiceNameById (serviceIdsToSendFileReplayEnd[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

bool FileReplayEndAgent::requiresFileReplayEndNotification(const WaveServiceId &waveServiceId)
{
    if (((WaveFrameworkObjectManager::getWaveServiceId               ()) == waveServiceId) ||
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
