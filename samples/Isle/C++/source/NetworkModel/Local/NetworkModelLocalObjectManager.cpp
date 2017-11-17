/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "NetworkModel/Local/NetworkModelLocalObjectManager.h"
#include "NetworkModel/Local/BootCompletion/NetworkModelLocalBootCompletionWorker.h"

namespace IsleNs
{

NetworkModelLocalObjectManager::NetworkModelLocalObjectManager ()
    : WaveLocalObjectManager (getServiceName ())
{
    m_pNetworkModelLocalBootCompletionWorker = new NetworkModelLocalBootCompletionWorker (this);

    waveAssert (NULL != m_pNetworkModelLocalBootCompletionWorker, __FILE__, __LINE__);
}

NetworkModelLocalObjectManager::~NetworkModelLocalObjectManager ()
{
    if (NULL != m_pNetworkModelLocalBootCompletionWorker)
    {
        delete m_pNetworkModelLocalBootCompletionWorker;
    }
}

string NetworkModelLocalObjectManager::getServiceName ()
{
    return ("Network Model Local");
}

NetworkModelLocalObjectManager *NetworkModelLocalObjectManager::getInstance ()
{
    static NetworkModelLocalObjectManager *pNetworkModelLocalObjectManager = new NetworkModelLocalObjectManager ();

    WaveNs::waveAssert (NULL != pNetworkModelLocalObjectManager, __FILE__, __LINE__);

    return (pNetworkModelLocalObjectManager);
}

}
