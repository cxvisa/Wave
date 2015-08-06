/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveMessagingBroker/WaveMessagingBrokerClientRepository.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveMessagingBroker/WaveMessagingBrokerClient.h"

namespace WaveNs
{

WaveMessagingBrokerClientRepository::WaveMessagingBrokerClientRepository ()
{
}

WaveMessagingBrokerClientRepository::~WaveMessagingBrokerClientRepository ()
{
}

string WaveMessagingBrokerClientRepository::getWaveMessagingBrokerClientUniqueString (const string &ipAddress, const SI32 &port)
{
    return ( ipAddress + string (":") + port);
}

bool WaveMessagingBrokerClientRepository::isAKnownWaveMessagingBrokerClient (const string &ipAddress, const SI32 &port)
{
    const string waveMessagingBrokerClientUniqueString = getWaveMessagingBrokerClientUniqueString (ipAddress, port);
          bool   isKnown                               = false;

    m_waveMessagingBrokerClientsMutex.lock ();

    map<string, WaveMessagingBrokerClient *>::const_iterator element    = m_waveMessagingBrokerClientsMap.find (waveMessagingBrokerClientUniqueString);
    map<string, WaveMessagingBrokerClient *>::const_iterator endElement = m_waveMessagingBrokerClientsMap.end  ();

    if (endElement == element)
    {
        isKnown = false;
    }
    else
    {
        isKnown = true;
    }

    m_waveMessagingBrokerClientsMutex.unlock ();

    return (isKnown);
}

void WaveMessagingBrokerClientRepository::addWaveMessagingBrokerClient (const string &name, const string &ipAddress, const SI32 &port)
{
    const string waveMessagingBrokerClientUniqueString = getWaveMessagingBrokerClientUniqueString (ipAddress, port);

    m_waveMessagingBrokerClientsMutex.lock ();

    map<string, WaveMessagingBrokerClient *>::iterator element    = m_waveMessagingBrokerClientsMap.find (waveMessagingBrokerClientUniqueString);
    map<string, WaveMessagingBrokerClient *>::iterator endElement = m_waveMessagingBrokerClientsMap.end  ();

    if (endElement == element)
    {
        m_waveMessagingBrokerClientsMap[waveMessagingBrokerClientUniqueString] = new WaveMessagingBrokerClient (name, ipAddress, port);
    }
    else
    {
        waveAssert (false, __FILE__, __LINE__);
    }

    m_waveMessagingBrokerClientsMutex.unlock ();
}

bool WaveMessagingBrokerClientRepository::addWaveMessagingBrokerClientIfNotKnown (const string &name, const string &ipAddress, const SI32 &port)
{
    const string waveMessagingBrokerClientUniqueString = getWaveMessagingBrokerClientUniqueString (ipAddress, port);
           bool  isAlreadyKnown                        = false;

    m_waveMessagingBrokerClientsMutex.lock ();

    map<string, WaveMessagingBrokerClient *>::iterator element    = m_waveMessagingBrokerClientsMap.find (waveMessagingBrokerClientUniqueString);
    map<string, WaveMessagingBrokerClient *>::iterator endElement = m_waveMessagingBrokerClientsMap.end  ();

    if (endElement == element)
    {
        isAlreadyKnown = false;
        m_waveMessagingBrokerClientsMap[waveMessagingBrokerClientUniqueString] = new WaveMessagingBrokerClient (name, ipAddress, port);
    }
    else
    {
        isAlreadyKnown = true;
    }

    m_waveMessagingBrokerClientsMutex.unlock ();

    return (!(isAlreadyKnown));
}

void WaveMessagingBrokerClientRepository::removeWaveMessagingBrokerClient (const string &ipAddress, const SI32 &port)
{
    const string waveMessagingBrokerClientUniqueString = getWaveMessagingBrokerClientUniqueString (ipAddress, port);

    m_waveMessagingBrokerClientsMutex.lock ();

    map<string, WaveMessagingBrokerClient *>::iterator element    = m_waveMessagingBrokerClientsMap.find (waveMessagingBrokerClientUniqueString);
    map<string, WaveMessagingBrokerClient *>::iterator endElement = m_waveMessagingBrokerClientsMap.end  ();

    if (endElement == element)
    {
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        WaveMessagingBrokerClient *pWaveMessagingBrokerClient = element->second;

        waveAssert (NULL != pWaveMessagingBrokerClient, __FILE__, __LINE__);

        m_waveMessagingBrokerClientsMap.erase (element);

        delete pWaveMessagingBrokerClient;
    }

    m_waveMessagingBrokerClientsMutex.unlock ();
}

void WaveMessagingBrokerClientRepository::addWaveMessagingBrokerClientSubscription (const string &ipAddress, const SI32 &port, const string &subscriptionTopic)
{
    const string waveMessagingBrokerClientUniqueString = getWaveMessagingBrokerClientUniqueString (ipAddress, port);

    m_waveMessagingBrokerClientsMutex.lock ();

    map<string, WaveMessagingBrokerClient *>::iterator element    = m_waveMessagingBrokerClientsMap.find (waveMessagingBrokerClientUniqueString);
    map<string, WaveMessagingBrokerClient *>::iterator endElement = m_waveMessagingBrokerClientsMap.end  ();

    if (endElement == element)
    {
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        WaveMessagingBrokerClient *pWaveMessagingBrokerClient = element->second;

        waveAssert (NULL != pWaveMessagingBrokerClient, __FILE__, __LINE__);

        pWaveMessagingBrokerClient->addSubscriptionTopic (subscriptionTopic);
    }

    m_waveMessagingBrokerClientsMutex.unlock ();
}

void WaveMessagingBrokerClientRepository::removeWaveMessagingBrokerClientSubscription (const string &ipAddress, const SI32 &port, const string &subscriptionTopic)
{
    const string waveMessagingBrokerClientUniqueString = getWaveMessagingBrokerClientUniqueString (ipAddress, port);

    m_waveMessagingBrokerClientsMutex.lock ();

    map<string, WaveMessagingBrokerClient *>::iterator element    = m_waveMessagingBrokerClientsMap.find (waveMessagingBrokerClientUniqueString);
    map<string, WaveMessagingBrokerClient *>::iterator endElement = m_waveMessagingBrokerClientsMap.end  ();

    if (endElement == element)
    {
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        WaveMessagingBrokerClient *pWaveMessagingBrokerClient = element->second;

        waveAssert (NULL != pWaveMessagingBrokerClient, __FILE__, __LINE__);

        pWaveMessagingBrokerClient->removeSubscriptionTopic (subscriptionTopic);
    }

    m_waveMessagingBrokerClientsMutex.unlock ();
}

WaveMessagingBrokerClient *WaveMessagingBrokerClientRepository::checkoutWaveMessagingBrokerClient (const string &ipAddress, const SI32 &port)
{
    const string                     waveMessagingBrokerClientUniqueString = getWaveMessagingBrokerClientUniqueString (ipAddress, port);
          WaveMessagingBrokerClient *pWaveMessagingBrokerClient            = NULL;

    m_waveMessagingBrokerClientsMutex.lock ();

    map<string, WaveMessagingBrokerClient *>::iterator element    = m_waveMessagingBrokerClientsMap.find (waveMessagingBrokerClientUniqueString);
    map<string, WaveMessagingBrokerClient *>::iterator endElement = m_waveMessagingBrokerClientsMap.end  ();

    if (endElement == element)
    {
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        pWaveMessagingBrokerClient = element->second;

        waveAssert (NULL != pWaveMessagingBrokerClient, __FILE__, __LINE__);

        pWaveMessagingBrokerClient->checkout ();
    }

    m_waveMessagingBrokerClientsMutex.unlock ();

    return (pWaveMessagingBrokerClient);
}

WaveMessagingBrokerClient *WaveMessagingBrokerClientRepository::checkoutWaveMessagingBrokerClient (const string &waveMessagingBrokerClientUniqueString)
{
    WaveMessagingBrokerClient *pWaveMessagingBrokerClient = NULL;

    m_waveMessagingBrokerClientsMutex.lock ();

    map<string, WaveMessagingBrokerClient *>::iterator element    = m_waveMessagingBrokerClientsMap.find (waveMessagingBrokerClientUniqueString);
    map<string, WaveMessagingBrokerClient *>::iterator endElement = m_waveMessagingBrokerClientsMap.end  ();

    if (endElement == element)
    {
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        pWaveMessagingBrokerClient = element->second;

        waveAssert (NULL != pWaveMessagingBrokerClient, __FILE__, __LINE__);

        pWaveMessagingBrokerClient->checkout ();
    }

    m_waveMessagingBrokerClientsMutex.unlock ();

    return (pWaveMessagingBrokerClient);
}

void WaveMessagingBrokerClientRepository::checkinWaveMessagingBrokerClient (WaveMessagingBrokerClient *pWaveMessagingBrokerClient)
{
    waveAssert (NULL != pWaveMessagingBrokerClient, __FILE__, __LINE__);

    const string waveMessagingBrokerClientUniqueString = pWaveMessagingBrokerClient->getUniqueString ();

    m_waveMessagingBrokerClientsMutex.lock ();

    map<string, WaveMessagingBrokerClient *>::iterator element    = m_waveMessagingBrokerClientsMap.find (waveMessagingBrokerClientUniqueString);
    map<string, WaveMessagingBrokerClient *>::iterator endElement = m_waveMessagingBrokerClientsMap.end  ();

    if (endElement == element)
    {
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        WaveMessagingBrokerClient *pWaveMessagingBrokerClient1 = element->second;

        waveAssert (NULL != pWaveMessagingBrokerClient1, __FILE__, __LINE__);

        pWaveMessagingBrokerClient1->checkin ();
    }

    m_waveMessagingBrokerClientsMutex.unlock ();
}

WaveMessagingBrokerClientRepository *WaveMessagingBrokerClientRepository::getInstance ()
{
    static WaveMutex                           waveMessagingBrokerClientRepositoryMutex;
    static WaveMessagingBrokerClientRepository *pWaveMessagingBrokerClientRepository      = NULL;

    waveMessagingBrokerClientRepositoryMutex.lock ();

    if (NULL == pWaveMessagingBrokerClientRepository)
    {
        pWaveMessagingBrokerClientRepository = new WaveMessagingBrokerClientRepository ();
    }

    waveMessagingBrokerClientRepositoryMutex.unlock ();

    return (pWaveMessagingBrokerClientRepository);
}

void WaveMessagingBrokerClientRepository::print ()
{
    m_waveMessagingBrokerClientsMutex.lock ();

    map<string, WaveMessagingBrokerClient *>::const_iterator element         = m_waveMessagingBrokerClientsMap.begin ();
    map<string, WaveMessagingBrokerClient *>::const_iterator endElement      = m_waveMessagingBrokerClientsMap.end   ();
    UI32                                                     i               = 0;
    UI32                                                     numberOfClients = m_waveMessagingBrokerClientsMap.size ();

    tracePrintf (TRACE_LEVEL_INFO, true, false, "Total Number Of Clients = %u\n\n", numberOfClients);

    while (endElement != element)
    {
        i++;

        string                     clientUniqueString         = element->first;
        WaveMessagingBrokerClient *pWaveMessagingBrokerClient = element->second;

        waveAssert (NULL != pWaveMessagingBrokerClient, __FILE__, __LINE__);

        vector<string> subscriptions;

        pWaveMessagingBrokerClient->getAllSubscribedTopics (subscriptions);

        UI32 numberOfSubscriptions = subscriptions.size ();
        UI32 j                     = 0;

        tracePrintf (TRACE_LEVEL_INFO, false, true, "%u - %s (%u)\n", i, clientUniqueString.c_str (), numberOfSubscriptions);

        for (j = 0; j < numberOfSubscriptions; j++)
        {
            tracePrintf (TRACE_LEVEL_INFO, false, true, "    %u - %s\n", j, (subscriptions[j]).c_str ());
        }

        tracePrintf (TRACE_LEVEL_INFO, false, true, "\n");

        element++;
    }

    m_waveMessagingBrokerClientsMutex.unlock ();
}

}
