/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anand Kumar Subramanian                                      *
 ***************************************************************************/

#include "Framework/Core/WaveNodeBackendSyncUpAgent.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/PrismFrameworkMessages.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"
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
    WaveNs::PrismSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&WaveNodeBackendSyncUpAgent::sendBackendSyncUpStep),

        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&WaveNodeBackendSyncUpAgent::prismSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&WaveNodeBackendSyncUpAgent::prismSynchronousLinearSequencerFailedStep)
    };

    PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext = new PrismSynchronousLinearSequencerContext (reinterpret_cast<PrismAsynchronousContext *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    ResourceId status = pPrismSynchronousLinearSequencerContext->execute ();

    return (status);
}

ResourceId WaveNodeBackendSyncUpAgent::sendBackendSyncUpStep (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext)
{
    vector<PrismServiceId> serviceIdsToSend;
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

bool WaveNodeBackendSyncUpAgent::requiresBackendSyncUpNotification (const PrismServiceId &prismServiceId)
{
    if ((!FrameworkToolKit::isALocalService (prismServiceId)) || ((PrismFrameworkObjectManager::getPrismServiceId ()) == prismServiceId) ||
		 (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (prismServiceId)))
    {
        return (false);
    }
    else
    {
        return (true);
    }
}

}
