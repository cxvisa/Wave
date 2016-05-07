/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/LightHouse/LightHouseTransportObjectManager.h"
#include "Framework/Messaging/LightHouse/LightHouseTransportBroadcastLightPulseWorker.h"

namespace WaveNs
{

LightHouseTransportObjectManager::LightHouseTransportObjectManager ()
    : WaveLocalObjectManager (getServiceName ())
{
    m_pLightHouseTransportBroadcastLightPulseWorker = new LightHouseTransportBroadcastLightPulseWorker (this);

    waveAssert (NULL != m_pLightHouseTransportBroadcastLightPulseWorker, __FILE__, __LINE__);
}

LightHouseTransportObjectManager::~LightHouseTransportObjectManager ()
{
    if (NULL != m_pLightHouseTransportBroadcastLightPulseWorker)
    {
       delete m_pLightHouseTransportBroadcastLightPulseWorker;
    }
}

string LightHouseTransportObjectManager::getServiceName ()
{
    return ("Light House Transport");
}

LightHouseTransportObjectManager *LightHouseTransportObjectManager::getInstance ()
{
    static LightHouseTransportObjectManager *pLightHouseTransportObjectManager = new LightHouseTransportObjectManager ();

    WaveNs::waveAssert (NULL != pLightHouseTransportObjectManager, __FILE__, __LINE__);

    return (pLightHouseTransportObjectManager);
}

WaveServiceId LightHouseTransportObjectManager::getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

}
