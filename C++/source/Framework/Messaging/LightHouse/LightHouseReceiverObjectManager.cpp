/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/LightHouse/LightHouseReceiverObjectManager.h"
#include "Framework/Utils/AssertUtils.h"

#include "Framework/Boot/BootCompleteForThisLocationEvent.h"
#include "Framework/Boot/BootTypes.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"

namespace WaveNs
{

LightHouseReceiverObjectManager::LightHouseReceiverObjectManager ()
    : WaveLocalObjectManager (getServiceName ())
{
    setAllowAutomaticallyUnlistenForEvents (false);
}

LightHouseReceiverObjectManager::~LightHouseReceiverObjectManager ()
{
}

string LightHouseReceiverObjectManager::getServiceName ()
{
    return ("Light House Receiver");
}

LightHouseReceiverObjectManager *LightHouseReceiverObjectManager::getInstance ()
{
    static LightHouseReceiverObjectManager *pLightHouseReceiverObjectManager = new LightHouseReceiverObjectManager ();

    WaveNs::waveAssert (NULL != pLightHouseReceiverObjectManager, __FILE__, __LINE__);

    return (pLightHouseReceiverObjectManager);
}

WaveServiceId LightHouseReceiverObjectManager::getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

void LightHouseReceiverObjectManager::initialize (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void LightHouseReceiverObjectManager::boot (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void LightHouseReceiverObjectManager::listenForEvents (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    listenForEvent (WaveFrameworkObjectManager::getWaveServiceId (), BOOT_COMPLETE_FOR_THIS_LOCATION, reinterpret_cast<WaveEventHandler> (&LightHouseReceiverObjectManager::bootCompleteForThisLocationEventHandler));

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void LightHouseReceiverObjectManager::bootCompleteForThisLocationEventHandler (const BootCompleteForThisLocationEvent *&pBootCompleteForThisLocationEvent)
{
    // Since we told framework not to unlistenEvents, we must explicitly unlisten for events since we are going to go into an infinite while loop.

    unlistenEvents ();

    reply (reinterpret_cast<const WaveEvent *&> (pBootCompleteForThisLocationEvent));

    trace (TRACE_LEVEL_INFO, "LightHouseReceiverObjectManager::bootCompleteForThisLocationEventHandler : Now accepting connections from Wave Clients.");

    for (;;)
    {
        waveSleep (1);
    }
}

}
