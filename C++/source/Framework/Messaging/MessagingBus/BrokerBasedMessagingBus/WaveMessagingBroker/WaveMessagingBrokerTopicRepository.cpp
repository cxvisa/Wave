/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveMessagingBroker/WaveMessagingBrokerTopicRepository.h"
#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveMessagingBroker/WaveMessagingBrokerTopic.h"
#include "Framework/Utils/AssertUtils.h"

namespace WaveNs
{

WaveMessagingBrokerTopicRepository::WaveMessagingBrokerTopicRepository ()
{
}

WaveMessagingBrokerTopicRepository::~WaveMessagingBrokerTopicRepository ()
{
}

bool WaveMessagingBrokerTopicRepository::isAKnownWaveMessagingBrokerTopic (const string &waveMessagingBrokerTopicName)
{
    bool isKnown = false;

    m_waveMesasgingBrokerTopicsMutex.lock ();

    map<string, WaveMessagingBrokerTopic *>::const_iterator element    = m_waveMesasgingBrokerTopics.find (waveMessagingBrokerTopicName);
    map<string, WaveMessagingBrokerTopic *>::const_iterator endElement = m_waveMesasgingBrokerTopics.end  ();

    if (element != endElement)
    {
        isKnown = true;
    }
    else
    {
        isKnown = false;
    }

    m_waveMesasgingBrokerTopicsMutex.unlock ();

    return (isKnown);
}

void WaveMessagingBrokerTopicRepository::addWaveMessagingBrokerTopic (const string &waveMessagingBrokerTopicName, const string &clientUniqueString)
{
    m_waveMesasgingBrokerTopicsMutex.lock ();

    map<string, WaveMessagingBrokerTopic *>::iterator element    = m_waveMesasgingBrokerTopics.find (waveMessagingBrokerTopicName);
    map<string, WaveMessagingBrokerTopic *>::iterator endElement = m_waveMesasgingBrokerTopics.end  ();

    if (element != endElement)
    {
        prismAssert (false, __FILE__, __LINE__);
    }
    else
    {
        WaveMessagingBrokerTopic *pWaveMessagingBrokerTopic = new WaveMessagingBrokerTopic (waveMessagingBrokerTopicName);

        prismAssert (NULL != pWaveMessagingBrokerTopic, __FILE__, __LINE__);

        m_waveMesasgingBrokerTopics[waveMessagingBrokerTopicName] = pWaveMessagingBrokerTopic;

        pWaveMessagingBrokerTopic->addSubscription (clientUniqueString);
    }

    m_waveMesasgingBrokerTopicsMutex.unlock ();
}

void WaveMessagingBrokerTopicRepository::addWaveMessagingBrokerTopicIfNotKnown (const string &waveMessagingBrokerTopicName, const string &clientUniqueString)
{
    WaveMessagingBrokerTopic *pWaveMessagingBrokerTopic = NULL;

    m_waveMesasgingBrokerTopicsMutex.lock ();

    map<string, WaveMessagingBrokerTopic *>::iterator element    = m_waveMesasgingBrokerTopics.find (waveMessagingBrokerTopicName);
    map<string, WaveMessagingBrokerTopic *>::iterator endElement = m_waveMesasgingBrokerTopics.end  ();

    if (element != endElement)
    {
        pWaveMessagingBrokerTopic = element->second;
    }
    else
    {
        pWaveMessagingBrokerTopic = new WaveMessagingBrokerTopic (waveMessagingBrokerTopicName);

        prismAssert (NULL != pWaveMessagingBrokerTopic, __FILE__, __LINE__);

        m_waveMesasgingBrokerTopics[waveMessagingBrokerTopicName] = pWaveMessagingBrokerTopic;
    }

    prismAssert (NULL != pWaveMessagingBrokerTopic, __FILE__, __LINE__);

    pWaveMessagingBrokerTopic->addSubscription (clientUniqueString);

    m_waveMesasgingBrokerTopicsMutex.unlock ();
}

void WaveMessagingBrokerTopicRepository::removeWaveMessagingBrokerTopic (const string &waveMessagingBrokerTopicName, const string &clientUniqueString)
{
    m_waveMesasgingBrokerTopicsMutex.lock ();

    map<string, WaveMessagingBrokerTopic *>::iterator element    = m_waveMesasgingBrokerTopics.find (waveMessagingBrokerTopicName);
    map<string, WaveMessagingBrokerTopic *>::iterator endElement = m_waveMesasgingBrokerTopics.end  ();

    if (element != endElement)
    {
        WaveMessagingBrokerTopic *pWaveMessagingBrokerTopic = element->second;

        prismAssert (NULL != pWaveMessagingBrokerTopic, __FILE__, __LINE__);

        pWaveMessagingBrokerTopic->removeSubscription (clientUniqueString);

        if (0 == (pWaveMessagingBrokerTopic->getNumberOfSubscribedClients ()))
        {
            m_waveMesasgingBrokerTopics.erase (element);

            delete pWaveMessagingBrokerTopic;
        }
    }
    else
    {
        prismAssert (false, __FILE__, __LINE__);
    }

    m_waveMesasgingBrokerTopicsMutex.unlock ();
}

void WaveMessagingBrokerTopicRepository::removeWaveMessagingBrokerTopicIfKnown (const string &waveMessagingBrokerTopicName, const string &clientUniqueString)
{
    m_waveMesasgingBrokerTopicsMutex.lock ();

    map<string, WaveMessagingBrokerTopic *>::iterator element    = m_waveMesasgingBrokerTopics.find (waveMessagingBrokerTopicName);
    map<string, WaveMessagingBrokerTopic *>::iterator endElement = m_waveMesasgingBrokerTopics.end  ();

    if (element != endElement)
    {
        WaveMessagingBrokerTopic *pWaveMessagingBrokerTopic = element->second;

        prismAssert (NULL != pWaveMessagingBrokerTopic, __FILE__, __LINE__);

        pWaveMessagingBrokerTopic->removeSubscription (clientUniqueString);

        if (0 == (pWaveMessagingBrokerTopic->getNumberOfSubscribedClients ()))
        {
            m_waveMesasgingBrokerTopics.erase (element);

            delete pWaveMessagingBrokerTopic;
        }
    }
    else
    {
        // Nothing to do
    }

    m_waveMesasgingBrokerTopicsMutex.unlock ();
}

void WaveMessagingBrokerTopicRepository::getCurrentlySubscribedClientsForTopic (const string &waveMessagingBrokerTopicName, vector<string> &currentlySubscribedClients)
{
    currentlySubscribedClients.clear ();

    m_waveMesasgingBrokerTopicsMutex.lock ();

    map<string, WaveMessagingBrokerTopic *>::iterator element    = m_waveMesasgingBrokerTopics.find (waveMessagingBrokerTopicName);
    map<string, WaveMessagingBrokerTopic *>::iterator endElement = m_waveMesasgingBrokerTopics.end  ();

    if (element != endElement)
    {
        WaveMessagingBrokerTopic *pWaveMessagingBrokerTopic = element->second;

        prismAssert (NULL != pWaveMessagingBrokerTopic, __FILE__, __LINE__);

        pWaveMessagingBrokerTopic->getSubscribedClients (currentlySubscribedClients);
    }
    else
    {
        // Nothing to do
    }

    m_waveMesasgingBrokerTopicsMutex.unlock ();
}

WaveMessagingBrokerTopicRepository *WaveMessagingBrokerTopicRepository::getInstance ()
{
    static PrismMutex                          waveMessagingBrokerTopicRepositoryMutex;
    static WaveMessagingBrokerTopicRepository *pWaveMessagingBrokerTopicRepository      = NULL;

    waveMessagingBrokerTopicRepositoryMutex.lock ();

    if (NULL == pWaveMessagingBrokerTopicRepository)
    {
        pWaveMessagingBrokerTopicRepository = new WaveMessagingBrokerTopicRepository ();

        prismAssert (NULL != pWaveMessagingBrokerTopicRepository, __FILE__, __LINE__);
    }

    waveMessagingBrokerTopicRepositoryMutex.unlock ();

    return (pWaveMessagingBrokerTopicRepository);
}

}
