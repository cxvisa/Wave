/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Amit Agrawal                                                 *
 ***************************************************************************/

#include "Framework/Core/WaveFrameworkObjectManagerPostbootWorker.h"
#include "Framework/Core/FrameworkObjectManagerMessages.h"
#include "Framework/MultiThreading/WaveThread.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/Postboot/WavePostbootAgent.h"
#include "Framework/Utils/TraceUtils.h"

namespace WaveNs
{

WaveFrameworkObjectManagerPostbootWorker::WaveFrameworkObjectManagerPostbootWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_EXECUTE_POSTBOOT_PASSES, reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManagerPostbootWorker::postbootMessageHandler));
}

WaveFrameworkObjectManagerPostbootWorker::~WaveFrameworkObjectManagerPostbootWorker ()
{
}

void WaveFrameworkObjectManagerPostbootWorker::postbootMessageHandler (WavePostbootObjectManagerMessage *pWavePostbootObjectManagerMessage)
{
    ResourceId  status;

    WavePostbootAgent  *pWavePostbootAgent = new WavePostbootAgent(m_pWaveObjectManager);

    updateHardwareSynchronizationState (WAVE_NODE_HARDWARE_SYNCHRONIZATION_STATE_SYNCHRONIZING, FrameworkToolKit::getThisLocationId ());

    status = pWavePostbootAgent->execute();

    if (WAVE_MESSAGE_SUCCESS == status)
    {
        updateHardwareSynchronizationState (WAVE_NODE_HARDWARE_SYNCHRONIZATION_STATE_IN_SYNC, FrameworkToolKit::getThisLocationId ());
    }
    else
    {
        updateHardwareSynchronizationState (WAVE_NODE_HARDWARE_SYNCHRONIZATION_STATE_OUT_OF_SYNC, FrameworkToolKit::getThisLocationId ());
    }

    pWavePostbootObjectManagerMessage->setCompletionStatus (status);
    reply (pWavePostbootObjectManagerMessage);

    delete(pWavePostbootAgent);
}

}
