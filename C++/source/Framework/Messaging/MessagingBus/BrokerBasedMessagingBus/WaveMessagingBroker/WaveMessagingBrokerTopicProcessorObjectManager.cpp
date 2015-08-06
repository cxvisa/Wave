/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveMessagingBroker/WaveMessagingBrokerTopicProcessorObjectManager.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveMessagingBroker/WaveMessagingBrokerTopicProcessorPublishWorker.h"

namespace WaveNs
{

map<string, WaveServiceId> WaveMessagingBrokerTopicProcessorObjectManager::m_topicNameToWaveServiceIdMap;
WaveMutex                  WaveMessagingBrokerTopicProcessorObjectManager::m_topicNameToWaveServiceIdMapMutex;

WaveMessagingBrokerTopicProcessorObjectManager::WaveMessagingBrokerTopicProcessorObjectManager (const string &topicName)
    : WaveLocalObjectManager                            ((getServiceNamePrefix ()) + topicName),
      m_topicName                                       (topicName),
      m_pWaveMessagingBrokerTopicProcessorPublishWorker (NULL)
{
    m_topicNameToWaveServiceIdMapMutex.lock ();

    map<string, WaveServiceId>::const_iterator element    = m_topicNameToWaveServiceIdMap.find (topicName);
    map<string, WaveServiceId>::const_iterator endElement = m_topicNameToWaveServiceIdMap.end  ();

    if (endElement == element)
    {
        m_topicNameToWaveServiceIdMap[topicName] = getServiceId ();
    }
    else
    {
        prismAssert (false, __FILE__, __LINE__);
    }

    m_topicNameToWaveServiceIdMapMutex.unlock ();

    m_pWaveMessagingBrokerTopicProcessorPublishWorker = new WaveMessagingBrokerTopicProcessorPublishWorker (this);

    bootStrapSelf ();
}

WaveMessagingBrokerTopicProcessorObjectManager::~WaveMessagingBrokerTopicProcessorObjectManager ()
{
    m_topicNameToWaveServiceIdMapMutex.lock ();

    map<string, WaveServiceId>::iterator element    = m_topicNameToWaveServiceIdMap.find (m_topicName);
    map<string, WaveServiceId>::iterator endElement = m_topicNameToWaveServiceIdMap.end  ();

    if (endElement != element)
    {
        m_topicNameToWaveServiceIdMap.erase (element);
    }
    else
    {
        prismAssert (false, __FILE__, __LINE__);
    }

    m_topicNameToWaveServiceIdMapMutex.unlock ();
}

WaveMessagingBrokerTopicProcessorObjectManager *WaveMessagingBrokerTopicProcessorObjectManager::createInstance (const string &topicName)
{
    WaveMessagingBrokerTopicProcessorObjectManager *pWaveMessagingBrokerTopicProcessorObjectManager = new WaveMessagingBrokerTopicProcessorObjectManager (topicName);

    WaveNs::prismAssert (NULL != pWaveMessagingBrokerTopicProcessorObjectManager, __FILE__, __LINE__);

    return (pWaveMessagingBrokerTopicProcessorObjectManager);
}

string WaveMessagingBrokerTopicProcessorObjectManager::getServiceNamePrefix ()
{
    return ("Wave Messaging Broker Topic Processor - ");
}

string WaveMessagingBrokerTopicProcessorObjectManager::getTopicName () const
{
    return (m_topicName);
}

WaveServiceId WaveMessagingBrokerTopicProcessorObjectManager::getWaveServiceIdByTopicName (const string &topicName)
{
    WaveServiceId prismServiceId = 0;

    m_topicNameToWaveServiceIdMapMutex.lock ();

    map<string, WaveServiceId>::const_iterator element    = m_topicNameToWaveServiceIdMap.find (topicName);
    map<string, WaveServiceId>::const_iterator endElement = m_topicNameToWaveServiceIdMap.end  ();

    if (endElement != element)
    {
        prismServiceId = element->second;
    }

    m_topicNameToWaveServiceIdMapMutex.unlock ();

    return (prismServiceId);
}

}
