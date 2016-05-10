/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/LightHouse/LightPulseDispatchObjectManager.h"
#include "Framework/Messaging/LightHouse/LightPulseDispatchWorker.h"
#include "Framework/Messaging/LightHouse/LightPulseRegistrationWorker.h"
#include "Framework/Messaging/LightHouse/LightPulseUnregistrationWorker.h"

namespace WaveNs
{

LightPulseDispatchObjectManager::LightPulseDispatchObjectManager ()
    : WaveLocalObjectManager (getServiceName ())
{
    m_pLightPulseDispatchWorker = new LightPulseDispatchWorker (this);

    waveAssert (NULL != m_pLightPulseDispatchWorker, __FILE__, __LINE__);

    m_pLightPulseRegistrationWorker = new LightPulseRegistrationWorker (this);

    waveAssert (NULL != m_pLightPulseRegistrationWorker, __FILE__, __LINE__);

    m_pLightPulseUnregistrationWorker = new LightPulseUnregistrationWorker (this);

    waveAssert (NULL != m_pLightPulseUnregistrationWorker, __FILE__, __LINE__);
}

LightPulseDispatchObjectManager::~LightPulseDispatchObjectManager ()
{
    if (NULL != m_pLightPulseDispatchWorker)
    {
        delete m_pLightPulseDispatchWorker;
    }

    if (NULL != m_pLightPulseRegistrationWorker)
    {
        delete m_pLightPulseRegistrationWorker;
    }

    if (NULL != m_pLightPulseUnregistrationWorker)
    {
        delete m_pLightPulseUnregistrationWorker;
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
