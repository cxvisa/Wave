/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveDeliverBrokerPublishMessageWorker.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveBrokerPublishMessage.h"
#include "Framework/Core/PrismFrameworkMessages.h"

namespace WaveNs
{

WaveDeliverBrokerPublishMessageWorker::WaveDeliverBrokerPublishMessageWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
    addOperationMap (WAVE_OBJECT_MANAGER_DELIVER_WAVE_BROKER_PUBLISH_MESSAGE, reinterpret_cast<WaveMessageHandler> (&WaveDeliverBrokerPublishMessageWorker::deliverBrokerPublishMessageHandler));
}

WaveDeliverBrokerPublishMessageWorker::~WaveDeliverBrokerPublishMessageWorker ()
{
}

void WaveDeliverBrokerPublishMessageWorker::deliverBrokerPublishMessageHandler (WaveDeliverBrokerPublishMessage *pWaveDeliverBrokerPublishMessage)
{
    //trace (TRACE_LEVEL_DEVEL, "WaveDeliverBrokerPublishMessageWorker::deliverBrokerPublishMessageHandler: Entering ...");

    waveAssert (NULL != pWaveDeliverBrokerPublishMessage, __FILE__, __LINE__);

    WaveBrokerPublishMessage *pWaveBrokerPublishMessage = pWaveDeliverBrokerPublishMessage->getPWaveBrokerPublishMessage ();

    reply (pWaveDeliverBrokerPublishMessage);

    waveAssert (NULL != pWaveBrokerPublishMessage, __FILE__, __LINE__);

    pWaveBrokerPublishMessage->loadFromSerializedData2 ();

    string brokerName = pWaveBrokerPublishMessage->getBrokerName ();
    string topicName  = pWaveBrokerPublishMessage->getTopicName  ();

    deliverWaveBrokerPublishedEvent (brokerName, topicName, pWaveBrokerPublishMessage);
}

}
