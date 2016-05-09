/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/LightHouse/LightPulseDispatchObjectManager.h"
#include "Framework/Messaging/LightHouse/LightPulseDispatchWorker.h"

namespace WaveNs
{

LightPulseDispatchObjectManager::LightPulseDispatchObjectManager ()
    : WaveLocalObjectManager (getServiceName ())
{
    m_pLightPulseDispatchWorker = new LightPulseDispatchWorker (this);

    waveAssert (NULL != m_pLightPulseDispatchWorker, __FILE__, __LINE__);
}

LightPulseDispatchObjectManager::~LightPulseDispatchObjectManager ()
{
    if (NULL != m_pLightPulseDispatchWorker)
    {
        delete m_pLightPulseDispatchWorker;
    }
}

string LightPulseDispatchObjectManager::getServiceName ()
{
    return ("Light Pulse Receiver Dispatch");
}

LightPulseDispatchObjectManager *LightPulseDispatchObjectManager::getInstance ()
{
    static LightPulseDispatchObjectManager *pLightPulseDispatchObjectManager = new LightPulseDispatchObjectManager ();

    WaveNs::waveAssert (NULL != pLightPulseDispatchObjectManager, __FILE__, __LINE__);

    return (pLightPulseDispatchObjectManager);
}

WaveServiceId LightPulseDispatchObjectManager::getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

}
