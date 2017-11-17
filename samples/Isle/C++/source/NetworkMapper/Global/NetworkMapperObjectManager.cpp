/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "NetworkMapper/Global/NetworkMapperObjectManager.h"

namespace IsleNs
{

NetworkMapperObjectManager::NetworkMapperObjectManager ()
    : WaveObjectManager (getServiceName ())
{
}

NetworkMapperObjectManager::~NetworkMapperObjectManager ()
{
}

string NetworkMapperObjectManager::getServiceName ()
{
    return ("Network Mapper");
}

NetworkMapperObjectManager *NetworkMapperObjectManager::getInstance ()
{
    return (new NetworkMapperObjectManager ());
}

}
