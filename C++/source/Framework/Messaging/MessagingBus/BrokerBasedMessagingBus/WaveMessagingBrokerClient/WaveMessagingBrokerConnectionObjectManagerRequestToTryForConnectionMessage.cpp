/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveMessagingBrokerClient/WaveMessagingBrokerConnectionObjectManagerRequestToTryForConnectionMessage.h"
#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveMessagingBrokerClient/WaveMessagingBrokerConnectionObjectManagerTypes.h"
#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveMessagingBrokerClient/WaveMessagingBrokerConnectionObjectManager.h"

namespace WaveNs
{

WaveMessagingBrokerConnectionObjectManagerRequestToTryForConnectionMessage::WaveMessagingBrokerConnectionObjectManagerRequestToTryForConnectionMessage (const vector<string> &brokerNames)
    : PrismMessage  (WaveMessagingBrokerConnectionObjectManager::getWaveServiceId (), WAVE_MESSAGING_BROKER_CONNECTION_OBJECT_MANAGER_REQUEST_TO_TRY_FOR_CONNECTION),
      m_brokerNames (brokerNames)
{
}

WaveMessagingBrokerConnectionObjectManagerRequestToTryForConnectionMessage::WaveMessagingBrokerConnectionObjectManagerRequestToTryForConnectionMessage (const string &brokerName)
    : PrismMessage  (WaveMessagingBrokerConnectionObjectManager::getWaveServiceId (), WAVE_MESSAGING_BROKER_CONNECTION_OBJECT_MANAGER_REQUEST_TO_TRY_FOR_CONNECTION)
{
    m_brokerNames.push_back (brokerName);
}

WaveMessagingBrokerConnectionObjectManagerRequestToTryForConnectionMessage::~WaveMessagingBrokerConnectionObjectManagerRequestToTryForConnectionMessage ()
{
}

vector<string> WaveMessagingBrokerConnectionObjectManagerRequestToTryForConnectionMessage::getBrokerNames () const
{
    return (m_brokerNames);
}

void WaveMessagingBrokerConnectionObjectManagerRequestToTryForConnectionMessage::setBrokerNames (const vector<string> &brokerNames)
{
    m_brokerNames = brokerNames;
}

void WaveMessagingBrokerConnectionObjectManagerRequestToTryForConnectionMessage::addBrokerNames (const vector<string> &brokerNames)
{
    m_brokerNames.insert (m_brokerNames.end (), brokerNames.begin (), brokerNames.end ());
}

void WaveMessagingBrokerConnectionObjectManagerRequestToTryForConnectionMessage::addBrokerName (const string &brokerName)
{
    m_brokerNames.push_back (brokerName);
}

}
