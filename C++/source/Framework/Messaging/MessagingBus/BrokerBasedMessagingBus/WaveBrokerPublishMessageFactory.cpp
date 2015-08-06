/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveBrokerPublishMessageFactory.h"
#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveBrokerPublishMessage.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"

namespace WaveNs
{

map<string, WaveBrokerPublishMessageInstantiator> WaveBrokerPublishMessageFactory::m_waveBrokerPublishMessageInstatiators;
WaveMutex                                        WaveBrokerPublishMessageFactory::m_waveBrokerPublishMessageInstatiatorsMutex;

WaveBrokerPublishMessageFactory::WaveBrokerPublishMessageFactory ()
{
}

WaveBrokerPublishMessageFactory::~WaveBrokerPublishMessageFactory ()
{
}

void WaveBrokerPublishMessageFactory::registerWaveBrokerPublishMessageInstantiator (const string &topicName, WaveBrokerPublishMessageInstantiator waveBrokerPublishMessageInstantiator)
{
    m_waveBrokerPublishMessageInstatiatorsMutex.lock ();

    map<string, WaveBrokerPublishMessageInstantiator>::iterator element    = m_waveBrokerPublishMessageInstatiators.find (topicName);
    map<string, WaveBrokerPublishMessageInstantiator>::iterator endElement = m_waveBrokerPublishMessageInstatiators.end  ();

    if (endElement == element)
    {
        m_waveBrokerPublishMessageInstatiators[topicName] = waveBrokerPublishMessageInstantiator;
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, "WaveBrokerPublishMessageFactory::registerWaveBrokerPublishMessageInstantiator : Duplicate Instantiator Registration for " + topicName);
        prismAssert (false, __FILE__, __LINE__);
    }

    m_waveBrokerPublishMessageInstatiatorsMutex.unlock ();
}

WaveBrokerPublishMessage *WaveBrokerPublishMessageFactory::createWaveBrokerPublishMessageInstance (const string &topicName)
{
    WaveBrokerPublishMessage *pWaveBrokerPublishMessage = NULL;

    m_waveBrokerPublishMessageInstatiatorsMutex.lock ();

    map<string, WaveBrokerPublishMessageInstantiator>::iterator element    = m_waveBrokerPublishMessageInstatiators.find (topicName);
    map<string, WaveBrokerPublishMessageInstantiator>::iterator endElement = m_waveBrokerPublishMessageInstatiators.end  ();

    if (endElement != element)
    {
        WaveBrokerPublishMessageInstantiator waveBrokerPublishMessageInstantiator = m_waveBrokerPublishMessageInstatiators[topicName];

        pWaveBrokerPublishMessage = (*waveBrokerPublishMessageInstantiator) ();

        prismAssert (NULL != pWaveBrokerPublishMessage, __FILE__, __LINE__);
    }

    m_waveBrokerPublishMessageInstatiatorsMutex.unlock ();

    return (pWaveBrokerPublishMessage);
}

}
