/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include <Framework/Utils/AssertUtils.h>
#include <NetworkModel/Global/Bridge/BridgeWorker.h>
#include <NetworkModel/Global/Hypervisor/HypervisorWorker.h>
#include <NetworkModel/Global/Interface/InterfaceWorker.h>
#include <NetworkModel/Global/NetworkModelObjectManager.h>
#include "HttpInterface/HttpInterfaceReceiverObjectManager.h"

namespace IsleNs
{

NetworkModelObjectManager::NetworkModelObjectManager ()
    : WaveObjectManager (getServiceName ())
{
    m_pHypervisorWorker = new HypervisorWorker (this);

    waveAssert (NULL != m_pHypervisorWorker, __FILE__, __LINE__);

    m_pBridgeWorker = new BridgeWorker (this);

    waveAssert (NULL != m_pBridgeWorker, __FILE__, __LINE__);

    m_pInterfaceWorker = new InterfaceWorker (this);

    waveAssert (NULL != m_pInterfaceWorker, __FILE__, __LINE__);
}

NetworkModelObjectManager::~NetworkModelObjectManager ()
{
    if (NULL != m_pHypervisorWorker)
    {
        delete m_pHypervisorWorker;
    }

    if (NULL != m_pBridgeWorker)
    {
        delete m_pBridgeWorker;
    }

    if (NULL != m_pInterfaceWorker)
    {
        delete m_pInterfaceWorker;
    }
}

string NetworkModelObjectManager::getServiceName ()
{
    return ("Network Model");
}

NetworkModelObjectManager *NetworkModelObjectManager::getInstance ()
{
    static NetworkModelObjectManager *pNetworkModelObjectManager = new NetworkModelObjectManager ();

    WaveNs::waveAssert (NULL != pNetworkModelObjectManager, __FILE__ ,__LINE__);

    return (pNetworkModelObjectManager);
}

}
