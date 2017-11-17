/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "NetworkMapper/Local/NetworkMapperLocalObjectManager.h"
#include "NetworkMapper/Local/BootCompletion/NetworkMapperLocalBootCompletionWorker.h"

namespace IsleNs
{

NetworkMapperLocalObjectManager::NetworkMapperLocalObjectManager ()
    : WaveLocalObjectManager (getServiceName ())
{
    m_pNetworkMapperLocalBootCompletionWorker = new NetworkMapperLocalBootCompletionWorker (this);

    waveAssert (NULL != m_pNetworkMapperLocalBootCompletionWorker, __FILE__, __LINE__);
}

NetworkMapperLocalObjectManager::~NetworkMapperLocalObjectManager ()
{
    if (NULL != m_pNetworkMapperLocalBootCompletionWorker)
    {
        delete m_pNetworkMapperLocalBootCompletionWorker;
    }
}

string NetworkMapperLocalObjectManager::getServiceName ()
{
    return ("Network Mapper Local");
}

NetworkMapperLocalObjectManager *NetworkMapperLocalObjectManager::getInstance ()
{
    return (new NetworkMapperLocalObjectManager ());
}

}
