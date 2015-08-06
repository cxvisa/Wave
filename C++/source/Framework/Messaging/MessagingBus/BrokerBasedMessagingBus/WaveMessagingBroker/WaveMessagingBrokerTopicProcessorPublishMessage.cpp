/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveMessagingBroker/WaveMessagingBrokerTopicProcessorPublishMessage.h"
#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveMessagingBroker/WaveMessagingBrokerTopicProcessorObjectManagerTypes.h"
#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveBrokerBasedMessagePayload.h"

namespace WaveNs
{

WaveMessagingBrokerTopicProcessorPublishMessage::WaveMessagingBrokerTopicProcessorPublishMessage (const WaveServiceId &prismServiceId)
    : WaveMessage                     (prismServiceId, WAVE_MESSAGING_BROKER_TOPIC_PROCESSOR_PUBLISH),
      m_pWaveBrokerBasedMessagePayload (NULL)
{
}

WaveMessagingBrokerTopicProcessorPublishMessage::~WaveMessagingBrokerTopicProcessorPublishMessage()
{
    if (NULL != m_pWaveBrokerBasedMessagePayload)
    {
        delete m_pWaveBrokerBasedMessagePayload;
    }
}

WaveBrokerBasedMessagePayload *WaveMessagingBrokerTopicProcessorPublishMessage::getPWaveBrokerBasedMessagePayload ()
{
    return (m_pWaveBrokerBasedMessagePayload);
}

void WaveMessagingBrokerTopicProcessorPublishMessage::setPWaveBrokerBasedMessagePayload (WaveBrokerBasedMessagePayload *pWaveBrokerBasedMessagePayload)
{
    m_pWaveBrokerBasedMessagePayload = pWaveBrokerBasedMessagePayload;
}

string &WaveMessagingBrokerTopicProcessorPublishMessage::getUniqueStringForPublisher ()
{
    return (m_uniqueStringForPublisher);
}

}
