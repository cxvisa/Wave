/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveDeliverLightPulseWorker.h"
#include "Framework/Core/WaveFrameworkMessages.h"

namespace WaveNs
{

WaveDeliverLightPulseWorker::WaveDeliverLightPulseWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
    addOperationMap (WAVE_OBJECT_MANAGER_DELIVER_WAVE_LIGHT_PULSE_MESSAGE, reinterpret_cast<WaveMessageHandler> (&WaveDeliverLightPulseWorker::deliverLightPulseHandler));
}

WaveDeliverLightPulseWorker::~WaveDeliverLightPulseWorker ()
{
}

void WaveDeliverLightPulseWorker::deliverLightPulseHandler (WaveDeliverLightPulseMessage *pWaveDeliverLightPulseMessage)
{
    trace (TRACE_LEVEL_DEVEL, "WaveDeliverLightPulseWorker::deliverLightPulseHandler : Entering ...");

    waveAssert (NULL != pWaveDeliverLightPulseMessage, __FILE__, __LINE__);

    const LightPulse *pLightPulse = pWaveDeliverLightPulseMessage->getPLightPulse ();

    reply (pWaveDeliverLightPulseMessage);

    waveAssert (NULL != pLightPulse, __FILE__, __LINE__);

    deliverWaveLightPulse (pLightPulse);
}

}
