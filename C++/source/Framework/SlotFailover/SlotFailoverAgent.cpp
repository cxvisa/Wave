/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/SlotFailover/SlotFailoverAgent.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/WaveFrameworkMessages.h"
#include "Framework/SlotFailover/SlotFailoverAgentContext.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"

namespace WaveNs
{

SlotFailoverAgent::SlotFailoverAgent (WaveObjectManager *pWaveObjectManager, UI32 slotNumber) 
    : WaveWorker (pWaveObjectManager),
    m_slotNumber (slotNumber)
{
}

SlotFailoverAgent::~SlotFailoverAgent ()
{
}

ResourceId SlotFailoverAgent::execute ()
{
    WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SlotFailoverAgent::getListOfEnabledServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SlotFailoverAgent::sendSlotFailoverStep),

        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SlotFailoverAgent::prismSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&SlotFailoverAgent::prismSynchronousLinearSequencerFailedStep)
    };

    SlotFailoverAgentContext *pSlotFailoverAgentContext = new SlotFailoverAgentContext (reinterpret_cast<WaveAsynchronousContext *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    ResourceId status = pSlotFailoverAgentContext->execute ();

    return (status);
}

ResourceId SlotFailoverAgent::getListOfEnabledServicesStep (SlotFailoverAgentContext *pSlotFailoverAgentContext)
{
    vector<WaveServiceId> &enabledServices = pSlotFailoverAgentContext->getEnabledServices ();

    WaveObjectManager::getListOfEnabledServices (enabledServices);

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId SlotFailoverAgent::sendSlotFailoverStep (SlotFailoverAgentContext *pSlotFailoverAgentContext)
{
    vector<WaveServiceId> &serviceIdsToSendSlotFailover = pSlotFailoverAgentContext->getEnabledServices ();
    UI32                    i                    = 0;
    UI32                    numberOfServices     = 0;

    numberOfServices = serviceIdsToSendSlotFailover.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (requiresSlotFailoverNotification (serviceIdsToSendSlotFailover[i])))
        {
            continue;
        }

        WaveSlotFailoverObjectManagerMessage *prismSlotFailoverObjectManagerMessage = new WaveSlotFailoverObjectManagerMessage (serviceIdsToSendSlotFailover[i], m_slotNumber);

        ResourceId status = sendSynchronously (prismSlotFailoverObjectManagerMessage);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveSlotFailoverAgent::sendSlotFailoverStep: Could not send SlotFailover to a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToSendSlotFailover[i]));
            return (status);
        }
        else
        {
            status = prismSlotFailoverObjectManagerMessage->getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, "WaveSlotFailoverAgent::sendSlotFailoverStep: Not able to update Instance Id  Completion Status : " + FrameworkToolKit::localize (status));
                waveAssert (false, __FILE__, __LINE__);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "WaveSlotFailoverAgent::sendSlotFailoverStep : Successfully sent SlotFailover " + FrameworkToolKit::getServiceNameById (serviceIdsToSendSlotFailover[i]));
            }
        }

        delete prismSlotFailoverObjectManagerMessage;
    }

    return (WAVE_MESSAGE_SUCCESS);
}

bool SlotFailoverAgent::requiresSlotFailoverNotification(const WaveServiceId &waveServiceId)
{
    if (((WaveFrameworkObjectManager::getWaveServiceId               ()) == waveServiceId) ||
        (true != (FrameworkToolKit::isALocalService (waveServiceId))) ||
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
