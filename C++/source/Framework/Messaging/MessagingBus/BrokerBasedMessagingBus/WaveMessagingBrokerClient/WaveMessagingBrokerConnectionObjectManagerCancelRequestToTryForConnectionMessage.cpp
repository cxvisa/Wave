/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveMessagingBrokerClient/WaveMessagingBrokerConnectionObjectManagerCancelRequestToTryForConnectionMessage.h"
#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveMessagingBrokerClient/WaveMessagingBrokerConnectionObjectManagerTypes.h"
#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveMessagingBrokerClient/WaveMessagingBrokerConnectionObjectManager.h"

namespace WaveNs
{

WaveMessagingBrokerConnectionObjectManagerCancelRequestToTryForConnectionMessage::WaveMessagingBrokerConnectionObjectManagerCancelRequestToTryForConnectionMessage (const vector<string> &brokerNames)
    : WaveMessage  (WaveMessagingBrokerConnectionObjectManager::getWaveServiceId (), WAVE_MESSAGING_BROKER_CONNECTION_OBJECT_MANAGER_CANCEL_REQUEST_TO_TRY_FOR_CONNECTION),
      m_brokerNames (brokerNames)
{
}

WaveMessagingBrokerConnectionObjectManagerCancelRequestToTryForConnectionMessage::WaveMessagingBrokerConnectionObjectManagerCancelRequestToTryForConnectionMessage (const string &brokerName)
    : WaveMessage  (WaveMessagingBrokerConnectionObjectManager::getWaveServiceId (), WAVE_MESSAGING_BROKER_CONNECTION_OBJECT_MANAGER_CANCEL_REQUEST_TO_TRY_FOR_CONNECTION)
{
    m_brokerNames.push_back (brokerName);
}

WaveMessagingBrokerConnectionObjectManagerCancelRequestToTryForConnectionMessage::~WaveMessagingBrokerConnectionObjectManagerCancelRequestToTryForConnectionMessage ()
{
}

vector<string> WaveMessagingBrokerConnectionObjectManagerCancelRequestToTryForConnectionMessage::getBrokerNames () const
{
    return (m_brokerNames);
}

void WaveMessagingBrokerConnectionObjectManagerCancelRequestToTryForConnectionMessage::setBrokerNames (const vector<string> &brokerNames)
{
    m_brokerNames = brokerNames;
}

void WaveMessagingBrokerConnectionObjectManagerCancelRequestToTryForConnectionMessage::addBrokerNames (const vector<string> &brokerNames)
{
    m_brokerNames.insert (m_brokerNames.end (), brokerNames.begin (), brokerNames.end ());
}

void WaveMessagingBrokerConnectionObjectManagerCancelRequestToTryForConnectionMessage::addBrokerName (const string &brokerName)
{
    m_brokerNames.push_back (brokerName);
}

}
