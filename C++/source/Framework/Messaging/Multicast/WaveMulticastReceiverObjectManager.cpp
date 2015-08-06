/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/Multicast/WaveMulticastReceiverObjectManager.h"
#include "Framework/Utils/AssertUtils.h"

namespace WaveNs
{

WaveMulticastReceiverObjectManager::WaveMulticastReceiverObjectManager ()
    : WaveLocalObjectManagerForUserSpecificTasks (getServiceName ())
{
}

WaveMulticastReceiverObjectManager::~WaveMulticastReceiverObjectManager ()
{
}

WaveMulticastReceiverObjectManager *WaveMulticastReceiverObjectManager::getInstance ()
{
    static WaveMulticastReceiverObjectManager *pWaveMessagingBrokerReceiverObjectManager = new WaveMulticastReceiverObjectManager ();

    WaveNs::prismAssert (NULL != pWaveMessagingBrokerReceiverObjectManager, __FILE__, __LINE__);

    return (pWaveMessagingBrokerReceiverObjectManager);
}

WaveServiceId WaveMulticastReceiverObjectManager::getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

string WaveMulticastReceiverObjectManager::getServiceName ()
{
    return ("Wave Multicast Receiver");
}

}
