/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anand Kumar Subramanian                                      *
 ***************************************************************************/

#include "Framework/Core/WaveNodeBackendSyncUpAgent.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/WaveFrameworkMessages.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Core/ApplicationSpecificServices.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"
#include "Cluster/Local/ClusterLocalObjectManager.h"

namespace WaveNs
{

WaveNodeBackendSyncUpAgent::WaveNodeBackendSyncUpAgent (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
}

WaveNodeBackendSyncUpAgent::~WaveNodeBackendSyncUpAgent ()
{
}

ResourceId WaveNodeBackendSyncUpAgent::execute ()
{
    WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveNodeBackendSyncUpAgent::sendBackendSyncUpStep),

        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveNodeBackendSyncUpAgent::waveSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveNodeBackendSyncUpAgent::waveSynchronousLinearSequencerFailedStep)
    };

    WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext = new WaveSynchronousLinearSequencerContext (reinterpret_cast<WaveAsynchronousContext *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    ResourceId status = pWaveSynchronousLinearSequencerContext->execute ();

    return (status);
}

ResourceId WaveNodeBackendSyncUpAgent::sendBackendSyncUpStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToSend;
    UI32                    i                    = 0;
    UI32                    numberOfServices     = 0;

    WaveObjectManager::getListOfEnabledServices (serviceIdsToSend);
    numberOfServices = serviceIdsToSend.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (requiresBackendSyncUpNotification(serviceIdsToSend[i])))
        {
            continue;
        }

        WaveObjectManagerBackendSyncUpMessage waveObjectManagerBackendSyncUpMessage (serviceIdsToSend[i]);

        WaveMessageStatus status = sendSynchronously (&waveObjectManagerBackendSyncUpMessage, FrameworkToolKit::getThisLocationId ());
        ResourceId        processingStatus = WAVE_MESSAGE_SUCCESS;

        if(WAVE_MESSAGE_SUCCESS != status)
        {
            processingStatus = status;

        }
        else
        {
            ResourceId    completionStatus = waveObjectManagerBackendSyncUpMessage.getCompletionStatus();
            if (WAVE_MESSAGE_SUCCESS != completionStatus)
            {
                processingStatus = completionStatus;

            }
        }

        if (WAVE_MESSAGE_SUCCESS != processingStatus)
        {
            trace (TRACE_LEVEL_FATAL, "WaveNodeBackendSyncUpAgent::sendBackendSyncUpStep: Could not send backend syncup message to a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToSend [i]));
            return (processingStatus);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "WaveNodeBackendSyncUpAgent::sendBackendSyncUpStep: Successfully completed Backend sync up for the service " + FrameworkToolKit::getServiceNameById (serviceIdsToSend[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

bool WaveNodeBackendSyncUpAgent::requiresBackendSyncUpNotification (const WaveServiceId &waveServiceId)
{
    if ((!FrameworkToolKit::isALocalService (waveServiceId)) || ((WaveFrameworkObjectManager::getWaveServiceId ()) == waveServiceId) ||
		 (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId)))
    {
        return (false);
    }
    else
    {
        return (true);
    }
}

}
