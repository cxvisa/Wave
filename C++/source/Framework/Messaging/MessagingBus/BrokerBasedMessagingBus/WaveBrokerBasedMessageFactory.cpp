/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveBrokerBasedMessageFactory.h"
#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveBrokerBasedMessage.h"
#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveBrokerPublishMessage.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveBrokerPublishMessageFactory.h"

namespace WaveNs
{

map<WaveBrokerBasedMessageType, WaveBrokerBasedMessageInstantiator> WaveBrokerBasedMessageFactory::m_waveBrokerBasedMessageInstatiators;
WaveMutex                                                          WaveBrokerBasedMessageFactory::m_waveBrokerBasedMessageInstatiatorsMutex;

WaveBrokerBasedMessageFactory::WaveBrokerBasedMessageFactory ()
{
}

WaveBrokerBasedMessageFactory::~WaveBrokerBasedMessageFactory ()
{
}

void WaveBrokerBasedMessageFactory::registerWaveBrokerBasedMessageInstantiator (WaveBrokerBasedMessageType waveBrokerBasedMessageType, WaveBrokerBasedMessageInstantiator waveBrokerBasedMessageInstantiator)
{
    m_waveBrokerBasedMessageInstatiatorsMutex.lock ();

    map<WaveBrokerBasedMessageType, WaveBrokerBasedMessageInstantiator>::iterator element    = m_waveBrokerBasedMessageInstatiators.find (waveBrokerBasedMessageType);
    map<WaveBrokerBasedMessageType, WaveBrokerBasedMessageInstantiator>::iterator endElement = m_waveBrokerBasedMessageInstatiators.end  ();

    if (endElement == element)
    {
        m_waveBrokerBasedMessageInstatiators[waveBrokerBasedMessageType] = waveBrokerBasedMessageInstantiator;
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, "WaveBrokerBasedMessageFactory::registerWaveBrokerBasedMessageInstantiator : Duplicate Instantiator Registration for " + FrameworkToolKit::localize (waveBrokerBasedMessageType));
        waveAssert (false, __FILE__, __LINE__);
    }

    m_waveBrokerBasedMessageInstatiatorsMutex.unlock ();
}

WaveBrokerBasedMessage *WaveBrokerBasedMessageFactory::createWaveBrokerBasedMessageInstance (WaveBrokerBasedMessageType waveBrokerBasedMessageType, const string &topicName)
{
    WaveBrokerBasedMessage *pWaveBrokerBasedMessage = NULL;

    m_waveBrokerBasedMessageInstatiatorsMutex.lock ();

    if (WAVE_BROKER_BASED_MESSAGING_BUS_MESSAGE_TYPE_PUBLISH != waveBrokerBasedMessageType)
    {
        map<WaveBrokerBasedMessageType, WaveBrokerBasedMessageInstantiator>::iterator element    = m_waveBrokerBasedMessageInstatiators.find (waveBrokerBasedMessageType);
        map<WaveBrokerBasedMessageType, WaveBrokerBasedMessageInstantiator>::iterator endElement = m_waveBrokerBasedMessageInstatiators.end  ();

        if (endElement != element)
        {
            WaveBrokerBasedMessageInstantiator waveBrokerBasedMessageInstantiator = m_waveBrokerBasedMessageInstatiators[waveBrokerBasedMessageType];

            pWaveBrokerBasedMessage = (*waveBrokerBasedMessageInstantiator) ();

            waveAssert (NULL != pWaveBrokerBasedMessage, __FILE__, __LINE__);
        }
    }
    else
    {
        pWaveBrokerBasedMessage = (WaveBrokerPublishMessageFactory::createWaveBrokerPublishMessageInstance (topicName));
    }

    m_waveBrokerBasedMessageInstatiatorsMutex.unlock ();

    return (pWaveBrokerBasedMessage);
}

}
